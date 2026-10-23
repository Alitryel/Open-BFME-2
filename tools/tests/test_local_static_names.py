"""Compiler-local `_$E<n>` statics may repeat across TUs, never resolve across them."""
import csv
import io
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match
import add_match_batch
import build
import check_csv
import ledger_io

HEADER = check_csv.FUNCTIONS_HEADER
NOTES = "atexit cleanup of a function-local static"


def row(source="Code/a.cpp", name="_$E2", notes=NOTES, rva=None):
    item = {"name": name, "source": source, "notes": notes}
    if rva is not None:
        item["target_rva"] = rva
    return item


def ledger(*rows):
    result = io.StringIO()
    writer = csv.writer(result, lineterminator="\n")
    writer.writerow(HEADER.split(","))
    for index, item in enumerate(rows):
        writer.writerow([item["name"], "", item.get("target_rva", hex(0x1000 + index * 0x20)),
                         item.get("size", 1), item["source"], "matched", item["notes"]])
    return result.getvalue().encode()


def test_local_statics_in_different_sources_have_distinct_ledger_identities():
    problems = []
    check_csv.check_functions(ledger(row(), row("Code/b.cpp")), problems,
                              {"Code/a.cpp", "Code/b.cpp"}, b"")
    assert problems == []


@pytest.mark.parametrize("second", [
    row(), row("Code\\a.cpp"),
    row("Code/b.cpp", notes=NOTES + ";object-symbol=_$E2"),
    row("Code/b.cpp", notes="gen-alias"), row("Code/b.cpp", notes="gen-dump"),
    row("Code/gen_asm/b.cpp"), row("Code/gen_small/b.cpp"),
    row("Code/b.asm"), row("reverse/b.cpp"),
])
def test_unscoped_or_same_source_duplicates_remain_refused(second):
    problems = []
    check_csv.check_functions(ledger(row(), second), problems,
                              {"Code/a.cpp", second["source"]}, b"")
    assert any("claims two addresses" in problem for problem in problems)


@pytest.mark.parametrize("name", ["?real@@YAXXZ", "_$E2x", "$E2", "_$S2", "_$E"])
def test_other_names_remain_global(name):
    assert not ledger_io.local_static(row(name=name))
    assert ledger_io.same_function_name(row(name=name), row("Code/b.cpp", name=name))


def test_local_static_does_not_enter_the_global_resolver(tmp_path, monkeypatch):
    monkeypatch.setattr(build, "build_call_thunks", lambda: {})
    monkeypatch.setattr(build, "load_all_function_rows", lambda: [
        row(rva="0x1000"), row("Code/b.cpp", rva="0x2000"),
        row(name="?real@@YAXXZ", notes="", rva="0x3000")])
    pins = tmp_path / "symbols.csv"
    pins.write_text("name,address,notes\n_$E2,0x4000,local fixture\n")
    monkeypatch.setattr(build, "SYMBOLS", pins)
    assert build.load_symbol_map() == {"?real@@YAXXZ": [0x3000]}


@pytest.fixture
def scoped_ledger(tmp_path, monkeypatch):
    path = tmp_path / "functions.csv"
    path.write_bytes(ledger(row(name="_$E1", rva="0x1000"),
                            row("Code/b.cpp", name="_$E1", rva="0x2000"),
                            row("Code/c.cpp", name="_$E1", rva="0x5000",
                                notes="object-symbol=_$E9")))
    monkeypatch.setattr(build, "FUNCTIONS", path)
    monkeypatch.setattr(build, "build_call_thunks", lambda: {0x2000: [0x10]})
    return path


def test_call_candidates_are_the_callers_own_tu(scoped_ledger):
    symbol_map = {"_$E1": [0x1000], "?real@@YAXXZ": [0x3000]}
    assert build.call_candidates(symbol_map, "_$E1", row("Code/b.cpp")) == [0x10, 0x2000]
    assert build.call_candidates(symbol_map, "_$E1", row("Code\\b.cpp")) == [0x10, 0x2000]
    assert build.call_candidates(symbol_map, "_$E1", row("Code/a.cpp")) == [0x1000]
    # no own row (an alias row is no local identity): never another TU's body
    assert list(build.call_candidates(symbol_map, "_$E1", row("Code/c.cpp"))) == []
    assert list(build.call_candidates(symbol_map, "_$E1", row("Code/d.cpp"))) == []
    assert build.call_candidates(symbol_map, "?real@@YAXXZ", row("Code/d.cpp")) == [0x3000]


def fake_object(monkeypatch, symbols, body=b"\xe8\0\0\0\0", relocs=((1, 0x0014, "_$E1"),)):
    monkeypatch.setattr(build, "_object_layout", lambda *a: (b"", [], symbols))
    monkeypatch.setattr(build, "read_object_symbol_bytes",
                        lambda path, name, *a, **k: (body, list(relocs)))


@pytest.mark.parametrize("symbols", [
    [],                                                     # stale ordinal: another _$E<n>
    [{"name": "_$E2", "section": 1, "storage": 2}],          # external definition
    [{"name": "_$E2", "section": 1, "storage": 3}] * 2,      # not one definition
    [{"name": "_$E2", "section": 0, "storage": 3}],          # undefined reference
])
def test_byte_gate_requires_one_local_definition(tmp_path, monkeypatch, symbols):
    fake_object(monkeypatch, symbols + [{"name": "_$E5", "section": 1, "storage": 3}])
    output = tmp_path / "b.obj"
    output.write_bytes(b"")
    with pytest.raises(SystemExit):
        build.read_local_static(row("Code/b.cpp"), output, 5)


@pytest.mark.parametrize("callee, verified", [(0x2000, True), (0x10, True), (0x1000, False)])
def test_local_call_verifies_only_against_its_own_tu(tmp_path, scoped_ledger, monkeypatch,
                                                     callee, verified):
    fake_object(monkeypatch, [{"name": "_$E2", "section": 1, "storage": 3}])
    caller = 0x3000
    target = b"\xe8" + struct.pack("<i", callee - (caller + 5))
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: target)
    output = tmp_path / "b.obj"
    output.write_bytes(b"")
    patch = build.compile_function(dict(row("Code/b.cpp"), target_rva="0x3000",
                                        target_size="5"), {"_$E1": [0x1000]}, output)
    assert (patch["bytes"] == target) is verified


@pytest.fixture
def admission(tmp_path, monkeypatch):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "Code").mkdir()
    for source in ("a", "b"):
        (tmp_path / f"Code/{source}.cpp").write_text("// fixture\n")
    (tmp_path / "build.sh").write_text("fixture")
    (tmp_path / "reverse/functions.csv").write_bytes(ledger(row()))
    calls = []
    monkeypatch.setattr(add_match.subprocess, "run", lambda *args, **kwargs: (
        calls.append(args[0]), SimpleNamespace(returncode=0))[1])
    monkeypatch.setenv("BFME_CLAIMS", "off")
    return tmp_path, calls


def invoke(root, monkeypatch, source="Code/b.cpp", *extra, notes=NOTES):
    monkeypatch.setattr(sys, "argv", ["add_match.py", "_$E2", "0x2000", "1",
                                     source, "--notes", notes, "--root", str(root), *extra])
    add_match.main()


def test_single_admission_accepts_other_tu_static_and_still_runs_byte_gate(admission, monkeypatch):
    root, calls = admission
    invoke(root, monkeypatch)
    assert len(add_match.parse_ledger((root / "reverse/functions.csv").read_bytes())) == 2
    assert len(calls) == 1 and calls[0][-1] == "Code/b.cpp"


@pytest.mark.parametrize("source, notes", [
    ("Code/a.cpp", NOTES), ("Code/b.cpp", "object-symbol=_$E7"), ("Code/b.cpp", "gen-alias")])
def test_single_admission_refuses_same_tu_or_alias_static(admission, monkeypatch, source, notes):
    root, calls = admission
    with pytest.raises(SystemExit):
        invoke(root, monkeypatch, source, notes=notes)
    assert calls == []


def test_batch_admission_uses_same_tu_scope(admission, monkeypatch):
    root, calls = admission
    manifest = root / "rows.csv"
    manifest.write_text(f"_$E2,0x2000,1,Code/b.cpp,{NOTES}\n")
    monkeypatch.setattr(sys, "argv", ["add_match_batch.py", str(manifest), "--root", str(root)])
    add_match_batch.main()
    assert len(calls) == 1


def test_batch_refuses_duplicate_statics_within_one_tu(admission, monkeypatch):
    root, calls = admission
    manifest = root / "rows.csv"
    manifest.write_text(f"_$E2,0x2000,1,Code/b.cpp,{NOTES}\n"
                        f"_$E2,0x3000,1,Code/b.cpp,{NOTES}\n")
    monkeypatch.setattr(sys, "argv", ["add_match_batch.py", str(manifest), "--root", str(root)])
    with pytest.raises(SystemExit):
        add_match_batch.main()
    assert calls == []


def test_local_statics_do_not_relax_range_ownership():
    raw = ledger(dict(row(), size=8), dict(row("Code/b.cpp"), target_rva="0x1004"))
    problems = []
    check_csv.check_functions(raw, problems, {"Code/a.cpp", "Code/b.cpp"}, b"")
    assert any("overlap" in problem for problem in problems)
