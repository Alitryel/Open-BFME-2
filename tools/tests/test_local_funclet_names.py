"""Compiler-local EH labels may repeat across TUs, never external identities."""
import csv
import io
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
NOTES = "gen-funclet;parent=?parent@@YAXXZ"


def row(source="Code/a.cpp", name="$L1893", notes=NOTES):
    return {"name": name, "source": source, "notes": notes}


def ledger(*rows):
    result = io.StringIO()
    writer = csv.writer(result, lineterminator="\n")
    writer.writerow(HEADER.split(","))
    for index, item in enumerate(rows):
        writer.writerow([item["name"], "", hex(0x1000 + index * 0x20), 8,
                         item["source"], "matched", item["notes"]])
    return result.getvalue().encode()


def test_local_labels_in_different_sources_have_distinct_ledger_identities():
    problems = []
    check_csv.check_functions(ledger(row(), row("Code/b.cpp")), problems,
                              {"Code/a.cpp", "Code/b.cpp"}, b"")
    assert problems == []


@pytest.mark.parametrize("second", [
    row(), row("Code\\a.cpp"), row("Code/b.cpp", notes="gen-funclet"),
    row("Code/b.cpp", notes="parent=?parent@@YAXXZ"),
    row("Code/b.cpp", notes=NOTES + ";object-symbol=$L1"),
    row("Code/gen_asm/b.cpp"), row("Code/gen_small/b.cpp"),
    row("Code/b.cpp", notes=NOTES + ";parent=?other@@YAXXZ"),
])
def test_unproven_or_same_source_duplicates_remain_refused(second):
    problems = []
    check_csv.check_functions(ledger(row(), second), problems,
                              {"Code/a.cpp", second["source"]}, b"")
    assert any("claims two addresses" in problem for problem in problems)


def test_external_names_remain_global_even_with_funclet_notes():
    assert ledger_io.same_function_name(row(name="?real@@YAXXZ"),
                                       row("Code/b.cpp", name="?real@@YAXXZ"))


def test_local_label_does_not_resolve_an_external_call(tmp_path, monkeypatch):
    monkeypatch.setattr(build, "build_call_thunks", lambda: {})
    monkeypatch.setattr(build, "load_all_function_rows", lambda: [
        dict(row(), target_rva="0x1000"),
        dict(row("Code/b.cpp"), target_rva="0x2000"),
        dict(row(name="?real@@YAXXZ", notes=""), target_rva="0x3000")])
    pins = tmp_path / "symbols.csv"
    pins.write_text("name,address,notes\n$L1893,0x4000,local fixture\n")
    monkeypatch.setattr(build, "SYMBOLS", pins)
    assert build.load_symbol_map() == {"?real@@YAXXZ": [0x3000]}


def test_both_repeated_labels_require_proof_and_ledger_changes_invalidate_cache(tmp_path, monkeypatch):
    (tmp_path / "reverse").mkdir()
    path = tmp_path / "reverse/functions.csv"
    monkeypatch.setattr(build, "ROOT", tmp_path)
    path.write_bytes(ledger(row()))
    assert not build.scoped_funclet_collision(row())
    path.write_bytes(ledger(row(), row("Code/b.cpp")))
    assert build.scoped_funclet_collision(row())
    assert build.scoped_funclet_collision(row("Code/b.cpp"))
    assert not build.scoped_funclet_collision(row(name="?real@@YAXXZ"))


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


def invoke(root, monkeypatch, source="Code/b.cpp", *extra):
    monkeypatch.setattr(sys, "argv", ["add_match.py", "$L1893", "0x2000", "8",
                                     source, "--notes", NOTES, "--root", str(root), *extra])
    add_match.main()


def test_single_admission_accepts_local_label_and_still_runs_byte_gate(admission, monkeypatch):
    root, calls = admission
    invoke(root, monkeypatch)
    assert len(add_match.parse_ledger((root / "reverse/functions.csv").read_bytes())) == 2
    assert len(calls) == 1 and calls[0][-1] == "Code/b.cpp"


def test_single_admission_refuses_same_tu_label(admission, monkeypatch):
    root, calls = admission
    with pytest.raises(SystemExit):
        invoke(root, monkeypatch, "Code/a.cpp")
    assert calls == []


def test_replacement_selects_only_the_requested_tu(admission, monkeypatch):
    root, calls = admission
    invoke(root, monkeypatch)
    invoke(root, monkeypatch, "Code/b.cpp", "--replace-existing")
    rows = add_match.parse_ledger((root / "reverse/functions.csv").read_bytes())
    assert [(item["source"], item["rva"]) for item in rows] == [
        ("Code/a.cpp", 0x1000), ("Code/b.cpp", 0x2000)]
    assert len(calls) == 2


def test_admission_rolls_back_if_parent_byte_gate_refuses(admission, monkeypatch):
    root, _ = admission
    original = (root / "reverse/functions.csv").read_bytes()
    monkeypatch.setattr(add_match.subprocess, "run", lambda *a, **k: SimpleNamespace(returncode=1))
    with pytest.raises(SystemExit):
        invoke(root, monkeypatch)
    assert (root / "reverse/functions.csv").read_bytes() == original


def test_batch_admission_uses_same_tu_scope(admission, monkeypatch):
    root, calls = admission
    manifest = root / "rows.csv"
    manifest.write_text(f"$L1893,0x2000,8,Code/b.cpp,{NOTES}\n")
    monkeypatch.setattr(sys, "argv", ["add_match_batch.py", str(manifest), "--root", str(root)])
    add_match_batch.main()
    assert len(calls) == 1


def test_batch_refuses_duplicate_labels_within_one_tu(admission, monkeypatch):
    root, calls = admission
    manifest = root / "rows.csv"
    manifest.write_text(f"$L1893,0x2000,8,Code/b.cpp,{NOTES}\n"
                        f"$L1893,0x3000,8,Code/b.cpp,{NOTES}\n")
    monkeypatch.setattr(sys, "argv", ["add_match_batch.py", str(manifest), "--root", str(root)])
    with pytest.raises(SystemExit):
        add_match_batch.main()
    assert calls == []


def test_local_names_do_not_relax_range_ownership():
    raw = ledger(row(), row("Code/b.cpp")).replace(b"0x1020", b"0x1004")
    problems = []
    check_csv.check_functions(raw, problems, {"Code/a.cpp", "Code/b.cpp"}, b"")
    assert any("overlap" in problem for problem in problems)
