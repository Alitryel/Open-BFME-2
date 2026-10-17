#!/usr/bin/env python3
"""tools/ghidra_refdb.py: deterministic snapshot load, typed verbs, evidence-only name sync."""
import sqlite3
import sys
from pathlib import Path

import pytest

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))

import ghidra_refdb as refdb  # noqa: E402

TSV = {
    "meta.tsv": "program\tgame.dat\nexecutable_sha256\tabc\nimage_base\t0x00400000\n",
    "functions.tsv": ("0x00002000\t16\t0x0000200F\t1\tFUN_00402000\tDEFAULT\t0\tunknown\tundefined f(void)\n"
                      "0x00001000\t32\t0x0000101F\t1\tFUN_00401000\tDEFAULT\t0\tunknown\tundefined g(void)\n"
                      "0x00003000\t16\t0x0000300F\t1\tKeepMe\tUSER_DEFINED\t0\t__thiscall\tvoid k(void)\n"),
    "xrefs.tsv": ("0x00001004\t0x00002000\tUNCONDITIONAL_CALL\t0\t0x00001000\n"
                  "0x00001008\t0x00005000\tDATA\t0\t0x00001000\n"
                  "0x0000100C\t0xFFFFFFFFFFC00000\tREAD\t0\t0x00001000\n"),
    "strings.tsv": "0x00005000\t6\t/string\thi\\tyou\n",
    "data.tsv": "0x00005000\t6\t/string\ts_hi\n",
    "switches.tsv": "0x00001000\t0x00001010\t1\t0x00001018\n0x00001000\t0x00001010\t0\t0x00001014\n",
    "types.tsv": "/Foo\t\tstruct\t8\t\t\t\n/Foo\t00000004\tmember\t4\tm_b\t/int\t\n",
}


@pytest.fixture
def snapshot(tmp_path):
    tsv = tmp_path / "tsv"
    tsv.mkdir()
    for name, text in TSV.items():
        (tsv / name).write_text(text, encoding="utf-8")
    meta = refdb.load(tsv, tmp_path / "a.sqlite")
    return tmp_path, tsv, meta


def test_load_is_deterministic(snapshot):
    tmp, tsv, meta = snapshot
    again = refdb.load(tsv, tmp / "b.sqlite")
    assert meta["content_sha256"] == again["content_sha256"]
    assert (tmp / "a.sqlite").read_bytes() == (tmp / "b.sqlite").read_bytes()
    assert meta["rows.functions"] == "3"


def test_verbs(snapshot):
    tmp, _, _ = snapshot
    db = refdb.connect(tmp / "a.sqlite")
    assert refdb.fn(db, "0x1010")[0]["rva"] == "0x00001000"   # containing function
    assert refdb.fn(db, "KeepMe")[0]["rva"] == "0x00003000"
    assert refdb.callers(db, "0x2000") == [{"from_func": "0x00001000", "name": "FUN_00401000"}]
    assert refdb.callees(db, "0x1000") == [{"to_rva": "0x00002000", "name": "FUN_00402000"}]
    assert refdb.strings(db, "0x1000") == [{"rva": "0x00005000", "value": "hi\tyou"}]
    assert [r["target_rva"] for r in refdb.switch(db, "0x1000")] == ["0x00001014", "0x00001018"]
    assert refdb.xrefs_from(db, "0x1000")[-1]["to_rva"] == "-0x00400000"  # below image base
    assert [r["member"] for r in refdb.type_(db, "Foo")] == ["", "m_b"]


def test_snapshot_is_opened_read_only(snapshot):
    tmp, _, _ = snapshot
    db = refdb.connect(tmp / "a.sqlite")
    with pytest.raises(Exception):
        db.execute("DELETE FROM functions")


def write(path, text):
    path.write_text(text, encoding="utf-8")


def test_sync_plan_admits_only_evidence_tiers(snapshot):
    tmp, _, _ = snapshot
    reverse = tmp / "reverse"
    reverse.mkdir()
    write(reverse / "exports.csv", "ordinal,rva,target_rva,section,kind,name\n"
                                   "1,0x00001000,,.text,code,?Exported@@YAXXZ\n")
    write(reverse / "functions.csv",
          "name,export_rva,target_rva,target_size,source,status,notes\n"
          "?Chosen@@YAXXZ,,0x00002000,16,Code/a.cpp,matched,agent named it\n"         # no evidence
          "?Proved@@YAXXZ,,0x00003000,16,Code/a.cpp,matched,ilt-verified=t1(efp=1e-4)\n")
    write(reverse / "reloc_names.csv", "name,target_rva,target_size,source,notes\n"
                                       "?Called@@YAXXZ,0x00002000,16,Code/b.cpp,reloc-derived;identity=generated\n"
                                       "?Rva00003000@@YAXXZ,0x00003000,16,Code/b.cpp,identity=real\n")
    plan = refdb.sync_plan(refdb.connect(tmp / "a.sqlite"), reverse)
    assert plan == [("0x00001000", "FUN_00401000", "?Exported@@YAXXZ", "export"),
                    ("0x00003000", "KeepMe", "?Proved@@YAXXZ", "ilt")]


def test_reloc_tier_never_overrides_a_user_name(snapshot):
    tmp, _, _ = snapshot
    reverse = tmp / "reverse"
    reverse.mkdir()
    write(reverse / "reloc_names.csv", "name,target_rva,target_size,source,notes\n"
                                       "?Called@@YAXXZ,0x00003000,16,Code/b.cpp,identity=real\n"
                                       "?Other@@YAXXZ,0x00002000,16,Code/b.cpp,identity=real\n")
    plan = refdb.sync_plan(refdb.connect(tmp / "a.sqlite"), reverse)
    assert plan == [("0x00002000", "FUN_00402000", "?Other@@YAXXZ", "reloc")]


def test_placeholders_never_sync():
    for name in ("FUN_00401000", "?rva00486F35@Rva00486F35@@QAEHXZ", "BfmeThing", "sub_4010A0"):
        assert refdb.placeholder(name), name
    assert not refdb.placeholder("?validateAudio@ThingTemplate@@IAEXXZ")


# ----------------------------------------------------------------- schema version 2 (docs/re_metadata.md A08, A09)

V2 = {
    "meta.tsv": "program\tfx\nexecutable_sha256\tabc\nimage_base\t0x10000000\n",
    "functions.tsv": ("0x00001000\t24\t0x0000102F\t2\tsplit\tDEFAULT\t0\t__cdecl\tint split(void)\n"
                      "0x00001010\t8\t0x00001017\t1\tinner\tDEFAULT\t0\t__cdecl\tint inner(void)\n"),
    "function_ranges.tsv": ("0x00001000\t0x00001000\t0x00001010\n0x00001000\t0x00001028\t0x00001030\n"
                            "0x00001010\t0x00001010\t0x00001018\n"),
}


def _load(tmp_path, files, name="db.sqlite"):
    tsv = tmp_path / ("tsv-" + name)
    tsv.mkdir()
    for n, text in files.items():
        (tsv / n).write_text(text)
    return refdb.load(tsv, tmp_path / name), tmp_path / name


def test_a08_exact_ranges_never_contain_gaps_or_end_addresses(tmp_path):
    meta, path = _load(tmp_path, V2)
    assert meta["schema_version"] == "2" and meta["rows.function_ranges"] == "3"
    db = refdb.connect(path)
    for rva in ("0x1000", "0x100F", "0x1028", "0x102F"):
        rows = refdb.fn(db, rva)
        assert [(r["rva"], r["containment"]) for r in rows] == [("0x00001000", "exact")], rva
    assert refdb.fn(db, "0x1000")[0]["body"] == [["0x00001000", "0x00001010"], ["0x00001028", "0x00001030"]]
    assert [r["rva"] for r in refdb.fn(db, "0x1014")] == ["0x00001010"]            # inside the gap: the other function
    assert refdb.fn(db, "0x1020") == []                                            # in the gap, owned by nobody
    assert refdb.fn(db, "0x1030") == []                                            # end-exclusive
    assert refdb.fn(db, "split")[0]["containment"] == "name"


def test_a09_version_1_snapshots_stay_readable_and_say_so(tmp_path):
    files = {k: v for k, v in V2.items() if k != "function_ranges.tsv"}
    meta, path = _load(tmp_path, files)
    assert meta["schema_version"] == "1" and "rows.function_ranges" not in meta
    db = refdb.connect(path)
    assert refdb.fn(db, "0x1000")[0]["containment"] == "entry"
    gap = refdb.fn(db, "0x1020")
    assert gap[0]["rva"] == "0x00001000" and gap[0]["containment"] == "bounds-candidate"
    assert refdb.callers(db, "0x1000") == []


def test_refdb_version_detection_and_consistency(tmp_path):
    bad = dict(V2, **{"function_ranges.tsv": "0x00001000\t0x00001000\t0x00001010\n"})
    with pytest.raises(SystemExit):
        _load(tmp_path, bad, "bad.sqlite")
    meta, path = _load(tmp_path, V2, "v2.sqlite")
    raw = sqlite3.connect(path)
    raw.execute("DROP TABLE function_ranges")
    raw.commit()
    raw.close()
    with pytest.raises(SystemExit, match="no function_ranges"):
        refdb.fn(refdb.connect(path), "0x1000")
    raw = sqlite3.connect(path)
    raw.execute("UPDATE meta SET value = '9' WHERE key = 'schema_version'")
    raw.commit()
    raw.close()
    with pytest.raises(SystemExit, match="newer than this tool"):
        refdb.fn(refdb.connect(path), "0x1000")
