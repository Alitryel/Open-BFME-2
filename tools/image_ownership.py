#!/usr/bin/env python3
"""Who produced each byte of the built game image: our compiled objects, or retail.

The north-star figure the fleet drives to zero is NOT OURS: the bytes of the
runnable image (tools/boot_image.py, tools/boot_relayout.py) that still come
from retail game.dat rather than from our build. Every .text function already
byte-matches one at a time; the image that runs is still retail "scaffold"
with our compiled units laid over it, so retail supplies the unowned code, the
data, the tables, the resources. This tool says how much, where, and what.

Every byte of the loaded image (its headers and each section's virtual extent)
has exactly one owner, as in Open-BFME-1's tools/image_compose.py:

  ours       a compiled unit (an overlaid or moved function) or a datum placed
             from a compiled object (--own-data), split by provenance lane
             (progress.source_lane: authored, vendored, generated, assembly, and
             library for a prebuilt .lib member; `unknown` when the ledger at
             the report's commit has no row for it).
  bridged    retail bytes the scaffold copies in (rewritten relocation fields
             aside): unowned code, .rdata, .data and its zero-fill tail, the
             export directory, CRT tables, resources. Also, never ours: a unit
             whose source is a dump (MASM `db`, __emit: retail re-encoded), and
             retail's copy of a datum we also own (`shadowed`: still in the
             image, still read by retail code).
  unproven   compiled bytes the artifacts cannot prove (see below), and image
             bytes no piece and no linker structure explains: not ours.
  filler     int3 the relayout writes over a moved unit's retail range.
  linker     what link.exe or boot_image writes besides the pieces, each with
              its proof: the PE headers; the import directory, IAT and base
              relocations, each by its PE data directory's exact extent;
              alignment only up to the
             first boundary the next contribution's alignment requires; and
             a piece's own padding (boot_image's pad and trailing int3) of the
             fill it writes. Anything else no piece covers is unproven.

NOT OURS = bridged + unproven. Filler and linker bytes are neither retail's nor
a compiled object's; they are reported, never counted either way.

Honest by construction. Nothing the report JSON says is credit by itself; every
verdict comes from the artifacts it is bound to:

  - Binding. The image (<tag>.exe) and the link map (<tag>.map) must be the
    files the build hashed into the report's provenance, each read once here.
    An unbound or legacy report is printable, and every compiled byte in it is
    `unproven`.
  - Geometry. Each piece's class and new address come from the link map: the
    public boot_image gave it (`_bootp_<rva>` scaffold or filler in a
    scaffold*.obj, `_bootu_<rva>` a unit in overlay*.obj or moved*.obj,
    `_bootd_<rva>` an owned datum in moved*.obj) at the address link.exe put
    it. A report piece with no such public, a public no report piece names, or
    one in another object, is refused. The scaffold, in-place units and fillers
    must tile every retail section boot_image carries (CARRIED) exactly, so no
    retail byte can leave the account; each moved unit has the filler of its
    range; each piece's bytes in the image must be retail's at its retail
    address but for relocated fields (the image's own base relocations), rel32
    operands in code and image-relative fields, and a filler must be int3.
  - Objects. A unit or datum is ours only when its bytes in the image are the
    bytes of a compiled object provenance lists (provenance.objects: its
    manifest digest re-derived, the file re-hashed to the digest the build
    consumed): the unit's COMDAT section (or its row's slice) or the datum's
    extent (boot_relayout.datum_extent), relocation fields masked, at the
    object location provenance names; the extent is the object's, not the
    report's; the unit's ledger row (at the report's commit) must name that
    object's source and lie in retail .text, a datum in one retail data section.
  - Cross-checks. The report's own check must agree: its per-class byte totals
    equal the rebuilt pieces, no counter named *-bad or *-differ (nor
    ZERO_COUNTERS) is non-zero, the image is image_ok and the mode is one of
    MODES. These only ever refuse. Anything refused and every compiled byte is
    `unproven`. No ledger row is credited by itself: a row only names the lane
    of a unit the objects already proved.
  - The partition is checked: owners never overlap, every piece lies in one
    section of the built image, and the buckets sum to the image size.

`record` appends one row to reverse/image_ownership_history.csv (append-only,
under a lock held across read, validation, append and fsync) for a verified,
bound measurement whose build was clean and still is. Under the lock it
re-reads the report and re-hashes the image, map and retail baseline it
measured, re-checks the inputs' git state against the state the build recorded
at its start and end, re-judges every consumed object (the bytes linked,
strictly current for its source, no untracked dependency) and re-hashes the
spec files (the build selected from snapshots of them) and tools. The row
carries the commit, the overlay specs and seed, and the digests of the report,
image, map, retail baseline, ledger, objects, inputs and tools, and an SSH
signature (ssh-keygen -Y, namespace SIGN_NAMESPACE) by the publisher seat's
key ($BFME_OWNERSHIP_SIGNING_KEY); a seat without it records nothing.
`check-history --staged` (.githooks/pre-commit) refuses a commit whose history
changes a committed row or adds one without a valid signature from a key in
the publisher's public-key pin outside the repository. Without that pin, new
rows are refused. Rows cannot re-verify at commit time (their image, map and
objects are build outputs no commit holds), so the signature is what says
record() accepted them. Timestamps are parsed UTC and only move forward, and
an image is recorded once. The private key must live on a host or account
agent seats cannot read. The publisher must re-record a conflicting history
row on the new tip, never rebase the row.

The object manifest proves source objects as read by boot_image, but does not
independently bind section bytes in overlay.obj or moved.obj to the bytes
link.exe consumed: the map establishes placement, not that last hop.

The worklist ranks the bridged regions by size and says what they are: data by
reverse/retail_inventory/data_items.csv (vtable, string, eh_*, ...), code by the
ledger row there and the overlay's verdict on it (<tag>.overlay.csv: refused
datum-differs, not requested, ...).

  python3 tools/image_ownership.py report [build/boot/relayout.json] [--image X.exe] [--limit 30] [--json]
  python3 tools/image_ownership.py worklist [REPORT] [--section .rdata] [--limit 50]
  python3 tools/image_ownership.py record REPORT        # append the history row (refuses unless current)
  python3 tools/image_ownership.py check-history [--staged]
  python3 tools/boot_image.py link --overlay Code/ --relayout --own-data --ownership   # build, then report

`measure(report_json_path, image=None) -> dict` is the API (tools/nightly_measure.py):
its `verified` and `refusals` say whether the compiled bytes were proven, and
`record(receipt)` appends it or raises SystemExit with every reason it may not.
"""
import argparse
import bisect
import calendar
import collections
import contextlib
import csv
import hashlib
import io
import json
import os
import re
import struct
import subprocess
import sys
import tempfile
import time
from pathlib import Path

import numpy as np

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))

RULES = "ownership-1"
KNOWN_RULES = (RULES,)
HISTORY = ROOT / "reverse" / "image_ownership_history.csv"
DATA_ITEMS = ROOT / "reverse" / "retail_inventory" / "data_items.csv"
DEFAULT_REPORT = ROOT / "build" / "boot" / "relayout.json"
LANES = ("authored", "vendored", "generated", "assembly", "library", "unknown")
# a datum takes the least-credited lane of the units its object supplied
LANE_CREDIT = ("dump", "unknown", "generated", "assembly", "library", "vendored", "authored")
SECTIONS = (".text", ".rdata", ".data", ".rsrc", "STLPORT_", "rts.ver")
OTHER = "headers/other"
# the retail sections boot_image's scaffold carries (boot_image.KEEP); the scaffold,
# in-place units and fillers must tile each exactly. Retail's two blank-named
# sections (base relocations and imports, regenerated by link.exe; and an
# unnamed executable one) are not in the image at all.
CARRIED = (".text", ".rdata", ".data", "STLPORT_", "rts.ver", ".rsrc")
# the modes boot_image (overlay, scaffold) and boot_relayout (relayout["mode"]) write
MODES = ("scaffold", "overlay", "relayout", "in-place", "relayout+own-data", "in-place+own-data")
# the objects boot_image writes each public kind into (boot_image.chunk_paths numbers the splits)
PIECE_OBJECTS = {"p": re.compile(r"scaffold\d*\.obj", re.I), "u": re.compile(r"(?:overlay|moved)\d*\.obj", re.I),
                 "d": re.compile(r"moved\d*\.obj", re.I)}
COMDAT, UNINITIALIZED = 0x1000, 0x80     # COFF section flags
IMPORT_DIR, BASERELOC_DIR, IAT_DIR = 1, 5, 12
# check counters that must be zero besides every *-bad and *-differ
ZERO_COUNTERS = ("filler-bytes-not-int3", "branch-into-filler", "owned-writable-referenced-by-retail-code",
                 "biased-across-owned-data", "text-pieces-moved", "baserelocs-missing", "baserelocs-extra")
# This tool and the lane rules it applies: a history row names their digest.
TOOL_FILES = ("image_ownership.py", "progress.py")
CHECK_CLASSES = ("moved", "inplace", "owned", "scaffold")
TIME_FORMAT = "%Y-%m-%dT%H:%M:%SZ"       # boot_image.TIME_FORMAT
CLOCK_SKEW = 300                         # seconds a build may postdate its measurement (clocks differ)


def sha256_bytes(data):
    return hashlib.sha256(data).hexdigest()


def sha256_file(path):
    h = hashlib.sha256()
    with open(path, "rb") as f:
        for block in iter(lambda: f.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


def tools_digest():
    h = hashlib.sha256()
    for name in TOOL_FILES:
        h.update(name.encode() + b"\0" + (ROOT / "tools" / name).read_bytes())
    return h.hexdigest()


def utc_seconds(text):
    """Seconds since the epoch of a TIME_FORMAT UTC timestamp (ValueError if it is not one)."""
    return calendar.timegm(time.strptime(str(text), TIME_FORMAT))


# ---------------------------------------------------------------- PE (stdlib, numpy for bytes)
def pe_layout(data):
    """Header facts and the section table of a PE image (Open-BFME-1 image_compose)."""
    if data[:2] != b"MZ":
        raise ValueError("not a PE image")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe:pe + 4] != b"PE\0\0":
        raise ValueError("no PE signature")
    count, optional = struct.unpack_from("<H", data, pe + 6)[0], struct.unpack_from("<H", data, pe + 20)[0]
    opt = pe + 24
    image_base = struct.unpack_from("<I", data, opt + 28)[0]
    entry = struct.unpack_from("<I", data, opt + 16)[0]
    image_size, header_size = struct.unpack_from("<II", data, opt + 56)
    ndirs = min(struct.unpack_from("<I", data, opt + 92)[0], 16, max(0, (optional - 96) // 8))
    dirs = [struct.unpack_from("<II", data, opt + 96 + 8 * k) for k in range(ndirs)] + [(0, 0)] * (16 - ndirs)
    reloc = dirs[BASERELOC_DIR]
    sections = []
    for index in range(count):
        at = opt + optional + 40 * index
        name = data[at:at + 8].rstrip(b"\0").decode("latin-1")
        vsize, rva, raw, pointer = struct.unpack_from("<IIII", data, at + 8)
        sections.append({"name": name, "rva": rva, "virtual_size": vsize, "raw_size": raw, "file_offset": pointer})
    return {"image_base": image_base, "entry": entry, "image_size": image_size, "header_size": header_size,
            "reloc_dir": reloc, "dirs": dirs, "sections": sections}


def mapped(data, layout):
    """The image as the loader maps it (file content at each RVA, zero-fill past it)."""
    end = max([layout["image_size"]] + [s["rva"] + max(s["virtual_size"], s["raw_size"])
                                        for s in layout["sections"]])
    img = bytearray(end)
    img[:layout["header_size"]] = data[:layout["header_size"]]
    for s in layout["sections"]:
        n = min(s["raw_size"], s["virtual_size"] or s["raw_size"])
        chunk = data[s["file_offset"]:s["file_offset"] + n] if s["file_offset"] else b""
        img[s["rva"]:s["rva"] + len(chunk)] = chunk
    return np.frombuffer(bytes(img), dtype=np.uint8)


def reloc_mask(img, rva, size):
    """Bool per image byte: inside a HIGHLOW field the image's base relocations list."""
    mask = np.zeros(len(img) + 4, dtype=bool)
    at, end = rva, min(rva + size, len(img))
    while at + 8 <= end:
        page, block = struct.unpack_from("<II", img, at)
        if block < 8:
            break
        entries = np.frombuffer(img[at + 8:at + block].tobytes(), dtype="<u2")
        sites = page + (entries[(entries >> 12) == 3] & 0xFFF).astype(np.int64)
        sites = sites[sites + 4 <= len(img)]
        for k in range(4):
            mask[sites + k] = True
        at += block
    return mask


class Retail:
    """The retail baseline's section table and mapped bytes."""
    def __init__(self, path):
        self.data = Path(path).read_bytes()
        self.sha256 = sha256_bytes(self.data)
        self.layout = pe_layout(self.data)
        self.secs = sorted((s["rva"], s) for s in self.layout["sections"] if s["name"].strip())
        self.starts = [s[0] for s in self.secs]
        self.image = mapped(self.data, self.layout)

    def section(self, rva):
        i = bisect.bisect_right(self.starts, rva) - 1
        if i >= 0:
            s = self.secs[i][1]
            if rva < s["rva"] + max(s["virtual_size"], s["raw_size"]):
                return s
        return None

    def named(self, name):
        return next((s for _, s in self.secs if s["name"] == name), None)

    def content_end(self, s):
        """End of the section's file content; past it the loader zero-fills."""
        return s["rva"] + min(s["raw_size"], s["virtual_size"] or s["raw_size"])

    def read(self, lo, hi):
        return self.image[lo:hi].tobytes().ljust(hi - lo, b"\0")


# ---------------------------------------------------------------- the link map
MAP_PUBLIC = re.compile(r"^\s*[0-9a-fA-F]{4}:[0-9a-fA-F]{8}\s+(_boot([pud])_([0-9A-F]{8}))\s+([0-9a-fA-F]{8})\s+"
                        r"(?:\S\s+)*?(\S+)\s*$")


def read_map(text, built):
    """(publics {name: (kind p/u/d, retail rva, new rva, object)}, duplicate names)
    from the text of a link.exe map."""
    publics, dup = {}, 0
    for line in text.splitlines():
        m = MAP_PUBLIC.match(line)
        if m:
            name, kind, rva, new, obj = m.groups()
            dup += name in publics
            publics[name] = (kind, int(rva, 16), int(new, 16) - built["image_base"], obj)
    return publics, dup


def geometry(report, publics):
    """([(class, coff name, retail start, new start, size)], refusals): the report's
    pieces whose public the map puts at that address, classed by the map: moved and
    in-place units, filler (a moved unit's int3'd retail range), data, scaffold."""
    moved = {rs for kind, rs, _, obj in publics.values() if kind == "u" and obj.lower().startswith("moved")}
    at, foreign = {}, []
    for name, (kind, rs, ns, obj) in publics.items():
        if not PIECE_OBJECTS[kind].fullmatch(obj):
            foreign.append(f"{name} in {obj}")
            continue
        if kind == "u":
            cls = "moved" if obj.lower().startswith("moved") else "inplace"
        else:
            cls = "data" if kind == "d" else "filler" if rs in moved else "scaffold"
        at[(rs, ns)] = (cls, name)
    out, used, unmatched = [], set(), 0
    for name, rs, ns, size in report.get("pieces_map", []):
        hit = at.get((rs, ns))
        if hit is None or hit[1] in used:
            unmatched += 1
            continue
        used.add(hit[1])
        out.append((hit[0], name, rs, ns, size))
    why = []
    if foreign:
        why.append(f"{len(foreign):,} piece public(s) are defined by an object boot_image did not write "
                   f"(first: {foreign[0]})")
    if unmatched:
        why.append(f"{unmatched:,} report piece(s) have no public of theirs at that address in the link map")
    if len(publics) - len(foreign) > len(used):
        why.append(f"the link map places {len(publics) - len(foreign) - len(used):,} piece(s) the report does not list")
    return out, why


def tiling(pieces, rt, report):
    """Refusals unless the scaffold, in-place units and fillers tile every carried
    retail section exactly, each moved unit has its filler and the owned data are
    the datums own_data names."""
    why, runs = [], collections.defaultdict(list)
    for cls, _, rs, _, size in pieces:
        if cls in ("scaffold", "inplace", "filler"):
            s = rt.section(rs)
            runs[s["name"] if s else None].append((rs, rs + size))
    for name in CARRIED:
        s = rt.named(name)
        if s is None:
            continue
        cur, end, holes, overlap = s["rva"], s["rva"] + s["virtual_size"], 0, 0
        for lo, hi in sorted(runs.pop(name, [])):
            holes += max(0, lo - cur)
            overlap += max(0, min(cur, hi) - lo)
            cur = max(cur, hi)
        holes += max(0, end - cur)
        if holes or overlap or cur > end:
            why.append(f"retail {name} is not tiled exactly: {holes:,} byte(s) no piece covers, "
                       f"{overlap:,} covered twice, {max(0, cur - end):,} past its end")
    for name, spans in runs.items():
        why.append(f"{len(spans):,} piece(s) copy retail bytes from {name or 'outside any section'}, "
                   "a section boot_image does not carry")
    fill = collections.Counter((rs, size) for cls, _, rs, _, size in pieces if cls == "filler")
    if fill != collections.Counter((rs, size) for cls, _, rs, _, size in pieces if cls == "moved"):
        why.append("filler ranges are not exactly the moved units' retail ranges")
    owners = (report.get("own_data") or {}).get("owners")
    data = sorted((rs, size) for cls, _, rs, _, size in pieces if cls == "data")
    if data and owners is not None and data != sorted((o[0], o[1]) for o in owners):
        why.append("the owned data pieces are not the datums own_data.owners names")
    return why


def foreign_pieces(pieces, img, ret, relocs):
    """[(class, name, retail start, new start, size, bytes)] for pieces whose bytes in
    the image are not retail's at their retail address, beyond what linking rewrites:
    the image's base-relocated fields, rel32 operands in code (E8 / E9 / 0F 8x), and
    image-relative fields (a 4-byte field holding an in-image RVA in both). A filler
    must be int3 throughout."""
    out, na, nr = [], len(img), len(ret)
    for cls, name, rs, ns, size in pieces:
        if ns < 0 or ns + size > na:
            out.append((cls, name, rs, ns, size, size))
            continue
        a = img[ns:ns + size]
        if cls == "filler":
            n = int(np.count_nonzero(a != 0xCC))
            if n:
                out.append((cls, name, rs, ns, size, n))
            continue
        b = ret[rs:rs + size] if rs + size <= nr else np.concatenate(
            [ret[min(rs, nr):nr], np.zeros(size - max(0, nr - rs), np.uint8)])
        if np.array_equal(a, b):
            continue
        d = np.flatnonzero(a != b) + ns
        d = d[~relocs[d]]
        if d.size and name.startswith(".text"):
            ok = np.zeros(d.size, dtype=bool)
            for k in range(1, 5):
                j = d - k
                op, prev = img[np.maximum(j, 0)], img[np.maximum(j - 1, 0)]
                ok |= (j >= ns) & ((op == 0xE8) | (op == 0xE9) | ((prev == 0x0F) & (op >= 0x80) & (op <= 0x8F)))
            d = d[~ok]
        if d.size:
            fr = (rs + d - ns) & ~3                   # the field, aligned on its retail address
            fb = fr - rs + ns
            inside = (fb >= ns) & (fb + 4 <= ns + size) & (fr + 4 <= nr)
            fbc, frc = np.clip(fb, 0, na - 4), np.clip(fr, 0, nr - 4)
            va = sum(img[fbc + k].astype(np.int64) << (8 * k) for k in range(4))
            vr = sum(ret[frc + k].astype(np.int64) << (8 * k) for k in range(4))
            d = d[~(inside & (va > 0) & (va < na) & (vr > 0) & (vr < nr))]
        if d.size:
            out.append((cls, name, rs, ns, size, int(d.size)))
    return out


# ---------------------------------------------------------------- the objects
def load_object(rel, digest):
    """((sections, symbols, bytes), None) for an object provenance lists, read once and
    re-hashed to the digest the build consumed; (None, why) if it is not that object."""
    import link_cycle
    path = Path(rel) if os.path.isabs(rel) else ROOT / rel
    try:
        data = path.read_bytes()
    except OSError:
        return None, "missing"
    if sha256_bytes(data) != digest:
        return None, "not the bytes the build consumed"
    try:
        return link_cycle.parse_coff(data) + (data,), None
    except (struct.error, ValueError, IndexError):
        return None, "not a COFF object"


def object_proofs(pieces, img, report, prov, by_key, rt):
    """Refusals unless every unit and datum piece is a compiled object's bytes. The
    object must be in provenance.objects (manifest digest re-derived, file re-hashed);
    a unit (provenance.objects.units: [rva, size, object, section, offset]) is its
    object's COMDAT .text section whole, else its ledger row's slice, and its ledger
    row names that object's source; a datum (own_data.owners: [rva, size, source,
    object, section, offset]) is boot_relayout.datum_extent of a non-code section.
    The image's bytes must equal the object's (zero for uninitialized data) outside
    its relocation fields, and the retail range must be .text (a unit) or lie in one
    retail data section (a datum)."""
    import boot_image
    import boot_relayout
    objects = prov.get("objects") or {}
    entries = objects.get("entries") or []
    why, bad, first = [], collections.Counter(), {}
    if objects.get("digest") != boot_image.objects_digest(entries):
        why.append("provenance.objects.digest is not the digest of the object manifest it lists")
    manifest = {e[0]: (e[1], e[2]) for e in entries if len(e) == 3}
    where = {(u[0], u[1]): u[2:] for u in objects.get("units") or [] if len(u) == 5}
    owners = {(o[0], o[1]): o for o in (report.get("own_data") or {}).get("owners") or [] if len(o) >= 2}
    names = {(a, n): name for a, n, name in report.get("authored", [])}
    text = rt.named(".text")
    jobs = collections.defaultdict(list)

    def fail(kind, what):
        bad[kind] += 1
        first.setdefault(kind, what)
    for cls, name, rs, ns, size in pieces:
        what = f"{cls} retail 0x{rs:08X}"
        if cls in ("moved", "inplace"):
            row = by_key.get((rs, names.get((rs, size))))
            if (rs, size) not in where:
                fail("have no object location in provenance.objects.units", what)
            elif row is None or row.get("status") != "matched":
                fail("have no matched ledger row", what)
            elif row["source"] != manifest.get(where[(rs, size)][0], (None, None))[1]:
                fail("come from an object provenance does not list for their row's source", what)
            elif text is None or not (text["rva"] <= rs and rs + size <= text["rva"] + text["virtual_size"]):
                fail("lie outside retail .text", what)
            else:
                jobs[where[(rs, size)][0]].append((cls, what, ns, size) + tuple(where[(rs, size)][1:]) + (row,))
        elif cls == "data":
            o = owners.get((rs, size))
            s1, s2 = rt.section(rs), rt.section(rs + size - 1)
            if o is None or len(o) != 6:
                fail("have no object location in own_data.owners", what)
            elif o[2] is None or o[2] != manifest.get(o[3], (None, None))[1]:
                fail("come from an object provenance does not list for their source", what)
            elif s1 is None or s1 is not s2 or s1["name"] in (".text", ".rsrc") or s1["name"] not in CARRIED:
                fail("do not lie in one retail data section", what)
            else:
                jobs[o[3]].append((cls, what, ns, size, o[4], o[5], None))
    for rel, items in sorted(jobs.items()):
        o, problem = load_object(rel, manifest[rel][0])
        if o is None:
            for _, what, *_x in items:
                fail(f"come from an object that is {problem}", f"{what} ({rel})")
            continue
        secs, _, data = o
        for cls, what, ns, size, sec, off, row in items:
            s = secs[sec - 1] if isinstance(sec, int) and 0 < sec <= len(secs) else None
            if s is None or not isinstance(off, int) or off < 0:
                fail("name no section of their object", what)
                continue
            code = s.name.startswith(".text")
            if cls == "data":
                extent = boot_relayout.datum_extent(o, sec, off) if not code else None
                exact = extent == (off, size)
            else:
                whole = s.flags & COMDAT and off == 0 and not s.name.startswith(".text$x")
                exact = code and bool(s.ptr) and (size == s.size if whole else
                                                  size == int(row.get("target_size") or 0) and off + size <= s.size)
            if not exact:
                fail("are not their object's extent" if code == (cls != "data") else
                     "come from the wrong kind of section", what)
                continue
            want = np.zeros(size, np.uint8) if s.flags & UNINITIALIZED or not s.ptr else \
                np.frombuffer(data[s.ptr + off:s.ptr + off + size], np.uint8)
            masked = np.zeros(size, dtype=bool)
            for at, _, _ in s.relocs:
                masked[max(0, at - off):max(0, min(size, at - off + 4))] = True
            got = img[ns:ns + size]
            if len(want) != size or len(got) != size or bool(((got != want) & ~masked).any()):
                fail("are not their object's bytes in the image", what)
        boot_image._SECTION_SYMBOLS.pop(id(o), None)         # datum_extent's cache holds the object
    for kind, n in bad.items():
        why.append(f"{n:,} compiled piece(s) {kind} (first: {first[kind]})")
    return why


# ---------------------------------------------------------------- ledger and lanes
def ledger_text(commit):
    """(functions.csv text, where it came from): the report's commit, or (a report
    with no provenance: printable, never recordable) the working tree."""
    if commit:
        res = subprocess.run(["git", "show", f"{commit}:reverse/functions.csv"], cwd=ROOT, capture_output=True)
        if res.returncode:
            raise SystemExit(f"image_ownership: the ledger at the report's commit {commit} is not readable "
                             f"({res.stderr.decode(errors='replace').strip()}); fetch it")
        return res.stdout.decode("utf-8"), f"commit {commit}"
    return (ROOT / "reverse/functions.csv").read_text(encoding="utf-8"), "worktree (report has no provenance)"


def naked_rows(rows, commit):
    """Matched-row keys (name, target_rva) whose C++ body is naked assembly (progress.py)."""
    import progress
    matched = {(r["name"], r["target_rva"]): (int(r["target_size"] or 0), r["source"]) for r in rows
               if r.get("status") == "matched"}
    return progress.naked_cpp_rows_at(matched, commit or None)


def least_credited(lanes):
    """The lane a datum takes from the lanes of the units its source supplied."""
    return min(lanes, key=LANE_CREDIT.index)


def lane_of(source, notes, naked):
    """progress.source_lane, `unknown` for what it cannot classify."""
    import progress
    if not source:
        return "unknown"
    try:
        return progress.source_lane(source, notes or "", naked)
    except SystemExit:
        return "unknown"


# ---------------------------------------------------------------- the image check's verdicts
def report_mode(report):
    if "relayout" in report:
        return report["relayout"].get("mode", "relayout")
    return "overlay" if report.get("authored") else "scaffold"


def verify(report, pieces, built):
    """Refusals: every way the report's own check disagrees with the rebuilt pieces
    or found a difference. A cross-check only: it never credits a byte."""
    import boot_image
    why = []
    chk = report.get("check") or {}
    if report_mode(report) not in MODES:
        why.append(f"mode {report_mode(report)!r} is none of {', '.join(MODES)}")
    if report.get("link_exit") != 0 or not chk:
        return why + ["the image did not link or was not checked"]
    if not boot_image.image_ok(report):
        why.append("boot_image.image_ok: the image check found a difference")
    if report.get("check_bad"):
        why.append(f"check_bad lists {len(report['check_bad'])} difference(s)")
    for key, value in sorted(chk.items()):
        if value and (key.endswith("-bad") or key.endswith("-differ") or key in ZERO_COUNTERS):
            why.append(f"check {key} = {value}")
    total = collections.Counter()
    for cls, _, _, _, size in pieces:
        total[cls] += size
    units = collections.Counter((a, n) for a, n, _ in report.get("authored", []))
    placed = collections.Counter((rs, size) for cls, _, rs, _, size in pieces if cls in ("moved", "inplace"))
    if any(v > 1 for v in units.values()):
        why.append("a unit is listed twice in `authored`")
    if placed != collections.Counter({k: 1 for k in units}):
        why.append(f"units placed {sum(placed.values())} time(s) for {len(units)} listed (each must be placed once)")
    unit_bytes = sum(n for _, n in units)
    ov = report.get("overlay")
    if units and (ov is None or ov.get("bytes") != unit_bytes or ov.get("verified_bytes") != unit_bytes
                  or ov.get("units") != len(units)):
        why.append("the overlay summary's bytes / verified_bytes / units disagree with the listed units")

    def need(key, want):
        if chk.get(key, 0) != want:
            why.append(f"check {key} = {chk.get(key, 0):,}, the pieces say {want:,}")
    if "relayout" in report:
        need("moved-bytes-equal", total["moved"])
        need("inplace-bytes-equal", total["inplace"])
        need("owned-bytes-equal", total["data"])
        need("owned-data-bytes", total["data"])
        need("scaffold-bytes-equal", total["scaffold"])
        need("filler-bytes", total["filler"])
        od = report.get("own_data")
        if total["data"] and (od is None or od.get("bytes_ours") != total["data"]):
            why.append("own_data.bytes_ours disagrees with the owned data pieces")
    else:
        if total["moved"] or total["data"] or total["filler"]:
            why.append("moved, filler or owned-data pieces in a report with no relayout check")
        need("authored-bytes-equal", total["inplace"])
        need("bytes-equal", sum(total.values()))
    # the pieces partition part of the built image: disjoint, each inside one section
    spans = sorted((ns, ns + size) for _, _, _, ns, size in pieces if size)
    if any(b[0] < a[1] for a, b in zip(spans, spans[1:])):
        why.append("pieces overlap in the built image")
    secs = sorted((s["rva"], s["rva"] + s["virtual_size"]) for s in built["sections"])
    los = [s[0] for s in secs]
    outside = 0
    for lo, hi in spans:
        i = bisect.bisect_right(los, lo) - 1
        if i < 0 or hi > secs[i][1] or lo < built["header_size"]:
            outside += 1
    if outside:
        why.append(f"{outside} piece(s) lie outside the built image's sections")
    return why


def image_directories(rt, built, pieces, map_text):
    """Check the entry and carried retail directories against PE and map bytes."""
    why = []
    placed = [(rs, rs + size, ns) for cls, _, rs, ns, size in pieces if cls != "filler"]

    def location(rva):
        return next((ns + rva - lo for lo, hi, ns in placed if lo <= rva < hi), None)

    entry = rt.layout["entry"]
    if not entry and built["entry"]:
        why.append("image entry is present although retail has no entry")
    elif entry:
        public = re.search(r"^\s*[0-9A-Fa-f]{4}:[0-9A-Fa-f]{8}\s+_boot_entry\s+"
                           r"([0-9A-Fa-f]{8})\s", map_text, re.M)
        mapped_entry = location(entry)
        map_entry = int(public.group(1), 16) - built["image_base"] if public else None
        if mapped_entry is None or built["entry"] != mapped_entry or map_entry != mapped_entry:
            why.append("image entry or _boot_entry map public disagrees with retail's entry piece")
    for index, kind in ((0, "export"), (2, "resource")):
        rva, _ = rt.layout["dirs"][index]
        expected = location(rva) if rva else 0
        if (rva and expected is None) or built["dirs"][index][0] != expected:
            why.append(f"image {kind} directory does not point to the retail directory's piece")
    return why


# ---------------------------------------------------------------- worklist labels
def disjoint(items):
    """Sorted, non-overlapping [(lo, hi, cls, detail)]: an earlier item keeps a byte."""
    out, end = [], -1
    for lo, hi, cls, detail in sorted(items, key=lambda x: (x[0], -x[1])):
        lo = max(lo, end)
        if lo < hi:
            out.append((lo, hi, cls, detail))
            end = hi
    return out


def label(intervals, items):
    """(lo, hi, payload, item or None) for every part of every interval [(lo, hi, payload)]."""
    starts = [x[0] for x in items]
    for lo, hi, payload in intervals:
        a = lo
        k = max(bisect.bisect_right(starts, a) - 1, 0)
        while a < hi:
            while k < len(items) and items[k][1] <= a:
                k += 1
            if k < len(items) and items[k][0] <= a:
                b = min(hi, items[k][1])
                yield a, b, payload, items[k]
            else:
                b = min(hi, items[k][0]) if k < len(items) else hi
                yield a, b, payload, None
            a = b


def data_items(path):
    if not path or not Path(path).exists():
        return []
    with open(path, newline="", encoding="utf-8") as f:
        return disjoint([(int(r["rva"], 16), int(r["rva"], 16) + int(r["size"]), r["class"], r["detail"])
                         for r in csv.DictReader(f) if int(r["size"] or 0) > 0])


def overlay_statuses(text):
    """{(rva, name): overlay verdict} from the text of <tag>.overlay.csv."""
    return {(int(r["retail_rva"], 16), r["name"]): r["overlay"] for r in csv.DictReader(io.StringIO(text))}


def code_items(rows, statuses, naked):
    """Ledger rows as worklist items: what each one's retail range is and why it is not ours."""
    items = []
    for r in rows:
        if not (r.get("target_rva") or "").startswith("0x") or not int(r.get("target_size") or 0):
            continue
        lo = int(r["target_rva"], 16)
        st = statuses.get((lo, r["name"])) if statuses is not None else None
        if st is None:
            lane = lane_of(r["source"], r.get("notes"), (r["name"], r["target_rva"]) in naked)
            cls = f"code: not overlaid ({lane})" if statuses is not None else "code: matched row (no overlay verdicts)"
        elif st.startswith("refused:"):
            cls = "code: refused " + st[len("refused:"):].split(":")[0]
        elif st.startswith("folded"):
            cls = "code: folded into another body"
        else:
            cls = "code: " + st
        items.append((lo, lo + int(r["target_size"]), cls, f"{r['name']}  {r['source']}"))
    return disjoint(items)


def gap_parts(sec, piece, retail, lo, hi):
    """[(lo, hi, class)] of bridged bytes no inventory item or ledger row covers;
    in .text, int3 runs (alignment padding) apart from the code between them."""
    if piece == ".edata":
        return [(lo, hi, "export directory")]
    if piece.startswith(".CRT"):
        return [(lo, hi, "crt initializer table")]
    if sec == ".text":
        return [(lo + m.start(), lo + m.end(), "padding (int3)" if m.group()[:1] == b"\xCC" else "code: no ledger row")
                for m in re.finditer(rb"\xCC+|[^\xCC]+", retail.read(lo, hi))]
    if sec in (".rdata", ".data"):
        return [(lo, hi, "no inventory item")]
    return [(lo, hi, "resources" if sec == ".rsrc" else "section data")]


# ---------------------------------------------------------------- measure
def empty_section():
    return {"ours": collections.Counter(), "bridged": collections.Counter(), "unproven": 0, "filler": 0, "linker": 0}


def piece_shape(name, rs):
    """(pad, trail, alignment, fill) of the section contribution boot_image writes for
    a piece (boot_image.plan / write_scaffold, boot_relayout.relayout_pieces /
    write_moved): `pad` fill bytes before it (retail's address mod the alignment),
    `trail` after it; None for a name it does not write."""
    import boot_image
    if name.startswith(".text$r"):
        return rs & 0xF, 1, 16, 0xCC                   # int3 before and after each moved body
    if name in (".ordata", ".odata"):
        return rs & 0xF, 0, 16, 0
    if name.startswith(".text$p"):
        return 0, 0, 4096 if name == ".text$p000000" else 1, 0
    flags = boot_image.FLAGS.get(".CRT" if name.startswith(".CRT") else name)
    if flags is None:
        return None
    align = 1 << (((flags >> 20) & 0xF) - 1)
    return (rs & 0xFFF if align == 4096 else 0), 0, align, 0


def linker_structures(img, built):
    """Only PE directory extents, not arbitrary descriptor pointers or section tails."""
    out = []
    for index, kind in ((IMPORT_DIR, "import directory"), (IAT_DIR, "import address table"),
                        (BASERELOC_DIR, "base relocations")):
        rva, size = built["dirs"][index]
        if size:
            out.append((rva, rva + size, kind, 4))
    return out


def linker_gaps(built, img, pieces):
    """({linker kind: bytes}, [(built section, lo, hi)] unproven) for every image byte
    no piece covers. Linker only with proof: the headers; linker_structures; a
    piece's own pad and trail (piece_shape) holding its fill; and, before a
    contribution, zeros or int3 up to exactly the first boundary its alignment
    requires. Anything else, the tail of a section past its last contribution
    included, is unproven."""
    linker = collections.Counter({"headers": built["header_size"]})
    unproven = []
    items = []
    for _, name, rs, ns, size in pieces:
        shape = piece_shape(name, rs) or (0, 0, None, None)
        pad, trail, align, fill = shape
        items.append((ns - pad, ns, ns + size, ns + size + trail, align, fill, None))
    for lo, hi, kind, align in linker_structures(img, built):
        items.append((lo, lo, hi, hi, align, None, kind))
    items.sort(key=lambda x: x[:4])
    starts = [x[0] for x in items]

    def uniform(a, b, fill=None):
        chunk = img[a:b]
        return bool((chunk == fill).all()) if fill is not None else not chunk.any() or bool((chunk == 0xCC).all())
    for s in built["sections"]:
        lo, hi, cur = s["rva"], s["rva"] + s["virtual_size"], s["rva"]
        for clo, blo, bhi, chi, align, fill, kind in items[bisect.bisect_left(starts, lo):
                                                           bisect.bisect_left(starts, hi)]:
            if clo > cur:
                if align and clo == -(-cur // align) * align and uniform(cur, clo):
                    linker["alignment"] += clo - cur
                else:
                    unproven.append((s["name"], cur, clo))
                cur = clo
            for a, b, what in ((cur, blo, "pad"), (max(cur, blo), bhi, "body"), (max(cur, bhi), chi, "pad")):
                b = min(b, hi)
                if a >= b:
                    continue
                if what == "body":
                    if kind is not None:
                        linker[kind] += b - a
                elif fill is not None and uniform(a, b, fill):
                    linker["piece padding"] += b - a
                else:
                    unproven.append((s["name"], a, b))
                cur = max(cur, b)
        if hi > cur:
            unproven.append((s["name"], cur, hi))
    return linker, unproven


def measure(report_json_path, *, image=None, map_path=None, retail=None, ledger=None, naked=None,
            data_items_path=DATA_ITEMS, rows_csv=None, worklist_limit=50, worklist_csv=None):
    """Who owns each byte of the image a boot_image / boot_relayout report describes.

    `image` is the linked image (default: <report>.exe beside the report), its link
    map `map_path` (default: the image's .map). Returns the receipt (see the module
    docstring): `verified` and `refusals` (why the compiled bytes are not proven),
    `north_star` (bridged + unproven bytes), `totals`, `sections`,
    `bridged_by_class`, `worklist`, `warnings`. `ledger` (functions.csv text),
    `naked` (row keys), `retail` and `rows_csv` override what the report and its
    commit name."""
    report_path = Path(report_json_path)
    raw = report_path.read_bytes()
    report = json.loads(raw)
    prov = report.get("provenance") or {}
    refusals, warnings = [], []
    image = Path(image) if image else report_path.with_suffix(".exe")
    map_path = Path(map_path) if map_path else image.with_suffix(".map")
    for path, what in ((image, "image"), (map_path, "link map")):
        if not path.exists():
            raise SystemExit(f"image_ownership: the {what} {path} is missing; there is nothing to account")
    if retail is None:
        import build
        retail = build.EXE
    rt = Retail(retail)
    data, map_raw = image.read_bytes(), map_path.read_bytes()       # each read once: what is hashed is measured
    image_sha, map_sha = sha256_bytes(data), sha256_bytes(map_raw)
    built = pe_layout(data)
    img = mapped(data, built)
    bound, map_bound = prov.get("image_sha256") == image_sha, prov.get("map_sha256") == map_sha
    if not prov:
        refusals.append("the report has no provenance (built before boot_image recorded it): nothing binds it "
                        "to this image, so no compiled byte is proven; rebuild")
    else:
        if prov.get("retail_sha256") != rt.sha256:
            refusals.append("the retail baseline is not the one the report was built against")
        if not bound:
            refusals.append("the image on disk is not the one the report checked (SHA-256 differs or unrecorded)")
        if not map_bound:
            refusals.append("the link map on disk is not the build's (SHA-256 differs or unrecorded)")
    commit = prov.get("commit")
    if ledger is None:
        text, ledger_from = ledger_text(commit)
    else:
        text, ledger_from = ledger, "given"
    ledger_sha = sha256_bytes(text.replace("\r\n", "\n").encode("utf-8"))      # as boot_image.provenance
    ledger = list(csv.DictReader(io.StringIO(text)))
    if naked is None:
        naked = naked_rows(ledger, commit)

    # the geometry, from the map and the image; the report only names sizes the tiling
    # and the objects pin
    publics, dup = read_map(map_raw.decode("latin-1"), built)
    if dup:
        refusals.append(f"the link map names {dup} piece public(s) twice")
    pieces, why = geometry(report, publics)
    refusals += why + tiling(pieces, rt, report) + verify(report, pieces, built)
    refusals += image_directories(rt, built, pieces, map_raw.decode("latin-1"))
    foreign = foreign_pieces(pieces, img, rt.image, reloc_mask(img, *built["reloc_dir"]))
    if foreign:
        cls, name, rs, ns, size, n = foreign[0]
        refusals.append(f"{len(foreign):,} piece(s) are not retail's bytes at their retail address in the image, "
                        f"beyond relocated fields ({sum(x[5] for x in foreign):,} byte(s); first: {cls} {name} "
                        f"retail 0x{rs:08X} at 0x{ns:08X}, {n} byte(s))")
    by_key = {}
    for r in ledger:
        if (r.get("target_rva") or "").startswith("0x"):
            by_key.setdefault((int(r["target_rva"], 16), r["name"]), r)
    if prov:
        refusals += object_proofs(pieces, img, report, prov, by_key, rt)
    verified = not refusals

    unit_lane, source_lanes = {}, collections.defaultdict(set)
    for rva, size, name in report.get("authored", []):
        r = by_key.get((rva, name))
        lane = lane_of(r["source"], r.get("notes"), (name, r["target_rva"]) in naked) if r else "unknown"
        unit_lane[(rva, size)] = (lane, name, r["source"] if r else None)
        if r:
            source_lanes[r["source"]].add(lane)
    data_lane = {}
    for owner in (report.get("own_data") or {}).get("owners", []):
        source = owner[2] if len(owner) > 2 else None
        data_lane[(owner[0], owner[1])] = (least_credited(source_lanes.get(source) or {"unknown"}), None, source)

    secs = collections.defaultdict(empty_section)
    owned_ranges = sorted((rs, rs + size) for cls, _, rs, _, size in pieces if cls == "data")
    bridged_iv = []                                   # (lo, hi, (section, piece, kind)) in retail addresses
    for cls, name, rs, ns, size in pieces:
        s = rt.section(rs)
        sec = s["name"] if s else OTHER
        if cls == "filler":
            secs[sec]["filler"] += size
        elif cls in ("moved", "inplace", "data"):
            lane, uname, source = (data_lane if cls == "data" else unit_lane).get((rs, size), ("unknown", None, None))
            if not verified:
                secs[sec]["unproven"] += size
            elif lane == "dump":
                secs[sec]["bridged"]["dump"] += size
                bridged_iv.append((rs, rs + size, (sec, name, "dump")))
            else:
                secs[sec]["ours"][lane] += size
        else:                                         # scaffold: retail bytes, split by kind
            cuts = {rs, rs + size}
            for lo, hi in owned_ranges[max(bisect.bisect_left(owned_ranges, (rs, 0)) - 1, 0):]:
                if lo >= rs + size:
                    break
                cuts |= {min(max(lo, rs), rs + size), min(max(hi, rs), rs + size)}
            if s is not None and rs < rt.content_end(s) < rs + size:
                cuts.add(rt.content_end(s))
            cuts = sorted(cuts)
            for lo, hi in zip(cuts, cuts[1:]):
                j = bisect.bisect_right(owned_ranges, (lo, float("inf"))) - 1
                if j >= 0 and owned_ranges[j][0] <= lo < owned_ranges[j][1]:
                    kind = "shadowed"
                elif s is not None and lo >= rt.content_end(s):
                    kind = "zero-fill"
                else:
                    kind = "bytes"
                secs[sec]["bridged"][kind] += hi - lo
                bridged_iv.append((lo, hi, (sec, name, kind)))
    linker_by, gaps = linker_gaps(built, img, pieces)
    secs[OTHER]["linker"] = sum(linker_by.values())
    for name, lo, hi in gaps:
        secs[name if name in SECTIONS else OTHER]["unproven"] += hi - lo
    image_bytes = built["header_size"] + sum(s["virtual_size"] for s in built["sections"])

    # totals, and the partition proof
    totals = {"ours_by_lane": collections.Counter(), "bridged_by_kind": collections.Counter(),
              "unproven": 0, "filler": 0, "linker": 0}
    for v in secs.values():
        totals["ours_by_lane"].update(v["ours"])
        totals["bridged_by_kind"].update(v["bridged"])
        for key in ("unproven", "filler", "linker"):
            totals[key] += v[key]
    totals["ours"] = sum(totals["ours_by_lane"].values())
    totals["bridged"] = sum(totals["bridged_by_kind"].values())
    parts = totals["ours"] + totals["bridged"] + totals["unproven"] + totals["filler"] + totals["linker"]
    if parts != image_bytes:
        raise SystemExit(f"image_ownership: the owners sum to {parts:,} bytes, the image has {image_bytes:,}; "
                         "pieces overlap or leave their sections (a report this tool cannot account for)")
    north = totals["bridged"] + totals["unproven"]
    content = totals["ours"] + north

    # worklist: what the bridged bytes are
    statuses, rows_note = None, None
    rows_csv = Path(rows_csv) if rows_csv else (Path((report.get("overlay") or {}).get("rows_csv") or "")
                                                if (report.get("overlay") or {}).get("rows_csv") else None)
    if rows_csv and rows_csv.exists():
        rows_raw = rows_csv.read_bytes()
        if prov.get("rows_csv_sha256") and sha256_bytes(rows_raw) != prov["rows_csv_sha256"]:
            rows_note = f"{rows_csv} is not the report's own (SHA-256 differs): code verdicts not used"
        else:
            statuses = overlay_statuses(rows_raw.decode("utf-8"))
    if rows_note:
        warnings.append(rows_note)
    text_items = code_items(ledger, statuses, naked)
    ditems = data_items(data_items_path)
    regions = collections.OrderedDict()
    by_class = collections.defaultdict(collections.Counter)
    bridged_iv.sort()
    for sec_items, wanted in ((text_items, {".text"}), (ditems, {".rdata", ".data"}), ([], None)):
        part = [x for x in bridged_iv if (x[2][0] in wanted if wanted else x[2][0] not in (".text", ".rdata", ".data"))]
        for lo, hi, (sec, piece, kind), item in label(part, sec_items):
            if kind == "dump":                        # a compiled unit, but its source is retail re-encoded
                parts = [(lo, hi, lo, "code: dump (retail re-encoded)", item[3] if item else "")]
            elif item is not None:                    # one region per inventory item / ledger row
                parts = [(lo, hi, item[0], item[2], item[3])]
            else:
                parts = [(a, b, a, cls, "") for a, b, cls in gap_parts(sec, piece, rt, lo, hi)]
            for a, b, start, cls, detail in parts:
                by_class[sec][cls] += b - a
                e = regions.setdefault((sec, start, cls), {"section": sec, "retail_rva": f"0x{start:08X}",
                                                           "bytes": 0, "class": cls, "detail": detail,
                                                           "kinds": collections.Counter()})
                e["bytes"] += b - a
                e["kinds"][kind] += b - a
    work = sorted(regions.values(), key=lambda e: (-e["bytes"], e["retail_rva"]))
    for e in work:
        e["kinds"] = dict(e["kinds"])
    if worklist_csv:
        with open(worklist_csv, "w", newline="", encoding="utf-8") as f:
            w = csv.writer(f)
            w.writerow(["section", "retail_rva", "bytes", "class", "kinds", "detail"])
            for e in work:
                w.writerow([e["section"], e["retail_rva"], e["bytes"], e["class"],
                            ";".join(f"{k}={v}" for k, v in sorted(e["kinds"].items())), e["detail"]])

    def plain(v):
        return {"ours": dict(v["ours"]), "ours_total": sum(v["ours"].values()), "bridged": dict(v["bridged"]),
                "bridged_total": sum(v["bridged"].values()), "unproven": v["unproven"], "filler": v["filler"],
                "linker": v["linker"]}
    order = list(SECTIONS) + sorted(k for k in secs if k not in SECTIONS and k != OTHER) + [OTHER]
    brief = {k: v for k, v in prov.items() if k != "dirty_paths"}
    if isinstance(brief.get("objects"), dict):         # record re-reads the entries from the report itself
        brief["objects"] = {k: v for k, v in brief["objects"].items() if k not in ("entries", "units")}
    runs = []
    for name, lo, hi in gaps:                          # adjacent unexplained parts read as one region
        if runs and runs[-1][0] == name and runs[-1][2] == lo:
            runs[-1][2] = hi
        else:
            runs.append([name, lo, hi])
    gaps = sorted(runs, key=lambda g: g[1] - g[2])
    return {
        "tool": "image_ownership", "rules": RULES, "measured_utc": time.strftime(TIME_FORMAT, time.gmtime()),
        "report": {"path": str(report_path), "sha256": sha256_bytes(raw), "mode": report_mode(report)},
        "image": {"path": str(image), "sha256": image_sha, "bound": bound},
        "map": {"path": str(map_path), "sha256": map_sha, "bound": map_bound},
        "retail": {"path": str(retail), "sha256": rt.sha256},
        "ledger": {"from": ledger_from, "sha256": ledger_sha},
        "provenance": brief,
        "tools_sha256": tools_digest(),
        "foreign_pieces": [{"class": c, "name": n, "retail_rva": f"0x{rs:08X}", "new_rva": f"0x{ns:08X}",
                            "size": size, "foreign_bytes": k} for c, n, rs, ns, size, k in foreign[:20]],
        "unproven_gaps": [{"section": name, "new_rva": f"0x{lo:08X}", "bytes": hi - lo} for name, lo, hi in gaps[:20]],
        "verified": verified, "refusals": refusals, "warnings": warnings,
        "image_bytes": image_bytes, "content_bytes": content,
        "north_star": north, "north_star_share": round(north / content, 6) if content else None,
        "totals": {"ours": totals["ours"], "ours_by_lane": {k: totals["ours_by_lane"][k] for k in LANES
                                                              if totals["ours_by_lane"][k]},
                   "bridged": totals["bridged"], "bridged_by_kind": dict(totals["bridged_by_kind"]),
                   "unproven": totals["unproven"], "filler": totals["filler"], "linker": totals["linker"],
                   "linker_by_kind": dict(linker_by)},
        "sections": {k: plain(secs[k]) for k in order if k in secs},
        "bridged_by_class": {k: dict(by_class[k].most_common()) for k in order if k in by_class},
        "worklist": work[:worklist_limit], "worklist_size": len(work),
    }


# ---------------------------------------------------------------- history
HISTORY_FIELDS = ["date", "measured", "commit", "mode", "rules", "overlay_specs", "seed",
                  "image_bytes", "content_bytes", "north_star",
                  "bridged", "unproven", "ours", "ours_authored", "ours_vendored", "ours_generated", "ours_assembly",
                  "ours_library", "linker", "filler", "not_ours_text", "not_ours_rdata", "not_ours_data",
                  "not_ours_rsrc", "not_ours_other", "report_sha256", "image_sha256", "map_sha256", "retail_sha256",
                  "ledger_sha256", "objects_digest", "inputs_digest", "build_tools_sha256", "tools_sha256",
                  "signature"]
INT_FIELDS = HISTORY_FIELDS[HISTORY_FIELDS.index("image_bytes"):HISTORY_FIELDS.index("report_sha256")]
SHA_FIELDS = HISTORY_FIELDS[HISTORY_FIELDS.index("report_sha256"):HISTORY_FIELDS.index("signature")]
HEX64 = re.compile(r"^[0-9a-f]{64}$")
LOCK_OFFSET = 1 << 30                    # the byte the history lock holds: past any content, so reads go on
# Rows are signed by the publisher seat: `ssh-keygen -Y sign` with the private key
# $BFME_OWNERSHIP_SIGNING_KEY names. The public-key pin is outside this repository.
SIGNERS = object()                       # default: resolve external pin at call time
SIGNERS_ENV = "BFME_OWNERSHIP_ALLOWED_SIGNERS"
SIGNER = "publisher"
SIGN_NAMESPACE = "bfme2-image-ownership"
KEY_ENV = "BFME_OWNERSHIP_SIGNING_KEY"
SIGNATURE = re.compile(r"[A-Za-z0-9+/]+={0,2}")


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, errors="replace")


def row_message(row):
    """The bytes a row's signature covers: every other field, in order."""
    return json.dumps([str(row.get(k, "")) for k in HISTORY_FIELDS if k != "signature"],
                      separators=(",", ":")).encode()


def sign_row(row, key):
    """The row's signature (the base64 body of an SSH signature) by private key `key`."""
    with tempfile.TemporaryDirectory(prefix="image_ownership_sign_") as d:
        msg = Path(d) / "row"
        msg.write_bytes(row_message(row))
        try:
            res = subprocess.run(["ssh-keygen", "-Y", "sign", "-q", "-f", str(key), "-n", SIGN_NAMESPACE, str(msg)],
                                 capture_output=True, text=True, errors="replace", stdin=subprocess.DEVNULL)
        except OSError as error:
            raise SystemExit(f"image_ownership: not recorded: ssh-keygen could not sign: {error}") from error
        sig = msg.with_name("row.sig")
        if res.returncode or not sig.exists():
            raise SystemExit(f"image_ownership: not recorded: ssh-keygen could not sign with {key}: "
                             f"{(res.stderr or res.stdout).strip()[:300]}")
        lines = [x.strip() for x in sig.read_text(encoding="ascii").splitlines() if x.strip()]
    return "".join(x for x in lines if not x.startswith("-----"))


def row_signed(row, signers):
    """Whether the row carries a valid signature by SIGNER in the allowed_signers file `signers`."""
    body = str(row.get("signature") or "")
    signers = allowed_signers(signers)
    if not signers or not SIGNATURE.fullmatch(body):
        return False
    try:
        lines = [line.strip() for line in Path(signers).read_text(encoding="ascii").splitlines()
                 if line.strip() and not line.lstrip().startswith("#")]
    except (OSError, UnicodeError):
        return False
    # OpenSSH accepts wildcard and comma-separated principals: allow one exact key only.
    if len(lines) != 1:
        return False
    fields = lines[0].split()
    if len(fields) not in (4, 5) or fields[0] != SIGNER or fields[1] != f'namespaces="{SIGN_NAMESPACE}"' \
            or fields[2] not in ("ssh-ed25519", "ecdsa-sha2-nistp256", "ssh-rsa"):
        return False
    armored = "-----BEGIN SSH SIGNATURE-----\n" + "".join(body[i:i + 70] + "\n" for i in range(0, len(body), 70)) \
        + "-----END SSH SIGNATURE-----\n"
    with tempfile.TemporaryDirectory(prefix="image_ownership_verify_") as d:
        sig = Path(d) / "row.sig"
        sig.write_bytes(armored.encode("ascii"))
        try:
            res = subprocess.run(["ssh-keygen", "-Y", "verify", "-f", str(signers), "-I", SIGNER, "-n", SIGN_NAMESPACE,
                                  "-s", str(sig)], input=row_message(row), capture_output=True)
        except OSError:
            return False
    return res.returncode == 0


def allowed_signers(signers=SIGNERS):
    """Resolve the external publisher pin; an unset pin fails closed."""
    if signers is SIGNERS:
        signers = os.environ.get(SIGNERS_ENV)
    if not signers:
        return None
    path = Path(signers).resolve()
    return path if not path.is_relative_to(ROOT.resolve()) and path.is_file() else None


def current_state(prov):
    """The record-time facts record_refusals compares with the build's provenance:
    the inputs' git state now, boot_image's verdict on every consumed object now,
    the spec files' and build tools' digests now, and edits to this tool."""
    import boot_image as bi
    state = bi.input_state()
    objects = bi.objects_now((prov.get("objects") or {}).get("entries") or [])
    specs = {}
    for rel in prov.get("spec_files_sha256") or {}:
        path = Path(rel) if os.path.isabs(rel) else ROOT / rel
        specs[rel] = sha256_file(path) if path.exists() else None
    tools = hashlib.sha256()
    for name in bi.BUILD_TOOLS:
        tools.update(name.encode() + b"\0" + (ROOT / "tools" / name).read_bytes())
    dirty = git("status", "--porcelain", "--untracked-files=all", "--", *("tools/" + t for t in TOOL_FILES)).stdout
    return {"head": state["head"], "status": state["status"], "digest": state["digest"], "objects": objects,
            "spec_files_sha256": specs, "build_tools_sha256": tools.hexdigest(), "tools_dirty": dirty.strip(),
            "now": time.time()}


def reread(receipt):
    """The report's bytes now, or None when it is gone or not the one measured."""
    path = Path(receipt["report"]["path"])
    raw = path.read_bytes() if path.exists() else None
    return raw if raw is not None and sha256_bytes(raw) == receipt["report"]["sha256"] else None


def record_refusals(receipt, now=None, raw=None):
    """Why this measurement may not enter the history (empty: it may). The report
    is re-read (`raw`: as record read it; it must be the one measured), the image,
    map and retail baseline re-hashed; the build's clean, unmoving inputs and
    current objects are re-checked as they are now (`now`: current_state)."""
    out = list(receipt["refusals"])
    raw = reread(receipt) if raw is None else raw
    if raw is None or sha256_bytes(raw) != receipt["report"]["sha256"]:
        return out + ["the report on disk is not the one measured; measure it again"]
    prov = json.loads(raw).get("provenance") or {}
    if not prov:
        return out + ["the report has no provenance; rebuild it with the current boot_image.py"]
    for what in ("image", "map", "retail"):
        path = Path(receipt[what]["path"])
        if not path.exists() or sha256_file(path) != receipt[what]["sha256"]:
            out.append(f"the {what} on disk is not the one measured; measure it again")
    if receipt["report"]["mode"] not in MODES:
        out.append(f"mode {receipt['report']['mode']!r} is none of {', '.join(MODES)}")
    now = current_state(prov) if now is None else now
    if prov.get("dirty") or prov.get("inputs_moved") or prov.get("inputs_start") != prov.get("inputs_end"):
        out.append("the image was built from uncommitted inputs, or inputs moved while it built")
    if prov.get("commit") != now["head"]:
        out.append(f"the image was built at {prov.get('commit')}, HEAD is {now['head']}: measure a current build")
    if now["status"]:
        out.append(f"{len(now['status'])} build input(s) are uncommitted now (first: {now['status'][0].strip()})")
    if now["digest"] != prov.get("inputs_end"):
        out.append("the build inputs' state now is not the state the build ended with")
    objects = prov.get("objects") or {}
    if objects.get("count") != len(objects.get("entries") or []) or not HEX64.match(str(objects.get("digest"))):
        out.append("provenance does not list the objects the link consumed")
    for key in ("changed", "not_current", "untracked_deps"):
        if objects.get(key, 1):
            out.append(f"at build time {objects.get(key, 'unknown')} object(s) were {key.replace('_', ' ')}")
        if now["objects"].get(key):
            out.append(f"now {len(now['objects'][key])} consumed object(s) are {key.replace('_', ' ')} "
                       f"(first: {now['objects'][key][0]})")
    for rel, digest in (prov.get("spec_files_sha256") or {}).items():
        if digest is None or now["spec_files_sha256"].get(rel) != digest:
            out.append(f"the overlay spec file {rel} is missing or changed since the build")
    if now["build_tools_sha256"] != prov.get("build_tools_sha256"):
        out.append("the build tools changed since the build")
    for key in ("retail_sha256", "ledger_sha256", "build_tools_sha256", "image_sha256", "map_sha256",
                "inputs_end"):
        if not HEX64.match(str(prov.get(key) or "")):
            out.append(f"provenance lacks {key}")
    if receipt["ledger"].get("sha256") != prov.get("ledger_sha256"):
        out.append("the ledger the lanes came from is not the one the image was built with")
    if not (receipt["image"]["bound"] and receipt["map"]["bound"]):
        out.append("the image or its map is not bound to the report")
    if receipt["totals"]["ours_by_lane"].get("unknown"):
        out.append(f"{receipt['totals']['ours_by_lane']['unknown']:,} compiled byte(s) have no ledger lane")
    if now["tools_dirty"]:
        out.append("tools/image_ownership.py or tools/progress.py has uncommitted edits")
    try:
        built, measured = utc_seconds(prov.get("built_utc")), utc_seconds(receipt["measured_utc"])
        if built > measured + CLOCK_SKEW:
            out.append("the build is dated after its measurement")
        if measured > now["now"] + CLOCK_SKEW:
            out.append("the measurement is dated in the future")
    except ValueError:
        out.append(f"a timestamp is not {TIME_FORMAT} UTC")
    return out


def history_row(receipt, prov):
    t, secs = receipt["totals"], receipt["sections"]

    def not_ours(*names):
        return sum(secs[n]["bridged_total"] + secs[n]["unproven"] for n in names if n in secs)
    other = [n for n in secs if n not in (".text", ".rdata", ".data", ".rsrc")]
    row = {"date": prov["built_utc"], "measured": receipt["measured_utc"], "commit": prov["commit"],
           "mode": receipt["report"]["mode"], "rules": receipt["rules"],
           "overlay_specs": ";".join(prov.get("overlay_specs") or []),
           "seed": "" if prov.get("seed") is None else prov["seed"], "image_bytes": receipt["image_bytes"],
           "content_bytes": receipt["content_bytes"], "north_star": receipt["north_star"],
           "bridged": t["bridged"], "unproven": t["unproven"], "ours": t["ours"],
           "linker": t["linker"], "filler": t["filler"],
           "not_ours_text": not_ours(".text"), "not_ours_rdata": not_ours(".rdata"),
           "not_ours_data": not_ours(".data"), "not_ours_rsrc": not_ours(".rsrc"), "not_ours_other": not_ours(*other),
           "report_sha256": receipt["report"]["sha256"], "image_sha256": receipt["image"]["sha256"],
           "map_sha256": receipt["map"]["sha256"], "retail_sha256": receipt["retail"]["sha256"],
           "ledger_sha256": prov["ledger_sha256"], "objects_digest": prov["objects"]["digest"],
           "inputs_digest": prov["inputs_end"], "build_tools_sha256": prov["build_tools_sha256"],
           "tools_sha256": receipt["tools_sha256"], "signature": ""}
    for lane in ("authored", "vendored", "generated", "assembly", "library"):
        row["ours_" + lane] = t["ours_by_lane"].get(lane, 0)
    return {k: str(v) for k, v in row.items()}


def check_rows(rows):
    """Problems with history rows: fields, digests, modes, the sums every row must
    keep, timestamps (parsed UTC, built no later than measured, both only moving
    forward), and no report or image recorded twice (under any mode)."""
    out, last = [], (float("-inf"), float("-inf"))
    reports, images = set(), set()
    for number, row in enumerate(rows, start=2):
        if set(row) != set(HISTORY_FIELDS):
            out.append(f"line {number}: fields differ from the header")
            continue
        if row["rules"] not in KNOWN_RULES:
            out.append(f"line {number}: unknown rules {row['rules']!r}")
        if row["mode"] not in MODES:
            out.append(f"line {number}: unknown mode {row['mode']!r}")
        if not all(str(row[k]).isdigit() for k in INT_FIELDS) or not (row["seed"] == "" or row["seed"].isdigit()):
            out.append(f"line {number}: a count is not a non-negative integer")
            continue
        if not all(HEX64.match(row[k]) for k in SHA_FIELDS) or not re.match(r"^[0-9a-f]{40}$", row["commit"]):
            out.append(f"line {number}: a digest or the commit is malformed")
        v = {k: int(row[k]) for k in INT_FIELDS}
        lanes = sum(v["ours_" + k] for k in ("authored", "vendored", "generated", "assembly", "library"))
        if v["ours"] != lanes:
            out.append(f"line {number}: ours != the sum of its lanes")
        if v["north_star"] != v["bridged"] + v["unproven"]:
            out.append(f"line {number}: north_star != bridged + unproven")
        if v["content_bytes"] != v["ours"] + v["north_star"]:
            out.append(f"line {number}: content_bytes != ours + north_star")
        if v["image_bytes"] != v["content_bytes"] + v["linker"] + v["filler"]:
            out.append(f"line {number}: image_bytes != content + linker + filler")
        if v["north_star"] != sum(v[k] for k in ("not_ours_text", "not_ours_rdata", "not_ours_data",
                                                 "not_ours_rsrc", "not_ours_other")):
            out.append(f"line {number}: the per-section figures do not sum to north_star")
        try:
            when = (utc_seconds(row["date"]), utc_seconds(row["measured"]))
        except ValueError:
            out.append(f"line {number}: date or measured is not {TIME_FORMAT} UTC")
        else:
            if when[0] > when[1] + CLOCK_SKEW:
                out.append(f"line {number}: built {row['date']}, after its measurement {row['measured']}")
            if when[0] < last[0] or when[1] < last[1]:
                out.append(f"line {number}: dated before the row above")
            last = (max(last[0], when[0]), max(last[1], when[1]))
        if row["report_sha256"] in reports:
            out.append(f"line {number}: the same report is recorded twice")
        if row["image_sha256"] in images:
            out.append(f"line {number}: this image is recorded twice")
        reports.add(row["report_sha256"])
        images.add(row["image_sha256"])
    return out


def parse_history(text, name="the history"):
    """The rows of history text (line ends normalized: a CRLF checkout is the same history)."""
    reader = csv.reader(io.StringIO(text.replace("\r\n", "\n")))
    header = next(reader, None)
    if header is not None and header != HISTORY_FIELDS:
        raise SystemExit(f"image_ownership: {name} has other columns than this tool writes; update the tools (git pull)")
    return [dict(zip(HISTORY_FIELDS, r)) if len(r) == len(HISTORY_FIELDS) else dict(enumerate(r)) for r in reader]


def read_history(path=HISTORY):
    text = Path(path).read_text(encoding="utf-8") if Path(path).exists() else ""
    return text, parse_history(text, Path(path).name)


def committed_history(path, ref="HEAD"):
    """The history as `ref` has it (None: not tracked there; ref ":" is the index)."""
    try:
        rel = Path(path).resolve().relative_to(ROOT).as_posix()
    except ValueError:
        return None
    res = git("show", f"{ref}:{rel}" if ref != ":" else f":{rel}")
    return res.stdout if res.returncode == 0 else None


def history_problems(text, committed, signers):
    """Problems with history text against the committed text: malformed rows, broken
    sums, a changed committed prefix, and an added row without SIGNER's signature
    in `signers` (an allowed_signers file; None: no key is registered, so no row
    may be added)."""
    signers = allowed_signers(signers)
    norm = text.replace("\r\n", "\n")
    rows = parse_history(norm)
    out = check_rows(rows)
    base = (committed or "").replace("\r\n", "\n")
    if base and not norm.startswith(base):
        out.append("the committed rows were changed (the history is append-only)")
        return out
    kept = len(parse_history(base))
    where = f"a key in {signers}" if signers and Path(signers).exists() else "a registered key (there is none)"
    for number, row in enumerate(rows[kept:], start=2 + kept):
        if not row_signed(row, signers):
            out.append(f"line {number}: not signed by the publisher seat ({where})")
    return out


def check_history(path=HISTORY, committed=None, signers=SIGNERS):
    """Problems with the history file (history_problems) against HEAD's (or `committed`)."""
    text, _ = read_history(path)
    committed = committed_history(path) if committed is None else committed
    return history_problems(text, committed, signers)


def check_range(base, tip, path=HISTORY):
    """Check each pushed commit's history against its predecessor, not just the tip."""
    rel = Path(path).resolve().relative_to(ROOT).as_posix()
    commits = git("rev-list", "--reverse", f"{base}..{tip}")
    if commits.returncode:
        return [f"cannot enumerate pushed range {base}..{tip}: {commits.stderr.strip()}"]
    previous = git("show", f"{base}:{rel}")
    before = previous.stdout if previous.returncode == 0 else ""
    problems = []
    for commit in commits.stdout.splitlines():
        current = git("show", f"{commit}:{rel}")
        if current.returncode:
            if before:
                problems.append(f"{commit[:12]}: the committed history is deleted")
            before = ""
            continue
        problems.extend(f"{commit[:12]}: {problem}" for problem in
                        history_problems(current.stdout, before, SIGNERS))
        before = current.stdout
    return problems


def check_staged(path=HISTORY):
    """Validate staged additions against the publisher's external pin."""
    committed, staged = committed_history(path), committed_history(path, ":")
    if staged is None:
        return ["the committed history is deleted"] if committed else []
    return history_problems(staged, committed or "", allowed_signers())


@contextlib.contextmanager
def history_lock(path):
    """An exclusive lock on the history file (created if missing) for one writer at a
    time: held across reading, validating, appending and fsync."""
    fd = os.open(path, os.O_RDWR | os.O_CREAT | getattr(os, "O_BINARY", 0), 0o644)
    try:
        if os.name == "nt":
            import msvcrt
            os.lseek(fd, LOCK_OFFSET, 0)
            msvcrt.locking(fd, msvcrt.LK_LOCK, 1)    # retries for ten seconds, then raises
        else:
            import fcntl
            fcntl.flock(fd, fcntl.LOCK_EX)
        try:
            yield
        finally:
            if os.name == "nt":
                os.lseek(fd, LOCK_OFFSET, 0)
                msvcrt.locking(fd, msvcrt.LK_UNLCK, 1)
            else:
                fcntl.flock(fd, fcntl.LOCK_UN)
    finally:
        os.close(fd)


def append_history(row, path=HISTORY, committed=None, signers=SIGNERS):
    """Append one row under the lock; refuses a history that is not this tool's, a
    rewritten or truncated committed prefix, an unsigned row, a duplicate report or
    image and time going back. `row` may be a callable run under the lock that
    returns the row (record's re-checks) or raises SystemExit."""
    path = Path(path)
    committed = committed_history(path) if committed is None else committed
    if not path.exists() and committed:
        raise SystemExit(f"image_ownership: {path.name} is missing but tracked at HEAD; restore it "
                         f"(git checkout -- {path.name}) before recording")
    with history_lock(path):
        problems = check_history(path, committed or "", signers)
        if problems:
            raise SystemExit("image_ownership: the history is not sound; nothing recorded:\n  "
                             + "\n  ".join(problems))
        text, rows = read_history(path)
        if text and not text.endswith("\n"):
            raise SystemExit(f"image_ownership: {path.name} does not end in a newline; nothing recorded")
        row = row() if callable(row) else row
        problems = check_rows(rows + [row]) + ([] if row_signed(row, signers) else
                                               ["the new row is not signed by the publisher seat"])
        if problems:
            raise SystemExit("image_ownership: the new row would break the history:\n  " + "\n  ".join(problems))
        handle = io.StringIO()
        if not text:
            handle.write(",".join(HISTORY_FIELDS) + "\n")
        csv.DictWriter(handle, HISTORY_FIELDS, lineterminator="\n").writerow(row)
        with open(path, "a", newline="", encoding="utf-8") as f:
            f.write(handle.getvalue())
            f.flush()
            os.fsync(f.fileno())
    return row


def record(receipt, path=HISTORY, now=None, committed=None, key=None, signers=SIGNERS):
    """Append the receipt's history row, signed with the publisher seat's `key`
    (default $BFME_OWNERSHIP_SIGNING_KEY), or refuse (SystemExit) and say why. Every
    re-check runs under the history lock, on the report bytes the row is made from."""
    key = key or os.environ.get(KEY_ENV)
    if not key:
        raise SystemExit(f"image_ownership: not recorded: rows are signed by the publisher seat (${KEY_ENV} names "
                         "its key) and this seat has none")
    why = record_refusals(receipt, now)                   # fail before touching the history; again under the lock
    if why:
        raise SystemExit("image_ownership: not recorded:\n  " + "\n  ".join(why))

    def gate():
        raw = reread(receipt)
        why = record_refusals(receipt, now, raw) if raw is not None else \
            ["the report changed while it was being recorded; measure it again"]
        if why:
            raise SystemExit("image_ownership: not recorded:\n  " + "\n  ".join(why))
        row = history_row(receipt, json.loads(raw)["provenance"])
        row["signature"] = sign_row(row, key)
        return row
    return append_history(gate, path, committed, signers)


# ---------------------------------------------------------------- printing
def summary_lines(receipt, limit=15):
    t = receipt["totals"]
    out = [f"image_ownership ({receipt['report']['mode']}, {receipt['report']['path']}): "
           + ("verified" if receipt["verified"] else "NOT VERIFIED: every compiled byte is unproven")]
    for why in receipt["refusals"]:
        out.append(f"  refused: {why}")
    for why in receipt["warnings"]:
        out.append(f"  warning: {why}")
    content = receipt["content_bytes"] or 1
    out.append(f"  NOT OURS (bridged + unproven): {receipt['north_star']:,} of {receipt['content_bytes']:,} content "
               f"bytes ({100 * receipt['north_star'] / content:.2f}%)")
    out.append(f"  ours {t['ours']:,}  bridged {t['bridged']:,}  unproven {t['unproven']:,}  "
               f"filler {t['filler']:,}  linker {t['linker']:,}  (image {receipt['image_bytes']:,})")
    out.append("  ours by lane: " + ", ".join(f"{k} {v:,}" for k, v in t["ours_by_lane"].items()))
    out.append("  bridged by kind: " + ", ".join(f"{k} {v:,}" for k, v in sorted(t["bridged_by_kind"].items(),
                                                                               key=lambda kv: -kv[1])))
    out.append("  linker by kind: " + ", ".join(f"{k} {v:,}" for k, v in t["linker_by_kind"].items()))
    for g in receipt["unproven_gaps"][:limit]:
        out.append(f"  unexplained image bytes: {g['bytes']:,} in {g['section']} at {g['new_rva']}")
    out.append(f"  {'section':<14}{'ours':>12}{'bridged':>12}{'unproven':>10}{'filler':>11}{'linker':>10}")
    for name, s in receipt["sections"].items():
        out.append(f"  {name:<14}{s['ours_total']:>12,}{s['bridged_total']:>12,}{s['unproven']:>10,}"
                   f"{s['filler']:>11,}{s['linker']:>10,}")
    out.append("  bridged by class (largest):")
    flat = sorted(((v, sec, cls) for sec, d in receipt["bridged_by_class"].items() for cls, v in d.items()),
                  reverse=True)
    for v, sec, cls in flat[:limit]:
        out.append(f"    {v:>11,}  {sec:<9} {cls}")
    out.append(f"  largest bridged regions ({receipt['worklist_size']:,} in all):")
    for e in receipt["worklist"][:limit]:
        out.append(f"    {e['bytes']:>11,}  {e['section']:<9} {e['retail_rva']}  {e['class']}  {e['detail'][:90]}")
    return out


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.splitlines()[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    for name, helptext in (("report", "print who owns the image's bytes"),
                           ("worklist", "the largest bridged regions"),
                           ("record", "append the measurement to the history (refuses unless current)")):
        p = sub.add_parser(name, help=helptext)
        p.add_argument("report", nargs="?" if name != "record" else None, type=Path, default=DEFAULT_REPORT,
                       help="a boot_image / boot_relayout report (<tag>.json beside <tag>.exe)")
        p.add_argument("--image", type=Path, help="the linked image (default: the report's <tag>.exe)")
        p.add_argument("--limit", type=int, default=30)
        p.add_argument("--json", action="store_true", help="print the receipt as JSON")
        p.add_argument("--worklist-csv", type=Path, help="write every bridged region here")
        if name == "worklist":
            p.add_argument("--section", help="only this retail section (.text, .rdata, .data, ...)")
    p = sub.add_parser("check-history", help="validate the history file")
    p.add_argument("--history", type=Path, default=HISTORY)
    p.add_argument("--staged", action="store_true",
                   help="the staged history against HEAD's, signed by the publisher (pre-commit)")
    p.add_argument("--range", nargs=2, metavar=("BASE", "TIP"),
                   help="recheck each commit in the pushed range (publisher)")
    a = ap.parse_args(argv)
    if a.cmd == "check-history":
        problems = check_range(*a.range, a.history) if a.range else \
            check_staged(a.history) if a.staged else check_history(a.history)
        for x in problems:
            print(f"image_ownership: {x}")
        return 1 if problems else 0
    receipt = measure(a.report, image=a.image, worklist_limit=max(a.limit, 50) if a.cmd != "worklist" else 10 ** 9,
                      worklist_csv=a.worklist_csv)
    if a.cmd == "worklist":
        work = [e for e in receipt["worklist"] if not a.section or e["section"] == a.section]
        if a.json:
            print(json.dumps(work[:a.limit], indent=1))
        else:
            for e in work[:a.limit]:
                print(f"{e['bytes']:>11,}  {e['section']:<9} {e['retail_rva']}  {e['class']}  {e['detail'][:100]}")
        return 0
    if a.json:
        print(json.dumps(receipt, indent=1))
    else:
        print("\n".join(summary_lines(receipt, a.limit)))
    if a.cmd == "record":
        row = record(receipt)
        print(f"image_ownership: recorded {row['commit'][:10]} {row['mode']}: not ours {int(row['north_star']):,}")
    return 0 if receipt["verified"] else 1


if __name__ == "__main__":
    sys.exit(main())
