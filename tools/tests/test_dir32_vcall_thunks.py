"""DIR32 keys MSVC vcall thunks by their retail-proven virtual slot."""
import importlib
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
build = importlib.import_module("build")


def _verify(monkeypatch, tmp_path, symbol, bases, thunk_bytes=None):
    reverse = tmp_path / "reverse"
    reverse.mkdir(exist_ok=True)
    (reverse / "dir32_consistency_whitelist.txt").write_text("")
    objects = [tmp_path / "a.obj", tmp_path / "b.obj", tmp_path / "c.obj"]
    for obj in objects:
        obj.write_bytes(b"fixture object")
    rows = [{"name": f"function{i}", "target_rva": hex(0x1000 + i * 16),
             "target_size": "6", "source": f"Code/file{i}.cpp", "notes": ""}
            for i in range(len(bases))]
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "require_row_object",
                        lambda row: objects[int(row["name"][-1])])
    monkeypatch.setattr(build, "_object_layout", lambda *args: (b"", [], []))
    monkeypatch.setattr(build, "read_object_symbol_bytes",
                        lambda *args: (b"\xa1\0\0\0\0\xc3", [(1, 6, symbol)]))
    def read_target(rva, size):
        for base, code in zip(bases, thunk_bytes or ()):
            if rva == base - build.IMAGE_BASE:
                return code[:size]
        index = (rva - 0x1000) // 16
        return b"\xa1" + struct.pack("<I", bases[index]) + b"\xc3"

    monkeypatch.setattr(build, "read_target_bytes", read_target)
    build.verify_dir32_consistency(rows)


def test_vcall_thunk_symbol_can_name_distinct_virtual_slots(monkeypatch, tmp_path):
    _verify(monkeypatch, tmp_path, "??_9@$B3AE", [0x009CB260, 0x009CC208],
            [b"\x8b\x01\xff\x60\x04", b"\x8b\x01\xff\x60\x08"])


def test_same_vcall_slot_still_requires_one_base(monkeypatch, tmp_path, capsys):
    with pytest.raises(SystemExit):
        _verify(monkeypatch, tmp_path, "??_9@$B3AE", [0x009CB260, 0x009CC208],
                [b"\x8b\x01\xff\x60\x04", b"\x8b\x01\xff\x60\x04"])
    assert "DIR32 consistency: FAIL 1 NEW" in capsys.readouterr().out


def test_unknown_vcall_thunk_shape_keeps_one_base_rule(monkeypatch, tmp_path,
                                                       capsys):
    with pytest.raises(SystemExit):
        _verify(monkeypatch, tmp_path, "??_9@$B3AE", [0x009CB260, 0x009CC208],
                [b"\x90\x90\x90\x90\x90", b"\x90\x90\x90\x90\x90"])
    assert "DIR32 consistency: FAIL 1 NEW" in capsys.readouterr().out


def test_vcall_thunk_rule_does_not_exempt_other_symbols(monkeypatch, tmp_path,
                                                        capsys):
    with pytest.raises(SystemExit):
        _verify(monkeypatch, tmp_path, "?ordinary@@YAXXZ", [0x009CB260, 0x009CC208])
    assert "DIR32 consistency: FAIL 1 NEW" in capsys.readouterr().out
