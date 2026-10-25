"""tu_skeleton's merge lane: verified flags, redefinition repair, repointing and claims."""
import re
import sys
import tempfile
import unittest
from pathlib import Path
from types import SimpleNamespace
from unittest.mock import patch

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import tu_skeleton as T

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"


class RedefinitionTests(unittest.TestCase):
    def test_reads_type_typedef_and_enum_redefinitions(self):
        errors = [
            "a.cpp(7) : error C2011: 'Coord3D' : 'struct' type redefinition",
            "a.cpp(9) : error C2371: 'Real' : redefinition; different basic types",
            "a.cpp(11) : error C2365: 'BODY_PRISTINE' : redefinition; previous definition was 'enumerator'",
            "a.cpp(12) : error C2065: 'm_4' : undeclared identifier",
        ]
        self.assertEqual(T.redefined(errors), {"Coord3D", "Real", "BODY_PRISTINE"})

    def compose(self, drop=frozenset(), drop_all=frozenset()):
        texts = {"Seed.cpp": "struct Coord3D { float x, y, z; };\nint seed() { return 1; }\n",
                 "Donor.cpp": "struct Coord3D { float x, y, z; };\nint donor() { return 2; }\n"}
        return T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "first",
                         drop=drop, drop_all=drop_all)

    def test_drop_keeps_the_seed_copy_and_drop_all_removes_every_copy(self):
        # identical spellings are emitted once already
        self.assertEqual(self.compose().count("struct Coord3D"), 1)
        texts = {"Seed.cpp": "struct Coord3D { float x, y, z; };\n",
                 "Donor.cpp": "struct Coord3D { float x; float y; float z; float w; };\n"}
        both = T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "first")
        self.assertEqual(both.count("struct Coord3D"), 1)   # first spelling chosen
        kept = T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "longest",
                         drop=frozenset({"Coord3D"}))
        self.assertIn("float x, y, z;", kept)             # the seed's copy survives a drop
        gone = T.compose("Seed.cpp", [], ["Seed.cpp", "Donor.cpp"], texts, [], "longest",
                         drop_all=frozenset({"Coord3D"}))
        self.assertNotIn("struct Coord3D", gone)          # a header owns it


class EffectiveFlagsTests(unittest.TestCase):
    def verifier(self, overridden=False):
        v = T.Verifier.__new__(T.Verifier)
        fd = SimpleNamespace(
            MANAGED=re.compile(r"[-/](?:O[12xstdg]|arch:SSE2?|G[567B])$"),
            overrides=lambda: {"Code/T.cpp": {}} if overridden else {},
            region_at=lambda rva: {"opt": "O1", "arch": "SSE", "tune": "G7", "vote": "1"},
            _flag_set=lambda region: (region["opt"], region["arch"], region["tune"]),
            region_tokens=lambda region: ["-O1", "-arch:SSE", "-G7"])
        v.fd, v.tu_rel = fd, "Code/T.cpp"
        return v

    def test_region_codegen_replaces_the_line_and_keeps_other_tokens(self):
        text = "// cl: /O2 /MD /EHsc\nint f() { return 0; }\n"
        out = self.verifier().effective(text, [{"target_rva": "0x1000", "target_size": "8"}])
        self.assertTrue(out.startswith("// cl: /O1 /arch:SSE /G7 /MD /EHsc\n"))

    def test_an_overridden_tu_keeps_its_own_flags(self):
        text = "// cl: /O2 /MD\nint f() { return 0; }\n"
        self.assertEqual(self.verifier(True).effective(text, [{"target_rva": "0x1000", "target_size": "8"}]), text)

    def test_a_file_without_a_cl_line_gets_one(self):
        out = self.verifier().effective("int f() { return 0; }\n", [{"target_rva": "0x1000", "target_size": "8"}])
        self.assertTrue(out.startswith("// cl: /O1 /arch:SSE /G7\n"))


class RepointTests(unittest.TestCase):
    def test_apply_stages_the_refreshed_header_queue(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "Code").mkdir()
            (root / "reverse").mkdir()
            (root / "reverse/ms_header_queue.tsv").write_text("fixture\n")
            with patch("ms_header_audit.load_index", return_value={}) as index, \
                    patch("ms_header_audit.scan_text", return_value={"occ": []}) as scan, \
                    patch("ms_header_audit.refresh_queue", return_value=True) as refresh, \
                    patch.object(T.subprocess, "run") as run:
                moved = T.apply("Code/T.cpp", ["Code/A.cpp"], "int x;\n", root=root)
            index.assert_called_once()
            scan.assert_called_once_with("Code/T.cpp", "int x;\n", {})
            self.assertEqual(refresh.call_args.kwargs["removed"], ["Code/A.cpp"])
            self.assertEqual(refresh.call_args.kwargs["queue"], root / "reverse/ms_header_queue.tsv")
            self.assertEqual(moved, {"reverse/ms_header_queue.tsv": 1})
            self.assertEqual(run.call_args.args[0],
                             ["git", "add", "--", "Code/T.cpp", "reverse/ms_header_queue.tsv"])

    def test_every_path_keyed_column_and_the_doxygen_list_move_to_the_tu(self):
        with tempfile.TemporaryDirectory() as tmp:
            root = Path(tmp)
            (root / "reverse").mkdir()
            (root / "docs/doxygen").mkdir(parents=True)
            # Union-merged ledgers require LF on Windows as well as Unix.
            (root / "reverse/functions.csv").write_text(
                HEADER + "?a@@YAXXZ,,0x00001000,8,Code/A.cpp,matched,\n"
                "?b@@YAXXZ,,0x00001010,8,Code/B.cpp,matched,keeps Code/A.cpp in notes\n"
                "?c@@YAXXZ,,0x00001020,8,Code/C.cpp,matched,\n", encoding="utf-8", newline="\n")
            (root / "reverse/data_rows.csv").write_text(
                "name,address,address_kind,size,section,source,status,evidence,model\n"
                "?g@@3HA,0x00002000,rva,4,.data,Code/B.cpp,matched,,\n", encoding="utf-8", newline="\n")
            (root / "docs/doxygen/sources.cfg").write_text(
                "# list\nINPUT += Code/A.cpp\nINPUT += Code/B.cpp\nINPUT += Code/C.cpp\n")
            moved = T.repoint_all(root, ["Code/A.cpp", "Code/B.cpp"], "Code/T.cpp")
            self.assertEqual(moved, {"reverse/functions.csv": 2, "reverse/data_rows.csv": 1,
                                     "docs/doxygen/sources.cfg": 2})
            fn = (root / "reverse/functions.csv").read_text()
            self.assertIn("0x00001000,8,Code/T.cpp,", fn)
            self.assertIn("0x00001010,8,Code/T.cpp,matched,keeps Code/A.cpp in notes", fn)
            self.assertIn("Code/C.cpp", fn)
            self.assertIn(",Code/T.cpp,matched", (root / "reverse/data_rows.csv").read_text())
            self.assertEqual((root / "docs/doxygen/sources.cfg").read_text(),
                             "# list\nINPUT += Code/T.cpp\nINPUT += Code/C.cpp\n")

    def test_an_existing_tu_input_line_is_not_duplicated(self):
        raw = b"INPUT += Code/T.cpp\nINPUT += Code/A.cpp\n"
        out, n = T.repoint_sources_cfg(raw, {"Code/A.cpp"}, "Code/T.cpp")
        self.assertEqual((out, n), (b"INPUT += Code/T.cpp\n", 1))


class ClaimTests(unittest.TestCase):
    def test_the_scope_is_the_tu_every_donor_and_every_moved_row(self):
        don = {"Code/T.cpp": [{"target_rva": "0x00001000"}],
               "Code/A.cpp": [{"target_rva": "0x00001010"}, {"target_rva": "0x00001020"}]}
        self.assertEqual(T.claim_keys("Code/T.cpp", don),
                         ["file:Code/T.cpp", "file:Code/A.cpp", "0x00001000", "0x00001010", "0x00001020"])

    def test_a_held_key_blocks_the_merge_before_anything_is_written(self):
        don = {"Code/A.cpp": [{"target_rva": "0x00001010"}]}
        calls = []

        def claim(keys, note="", root=None):
            calls.append(keys)
            return SimpleNamespace(refused=[T.claims.key_of("file:Code/A.cpp")], claimed=[])

        original = T.claims.claim
        T.claims.claim = claim
        try:
            held = T.claim_scope("Code/T.cpp", don)
        finally:
            T.claims.claim = original
        self.assertEqual(held, ["file:Code/A.cpp"])
        self.assertEqual(len(calls), 1)

    def test_a_merge_blocked_after_claiming_releases_its_scope(self):
        don = {"Code/T.cpp": [{"target_rva": "0x00001000", "status": "matched"}],
               "Code/A.cpp": [{"target_rva": "0x00001010", "status": "matched"}]}
        released = []
        saved = (T.skeleton, T.donors, T.claim_scope, T._merge, T.claims.release)
        T.skeleton = lambda tu: []
        T.donors = lambda tu, sk: (don, {}, {})
        T.claim_scope = lambda tu, d: []
        T._merge = lambda tu, sk, d, report, dry_run: dict(report, blocked="no verified merge")
        T.claims.release = lambda keys, **kw: released.append(keys)
        try:
            report = T.merge("Code/T.cpp")
        finally:
            T.skeleton, T.donors, T.claim_scope, T._merge, T.claims.release = saved
        self.assertEqual(report["blocked"], "no verified merge")
        self.assertEqual(released, [T.claim_keys("Code/T.cpp", don)])


if __name__ == "__main__":
    unittest.main()
