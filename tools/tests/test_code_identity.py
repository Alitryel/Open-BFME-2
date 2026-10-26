"""Code identity: allowed-symbol classes, duplicate removal spans, alias and
register rules (tools/allowed_symbols.py, dup_defs.py, code_identity_gate.py)."""
import sys
import subprocess
import textwrap
import unittest
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import allowed_symbols as allowed  # noqa: E402
import code_identity_gate as gate  # noqa: E402
import dup_defs  # noqa: E402

OWNER = 0x1000      # row "?owner@@YAXXZ" at 0x1000, 0x20 bytes
OTHER = 0x2000      # no row, Ghidra function of 0x10 bytes


class FakeObj:
    path = Path("a.obj")
    by_name = {}


@pytest.mark.parametrize("entrypoint", ["stdin", "file"])
@pytest.mark.parametrize("malformed", [False, True], ids=["definitions", "strict-refusal"])
def test_definitions_from_spawn_entrypoints(tmp_path, entrypoint, malformed):
    """Historical hook scripts run via stdin; scan real COFF without a shared cache."""
    from test_gate_exploits import TEXT, coff

    raw = coff([(".text", TEXT, b"\xe8\0\0\0\0\xc3", [(1, 1, allowed.REL32)])],
               [("owner", 0, 1, 0x20, allowed.EXTERNAL, 0),
                ("callee", 0, 0, 0x20, allowed.EXTERNAL, 0)])
    for index in range(65):
        (tmp_path / f"{index:02}.obj").write_bytes(raw)
    if malformed:
        (tmp_path / "bad.obj").write_bytes(b"not a COFF object")
    script = textwrap.dedent(f"""
        import multiprocessing
        import sys
        from pathlib import Path
        sys.path.insert(0, {str(Path(allowed.__file__).parent)!r})
        import allowed_symbols as allowed

        def main():
            multiprocessing.set_start_method("spawn", force=True)
            root = Path(sys.argv[1])
            allowed.OUT = root / "isolated-cache"
            allowed.build._pool_size = lambda: 2
            objects = sorted(root.glob("*.obj"))
            malformed = sys.argv[2] == "True"
            try:
                found = allowed.definitions(objects, strict=True)
            except allowed.Unreadable as exc:
                assert malformed and "bad.obj" in str(exc), str(exc)
                print("strictly refused malformed COFF")
                return
            assert not malformed, "strict scan accepted a malformed object"
            assert list(found) == ["owner"], list(found)
            assert [row[0] for row in found["owner"]] == [str(p) for p in objects]
            assert all(row[2:] == (6, True) for row in found["owner"])
            assert len({{row[1] for row in found["owner"]}}) == 1
            assert found.referrers == {{"callee": {{str(p) for p in objects}}}}
            cached = allowed.definitions(objects, strict=True)
            assert cached == found and cached.referrers == found.referrers
            print("65 definitions and referrers preserved in link order")

        if __name__ == "__main__":
            main()
    """)
    if entrypoint == "file":
        runner = tmp_path / "scan.py"
        runner.write_text(script, encoding="utf-8")
        command, stdin = [sys.executable, str(runner)], None
    else:
        command, stdin = [sys.executable, "-"], script
    result = subprocess.run(command + [str(tmp_path), str(malformed)], input=stdin,
                            text=True, capture_output=True, timeout=45)
    assert result.returncode == 0, result.stdout + result.stderr
    expected = "strictly refused malformed COFF" if malformed else "65 definitions and referrers preserved"
    assert expected in result.stdout


class FakeIdentity(allowed.Identity):
    """Identity over a two-row ledger with scripted certification and definitions."""

    def __init__(self, defs, certified):
        self.at = {OWNER: [{"name": "?owner@@YAXXZ", "target_size": "32", "notes": "", "source": "a.cpp"}],
                   0x3000: [{"name": "?big@@YAXXZ", "target_size": "64", "notes": "", "source": "b.cpp"}]}
        self.spans = [(OWNER, OWNER + 32, self.at[OWNER][0]), (0x3000, 0x3040, self.at[0x3000][0])]
        self.span_starts = [OWNER, 0x3000]
        self.ghidra = {OWNER: 32, OTHER: 16, 0x3000: 64}
        self.defs = defs
        self._certified = certified
        self._gstarts = None

    def certify(self, path, name, t):
        return self._certified.get((name, t), "bytes")


ROW = {"name": "?caller@@YAXXZ", "notes": "", "source": "c.cpp"}
SYM = {"section": 1}


def ext(name):
    return {"name": name, "storage": allowed.EXTERNAL, "section": 0, "value": 0}


class ClassifyTests(unittest.TestCase):
    def classify(self, ref, t, defs=None, certified=None):
        ident = FakeIdentity(defs or {}, certified or {})
        return ident.classify(ROW, FakeObj(), SYM, 0, allowed.REL32, ref, t)

    def test_owner_name_is_allowed(self):
        self.assertEqual(self.classify(ext("?owner@@YAXXZ"), OWNER), ("owner", ""))

    def test_undefined_other_name_is_an_alias_to_the_owner(self):
        self.assertEqual(self.classify(ext("?pinned@@YAXXZ"), OWNER), ("alias", "?owner@@YAXXZ"))

    def test_other_name_defined_with_other_code_is_wrong(self):
        # the exploit: a pin makes the call byte-match, the link runs the other copy
        defs = {"?copy@@YAXXZ": [("x.obj", "d1", 20, True)]}
        self.assertEqual(self.classify(ext("?copy@@YAXXZ"), OWNER, defs), ("wrong", "bytes"))

    def test_certified_fold_is_allowed(self):
        defs = {"?twin@@YAXXZ": [("x.obj", "d1", 32, False)]}
        self.assertEqual(self.classify(ext("?twin@@YAXXZ"), OWNER, defs, {("?twin@@YAXXZ", OWNER): "retail"}),
                         ("fold", ""))

    def test_divergent_copies_are_their_own_class(self):
        defs = {"?inl@@YAXXZ": [("x.obj", "d1", 32, False), ("y.obj", "d2", 32, False)]}
        self.assertEqual(self.classify(ext("?inl@@YAXXZ"), OWNER, defs)[0], "divergent")

    def test_interior_target_is_wrong(self):
        self.assertEqual(self.classify(ext("?owner@@YAXXZ"), OWNER + 4), ("interior", "?owner@@YAXXZ+0x4"))

    def test_unowned_target(self):
        self.assertEqual(self.classify(ext("?gone@@YAXXZ"), OTHER), ("unowned", "undefined"))
        defs = {"?here@@YAXXZ": [("x.obj", "d1", 16, True)]}
        self.assertEqual(self.classify(ext("?here@@YAXXZ"), OTHER, defs, {("?here@@YAXXZ", OTHER): "retail"}),
                         ("unowned", "match"))

    def test_own_eh_and_labels(self):
        eh = {"name": "__ehhandler$?caller@@YAXXZ", "storage": allowed.STATIC, "section": 9, "value": 0}
        self.assertEqual(self.classify(eh, OTHER), ("eh", ""))
        foreign = dict(eh, name="__ehhandler$?someone@@YAXXZ")
        self.assertEqual(self.classify(foreign, OTHER), ("wrong", "foreign-eh"))
        label = {"name": "$L123", "storage": allowed.STATIC, "section": 1, "value": 8}
        self.assertEqual(self.classify(label, OWNER + 8)[0], "label")


class AlternatenameTests(unittest.TestCase):
    def test_alias_must_name_the_owner_of_its_one_target(self):
        ident = FakeIdentity({}, {})
        targets = {"?a@@YAXXZ": {OWNER}, "?b@@YAXXZ": {OWNER, 0x3000}}
        self.assertEqual(allowed.judge_alternatename(ident, "?a@@YAXXZ", "?owner@@YAXXZ", targets), "ok")
        self.assertEqual(allowed.judge_alternatename(ident, "?a@@YAXXZ", "?big@@YAXXZ", targets), "wrong")
        self.assertEqual(allowed.judge_alternatename(ident, "?b@@YAXXZ", "?owner@@YAXXZ", targets), "wrong")
        self.assertEqual(allowed.judge_alternatename(ident, "?c@@YAXXZ", "?owner@@YAXXZ", targets), "unreferenced")

    def test_generated_aliases_skip_names_with_two_targets(self):
        found = [(ROW, 0, 0, "?a@@YAXXZ", OWNER, "alias", "?owner@@YAXXZ"),
                 (ROW, 0, 0, "?b@@YAXXZ", OWNER, "alias", "?owner@@YAXXZ"),
                 (ROW, 0, 0, "?b@@YAXXZ", 0x3000, "alias", "?big@@YAXXZ")]
        self.assertEqual(allowed.alternatenames(found), {"?a@@YAXXZ": "?owner@@YAXXZ"})


class DefinitionSpanTests(unittest.TestCase):
    SRC = ("int keep() { return 1; }\n\n"
           "/**\n * doc\n */\n"
           "UnsignedInt FrameData::getCount() {\n\tif (x) { return '}'; }\n\treturn m;\n}\n\n"
           "void FrameData::other() {}\n")

    def test_removes_definition_and_its_comment(self):
        a, b = dup_defs.definition_span(self.SRC, "?getCount@FrameData@@QAEIXZ")
        self.assertEqual(self.SRC[:a] + self.SRC[b:], "int keep() { return 1; }\n\nvoid FrameData::other() {}\n")

    def test_refuses_overloads_templates_and_declarations(self):
        twice = self.SRC + "UnsignedInt FrameData::getCount(int) {}\n"
        self.assertIsNone(dup_defs.definition_span(twice, "?getCount@FrameData@@QAEIXZ"))
        self.assertIsNone(dup_defs.definition_span(self.SRC, "??$f@H@FrameData@@QAEXXZ"))
        self.assertIsNone(dup_defs.definition_span("void FrameData::getCount();\n", "?getCount@FrameData@@QAEIXZ"))


class RegisterTests(unittest.TestCase):
    def test_mode_and_keys(self):
        keys, mode = gate.read_register("# x\n# mode: enforce\na\tb\n\n")
        self.assertEqual((keys, mode), ({"a\tb"}, "enforce"))
        self.assertEqual(gate.read_register("")[1], "shadow")

    def test_dup_debt_keys(self):
        found = [{"class": "duplicate", "name": "a", "kept_verdict": "retail"},
                 {"class": "divergent", "name": "b", "kept_verdict": "retail"},
                 {"class": "divergent", "name": "c", "kept_verdict": "wrong"}]
        self.assertEqual(dup_defs.debt(found), {"duplicate\ta", "divergent\tc"})


class TierTests(unittest.TestCase):
    def tier(self, name, notes="", source="Code/x.cpp"):
        return allowed.name_tier({"name": name, "notes": notes, "source": source, "target_rva": "0x00001000"}, {})[0]

    def test_tiers(self):
        self.assertEqual(self.tier("?Rva00401000Get@@YAXXZ"), "address")
        self.assertEqual(self.tier("?dup_00401000@@YAXXZ"), "address")
        self.assertEqual(self.tier("_compress", "vendored=zlib-1.1.4"), "evidence")
        self.assertEqual(self.tier("?update@Foo@@UAEXXZ"), "unverified")


class LocalDataReceiptTests(unittest.TestCase):
    """Exercise actual COFF statics and RetailTruth's resolved-relocation check."""

    def certificate(self, *, data_storage=allowed.STATIC, writable=True,
                    bad_caller=False, bad_callback=False, conflicting=False,
                    foreign=False, missing=False, bad_callee=False,
                    truncated=False, code_data=False, outside=False):
        import struct
        import tempfile
        from unittest.mock import patch
        from test_gate_exploits import coff, TEXT

        caller = b"\xb9" + b"\0" * 4 + b"\xc3"
        callback = b"\xb9" + b"\0" * 4 + b"\xe9" + b"\0" * 4
        if bad_callback:
            callback = b"\xb8" + callback[1:]
        sections = [
            (".text", TEXT, caller, [(1, 2, allowed.DIR32)]),
            (".text", TEXT, callback,
             [(1, 2, allowed.DIR32), (6, 3, allowed.REL32)]),
            (".data", TEXT if code_data else (0xC0300040 if writable else 0x40301040), b"\0" * 4, []),
        ]
        symbols = [
            ("?caller@@YAXXZ", 0, 1, 32, allowed.EXTERNAL, 0),
            ("_$E4", 0, 2, 32, allowed.STATIC, 0),
            ("texture", 0, 3, 0, data_storage, 0),
            ("?release@@YAXXZ", 0, 0, 32, allowed.EXTERNAL, 0),
        ]
        rows = [{"name": "?caller@@YAXXZ", "source": "own.cpp",
                 "target_rva": "0x1000", "target_size": "6", "notes": ""}]
        memory = {
            0x1000: b"\xb9" + struct.pack("<I", allowed.BASE + 0x4000) + b"\xc3",
            0x2000: b"\xb9" + struct.pack("<I", allowed.BASE + 0x4000)
                    + b"\xe9" + struct.pack("<i", (0x3010 if bad_callee else 0x3000) - 0x200A),
        }
        if outside:
            memory[0x1000] = b"\xb9" + struct.pack("<I", allowed.BASE + 0x9000) + b"\xc3"
        if truncated:
            rows[0]["target_size"] = "5"
        if bad_caller:
            memory[0x1000] = b"\xb8" + memory[0x1000][1:]
        if conflicting:
            sections.append((".text", TEXT, caller, [(1, 2, allowed.DIR32)]))
            symbols.append(("?other@@YAXXZ", 0, 4, 32, allowed.EXTERNAL, 0))
            rows.append({"name": "?other@@YAXXZ", "source": "own.cpp",
                         "target_rva": "0x1100", "target_size": "6", "notes": ""})
            memory[0x1100] = b"\xb9" + struct.pack("<I", allowed.BASE + 0x4004) + b"\xc3"
        if foreign:
            rows[0]["source"] = "foreign.cpp"
        if missing:
            rows = []
        read = lambda rva, size: memory.get(rva, b"")[:size] or None
        truth = allowed.census.RetailTruth.__new__(allowed.census.RetailTruth)
        truth.ledger = {"?release@@YAXXZ": {0x3000}}
        truth.pinned, truth.import_routes, truth.import_thunks, truth.slots = {}, {}, {}, {}
        truth.shared = set()
        truth.sections = []
        truth._read = read
        ident = allowed.Identity.__new__(allowed.Identity)
        ident.rows = rows
        ident.secs = [{"name": ".text", "rva": 0x1000, "size": 0x2000},
                      {"name": ".data", "rva": 0x4000, "size": 0x1000}]
        ident._objcache, ident._certified, ident._extents, ident._local_data_cache = {}, {}, {}, {}
        ident.truth, ident.read = truth, read
        ident.extent = lambda target, size=None: 10
        with tempfile.TemporaryDirectory() as temp:
            path = Path(temp) / "own.obj"
            path.write_bytes(coff(sections, symbols))
            ident._rows_by_object = {str(path): [row for row in rows if row["source"] == "own.cpp"]}
            with patch.object(allowed, "row_object",
                              lambda row: path if row["source"] == "own.cpp" else Path(temp) / "foreign.obj"):
                verdict = ident.certify(str(path), "_$E4", 0x2000)
                self.assertEqual(ident._certified, {(str(path), "_$E4", 0x2000): verdict})
                self.assertEqual(ident.certify(str(path), "_$E4", 0x2000), verdict)
                # A receipt must not leak a synthetic/local binding into the
                # shared truth used to check external names in other objects.
                self.assertEqual(truth.ledger, {"?release@@YAXXZ": {0x3000}})
                return verdict

    def test_complete_matching_caller_certifies_local_shutdown_callback(self):
        self.assertEqual(self.certificate(), "retail")

    def test_same_local_name_in_another_object_supplies_no_receipt(self):
        self.assertEqual(self.certificate(foreign=True), "unknown")

    def test_missing_matching_caller_supplies_no_receipt(self):
        self.assertEqual(self.certificate(missing=True), "unknown")

    def test_conflicting_local_placements_supply_no_receipt(self):
        self.assertEqual(self.certificate(conflicting=True), "unknown")

    def test_nonmatching_caller_supplies_no_receipt(self):
        self.assertEqual(self.certificate(bad_caller=True), "unknown")

    def test_external_data_cannot_use_a_local_receipt(self):
        self.assertEqual(self.certificate(data_storage=allowed.EXTERNAL), "unknown")

    def test_readonly_data_cannot_use_a_writable_static_receipt(self):
        self.assertEqual(self.certificate(writable=False), "unknown")

    def test_truncated_caller_supplies_no_receipt(self):
        self.assertEqual(self.certificate(truncated=True), "unknown")

    def test_code_symbol_cannot_supply_a_data_receipt(self):
        self.assertEqual(self.certificate(code_data=True), "unknown")

    def test_out_of_image_data_address_supplies_no_receipt(self):
        self.assertEqual(self.certificate(outside=True), "unknown")

    def test_wrong_callback_instruction_is_still_refused(self):
        self.assertEqual(self.certificate(bad_callback=True), "bytes")

    def test_wrong_external_callee_is_still_refused(self):
        self.assertEqual(self.certificate(bad_callee=True), "bytes")


@pytest.mark.parametrize("case,expected", [
    ("direct", "retail"),
    ("tail_jump", "retail"),
    ("child_offset", "retail"),
    ("child_padding", "retail"),
    ("child_external", "retail"),
    ("wrong_child", "unknown"),
    ("wrong_parent", "bytes"),
    ("wrong_child_external", "unknown"),
    ("child_unknown_external", "unknown"),
    ("nested_static", "unknown"),
    ("same_section_grandchild", "unknown"),
    ("same_section_outside_addend", "unknown"),
    ("cycle", "unknown"),
    ("nonzero_addend", "unknown"),
    ("negative_addend", "unknown"),
    ("conflicting_sites", "unknown"),
    ("duplicate_name", "unknown"),
    ("overlapping_external", "bytes"),
    ("overlapping_child", "unknown"),
    ("opcode_in_immediate", "unknown"),
    ("nonfunction", "unknown"),
    ("noncode", "unknown"),
    ("external", "unknown"),
    ("missing_definition", "unknown"),
    ("invalid_symbol_index", "unknown"),
    ("missing_boundary", "unknown"),
    ("interior_target", "unknown"),
    ("outside_text", "unknown"),
    ("child_extent", "unknown"),
    ("parent_section_extent", "unknown"),
    ("child_section_extent", "unknown"),
    ("empty_child", "unknown"),
    ("child_crossing_relocation", "unknown"),
    ("child_trailing_relocation", "unknown"),
])
def test_static_call_certificate(tmp_path, case, expected):
    """Real COFF + RetailTruth: infer only a complete private direct callee."""
    import struct
    from test_gate_exploits import coff, TEXT

    parent = b"\xe8\0\0\0\0\xc3"
    child = b"\x33\xc0\xc3"
    parent_relocs, child_relocs = [(1, 1, allowed.REL32)], []
    child_section, child_storage, child_type, child_value = 2, allowed.STATIC, 0x20, 0
    child_flags, target = TEXT, 0x2000
    child_native = child
    if case == "tail_jump":
        parent = b"\xe9" + parent[1:]
    if case == "child_offset":
        child_value = 7
    if case == "child_padding":
        child += b"\xcc\x90"
    if case == "wrong_child":
        child = b"\x33\xc9\xc3"
    if case in ("child_external", "wrong_child_external", "child_unknown_external",
                "nested_static", "same_section_grandchild", "overlapping_child", "cycle"):
        child = b"\xe8\0\0\0\0\xc3"
        child_relocs = [(1, 0 if case == "cycle" else 2, allowed.REL32)]
        destination = (0x3010 if case == "wrong_child_external" else
                       0x1000 if case == "cycle" else
                       0x2006 if case == "same_section_grandchild" else 0x3000)
        child_native = b"\xe8" + struct.pack("<i", destination - 0x2005) + b"\xc3"
    if case == "same_section_outside_addend":
        child = b"\xe9\x06\0\0\0\xc3"
        child_native = b"\xe9\x01\0\0\0\xc3"
        child_relocs = [(1, 1, allowed.REL32)]
    if case in ("nonzero_addend", "negative_addend"):
        parent = b"\xe8" + struct.pack("<i", 1 if case == "nonzero_addend" else -1) + b"\xc3"
    if case == "conflicting_sites":
        parent = b"\xe8\0\0\0\0\xe8\0\0\0\0\xc3"
        parent_relocs.append((6, 1, allowed.REL32))
    if case == "opcode_in_immediate":
        parent = b"\xb8\xe8\0\0\0\0\xc3\xc3"
        parent_relocs = [(2, 1, allowed.REL32)]
    if case == "nonfunction":
        child_type = 0
    if case == "noncode":
        child_flags = 0xC0300040
    if case == "external":
        child_storage = allowed.EXTERNAL
    if case == "missing_definition":
        child_section = 0
    if case == "invalid_symbol_index":
        parent_relocs = [(1, 999, allowed.REL32)]
    if case == "child_extent":
        child += b"\xc3"
    if case == "empty_child":
        child = child_native = b""
    if case == "child_crossing_relocation":
        child_relocs.append((1, 2, allowed.DIR32))
    if case == "child_trailing_relocation":
        child += b"\x90" * 4
        child_relocs.append((3, 2, allowed.DIR32))
    if case == "overlapping_external":
        parent_relocs.append((1, 2, allowed.REL32))
    if case == "overlapping_child":
        child_relocs.append((1, 2, allowed.REL32))
    if case == "outside_text":
        target = 0x9000
    native_parent = bytearray(parent)
    for where, _, _ in parent_relocs:
        dest = 0x2100 if case == "conflicting_sites" and where == 6 else target
        struct.pack_into("<i", native_parent, where,
                         dest - (0x1000 + where + 4) + struct.unpack_from("<i", parent, where)[0])
    if case == "wrong_parent":
        native_parent[-1] = 0x90
    sections = [
        (".text", TEXT, parent, parent_relocs),
        (".text", child_flags, b"\xcc" * child_value + child, child_relocs),
    ]
    symbols = [
        ("_parent", 0, 1, 0x20, allowed.STATIC if case == "cycle" else allowed.EXTERNAL, 0),
        ("_helper", child_value, child_section, child_type, child_storage, 0),
        ("_external", 0, 3 if case == "nested_static" else 0, 0x20,
         allowed.STATIC if case == "nested_static" else allowed.EXTERNAL, 0),
    ]
    if case == "nested_static":
        sections.append((".text", TEXT, b"\x33\xc0\xc3", []))
    if case == "same_section_grandchild":
        sections[1] = (".text", TEXT, child + b"\x33\xc0\xc3", child_relocs)
        symbols[2] = ("_external", len(child), 2, 0x20, allowed.STATIC, 0)
    if case == "duplicate_name":
        sections.append((".text", TEXT, b"\x33\xc9\xc3", []))
        symbols.append(("_helper", 0, 3, 0x20, allowed.STATIC, 0))
        parent_relocs[0] = (1, 3, allowed.REL32)
    if case == "child_section_extent":
        symbols.append(("_past_section", len(child), 2, 0x20, allowed.STATIC, 0))
    if case == "parent_section_extent":
        symbols.append(("_past_parent_section", len(parent), 1, 0x20, allowed.STATIC, 0))
    path = tmp_path / "own.obj"
    object_data = bytearray(coff(sections, symbols))
    if case == "child_section_extent":
        struct.pack_into("<I", object_data, 20 + 40 + 16, 1)
    if case == "parent_section_extent":
        struct.pack_into("<I", object_data, 20 + 16, 1)
    path.write_bytes(object_data)
    memory = {0x1000: bytes(native_parent), target: child_native,
              0x2100: child_native, 0x3000: b"\x33\xc0\xc3"}
    read = lambda rva, size: memory.get(rva, b"")[:size] or None
    truth = allowed.census.RetailTruth.__new__(allowed.census.RetailTruth)
    truth.ledger = {} if case == "child_unknown_external" else {"_external": {0x3000}}
    truth.pinned, truth.import_routes, truth.import_thunks, truth.slots = {}, {}, {}, {}
    truth.shared, truth.sections, truth._read = set(), [], read
    original = {k: set(v) for k, v in truth.ledger.items()}
    ident = allowed.Identity.__new__(allowed.Identity)
    ident.truth, ident.read, ident.text = truth, read, (0x1000, 0x4000)
    ident.rows, ident.secs = [], []
    ident.at = {0x1000: [{"target_size": str(len(parent))}],
                target: [{"target_size": str(len(child_native))}]}
    if case == "missing_boundary":
        del ident.at[target]
    ident.ghidra = {}
    ident.spans = [(0x1000, 0x1000 + len(parent), ident.at[0x1000][0])]
    if case == "interior_target":
        ident.spans.append((0x1FF0, 0x2010, {"name": "_containing"}))
    ident.span_starts = [s[0] for s in ident.spans]
    ident._objcache, ident._certified, ident._extents = {}, {}, {}
    ident._local_data_cache, ident._rows_by_object, ident._fold_pins = {}, {}, {}
    assert ident.certify(str(path), "_parent", 0x1000) == expected
    assert ident.certify(str(path), "_parent", 0x1000) == expected
    assert truth.ledger == original
    assert list(ident._certified) == [(str(path), "_parent", 0x1000)]


def test_static_call_missing_body_is_not_a_certificate():
    ident = allowed.Identity.__new__(allowed.Identity)
    assert ident.static_call_bindings(None, None, None, [], 0x1000) == ({}, {})


# ---- the registers' mode, reseed and flip (code_identity_gate.py), over a fixture repository

import os  # noqa: E402
import subprocess  # noqa: E402

OLD_KEY = "Code/a.cpp\t?a@@YAXXZ\t?x@@YAXXZ\t0x00001000\twrong"
NEW_ROW = {"source": "Code/b.cpp", "name": "?b@@YAXXZ"}


def _git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="",
               GIT_COMMITTER_EMAIL="")
    got = subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, env=env)
    assert got.returncode == 0, got.stderr
    return got.stdout


class _Ident:
    defs = {}
    truth = None


@pytest.fixture
def registers(tmp_path, monkeypatch):
    """A repository whose registers are committed in shadow; the scans are scripted: `found`
    is what allowed_symbols.scan reports, `dup` the dup_defs debt keys."""
    (tmp_path / "reverse").mkdir()
    base = tmp_path / "reverse" / "code_identity_baseline.tsv"
    dup = tmp_path / "reverse" / "dup_defs_baseline.tsv"
    base.write_text(gate.HEADER + "# mode: shadow\n" + OLD_KEY + "\n", newline="\n")
    dup.write_text(dup_defs.HEADER + "duplicate\t?old@@3HA\n", newline="\n")
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "config", "core.autocrlf", "false")
    _git(tmp_path, "add", ".")
    _git(tmp_path, "commit", "-qm", "init")
    monkeypatch.setattr(gate, "ROOT", tmp_path)
    monkeypatch.setattr(gate, "BASELINE", base)
    monkeypatch.setattr(dup_defs, "BASELINE", dup)
    state = {"found": [], "dup": {"duplicate\t?old@@3HA"}, "ledger": []}
    monkeypatch.setattr(allowed, "load", lambda sources=None: (_Ident(), []))
    monkeypatch.setattr(allowed, "scan", lambda ident, rows: list(state["found"]))
    monkeypatch.setattr(allowed.census, "ledger", lambda: list(state["ledger"]))
    monkeypatch.setattr(dup_defs, "analyse", lambda rows, defs, truth: [])
    monkeypatch.setattr(dup_defs, "debt", lambda found: set(state["dup"]))
    monkeypatch.setattr(gate, "added_alternatenames", lambda: [])
    monkeypatch.chdir(tmp_path)
    state["root"], state["base"], state["dup_path"] = tmp_path, base, dup
    return state


def _finding(row):
    return (row, 0, allowed.REL32, "?x@@YAXXZ", 0x2000, "wrong", "")


def _set(path, mode, *keys):
    path.write_text(gate.HEADER + f"# mode: {mode}\n" + "".join(k + "\n" for k in keys), newline="\n")


NAMES = ["reverse/code_identity_baseline.tsv"]


def test_reseed_and_flip_land_as_one_commit(registers):
    registers["found"] = [_finding(NEW_ROW)]                       # drift the shadow register never saw
    registers["dup"] = {"duplicate\t?old@@3HA", "duplicate\t?new@@3HA"}
    assert gate.main(["--reseed", "--mode", "enforce"]) == 0
    text = registers["base"].read_text()
    assert "# mode: enforce" in text and "Code/b.cpp\t?b@@YAXXZ" in text and OLD_KEY not in text
    assert "?new@@3HA" in registers["dup_path"].read_text()
    _git(registers["root"], "add", ".")
    notes = []
    problems, mode, *_ = gate.check([], NAMES + ["reverse/dup_defs_baseline.tsv"], staged=True, notes=notes)
    assert problems == [] and mode == "enforce"                    # HEAD in shadow: the growth is the reseed
    assert any("grew by 1 key(s) while HEAD's register is in shadow" in n for n in notes)
    _git(registers["root"], "commit", "-qm", "flip")
    with pytest.raises(SystemExit, match="never reseeded"):        # one-way
        gate.main(["--reseed"])


def test_an_enforced_register_only_shrinks_and_never_goes_back(registers):
    _set(registers["base"], "enforce", OLD_KEY)
    _git(registers["root"], "commit", "-qam", "enforce")
    _set(registers["base"], "enforce", OLD_KEY, "Code/b.cpp\t?b@@YAXXZ\t?x@@YAXXZ\t0x00002000\twrong")
    _git(registers["root"], "add", ".")
    problems, mode, *_ = gate.check([], NAMES, staged=True)
    assert mode == "enforce" and any("grew by 1 key(s); an enforced register only shrinks" in p for p in problems)
    _set(registers["base"], "shadow", OLD_KEY)
    _git(registers["root"], "add", ".")
    problems, mode, *_ = gate.check([], NAMES, staged=True)
    assert mode == "enforce" and any("may not go back" in p for p in problems)
    _set(registers["base"], "enforce")                             # shrinking is fine
    _git(registers["root"], "add", ".")
    assert gate.check([], NAMES, staged=True)[0] == []


def test_the_mode_is_the_staged_registers_not_the_working_copy(registers):
    _set(registers["base"], "enforce", OLD_KEY)
    _git(registers["root"], "add", ".")
    _set(registers["base"], "shadow", OLD_KEY)                     # unstaged edit back to shadow
    registers["found"] = [_finding(NEW_ROW)]
    problems, mode, *_ = gate.check([], [], staged=True)
    assert mode == "enforce" and any(p.startswith("binding: Code/b.cpp") for p in problems)


def test_enforced_refusal_says_what_to_do(registers, capsys):
    _set(registers["base"], "enforce", OLD_KEY)
    _git(registers["root"], "commit", "-qam", "enforce")
    registers["found"] = [_finding(NEW_ROW)]
    assert gate.main(["--full"]) == 1
    err = capsys.readouterr().err
    assert "REFUSED" in err and "allowed_symbols.py --source FILE" in err and "false-reject" in err
    registers["found"] = []
    assert gate.main(["--full"]) == 0


HAND_KEY = "Code/c.cpp\t?c@@YAXXZ\t?x@@YAXXZ\t0x00003000\twrong"


@pytest.mark.parametrize("mode", ["enforce", "shadow"])
def test_a_hand_grown_register_is_no_reseed_in_either_mode(registers, mode):
    # HEAD in shadow: growth is taken only as an exact scan of the staged tree. A key typed in
    # (a register-only change: no source staged, so the ordinary scan reads nothing) is refused,
    # staged as the flip or still in shadow.
    _set(registers["base"], mode, OLD_KEY, HAND_KEY)
    _git(registers["root"], "add", ".")
    sources, names = gate.staged_sources()
    assert sources == [] and "reverse/code_identity_baseline.tsv" in names
    problems, got_mode, *_ = gate.check(sources, names, staged=True)
    assert got_mode == "enforce" and any("not exactly the staged tree's scan" in p for p in problems)


def test_a_flip_that_is_not_the_scan_is_refused(registers):
    _set(registers["base"], "enforce", OLD_KEY)          # no growth, but the scan no longer finds OLD_KEY
    _git(registers["root"], "add", ".")
    problems, mode, *_ = gate.check([], NAMES, staged=True)
    assert mode == "enforce" and any("not exactly the staged tree's scan" in p for p in problems)
    registers["found"] = [_finding({"source": "Code/a.cpp", "name": "?a@@YAXXZ"})]
    _set(registers["base"], "enforce", allowed.key(registers["found"][0]))   # the tool's own output passes
    _git(registers["root"], "add", ".")
    assert gate.check([], NAMES, staged=True)[0] == []


def test_a_reseed_staged_over_unstaged_sources_or_missing_objects_is_refused(registers):
    (registers["root"] / "Code").mkdir()
    (registers["root"] / "Code/a.cpp").write_text("int a;\n", newline="\n")
    _git(registers["root"], "add", ".")
    _git(registers["root"], "commit", "-qm", "source")
    assert gate.main(["--reseed", "--mode", "enforce"]) == 0
    _git(registers["root"], "add", ".")
    (registers["root"] / "Code/a.cpp").write_text("int a, b;\n", newline="\n")    # not staged
    problems, mode, *_ = gate.check([], NAMES, staged=True)
    assert mode == "enforce" and any("differ from the index (Code/a.cpp)" in p for p in problems)
    _git(registers["root"], "checkout", "--", "Code/a.cpp")
    registers["ledger"] = [{"source": "Code/never_built.cpp", "name": "?n@@YAXXZ", "target_rva": "0x00001000",
                            "target_size": "4", "notes": "", "status": "matched"}]
    problems, mode, *_ = gate.check([], NAMES, staged=True)
    assert mode == "enforce" and any("have no current object" in p for p in problems)


@pytest.mark.parametrize("which", ["reverse/code_identity_baseline.tsv", "reverse/dup_defs_baseline.tsv"])
def test_a_deleted_register_is_refused(registers, which):
    _git(registers["root"], "rm", "-q", "--cached", which)
    sources, names = gate.staged_sources()
    assert which in names                                # deletions are staged names too
    problems, mode, *_ = gate.check(sources, names, staged=True)
    assert mode == "enforce" and any(p.startswith(which + " deleted") for p in problems)


def test_a_downgrade_is_refused_and_judged_as_enforced(registers):
    _set(registers["base"], "enforce", OLD_KEY)
    _git(registers["root"], "commit", "-qam", "enforce")
    _set(registers["base"], "shadow", OLD_KEY)
    _git(registers["root"], "add", ".")
    registers["found"] = [_finding(NEW_ROW)]
    problems, mode, *_ = gate.check([], NAMES, staged=True)
    assert mode == "enforce"
    assert any("may not go back" in p for p in problems) and any(p.startswith("binding: Code/b.cpp") for p in problems)


def test_reseed_refuses_an_incomplete_tree(registers):
    registers["ledger"] = [{"source": "Code/never_built.cpp", "name": "?n@@YAXXZ", "target_rva": "0x00001000",
                            "target_size": "4", "notes": "", "status": "matched"}]
    before = registers["base"].read_text()
    with pytest.raises(SystemExit, match="no current object"):
        gate.main(["--reseed", "--mode", "enforce"])
    assert registers["base"].read_text() == before


def test_reseed_cannot_hide_an_enforced_head_with_a_shadow_working_copy(registers):
    _set(registers["base"], "enforce", OLD_KEY)
    _git(registers["root"], "commit", "-qam", "enforced")
    _set(registers["base"], "shadow", OLD_KEY)
    before = registers["base"].read_bytes(), registers["dup_path"].read_bytes()
    with pytest.raises(SystemExit, match="never reseeded"):
        gate.main(["--reseed"])
    assert (registers["base"].read_bytes(), registers["dup_path"].read_bytes()) == before


@pytest.mark.parametrize("current", [False, True])
def test_register_only_reseed_scans_every_source_and_requires_current_objects(registers, monkeypatch, current):
    row = {**NEW_ROW, "target_rva": "0x00002000", "target_size": "4", "notes": "", "status": "matched"}
    registers["ledger"] = [row]
    registers["found"] = [_finding(row)]
    obj = registers["root"] / "b.obj"
    obj.write_bytes(b"fixture object")
    monkeypatch.setattr(allowed, "row_object", lambda row: obj)
    monkeypatch.setattr(allowed.build, "compile_is_current", lambda source, path: current)
    calls = []
    def load(sources=None):
        calls.append(sources)
        return _Ident(), [row] if sources is None else []
    monkeypatch.setattr(allowed, "load", load)
    _set(registers["base"], "enforce", allowed.key(registers["found"][0]))
    _git(registers["root"], "add", ".")
    problems, mode, *_ = gate.check([], NAMES, staged=True)
    assert mode == "enforce"
    if current:
        assert problems == []
        assert calls == [["<none>"], None]  # baseline-only changes still require the whole ledger
    else:
        assert any("have no current object" in p for p in problems)


def test_duplicate_register_only_growth_requires_the_exact_full_scan(registers):
    registers["dup_path"].write_text(dup_defs.HEADER + "duplicate\t?typed@@3HA\n", newline="\n")
    _git(registers["root"], "add", ".")
    sources, names = gate.staged_sources()
    problems, mode, *_ = gate.check(sources, names, staged=True)
    assert mode == "enforce"
    assert any("reverse/dup_defs_baseline.tsv is not exactly" in p for p in problems)


def test_main_rejects_a_deleted_register_even_while_head_is_shadow(registers, monkeypatch):
    _git(registers["root"], "rm", "-q", "--cached", NAMES[0])
    monkeypatch.setattr(allowed.build, "compile_rows", lambda *args: None)
    assert gate.main(["--staged"]) == 1


if __name__ == "__main__":
    unittest.main()
