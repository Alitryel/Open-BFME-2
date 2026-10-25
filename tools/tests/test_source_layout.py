"""Adversarial routing and snapshot tests; no compiler or production ledger writes."""
import csv
import io
import json
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import source_layout as layout


HOME = "Code/GameEngine/Source/Common/Box.cpp"
OTHER = "Code/GameEngine/Source/Common/Other.cpp"
SOURCE = "Code/GameEngine/Source/Common/Fragment.cpp"


def write(root, name, text):
    path = root / name
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(text, encoding="utf-8", newline="")
    return path


def ledger(root, rows):
    text = layout.csv_text([
        dict(name=name, target_rva=f"0x{rva:08X}", target_size=size, source=source,
             status="matched", notes=notes)
        for name, rva, size, source, notes in rows
    ], ("name", "target_rva", "target_size", "source", "status", "notes"))
    write(root, "reverse/functions.csv", text)


def mapped(root, rows):
    write(root, "reverse/tu_map.csv", layout.csv_text([
        dict(rva=f"0x{rva:08X}", kind="code", tu=target, confidence=confidence,
             evidence=evidence, source=source, size=20, by="F")
        for rva, target, confidence, evidence, source in rows
    ], tu_columns()))


def tu_columns():
    return ("rva", "size", "kind", "tu", "confidence", "by", "evidence", "source")


def pe(root, name="retail.exe"):
    data = bytearray(0xa00)
    data[:2] = b"MZ"
    struct.pack_into("<I", data, 0x3c, 0x80)
    data[0x80:0x84] = b"PE\0\0"
    struct.pack_into("<H", data, 0x86, 2)
    struct.pack_into("<H", data, 0x94, 0xe0)
    struct.pack_into("<H", data, 0x98, 0x10b)
    struct.pack_into("<I", data, 0xb4, 0x400000)
    for off, va, raw, flags in ((0x178, 0x1000, 0x200, 0x60000020),
                                (0x1a0, 0x2000, 0x600, 0x40000040)):
        struct.pack_into("<IIII", data, off + 8, 0x400, va, 0x400, raw)
        struct.pack_into("<I", data, off + 36, flags)
    path = r"C:\projects\bfme2\Code\GameEngine\Source\Common\Box.cpp"
    encoded = path.encode("ascii") + b"\0"
    data[0x600:0x600 + len(encoded)] = encoded
    wide = (r"Z:\Code\GameEngine\Include\Box.h" + "\0").encode("utf-16le")
    data[0x700:0x700 + len(wide)] = wide
    data[0x200:0x205] = b"\x68" + struct.pack("<I", 0x402000)
    out = root / name
    out.parent.mkdir(parents=True, exist_ok=True)
    out.write_bytes(data)
    if name == layout.IMAGE_DIR + "/game.dat":
        write(root, "baselines/bfme2/workshop-vanilla-1.06/manifest.json", json.dumps({"files": [
            dict(path="files/game.dat", size=len(data), sha256=layout.digest(data))]}))
    return out, path


def planning(root, **kwargs):
    result = layout.plan(root, kwargs.pop("under", "Code/"), kwargs.pop("cat", layout.Catalogue()),
                       kwargs.pop("image", None), kwargs.pop("image_paths", []),
                       kwargs.pop("zh", {}), kwargs.pop("bfme1", {}), kwargs.pop("fresh", True))
    return result[0], result[1], result[3]


@pytest.mark.parametrize("path", ["Code/../owned.cpp", "Code/Bad/NUL.cpp", "Code/C:/x.cpp",
                                  "/tmp/x.cpp", "Code/x.cpp/../../y.cpp", "Code/x.h\x00.cpp",
                                  "Code/Trailing./x.cpp", "Code/x.exe"])
def test_paths_cannot_escape_or_name_windows_devices(path):
    with pytest.raises(ValueError):
        layout.canonical_path(path)


def test_image_catalogue_keeps_raw_occurrences_offsets_and_wide_headers(tmp_path):
    path, raw = pe(tmp_path)
    image = layout.Image(path)
    paths = image.paths("retail")
    assert len(paths) == 2
    cpp = next(p for p in paths if p["path"] == HOME)
    assert cpp["raw_path"] == raw
    assert cpp["offset"] == "0x00000600"
    assert cpp["string_rva"] == "0x00002000"
    assert next(p for p in paths if p["path"].endswith(".h"))["encoding"] == "utf-16le"
    assert image.literal_reference(0x1000, {0x2000})
    assert not image.literal_reference(0x1001, {0x2000})
    assert not image.literal_reference(0x1000, {0x2010})
    assert not image.literal_reference(0x2000, {0x2000})  # non-executable section


def test_verified_reference_requires_current_literal_not_xref_prose(tmp_path):
    path, raw = pe(tmp_path)
    image = layout.Image(path)
    write(tmp_path, "reverse/string_xrefs.tsv", raw + "\t0x1000,0x1008\n")
    rows = {SOURCE: [dict(rva=0x1000, size=20)]}
    assert layout.direct_references(tmp_path, image, image.paths("retail"), rows) == {(0x1000, 20): {(HOME, 0x1000)}}
    data = bytearray(path.read_bytes())
    data[0x201:0x205] = struct.pack("<I", 0x402010)
    path.write_bytes(data)
    assert not layout.direct_references(tmp_path, layout.Image(path), image.paths("retail"), rows)


def test_owner_xref_decodes_instructions_and_cannot_borrow_longer_twins_extent(tmp_path):
    path, raw = pe(tmp_path)
    data = bytearray(path.read_bytes())
    data[0x200:0x20c] = b"\x55\x8b\xec\x90\x90\x68" + struct.pack("<I", 0x402000) + b"\xc3\x90"
    path.write_bytes(data)
    image = layout.Image(path)
    write(tmp_path, "reverse/string_xrefs.tsv", raw + "\t0x1000\n")
    rows = {SOURCE: [dict(rva=0x1000, size=5), dict(rva=0x1000, size=20)]}
    refs = layout.direct_references(tmp_path, image, image.paths("retail"), rows)
    assert refs == {(0x1000, 20): {(HOME, 0x1005)}}


def test_stale_naming_convention_guess_does_not_invent_an_original_filename():
    row = dict(rva=0x1000, name="?f@Box@@QAEXXZ")
    mapping = {0x1000: [dict(tu=HOME, confidence="proposed", evidence=f"N={HOME}", rva="0x1000")]}
    assert not layout.row_route(row, {}, mapping, False, {}, {}, {}, layout.Catalogue())["target"]


def test_conflicting_target_facts_cannot_be_voted_away():
    row = dict(rva=0x1000, size=20, name="?f@Box@@QAEXXZ")
    mapping = {0x1000: [dict(tu=OTHER, confidence="approved", evidence=f"F={OTHER}", rva="0x1000")]}
    route = layout.row_route(row, {(0x1000, 20): {(HOME, 0x1000)}}, mapping, True, {}, {}, {}, layout.Catalogue())
    assert route["conflict"] and not route["target"]


def test_stale_map_never_has_target_strength():
    row = dict(rva=0x1000, name="?f@Box@@QAEXXZ")
    mapping = {0x1000: [dict(tu=HOME, confidence="approved", evidence=f"F={HOME}", rva="0x1000")]}
    route = layout.row_route(row, {}, mapping, False, {}, {}, {}, layout.Catalogue())
    assert route["target"] == HOME and route["strength"] == "hint"
    assert any("stale-tu-map" in e for e in route["evidence"])


def test_target_reference_beats_donor_hint_without_erasing_disagreement():
    row = dict(rva=0x1000, size=20, name="?f@Box@@QAEXXZ")
    route = layout.row_route(row, {(0x1000, 20): {(HOME, 0x1000)}}, {}, True, {("Box", "f"): {OTHER}}, {}, {}, layout.Catalogue())
    assert route["target"] == HOME and route["strength"] == "target"
    assert route["alternatives"] == sorted([HOME, OTHER])


def test_bfme1_rvas_do_not_cross_games_and_run_paths_are_only_catalogued(tmp_path):
    bfme1 = tmp_path / "bfme1"
    write(bfme1, "targets/game/reverse/ea_evidence.csv",
          "rva,kind,value,route,basis\n"
          "0x99,file,GameEngine/Source/Common/Box.cpp,wb1,\n"
          "0x99,name,Box::f,wb1,strong\n"
          "0x88,file,GameEngine/Source/Common/Other.cpp,retail-run,\n"
          "0x88,name,Box::f,wb1,strong\n")
    cat = layout.Catalogue()
    _, hints = layout.donor_index(None, bfme1, cat)
    assert hints == {"Box::f": {HOME}}
    assert OTHER.casefold() in cat.entries  # retained with its route, not used to route
    route = layout.row_route(dict(rva=0x99, name="?g@Else@@QAEXXZ"), {}, {}, True,
                             {}, hints, {}, cat)
    assert route["strength"] == "unresolved"


def test_header_is_never_a_destination():
    row = dict(rva=0x1000, size=20, name="?f@Box@@QAEXXZ")
    route = layout.row_route(row, {(0x1000, 20): {("Code/GameEngine/Include/Box.h", 0x1000)}}, {}, True,
                             {}, {}, {}, layout.Catalogue())
    assert not route["target"]


def test_mixed_file_is_not_a_whole_file_move(tmp_path):
    write(tmp_path, SOURCE, "// cl: /O1\nvoid f() {}\nvoid g() {}\n")
    ledger(tmp_path, [("?f@Box@@QAEXXZ", 0x1000, 20, SOURCE, ""),
                      ("?g@Else@@QAEXXZ", 0x1100, 20, SOURCE, "")])
    queue, groups, _ = planning(tmp_path, zh={("Box", "f"): {HOME}})
    assert queue[0]["state"] == "mixed-or-incomplete" and not queue[0]["target"]
    assert len(groups) == 1 and not groups[0]["files"][0]["complete"]
    assert any("mixed-or-incomplete-routing" in b for b in groups[0]["blockers"])
    assert not groups[0]["verified"]


def test_two_destinations_keep_every_row_and_block_both_groups(tmp_path):
    write(tmp_path, SOURCE, "void f() {}\nvoid g() {}\n")
    ledger(tmp_path, [("?f@Box@@QAEXXZ", 0x1000, 20, SOURCE, ""),
                      ("?g@Else@@QAEXXZ", 0x1100, 20, SOURCE, "")])
    _, groups, packets = planning(tmp_path, zh={("Box", "f"): {HOME}, ("Else", "g"): {OTHER}})
    assert len(groups) == 2
    assert len(packets[0]["rows"]) == 2
    assert all(any("mixed-or-incomplete-routing" in b for b in g["blockers"]) for g in groups)


def test_attached_funclet_cannot_nominate_a_different_file(tmp_path):
    write(tmp_path, SOURCE, "void f() {}\n")
    ledger(tmp_path, [("?f@Box@@QAEXXZ", 0x1000, 20, SOURCE, ""),
                      ("__unwindfunclet$1", 0x1100, 10, SOURCE, "parent=?f@Box@@QAEXXZ")])
    queue, groups, packets = planning(tmp_path, zh={("Box", "f"): {HOME}})
    assert queue[0]["state"] == "whole-file-candidate"
    assert len(packets[0]["rows"]) == 2  # packet still retains the funclet


def test_duplicate_views_and_flags_require_reconciliation(tmp_path):
    other_source = SOURCE.replace("Fragment", "Fragment2")
    write(tmp_path, SOURCE, "// cl: /O1\nstruct Box { int x; };\n")
    write(tmp_path, other_source, "// cl: /O2\nstruct Box { int y; };\n")
    ledger(tmp_path, [("?f@Box@@QAEXXZ", 0x1000, 20, SOURCE, ""),
                      ("?g@Box@@QAEXXZ", 0x1100, 20, other_source, "")])
    _, groups, _ = planning(tmp_path, zh={("Box", "f"): {HOME}, ("Box", "g"): {HOME}})
    assert any("duplicate-type-definitions: Box" == b for b in groups[0]["blockers"])
    assert any("compiler-settings-disagree" in b for b in groups[0]["blockers"])


def test_case_and_path_keyed_registers_are_visible(tmp_path):
    write(tmp_path, SOURCE, "void f() {}\n")
    write(tmp_path, HOME.lower().replace("code/", "Code/"), "void resident() {}\n")
    write(tmp_path, "reverse/flag_overrides.csv", "source,flags\n" + SOURCE + ",/O1\n")
    ledger(tmp_path, [("?f@Box@@QAEXXZ", 0x1000, 20, SOURCE, "")])
    _, groups, _ = planning(tmp_path, zh={("Box", "f"): {HOME}})
    assert any("case-spelling-conflict" in b for b in groups[0]["blockers"])
    assert any("path-keyed-registers" in b for b in groups[0]["blockers"])


def test_implementation_includers_and_data_ownership_are_preserved(tmp_path):
    write(tmp_path, SOURCE, "void f() {}\n")
    consumer = SOURCE.replace("Fragment", "Consumer")
    write(tmp_path, consumer, '#include "Fragment.cpp"\n')
    write(tmp_path, "reverse/data_rows.csv", "name,address,address_kind,status,source\n"
          f"g_data,0x9000,rva,matched,{SOURCE}\n")
    ledger(tmp_path, [("?f@Box@@QAEXXZ", 0x1000, 20, SOURCE, "")])
    _, groups, packets = planning(tmp_path, zh={("Box", "f"): {HOME}})
    assert any("included-by: " + consumer in b for b in groups[0]["blockers"])
    assert any("data-ownership-review" in b for b in groups[0]["blockers"])
    assert packets[0]["data_rows"][0]["name"] == "g_data"
    assert packets[0]["included_by"] == [consumer]


def test_commented_include_is_not_a_dependency(tmp_path):
    write(tmp_path, SOURCE, '/*\n#include "Ghost.cpp"\n*/\nvoid f() {}\n')
    assert not layout.source_info(tmp_path, SOURCE, [], {})["includes"]


def test_existing_destination_has_a_packet_even_outside_selected_ledger(tmp_path):
    write(tmp_path, SOURCE, "void f() {}\n")
    write(tmp_path, HOME, "void unledgered() {}\n")
    ledger(tmp_path, [("?f@Box@@QAEXXZ", 0x1000, 20, SOURCE, "")])
    _, groups, packets = planning(tmp_path, zh={("Box", "f"): {HOME}})
    assert all(f["packet_key"] in {p["source"] for p in packets} for f in groups[0]["files"])
    assert next(p for p in packets if p["source"] == HOME)["scope"] == "outside-selected-active-ledger"
    assert any("destination-not-in-selected-active-ledger" in b for b in groups[0]["blockers"])


def test_macro_line_assembly_include_and_static_contexts_are_reported(tmp_path):
    write(tmp_path, SOURCE, '#include "Local.h"\n#define X 1\nstatic int x;\nvoid f() { __asm nop; use(__LINE__); }\n')
    blockers = layout.source_info(tmp_path, SOURCE, [], {})["blockers"]
    assert any("assembly-or-lift" in b for b in blockers)
    assert "path-or-line-sensitive" in blockers
    assert "internal-linkage-review" in blockers
    assert "macro-or-pragma-context" in blockers
    assert "quoted-include-resolution-review" in blockers


def test_no_file_reduction_is_claimed_for_overlapping_rows():
    assert layout.interval_bytes([dict(rva=10, size=20), dict(rva=10, size=20), dict(rva=25, size=20)]) == 35


@pytest.mark.parametrize("out", ["Code", "reverse", ".git", "build/consolidation/../../Code"])
def test_output_cannot_overwrite_sources_or_ledgers(tmp_path, out):
    with pytest.raises(ValueError):
        layout.output_dir(tmp_path, out)


def test_rotwk_data_never_manufactures_cpp_paths(tmp_path):
    write(tmp_path, "data/ini/objects.ini", "Behavior = HordeAIUpdate ModuleTag_1\n")
    write(tmp_path, "maps/test.map", "not a linker map")
    cat = layout.Catalogue()
    counts, hints = layout.rotwk_hints(tmp_path, cat)
    assert not cat.entries
    assert counts[".map"] == 1
    assert hints[0]["token"] == "HordeAIUpdate"
    assert hints[0]["strength"] == "data-vocabulary-only"


def scan_tree(tmp_path, monkeypatch):
    pe(tmp_path, layout.IMAGE_DIR + "/game.dat")
    write(tmp_path, SOURCE, "void f() {}\n")
    write(tmp_path, ".git/index", "untouched test index")
    ledger(tmp_path, [("?f@Box@@QAEXXZ", 0x1000, 20, SOURCE, "")])
    monkeypatch.setattr(layout, "git", lambda *a: None)
    args = SimpleNamespace(check=None, out="build/consolidation", bfme1=None, zh=None, rotwk=None, under="Code/")
    original = {p: p.read_bytes() for p in tmp_path.rglob("*") if p.is_file()}
    assert layout.run(args, tmp_path) == 0
    assert all(p.read_bytes() == raw for p, raw in original.items())
    return tmp_path / args.out


def test_snapshot_is_deterministic_and_detects_new_source_and_changed_output(tmp_path, monkeypatch):
    out = scan_tree(tmp_path, monkeypatch)
    first = (out / "inputs.json").read_bytes()
    assert layout.check_snapshot(tmp_path, out) == 0
    out2 = scan_tree(tmp_path, monkeypatch)
    assert (out2 / "inputs.json").read_bytes() == first
    write(tmp_path, "Code/GameEngine/New.cpp", "void new_body() {}\n")
    assert layout.check_snapshot(tmp_path, out) == 1
    (tmp_path / "Code/GameEngine/New.cpp").unlink()
    (out / "queue.csv").write_text("tampered", encoding="utf-8")
    assert layout.check_snapshot(tmp_path, out) == 1


def test_snapshot_cannot_report_success_after_omitting_its_output_checks(tmp_path, monkeypatch):
    out = scan_tree(tmp_path, monkeypatch)
    manifest = json.loads((out / "inputs.json").read_text())
    manifest["outputs"] = {}
    (out / "inputs.json").write_text(json.dumps(manifest))
    with pytest.raises(ValueError, match="incomplete snapshot"):
        layout.check_snapshot(tmp_path, out)


def test_missing_retail_image_is_an_error_not_an_empty_success(tmp_path):
    args = SimpleNamespace(check=None, out="build/consolidation", bfme1=None, zh=None, rotwk=None, under="Code/")
    with pytest.raises(ValueError, match="required"):
        layout.run(args, tmp_path)
    assert not (tmp_path / args.out).exists()


def test_image_must_match_its_baseline_manifest(tmp_path, monkeypatch):
    image, _ = pe(tmp_path, layout.IMAGE_DIR + "/game.dat")
    image.write_bytes(image.read_bytes() + b"patched")
    ledger(tmp_path, [])
    monkeypatch.setattr(layout, "git", lambda *a: None)
    args = SimpleNamespace(check=None, out="build/consolidation", bfme1=None, zh=None, rotwk=None, under="Code/")
    with pytest.raises(ValueError, match="declared baseline"):
        layout.run(args, tmp_path)


def test_snapshot_detects_omitted_input_coverage(tmp_path, monkeypatch):
    out = scan_tree(tmp_path, monkeypatch)
    manifest = json.loads((out / "inputs.json").read_text())
    manifest["inputs"] = []
    (out / "inputs.json").write_text(json.dumps(manifest))
    with pytest.raises(ValueError, match="input coverage"):
        layout.check_snapshot(tmp_path, out)


def test_concurrent_input_change_refuses_publication(tmp_path, monkeypatch):
    pe(tmp_path, layout.IMAGE_DIR + "/game.dat")
    write(tmp_path, SOURCE, "void f() {}\n")
    ledger(tmp_path, [("?f@Box@@QAEXXZ", 0x1000, 20, SOURCE, "")])
    monkeypatch.setattr(layout, "git", lambda *a: None)
    fingerprint = layout.fingerprint
    seen = []
    def moving(spec):
        value = fingerprint(spec)
        if spec["path"] == str(tmp_path / "reverse/functions.csv"):
            seen.append(value)
            return value if len(seen) == 1 else "concurrent-change"
        return value
    monkeypatch.setattr(layout, "fingerprint", moving)
    args = SimpleNamespace(check=None, out="build/consolidation", bfme1=None, zh=None, rotwk=None, under="Code/")
    with pytest.raises(ValueError, match="inputs changed during the scan"):
        layout.run(args, tmp_path)
    assert not (tmp_path / args.out).exists()


def test_all_173_retail_cpp_paths_and_ten_headers_are_recovered():
    image_path = layout.ROOT / layout.IMAGE_DIR / "game.dat"
    if not image_path.exists():
        pytest.skip("retail baseline is unavailable")
    paths = layout.Image(image_path).paths("retail")
    assert len({p["path"] for p in paths if p["path"].endswith(".cpp")}) == 173
    assert len({p["path"] for p in paths if p["path"].endswith(".h")}) == 10


def test_naming_picker_calls_planner_without_constructing_mutating_lane(tmp_path, monkeypatch):
    import name_lane
    monkeypatch.setattr(name_lane, "ROOT", tmp_path)
    monkeypatch.setattr(name_lane, "Lane", lambda: pytest.fail("must not instantiate naming lane"))
    monkeypatch.setattr(layout, "run", lambda args, root: 7 if root == tmp_path and args.out == "build/consolidation" else 8)
    assert name_lane.main(["consolidate"]) == 7
