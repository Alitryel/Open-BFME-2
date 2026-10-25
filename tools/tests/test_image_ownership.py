"""image_ownership: who owns each byte of a boot image, from small fabricated reports.

No link and no game.dat: each test writes a tiny retail PE, the compiled COFF
objects its units and datum come from, a tiny "built" PE whose bytes are
retail's at the pieces' new addresses, its link map, and the boot_image /
boot_relayout report that describes it. Every exploit a review found is
reproduced here and must be refused, each by the check that names it.
"""
import collections
import contextlib
import copy
import csv
import hashlib
import io
import json
import shutil
import struct
import subprocess
import sys
import tempfile
import threading
import time
import types
import unittest
from pathlib import Path
from unittest import mock

import numpy as np

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import boot_image  # noqa: E402
import boot_relayout  # noqa: E402
import image_ownership as io_  # noqa: E402

HEADER = 0x400
BASE = 0x10000000
SSH_KEYGEN = shutil.which("ssh-keygen")


def make_pe(sections, dirs=None):
    """A PE with just what pe_layout reads: [(name, rva, virtual size, raw bytes)] and
    data directories {index: (rva, size)}."""
    opt_size, n = 0xE0, len(sections)
    head = bytearray(HEADER)
    head[0:2] = b"MZ"
    struct.pack_into("<I", head, 0x3C, 0x40)
    head[0x40:0x44] = b"PE\0\0"
    struct.pack_into("<HH", head, 0x44, 0x14C, n)
    struct.pack_into("<H", head, 0x54, opt_size)
    opt = 0x58
    struct.pack_into("<H", head, opt, 0x10B)
    struct.pack_into("<I", head, opt + 28, BASE)
    end = max(rva + vs for _, rva, vs, _ in sections)
    struct.pack_into("<II", head, opt + 56, (end + 0xFFF) & ~0xFFF, HEADER)
    struct.pack_into("<I", head, opt + 92, 16)
    for k, (rva, size) in (dirs or {}).items():
        struct.pack_into("<II", head, opt + 96 + 8 * k, rva, size)
    body, ptr = bytearray(), HEADER
    for k, (name, rva, vs, raw) in enumerate(sections):
        at = opt + opt_size + 40 * k
        head[at:at + 8] = name.encode().ljust(8, b"\0")
        struct.pack_into("<IIII", head, at + 8, vs, rva, len(raw), ptr if raw else 0)
        body += raw
        ptr += len(raw)
    return bytes(head) + bytes(body)


# retail: .text 0x1000+0x100 (padding at 0x1040..0x1050, a call at 0x1060), .rdata
# 0x2000+0x80, .data 0x3000+0x100 of which 0x40 are in the file (the rest zero-fills)
TEXT = bytearray(b"\x90" * 0x100)
TEXT[0x40:0x50] = b"\xCC" * 0x10
TEXT[0x60:0x65] = b"\xE8\0\0\0\0"
RETAIL = make_pe([(".text", 0x1000, 0x100, bytes(TEXT)), (".rdata", 0x2000, 0x80, b"\x11" * 0x80),
                  (".data", 0x3000, 0x100, b"\x22" * 0x40)])
RETAIL_IMAGE = bytes(io_.mapped(RETAIL, io_.pe_layout(RETAIL)))

A_CPP, B_C = "Code/GameEngine/Source/Common/A.cpp", "Code/Libraries/Source/Lua/b.c"
LEDGER = "name,export_rva,target_rva,target_size,source,status,notes\n" + "\n".join([
    f"?a@@YAXXZ,,0x00001000,16,{A_CPP},matched,",
    f"?b@@YAXXZ,,0x00001010,16,{B_C},matched,vendored=lua",
    "?c@@YAXXZ,,0x00001020,32,Code/GameEngine/Source/Common/C.cpp,matched,",
]) + "\n"
ROWS_CSV = ("retail_rva,size,name,source,overlay\n"
            f"0x00001000,16,?a@@YAXXZ,{A_CPP},overlaid\n"
            f"0x00001010,16,?b@@YAXXZ,{B_C},overlaid\n"
            "0x00001020,32,?c@@YAXXZ,Code/GameEngine/Source/Common/C.cpp,refused:datum-differs:_g\n")
DATA_ITEMS = ("rva,size,section,class,detail,confidence\n"
              "0x00002000,64,.rdata,string,string,high\n0x00002040,64,.rdata,vtable,??_7X@@6B@,high\n"
              "0x00003000,64,.data,global,global,high\n")
AUTHORED = [[0x1000, 0x10, "?a@@YAXXZ"], [0x1010, 0x10, "?b@@YAXXZ"]]
GOOD = {"entry-ok": 1, "export-dir": 1, "resource-dir": 1, "text-pieces-moved": 0,
        "baserelocs-missing": 0, "baserelocs-extra": 0}
IMPORTS = b"\x55" * 0x10                                # what link.exe writes for the IAT
CODE_COMDAT, RDATA = 0x60501020, 0x40400040


def build(sections, pieces, fillers=(), extra=(), dirs=None):
    """A built image: retail's bytes at each piece's new address (int3 for a filler
    (retail start, new start)), `extra` [(rva, bytes)] written over."""
    secs = []
    for name, rva, vs in sections:
        body = bytearray(vs)
        for _, rs, ns, size in pieces:
            if rva <= ns < rva + vs:
                fill = b"\xCC" * size if (rs, ns) in fillers else RETAIL_IMAGE[rs:rs + size]
                body[ns - rva:ns - rva + size] = fill
        for at, data in extra:
            if rva <= at < rva + vs:
                body[at - rva:at - rva + len(data)] = data
        secs.append((name, rva, vs, bytes(body)))
    return make_pe(secs, dirs)


def map_text(publics, groups=()):
    lines = [" t", "", "  Start         Length     Name                   Class"]
    lines += [f" {sec:04x}:{off:08x} {n:08x}H {name:<23} DATA" for sec, off, n, name in groups]
    lines += ["", "  Address         Publics by Value              Rva+Base     Lib:Object", ""]
    lines += [f" 0001:00000000       {name:<26} {BASE + rva:08x}     {obj}" for name, rva, obj in publics]
    return "\n".join(lines) + "\n"


OVERLAY_SECTIONS = [(".text", 0x1000, 0x100), (".rdata", 0x2000, 0x90), (".data", 0x3000, 0x100)]
OVERLAY_PIECES = [[".text$p000000", 0x1000, 0x1000, 0x10], [".text$p000001", 0x1010, 0x1010, 0x10],
                  [".text$p000002", 0x1020, 0x1020, 0xE0], [".rdata", 0x2000, 0x2000, 0x80],
                  [".data", 0x3000, 0x3000, 0x100]]
OVERLAY_DIRS = {12: (0x2080, 0x10)}
OVERLAY_IMAGE = build(OVERLAY_SECTIONS, OVERLAY_PIECES, extra=[(0x2080, IMPORTS)], dirs=OVERLAY_DIRS)
OVERLAY_PUBLICS = [("_bootu_00001000", 0x1000, "overlay.obj"), ("_bootu_00001010", 0x1010, "overlay.obj"),
                   ("_bootp_00001020", 0x1020, "scaffold.obj"), ("_bootp_00002000", 0x2000, "scaffold.obj"),
                   ("_bootp_00003000", 0x3000, "scaffold.obj")]
OVERLAY_MAP = map_text(OVERLAY_PUBLICS)


def overlay_report():
    """boot_image.py link --overlay: units in place, everything else scaffold."""
    return {"link_exit": 0, "check_bad": [], "authored": copy.deepcopy(AUTHORED),
            "overlay": {"bytes": 0x20, "verified_bytes": 0x20, "units": 2},
            "check": dict(GOOD, **{"bytes-equal": 0x280, "bytes-differ": 0, "authored-bytes-equal": 0x20,
                                   "authored-bytes-differ": 0}),
            "pieces_map": copy.deepcopy(OVERLAY_PIECES)}


RELAYOUT_SECTIONS = [(".text", 0x1000, 0x111), (".rdata", 0x3000, 0x90), (".data", 0x4000, 0x100),
                     (".ordata", 0x5000, 0x40)]
RELAYOUT_PIECES = [[".text$p000000", 0x1000, 0x1000, 0x10], [".text$p000001", 0x1010, 0x1010, 0x10],
                   [".text$p000002", 0x1020, 0x1020, 0xE0], [".rdata", 0x2000, 0x3000, 0x80],
                   [".data", 0x3000, 0x4000, 0x100], [".text$r000000", 0x1000, 0x1100, 0x10],
                   [".ordata", 0x2000, 0x5000, 0x40]]
RELAYOUT_DIRS = {12: (0x3080, 0x10)}
RELAYOUT_IMAGE = build(RELAYOUT_SECTIONS, RELAYOUT_PIECES, fillers={(0x1000, 0x1000)},
                       extra=[(0x3080, IMPORTS), (0x1110, b"\xCC")], dirs=RELAYOUT_DIRS)
RELAYOUT_MAP = map_text([("_bootp_00001000", 0x1000, "scaffold.obj"), ("_bootu_00001010", 0x1010, "overlay.obj"),
                         ("_bootp_00001020", 0x1020, "scaffold.obj"), ("_bootp_00002000", 0x3000, "scaffold.obj"),
                         ("_bootp_00003000", 0x4000, "scaffold.obj"), ("_bootu_00001000", 0x1100, "moved.obj"),
                         ("_bootd_00002000", 0x5000, "moved.obj")])


def relayout_report():
    """boot_relayout --relayout --own-data: unit a moved (its range int3), b kept in
    place, the string at .rdata 0x2000 placed from a's object."""
    return {"link_exit": 0, "check_bad": [], "authored": copy.deepcopy(AUTHORED),
            "overlay": {"bytes": 0x20, "verified_bytes": 0x20, "units": 2},
            "relayout": {"mode": "relayout+own-data"},
            "own_data": {"bytes_ours": 0x40, "owners": [[0x2000, 0x40, A_CPP, "A.obj", 2, 0]]},
            "check": dict(GOOD, **{"filler-bytes": 0x10, "filler-bytes-not-int3": 0, "bytes-differ": 0,
                                   "reloc-bad": 0, "scaffold-bytes-equal": 0x260, "scaffold-bytes-differ": 0,
                                   "moved-bytes-equal": 0x10, "moved-bytes-differ": 0,
                                   "inplace-bytes-equal": 0x10, "inplace-bytes-differ": 0,
                                   "owned-data-bytes": 0x40, "owned-bytes-equal": 0x40, "owned-bytes-differ": 0}),
            "pieces_map": copy.deepcopy(RELAYOUT_PIECES)}


def sha(data):
    return hashlib.sha256(data).hexdigest()


def write_object(path, text, rdata=None, name="?a@@YAXXZ"):
    """A compiled object: a COMDAT .text$mn holding `text` under `name`, and an
    .rdata datum (a static) when `rdata` is given."""
    secs = [(".text$mn", CODE_COMDAT, bytes(text), [])]
    syms = [(name, 1, 0, 2)]
    if rdata is not None:
        secs.append((".rdata", RDATA, bytes(rdata), []))
        syms.append(("??_C@_0str@", 2, 0, 3))
    boot_image.write_coff(Path(path), secs, syms)
    return Path(path).read_bytes()


class Fixture(unittest.TestCase):
    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp(prefix="image_ownership_"))
        (self.tmp / "retail.dat").write_bytes(RETAIL)
        (self.tmp / "items.csv").write_bytes(DATA_ITEMS.encode())
        (self.tmp / "rows.csv").write_bytes(ROWS_CSV.encode())         # byte-exact: its digest is bound
        self.a_obj, self.b_obj = str(self.tmp / "A.obj"), str(self.tmp / "b.obj")
        write_object(self.a_obj, TEXT[0:0x10], b"\x11" * 0x40)
        write_object(self.b_obj, TEXT[0x10:0x20], name="?b@@YAXXZ")

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def objects(self, **over):
        entries = sorted([[self.a_obj, sha(Path(self.a_obj).read_bytes()), A_CPP],
                          [self.b_obj, sha(Path(self.b_obj).read_bytes()), B_C]])
        o = {"count": 2, "digest": boot_image.objects_digest(entries), "entries": entries,
             "units": [[0x1000, 0x10, self.a_obj, 1, 0], [0x1010, 0x10, self.b_obj, 1, 0]],
             "changed": 0, "not_current": 0, "untracked_deps": 0}
        o.update(over)
        return o

    def provenance(self, image_bytes, map_bytes, **over):
        p = {"commit": "c" * 40, "dirty": False, "inputs_moved": False, "inputs_start": "a" * 64,
             "inputs_end": "a" * 64, "built_utc": "2026-10-24T01:00:00Z",
             "retail_sha256": sha(RETAIL), "ledger_sha256": sha(LEDGER.encode()), "build_tools_sha256": "b" * 64,
             "objects": self.objects(), "spec_files_sha256": {}, "overlay_specs": ["Code/"], "seed": 0,
             "image_sha256": sha(image_bytes), "map_sha256": sha(map_bytes),
             "rows_csv_sha256": sha(ROWS_CSV.encode())}
        p.update(over)
        return p

    def measure(self, report, image, mapt, tag="t", naked=frozenset(), ledger=LEDGER, provenance=True, **kw):
        mapb = mapt.encode()
        for owner in (report.get("own_data") or {}).get("owners") or []:
            if len(owner) == 6 and owner[3] == "A.obj":
                owner[3] = self.a_obj
        if provenance:
            report.setdefault("provenance", self.provenance(image, mapb))
        (self.tmp / f"{tag}.exe").write_bytes(image)
        (self.tmp / f"{tag}.map").write_bytes(mapb)
        (self.tmp / f"{tag}.json").write_text(json.dumps(report), encoding="utf-8")
        return io_.measure(self.tmp / f"{tag}.json", retail=self.tmp / "retail.dat", ledger=ledger, naked=naked,
                           data_items_path=self.tmp / "items.csv", rows_csv=self.tmp / "rows.csv", **kw)

    def overlay(self, report=None, image=OVERLAY_IMAGE, mapt=OVERLAY_MAP, **kw):
        return self.measure(report or overlay_report(), image, mapt, **kw)

    def relayout(self, report=None, image=RELAYOUT_IMAGE, mapt=RELAYOUT_MAP, **kw):
        return self.measure(report or relayout_report(), image, mapt, **kw)

    def assert_refused(self, r, words, baseline=0x260):
        self.assertFalse(r["verified"])
        self.assertEqual(r["totals"]["ours"], 0)
        self.assertGreaterEqual(r["north_star"], baseline)
        self.assertTrue(any(words in x for x in r["refusals"]), r["refusals"])


class Overlay(Fixture):
    def test_every_byte_has_one_owner(self):
        r = self.overlay()
        self.assertTrue(r["verified"], r["refusals"])
        self.assertTrue(r["image"]["bound"] and r["map"]["bound"])
        t = r["totals"]
        self.assertEqual(t["ours_by_lane"], {"authored": 0x10, "vendored": 0x10})
        self.assertEqual(t["bridged_by_kind"], {"bytes": 0xE0 + 0x80 + 0x40, "zero-fill": 0xC0})
        self.assertEqual(t["linker_by_kind"], {"headers": HEADER, "import address table": 0x10})
        self.assertEqual(r["image_bytes"], HEADER + 0x100 + 0x90 + 0x100)
        self.assertEqual(r["north_star"], 0xE0 + 0x80 + 0x100)
        self.assertEqual(r["content_bytes"], 0x20 + r["north_star"])
        self.assertEqual(r["sections"][".text"]["ours_total"], 0x20)
        self.assertEqual(r["sections"][".data"]["bridged"], {"bytes": 0x40, "zero-fill": 0xC0})
        self.assertNotIn("entries", r["provenance"]["objects"])
        self.assertNotIn("units", r["provenance"]["objects"])

    def test_worklist_says_what_the_bridged_bytes_are(self):
        r = self.overlay()
        text = r["bridged_by_class"][".text"]
        self.assertEqual(text, {"code: refused datum-differs": 0x20, "padding (int3)": 0x10,
                                "code: no ledger row": 0xB0})
        self.assertEqual(r["bridged_by_class"][".rdata"], {"string": 0x40, "vtable": 0x40})
        self.assertEqual(r["bridged_by_class"][".data"], {"global": 0x40, "no inventory item": 0xC0})
        top = r["worklist"][0]
        self.assertEqual((top["section"], top["retail_rva"], top["bytes"]), (".data", "0x00003040", 0xC0))
        self.assertEqual(top["kinds"], {"zero-fill": 0xC0})
        refused = next(e for e in r["worklist"] if e["class"] == "code: refused datum-differs")
        self.assertIn("?c@@YAXXZ", refused["detail"])

    def test_a_differing_check_proves_nothing(self):
        for key in ("authored-bytes-differ", "bytes-differ", "authored-reloc-bad", "reloc-bad",
                    "some-new-check-bad", "biased-across-owned-data"):
            rep = overlay_report()
            rep["check"][key] = 1
            r = self.overlay(rep, tag=key)
            self.assertFalse(r["verified"], key)
            self.assertTrue(any(key in x for x in r["refusals"]), key)
            self.assertEqual(r["totals"]["ours"], 0, key)
            self.assertEqual(r["totals"]["unproven"], 0x20, key)
            self.assertEqual(r["north_star"], 0x260 + 0x20, key)

    def test_image_ok_is_required(self):
        for key in ("entry-ok", "export-dir", "resource-dir"):
            rep = overlay_report()
            rep["check"][key] = 0
            self.assert_refused(self.overlay(rep, tag=key), "boot_image.image_ok")

    def test_entry_and_directories_are_checked_in_the_image_not_the_report(self):
        retail = bytearray(RETAIL)
        struct.pack_into("<I", retail, 0x58 + 16, 0x1000)
        for index in (0, 2):
            struct.pack_into("<II", retail, 0x58 + 96 + 8 * index, 0x2000, 0x10)
        self.tmp.joinpath("retail.dat").write_bytes(retail)
        good = bytearray(OVERLAY_IMAGE)
        struct.pack_into("<I", good, 0x58 + 16, 0x1000)
        for index in (0, 2):
            struct.pack_into("<II", good, 0x58 + 96 + 8 * index, 0x2000, 0x10)
        publics = map_text(OVERLAY_PUBLICS + [("_boot_entry", 0x1000, "overlay.obj")])

        def measured(image, mapt, tag):
            rep = overlay_report()
            rep["provenance"] = self.provenance(image, mapt.encode(), retail_sha256=sha(retail))
            return self.overlay(rep, image=bytes(image), mapt=mapt, tag=tag)

        self.assertTrue(measured(good, publics, "dirs-good")["verified"])
        bad = bytearray(good)
        struct.pack_into("<I", bad, 0x58 + 16, 0x1010)
        self.assert_refused(measured(bad, publics, "entry-wrong"), "image entry")
        self.assert_refused(measured(good, OVERLAY_MAP, "entry-public-missing"), "_boot_entry")
        for index, kind in ((0, "export"), (2, "resource")):
            bad = bytearray(good)
            struct.pack_into("<I", bad, 0x58 + 96 + 8 * index, 0x2040)
            self.assert_refused(measured(bad, publics, kind + "-wrong"), f"image {kind} directory")

    def test_unexpected_entry_or_directory_is_not_credited(self):
        for offset, kind in ((0x58 + 16, "image entry"), (0x58 + 96, "image export directory"),
                             (0x58 + 96 + 16, "image resource directory")):
            bad = bytearray(OVERLAY_IMAGE)
            struct.pack_into("<I", bad, offset, 0x2000)
            self.assert_refused(self.overlay(image=bytes(bad), tag=kind), kind)

    def test_a_unit_the_check_did_not_judge_is_not_ours(self):
        rep = overlay_report()                                # the report claims 0x20, the check judged 0x10
        rep["check"]["authored-bytes-equal"] = 0x10
        self.assert_refused(self.overlay(rep), "check authored-bytes-equal")

    def test_the_overlay_summary_must_agree(self):
        rep = overlay_report()
        rep["overlay"]["verified_bytes"] = 0x10
        self.assert_refused(self.overlay(rep), "overlay summary")

    def test_a_unit_listed_without_a_piece_is_refused(self):
        rep = overlay_report()
        rep["authored"].append([0x1020, 0x20, "?c@@YAXXZ"])   # a ledger row alone is never ours
        rep["overlay"].update(bytes=0x40, verified_bytes=0x40, units=3)
        self.assert_refused(self.overlay(rep), "placed")

    def test_another_retail_is_refused(self):
        rep = overlay_report()
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode(), retail_sha256="0" * 64)
        self.assert_refused(self.overlay(rep), "retail baseline")

    def test_a_dump_is_retail_re_encoded(self):
        r = self.overlay(naked={("?a@@YAXXZ", "0x00001000")})
        self.assertEqual(r["totals"]["ours_by_lane"], {"vendored": 0x10})
        self.assertEqual(r["totals"]["bridged_by_kind"]["dump"], 0x10)
        self.assertEqual(r["bridged_by_class"][".text"]["code: dump (retail re-encoded)"], 0x10)

    def test_a_unit_with_no_ledger_row_is_not_ours(self):
        ledger = "\n".join(LEDGER.splitlines()[:1] + LEDGER.splitlines()[2:]) + "\n"
        self.assert_refused(self.overlay(ledger=ledger), "have no matched ledger row")

    def test_a_stale_rows_csv_is_not_used(self):
        rep = overlay_report()
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode(), rows_csv_sha256="9" * 64)
        r = self.overlay(rep)
        self.assertTrue(r["verified"])                       # the count does not depend on it
        self.assertNotIn("code: refused datum-differs", r["bridged_by_class"][".text"])
        self.assertTrue(any("not the report's own" in w for w in r["warnings"]))

    def test_the_image_may_live_elsewhere(self):
        """measure(report, image=): the nightly runner names the image it built."""
        rep = overlay_report()
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode())
        other = self.tmp / "elsewhere"
        other.mkdir()
        (other / "game.exe").write_bytes(OVERLAY_IMAGE)
        (other / "game.map").write_bytes(OVERLAY_MAP.encode())
        (self.tmp / "r.json").write_text(json.dumps(rep), encoding="utf-8")
        r = io_.measure(self.tmp / "r.json", image=other / "game.exe", retail=self.tmp / "retail.dat",
                        ledger=LEDGER, naked=frozenset(), data_items_path=self.tmp / "items.csv")
        self.assertTrue(r["verified"], r["refusals"])
        self.assertEqual(r["totals"]["ours"], 0x20)
        with self.assertRaises(SystemExit):                  # no image there at all
            io_.measure(self.tmp / "r.json", retail=self.tmp / "retail.dat", ledger=LEDGER, naked=frozenset())

    def test_an_unknown_mode_is_refused(self):
        rep = relayout_report()
        rep["relayout"]["mode"] = "relayout+own-data,x"
        self.assert_refused(self.relayout(rep), "is none of")


class Exploits(Fixture):
    """Every exploit the reviews found: each is refused, and NOT OURS never drops."""
    BASELINE = 0x260

    def test_unbound_image_gets_no_credit(self):
        """An old passing report beside an unrelated same-layout image (no image digest)."""
        rep = overlay_report()
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode(), image_sha256=None)
        self.assert_refused(self.overlay(rep), "the image on disk is not the one")
        rep = overlay_report()
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode(), image_sha256="e" * 64)
        self.assert_refused(self.overlay(rep, tag="other"), "the image on disk is not the one")

    def test_a_legacy_report_proves_nothing(self):
        r = self.overlay(provenance=False)
        self.assert_refused(r, "no provenance")
        self.assertEqual(r["totals"]["unproven"], 0x20)

    def test_an_unbound_map_proves_nothing(self):
        rep = overlay_report()
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, b"another map")
        self.assert_refused(self.overlay(rep), "link map on disk")

    def test_edited_geometry_and_counters(self):
        """Reclassify the scaffold piece at 0x1020 as a unit, counters to match: the
        map says it is scaffold, so the unit is never placed."""
        rep = overlay_report()
        rep["authored"].append([0x1020, 0xE0, "?c@@YAXXZ"])
        rep["overlay"].update(bytes=0x100, verified_bytes=0x100, units=3)
        rep["check"]["authored-bytes-equal"] = 0x100
        self.assert_refused(self.overlay(rep), "placed")

    def relabelled(self, obj):
        """The scaffold piece at 0x1020 relabelled a unit in the map (object `obj`), the
        report's lists and counters edited to match and rehashed: everything the
        round-2 attack controlled."""
        rep = overlay_report()
        rep["authored"].append([0x1020, 0xE0, "?c@@YAXXZ"])
        rep["overlay"].update(bytes=0x100, verified_bytes=0x100, units=3)
        rep["check"]["authored-bytes-equal"] = 0x100
        mapt = OVERLAY_MAP.replace("_bootp_00001020", "_bootu_00001020").replace(
            "10001020     scaffold.obj", f"10001020     {obj}")
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, mapt.encode())
        return self.overlay(rep, mapt=mapt, tag="relabel" + obj[:1])

    def test_a_map_public_relabelled_in_another_object(self):
        self.assert_refused(self.relabelled("C.obj"), "object boot_image did not write")

    def test_a_map_public_relabelled_without_an_object(self):
        """The same with the object name boot_image uses: no compiled object holds it."""
        self.assert_refused(self.relabelled("overlay.obj"), "no object location in provenance.objects.units")

    def test_a_unit_located_in_an_object_that_is_not_its_source(self):
        """Point the scaffold-relabelled unit at a listed object: its row's source is C.cpp."""
        rep = overlay_report()
        rep["authored"].append([0x1020, 0xE0, "?c@@YAXXZ"])
        rep["overlay"].update(bytes=0x100, verified_bytes=0x100, units=3)
        rep["check"]["authored-bytes-equal"] = 0x100
        mapt = OVERLAY_MAP.replace("_bootp_00001020", "_bootu_00001020").replace(
            "10001020     scaffold.obj", "10001020     overlay.obj")
        units = self.objects()["units"] + [[0x1020, 0xE0, self.a_obj, 1, 0]]
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, mapt.encode(), objects=self.objects(units=units))
        self.assert_refused(self.overlay(rep, mapt=mapt), "does not list for their row's source")

    def test_a_unit_whose_extent_is_not_its_objects(self):
        rep = overlay_report()
        units = [[0x1000, 0x10, self.a_obj, 1, 0], [0x1010, 0x10, self.a_obj, 1, 0]]
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode(), objects=self.objects(units=units))
        self.assert_refused(self.overlay(rep), "does not list for their row's source")
        write_object(self.a_obj, TEXT[0:0x18], b"\x11" * 0x40)    # a COMDAT of 0x18 for a 0x10 unit
        self.assert_refused(self.overlay(tag="long"), "are not their object's extent")

    def test_a_unit_outside_retail_text(self):
        """A unit claimed over retail .rdata, from a listed object's section of its size."""
        rep = overlay_report()
        rep["authored"].append([0x2000, 0x40, "?d@@YAXXZ"])
        rep["overlay"].update(bytes=0x60, verified_bytes=0x60, units=3)
        rep["pieces_map"][3:4] = [[".text$p000003", 0x2000, 0x2000, 0x40], [".rdata", 0x2040, 0x2040, 0x40]]
        mapt = map_text(OVERLAY_PUBLICS[:3] + [("_bootu_00002000", 0x2000, "overlay.obj"),
                                               ("_bootp_00002040", 0x2040, "scaffold.obj"), OVERLAY_PUBLICS[4]])
        units = self.objects()["units"] + [[0x2000, 0x40, self.a_obj, 2, 0]]
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, mapt.encode(), objects=self.objects(units=units))
        ledger = LEDGER + f"?d@@YAXXZ,,0x00002000,64,{A_CPP},matched,\n"
        self.assert_refused(self.overlay(rep, mapt=mapt, ledger=ledger), "lie outside retail .text")

    def test_a_datum_outside_one_retail_data_section(self):
        rep = relayout_report()
        rep["pieces_map"][-1] = [".ordata", 0x2060, 0x5000, 0x40]
        rep["own_data"]["owners"] = [[0x2060, 0x40, A_CPP, "A.obj", 2, 0]]
        mapt = RELAYOUT_MAP.replace("_bootd_00002000", "_bootd_00002060")
        self.assert_refused(self.relayout(rep, mapt=mapt), "do not lie in one retail data section")

    def test_an_image_that_is_not_the_objects_bytes(self):
        """A stale report rebound to an image: the image equals retail, but the object
        consumed now compiles another body, so the image is not its bytes."""
        body = bytearray(TEXT[0:0x10])
        body[3] = 0x91
        write_object(self.a_obj, body, b"\x11" * 0x40)
        self.assert_refused(self.overlay(), "are not their object's bytes in the image")

    def test_relocation_fields_are_masked(self):
        body = bytearray(TEXT[0:0x10])
        body[4:8] = b"\0\0\0\0"
        secs = [(".text$mn", CODE_COMDAT, bytes(body), [(4, 0, boot_image.DIR32)]), (".rdata", RDATA, b"\x11" * 0x40, [])]
        boot_image.write_coff(Path(self.a_obj), secs, [("?a@@YAXXZ", 1, 0, 2), ("??_C@_0str@", 2, 0, 3)])
        r = self.overlay()
        self.assertTrue(r["verified"], r["refusals"])
        body[9] = 0x91                                   # outside the field: refused
        secs[0] = (".text$mn", CODE_COMDAT, bytes(body), [(4, 0, boot_image.DIR32)])
        boot_image.write_coff(Path(self.a_obj), secs, [("?a@@YAXXZ", 1, 0, 2), ("??_C@_0str@", 2, 0, 3)])
        self.assert_refused(self.overlay(tag="outside"), "are not their object's bytes")

    def test_an_object_changed_since_the_build(self):
        rep = overlay_report()
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode())
        write_object(self.b_obj, TEXT[0x10:0x20], name="?b@@YAXXZ" + "x")
        self.assert_refused(self.overlay(rep), "not the bytes the build consumed")

    def test_a_manifest_whose_digest_is_not_its_own(self):
        rep = overlay_report()
        rep["provenance"] = self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode(),
                                            objects=self.objects(digest="d" * 64))
        self.assert_refused(self.overlay(rep), "provenance.objects.digest")

    def test_a_grown_datum(self):
        """Grow the owned datum to all of retail .rdata in the report, counters to match:
        the object's datum is 0x40 bytes."""
        rep = relayout_report()
        rep["pieces_map"][-1][3] = 0x80
        rep["own_data"].update(bytes_ours=0x80, owners=[[0x2000, 0x80, A_CPP, "A.obj", 2, 0]])
        rep["check"].update({"owned-data-bytes": 0x80, "owned-bytes-equal": 0x80})
        sections = RELAYOUT_SECTIONS[:3] + [(".ordata", 0x5000, 0x80)]
        pieces = copy.deepcopy(RELAYOUT_PIECES)
        pieces[-1][3] = 0x80
        image = build(sections, pieces, fillers={(0x1000, 0x1000)}, extra=[(0x3080, IMPORTS), (0x1110, b"\xCC")],
                      dirs=RELAYOUT_DIRS)
        self.assert_refused(self.relayout(rep, image=image), "are not their object's extent")

    def test_a_datum_from_an_unlisted_object(self):
        rep = relayout_report()
        rep["own_data"]["owners"][0][3] = str(self.tmp / "other.obj")
        self.assert_refused(self.relayout(rep), "does not list for their source")

    def test_an_old_report_without_owners_proves_no_data(self):
        rep = relayout_report()
        del rep["own_data"]["owners"]
        self.assert_refused(self.relayout(rep), "no object location in own_data.owners")

    def test_a_piece_the_map_does_not_have(self):
        rep = overlay_report()
        rep["pieces_map"][3][2] = 0x2008                     # the .rdata piece, claimed elsewhere
        self.assert_refused(self.overlay(rep), "no public of theirs")

    def test_a_public_named_twice(self):
        mapt = map_text(OVERLAY_PUBLICS + [("_bootp_00002000", 0x2000, "scaffold.obj")])
        self.assert_refused(self.overlay(mapt=mapt), "names 1 piece public(s) twice")

    def test_shrunk_piece_and_counters(self):
        """Halve the .rdata piece and lower the counters: a retail hole, refused, and its
        bytes become unexplained image bytes, never linker."""
        rep = overlay_report()
        rep["pieces_map"][3][3] = 0x40
        rep["check"]["bytes-equal"] -= 0x40
        r = self.overlay(rep)
        self.assert_refused(r, "not tiled exactly")
        self.assertEqual(r["totals"]["linker_by_kind"], {"headers": HEADER, "import address table": 0x10})
        self.assertEqual(r["unproven_gaps"], [{"section": ".rdata", "new_rva": "0x00002040", "bytes": 0x40}])

    def test_a_missing_retail_piece_is_not_linker(self):
        """Drop the .data piece (and its counter): 608 must not fall to 352."""
        rep = overlay_report()
        del rep["pieces_map"][4]
        rep["check"]["bytes-equal"] -= 0x100
        r = self.overlay(rep)
        self.assert_refused(r, "not tiled exactly")
        self.assertTrue(any("does not list" in x for x in r["refusals"]))
        self.assertEqual(r["sections"][".data"]["unproven"], 0x100)

    def test_a_dropped_zero_tail_is_not_alignment(self):
        """Cut the .data piece's zero-fill tail (counters to match): its zeros are no
        alignment: NOT OURS is 608 plus the refused units' 32 (round 2: it fell to 448)."""
        rep = overlay_report()
        rep["pieces_map"][4][3] = 0x40
        rep["check"]["bytes-equal"] -= 0xC0
        r = self.overlay(rep)
        self.assert_refused(r, "not tiled exactly")
        self.assertEqual(r["north_star"], 0x260 + 0x20)
        self.assertEqual(r["sections"][".data"]["unproven"], 0xC0)
        self.assertNotIn("alignment", r["totals"]["linker_by_kind"])

    def test_a_piece_from_a_section_boot_image_does_not_carry(self):
        rep = overlay_report()
        rep["pieces_map"].append([".rdata", 0x5000, 0x2090, 0x10])
        sections = OVERLAY_SECTIONS[:1] + [(".rdata", 0x2000, 0xA0)] + OVERLAY_SECTIONS[2:]
        image = build(sections, OVERLAY_PIECES, extra=[(0x2080, IMPORTS)], dirs=OVERLAY_DIRS)
        mapt = map_text(OVERLAY_PUBLICS + [("_bootp_00005000", 0x2090, "scaffold.obj")])
        self.assert_refused(self.overlay(rep, image=image, mapt=mapt), "a section boot_image does not carry")

    def test_bytes_that_are_not_retail(self):
        """The image's bytes at a piece are not retail's (rebound, so the digest holds)."""
        image = build(OVERLAY_SECTIONS, OVERLAY_PIECES, extra=[(0x2080, IMPORTS), (0x2010, b"\x99")],
                      dirs=OVERLAY_DIRS)
        self.assert_refused(self.overlay(image=image), "not retail's bytes")

    def test_only_a_rel32_operand_follows_its_opcode(self):
        """Retail calls at 0x1060: its four operand bytes may differ, the byte after not."""
        image = build(OVERLAY_SECTIONS, OVERLAY_PIECES, extra=[(0x2080, IMPORTS), (0x1061, b"\x01\x02\x03\x04")],
                      dirs=OVERLAY_DIRS)
        self.assertTrue(self.overlay(image=image)["verified"])
        image = build(OVERLAY_SECTIONS, OVERLAY_PIECES, extra=[(0x2080, IMPORTS), (0x1066, b"\x99")],
                      dirs=OVERLAY_DIRS)
        self.assert_refused(self.overlay(image=image, tag="after"), "not retail's bytes")
        image = build(OVERLAY_SECTIONS, OVERLAY_PIECES, extra=[(0x2080, IMPORTS), (0x1068, b"\x99")],
                      dirs=OVERLAY_DIRS)
        self.assert_refused(self.overlay(image=image, tag="far-after"), "not retail's bytes")

    def test_a_filler_must_be_int3(self):
        image = build(RELAYOUT_SECTIONS, RELAYOUT_PIECES, extra=[(0x3080, IMPORTS), (0x1110, b"\xCC")],
                      dirs=RELAYOUT_DIRS)
        self.assert_refused(self.relayout(image=image), "not retail's bytes")

    def test_unexplained_image_bytes_are_unproven(self):
        """Bytes no piece covers and no data directory names: a map `.idata$` group
        (source can make one with #pragma section) earns nothing."""
        image = build(OVERLAY_SECTIONS, OVERLAY_PIECES, extra=[(0x2080, IMPORTS)])
        mapt = map_text(OVERLAY_PUBLICS, [(2, 0x80, 0x10, ".idata$9")])
        rep = overlay_report()
        rep["provenance"] = self.provenance(image, mapt.encode())
        r = self.overlay(rep, image=image, mapt=mapt)
        self.assertTrue(r["verified"], r["refusals"])
        self.assertEqual(r["totals"]["linker_by_kind"], {"headers": HEADER})
        self.assertEqual(r["sections"][".rdata"]["unproven"], 0x10)
        self.assertEqual(r["north_star"], self.BASELINE + 0x10)


def layout(sections, dirs=None):
    return {"header_size": HEADER, "sections": [{"name": n, "rva": a, "virtual_size": v} for n, a, v in sections],
            "dirs": [(dirs or {}).get(k, (0, 0)) for k in range(16)]}


class LinkerGaps(unittest.TestCase):
    """linker_gaps: only what a rule proves is linker."""

    def gaps(self, sections, pieces, img, dirs=None):
        return io_.linker_gaps(layout(sections, dirs), np.frombuffer(bytes(img), np.uint8), pieces)

    def test_alignment_only_to_the_next_boundary(self):
        img = bytearray(0x5100)
        img[0x5000:0x5100] = b"\x11" * 0x100
        pieces = [("data", ".ordata", 0x2000, 0x5000, 0x16), ("data", ".ordata", 0x2004, 0x5024, 0x8)]
        img[0x5016:0x5024] = bytes(0xE)                    # 10 zeros to 0x5020, then the datum's pad (0x2004 & 0xF)
        linker, unproven = self.gaps([(".ordata", 0x5000, 0x2C)], pieces, img)
        self.assertEqual(unproven, [])
        self.assertEqual(linker, {"headers": HEADER, "alignment": 0xA, "piece padding": 4})
        pieces[1] = ("data", ".ordata", 0x2004, 0x5034, 0x8)    # 16 more zeros: past the first boundary
        img[0x5024:0x5040] = bytes(0x1C)
        linker, unproven = self.gaps([(".ordata", 0x5000, 0x3C)], pieces, img)
        self.assertEqual(unproven, [(".ordata", 0x5016, 0x5030)])
        self.assertEqual(linker["piece padding"], 4)

    def test_a_section_tail_is_unproven(self):
        img = bytes(0x2000)
        linker, unproven = self.gaps([(".data", 0x1000, 0x100)], [("scaffold", ".data", 0x3000, 0x1000, 0x40)], img)
        self.assertEqual(unproven, [(".data", 0x1040, 0x1100)])

    def test_base_relocations_by_their_directory_only(self):
        img = bytes(0x3000)
        linker, unproven = self.gaps([(".reloc", 0x2000, 0x100)], [], img, {5: (0x2000, 0x40)})
        self.assertEqual(linker["base relocations"], 0x40)
        self.assertEqual(unproven, [(".reloc", 0x2040, 0x2100)])

    def test_import_descriptors_do_not_credit_indirect_names_or_tables(self):
        img = bytearray(0x3000)
        struct.pack_into("<IIIII", img, 0x2000, 0x2040, 0, 0, 0x2060, 0x2080)   # one descriptor, then null
        struct.pack_into("<II", img, 0x2040, 0x2068, 0)                           # lookup table: one name
        img[0x2060:0x2066] = b"k.dll\0"
        img[0x2068:0x2070] = b"\x01\x00Foo\0\0\0"                                 # hint, "Foo", even pad
        struct.pack_into("<II", img, 0x2080, 0x2068, 0)
        linker, unproven = self.gaps([(".idata", 0x2000, 0x88)], [], img, {1: (0x2000, 0x28), 12: (0x2080, 8)})
        self.assertEqual(linker["import directory"], 0x28)
        self.assertEqual(linker["import address table"], 8)
        self.assertNotIn("import lookup tables", linker)
        self.assertNotIn("import names", linker)
        self.assertTrue(any(lo <= 0x2040 < hi for _, lo, hi in unproven))
        self.assertTrue(any(lo <= 0x2060 < hi for _, lo, hi in unproven))

    def test_a_moved_unit_pad_and_trail_are_its_own(self):
        img = bytearray(0x2000)
        img[0x1000:0x1003] = b"\xCC" * 3
        img[0x1003:0x1010] = b"\x90" * 0xD
        img[0x1010] = 0xCC
        linker, unproven = self.gaps([(".text", 0x1000, 0x11)], [("moved", ".text$r000000", 0x4003, 0x1003, 0xD)], img)
        self.assertEqual((linker["piece padding"], unproven), (4, []))
        img[0x1001] = 0x90                                  # the pad is not its fill
        _, unproven = self.gaps([(".text", 0x1000, 0x11)], [("moved", ".text$r000000", 0x4003, 0x1003, 0xD)], img)
        self.assertEqual(unproven, [(".text", 0x1000, 0x1003)])


class Verify(unittest.TestCase):
    """verify: the cross-checks that need a malformed build to trip."""
    BUILT = layout([(".text", 0x1000, 0x100)])

    def report(self):
        return {"link_exit": 0, "check_bad": [], "check": dict(GOOD, **{"bytes-equal": 0x20})}

    def test_pieces_overlapping_in_the_image(self):
        pieces = [("scaffold", ".text$p000000", 0x1000, 0x1000, 0x10), ("scaffold", ".text$p000001", 0x1010, 0x1008,
                                                                         0x10)]
        self.assertIn("pieces overlap in the built image", io_.verify(self.report(), pieces, self.BUILT))

    def test_a_piece_outside_the_sections(self):
        pieces = [("scaffold", ".text$p000000", 0x1000, 0x10F0, 0x20)]
        self.assertTrue(any("outside the built image" in x for x in io_.verify(self.report(), pieces, self.BUILT)))


class Relayout(Fixture):
    def test_moved_inplace_owned_filler_and_shadowed(self):
        r = self.relayout()
        self.assertTrue(r["verified"], r["refusals"])
        t = r["totals"]
        self.assertEqual(t["ours_by_lane"], {"authored": 0x10 + 0x40, "vendored": 0x10})
        self.assertEqual(t["filler"], 0x10)
        self.assertEqual(t["bridged_by_kind"], {"bytes": 0xE0 + 0x40 + 0x40, "shadowed": 0x40, "zero-fill": 0xC0})
        self.assertEqual(t["linker_by_kind"], {"headers": HEADER, "import address table": 0x10, "piece padding": 1})
        self.assertEqual(r["north_star"], 0x260)              # retail's copy of owned data is still retail's
        self.assertEqual(r["sections"][".rdata"]["ours"], {"authored": 0x40})
        self.assertEqual(r["sections"][".text"]["filler"], 0x10)
        self.assertEqual(r["image_bytes"], t["ours"] + t["bridged"] + t["filler"] + t["linker"])

    def test_each_class_must_be_judged_clean(self):
        for key in ("moved-bytes-differ", "owned-reloc-bad", "filler-bytes-not-int3", "scaffold-bytes-differ",
                    "inplace-reloc-bad", "branch-into-filler", "owned-writable-referenced-by-retail-code"):
            rep = relayout_report()
            rep["check"][key] = 1
            r = self.relayout(rep, tag=key)
            self.assertFalse(r["verified"], key)
            self.assertEqual(r["totals"]["unproven"], 0x60, key)

    def test_owned_data_must_match_the_check(self):
        rep = relayout_report()
        rep["check"]["owned-bytes-equal"] = 0x20
        self.assert_refused(self.relayout(rep), "check owned-bytes-equal")

    def test_a_moved_unit_needs_its_filler(self):
        rep = relayout_report()
        rep["pieces_map"][0] = [".text$p000000", 0x1000, 0x1000, 0x8]   # filler no longer the unit's range
        rep["pieces_map"].insert(1, [".text$p000009", 0x1008, 0x1008, 0x8])
        self.assert_refused(self.relayout(rep), "filler ranges are not exactly")

    def test_owned_data_are_the_owners(self):
        rep = relayout_report()
        rep["own_data"]["owners"].append([0x2040, 0x40, A_CPP, "A.obj", 2, 0])
        self.assert_refused(self.relayout(rep), "not the datums own_data.owners names")

    def test_owned_data_takes_its_units_lane(self):
        """A datum from the object of a naked (dump) unit is not credited as authored."""
        r = self.relayout(naked={("?a@@YAXXZ", "0x00001000")})
        self.assertTrue(r["verified"], r["refusals"])
        self.assertEqual(r["totals"]["ours_by_lane"], {"vendored": 0x10})
        self.assertEqual(r["totals"]["bridged_by_kind"]["dump"], 0x10 + 0x40)

    def test_a_datum_takes_the_least_credited_lane(self):
        self.assertEqual(io_.least_credited({"authored", "dump"}), "dump")
        self.assertEqual(io_.least_credited({"vendored", "authored", "generated"}), "generated")

    def test_data_owners_name_each_datums_object(self):
        live = [types.SimpleNamespace(path="o/a.obj", rows=[{"source": "Code/A.cpp"}]),
                types.SimpleNamespace(path="o/b.obj", rows=[{"source": "Code/B.cpp"}])]
        owned = {0x2040: (8, "o/b.obj", 3, 8, False), 0x2000: (0x40, "o/a.obj", 2, 0, False),
                 0x2100: (4, "o/gone.obj", 2, 0, False)}
        self.assertEqual(boot_relayout.data_owners(owned, live),
                         [[0x2000, 0x40, "Code/A.cpp", "o/a.obj", 2, 0], [0x2040, 8, "Code/B.cpp", "o/b.obj", 3, 8],
                          [0x2100, 4, None, "o/gone.obj", 2, 0]])


def clean_now(**over):
    now = {"head": "c" * 40, "status": [], "digest": "a" * 64,
           "objects": {"changed": [], "not_current": [], "untracked_deps": []},
           "spec_files_sha256": {}, "build_tools_sha256": "b" * 64, "tools_dirty": "", "now": 1792900000.0}
    now.update(over)
    return now


@unittest.skipUnless(SSH_KEYGEN, "ssh-keygen (OpenSSH) signs history rows")
class History(Fixture):
    @classmethod
    def setUpClass(cls):
        cls.keys = Path(tempfile.mkdtemp(prefix="image_ownership_keys_"))
        cls.key = cls.keys / "publisher"
        subprocess.run([SSH_KEYGEN, "-q", "-t", "ed25519", "-N", "", "-C", "test", "-f", str(cls.key)], check=True)
        cls.signers = cls.keys / "signers"
        pub = (cls.keys / "publisher.pub").read_text().strip()
        cls.signers.write_text(f'{io_.SIGNER} namespaces="{io_.SIGN_NAMESPACE}" {pub}\n')
        subprocess.run([SSH_KEYGEN, "-q", "-t", "ed25519", "-N", "", "-C", "x", "-f", str(cls.keys / "other")],
                       check=True)

    @classmethod
    def tearDownClass(cls):
        shutil.rmtree(cls.keys, ignore_errors=True)

    def receipt(self, tag="t", measured="2026-10-24T01:05:00Z", image=OVERLAY_IMAGE, mode=None, **prov):
        rep = overlay_report() if mode is None else relayout_report()
        if mode is not None:
            rep["relayout"]["mode"] = mode
        mapt = OVERLAY_MAP if mode is None else RELAYOUT_MAP
        image = image if mode is None else RELAYOUT_IMAGE
        rep["provenance"] = self.provenance(image, mapt.encode(), **prov)
        r = self.measure(rep, image, mapt, tag=tag)
        r["measured_utc"] = measured
        return r

    def record(self, receipt, path=None, committed="", key=None, **now):
        return io_.record(receipt, path or self.tmp / "hist.csv", now=clean_now(**now), committed=committed,
                          key=key or self.key, signers=self.signers)

    def signed(self, row, key=None):
        return dict(row, signature=io_.sign_row(row, key or self.key))

    def test_a_current_measurement_is_recorded_once(self):
        path = self.tmp / "hist.csv"
        row = self.record(self.receipt(), path)
        self.assertEqual(int(row["north_star"]), 0x260)
        rows = list(csv.DictReader(io.StringIO(path.read_text(encoding="utf-8"))))
        self.assertEqual(len(rows), 1)
        self.assertEqual((rows[0]["commit"], rows[0]["overlay_specs"], rows[0]["seed"]), ("c" * 40, "Code/", "0"))
        self.assertEqual(rows[0]["ledger_sha256"], sha(LEDGER.encode()))
        self.assertEqual(rows[0]["map_sha256"], sha(OVERLAY_MAP.encode()))
        self.assertTrue(io_.row_signed(rows[0], self.signers))
        self.assertEqual(io_.check_history(path, committed="", signers=self.signers), [])
        with self.assertRaises(SystemExit):                  # the same report again
            self.record(self.receipt(), path)

    def test_a_seat_without_the_key_records_nothing(self):
        with mock.patch.dict("os.environ", {io_.KEY_ENV: ""}), self.assertRaises(SystemExit) as e:
            io_.record(self.receipt(), self.tmp / "hist.csv", now=clean_now(), committed="", signers=self.signers)
        self.assertIn("publisher seat", str(e.exception))
        with self.assertRaises(SystemExit) as e:             # another key: not in the signer list
            self.record(self.receipt(tag="other"), key=self.keys / "other")
        self.assertIn("not signed by the publisher seat", str(e.exception))
        self.assertFalse((self.tmp / "hist.csv").read_text(encoding="utf-8"))

    def test_refusals(self):
        """Each case trips the check it names (so each check is needed on its own)."""
        cases = {
            "dirty at build": ({"dirty": True}, {}, "uncommitted inputs, or inputs moved"),
            "inputs moved while building": ({"inputs_moved": True, "inputs_end": "f" * 64}, {"digest": "f" * 64},
                                            "uncommitted inputs, or inputs moved"),
            "stale objects at build": ({"objects": self.objects(not_current=3)}, {},
                                       "at build time 3 object(s) were not current"),
            "not HEAD": ({}, {"head": "f" * 40}, "HEAD is ffff"),
            "uncommitted now": ({}, {"status": [" M Code/A.cpp"]}, "build input(s) are uncommitted now"),
            "untracked header now": ({}, {"status": ["?? Code/new.h"]}, "build input(s) are uncommitted now"),
            "inputs moved since": ({}, {"digest": "9" * 64}, "the build inputs' state now is not"),
            "object rewritten since": ({}, {"objects": {"changed": ["build/x.obj"], "not_current": [],
                                                        "untracked_deps": []}}, "consumed object(s) are changed"),
            "object not current now": ({}, {"objects": {"changed": [], "not_current": ["build/x.obj"],
                                                        "untracked_deps": []}}, "consumed object(s) are not current"),
            "untracked dependency": ({}, {"objects": {"changed": [], "not_current": [],
                                                      "untracked_deps": ["build/x.obj: Code/new.h"]}},
                                     "are untracked deps"),
            "spec file changed": ({"spec_files_sha256": {"build/link_status.csv": "1" * 64}},
                                  {"spec_files_sha256": {"build/link_status.csv": "2" * 64}}, "overlay spec file"),
            "build tools changed": ({}, {"build_tools_sha256": "3" * 64}, "the build tools changed"),
            "tools edited": ({}, {"tools_dirty": " M tools/progress.py"}, "has uncommitted edits"),
            "other ledger": ({"ledger_sha256": "7" * 64}, {}, "the ledger the lanes came from"),
            "unbound": ({"image_sha256": None}, {}, "provenance lacks image_sha256"),
            "no map digest": ({"map_sha256": None}, {}, "provenance lacks map_sha256"),
            "malformed tools digest": ({"build_tools_sha256": "zz"}, {"build_tools_sha256": "zz"},
                                       "provenance lacks build_tools_sha256"),
            "objects not listed": ({"objects": self.objects(count=3)}, {}, "does not list the objects"),
            "built after measured": ({"built_utc": "2026-10-24T02:00:00Z"}, {}, "dated after its measurement"),
            "malformed date": ({"built_utc": "zzzz"}, {}, "is not %Y"),
            "measured in the future": ({}, {"now": 1700000000.0}, "dated in the future"),
        }
        for name, (prov, now, words) in cases.items():
            receipt = self.receipt(tag=name.replace(" ", "_"), **prov)
            why = io_.record_refusals(receipt, now=clean_now(**now))
            self.assertTrue(any(words in x for x in why), (name, why))
            with self.assertRaises(SystemExit, msg=name):
                self.record(receipt, self.tmp / f"{name}.csv", **now)
            self.assertFalse((self.tmp / f"{name}.csv").exists(), name)

    def test_a_forged_receipt_is_refused(self):
        """record re-checks what a receipt says even if a caller edits it."""
        for name, edit, words in (
                ("unbound", lambda r: r["image"].update(bound=False), "not bound to the report"),
                ("unlaned", lambda r: r["totals"]["ours_by_lane"].update(unknown=4), "have no ledger lane"),
                ("mode", lambda r: r["report"].update(mode="relayout+own-data,x"), "is none of")):
            receipt = self.receipt(tag=name)
            edit(receipt)
            self.assertTrue(any(words in x for x in io_.record_refusals(receipt, now=clean_now())), name)

    def test_artifacts_changed_after_measuring_are_refused(self):
        receipt = self.receipt()
        Path(receipt["report"]["path"]).write_text("{}", encoding="utf-8")
        self.assertIn("the report on disk is not the one measured; measure it again",
                      io_.record_refusals(receipt, now=clean_now()))
        receipt = self.receipt(tag="img")
        Path(receipt["image"]["path"]).write_bytes(OVERLAY_IMAGE + b"\0")
        self.assertIn("the image on disk is not the one measured; measure it again",
                      io_.record_refusals(receipt, now=clean_now()))
        receipt = self.receipt(tag="map")
        Path(receipt["map"]["path"]).write_bytes(b"\n")
        self.assertIn("the map on disk is not the one measured; measure it again",
                      io_.record_refusals(receipt, now=clean_now()))

    def test_a_report_changed_while_recording_is_refused(self):
        """The re-checks run again under the lock, on the bytes the row is made from."""
        receipt = self.receipt()
        real = io_.record_refusals

        def then_edit(*a, **k):
            out = real(*a, **k)
            Path(receipt["report"]["path"]).write_text("{}", encoding="utf-8")
            return out
        with mock.patch.object(io_, "record_refusals", then_edit), self.assertRaises(SystemExit) as e:
            self.record(receipt)
        self.assertIn("changed while it was being recorded", str(e.exception))
        self.assertFalse((self.tmp / "hist.csv").read_text(encoding="utf-8"))
        receipt = self.receipt(tag="img")
        calls = []

        def then_swap(*a, **k):                              # the image swapped between the checks
            out = real(*a, **k)
            calls.append(out)
            if len(calls) == 1:
                Path(receipt["image"]["path"]).write_bytes(OVERLAY_IMAGE + b"\0")
            return out
        with mock.patch.object(io_, "record_refusals", then_swap), self.assertRaises(SystemExit) as e:
            self.record(receipt, self.tmp / "hist2.csv")
        self.assertIn("the image on disk is not the one measured", str(e.exception))
        self.assertEqual(len(calls), 2)

    def test_unverified_or_unlaned_is_not_recorded(self):
        rep = overlay_report()
        rep["check"]["authored-bytes-differ"] = 2
        with self.assertRaises(SystemExit):
            self.record(self.overlay(rep))
        ledger = LEDGER.splitlines()[0] + "\n"
        with self.assertRaises(SystemExit):
            self.record(self.overlay(ledger=ledger, tag="nolane"))

    def test_committed_rows_are_append_only(self):
        path = self.tmp / "hist.csv"
        self.record(self.receipt(), path)
        committed = path.read_text(encoding="utf-8")
        path.write_text(committed.replace(f",{0x260},", f",{0x100},", 1), encoding="utf-8")
        self.assertIn("the committed rows were changed (the history is append-only)",
                      io_.check_history(path, committed=committed, signers=self.signers))
        path.write_bytes(committed.replace("\n", "\r\n").encode())          # an autocrlf checkout
        self.assertEqual(io_.check_history(path, committed=committed, signers=self.signers), [])
        path.write_text(committed, encoding="utf-8")
        image = build(OVERLAY_SECTIONS, OVERLAY_PIECES, extra=[(0x2080, IMPORTS), (0x208F, b"\0")], dirs=OVERLAY_DIRS)
        later = self.receipt(tag="later", measured="2026-10-24T02:05:00Z", image=image,
                             built_utc="2026-10-24T02:00:00Z")      # a later build of the same commit appends
        self.record(later, path, committed=committed)
        self.assertEqual(io_.check_history(path, committed=committed, signers=self.signers), [])
        path.unlink()
        with self.assertRaises(SystemExit) as e:             # tracked at HEAD but gone: restore, never recreate
            again = self.receipt(tag="again", measured="2026-10-24T03:05:00Z", built_utc="2026-10-24T03:00:00Z",
                                 image=image + b"\0")
            self.record(again, path, committed=committed)
        self.assertIn("missing but tracked at HEAD", str(e.exception))

    def test_a_history_without_its_last_newline_is_not_appended_to(self):
        path = self.tmp / "hist.csv"
        self.record(self.receipt(), path)
        path.write_text(path.read_text(encoding="utf-8").rstrip("\n"), encoding="utf-8")
        with self.assertRaises(SystemExit) as e:
            self.record(self.receipt(tag="next", measured="2026-10-24T02:05:00Z",
                                     image=OVERLAY_IMAGE + b"\0", built_utc="2026-10-24T02:00:00Z"), path)
        self.assertIn("does not end in a newline", str(e.exception))

    def test_an_image_is_recorded_once_under_any_mode(self):
        """Round 2 recorded one image as relayout+own-data and relayout+own-data,x."""
        path = self.tmp / "hist.csv"
        self.record(self.receipt(tag="m0", mode="relayout+own-data"), path)
        with self.assertRaises(SystemExit) as e:
            self.record(self.receipt(tag="m1", mode="in-place+own-data", measured="2026-10-24T01:06:00Z"), path)
        self.assertIn("this image is recorded twice", str(e.exception))

    def test_added_rows_must_be_signed(self):
        """Hand-edited history: an added row without the publisher's signature, or with
        a signature over other figures or by another key, is refused."""
        path = self.tmp / "hist.csv"
        row = self.record(self.receipt(), path)
        committed = path.read_text(encoding="utf-8")
        later = dict(row, report_sha256="1" * 64, image_sha256="2" * 64, date="2026-10-24T02:00:00Z",
                     measured="2026-10-24T02:05:00Z")
        for name, bad in (("unsigned", dict(later, signature="")),
                          ("edited after signing", dict(self.signed(later), ours=str(int(later["ours"]) - 0x10),
                                                        ours_authored=str(int(later["ours_authored"]) - 0x10),
                                                        content_bytes=str(int(later["content_bytes"]) - 0x10),
                                                        linker=str(int(later["linker"]) + 0x10))),
                          ("another key", self.signed(later, self.keys / "other"))):
            handle = io.StringIO()
            csv.DictWriter(handle, io_.HISTORY_FIELDS, lineterminator="\n").writerow(bad)
            path.write_text(committed + handle.getvalue(), encoding="utf-8")
            problems = io_.check_history(path, committed=committed, signers=self.signers)
            self.assertEqual(problems, [f"line 3: not signed by the publisher seat (a key in {self.signers})"], name)
            self.assertTrue(io_.check_history(path, committed=committed, signers=None), name)
        handle = io.StringIO()
        csv.DictWriter(handle, io_.HISTORY_FIELDS, lineterminator="\n").writerow(self.signed(later))
        path.write_text(committed + handle.getvalue(), encoding="utf-8")
        self.assertEqual(io_.check_history(path, committed=committed, signers=self.signers), [])
        self.assertEqual(io_.check_history(path, committed=committed, signers=None),
                         ["line 3: not signed by the publisher seat (a registered key (there is none))"])

    def test_check_staged_uses_external_pin(self):
        """No in-repo key registration can authorize a staged row."""
        path = self.tmp / "hist.csv"
        row = self.record(self.receipt(), path)
        staged = path.read_text(encoding="utf-8")
        blobs = {":": staged, "HEAD": None}

        def fake_committed(p, ref="HEAD"):
            return blobs[ref]

        with mock.patch.object(io_, "committed_history", fake_committed), \
                mock.patch.dict("os.environ", {io_.SIGNERS_ENV: ""}):
            self.assertEqual(io_.check_staged(path), ["line 2: not signed by the publisher seat "
                                                      "(a registered key (there is none))"])
            with mock.patch.dict("os.environ", {io_.SIGNERS_ENV: str(self.signers)}):
                self.assertEqual(io_.check_staged(path), [])
            blobs["signers"] = self.signers.read_text()
            self.assertTrue(io_.check_staged(path))
            blobs.update({":": None, "HEAD": staged})
            self.assertEqual(io_.check_staged(path), ["the committed history is deleted"])
            blobs.update({":": staged.replace(row["north_star"], "1", 1), "HEAD": staged})
            self.assertIn("the committed rows were changed (the history is append-only)", io_.check_staged(path))

    def test_pin_rejects_wildcards_multiple_keys_and_repo_paths(self):
        row = self.record(self.receipt(), self.tmp / "row.csv")
        agent = self.keys / "other.pub"
        forged = self.signed(row, self.keys / "other")
        for name, contents in (
                ("star", "* " + agent.read_text()),
                ("multi", "publisher,agent " + agent.read_text()),
                ("two-keys", self.signers.read_text() +
                 f'{io_.SIGNER} namespaces="{io_.SIGN_NAMESPACE}" ' + agent.read_text())):
            pin = self.tmp / name
            pin.write_text(contents)
            self.assertFalse(io_.row_signed(forged, pin), name)
        with mock.patch.object(io_, "ROOT", self.tmp), \
                mock.patch.dict("os.environ", {io_.SIGNERS_ENV: str(self.tmp / "two-keys")}):
            self.assertIsNone(io_.allowed_signers())

    def test_signing_without_ssh_keygen_is_a_clean_refusal(self):
        with mock.patch.object(io_.subprocess, "run", side_effect=FileNotFoundError("ssh-keygen")):
            with self.assertRaisesRegex(SystemExit, "ssh-keygen could not sign"):
                io_.sign_row({}, self.key)

    def test_range_checks_intermediate_commits_and_missing_pin(self):
        row = self.record(self.receipt(), self.tmp / "row.csv")
        output = io.StringIO()
        writer = csv.DictWriter(output, io_.HISTORY_FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerow(row)
        good = output.getvalue()
        forged = self.signed(dict(row, report_sha256="a" * 64), self.keys / "other")
        output = io.StringIO()
        writer = csv.DictWriter(output, io_.HISTORY_FIELDS, lineterminator="\n")
        writer.writeheader()
        writer.writerow(forged)
        bad = output.getvalue()
        def fake_git(*args):
            if args[0] == "rev-list":
                return types.SimpleNamespace(returncode=0, stdout="bad\ngood\n")
            return types.SimpleNamespace(returncode=0, stdout={"base": good.splitlines()[0] + "\n",
                                                                "bad": bad, "good": good}[args[1].split(":")[0]])
        with mock.patch.object(io_, "git", fake_git), \
                mock.patch.dict("os.environ", {io_.SIGNERS_ENV: str(self.signers)}):
            self.assertTrue(any("bad:" in x and "not signed" in x for x in io_.check_range("base", "good")))
        with mock.patch.object(io_, "git", fake_git), mock.patch.dict("os.environ", {io_.SIGNERS_ENV: ""}):
            self.assertTrue(io_.check_range("base", "good"))

    def test_rows_keep_their_sums_and_their_order(self):
        receipt = self.receipt()
        prov = json.loads(Path(receipt["report"]["path"]).read_bytes())["provenance"]
        row = io_.history_row(receipt, prov)
        self.assertEqual(io_.check_rows([row]), [])
        for field in ("ours_authored", "not_ours_text", "linker"):
            bad = dict(row, **{field: str(int(row[field]) + 1)})
            self.assertTrue(io_.check_rows([bad]), field)
        for field, value, words in (("date", "zzzz", "UTC"), ("measured", "not-a-date", "UTC"),
                                    ("date", "2026-10-24 01:00", "UTC"), ("seed", "x", "non-negative"),
                                    ("ours", "-5", "non-negative"), ("rules", "ownership-0", "unknown rules"),
                                    ("mode", "relayout+own-data,x", "unknown mode")):
            self.assertTrue(any(words in x for x in io_.check_rows([dict(row, **{field: value})])), (field, value))
        self.assertTrue(io_.check_rows([dict(row, date="2026-10-24T09:00:00Z")]))     # built after measured
        early = dict(row, date="2026-10-23T00:00:00Z", measured="2026-10-23T00:05:00Z", report_sha256="1" * 64,
                     image_sha256="2" * 64)
        self.assertTrue(any("before the row above" in x for x in io_.check_rows([row, early])))
        again = dict(row, report_sha256="1" * 64, mode="in-place")          # the same image, another mode
        self.assertTrue(any("this image is recorded twice" in x for x in io_.check_rows([row, again])))
        same = dict(row, image_sha256="2" * 64)                           # the same report, another image
        self.assertTrue(any("the same report is recorded twice" in x for x in io_.check_rows([row, same])))

    def test_concurrent_records_race_for_one_slot(self):
        """Validation must be serialized as well as the append."""
        path = self.tmp / "hist.csv"
        row = self.signed(io_.history_row(self.receipt(), self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode())))
        landed, errors = [], []
        real = io_.check_rows
        checking = 0
        checking_lock = threading.Lock()
        simultaneous = []

        def slow(rows):
            nonlocal checking
            with checking_lock:
                checking += 1
                if checking > 1:
                    simultaneous.append(checking)
            try:
                time.sleep(0.05)
                return real(rows)
            finally:
                with checking_lock:
                    checking -= 1

        def go():
            try:
                landed.append(io_.append_history(dict(row), path, committed="", signers=self.signers))
            except SystemExit as e:
                errors.append(str(e))
        with mock.patch.object(io_, "check_rows", slow):
            threads = [threading.Thread(target=go) for _ in range(8)]
            for t in threads:
                t.start()
            for t in threads:
                t.join()
        self.assertEqual(len(landed), 1, errors)
        self.assertEqual(len(errors), 7)
        self.assertFalse(simultaneous, "the history lock must cover validation")
        self.assertTrue(all("recorded twice" in e for e in errors), errors)
        _, got = io_.read_history(path)
        self.assertEqual(len(got), 1)


class Provenance(unittest.TestCase):
    """boot_image's provenance: what measure and record later re-check."""

    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp(prefix="provenance_"))

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def unit(self, name, data, source, rva=0x1000, sec=1, off=0):
        path = self.tmp / name
        path.write_bytes(data)
        (self.tmp / (name + ".deps.json")).write_text(json.dumps({"deps": {"Code/tracked.h": "x",
                                                                           "Code/untracked.h": "y"}}))
        return types.SimpleNamespace(path=str(path), obj=(None, None, data), rows=[{"source": source}], rva=rva,
                                     size=len(data), sec=sec, off=off)

    @contextlib.contextmanager
    def fakes(self, current=True, states=None):
        states = list(states or [{"head": "c" * 40, "status": [], "digest": "a" * 64}])
        with mock.patch.object(boot_image.build, "compile_is_current", return_value=current) as cic, \
                mock.patch.object(boot_image.build, "_deps_sidecar", lambda p: Path(str(p) + ".deps.json")), \
                mock.patch.object(boot_image, "_git", lambda *a: "Code/tracked.h\n"), \
                mock.patch.object(boot_image, "input_state", lambda: states.pop(0) if len(states) > 1
                                  else states[0]):
            yield cic

    def test_objects_state_names_the_bytes_consumed(self):
        units = [self.unit("a.obj", b"A" * 8, "Code/A.cpp"), self.unit("a.obj", b"A" * 8, "Code/A.cpp", rva=0x1008),
                 self.unit("lib.obj", b"L", "vendor/x.lib", rva=0x2000, sec=3, off=4)]
        with self.fakes(current=False) as cic:
            st = boot_image.objects_state(units)
        self.assertEqual(st["count"], 2)
        self.assertEqual([e[1] for e in st["entries"]], [sha(b"A" * 8), sha(b"L")])
        self.assertEqual(st["digest"], boot_image.objects_digest(st["entries"]))
        self.assertEqual([u[:2] + u[3:] for u in st["units"]], [[0x1000, 8, 1, 0], [0x1008, 8, 1, 0], [0x2000, 1, 3, 4]])
        self.assertEqual(st["not_current"], 1)               # the .lib member has no source to be current for
        self.assertEqual(st["untracked_deps"], 1)
        self.assertTrue(all(c.kwargs.get("strict") for c in cic.call_args_list))
        units[0].path = units[1].path = str(self.tmp / "a.obj")
        (self.tmp / "a.obj").write_bytes(b"changed")         # the object on disk is not what was linked
        with self.fakes():
            self.assertEqual(boot_image.objects_now(st["entries"])["changed"], [st["entries"][0][0]])

    def test_provenance_binds_image_map_inputs_and_specs(self):
        exe = self.tmp / "t.exe"
        exe.write_bytes(b"MZ image")
        exe.with_suffix(".map").write_bytes(b"map")
        status = self.tmp / "link_status.csv"
        status.write_text("status")
        rows = self.tmp / "rows.csv"
        rows.write_text("rows")
        overlay_csv = self.tmp / "t.overlay.csv"
        overlay_csv.write_text("verdicts")
        r = types.SimpleNamespace(data=b"retail")
        start = {"head": "c" * 40, "status": [], "digest": "0" * 64}
        with self.fakes(states=[{"head": "c" * 40, "status": [], "digest": "a" * 64}]):
            p = boot_image.provenance(r, [self.unit("a.obj", b"A", "Code/A.cpp")], exe, overlay_csv, start,
                                      ["closed", f"rows:{rows}"], status, 7)
        self.assertEqual((p["image_sha256"], p["map_sha256"], p["retail_sha256"]),
                         (sha(b"MZ image"), sha(b"map"), sha(b"retail")))
        self.assertEqual(p["rows_csv_sha256"], sha(b"verdicts"))
        self.assertTrue(p["dirty"] and p["inputs_moved"])    # the inputs moved while it built
        self.assertFalse(p["specs_moved"])
        self.assertEqual((p["inputs_start"], p["inputs_end"]), ("0" * 64, "a" * 64))
        self.assertIn("reverse/ghidra_functions.csv", p["inputs_sha256"])
        self.assertEqual(sorted(p["spec_files_sha256"].values()), sorted([sha(b"status"), sha(b"rows")]))
        self.assertEqual((p["overlay_specs"], p["seed"]), (["closed", f"rows:{rows}"], 7))
        io_.utc_seconds(p["built_utc"])
        self.assertEqual(p["objects"]["count"], 1)

    def test_the_ledger_digest_is_of_lf_line_ends(self):
        root = self.tmp / "root"
        (root / "reverse").mkdir(parents=True)
        (root / "reverse/functions.csv").write_bytes(b"a,b\r\n1,2\r\n")
        exe = self.tmp / "t.exe"
        exe.write_bytes(b"MZ")
        with self.fakes(), mock.patch.object(boot_image, "ROOT", root), mock.patch.object(boot_image, "BUILD_TOOLS", ()):
            p = boot_image.provenance(types.SimpleNamespace(data=b"r"), [], exe)
        self.assertEqual(p["ledger_sha256"], sha(b"a,b\n1,2\n"))

    def test_input_state_covers_the_build_tools(self):
        calls = []

        def fake_git(*a):
            calls.append(a)
            return ""
        with mock.patch.object(boot_image, "_git", fake_git):
            boot_image.input_state()
        status = next(c for c in calls if c[0] == "status")
        self.assertIn("tools/boot_relayout.py", status)
        self.assertIn("reverse/functions.csv", status)

    def test_spec_files_are_selected_from_snapshots(self):
        """The overlay reads a copy taken before selection; an edit to the original after
        it makes the build dirty (specs_moved), and the digests are of the copy."""
        status, rows = self.tmp / "link_status.csv", self.tmp / "rows.txt"
        status.write_text("first")
        rows.write_text("0x1000\n")
        snap = self.tmp / "snap"
        snap.mkdir()
        specs, status2, digests = boot_image.snapshot_specs(["closed", f"rows:{rows}", "Code/"], status, snap)
        self.assertTrue(Path(status2).is_relative_to(snap) and Path(specs[1][5:]).is_relative_to(snap))
        self.assertEqual(specs[2], "Code/")
        self.assertEqual(Path(status2).read_text(), "first")
        status.write_text("second")                          # a concurrent link_cycle rewrites it
        self.assertEqual(Path(status2).read_text(), "first")
        exe = self.tmp / "t.exe"
        exe.write_bytes(b"MZ")
        with self.fakes():
            p = boot_image.provenance(types.SimpleNamespace(data=b"r"), [], exe, None, None,
                                      ["closed", f"rows:{rows}"], status, spec_digests=digests)
        self.assertTrue(p["specs_moved"] and p["dirty"])
        self.assertIn(sha(b"first"), p["spec_files_sha256"].values())

    def test_artifacts_are_checked_from_snapshots(self):
        exe = self.tmp / "out" / "t.exe"
        exe.parent.mkdir()
        exe.write_bytes(b"MZ checked")
        exe.with_suffix(".map").write_bytes(b"map checked")
        copy_exe, copy_map = boot_image.snapshot_artifacts(exe, self.tmp / "snap")
        exe.write_bytes(b"MZ swapped")                       # another build rewrites out/ after the copy
        self.assertEqual((copy_exe.read_bytes(), copy_map.read_bytes()), (b"MZ checked", b"map checked"))
        self.assertEqual(copy_map, copy_exe.with_suffix(".map"))


class BuildProvenance(unittest.TestCase):
    """boot_image.build_image and boot_relayout.build_image, link and check faked: each
    writes provenance, and binds the bytes it checked even when out/ is rewritten
    while the check runs."""

    def setUp(self):
        self.tmp = Path(tempfile.mkdtemp(prefix="build_provenance_"))
        self.out = self.tmp / "out"
        self.out.mkdir()
        self.checked = []

    def tearDown(self):
        shutil.rmtree(self.tmp, ignore_errors=True)

    def link(self, objs, base, out, tag, entry="boot_entry"):
        (out / f"{tag}.exe").write_bytes(b"MZ linked")
        (out / f"{tag}.map").write_bytes(b"map linked")
        return 0, "", 0.1

    def publics(self, mapfile, base):
        (self.out / "t.exe").write_bytes(b"MZ swapped before the check")   # a concurrent build of the same out/
        return {}

    def check(self, exe):
        self.checked.append(Path(exe).read_bytes())
        (self.out / "t.exe").write_bytes(b"MZ swapped mid-check")
        return dict(GOOD, **{"bytes-equal": 0})

    @contextlib.contextmanager
    def common(self, on_retail=lambda: None):
        r = types.SimpleNamespace(data=b"retail", entry=0x1000, imports=lambda: {})
        with mock.patch.object(boot_image, "Retail", lambda: (on_retail(), r)[1]), \
                mock.patch.object(boot_image, "input_state", lambda: {"head": "c" * 40, "status": [],
                                                                      "digest": "a" * 64}), \
                mock.patch.object(boot_image, "_git", lambda *a: ""), \
                mock.patch.object(boot_image, "write_scaffold", lambda *a, **k: ([], [])), \
                mock.patch.object(boot_image, "write_import_lib", lambda *a, **k: None), \
                mock.patch.object(boot_image, "descriptor_libs", lambda *a, **k: []), \
                mock.patch.object(boot_image, "link_image", self.link), \
                mock.patch.object(boot_image, "read_publics", self.publics):
            yield

    def assert_bound_to_checked(self, rep):
        p = rep["provenance"]
        self.assertEqual(self.checked, [b"MZ linked"])
        self.assertEqual((p["image_sha256"], p["map_sha256"]), (sha(b"MZ linked"), sha(b"map linked")))
        self.assertNotEqual(p["image_sha256"], sha((self.out / "t.exe").read_bytes()))
        self.assertIn("provenance", json.loads((self.out / "t.json").read_text(encoding="utf-8")))

    def test_boot_image_build(self):
        status = self.tmp / "link_status.csv"
        status.write_text("as selected")
        seen = []

        def layout(r, specs, status_read, rows):
            seen.append((list(specs), Path(status_read).read_text()))
            return [], {}, {}, [], [], {}, None
        # link_cycle rewrites the status after the build's start, before it selects
        with self.common(lambda: status.write_text("rewritten by link_cycle")), \
                mock.patch.object(boot_image, "layout", layout), \
                mock.patch.object(boot_image, "check_image", lambda r, pieces, exe, base, publics:
                                  (self.check(exe), [])):
            rep = boot_image.build_image(out=self.out, tag="t", overlay=["closed"], status=status)
        self.assert_bound_to_checked(rep)
        self.assertEqual(seen, [(["closed"], "as selected")])
        p = rep["provenance"]
        self.assertEqual(list(p["spec_files_sha256"].values()), [sha(b"as selected")])
        self.assertTrue(p["specs_moved"] and p["dirty"])

    def test_boot_relayout_build(self):
        ctx = {"datum_refs": {}, "iat": {}, "ident": {}, "authored": {}, "need": {}}
        none = collections.Counter()
        status = self.tmp / "link_status.csv"
        status.write_text("as selected")
        seen = []

        def overlay_rows(specs, status_read):
            seen.append((list(specs), Path(status_read).read_text()))
            return []
        with self.common(lambda: status.write_text("rewritten by link_cycle")), \
                mock.patch.object(boot_image, "overlay_rows", overlay_rows), \
                mock.patch.object(boot_image, "all_sites", lambda r: ([], {"lost_pages": ["0x0", "0x0"]})), \
                mock.patch.object(boot_image, "plan", lambda *a: ([], {})), \
                mock.patch.object(boot_image, "overlay_report", lambda *a: {"bytes": 0}), \
                mock.patch.object(boot_relayout, "branch_sweep", lambda *a: ([], None)), \
                mock.patch.object(boot_relayout, "admit", lambda *a: ([], [], {}, ctx, {}, none, none)), \
                mock.patch.object(boot_relayout, "choose_moves", lambda *a: ([], {}, [], {})), \
                mock.patch.object(boot_relayout, "relayout_pieces", lambda *a: ([], [], set())), \
                mock.patch.object(boot_relayout, "validate_sweep", lambda *a: {}), \
                mock.patch.object(boot_relayout, "check_semantic", lambda r, sc, mv, dt, br, si, exe, base, pub, bi=None:
                                  (self.check(exe), [], {})):
            rep = boot_relayout.build_image(out=self.out, tag="t", overlay=["closed"], status=status, objs=object(),
                                            own_data=True)
        self.assert_bound_to_checked(rep)
        self.assertEqual(rep["own_data"]["owners"], [])
        self.assertEqual(seen, [(["closed"], "as selected")])
        self.assertTrue(rep["provenance"]["specs_moved"] and rep["provenance"]["dirty"])


class Integration(Fixture):
    def test_carried_sections_are_boot_images(self):
        self.assertEqual(io_.CARRIED, boot_image.KEEP)
        self.assertEqual(io_.TIME_FORMAT, boot_image.TIME_FORMAT)

    def test_boot_image_link_ownership_reports(self):
        """boot_image.py link --ownership builds, then measures the report it wrote."""
        out = self.tmp / "out"
        out.mkdir()

        def fake_build(base, out_dir, tag, *a, **k):
            rep = overlay_report()
            rep["provenance"] = self.provenance(OVERLAY_IMAGE, OVERLAY_MAP.encode())
            (out_dir / f"{tag}.exe").write_bytes(OVERLAY_IMAGE)
            (out_dir / f"{tag}.map").write_bytes(OVERLAY_MAP.encode())
            (out_dir / f"{tag}.json").write_text(json.dumps(rep), encoding="utf-8")
            return rep
        printed = io.StringIO()
        with mock.patch.object(boot_image, "build_image", fake_build), \
                mock.patch.object(boot_image.build, "EXE", self.tmp / "retail.dat"), \
                mock.patch.object(io_, "ledger_text", lambda commit: (LEDGER, "given")), \
                mock.patch.object(io_, "naked_rows", lambda rows, commit: frozenset()), \
                contextlib.redirect_stdout(printed):
            rc = boot_image.main(["link", "--out", str(out), "--tag", "t", "--ownership"])
        self.assertEqual(rc, 0)
        text = printed.getvalue()
        self.assertIn(f"image_ownership (overlay, {out / 't.json'}): verified", text)
        self.assertIn(f"NOT OURS (bridged + unproven): {0x260:,}", text)


if __name__ == "__main__":
    unittest.main()
