"""The `unreferenced` rule's diagnostic: copies keep_rule exempts that differ
from the majority copy are listed (link_census.unreferenced_differs,
link_check's `diagnostic` lines, link_rank --stale-views) and classified
layout-like / relocation / codegen-like, never charged as blockers."""
import struct
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_census as L  # noqa: E402
import link_check as C  # noqa: E402
import link_rank as R  # noqa: E402

TEXT, COMDAT, ANY = 0x60000020, 0x1000, 2


def coff(path, bodies):
    """A COFF object with one ANY COMDAT .text section per {name: bytes}."""
    names = list(bodies)
    sym, strings = b"", bytearray(4)

    def entry(name, section, storage, aux=b""):
        nonlocal sym
        encoded = name.encode()
        if len(encoded) <= 8:
            field = encoded.ljust(8, b"\0")
        else:
            field = struct.pack("<II", 0, len(strings))
            strings.extend(encoded + b"\0")
        sym += field + struct.pack("<IhHBB", 0, section, 0, storage, len(aux) // 18) + aux

    for number, name in enumerate(names, 1):
        entry(".text", number, 3, struct.pack("<IHHIHB3x", len(bodies[name]), 0, 0, 0, 0, ANY))
        entry(name, number, 2)
    start = 20 + 40 * len(names)
    headers, data = b"", b""
    for name in names:
        headers += b".text\0\0\0" + struct.pack("<IIIIIIHHI", 0, 0, len(bodies[name]), start + len(data), 0, 0,
                                                0, 0, TEXT | COMDAT)
        data += bodies[name]
    strings[:4] = struct.pack("<I", len(strings))
    header = struct.pack("<HHIIIHH", 0x14C, len(names), 0, start + len(data), len(sym) // 18, 0, 0)
    path.write_bytes(header + headers + data + sym + bytes(strings))
    return path


GETTER = bytes.fromhex("8b8124010000c3")          # mov eax,[ecx+124h]; ret
STALE = bytes.fromhex("8b8120010000c3")           # the same read at a stale offset
LONGER = bytes.fromhex("8b81240100008bc0c3")      # other codegen
NO_TRUTH = SimpleNamespace(verdict=lambda *args: None)  # no row gives these names a retail address


def census(tmp_path, bodies_by_object):
    objs = [coff(tmp_path / name, bodies) for name, bodies in bodies_by_object.items()]
    facts = [([(n, d, s, None) for n, d, s in L.comdat_bodies(obj)], [], [], []) for obj in objs]
    return objs, facts


@pytest.mark.parametrize("body,majority,kind,differ", [
    (STALE, GETTER, "layout", 1),
    (GETTER, GETTER, "relocation", 0),
    (LONGER, GETTER, "codegen", None),
    (bytes(7), GETTER, "codegen", 5),
    (None, GETTER, "unclassified", None),
])
def test_copy_kind(body, majority, kind, differ):
    assert L.copy_kind(body, majority) == (kind, differ)


def test_majority_digest_ties_go_to_link_order():
    assert L.majority_digest(["x", "y", "y"]) == "y"
    assert L.majority_digest(["x", "y"]) == "x"


def test_unreferenced_differs_lists_minority_copies_only(tmp_path):
    objs, facts = census(tmp_path, {"a.obj": {"?get": STALE}, "b.obj": {"?get": GETTER},
                                    "c.obj": {"?get": GETTER}, "d.obj": {"?get": LONGER}})
    found = L.unreferenced_differs(objs, facts, referenced=set())
    assert set(found) == {"a.obj", "d.obj"}  # the first copy is no majority
    (stale,), (other,) = found["a.obj"], found["d.obj"]
    assert stale == {"name": "?get", "kind": "layout", "bytes_differ": 1, "size": 7, "majority_size": 7,
                     "majority_object": "b.obj"}
    assert other["kind"] == "codegen" and other["size"] == 9


def test_unreferenced_differs_skips_what_the_rule_does_not_exempt(tmp_path):
    objs, facts = census(tmp_path, {"a.obj": {"?get": STALE}, "b.obj": {"?get": GETTER},
                                    "c.obj": {"?get": GETTER}})
    assert L.unreferenced_differs(objs, facts, referenced={"?get"}) == {}   # referenced: keep_rule charges it
    assert L.unreferenced_differs(objs, facts, referenced=None) == {}       # retail-truth-1: nothing exempt
    judged = [([(n, d, s, "retail") for n, d, s, _ in found], *rest) for found, *rest in facts]
    assert L.unreferenced_differs(objs, judged, referenced=set()) == {}     # retail truth judges it


def test_the_diagnostic_charges_nothing(tmp_path):
    objs, facts = census(tmp_path, {"a.obj": {"?get": GETTER}, "b.obj": {"?get": STALE},
                                    "c.obj": {"?get": GETTER}})
    stats = {}
    assert L.comdat_losers(objs, [], stats, facts, referenced=set()) == {}
    assert stats == {"symbols_unreferenced": 1}
    assert L.unreferenced_differs(objs, facts, set())["b.obj"][0]["kind"] == "layout"


def test_unreferenced_summary_counts_copies_and_units():
    by_source = {"x.cpp": [{"kind": "layout"}, {"kind": "layout"}, {"kind": "codegen"}],
                 "y.cpp": [{"kind": "layout"}]}
    assert L.unreferenced_summary(by_source) == ({"layout": 3, "codegen": 1}, {"layout": 2, "codegen": 1})


def test_read_unreferenced_copies(tmp_path):
    assert L.read_unreferenced_copies(tmp_path / "missing.json") == {}
    path = tmp_path / "u.json"
    path.write_text('{"units": {"x.cpp": [{"name": "?get", "kind": "layout"}]}}')
    assert L.read_unreferenced_copies(path) == {"x.cpp": [{"name": "?get", "kind": "layout"}]}


def test_unreadable_objects_give_an_unclassified_entry(tmp_path):
    objs = [SimpleNamespace(name="a.obj"), SimpleNamespace(name="b.obj"), tmp_path / "gone.obj"]
    facts = [([("?get", "x", 7, None)], [], [], []), ([("?get", "y", 7, None)], [], [], []),
             ([("?get", "x", 7, None)], [], [], [])]
    entry, = L.unreferenced_differs(objs, facts, set())["b.obj"]
    assert entry["kind"] == "unclassified" and entry["size"] is None


def index_for(tmp_path, monkeypatch, bodies_by_object):
    objs, facts = census(tmp_path, bodies_by_object)
    monkeypatch.setattr(C.build, "BUILD_DIR", tmp_path)
    comdat = {}
    for position, (found, _, _, _) in enumerate(facts):
        for name, digest, _, verdict in found:
            comdat.setdefault(name, []).append((position, digest, verdict))
    return objs, {"meta": {"date": "d", "commit": "c"}, "objects": [o.name for o in objs], "strong": {},
                  "comdat": comdat, "blockers": {}, "bytes": {}, "common_schema": C.COMMON_SCHEMA, "common": {},
                  "alternates": {}, "selection": {"exceptions": {}, "owners": {}},
                  "excuses": {"runtime": set(), "imported": {}, "stubs": {}},
                  "references": {"schema": C.REFERENCES_SCHEMA, "edges": {}, "referenced": set()}}


def test_link_check_reports_a_layout_copy_and_still_links(tmp_path, monkeypatch, capsys):
    objs, ix = index_for(tmp_path, monkeypatch, {"a.obj": {"?get": GETTER}, "b.obj": {"?get": STALE},
                                                 "c.obj": {"?get": GETTER}})
    monkeypatch.setattr(C, "alternate_names", lambda obj: {})
    result = C.check_object(objs[1], ix, NO_TRUTH)
    assert result["comdat"] == []
    assert result["unreferenced_differs"] == [{"name": "?get", "kind": "layout", "bytes_differ": 1, "size": 7,
                                               "majority_size": 7, "majority_object": "a.obj"}]
    assert C.report("x.cpp", objs[1], result, ix, 10) is True
    out = capsys.readouterr().out
    assert "LINKS" in out and "diagnostic  ?get  (layout-like: 1 byte(s) differ" in out
    assert C.check_object(objs[0], ix, NO_TRUTH)["unreferenced_differs"] == []  # the majority copy


def test_link_check_skips_a_majority_holder_whose_object_moved(tmp_path, monkeypatch):
    objs, ix = index_for(tmp_path, monkeypatch, {"a.obj": {"?get": GETTER}, "b.obj": {"?get": STALE},
                                                 "c.obj": {"?get": GETTER}})
    monkeypatch.setattr(C, "alternate_names", lambda obj: {})
    coff(tmp_path / "a.obj", {"?get": LONGER})  # recompiled since the census: not the majority body any more
    assert C.check_object(objs[1], ix, NO_TRUTH)["unreferenced_differs"][0]["majority_object"] == "c.obj"


def test_link_check_a_referenced_copy_is_a_blocker_not_a_diagnostic(tmp_path, monkeypatch):
    objs, ix = index_for(tmp_path, monkeypatch, {"a.obj": {"?get": GETTER}, "b.obj": {"?get": STALE}})
    ix["references"]["referenced"] = {"?get"}
    monkeypatch.setattr(C, "alternate_names", lambda obj: {})
    result = C.check_object(objs[1], ix, NO_TRUTH)
    assert result["comdat"] == [("?get", "first", None)] and result["unreferenced_differs"] == []


def test_link_rank_stale_views_lists_layout_units_and_no_blockers(monkeypatch, capsys):
    blockers = {"x.cpp": {"unresolved": [], "duplicates": [], "losers": [], "addresses": 0,
                          "unreferenced_differs": [{"name": "?get", "kind": "layout", "bytes_differ": 1}]},
                "y.cpp": {"unresolved": ["?u"], "duplicates": [], "losers": [], "addresses": 0,
                          "unreferenced_differs": [{"name": "?big", "kind": "codegen", "bytes_differ": None,
                                                    "size": 9, "majority_size": 7}]}}
    monkeypatch.setattr(C, "census_blockers", lambda: blockers)
    monkeypatch.setattr(R.lc, "ledger", lambda: [])
    found, _ = R.blockers()
    assert found == {"x.cpp": set(), "y.cpp": {("U", "?u")}}  # V is never a blocker
    assert R.main(["--stale-views"]) == 0
    out = capsys.readouterr().out
    assert "1 units hold 1 layout-like" in out and "x.cpp" in out and "y.cpp" not in out
    assert R.main(["--file", "x.cpp"]) == 0
    assert "links" in capsys.readouterr().out
