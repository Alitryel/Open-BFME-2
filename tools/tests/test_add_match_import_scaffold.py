"""Verified generated imports yield by address; real claims and failed builds do not."""
import subprocess
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import add_match
import add_match_batch
import build
from test_pe_imports import fixture_pe, scaffold_row, scaffold_source, legacy_scaffold_source, thunk


@pytest.fixture(params=["single", "batch"])
def admission(landing, request, tmp_path, monkeypatch):
    if request.param == "single":
        return add_match.main
    manifest = tmp_path / "rows.csv"
    manifest.write_text("_D3DXMatrixMultiply@12,0x00001000,6,Code/masm_dumps/Import.asm,,0x00001000\n")
    monkeypatch.setattr(sys, "argv", ["add_match_batch.py", str(manifest), "--root", str(tmp_path)])
    return add_match_batch.main


@pytest.fixture(params=["current", "legacy"])
def landing(tmp_path, monkeypatch, request):
    data, slots = fixture_pe([("d3dx9_27.dll", "D3DXMatrixMultiply")])
    exe = tmp_path / "fixture.exe"
    exe.write_bytes(data)
    monkeypatch.setattr(build, "EXE", exe)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: thunk(slots[0]))
    row = scaffold_row(slots[0])
    source = tmp_path / row["source"]
    source.parent.mkdir(parents=True)
    source.write_text(legacy_scaffold_source() if request.param == "legacy" else scaffold_source(),
                      encoding="utf-8")
    ledger = tmp_path / "reverse/functions.csv"
    ledger.parent.mkdir()
    header = "name,export_rva,target_rva,target_size,source,status,notes\n"
    def write_row(row):
        ledger.write_bytes((header + ",".join(row.get(k, "") for k in header.strip().split(",")) + "\n").encode())
    write_row(row)
    dest = "Code/masm_dumps/Import.asm"
    asm = tmp_path / dest
    asm.parent.mkdir(parents=True)
    asm.write_text(".386\n.model flat\nEND\n", encoding="utf-8")
    (tmp_path / "build.sh").write_text("#!/bin/sh\nexit 0\n", encoding="utf-8")
    monkeypatch.setattr(sys, "argv", ["add_match.py", "_D3DXMatrixMultiply@12", "0x00001000", "6",
                                    dest, "--replace-rva", "0x00001000", "--root", str(tmp_path)])
    calls = []
    def run(command, **kwargs):
        calls.append((command, kwargs))
        return SimpleNamespace(returncode=0)
    monkeypatch.setattr(add_match.subprocess, "run", run)
    return row, source, ledger, write_row, calls


def test_verified_import_replacement_still_runs_normal_build(landing, admission):
    row, _, ledger, _, calls = landing
    admission()
    assert len(calls) == 1
    command, opts = calls[0]
    assert "Code/masm_dumps/Import.asm" == command[-1]
    assert opts["cwd"] == ledger.parent.parent
    assert "_D3DXMatrixMultiply@12" in ledger.read_text()
    assert row["name"] not in ledger.read_text()


def test_failed_normal_build_restores_import_row(landing, admission, monkeypatch):
    _, _, ledger, _, _ = landing
    before = ledger.read_bytes()
    monkeypatch.setattr(add_match.subprocess, "run", lambda *a, **k: SimpleNamespace(returncode=1))
    with pytest.raises(SystemExit) as error:
        admission()
    assert error.value.code == 1
    assert ledger.read_bytes() == before


@pytest.mark.parametrize("forge", ["name", "source-body", "export", "missing-source", "size"])
def test_unproven_import_never_reaches_build_or_changes_ledger(landing, admission, forge):
    row, source, ledger, write_row, calls = landing
    if forge == "name":
        row["name"] = "?realBody@@YAXXZ"
    elif forge == "source-body":
        source.write_text(scaffold_source().replace("D3DXMatrixMultiply(); }",
                                                   "D3DXMatrixMultiply(); side_effect(); }"), encoding="utf-8")
    elif forge == "export":
        row["notes"] = row["notes"].replace("import=D3DXMatrixMultiply", "import=D3DXMatrixTranspose")
    elif forge == "missing-source":
        source.unlink()
    else:
        row["target_size"] = "7"
    write_row(row)
    before = ledger.read_bytes()
    with pytest.raises(SystemExit) as error:
        admission()
    assert error.value.code == 1
    assert ledger.read_bytes() == before
    assert not calls


def test_alias_replacement_still_runs_normal_build(landing, admission):
    row, _, ledger, write_row, calls = landing
    row["name"] = "?dup_00001000@@YAXXZ"
    row["notes"] = "gen-alias;object-symbol=?existing@@YAXXZ"
    write_row(row)
    admission()
    assert len(calls) == 1
    assert row["name"] not in ledger.read_text()


def test_real_claim_cannot_be_replaced(landing, admission):
    row, _, ledger, write_row, calls = landing
    row["name"] = "?existing@@YAXXZ"
    row["notes"] = "recovered C++ body"
    write_row(row)
    before = ledger.read_bytes()
    with pytest.raises(SystemExit):
        admission()
    assert ledger.read_bytes() == before
    assert not calls


@pytest.fixture
def unwind_landing(landing, monkeypatch):
    row, _, ledger, write_row, calls = landing
    row.update(name="uw_00001000", source="Code/gen_small/uw_gen_009.cpp",
               target_size="11", notes="gen-funclet;object-symbol=$L3687")
    source = ledger.parent.parent / row["source"]
    source.parent.mkdir(parents=True, exist_ok=True)
    source.write_text("// cl: /MD /EHsc\n// Generated by: python3 tools/gen_uw.py land\n")
    # Complete member cleanup, the form of the reported 0x007A0E79 refusal.
    body = bytes.fromhex("8b4df083c108e900000000")
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: body[:size])
    write_row(row)
    return row, source, ledger, write_row, calls


def test_generated_unwind_replacement_runs_normal_build(unwind_landing, admission):
    row, _, ledger, _, calls = unwind_landing
    admission()
    assert len(calls) == 1
    assert row["name"] not in ledger.read_text()


def test_failed_unwind_replacement_restores_row(unwind_landing, admission, monkeypatch):
    _, _, ledger, _, _ = unwind_landing
    before = ledger.read_bytes()
    monkeypatch.setattr(add_match.subprocess, "run", lambda *a, **k: SimpleNamespace(returncode=1))
    with pytest.raises(SystemExit):
        admission()
    assert ledger.read_bytes() == before


@pytest.mark.parametrize("forge", ["real-parent", "name", "rva-name", "source", "path-traversal",
                                   "marker", "missing-source", "notes-suffix", "size", "bytes"])
def test_unproven_unwind_cannot_retire_claim(unwind_landing, admission, monkeypatch, forge):
    row, source, ledger, write_row, calls = unwind_landing
    if forge == "real-parent":
        row["notes"] = "gen-funclet;parent=??0RealOwner@@QAE@XZ"
    elif forge == "name":
        row["name"] = "$L3687"
    elif forge == "rva-name":
        row["name"] = "uw_00001001"
    elif forge == "source":
        row["source"] = "Code/RealOwner.cpp"
    elif forge == "path-traversal":
        row["source"] = "Code/gen_small/../gen_small/uw_gen_009.cpp"
    elif forge == "marker":
        source.write_text("// Hand-authored owner\n")
    elif forge == "missing-source":
        source.unlink()
    elif forge == "notes-suffix":
        row["notes"] += ";parent=??0RealOwner@@QAE@XZ"
    elif forge == "size":
        row["target_size"] = "10"
    else:
        monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: b"\x90" * size)
    write_row(row)
    before = ledger.read_bytes()
    with pytest.raises(SystemExit):
        admission()
    assert ledger.read_bytes() == before
    assert not calls
