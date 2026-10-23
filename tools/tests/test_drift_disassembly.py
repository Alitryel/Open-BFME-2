"""Drift classification prefers the in-process decoder and keeps a fallback."""
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import drift_classify


def test_capstone_is_preferred_without_starting_objdump(monkeypatch):
    monkeypatch.setattr(drift_classify, "_disasm_capstone", lambda data:
                        [("ret", "", "")])
    monkeypatch.setattr(drift_classify.subprocess, "run", lambda *args, **kwargs:
                        pytest.fail("Capstone should avoid objdump subprocesses"))
    assert drift_classify.disasm(b"\xc3") == [("ret", "", "")]


def test_objdump_is_used_when_capstone_is_unavailable(monkeypatch, tmp_path):
    monkeypatch.setattr(drift_classify, "SCRATCH", tmp_path)
    monkeypatch.setattr(drift_classify, "_disasm_capstone", lambda data:
                        (_ for _ in ()).throw(ImportError("capstone unavailable")))
    monkeypatch.setattr(drift_classify.subprocess, "run", lambda *args, **kwargs:
                        subprocess.CompletedProcess(args[0], 0, "   0:  c3                   ret\n", ""))
    assert drift_classify.disasm(b"\xc3") == [("ret", "", "")]


def test_no_supported_decoder_returns_empty(monkeypatch, tmp_path):
    monkeypatch.setattr(drift_classify, "SCRATCH", tmp_path)
    monkeypatch.setattr(drift_classify, "_disasm_capstone", lambda data:
                        (_ for _ in ()).throw(ImportError("capstone unavailable")))

    def missing(*args, **kwargs):
        raise FileNotFoundError("objdump")

    monkeypatch.setattr(drift_classify.subprocess, "run", missing)
    assert drift_classify.disasm(b"\xc3") == []
