"""A cross-source audit reads each object once even beyond the layout cache."""
import collections
import functools
import struct
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build
from test_gate_exploits import TEXT, coff


@pytest.mark.parametrize("members", [False, True])
@pytest.mark.parametrize("conflict", [False, True])
def test_scattered_siblings_do_not_reparse_objects_or_hide_global_conflicts(
        tmp_path, monkeypatch, members, conflict):
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/dir32_consistency_whitelist.txt").write_text("")
    monkeypatch.setattr(build, "ROOT", tmp_path)
    first, second, outputs, target = [], [], {}, {}
    body = b"\xa1\0\0\0\0\xc3"
    # More live objects than the real 256-entry layout cache. Retail order can
    # scatter siblings this far apart, forcing a second parse of every object.
    for index in range(258):
        source = "vendor/fixtures.lib" if members else f"Code/unit{index:03d}.cpp"
        member = f"unit{index:03d}.obj" if members else ""
        obj = tmp_path / f"unit{index:03d}.obj"
        names = (f"_first{index}", f"_second{index}")
        obj.write_bytes(coff(
            [(".text", TEXT, body + body, [(1, 2, 6), (7, 2, 6)])],
            [(names[0], 0, 1, 0x20, 2, 0),
             (names[1], 6, 1, 0x20, 2, 0),
             ("_shared", 0, 0, 0, 2, 0)]))
        outputs[source, member] = obj
        for half, rows in enumerate((first, second)):
            rva = 0x1000 + index * 32 + half * 16
            base = 0x402004 if conflict and index == 257 and half else 0x402000
            target[rva] = b"\xa1" + struct.pack("<I", base) + b"\xc3"
            rows.append({"name": names[half], "target_rva": hex(rva),
                         "target_size": "6", "source": source,
                         "notes": f"member={member}" if members else ""})

    def require(row):
        member = build.ledger_member(row) if members else ""
        return outputs[row["source"], member]

    monkeypatch.setattr(build, "require_row_object", require)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size: target[rva][:size])
    parsed = collections.Counter()
    uncached = build._object_layout.__wrapped__

    @functools.lru_cache(maxsize=256)
    def layout(path, mtime, size):
        parsed[path] += 1
        return uncached(path, mtime, size)

    monkeypatch.setattr(build, "_object_layout", layout)
    if conflict:
        with pytest.raises(SystemExit) as exc:
            build.verify_dir32_consistency(first + second)
        assert exc.value.code == 1
    else:
        build.verify_dir32_consistency(first + second)
    # This checks real COFF parsing, not merely the order of a mock iterator.
    # A conflict in a far-away sibling must still be judged across all units.
    assert len(parsed) == 258
    assert sum(parsed.values()) == 258
