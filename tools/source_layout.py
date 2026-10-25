#!/usr/bin/env python3
"""Build original-file consolidation packets alongside the naming lanes.

Read-only with respect to game source, ledgers, the index and references. Outputs
are restricted to build/consolidation[/...] or reverse/consolidation[/...]. This
is an evidence catalogue and investigation queue, never an automatic merger.
See docs/consolidation.md for evidence grades and the merge admission steps.
"""
import argparse
import bisect
import collections
import csv
import hashlib
import io
import itertools
import json
import os
import posixpath
import re
import struct
import subprocess
import sys
from pathlib import Path

import tu_map

ROOT = Path(__file__).resolve().parents[1]
SCHEMA = 1
SOURCE_EXT = {".c", ".cpp", ".asm"}
TREE_EXT = SOURCE_EXT | {".h", ".hpp", ".inl", ".inc"}
IMAGE_DIR = "baselines/bfme2/workshop-vanilla-1.06/files"
IMAGES = {"retail": "game.dat", "worldbuilder": "worldbuilder.exe"}
PATH_PATTERN = (r"[A-Za-z]:[\\/](?:[^\x00\r\n\"<>|]*?[\\/])?Code[\\/]"
                r"[^\x00\r\n\"<>|]*?\.(?:cpp|hpp|inl|asm|h|c)\b")
IMAGE_PATH = re.compile(PATH_PATTERN, re.I)
ORIGIN_ORDER = ("retail", "worldbuilder", "zh", "bfme1-ea", "rotwk-source")
REGISTERS = (
    "reverse/flag_overrides.csv", "reverse/hatch_baseline.tsv",
    "reverse/data_check_baseline.txt", "reverse/code_identity_baseline.tsv",
    "reverse/data_ledger.csv", "reverse/body_owners.csv",
)
CONTROL_INPUTS = (
    "reverse/functions.csv", "reverse/tu_map.csv", "reverse/tu_map.inputs.sha256",
    "reverse/string_xrefs.tsv", "reverse/ghidra_functions.csv", "reverse/data_xrefs.tsv",
    "reverse/exports.csv", "reverse/wb_name_leads.csv", "reverse/data_rows.csv",
    "reverse/name_basis.csv", "reverse/canonical_classes.csv",
    "reverse/retail_inventory/flag_regions.csv", *REGISTERS,
    "tools/source_layout.py", "tools/name_lane.py", "tools/tu_map.py",
    "tools/flag_defaults.py", "tools/compiler_profiles.py", "tools/build.py",
    "tools/rename.py", "tools/name_evidence.py", "docs/naming.md",
    "docs/doxygen/sources.cfg", "baselines/bfme2/workshop-vanilla-1.06/manifest.json",
)
OUTPUTS = ("paths.csv", "retail_paths.csv", "image_paths.jsonl", "queue.csv", "groups.json", "files.jsonl",
           "data_hints.csv", "report.md")
CL = re.compile(r"^\s*//\s*cl:(.*)$", re.M)
INCLUDE = re.compile(r'^\s*#\s*include\s*"([^"\n]+)"', re.M)
TYPE = re.compile(r"\b(?:class|struct|union|enum)\s+([A-Za-z_]\w*)\b[^;{}]*\{")
DATA_MODULE = re.compile(
    r"^\s*(?:Behavior|Body|Draw|ClientBehavior|ClientUpdate|AIUpdateInterface|Physics)"
    r"\s*=\s*([A-Za-z_]\w*)\b", re.I)


def digest(data):
    return hashlib.sha256(data).hexdigest()


def decoder_identity():
    try:
        import capstone
        return "capstone:" + capstone.__version__
    except ImportError:
        return "capstone:unavailable; owner references unverified"


def canonical_path(value):
    """A Code/ path, without guessing directories or permitting path escapes."""
    value = value.replace("\\", "/")
    match = re.search(r"(?:^|/)Code/", value, re.I)
    if match:
        value = "Code/" + value[match.end():]
    elif value.startswith(("GameEngine/", "GameEngineDevice/", "Libraries/", "Tools/")):
        value = "Code/" + value
    else:
        raise ValueError(f"not an original Code/ path: {value!r}")
    parts = value.split("/")
    if any(p in ("", ".", "..") or re.search(r'[\x00-\x1f:<>"|?*]', p)
           or p.endswith((" ", "."))
           or re.fullmatch(r"(?:CON|PRN|AUX|NUL|COM[1-9]|LPT[1-9])(?:\..*)?", p, re.I)
           for p in parts):
        raise ValueError(f"unsafe Code/ path: {value!r}")
    if Path(value).suffix.lower() not in TREE_EXT:
        raise ValueError(f"not a C/C++ source or header path: {value!r}")
    return value


def git(root, *args):
    # The explicitly selected local reference can be owned by the interactive
    # user. A command-local trust setting avoids editing anyone's global config.
    result = subprocess.run(
        ["git", "-c", f"safe.directory={Path(root).as_posix()}", "-C", str(root), *args],
        capture_output=True, text=True, encoding="utf-8", errors="replace")
    return result.stdout.strip() if result.returncode == 0 else None


def files_in(root, extensions=None):
    """Stable inventory; never follow a reference's symlinks/junctions outside it."""
    root = Path(root).resolve()
    if not root.is_dir():
        return []
    found, todo = [], [root]
    while todo:
        # scandir's cached attributes avoid several Windows filesystem round
        # trips per source. No descendant symlinks or junctions are followed.
        with os.scandir(todo.pop()) as entries:
            for entry in entries:
                if entry.name == ".git" or entry.is_symlink() or getattr(entry, "is_junction", lambda: False)():
                    continue
                if entry.is_dir(follow_symlinks=False):
                    todo.append(Path(entry.path))
                elif entry.is_file(follow_symlinks=False):
                    path = Path(entry.path)
                    if extensions is None or path.suffix.lower() in extensions:
                        found.append(path)
    return sorted(found)


def csv_rows(path):
    if Path(path).is_file():
        with Path(path).open(encoding="utf-8-sig", newline="") as handle:
            yield from csv.DictReader(handle)


def csv_text(rows, columns):
    out = io.StringIO(newline="")
    writer = csv.DictWriter(out, columns, lineterminator="\n")
    writer.writeheader()
    writer.writerows(rows)
    return out.getvalue()


class Image:
    """PE section mapping and checked literal operands at instruction boundaries."""
    def __init__(self, path):
        self.data = Path(path).read_bytes()
        data = self.data
        if len(data) < 64 or data[:2] != b"MZ":
            raise ValueError(f"not a PE image: {path}")
        pe = struct.unpack_from("<I", data, 0x3c)[0]
        if data[pe:pe + 4] != b"PE\0\0":
            raise ValueError(f"not a PE image: {path}")
        if struct.unpack_from("<H", data, pe + 24)[0] != 0x10b:
            raise ValueError(f"expected a PE32 image: {path}")
        self.base = struct.unpack_from("<I", data, pe + 52)[0]
        table = pe + 24 + struct.unpack_from("<H", data, pe + 20)[0]
        self.sections = []
        for i in range(struct.unpack_from("<H", data, pe + 6)[0]):
            off = table + i * 40
            vsize, va, size, raw = struct.unpack_from("<IIII", data, off + 8)
            flags = struct.unpack_from("<I", data, off + 36)[0]
            if raw + size > len(data):
                raise ValueError(f"PE section extends beyond image: {path}")
            self.sections.append((va, min(vsize, size), raw, flags))
        self._literals = {}

    def rva(self, offset):
        for va, size, raw, _ in self.sections:
            if raw <= offset < raw + size:
                return va + offset - raw
        return None

    def literal_reference(self, rva, string_rvas):
        """Verify a PUSH imm32 or MOV r32,imm32 at the recorded code xref.

        Other instruction forms stay unverified hints. Do not search arbitrary
        neighbouring bytes for an address: that can validate the next instruction.
        """
        for va, size, raw, flags in self.sections:
            if flags & 0x20000000 and va <= rva and rva + 5 <= va + size:
                offset = raw + rva - va
                if self.data[offset] == 0x68 or 0xb8 <= self.data[offset] <= 0xbf:
                    operand = struct.unpack_from("<I", self.data, offset + 1)[0]
                    return operand - self.base in string_rvas
        return False

    def body_literals(self, rva, size):
        """Decode owner-level xrefs from this repo without borrowing a twin's extent.

        Capstone is already a repository dependency. Without it, owner-level
        xrefs cannot be promoted; an exact instruction xref can still be checked.
        """
        key = rva, size
        if key not in self._literals:
            found = []
            try:
                from capstone import Cs, CS_ARCH_X86, CS_MODE_32
            except ImportError:
                return []
            for va, section_size, raw, flags in self.sections:
                if flags & 0x20000000 and va <= rva and rva + size <= va + section_size:
                    data = self.data[raw + rva - va:raw + rva - va + size]
                    for insn in Cs(CS_ARCH_X86, CS_MODE_32).disasm(data, rva):
                        if len(insn.bytes) == 5 and (insn.bytes[0] == 0x68 or 0xb8 <= insn.bytes[0] <= 0xbf):
                            found.append((insn.address, struct.unpack_from("<I", insn.bytes, 1)[0] - self.base))
            self._literals[key] = found
        return self._literals[key]

    def paths(self, origin):
        text = self.data.decode("latin1")
        hits = [(m.start(), "ascii", m.group()) for m in IMAGE_PATH.finditer(text)]
        for run in re.finditer(rb"(?:[\x20-\x7e]\x00){8,}", self.data):
            for match in IMAGE_PATH.finditer(run.group().decode("utf-16le")):
                hits.append((run.start() + 2 * match.start(), "utf-16le", match.group()))
        out = []
        for offset, encoding, raw_path in sorted(hits):
            try:
                path = canonical_path(raw_path)
            except ValueError:
                continue
            rva = self.rva(offset)
            out.append(dict(origin=origin, path=path, raw_path=raw_path, encoding=encoding,
                            offset=f"0x{offset:08X}", string_rva=f"0x{rva:08X}" if rva is not None else ""))
        return out


class Catalogue:
    def __init__(self):
        self.entries = {}

    def add(self, path, origin, citation):
        path = canonical_path(path)
        item = self.entries.setdefault(path.casefold(), {"variants": collections.defaultdict(set),
                                                        "citations": collections.defaultdict(set)})
        item["variants"][origin].add(path)
        item["citations"][origin].add(citation)

    def spelling(self, path):
        item = self.entries.get(path.casefold())
        if item:
            return next(sorted(item["variants"][k])[0] for k in ORIGIN_ORDER if item["variants"].get(k))
        return canonical_path(path)

    def rows(self, existing, bfme1_files):
        for key, item in sorted(self.entries.items()):
            path = self.spelling(key)
            yield dict(path=path, kind=Path(path).suffix.lower().lstrip("."),
                       origins=";".join(k for k in ORIGIN_ORDER if item["citations"].get(k)),
                       case_variants=json.dumps(sorted({v for vs in item["variants"].values() for v in vs})),
                       target_case_conflict=str(len(item["variants"].get("retail", ())) > 1).lower(),
                       bfme2_file=existing.get(key, ""), bfme1_reconstructed=bfme1_files.get(key, ""),
                       **{k.replace("-", "_") + "_evidence": json.dumps(sorted(item["citations"].get(k, ())))
                          for k in ORIGIN_ORDER})


def choose_layout(base, choices):
    """Resolve an actual reference layout; missing layouts stay explicitly missing."""
    return next((Path(base) / c for c in choices if (Path(base) / c).is_dir()), None)


def donor_index(zh, bfme1, cat):
    methods = collections.defaultdict(set)
    bfme_methods = collections.defaultdict(set)
    if zh:
        for path in files_in(zh, TREE_EXT):
            rel = "Code/" + path.relative_to(zh).as_posix()
            cat.add(rel, "zh", path.relative_to(zh).as_posix())
            if path.suffix.lower() == ".cpp":
                for cls, method in tu_map.zh_definitions(path.read_text(encoding="utf-8", errors="replace")):
                    methods[(cls, method)].add(rel)
    ea = Path(bfme1) / "targets/game/reverse/ea_evidence.csv"
    # Do not transfer BFME 1 RVAs to BFME 2. Join its own name/file records
    # first, then offer same-name structural hints to BFME 2.
    at = collections.defaultdict(lambda: {"files": set(), "names": set()})
    for line, row in enumerate(csv_rows(ea), 2):
        if row.get("kind") == "file":
            try:
                rel = canonical_path(row["value"])
            except ValueError:
                continue
            cat.add(rel, "bfme1-ea", f"ea_evidence.csv:{line} route={row.get('route', '')}")
            if row.get("route") in ("wb1", "zh"):
                at[row["rva"]]["files"].add(rel)
        elif row.get("kind") == "name" and row.get("basis") in ("strong", "aligned"):
            at[row["rva"]]["names"].add(row["value"])
    for evidence in at.values():
        for name in evidence["names"]:
            bfme_methods[name].update(evidence["files"])
    return methods, bfme_methods


def rotwk_hints(base, cat):
    modules = collections.defaultdict(list)
    counts = collections.Counter()
    for path in files_in(base) if base else ():
        counts[path.suffix.lower()] += 1
        rel = path.relative_to(base).as_posix()
        if path.suffix.lower() in SOURCE_EXT | {".h", ".hpp"}:
            try:
                code = canonical_path(rel)
            except ValueError:
                pass
            else:
                cat.add(code, "rotwk-source", rel)
        if path.suffix.lower() in (".ini", ".inc"):
            for line, text in enumerate(path.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
                match = DATA_MODULE.match(text)
                if match:
                    modules[match.group(1)].append(f"{rel}:{line}")
    hints = [dict(token=token, occurrences=len(refs), examples=json.dumps(refs[:5]),
                  strength="data-vocabulary-only") for token, refs in sorted(modules.items())]
    return dict(sorted(counts.items())), hints


def ledger_projection(root, under="Code/"):
    """Stream a narrow active-source projection, never materialise the ledger."""
    by_file = collections.defaultdict(list)
    for row in csv_rows(root / "reverse/functions.csv"):
        source = row.get("source", "")
        if (row.get("status") != "matched" or not source.startswith(under)
                or not source.startswith(("Code/GameEngine/", "Code/GameEngineDevice/", "Code/Libraries/"))
                or Path(source).suffix.lower() not in SOURCE_EXT):
            continue
        canonical_path(source)  # reject unsafe ledger paths before reading source
        try:
            rva, size = int(row["target_rva"], 16), int(row["target_size"], 0)
        except ValueError:
            continue
        if size > 0:
            by_file[source].append(dict(rva=rva, size=size, name=row["name"], notes=row.get("notes", "")))
    return dict(by_file)


def direct_references(root, image, paths, rows):
    by_raw = collections.defaultdict(set)
    path_spelling = {}
    for item in paths:
        if item["origin"] == "retail" and item["string_rva"] and Path(item["path"]).suffix.lower() in (".cpp", ".c"):
            by_raw[item["raw_path"]].add(int(item["string_rva"], 16))
            path_spelling[item["raw_path"]] = item["path"]
    spans = collections.defaultdict(set)
    for members in rows.values():
        for row in members:
            spans[row["rva"]].add(row["size"])
    starts = sorted(spans)
    ends = [s + max(spans[s]) for s in starts]
    reach = list(itertools.accumulate(ends, max))
    out = collections.defaultdict(set)
    if not image or not (root / "reverse/string_xrefs.tsv").is_file():
        return out
    with (root / "reverse/string_xrefs.tsv").open(encoding="utf-8") as handle:
        for line in handle:
            text, _, refs = line.rstrip("\r\n").rpartition("\t")
            if text not in by_raw:
                continue
            for ref in refs.split(","):
                try:
                    ref = int(ref, 16)
                except ValueError:
                    continue
                i = bisect.bisect_right(starts, ref) - 1
                while i >= 0 and reach[i] > ref:
                    for size in spans[starts[i]]:
                        if starts[i] <= ref < starts[i] + size:
                            if ref == starts[i]:
                                # list_string_xrefs.java records the OWNER's
                                # entry, rather than the referring instruction.
                                refs_in_body = [address for address, operand in image.body_literals(starts[i], size)
                                                if operand in by_raw[text]]
                            else:
                                refs_in_body = [ref] if image.literal_reference(ref, by_raw[text]) else []
                            for instruction in refs_in_body:
                                out[(starts[i], size)].add((path_spelling[text], instruction))
                    i -= 1
    return out


def map_index(root):
    # tu_map is already a derived map, not a second copy of functions.csv.
    mapping = collections.defaultdict(list)
    for row in csv_rows(root / "reverse/tu_map.csv"):
        if row.get("kind", "").startswith("code"):
            mapping[int(row["rva"], 16)].append(row)
    return mapping


def row_route(row, direct, mapping, fresh, zh, bfme1, wb, cat):
    rva = row["rva"]
    references = direct.get((rva, row.get("size", 0)), ())
    facts, hints = {path for path, _ in references}, set()
    evidence = [f"retail-path-reference: instruction=0x{address:08X} path={path}; literal operand verified"
                for path, address in sorted(references)]
    for item in mapping.get(rva, ()):
        own_anchors = tu_map.anchors(item.get("evidence", ""))
        approved = tu_map.approved_tu(mapping, item) if fresh else None
        if approved:
            facts.add(approved)
            evidence.append("approved-tu-map: " + item["evidence"])
        elif item.get("tu") and (item["tu"].casefold() in cat.entries
                                  or any(tu_map.same(item["tu"], own_anchors.get(k)) for k in "FZS")):
            # An unapproved/stale N/K/C guess must not create an invented
            # original filename and more fragmentation. Retain real anchors.
            hints.add(item["tu"])
            evidence.append(("stale-tu-map: " if not fresh else "proposed-tu-map: ") + item["evidence"])
        own = own_anchors.get("F")
        if own and not approved:
            hints.add(own)
    cls, method = tu_map.demangle(row["name"])
    hints.update(zh.get((cls, method), ()))
    hints.update(bfme1.get(f"{cls}::{method}", ()))
    hints.update(wb.get(rva, ()))
    if zh.get((cls, method)):
        evidence.append("zh-definition: same spelling; target identity unproven")
    if bfme1.get(f"{cls}::{method}"):
        evidence.append("bfme1-ea: same spelling; no cross-game RVA transfer")
    if wb.get(rva):
        evidence.append("worldbuilder-pair: identity/file hint; not a verified target TU")
    def valid(values):
        out = set()
        for value in values:
            try:
                path = cat.spelling(canonical_path(value))
            except ValueError:
                continue
            if Path(path).suffix.lower() in (".cpp", ".c", ".asm"):
                out.add(path)
        return out
    facts, hints = valid(facts), valid(hints)
    picks = facts or hints
    return dict(target=next(iter(picks)) if len(picks) == 1 else "",
                strength="target" if facts else "hint" if hints else "unresolved",
                alternatives=sorted(facts | hints), conflict=len(picks) > 1, evidence=evidence)


def source_info(root, source, rows, registers):
    path = root / source
    if not path.is_file() or path.is_symlink() or not path.resolve().is_relative_to(root):
        return dict(source=source, blockers=["missing-or-redirected-source"], flags=[], types=[], includes=[], sha256="")
    raw = path.read_bytes()
    text = raw.decode("utf-8", errors="replace")
    code = tu_map.CPP_NOISE.sub(tu_map._blank, text)
    blockers = []
    if re.search(r"\b(?:__asm|__emit)\b|__declspec\s*\(\s*naked\s*\)", code):
        blockers.append("assembly-or-lift: convert or separately justify before merging")
    if re.search(r"\b(?:__FILE__|__LINE__|__COUNTER__)\b|^\s*#\s*line\b", code, re.M):
        blockers.append("path-or-line-sensitive")
    if re.search(r"^\s*#\s*(?:define|undef|pragma)\b", code, re.M):
        blockers.append("macro-or-pragma-context")
    if re.search(r"\bstatic\b|\bnamespace\s*\{", code):
        blockers.append("internal-linkage-review")
    # Preserve quoted operands while removing comments, including commented-out
    # includes that would otherwise produce spurious dependency blockers.
    uncommented = tu_map.CPP_NOISE.sub(lambda m: tu_map._blank(m) if m.group().startswith("/") else m.group(), text)
    includes = INCLUDE.findall(uncommented)
    if includes:
        blockers.append("quoted-include-resolution-review")
    if any(Path(inc).suffix.lower() in SOURCE_EXT for inc in includes):
        blockers.append("includes-implementation-source")
    if registers.get(source.casefold()):
        blockers.append("path-keyed-registers: " + ", ".join(sorted(registers[source.casefold()])))
    if any("vendored=" in r["notes"] or ".lib" in r["notes"] for r in rows):
        blockers.append("vendored-or-library-identity: preserve upstream organisation")
    if re.search(r"\b(?:present-unmatched|absent-from-retail)\b", text):
        blockers.append("unledgered-definitions: retain and reconcile declarations before draining source")
    return dict(source=source, blockers=blockers, flags=CL.findall(text),
                types=sorted(set(TYPE.findall(code))), includes=includes, sha256=digest(raw))


def interval_bytes(rows):
    total, end = 0, -1
    for lo, hi in sorted((r["rva"], r["rva"] + r["size"]) for r in rows):
        total += max(0, hi - max(lo, end))
        end = max(end, hi)
    return total


def plan(root, under, cat, image, image_paths, zh, bfme1, fresh):
    rows = ledger_projection(root, under)
    direct = direct_references(root, image, image_paths, rows)
    mapping = map_index(root)
    wb = collections.defaultdict(set)
    active_rvas = {r["rva"] for members in rows.values() for r in members}
    exports = collections.defaultdict(set)
    for row in csv_rows(root / "reverse/exports.csv"):
        try:
            rva = int(row.get("target_rva") or row.get("rva"), 16)
        except (ValueError, TypeError):
            continue
        if rva in active_rvas:
            exports[rva].add(row["name"])
    for row in csv_rows(root / "reverse/wb_name_leads.csv"):
        try:
            rva = int(row["target_rva"], 16)
            path = canonical_path(row["wb_file"])
        except (ValueError, KeyError):
            continue
        if rva in active_rvas:
            wb[rva].add(path)
    registers = collections.defaultdict(set)
    for rel in REGISTERS:
        if (root / rel).is_file():
            for line in (root / rel).read_text(encoding="utf-8", errors="replace").splitlines():
                for match in re.finditer(r'Code/[^\s,;\t"<>]+', line):
                    registers[match.group().casefold()].add(rel)
    regions = []
    for region in csv_rows(root / "reverse/retail_inventory/flag_regions.csv"):
        regions.append((int(region["rva_start"], 16), int(region["rva_end"], 16),
                        (region["opt"], region["arch"], region["tune"])))
    source_paths = files_in(root / "Code", TREE_EXT)
    existing = {"Code/" + p.relative_to(root / "Code").as_posix() for p in source_paths}
    case_index = {s.casefold(): s for s in existing}
    parts_index = collections.defaultdict(set)
    for source in existing:
        parts = source.split("/")
        for i in range(1, len(parts) + 1):
            part = "/".join(parts[:i])
            parts_index[part.casefold()].add(part)
    data_rows = collections.defaultdict(list)
    for row in csv_rows(root / "reverse/data_rows.csv"):
        if row.get("source") in rows:
            data_rows[row["source"]].append({key: row.get(key, "") for key in ("name", "address", "address_kind", "status")})
    infos, queue, members_by_target = {}, [], collections.defaultdict(set)
    for source, members in sorted(rows.items()):
        info = source_info(root, source, members, registers)
        infos[source] = info
        routes = []
        parents = {r["name"] for r in members if not r["name"].startswith(("__ehhandler$", "__unwindfunclet$"))}
        for row in members:
            if row["name"].startswith(("__ehhandler$", "__unwindfunclet$")):
                parent = re.search(r"(?:^|\s)parent=([^\s]+)", row["notes"])
                if parent and parent.group(1) in parents:
                    continue  # travels with its proven parent, never creates a home
            route = row_route(row, direct, mapping, fresh, zh, bfme1, wb, cat)
            route.update(rva=f"0x{row['rva']:08X}", name=row["name"])
            routes.append(route)
        targets = {r["target"] for r in routes if r["target"]}
        complete = bool(routes) and all(r["target"] for r in routes) and len(targets) == 1
        info.update(routes=routes, complete=complete)
        for target in targets:
            members_by_target[target].add(source)
        queue.append(dict(source=source, target=next(iter(targets)) if complete else "",
                          state="whole-file-candidate" if complete else "mixed-or-incomplete" if targets else "unresolved",
                          rows=len(members), unique_bytes=interval_bytes(members),
                          target_rows=sum(r["strength"] == "target" for r in routes),
                          hint_rows=sum(r["strength"] == "hint" for r in routes),
                          unrouted_rows=sum(not r["target"] for r in routes),
                          candidates=json.dumps(sorted(targets)),
                          export_names=sum(bool(exports.get(r["rva"])) for r in members),
                          blockers=json.dumps(info["blockers"])))
    includers = collections.defaultdict(set)
    for path in source_paths:
        source = "Code/" + path.relative_to(root / "Code").as_posix()
        if source in infos:
            includes = infos[source]["includes"]
        else:
            text = path.read_text(encoding="utf-8", errors="replace")
            uncommented = tu_map.CPP_NOISE.sub(lambda m: tu_map._blank(m) if m.group().startswith("/") else m.group(), text)
            includes = INCLUDE.findall(uncommented)
        for inc in includes:
            if Path(inc).suffix.lower() not in SOURCE_EXT:
                continue
            relative = posixpath.normpath(posixpath.join(posixpath.dirname(source), inc.replace("\\", "/")))
            for candidate in (relative, inc.replace("\\", "/")):
                target = case_index.get(candidate.casefold())
                if target:
                    includers[target].add(source)
    groups = []
    for target, donors in sorted(members_by_target.items()):
        resident = case_index.get(target.casefold())
        files = set(donors)
        if resident:
            files.add(resident)
        if files == {target}:
            continue
        blockers, types, flags, region_flags = [], collections.Counter(), set(), set()
        details = []
        for source in sorted(files):
            info = infos.get(source)
            if info is None:
                # A resident outside --under is never silently treated as empty.
                blockers.append("destination-not-in-selected-active-ledger: review unledgered definitions and data")
                info = source_info(root, source, [], registers)
                info.update(complete=False, routes=[])
                infos[source] = info
            blockers.extend(f"{source}: {b}" for b in info["blockers"])
            if includers.get(source):
                blockers.append(f"{source}: included-by: " + ", ".join(sorted(includers[source])))
            if data_rows.get(source):
                blockers.append(f"{source}: data-ownership-review: {len(data_rows[source])} ledger rows")
            if not info["complete"] or any(r["target"] != target for r in info["routes"]):
                blockers.append(f"{source}: mixed-or-incomplete-routing; split/review every row first")
            if any(r["strength"] != "target" for r in info["routes"]):
                blockers.append(f"{source}: placement-needs-target-corroboration")
            types.update(info["types"])
            flags.add(tuple(info["flags"]))
            for row in rows.get(source, ()):
                region_flags.update(tuple(v) for lo, hi, v in regions if lo <= row["rva"] <= hi)
            details.append(dict(source=source, sha256=info["sha256"], rows=len(rows.get(source, ())),
                                complete=info["complete"], packet_key=source))
        duplicates = sorted(t for t, n in types.items() if n > 1)
        if duplicates:
            blockers.append("duplicate-type-definitions: " + ", ".join(duplicates))
        if len(flags) > 1 or len(region_flags) > 1:
            blockers.append("compiler-settings-disagree: reconcile cl lines, region flags and overrides")
        for i in range(1, len(target.split("/")) + 1):
            part = "/".join(target.split("/")[:i])
            if parts_index.get(part.casefold(), {part}) != {part}:
                blockers.append("case-spelling-conflict: " + part)
        item = cat.entries.get(target.casefold(), {})
        if len(item.get("variants", {}).get("retail", ())) > 1:
            blockers.append("retail-path-case-conflict")
        if Path(target).suffix.lower() == ".c" and any(Path(s).suffix.lower() != ".c" for s in files):
            blockers.append("language-mode-change: C and C++ cannot be concatenated blindly")
        if not fresh and any(any(e.startswith("stale-tu-map:") for e in r["evidence"])
                             for source in files for r in infos.get(source, {}).get("routes", ())):
            blockers.append("stale-tu-map: regenerate and recheck before using map assignments")
        all_rows = [r for s in files for r in rows.get(s, ())]
        groups.append(dict(target=target, stage="investigate" if blockers else "compile-trial-required",
                           file_count=len(files), potential_file_reduction=max(0, len(files) - 1),
                           unique_bytes=interval_bytes(all_rows), verified=False,
                           blockers=sorted(set(blockers)), files=details,
                           next_checks=[ ["python3", "tools/name_evidence.py"],
                                         ["python3", "tools/class_views.py", "--class", "<owner>"],
                                         ["python3", "tools/find_declared_unmatched.py", *sorted(files)] ]))
    groups.sort(key=lambda g: (g["potential_file_reduction"] == 0,
                               g["stage"] != "compile-trial-required", len(g["blockers"]),
                               -g["potential_file_reduction"], -g["unique_bytes"], g["target"]))
    packets = [dict(source=source, sha256=info["sha256"], cl_lines=info["flags"],
                    blockers=info["blockers"], included_by=sorted(includers.get(source, ())),
                    scope="selected-active-ledger" if source in rows else "outside-selected-active-ledger",
                    complete=info["complete"], placement_evidence=info["routes"],
                    data_rows=data_rows.get(source, []),
                    rows=[dict(rva=f"0x{r['rva']:08X}", size=r["size"], name=r["name"], notes=r["notes"])
                          for r in rows.get(source, ())]) for source, info in sorted(infos.items())]
    return queue, groups, case_index, packets


def input_spec(root, bfme1, zh, bfme_game, rotwk):
    specs = [{"path": str((root / p).resolve()), "kind": "file"} for p in CONTROL_INPUTS]
    specs += [{"path": str(root / IMAGE_DIR / name), "kind": "file"} for name in IMAGES.values()]
    specs += [{"path": str(root / "Code"), "kind": "code-tree"},
              {"path": str(Path(bfme1) / "targets/game/reverse/ea_evidence.csv"), "kind": "file"}]
    for path, kind in ((zh, "code-tree"), (bfme_game, "path-tree"), (rotwk, "rotwk-tree")):
        if path:
            specs.append({"path": str(Path(path).resolve()), "kind": kind})
    return specs


def fingerprint(spec):
    path = Path(spec["path"])
    if spec["kind"] == "file":
        return digest(path.read_bytes()) if path.is_file() else "missing"
    if not path.is_dir():
        return "missing"
    sha = hashlib.sha256()
    for file in files_in(path, TREE_EXT if spec["kind"] in ("code-tree", "path-tree") else None):
        sha.update(file.relative_to(path).as_posix().encode("utf-8") + b"\0")
        if spec["kind"] != "path-tree" and (spec["kind"] != "rotwk-tree"
                                             or file.suffix.lower() in TREE_EXT | {".ini"}):
            sha.update(hashlib.sha256(file.read_bytes()).digest())
    return sha.hexdigest()


def output_dir(root, value):
    raw = Path(value)
    out = (root / raw).resolve() if not raw.is_absolute() else raw.resolve()
    allowed = [root / "build/consolidation", root / "reverse/consolidation"]
    if not any(out.is_relative_to(base) for base in allowed):
        raise ValueError("output must be inside build/consolidation/ or reverse/consolidation/")
    # Check resolved bases too: a junction named consolidation must not redirect writes.
    if not out.is_relative_to(root.resolve()):
        raise ValueError("output escapes the workspace through a symlink/junction")
    for name in (*OUTPUTS, "inputs.json"):
        if (out / name).is_symlink() or not (out / name).resolve().is_relative_to(out):
            raise ValueError("output artifact redirects outside its report directory")
    return out


def check_snapshot(root, directory):
    out = output_dir(root, directory)
    manifest = json.loads((out / "inputs.json").read_text(encoding="utf-8"))
    if manifest.get("schema") != SCHEMA:
        raise ValueError("unsupported consolidation snapshot schema")
    if set(manifest.get("outputs", ())) != set(OUTPUTS):
        raise ValueError("incomplete snapshot output manifest")
    if not isinstance(manifest.get("inputs"), list) or not isinstance(manifest.get("references"), dict):
        raise ValueError("incomplete snapshot input manifest")
    stale = []
    refs = manifest["references"]
    if not isinstance(refs.get("bfme1"), dict) or not refs["bfme1"].get("path"):
        raise ValueError("missing BFME 1 reference identity")
    expected = input_spec(root, refs["bfme1"]["path"], refs.get("zh"),
                          choose_layout(refs["bfme1"]["path"], ("game", "Code")), refs.get("rotwk"))
    if {(s["path"], s["kind"]) for s in expected} != {(s["path"], s["kind"]) for s in manifest["inputs"]}:
        raise ValueError("incomplete or changed snapshot input coverage; regenerate")
    if manifest.get("decoder") != decoder_identity():
        stale.append("instruction decoder identity")
    for spec in manifest["inputs"]:
        if fingerprint(spec) != spec["sha256"]:
            stale.append(spec["path"])
    for name, expected in manifest["outputs"].items():
        if name not in OUTPUTS:
            raise ValueError("unexpected snapshot output name")
        if not (out / name).is_file() or digest((out / name).read_bytes()) != expected:
            stale.append(name)
    bfme1 = manifest["references"]["bfme1"]
    if git(bfme1["path"], "rev-parse", "HEAD") != bfme1["checkout"]:
        stale.append("BFME 1 checkout revision")
    if git(root, "ls-tree", "HEAD", "reference/open-bfme-1") != bfme1["superproject_gitlink"]:
        stale.append("BFME 1 superproject gitlink")
    if stale:
        print("STALE consolidation snapshot:\n" + "\n".join(stale))
        return 1
    print("Consolidation snapshot inputs and outputs agree; no code or merge verification is implied.")
    return 0


def report(summary, groups, stale, counts):
    text = ["# Consolidation evidence and work queue", "", "No source, ledger, git index or reference was changed. No merge is verified.", "",
            f"Retail original .cpp paths: **{summary['retail_cpp_paths']}**; header paths: **{summary['retail_header_paths']}**.",
            f"WorldBuilder original paths: **{summary['worldbuilder_paths']}** after case folding (editor and game paths are not interchangeable).",
            f"Catalogue: {summary['catalogue_paths']} paths; active source files surveyed: {summary['source_files']}.",
            f"Verified retail path references in selected rows: {summary['retail_routed_rows']}; decoder: {summary['decoder']}.",
            f"Investigation groups: {len(groups)}; static checks clear in {summary['compile_trial_groups']} groups, each still needs a compiler trial.",
            f"TU map freshness: {'current' if not stale else 'STALE: ' + ', '.join(stale)}.", "",
            "The catalogue preserves raw path occurrences, offsets and string RVAs in image_paths.jsonl; retail_paths.csv lists the retail subset.",
            "Target literal operands are checked before using string_xrefs.tsv to route a body.",
            "ZH definitions, BFME 1 EA file/name pairs and WorldBuilder pairings supply hints. Names and ABI still need BFME 2 proof.",
            "Potential file reductions are upper bounds; mixed files can appear in several investigation groups. Do not sum them.", "",
            "## ROTWK reference", "",
            f"File extensions: `{json.dumps(counts, sort_keys=True)}`.",
            "INI module tokens are vocabulary hints only; map and asset files are not linker/source evidence.", "",
            "## First investigation packets", "", "| Destination | Files | Static blockers |", "|---|---:|---:|"]
    text += [f"| `{g['target']}` | {g['file_count']} | {len(g['blockers'])} |" for g in groups[:20]]
    text += ["", "See groups.json and its files.jsonl packets for exact sources, row identities, evidence, hashes and blockers; queue.csv includes unresolved files.",
             "Before execution, recheck inputs.json, settle routing and class contracts, and run the ordinary byte, EH, data, ownership and link checks.",
             "Use rename.py for proven or agreed identifier changes. This planner grants no canonical name basis and applies nothing.", ""]
    text += ["Before pushing, audit affected tooling once across all path changes in the outgoing batch; see docs/consolidation.md.", ""]
    return "\n".join(text)


def configure_parser(parser):
    parser.add_argument("--out", default="build/consolidation", help="isolated report output directory")
    parser.add_argument("--check", metavar="DIRECTORY", help="check a previous snapshot; writes nothing")
    parser.add_argument("--bfme1", help="BFME 1 checkout; default reference/open-bfme-1")
    parser.add_argument("--zh", help="explicit GeneralsMD/Code reference tree")
    parser.add_argument("--rotwk", help="optional ROTWK source/data folder; never required on other machines")
    parser.add_argument("--under", default="Code/", help="active BFME 2 source prefix to survey")


def run(args, root=ROOT):
    root = Path(root).resolve()
    if args.check:
        return check_snapshot(root, args.check)
    out = output_dir(root, args.out)
    if not args.under.startswith("Code/") or ".." in args.under.split("/"):
        raise ValueError("--under must be a Code/ source prefix")
    bfme1 = Path(args.bfme1).resolve() if args.bfme1 else root / "reference/open-bfme-1"
    bfme_game = choose_layout(bfme1, ("game", "Code"))
    zh = Path(args.zh).resolve() if args.zh else choose_layout(
        bfme1, ("inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code",
                "reference/CnC_Generals_Zero_Hour/GeneralsMD/Code"))
    if args.zh and (not zh.is_dir() or not (zh / "GameEngine").is_dir()):
        raise ValueError("--zh must hold the Zero Hour GeneralsMD/Code tree with GameEngine/")
    rotwk = Path(args.rotwk).resolve() if args.rotwk else None
    if rotwk and not rotwk.is_dir():
        raise ValueError("--rotwk directory does not exist")
    if not (root / IMAGE_DIR / "game.dat").is_file() or not (root / "reverse/functions.csv").is_file():
        raise ValueError("retail game.dat and reverse/functions.csv are required; no empty-success scan")
    baseline_manifest = root / "baselines/bfme2/workshop-vanilla-1.06/manifest.json"
    if not baseline_manifest.is_file():
        raise ValueError("baseline manifest is required before treating image paths as target evidence")
    declared_images = {entry["path"]: entry for entry in json.loads(baseline_manifest.read_text(encoding="utf-8"))["files"]}
    specs = input_spec(root, bfme1, zh, bfme_game, rotwk)
    reference_state = dict(path=str(bfme1), checkout=git(bfme1, "rev-parse", "HEAD"),
                           superproject_gitlink=git(root, "ls-tree", "HEAD", "reference/open-bfme-1"),
                           status=git(bfme1, "status", "--short"))
    print("Fingerprinting selected sources and reference inputs...", flush=True)
    for spec in specs:
        spec["sha256"] = fingerprint(spec)
    cat, images, occurrences = Catalogue(), {}, []
    for origin, name in IMAGES.items():
        path = root / IMAGE_DIR / name
        if path.is_file():
            images[origin] = Image(path)
            declared = declared_images.get("files/" + name)
            if not declared or declared.get("sha256", "").lower() != digest(images[origin].data) or declared.get("size") != len(images[origin].data):
                raise ValueError(f"{name} does not match the declared baseline size and SHA-256")
            for item in images[origin].paths(origin):
                occurrences.append(item)
                cat.add(item["path"], origin, f"{name}:offset={item['offset']} rva={item['string_rva']}")
    print(f"Catalogued {len(occurrences)} original image-path occurrences; indexing donor structure...", flush=True)
    zh_methods, bfme_methods = donor_index(zh, bfme1, cat)
    counts, hints = rotwk_hints(rotwk, cat)
    layout = tu_map.Layout(root, zh=zh)
    stale = tu_map.check_fresh(layout)
    print("Building consolidation investigation packets...", flush=True)
    queue, groups, existing, packets = plan(root, args.under, cat, images.get("retail"), occurrences,
                                            zh_methods, bfme_methods, not stale)
    bfme_files = {("Code/" + p.relative_to(bfme_game).as_posix()).casefold(): p.relative_to(bfme1).as_posix()
                  for p in files_in(bfme_game, TREE_EXT)} if bfme_game else {}
    paths = list(cat.rows(existing, bfme_files))
    summary = dict(retail_cpp_paths=len({i["path"] for i in occurrences if i["origin"] == "retail" and i["path"].lower().endswith(".cpp")}),
                   retail_header_paths=len({i["path"] for i in occurrences if i["origin"] == "retail" and Path(i["path"]).suffix.lower() in (".h", ".hpp")}),
                   worldbuilder_paths=len({i["path"].casefold() for i in occurrences if i["origin"] == "worldbuilder"}),
                   catalogue_paths=len(paths), source_files=len(queue),
                   compile_trial_groups=sum(not g["blockers"] for g in groups),
                   unresolved_files=sum(q["state"] == "unresolved" for q in queue), groups=len(groups),
                   retail_routed_rows=sum(q["target_rows"] for q in queue), decoder=decoder_identity())
    summary["missing_inputs"] = [spec["path"] for spec in specs if spec["sha256"] == "missing"]
    retail_sha = digest(images["retail"].data)
    payloads = {
        "paths.csv": csv_text(paths, ("path", "kind", "origins", "case_variants", "target_case_conflict", "bfme2_file", "bfme1_reconstructed",
                                     *(k.replace("-", "_") + "_evidence" for k in ORIGIN_ORDER))),
        "image_paths.jsonl": "".join(json.dumps(i, sort_keys=True) + "\n" for i in occurrences),
        "retail_paths.csv": csv_text([dict(i, image_sha256=retail_sha)
                                      for i in occurrences if i["origin"] == "retail"],
                                     ("origin", "path", "raw_path", "encoding", "offset", "string_rva", "image_sha256")),
        "queue.csv": csv_text(queue, ("source", "target", "state", "rows", "unique_bytes", "target_rows", "hint_rows",
                                     "unrouted_rows", "candidates", "export_names", "blockers")),
        "groups.json": json.dumps(groups, indent=2, sort_keys=True) + "\n",
        "files.jsonl": "".join(json.dumps(p, sort_keys=True) + "\n" for p in packets),
        "data_hints.csv": csv_text(hints, ("token", "occurrences", "examples", "strength")),
        "report.md": report(summary, groups, stale, counts),
    }
    # A concurrent source/ledger/donor edit invalidates the entire observation.
    print("Rechecking input currency before writing the snapshot...", flush=True)
    moved = [spec["path"] for spec in specs if fingerprint(spec) != spec["sha256"]]
    if git(bfme1, "rev-parse", "HEAD") != reference_state["checkout"]:
        moved.append("BFME 1 checkout revision")
    if moved:
        raise ValueError("inputs changed during the scan; no snapshot written: " + ", ".join(moved))
    manifest = dict(schema=SCHEMA, inputs=specs, summary=summary, under=args.under, decoder=decoder_identity(),
                    tu_map_stale=stale, references=dict(bfme1=reference_state, zh=str(zh) if zh else None,
                        rotwk=str(rotwk) if rotwk else None),
                    outputs={name: digest(text.encode("utf-8")) for name, text in payloads.items()})
    out.mkdir(parents=True, exist_ok=True)
    for name, text in {**payloads, "inputs.json": json.dumps(manifest, indent=2, sort_keys=True) + "\n"}.items():
        # Manifest is replaced last. An interrupted publication fails --check.
        temp = out / (name + f".{os.getpid()}.tmp")
        with temp.open("x", encoding="utf-8", newline="\n") as handle:
            handle.write(text)
        os.replace(temp, out / name)
    print(json.dumps(summary, sort_keys=True))
    print(f"Consolidation report written to {out}; no source/ledger edits, staging, commits or pushes.")
    return 0


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__)
    configure_parser(parser)
    try:
        return run(parser.parse_args(argv))
    except (ValueError, OSError, struct.error) as exc:
        parser.exit(2, f"source-layout: {exc}\n")


if __name__ == "__main__":
    sys.exit(main())
