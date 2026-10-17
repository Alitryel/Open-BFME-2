#!/usr/bin/env python3
"""Curated RE metadata: a Git-tracked overlay replayed into private Ghidra projects.

Called by tools/ghidra_refdb.py (`metadata-validate`, `metadata-export`,
`metadata-plan`, `metadata-apply`, `metadata-compare`, `metadata-rebuild`, and the
bound `sync-plan`/`sync-apply` path); docs/re_metadata.md is the user manual.

Three roles, with explicit authority:
  * the package (reverse/re_metadata/<target>/: manifest, one JSON record per
    function entry, type references, managed comment segments) states accepted
    facts and their provenance; the ledgers and reverse/class_contracts/ stay the
    authority for identity and class layout, and the package only points at them;
  * a Ghidra project is private working state, rebuilt from the executable and
    the manifest's recipe and mutated only through a validated plan;
  * the SQLite refdb (tools/ghidra_refdb.py) stays a derived read index.

A plan is computed against one program's actual state, binds every digest it
relied on, and is replayed by tools/ghidra/apply_metadata.java, which rechecks
target, preconditions and name evidence itself and rolls back the whole batch on
any failure. Canonical JSON (sorted keys, compact, UTF-8, integers only) is the
one serialization every digest uses; the Java side reproduces it byte for byte.
"""
import contextlib
import csv
import hashlib
import json
import os
import re
import shutil
import struct
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import class_contract  # noqa: E402
import ghidra_refdb  # noqa: E402

SCHEMA = "re-metadata/1"
PLAN_SCHEMA = "re-metadata-plan/1"
OBSERVATION_SCHEMA = "re-metadata-observation/1"
RECEIPT_SCHEMA = "re-metadata-receipt/1"
TYPE_ROOT = "/ReMetadata"
SCRIPTS = ROOT / "tools" / "ghidra"
TOOLS = ("tools/re_metadata.py", "tools/ghidra_refdb.py", "tools/ghidra/export_metadata.java",
         "tools/ghidra/apply_metadata.java")
RVA = re.compile(r"0x[0-9a-f]{8}\Z")
SEGMENT_ID = re.compile(r"[A-Za-z0-9_.-]{1,64}\Z")
ORIGINS = ("target", "donor", "analysis")
STATUSES = ("observation", "hypothesis", "supported")
REVIEWS = ("proposed", "accepted", "rejected")
COMMENT_KINDS = ("plate", "pre", "post", "eol", "repeatable")
CONVENTIONS = ("__cdecl", "__stdcall", "__thiscall")
PRIM_SIZE = {"void": 0, "bool8": 1, "char8": 1, "wchar16": 2, "i8": 1, "u8": 1, "i16": 2, "u16": 2,
             "i32": 4, "u32": 4, "i64": 8, "u64": 8, "f32": 4, "f64": 8}
# class_contract.py field type spellings -> fixed-width primitives (MSVC x86 data model).
CONTRACT_PRIM = {"float": "f32", "double": "f64", "int": "i32", "uint": "u32", "long": "i32",
                 "ulong": "u32", "short": "i16", "ushort": "u16", "char": "char8", "uchar": "u8",
                 "bool": "bool8", "int64": "i64", "uint64": "u64", "wchar": "wchar16",
                 "int8": "i8", "uint8": "u8"}
OP_ORDER = ("set_type", "create_function", "set_function_body", "set_function_name",
            "set_function_signature", "set_comment_segment")
FIELDS = ("name", "body", "signature")
EXIT = {"ok": 0, "noop": 0, "pass": 0, "invalid": 2, "blocked": 3, "unsupported": 4,
        "environment": 5, "execution": 6, "mismatch": 7}


class MetadataError(Exception):
    """A failure with a category from EXIT and structured details."""

    def __init__(self, category, message, **details):
        super().__init__(message)
        self.category, self.details = category, details


# ----------------------------------------------------------------- canonical form

def _check(value, where="$"):
    if isinstance(value, float):
        raise MetadataError("invalid", f"{where}: floats have no canonical form")
    if isinstance(value, dict):
        for k, v in value.items():
            if not isinstance(k, str):
                raise MetadataError("invalid", f"{where}: non-string key {k!r}")
            _check(v, f"{where}.{k}")
    elif isinstance(value, (list, tuple)):
        for i, v in enumerate(value):
            _check(v, f"{where}[{i}]")


def canonical(value):
    """The one serialization every digest uses: sorted keys, compact, UTF-8, integers only."""
    _check(value)
    return json.dumps(value, sort_keys=True, separators=(",", ":"), ensure_ascii=False).encode("utf-8")


def digest(value):
    return hashlib.sha256(canonical(value)).hexdigest()


def file_sha256(path):
    h = hashlib.sha256()
    with open(path, "rb") as handle:
        for block in iter(lambda: handle.read(1 << 20), b""):
            h.update(block)
    return h.hexdigest()


def read_json(path):
    try:
        with open(path, encoding="utf-8") as handle:
            return json.load(handle)
    except (OSError, ValueError) as exc:
        raise MetadataError("invalid", f"{path}: {exc}") from exc


def write_json(path, value):
    """Stable, reviewable text: sorted keys, two-space indent, trailing newline."""
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_text(json.dumps(value, sort_keys=True, indent=2, ensure_ascii=False) + "\n", encoding="utf-8")


def rva_text(value):
    return f"0x{value:08x}"


def rel(path):
    path = Path(path).resolve()
    try:
        return path.relative_to(ROOT).as_posix()
    except ValueError:
        return path.as_posix()


# ----------------------------------------------------------------- names

def qualified_parts(raw):
    """ghidra_refdb.qualified() as components: [scope..., name], or [raw] when it does not demangle.

    apply_metadata.java's qualified() mirrors this line for line."""
    m = ghidra_refdb.MANGLED.match(raw)
    if not m:
        return [raw]
    special, base, scopes = m.groups()
    scopes = [s for s in scopes.split("@") if s][::-1]
    if special == "?0":
        base = base or (scopes[-1] if scopes else "")
        scopes = scopes + [base]
    elif special == "?1":
        scopes, base = scopes + [base], "~" + base
    elif special:
        return [raw]
    parts = scopes + [base]
    assert "::".join(parts) == ghidra_refdb.qualified(raw), raw
    return parts


def ghidra_name(raw):
    """(namespace, name) a function carrying this evidence spelling gets in Ghidra."""
    parts = qualified_parts(raw)
    return parts[:-1], parts[-1]


def split_qualified(key):
    """'A::B<C::D>::E' -> ['A', 'B<C::D>', 'E']; never collapses to the last component."""
    parts, depth, cur, i = [], 0, "", 0
    while i < len(key):
        c = key[i]
        if c in "<(":
            depth += 1
        elif c in ">)":
            depth -= 1
        if depth == 0 and key.startswith("::", i):
            parts.append(cur)
            cur, i = "", i + 2
            continue
        cur += c
        i += 1
    parts.append(cur)
    return parts


def type_record_name(key):
    """types/<lowercased portable key>-<8 hex of the key's SHA-256>.json.

    Lowercase because reverse/ and tools/ are control trees (tools/check_case_collisions.py);
    the digest keeps keys that differ only in case apart."""
    return (f"types/{class_contract.portable_component(key).lower()}-"
            f"{hashlib.sha256(key.encode('utf-8')).hexdigest()[:8]}.json")


def type_path(key):
    parts = split_qualified(key)
    if not key or any(not p or "/" in p for p in parts) or "\n" in key:
        raise MetadataError("invalid", f"type key {key!r} has no portable Ghidra path")
    return TYPE_ROOT + "/" + "/".join(parts)


# ----------------------------------------------------------------- comment segments

def _segment_bounds(text, sid):
    if text is None:
        return None
    opening, closing = f"[re-metadata:{sid}]\n", f"\n[/re-metadata:{sid}]"
    starts = [m.start() for m in re.finditer(re.escape(opening), text)
              if m.start() == 0 or text[m.start() - 1] == "\n"]
    if not starts:
        if f"[re-metadata:{sid}]" in text or f"[/re-metadata:{sid}]" in text:
            raise MetadataError("blocked", f"malformed managed segment {sid}")
        return None
    end = text.find(closing, starts[0] + len(opening))
    if len(starts) > 1 or end < 0:
        raise MetadataError("blocked", f"malformed managed segment {sid}")
    end += len(closing)
    if end < len(text) and text[end] != "\n":
        raise MetadataError("blocked", f"malformed managed segment {sid}")
    return starts[0], end


def segment_text(text, sid):
    """The managed segment `sid` inside a comment, or None. Mirrors apply_metadata.java."""
    bounds = _segment_bounds(text, sid)
    if bounds is None:
        return None
    return text[bounds[0] + len(f"[re-metadata:{sid}]\n"):bounds[1] - len(f"\n[/re-metadata:{sid}]")]


def with_segment(text, sid, value):
    """The comment with segment `sid` set to `value` (None removes it), other text untouched."""
    bounds = _segment_bounds(text, sid)
    block = None if value is None else f"[re-metadata:{sid}]\n{value}\n[/re-metadata:{sid}]"
    if bounds is None:
        if block is None:
            return text
        out = block if not text else text + "\n" + block
    elif block is not None:
        out = text[:bounds[0]] + block + text[bounds[1]:]
    elif bounds[0] > 0:
        out = text[:bounds[0] - 1] + text[bounds[1]:]
    else:
        out = text[bounds[1] + 1 if bounds[1] < len(text) else bounds[1]:]
    return out or None


# ----------------------------------------------------------------- package

class Package:
    """A metadata package: manifest.json plus records under functions/, types/,
    comments/ and recipe/. Relative paths in it resolve from the repository root."""

    def __init__(self, root, manifest, records):
        self.root, self.manifest, self.records = Path(root), manifest, records

    @classmethod
    def load(cls, root):
        root = Path(root)
        if not (root / "manifest.json").exists():
            raise MetadataError("invalid", f"{root}: no manifest.json")
        records = {}
        for sub in ("functions", "types", "comments", "recipe"):
            for path in sorted((root / sub).glob("*.json")):
                records[f"{sub}/{path.name}"] = read_json(path)
        return cls(root, read_json(root / "manifest.json"), records)

    def write(self, root=None):
        root = Path(root or self.root)
        write_json(root / "manifest.json", self.manifest)
        for name, value in self.records.items():
            write_json(root / name, value)

    def digest(self):
        manifest = {k: v for k, v in self.manifest.items() if k != "metadata_sha256"}
        return digest({"manifest": manifest, "records": self.records})

    def recipe_digest(self):
        return digest({"recipe": self.manifest.get("recipe"),
                       "records": {k: v for k, v in self.records.items() if k.startswith("recipe/")}})

    def evidence_root(self, override=None):
        return Path(override) if override else ROOT / self.manifest.get("evidence_root", ".")

    def contract_roots(self):
        return [ROOT / p for p in self.manifest.get("contract_roots", ["reverse/class_contracts"])]

    def excluded(self, record, field):
        return any(e.get("record") == record and e.get("field") in (field, "*")
                   for e in self.manifest.get("exclusions", []))


def _provenance_errors(prov, where):
    errors = []
    if not isinstance(prov, dict):
        return [f"{where}: provenance missing"]
    for key, allowed in (("origin", ORIGINS), ("status", STATUSES), ("review", REVIEWS)):
        if prov.get(key) not in allowed:
            errors.append(f"{where}: provenance.{key} must be one of {allowed}")
    for ref in prov.get("evidence_refs", []):
        if not isinstance(ref, dict) or set(ref) - {"path", "record_key", "sha256", "note"} \
                or not ref.get("path") or not re.fullmatch(r"[0-9a-f]{64}", str(ref.get("sha256", ""))):
            errors.append(f"{where}: malformed evidence_ref {ref!r}")
    return errors


def range_errors(ranges, entry=None):
    """Half-open [start, end) RVA intervals: sorted, disjoint, non-adjacent, non-wrapping."""
    errors, last = [], None
    if not isinstance(ranges, list) or not ranges:
        return ["body has no ranges"]
    for r in ranges:
        if not (isinstance(r, list) and len(r) == 2 and all(isinstance(x, str) and RVA.match(x) for x in r)):
            errors.append(f"malformed interval {r!r}")
            continue
        start, end = int(r[0], 16), int(r[1], 16)
        if end <= start:
            errors.append(f"empty or inverted interval {r!r}")
        if last is not None and start <= last:
            errors.append(f"interval {r!r} overlaps or touches its predecessor (Ghidra would merge it)")
        last = end
    if entry is not None and not errors:
        e = int(entry, 16)
        if not any(int(s, 16) <= e < int(x, 16) for s, x in ranges):
            errors.append(f"entry {entry} lies outside its body")
    return errors


def pe_layout(path):
    """(image_base, [(rva, size, executable)]) of a PE32 image."""
    data = Path(path).read_bytes()
    if data[:2] != b"MZ":
        raise MetadataError("invalid", f"{path}: not a PE image")
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    if data[pe:pe + 4] != b"PE\0\0":
        raise MetadataError("invalid", f"{path}: not a PE image")
    nsect, optsize = struct.unpack_from("<H", data, pe + 6)[0], struct.unpack_from("<H", data, pe + 20)[0]
    opt = pe + 24
    if struct.unpack_from("<H", data, opt)[0] != 0x10B:
        raise MetadataError("unsupported", f"{path}: only PE32 images are supported")
    image_base = struct.unpack_from("<I", data, opt + 28)[0]
    sections = []
    for i in range(nsect):
        at = opt + optsize + 40 * i
        vsize, va, rawsize = struct.unpack_from("<III", data, at + 8)
        flags = struct.unpack_from("<I", data, at + 36)[0]
        sections.append((va, max(vsize, 0) or rawsize, bool(flags & 0x20000000)))
    return image_base, sections


def validate(pkg, executable=None, evidence_root=None):
    """Structural validation plus input and digest binding. Returns a report dict."""
    errors, warnings = [], []
    m = pkg.manifest
    if m.get("schema") != SCHEMA:
        return {"status": "invalid", "errors": [f"unknown manifest schema {m.get('schema')!r}"],
                "warnings": [], "counts": {}}
    target = m.get("target") or {}
    for key in ("executable_sha256", "image_base", "address_space", "pointer_size", "language_id",
                "compiler_spec_id"):
        if key not in target:
            errors.append(f"manifest.target.{key} missing")
    if not re.fullmatch(r"[0-9a-f]{64}", str(target.get("executable_sha256", ""))):
        errors.append("manifest.target.executable_sha256 is not a lowercase SHA-256")
    for key in ("recipe", "capabilities", "inputs"):
        if key not in m:
            errors.append(f"manifest.{key} missing")
    for item in m.get("inputs", []):
        path = ROOT / item.get("path", "")
        if not path.is_file():
            errors.append(f"input {item.get('path')} is missing")
        elif file_sha256(path) != item.get("sha256"):
            errors.append(f"input {item.get('path')} changed: sha256 {file_sha256(path)} != {item.get('sha256')}")
    bound = {i.get("path") for i in m.get("inputs", [])}
    for script in (m.get("recipe") or {}).get("pre_scripts", []):
        if f"tools/ghidra/{script.get('script')}" not in bound:
            errors.append(f"recipe pre-script {script.get('script')} is not a hash-bound input")
        if script.get("args_are_paths"):
            errors += [f"recipe pre-script argument {a} is not a hash-bound input"
                       for a in script.get("args", []) if a not in bound]
    counts = {"functions": 0, "types": 0, "comments": 0}
    for name, rec in sorted(pkg.records.items()):
        sub = name.split("/")[0]
        if sub == "recipe":
            continue
        if not isinstance(rec, dict) or rec.get("schema") != SCHEMA:
            errors.append(f"{name}: unknown record schema {rec.get('schema') if isinstance(rec, dict) else rec!r}")
            continue
        kind = {"functions": "function", "types": "type", "comments": "comment"}[sub]
        if rec.get("kind") != kind:
            errors.append(f"{name}: kind must be {kind}")
            continue
        counts[sub] += 1
        if kind == "function":
            entry = rec.get("entry_rva", "")
            if not RVA.match(str(entry)):
                errors.append(f"{name}: malformed entry_rva {entry!r}")
                continue
            if name != f"functions/{entry}.json":
                errors.append(f"{name}: file name must be functions/{entry}.json")
            for field in FIELDS:
                if field in rec:
                    errors += _provenance_errors(rec[field].get("provenance"), f"{name}:{field}")
            if "body" in rec:
                errors += [f"{name}: {e}" for e in range_errors(rec["body"].get("ranges"), entry)]
            if "name" in rec:
                raw = rec["name"].get("raw")
                if not raw:
                    errors.append(f"{name}: name.raw missing")
                else:
                    ns, base = ghidra_name(raw)
                    if rec["name"].get("namespace", ns) != ns or rec["name"].get("ghidra_name", base) != base:
                        errors.append(f"{name}: namespace/ghidra_name disagree with the raw spelling")
        elif kind == "type":
            key = rec.get("key", "")
            try:
                type_path(key)
            except MetadataError as exc:
                errors.append(f"{name}: {exc}")
                continue
            if name != type_record_name(key):
                errors.append(f"{name}: file name must be {type_record_name(key)}")
            errors += _provenance_errors(rec.get("provenance"), name)
            if rec.get("representation") not in ("struct", "enum", "typedef"):
                errors.append(f"{name}: representation must be struct, enum or typedef")
            if "contract" in rec:
                cpath = ROOT / rec["contract"].get("path", "")
                expected = [r / f"{class_contract.portable_component(key)}.json" for r in pkg.contract_roots()]
                if cpath.resolve() not in [e.resolve() for e in expected]:
                    errors.append(f"{name}: contract path is not class_contract.contract_path({key!r}) "
                                  f"under the package's contract roots")
                elif not cpath.is_file():
                    errors.append(f"{name}: contract {rec['contract']['path']} is missing")
                elif file_sha256(cpath) != rec["contract"].get("sha256"):
                    errors.append(f"{name}: contract {rec['contract']['path']} changed since the record was made")
            elif "layout" not in rec:
                errors.append(f"{name}: a type needs a contract reference or a layout")
        else:
            addr, ck, sid = rec.get("address_rva", ""), rec.get("comment_kind"), rec.get("segment_id", "")
            if not RVA.match(str(addr)) or ck not in COMMENT_KINDS or not SEGMENT_ID.match(str(sid)):
                errors.append(f"{name}: malformed address_rva/comment_kind/segment_id")
                continue
            if name != f"comments/{addr}-{ck}-{sid}.json":
                errors.append(f"{name}: file name must be comments/{addr}-{ck}-{sid}.json")
            if not rec.get("deleted") and not isinstance(rec.get("text"), str):
                errors.append(f"{name}: text missing (use deleted: true for a tombstone)")
            if isinstance(rec.get("text"), str) and "[re-metadata:" in rec["text"]:
                errors.append(f"{name}: text may not contain segment delimiters")
            errors += _provenance_errors(rec.get("provenance"), name)
    for item in m.get("exclusions", []):
        if item.get("record") not in pkg.records or not item.get("reason"):
            errors.append(f"exclusion {item!r} names no record or gives no reason")
    if executable is not None:
        exe = Path(executable)
        if not exe.is_file():
            errors.append(f"executable {exe} is missing")
        else:
            sha = file_sha256(exe)
            if sha != target.get("executable_sha256"):
                errors.append(f"executable sha256 {sha} != manifest {target.get('executable_sha256')}")
            else:
                base, sections = pe_layout(exe)
                if rva_text(base) != target.get("image_base"):
                    errors.append(f"executable image base {rva_text(base)} != manifest {target.get('image_base')}")
                for name, rec in pkg.records.items():
                    for s, e in (rec.get("body", {}) or {}).get("ranges", []) if name.startswith("functions/") else []:
                        if not any(va <= int(s, 16) and int(e, 16) <= va + size and x for va, size, x in sections):
                            errors.append(f"{name}: interval [{s}, {e}) is not inside one executable section")
    actual = pkg.digest()
    if m.get("metadata_sha256") != actual:
        errors.append(f"metadata_sha256 {m.get('metadata_sha256')} != computed {actual} "
                      "(run metadata-validate --update-digest after reviewing the change)")
    status = "invalid" if errors else "ok"
    return {"status": status, "errors": errors, "warnings": warnings, "counts": counts,
            "metadata_sha256": actual}


# ----------------------------------------------------------------- evidence

_CSV_CACHE = {}


def evidence_rows(root, relative):
    path = Path(root) / relative
    key = (path.resolve(), path.stat().st_mtime_ns if path.exists() else None)
    if key not in _CSV_CACHE:
        rows = []
        if path.exists():
            with path.open(encoding="utf-8", newline="") as handle:
                reader = csv.DictReader(handle)
                header = reader.fieldnames or []
                rows = [{h: row.get(h) for h in header} for row in reader]
        _CSV_CACHE[key] = rows
    return _CSV_CACHE[key]


def tier_file(tier):
    return "reverse/" + ghidra_refdb.TIER_FILES[tier]


def record_key(tier, row):
    column = ghidra_refdb.TIER_RVA[tier]
    return f"{column}={row.get(column) or ''};name={row.get('name') or ''}"


def evidence_ref(tier, row):
    return {"path": tier_file(tier), "record_key": record_key(tier, row), "sha256": digest(row)}


def verify_refs(root, refs):
    """(problems, {binding key: sha256}, [rows]) for evidence_refs of any field.

    A ref into a ledger CSV binds one row (record_key, row digest); any other path
    binds the whole file, resolved from the repository root."""
    problems, bound, rows = [], {}, []
    tiers = {tier_file(t): t for t in ghidra_refdb.TIER_FILES}
    for ref in refs or []:
        path = ref.get("path", "")
        if path in tiers:
            hits = [r for r in evidence_rows(root, path) if record_key(tiers[path], r) == ref.get("record_key")]
            if len(hits) != 1:
                problems.append(f"{path} [{ref.get('record_key')}] matched {len(hits)} rows")
            elif digest(hits[0]) != ref.get("sha256"):
                problems.append(f"evidence changed: {path} [{ref['record_key']}]")
            else:
                bound[f"{path}#{ref['record_key']}"] = ref["sha256"]
                rows.append((path, hits[0]))
        else:
            f = ROOT / path
            if not path or not f.is_file():
                problems.append(f"evidence file {path!r} is missing")
            elif file_sha256(f) != ref.get("sha256"):
                problems.append(f"evidence changed: {path}")
            else:
                bound[path] = ref["sha256"]
    return problems, bound, rows


def admissible_names(root, entry):
    """{name: [(tier, row)]} every evidence tier admits at this entry RVA."""
    found = {}
    for tier in ("export", "ilt", "reloc"):
        column = ghidra_refdb.TIER_RVA[tier]
        for row in evidence_rows(root, tier_file(tier)):
            if row.get(column) and int(row[column], 16) == entry and ghidra_refdb.admits(tier, row):
                found.setdefault(row["name"], []).append((tier, row))
    return found


def check_name_evidence(root, entry_rva, raw, prov):
    """[] when the claimed tier is backed by unchanged admitting rows, else the problems.

    The tier string in a record is a claim; this re-reads the evidence it cites and
    applies ghidra_refdb.admits(), the same predicate sync-plan uses."""
    tier, problems, rows = prov.get("identity_tier"), [], []
    if tier not in ghidra_refdb.TIER_FILES:
        return [f"identity tier {tier!r} is not export, ilt or reloc"], rows
    refs = prov.get("evidence_refs") or []
    if not refs:
        return ["no evidence_refs for the claimed tier"], rows
    entry = int(entry_rva, 16)
    for ref in refs:
        if ref.get("path") != tier_file(tier):
            problems.append(f"{ref.get('path')} cannot establish tier {tier}")
            continue
        hits = [r for r in evidence_rows(root, ref["path"]) if record_key(tier, r) == ref.get("record_key")]
        if len(hits) != 1:
            problems.append(f"{ref['path']} [{ref.get('record_key')}] matched {len(hits)} rows")
            continue
        row = hits[0]
        if digest(row) != ref.get("sha256"):
            problems.append(f"evidence changed: {ref['path']} [{ref['record_key']}]")
        elif not ghidra_refdb.admits(tier, row):
            problems.append(f"{ref['path']} [{ref['record_key']}] does not admit tier {tier}")
        elif int(row[ghidra_refdb.TIER_RVA[tier]], 16) != entry or row["name"] != raw:
            problems.append(f"{ref['path']} [{ref['record_key']}] names another function or symbol")
        else:
            rows.append({"ref": ref, "row": row})
    aliases = sorted(n for n in admissible_names(root, entry) if n != raw)
    if aliases:
        problems.append(f"alias conflict: evidence also admits {aliases} at {entry_rva}")
    return problems, rows


# ----------------------------------------------------------------- types

def _ref_from_contract(text):
    text = text.replace(" ", "")
    if text.endswith("*"):
        inner = text[:-1]
        return {"ptr": {"prim": "void"} if inner == "void" else _ref_from_contract(inner)}
    m = re.fullmatch(r"(.+)\[(\d+)\]", text)
    if m:
        return {"array": _ref_from_contract(m[1]), "count": int(m[2])}
    if text in CONTRACT_PRIM:
        return {"prim": CONTRACT_PRIM[text]}
    if text in PRIM_SIZE:
        return {"prim": text}
    return {"named": text}


class TypeSet:
    """Desired managed types resolved from the package: contracts and novel layouts."""

    def __init__(self):
        self.types, self.problems = {}, []      # key -> dict; [(category, record, message)]

    def size(self, ref, seen=()):
        if "prim" in ref:
            return PRIM_SIZE[ref["prim"]]
        if "ptr" in ref:
            return 4
        if "array" in ref:
            return ref["count"] * self.size(ref["array"], seen)
        key = ref["named"]
        if key in seen:
            raise MetadataError("unsupported", f"impossible by-value cycle through {key}")
        t = self.types[key]
        if t["representation"] == "typedef":
            return self.size(t["layout"]["target"], seen + (key,))
        return t["layout"]["size"]

    def scalar(self, ref):
        """The primitive a supported scalar/pointer reference resolves to, else None."""
        if "ptr" in ref:
            return "ptr"
        if "typedef" in ref:
            return self.scalar(ref["of"])
        if "prim" in ref:
            return None if ref["prim"] == "void" else ref["prim"]
        if "named" in ref and ref["named"] in self.types:
            t = self.types[ref["named"]]
            if t["representation"] == "enum":
                return {1: "i8", 2: "i16", 4: "i32", 8: "i64"}[t["layout"]["size"]]
            if t["representation"] == "typedef":
                return self.scalar(t["layout"]["target"])
        return None

    def refs(self, ref, by_value=True):
        """(named key, by_value) pairs a reference depends on."""
        if "ptr" in ref:
            return self.refs(ref["ptr"], False)
        if "array" in ref:
            return self.refs(ref["array"], by_value)
        if "named" in ref:
            return [(ref["named"], by_value)]
        return []

    def projection_ref(self, ref):
        if "ptr" in ref:
            return {"ptr": self.projection_ref(ref["ptr"])}
        if "array" in ref:
            return {"array": self.projection_ref(ref["array"]), "count": ref["count"]}
        if "named" in ref:
            return {"named": type_path(ref["named"])}
        return dict(ref)


def resolve_types(pkg, records):
    """TypeSet from the accepted type records (contract adapters and novel layouts)."""
    ts = TypeSet()
    for name, rec in sorted(records.items()):
        key, prov = rec["key"], rec.get("provenance", {})
        if prov.get("review") != "accepted" or prov.get("status") == "hypothesis":
            continue
        t = {"key": key, "record": name, "representation": rec["representation"], "provenance": prov,
             "abi_unknown": rec.get("abi_unknown", [])}
        if "contract" in rec:
            cpath = ROOT / rec["contract"]["path"]
            contract = read_json(cpath)
            why = []
            if contract.get("class") != key:
                why.append(f"contract names {contract.get('class')!r}, not {key!r}")
            if contract.get("bases"):
                why.append("inheritance (bases) is deferred")
            if contract.get("vslots") or any(f.get("kind") == "VPTR" for f in contract.get("fields", [])):
                why.append("virtual tables are deferred")
            if contract.get("queue"):
                ts.problems.append(("conflict", name, f"contract {key} has {len(contract['queue'])} "
                                    "unresolved ABI decision(s) in its queue"))
                continue
            if why:
                ts.problems.append(("unsupported", name, "; ".join(why)))
                continue
            fields = []
            for f in contract.get("fields", []):
                if "bit" in str(f.get("kind", "")).lower() or ":" in str(f.get("name", "")):
                    why.append(f"bitfield {f.get('name')} is deferred")
                fields.append({"offset": f["offset"], "size": f["size"], "name": f["name"],
                               "type": _ref_from_contract(f["type"]),
                               "comment": f"layout_by={f.get('decided_by')}; name_by={f.get('name_by')}"})
            if why:
                ts.problems.append(("unsupported", name, "; ".join(why)))
                continue
            t["layout"] = {"size": contract["size"], "fields": fields}
            t["source"] = f"{rec['contract']['path']}@{rec['contract']['sha256'][:12]}"
            t["contract"] = rec["contract"]
        else:
            t["layout"] = rec["layout"]
            t["source"] = "overlay"
            if t["representation"] == "struct":
                for f in t["layout"].get("fields", []):
                    f.setdefault("comment", f"layout_by={f.pop('layout_by', 'overlay')}; "
                                            f"name_by={f.pop('name_by', 'overlay')}")
        ts.types[key] = t
    # Dependencies: every named reference must resolve; by-value references must be acyclic.
    for key in sorted(ts.types):
        t = ts.types[key]
        deps = []
        if t["representation"] == "struct":
            for f in t["layout"]["fields"]:
                deps += ts.refs(f["type"])
        elif t["representation"] == "typedef":
            deps += ts.refs(t["layout"]["target"])
        missing = sorted({d for d, _ in deps if d not in ts.types})
        if missing:
            ts.problems.append(("conflict", t["record"], f"unresolved field type(s) {missing}"))
            t["broken"] = True
        t["by_value"] = sorted({d for d, v in deps if v and d in ts.types})
        t["pointer"] = sorted({d for d, v in deps if not v and d in ts.types})
    changed = True
    while changed:
        changed = False
        for t in ts.types.values():
            if not t.get("broken") and any(ts.types[d].get("broken") for d in t["by_value"] + t["pointer"]):
                t["broken"] = True
                changed = True
    for key in sorted(ts.types):
        t = ts.types[key]
        if t.get("broken"):
            continue
        try:
            if t["representation"] == "struct":
                _check_struct(ts, t)
            elif t["representation"] == "enum":
                _check_enum(t)
            else:
                ts.size(t["layout"]["target"], (key,))
        except MetadataError as exc:
            ts.problems.append((exc.category, t["record"], str(exc)))
            t["broken"] = True
    return ts


def _check_struct(ts, t):
    size, last = t["layout"]["size"], 0
    if not isinstance(size, int) or size < 0:
        raise MetadataError("invalid", f"{t['key']}: size must be a non-negative integer")
    for f in sorted(t["layout"]["fields"], key=lambda f: f["offset"]):
        want = ts.size(f["type"], (t["key"],))
        if f["offset"] < last:
            raise MetadataError("unsupported", f"{t['key']}.{f['name']} overlaps its predecessor (union-like layout)")
        if f["size"] != want:
            raise MetadataError("unsupported", f"{t['key']}.{f['name']}: field size {f['size']} != "
                                f"{want} for its type")
        if f["offset"] + f["size"] > size:
            raise MetadataError("invalid", f"{t['key']}.{f['name']} extends past the type's size {size}")
        last = f["offset"] + f["size"]


def _check_enum(t):
    lay = t["layout"]
    width, signed = lay.get("size"), lay.get("signed")
    if width not in (1, 2, 4, 8) or not isinstance(signed, bool):
        raise MetadataError("invalid", f"{t['key']}: an enum needs size 1/2/4/8 and an explicit signed flag")
    lo, hi = (-(1 << (8 * width - 1)), (1 << (8 * width - 1)) - 1) if signed else (0, (1 << (8 * width)) - 1)
    for name, value in lay.get("values", []):
        if not isinstance(value, int) or not lo <= value <= hi:
            raise MetadataError("invalid", f"{t['key']}.{name}={value} does not fit a "
                                f"{'signed' if signed else 'unsigned'} {width}-byte enum")
        if value > (1 << 63) - 1:
            raise MetadataError("unsupported", f"{t['key']}.{name}: values above 2^63-1 are not representable")


def type_projection(ts, t):
    """The semantic projection apply_metadata.java must produce for a managed type."""
    lay = t["layout"]
    if t["representation"] == "enum":
        values = sorted(([n, v] for n, v in lay["values"]), key=lambda p: (p[1], p[0]))
        width = lay["size"]
        if any(v < 0 for _, v in values):
            state = "signed"
        elif any(v > (1 << (8 * width - 1)) - 1 for _, v in values):
            state = "unsigned"
        else:
            state = "either"
        return {"kind": "enum", "size": width, "signed_state": state, "values": values,
                "description": f"re-metadata key={t['key']} source={t['source']} "
                               f"signed={'true' if lay['signed'] else 'false'}"}
    description = f"re-metadata key={t['key']} source={t['source']}"
    if t["representation"] == "typedef":
        # Ghidra typedefs carry no description; the managed-state record holds their provenance.
        return {"kind": "typedef", "target": ts.projection_ref(lay["target"]), "description": ""}
    return {"kind": "struct", "size": lay["size"], "packing": False, "description": description,
            "fields": [{"offset": f["offset"], "size": f["size"], "name": f["name"],
                        "type": ts.projection_ref(f["type"]), "comment": f.get("comment", "")}
                       for f in sorted(lay["fields"], key=lambda f: f["offset"])]}


def type_order(ts, keys):
    """Deterministic dependency order: by-value dependencies (and typedef targets) first."""
    out, done = [], set()

    def visit(key, stack=()):
        if key in done:
            return
        for dep in ts.types[key]["by_value"]:
            if dep in keys and dep not in stack:
                visit(dep, stack + (key,))
        done.add(key)
        out.append(key)
    for key in sorted(keys):
        visit(key)
    return out


# ----------------------------------------------------------------- signatures

def signature_problems(sig, ts):
    """[] for a replayable standard-convention signature, else why it is deferred."""
    why = []
    if sig.get("convention") not in CONVENTIONS:
        why.append(f"calling convention {sig.get('convention')!r} is deferred")
    if sig.get("variadic"):
        why.append("varargs replay is deferred")
    if sig.get("storage_mode", "dynamic") != "dynamic":
        why.append("custom storage is deferred")
    ret = sig.get("return") or {}
    rtype = ret.get("type") or {}
    if rtype != {"prim": "void"}:
        scalar = ts.scalar(rtype)
        if scalar is None:
            why.append("aggregate (or unresolved) return and hidden return buffers are deferred")
        elif scalar in ("i64", "u64"):
            why.append("register-pair return storage is deferred")
    for p in sig.get("params", []):
        if p.get("name") == "this":
            why.append("an explicit 'this' parameter would duplicate the automatic one")
        if ts.scalar(p.get("type") or {}) is None:
            why.append(f"parameter {p.get('name')!r}: aggregate-by-value (or unresolved) types are deferred")
    for item in [ret] + list(sig.get("params", [])) + list(sig.get("auto_params", [])):
        storage = item.get("storage")
        if storage is None:
            why.append("storage is not recorded")
        elif len(storage) > 1:
            why.append("split or register-pair storage is deferred")
        elif storage and not ({"reg", "size"} == set(storage[0]) or {"stack", "size"} == set(storage[0])):
            why.append(f"storage {storage} is neither one register nor one stack slot")
    autos = [a.get("role") for a in sig.get("auto_params", [])]
    if autos != (["this"] if sig.get("convention") == "__thiscall" else []):
        why.append(f"automatic parameters {autos} are ambiguous for {sig.get('convention')}")
    return why


def signature_projection(sig, ts):
    return {"convention": sig["convention"], "variadic": False, "storage_mode": "dynamic",
            "return": {"type": ts.projection_ref(sig["return"]["type"]), "storage": sig["return"]["storage"]},
            "params": [{"name": p["name"], "type": ts.projection_ref(p["type"]), "storage": p["storage"]}
                       for p in sig.get("params", [])],
            "auto_params": [{"role": a["role"], "storage": a["storage"]} for a in sig.get("auto_params", [])]}


# ----------------------------------------------------------------- desired state

def replayable(prov):
    return prov.get("review") == "accepted" and prov.get("status") != "hypothesis"


def resolve(pkg, evidence_root=None):
    """Desired facts from the package, plus conflicts/unsupported/excluded/context.

    Offline: needs the repository, not Ghidra. Field-specific evidence decides what
    is replayable; review acceptance alone only makes a field eligible."""
    root = pkg.evidence_root(evidence_root)
    out = {"functions": {}, "types": {}, "comments": {}, "conflicts": [], "unsupported": [],
           "excluded": [], "context": [], "evidence": {}}
    type_records = {k: v for k, v in pkg.records.items() if k.startswith("types/")}
    for name in sorted(type_records):
        if pkg.excluded(name, "*"):
            reason = next(e["reason"] for e in pkg.manifest["exclusions"] if e["record"] == name)
            out["excluded"].append({"record": name, "field": "*", "reason": reason})
            type_records.pop(name)
    ts = resolve_types(pkg, type_records)
    for category, record, message in ts.problems:
        out["conflicts" if category in ("conflict", "invalid") else "unsupported"].append(
            {"record": record, "field": "type", "reason": message})
    for name, rec in sorted(type_records.items()):
        if not replayable(rec.get("provenance", {})):
            out["context"].append({"record": name, "field": "type", "review": rec["provenance"].get("review"),
                                   "status": rec["provenance"].get("status")})
    for key, t in sorted(ts.types.items()):
        if not t.get("broken"):
            out["types"][type_path(key)] = {"key": key, "record": t["record"],
                                            "projection": type_projection(ts, t),
                                            "by_value": [type_path(d) for d in t["by_value"]],
                                            "provenance": t["provenance"], "abi_unknown": t["abi_unknown"]}
    out["type_order"] = [type_path(k) for k in type_order(ts, [k for k, t in ts.types.items() if not t.get("broken")])]
    broken_paths = {type_path(k) for k, t in ts.types.items() if t.get("broken")}

    def uses_broken(ref):
        return any(type_path(d) in broken_paths or d not in ts.types for d, _ in ts.refs(ref))

    for name, rec in sorted(pkg.records.items()):
        if not name.startswith("functions/"):
            continue
        entry = rec["entry_rva"]
        fn = {}
        for field in FIELDS:
            if field not in rec:
                continue
            value, prov = rec[field], rec[field].get("provenance", {})
            if pkg.excluded(name, field):
                reason = next(e["reason"] for e in pkg.manifest["exclusions"]
                              if e["record"] == name and e["field"] in (field, "*"))
                out["excluded"].append({"record": name, "field": field, "reason": reason})
                continue
            if not replayable(prov):
                out["context"].append({"record": name, "field": field, "review": prov.get("review"),
                                       "status": prov.get("status")})
                continue
            if field == "name":
                problems, rows = check_name_evidence(root, entry, value["raw"], prov)
                if problems:
                    out["conflicts"].append({"record": name, "field": "name", "reason": "; ".join(problems)})
                    continue
                ns, base = ghidra_name(value["raw"])
                for r in rows:
                    out["evidence"][f"{r['ref']['path']}#{r['ref']['record_key']}"] = r["ref"]["sha256"]
                fn["name"] = {"desired": {"name": {"name": base, "namespace": ns}, "raw": value["raw"]},
                              "provenance": prov, "evidence": rows}
            elif field == "body":
                if prov.get("status") != "supported":
                    out["context"].append({"record": name, "field": "body", "review": prov.get("review"),
                                           "status": prov.get("status"),
                                           "reason": "a body replaces analysis only on supported evidence"})
                    continue
                problems, bound, rows = verify_refs(root, prov.get("evidence_refs"))
                if not bound and not problems:
                    problems.append("an accepted body needs evidence_refs")
                for path, row in rows:
                    if path == tier_file("ilt"):
                        start = int(row.get("target_rva") or "0", 16)
                        extent = [[rva_text(start), rva_text(start + int(row.get("target_size") or 0))]]
                        if row.get("status") != "matched" or start != int(entry, 16) or extent != value["ranges"]:
                            problems.append(f"ledger row {row.get('name')} ({row.get('status')}, "
                                            f"{extent}) does not support this body")
                if problems:
                    out["conflicts"].append({"record": name, "field": "body", "reason": "; ".join(problems)})
                    continue
                out["evidence"].update(bound)
                fn["body"] = {"desired": {"body": value["ranges"]}, "provenance": prov,
                              "seeded": bool(value.get("seeded"))}
            else:
                why = signature_problems(value, ts)
                for part in [value.get("return", {}).get("type", {})] + [p.get("type", {}) for p in value.get("params", [])]:
                    if not why and uses_broken(part):
                        why.append("a signature type is unresolved or unsupported")
                if why:
                    out["unsupported"].append({"record": name, "field": "signature", "reason": "; ".join(why)})
                    continue
                problems, bound, _ = verify_refs(root, prov.get("evidence_refs"))
                if not bound and not problems:
                    problems.append("an accepted signature needs evidence_refs")
                if problems:
                    out["conflicts"].append({"record": name, "field": "signature", "reason": "; ".join(problems)})
                    continue
                out["evidence"].update(bound)
                fn["signature"] = {"desired": {"signature": signature_projection(value, ts)}, "provenance": prov}
        out["functions"][entry] = fn
    for name, rec in sorted(pkg.records.items()):
        if not name.startswith("comments/"):
            continue
        prov = rec.get("provenance", {})
        if pkg.excluded(name, "*"):
            continue
        if not replayable(prov):
            out["context"].append({"record": name, "field": "comment", "review": prov.get("review"),
                                   "status": prov.get("status")})
            continue
        problems, bound, _ = verify_refs(root, prov.get("evidence_refs"))
        if problems:
            out["conflicts"].append({"record": name, "field": "comment", "reason": "; ".join(problems)})
            continue
        out["evidence"].update(bound)
        key = (rec["address_rva"], rec["comment_kind"], rec["segment_id"])
        out["comments"][key] = {"desired": {"segment": None if rec.get("deleted") else rec["text"]},
                                "provenance": prov, "record": name}
    return out


# ----------------------------------------------------------------- observation requests

def observation_request(resolved, pkg):
    functions = []
    for entry in sorted({r["entry_rva"] for n, r in pkg.records.items() if n.startswith("functions/")}):
        q = {"entry_rva": entry}
        fn = resolved["functions"].get(entry, {})
        if "body" in fn:
            q["probe_body"] = fn["body"]["desired"]["body"]
        if "name" in fn:
            q["probe_name"] = fn["name"]["desired"]["name"]
        functions.append(q)
    types = sorted(set(resolved["types"]) | {type_path(r["key"]) for n, r in pkg.records.items()
                                              if n.startswith("types/")})
    comments = sorted({(a, k) for a, k, _ in resolved["comments"]})
    return {"functions": functions, "types": types,
            "comments": [{"address_rva": a, "kind": k} for a, k in comments]}


# ----------------------------------------------------------------- planning

def _op(kind, target, expected, desired, provenance, **extra):
    op = {"kind": kind, "target": target, "expected": expected, "desired": desired, "provenance": provenance}
    op["operation_id"] = digest(op)
    op.update(extra)
    return op


def _state_digest(state, key):
    return ((state or {}).get("fields", {}).get(key) or {}).get("digest")


def tool_digests():
    return {p: file_sha256(ROOT / p) for p in TOOLS}


def build_plan(pkg, resolved, obs):
    """A deterministic, reviewable plan of the writes that would reach `resolved`."""
    if obs.get("schema") != OBSERVATION_SCHEMA:
        raise MetadataError("invalid", "unknown observation schema")
    target, program = pkg.manifest["target"], obs["program"]
    conflicts = [dict(c) for c in resolved["conflicts"]]
    unsupported = [dict(u) for u in resolved["unsupported"]]
    for key in ("executable_sha256", "image_base", "address_space", "pointer_size", "language_id",
                "compiler_spec_id"):
        if str(program.get(key)) != str(target.get(key)):
            raise MetadataError("blocked", f"wrong target: program {key} is {program.get(key)!r}, "
                                f"the package is for {target.get(key)!r}", key=key)
    exe = target["executable_sha256"]
    state, baseline = obs.get("state"), obs.get("baseline")
    if baseline and baseline.get("binding", {}).get("executable_sha256") != exe:
        raise MetadataError("blocked", "the program's baseline is bound to another executable")
    ops, noops = [], []

    def conflict(record, field, reason):
        conflicts.append({"record": record, "field": field, "reason": reason})

    # Types, in dependency order.
    for path in resolved["type_order"]:
        t = resolved["types"][path]
        seen = obs["types"].get(path, {})
        cur, want = seen.get("projection"), t["projection"]
        suffixed = [p for p in obs.get("managed_type_paths", []) if p != path and p.startswith(path)
                    and re.fullmatch(re.escape(path) + r"(\.conflict\d*|_\d+)", p)]
        if suffixed:
            conflict(t["record"], "type", f"suffixed duplicate type(s) {suffixed} exist; never equivalent")
            continue
        if cur == want:
            noops.append({"kind": "set_type", "key": f"type:{path}"})
            continue
        if cur is not None:
            if _state_digest(state, f"type:{path}") != digest({"projection": cur}):
                conflict(t["record"], "type", f"{path} exists with a different, unmanaged layout")
                continue
            outside = [p for p in seen.get("parents", []) if p not in resolved["types"]]
            if outside:
                conflict(t["record"], "type", f"updating {path} would change out-of-scope consumers {outside}")
                continue
        ops.append(_op("set_type", {"executable_sha256": exe, "type_path": path},
                       {"projection": cur}, {"projection": want}, t["provenance"],
                       dependencies=t["by_value"], abi_unknown=t["abi_unknown"]))
    # Functions.
    fbase = (baseline or {}).get("functions", {})
    for entry, fn in sorted(resolved["functions"].items()):
        record = f"functions/{entry}.json"
        o = obs["functions"].get(entry)
        if o is None:
            raise MetadataError("invalid", f"observation lacks {entry}")
        tgt = {"executable_sha256": exe, "address_space": target["address_space"], "entry_rva": entry}
        created = False
        if "body" in fn:
            # A conflicting body stops this function's operations (and, as a conflict, the plan).
            probe = o.get("probe", {})
            problem = probe.get("unmapped") or (
                f"desired body overlaps function(s) {probe['overlaps']}: no ownership transfer"
                if probe.get("overlaps") else "desired body contains defined data" if probe.get("defined_data")
                else None)
            if problem:
                conflict(record, "body", problem)
                continue
        if not fn:
            continue
        if not o["exists"]:
            if "body" not in fn:
                conflict(record, "function", "no function at this entry and no accepted body to create it")
                continue
            if o.get("containing"):
                conflict(record, "body", f"entry lies inside the function at {o['containing']}: no automatic split")
                continue
            ops.append(_op("create_function", tgt, {"exists": False}, {"body": fn["body"]["desired"]["body"]},
                           fn["body"]["provenance"], seeded=fn["body"]["seeded"]))
            created = True
        elif "body" in fn:
            cur, want = o["body"], fn["body"]["desired"]["body"]
            b = fbase.get(entry)
            if cur == want:
                noops.append({"kind": "set_function_body", "key": f"function:{entry}:body"})
            elif (b and b.get("exists") and b.get("body_sha256") == digest(cur)) \
                    or _state_digest(state, f"function:{entry}:body") == digest({"body": cur}):
                ops.append(_op("set_function_body", tgt, {"body": cur}, {"body": want},
                               fn["body"]["provenance"], seeded=fn["body"]["seeded"]))
            else:
                conflict(record, "body", "current body is neither the recorded auto-analysis baseline nor "
                                         "an unchanged managed body" + ("" if baseline else
                                                                        " (this program has no baseline)"))
        if "name" in fn:
            want = fn["name"]["desired"]
            tier = fn["name"]["provenance"]["identity_tier"]
            if created:
                expected = None
            else:
                cur = o["name"]
                expected = {"name": cur, "source": o["name_source"]}
            probe = o.get("name_probe", {})
            if not created and cur == want["name"]:
                noops.append({"kind": "set_function_name", "key": f"function:{entry}:name"})
            elif any(k.startswith("clash:") for k in probe.get("kinds", [])):
                conflict(record, "name", f"namespace collision on {want['name']['namespace']}: {probe['kinds']}")
            elif [h for h in probe.get("holders", []) if h != entry]:
                conflict(record, "name", f"name collision: {want['name']} is held by {probe['holders']}")
            elif not created and tier != "ilt" and not (
                    o["name_source"] == "DEFAULT"
                    or ghidra_refdb.placeholder("::".join(cur["namespace"] + [cur["name"]]))):
                conflict(record, "name", f"tier {tier} may not overwrite the non-placeholder name "
                                         f"{'::'.join(cur['namespace'] + [cur['name']])} (only ilt may)")
            else:
                ops.append(_op("set_function_name", tgt, expected, want, fn["name"]["provenance"],
                               evidence=fn["name"]["evidence"]))
        if "signature" in fn:
            want = fn["signature"]["desired"]
            if created:
                ops.append(_op("set_function_signature", tgt, None, want, fn["signature"]["provenance"]))
                continue
            cur, source = o["signature"], o["signature_source"]
            b = fbase.get(entry)
            if cur == want["signature"]:
                noops.append({"kind": "set_function_signature", "key": f"function:{entry}:signature"})
            elif (b and b.get("signature_sha256") == digest(cur)) \
                    or _state_digest(state, f"function:{entry}:signature") == digest({"signature": cur, "source": source}) \
                    or (not baseline and source in ("DEFAULT", "ANALYSIS")):
                ops.append(_op("set_function_signature", tgt, {"signature": cur, "source": source}, want,
                               fn["signature"]["provenance"]))
            else:
                conflict(record, "signature", f"current {source} signature is not a verified analysis "
                                              "baseline or an unchanged managed signature")
    # Managed comment segments.
    for (addr, kind, sid), c in sorted(resolved["comments"].items()):
        text = obs["comments"].get(f"{addr}:{kind}")
        try:
            cur = segment_text(text, sid)
        except MetadataError as exc:
            conflict(c["record"], "comment", str(exc))
            continue
        want = c["desired"]["segment"]
        key = f"comment:{addr}:{kind}:{sid}"
        if cur == want:
            noops.append({"kind": "set_comment_segment", "key": key})
            continue
        if cur is not None and _state_digest(state, key) != digest({"segment": cur}):
            conflict(c["record"], "comment", "the managed segment was edited outside the tool")
            continue
        ops.append(_op("set_comment_segment", {"executable_sha256": exe, "address_space": target["address_space"],
                                               "address_rva": addr, "kind": kind, "segment_id": sid},
                       {"segment": cur}, {"segment": want}, c["provenance"]))
    ops.sort(key=lambda op: OP_ORDER.index(op["kind"]))   # stable: keeps type and RVA order inside a kind
    scope = {"functions": sorted(resolved["functions"]), "types": resolved["type_order"],
             "comments": [{"address_rva": a, "kind": k} for a, k in sorted({(a, k) for a, k, _ in resolved["comments"]})]}
    status = "blocked" if conflicts else "unsupported" if unsupported else "ready" if ops else "noop"
    plan = {"schema": PLAN_SCHEMA, "package_id": pkg.manifest.get("package_id"),
            "metadata_sha256": pkg.digest(), "recipe_sha256": pkg.recipe_digest(),
            "inputs": {i["path"]: i["sha256"] for i in pkg.manifest.get("inputs", [])},
            "evidence": resolved["evidence"], "tools": tool_digests(),
            "target": {k: target[k] for k in ("executable_sha256", "image_base", "address_space", "pointer_size",
                                              "language_id", "compiler_spec_id")},
            "program": {"name": program["name"], "ghidra_version": program["ghidra_version"]},
            "baseline_sha256": digest(baseline) if baseline else None,
            "state_sha256": digest(state) if state else None,
            "observation_sha256": digest({k: obs[k] for k in ("functions", "types", "comments")}),
            "scope": scope, "operations": ops, "noops": noops, "conflicts": conflicts,
            "unsupported": unsupported, "excluded": resolved["excluded"], "context": resolved["context"],
            "status": status}
    plan["plan_sha256"] = digest(plan)
    return plan


def check_plan_bindings(plan, pkg, evidence_root=None):
    """[] when nothing the plan relied on changed since planning, else what changed."""
    changed = []
    unsigned = {k: v for k, v in plan.items() if k != "plan_sha256"}
    if plan.get("schema") != PLAN_SCHEMA:
        return ["plan schema"]
    if digest(unsigned) != plan.get("plan_sha256"):
        return ["plan content (its digest does not match)"]
    if pkg.digest() != plan["metadata_sha256"]:
        changed.append("metadata package (records or manifest)")
    if pkg.recipe_digest() != plan["recipe_sha256"]:
        changed.append("recipe")
    for path, sha in plan["inputs"].items():
        if not (ROOT / path).is_file() or file_sha256(ROOT / path) != sha:
            changed.append(f"input {path}")
    root = pkg.evidence_root(evidence_root)
    for key, sha in plan["evidence"].items():
        if "#" not in key:
            if not (ROOT / key).is_file() or file_sha256(ROOT / key) != sha:
                changed.append(f"evidence file {key}")
            continue
        path, record = key.split("#", 1)
        tier = {tier_file(t): t for t in ghidra_refdb.TIER_FILES}[path]
        rows = [r for r in evidence_rows(root, path) if record_key(tier, r) == record]
        if len(rows) != 1 or digest(rows[0]) != sha:
            changed.append(f"evidence record {key}")
    for path, sha in plan["tools"].items():
        if file_sha256(ROOT / path) != sha:
            changed.append(f"tool {path}")
    return changed


# ----------------------------------------------------------------- comparison

EXPECTED_SOURCE = {"name": "IMPORTED", "signature": "IMPORTED"}


def compare(resolved, obs):
    """Field-by-field comparison of desired facts with an observation, provenance included."""
    state = (obs.get("state") or {}).get("fields", {})
    results = []

    def check(key, record, field, want, have, provenance, source=None):
        r = {"key": key, "record": record, "field": field}
        managed = state.get(key)
        if have != want:
            r.update(result="fail", reason="value differs", desired=want, actual=have)
        elif managed is None:
            # Equal before any replay (e.g. auto-analysis already found this body): nothing to manage.
            r.update(result="pass", provenance="unmanaged-equal", observed_source=source)
        elif managed.get("digest") != digest(dict(want, **({"source": EXPECTED_SOURCE[field]}
                                                            if field in EXPECTED_SOURCE else {}))):
            r.update(result="fail", reason="managed-state digest does not match the persisted value")
        elif managed.get("provenance_sha256") != digest(provenance):
            r.update(result="fail", reason="managed provenance differs from the package's")
        elif source is not None and field in EXPECTED_SOURCE and source != EXPECTED_SOURCE[field]:
            r.update(result="fail", reason=f"source is {source}, expected {EXPECTED_SOURCE[field]}")
        else:
            r.update(result="pass", provenance="managed", original=managed.get("original"))
        results.append(r)

    for path, t in sorted(resolved["types"].items()):
        have = (obs["types"].get(path) or {}).get("projection")
        check(f"type:{path}", t["record"], "type", {"projection": t["projection"]}, {"projection": have},
              t["provenance"])
        dupes = [p for p in obs.get("managed_type_paths", []) if re.fullmatch(re.escape(path) + r"(\.conflict\d*|_\d+)", p)]
        if dupes:
            results.append({"key": f"type:{path}", "record": t["record"], "field": "type", "result": "fail",
                            "reason": f"suffixed duplicates {dupes}"})
    for entry, fn in sorted(resolved["functions"].items()):
        o = obs["functions"].get(entry) or {"exists": False}
        record = f"functions/{entry}.json"
        for field in FIELDS:
            if field not in fn:
                continue
            if not o.get("exists"):
                results.append({"key": f"function:{entry}:{field}", "record": record, "field": field,
                                "result": "fail", "reason": "no function at entry"})
                continue
            if field == "name":
                check(f"function:{entry}:name", record, "name", {"name": fn["name"]["desired"]["name"]},
                      {"name": o["name"]}, fn["name"]["provenance"], o["name_source"])
            elif field == "body":
                check(f"function:{entry}:body", record, "body", fn["body"]["desired"], {"body": o["body"]},
                      fn["body"]["provenance"])
            else:
                check(f"function:{entry}:signature", record, "signature", fn["signature"]["desired"],
                      {"signature": o["signature"]}, fn["signature"]["provenance"], o["signature_source"])
    for (addr, kind, sid), c in sorted(resolved["comments"].items()):
        try:
            have = segment_text(obs["comments"].get(f"{addr}:{kind}"), sid)
        except MetadataError as exc:
            have = f"<{exc}>"
        check(f"comment:{addr}:{kind}:{sid}", c["record"], "comment", c["desired"], {"segment": have},
              c["provenance"])
    failed = [r for r in results if r["result"] != "pass"]
    counts = {"pass": len(results) - len(failed), "fail": len(failed),
              "excluded": len(resolved["excluded"]), "unsupported": len(resolved["unsupported"]),
              "conflicts": len(resolved["conflicts"])}
    return {"status": "pass" if not failed else "mismatch", "counts": counts, "fields": results,
            "excluded": resolved["excluded"], "unsupported": resolved["unsupported"],
            "conflicts": resolved["conflicts"],
            "compared_sha256": digest([{k: r[k] for k in ("key", "result")} for r in results])}


# ----------------------------------------------------------------- Ghidra runs

def ghidra_versions(ghidra, java):
    props = {}
    for line in (Path(ghidra) / "Ghidra" / "application.properties").read_text(encoding="utf-8").splitlines():
        key, _, value = line.partition("=")
        props[key.strip()] = value.strip()
    proc = subprocess.run([str(Path(java) / "bin" / "java"), "-XshowSettings:properties", "-version"],
                          capture_output=True, text=True)
    jv = re.search(r"java\.runtime\.version = (\S+)", proc.stderr)
    return {"ghidra_version": props.get("application.version"),
            "ghidra_revision": props.get("application.revision.ghidra"),
            "ghidra_release": props.get("application.release.name"),
            "java_version": jv[1] if jv else None}


def run_headless(project_dir, project_name, *, log, program=None, import_path=None, import_args=(),
                 pre=(), post=(), read_only=False, analysis=False, ghidra=None, java=None, max_cpu=None,
                 script_paths=()):
    """One analyzeHeadless process. Returns its log text; raises MetadataError on failure."""
    ghidra, java = ghidra_refdb.ghidra_home(ghidra), ghidra_refdb.java_home(java)
    launcher = ghidra / "support" / ("analyzeHeadless.bat" if os.name == "nt" else "analyzeHeadless")
    Path(project_dir).mkdir(parents=True, exist_ok=True)
    command = [str(launcher), str(Path(project_dir).resolve()), project_name]
    if import_path:
        command += ["-import", str(Path(import_path).resolve()), *import_args]
    else:
        command += ["-process", program]
    if not analysis:
        command.append("-noanalysis")
    if read_only:
        command.append("-readOnly")
    if max_cpu:
        command += ["-max-cpu", str(max_cpu)]
    command += ["-scriptPath", ";".join([str(SCRIPTS), *map(str, script_paths)])]
    for script, args in pre:
        command += ["-preScript", script, *map(str, args)]
    for script, args in post:
        command += ["-postScript", script, *map(str, args)]
    env = dict(os.environ, JAVA_HOME=str(java))
    started = time.monotonic()
    proc = subprocess.run(command, env=env, capture_output=True, text=True, errors="replace")
    text = proc.stdout + proc.stderr
    Path(log).parent.mkdir(parents=True, exist_ok=True)
    Path(log).write_text(" ".join(command) + "\n\n" + text, encoding="utf-8")
    if proc.returncode != 0 or "SCRIPT ERROR" in text or "ERROR REPORT" in text:
        raise MetadataError("execution", f"analyzeHeadless failed ({Path(log)})", log=str(log),
                            seconds=round(time.monotonic() - started, 1))
    return text


def saved(log_text):
    return "REPORT: Save succeeded" in log_text


def gpr_parts(gpr):
    gpr = Path(gpr)
    if gpr.suffix != ".gpr":
        raise MetadataError("invalid", f"{gpr}: a project is named by its .gpr path")
    return gpr.parent, gpr.stem


@contextlib.contextmanager
def project_lock(gpr):
    """One mutator per project: an exclusive lock beside the .gpr, plus Ghidra's own lock.

    flock where available (released if the process dies); elsewhere an O_EXCL file
    that a crashed run leaves behind and the error message names."""
    path = Path(str(gpr) + ".re_metadata.lock")
    path.parent.mkdir(parents=True, exist_ok=True)
    try:
        import fcntl
    except ImportError:
        fcntl = None
    if fcntl is not None:
        with path.open("w") as handle:
            try:
                fcntl.flock(handle, fcntl.LOCK_EX | fcntl.LOCK_NB)
            except OSError as exc:
                raise MetadataError("blocked", f"{gpr} is locked by another metadata mutator") from exc
            yield
        return
    try:
        fd = os.open(path, os.O_CREAT | os.O_EXCL | os.O_WRONLY)
    except FileExistsError as exc:
        raise MetadataError("blocked", f"{gpr} is locked ({path} exists; remove it only if no "
                            "metadata run is active)") from exc
    try:
        yield
    finally:
        os.close(fd)
        path.unlink(missing_ok=True)


def observe(gpr, program, request, out, *, log, ghidra=None, java=None):
    project_dir, name = gpr_parts(gpr)
    req = Path(out).with_suffix(".request.json")
    write_json(req, request)
    run_headless(project_dir, name, program=program, read_only=True, log=log, ghidra=ghidra, java=java,
                 post=[("export_metadata.java", ["observe", req.resolve(), Path(out).resolve()])])
    return read_json(out)


def apply_plan(gpr, program, plan_path, result_path, evidence_root, *, log, fail_after=None,
               ghidra=None, java=None):
    project_dir, name = gpr_parts(gpr)
    args = ["apply", Path(plan_path).resolve(), Path(evidence_root).resolve(), Path(result_path).resolve()]
    if fail_after is not None:
        args.append(f"fail-after={fail_after}")
    text = run_headless(project_dir, name, program=program, log=log, ghidra=ghidra, java=java,
                        post=[("apply_metadata.java", args)])
    return read_json(result_path), saved(text)


# ----------------------------------------------------------------- commands

def _work_dir(path):
    path = Path(path)
    path.mkdir(parents=True, exist_ok=True)
    return path


def cmd_validate(pkg_path, executable=None, update_digest=False, evidence_root=None):
    pkg = Package.load(pkg_path)
    if update_digest:
        pkg.manifest["metadata_sha256"] = pkg.digest()
        write_json(Path(pkg_path) / "manifest.json", pkg.manifest)
    report = validate(pkg, executable)
    if report["status"] == "ok":
        resolved = resolve(pkg, evidence_root)
        report["counts"].update({"conflicts": len(resolved["conflicts"]),
                                 "unsupported": len(resolved["unsupported"]),
                                 "excluded": len(resolved["excluded"]), "context": len(resolved["context"])})
        report.update(conflicts=resolved["conflicts"], unsupported=resolved["unsupported"],
                      excluded=resolved["excluded"])
        if resolved["conflicts"]:
            report["status"] = "blocked"
        elif resolved["unsupported"]:
            report["status"] = "unsupported"
    return report


def cmd_plan(pkg_path, gpr, program, out, *, evidence_root=None, work=None, ghidra=None, java=None,
             observation=None):
    pkg = Package.load(pkg_path)
    report = validate(pkg)
    if report["status"] != "ok":
        raise MetadataError("invalid", "package does not validate", errors=report["errors"])
    resolved = resolve(pkg, evidence_root)
    work = _work_dir(work or Path(out).parent)
    if observation is None:
        observation = observe(gpr, program, observation_request(resolved, pkg), work / "plan_observation.json",
                              log=work / "plan_observe.log", ghidra=ghidra, java=java)
    plan = build_plan(pkg, resolved, observation)
    write_json(out, plan)
    return plan


def cmd_apply(pkg_path, gpr, program, plan_path, receipt_path, *, evidence_root=None, fail_after=None,
              ghidra=None, java=None):
    pkg = Package.load(pkg_path)
    plan = read_json(plan_path)
    changed = check_plan_bindings(plan, pkg, evidence_root)
    receipt = {"schema": RECEIPT_SCHEMA, "command": "metadata-apply", "plan_sha256": plan.get("plan_sha256"),
               "metadata_sha256": plan.get("metadata_sha256"), "recipe_sha256": plan.get("recipe_sha256"),
               "inputs": plan.get("inputs"), "tools": tool_digests(),
               "operational": {"project": str(Path(gpr).resolve()), "program": program,
                               "started": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())}}
    if changed:
        receipt.update(status="blocked", reason="stale plan: inputs changed since planning", changed=changed)
        write_json(receipt_path, receipt)
        raise MetadataError("blocked", "stale plan: inputs changed since planning", changed=changed)
    if plan["status"] not in ("ready", "noop"):
        receipt.update(status=plan["status"], conflicts=plan["conflicts"], unsupported=plan["unsupported"])
        write_json(receipt_path, receipt)
        raise MetadataError(plan["status"] if plan["status"] in EXIT else "blocked",
                            f"plan status is {plan['status']}; nothing was applied")
    work = Path(receipt_path).parent
    with project_lock(gpr):
        result, ok_save = apply_plan(gpr, program, plan_path, work / (Path(receipt_path).stem + ".result.json"),
                                     pkg.evidence_root(evidence_root), log=work / (Path(receipt_path).stem + ".log"),
                                     fail_after=fail_after, ghidra=ghidra, java=java)
    receipt.update(result=result, save="succeeded" if ok_save else "failed",
                   log=str(work / (Path(receipt_path).stem + ".log")),
                   counts={"changed": result.get("changed", 0), "noop": len(plan["noops"]),
                           "conflicts": len(plan["conflicts"]), "unsupported": len(plan["unsupported"])},
                   before_sha256=result.get("before_sha256"), after_sha256=result.get("after_sha256"))
    status = {"committed": "ok", "noop": "noop"}.get(result.get("status"), "blocked")
    if result.get("status") == "rolled_back":
        status = "execution"
    if status in ("ok", "noop") and not ok_save:
        status = "execution"
        receipt["reason"] = "the transaction committed in memory but analyzeHeadless did not report a save"
    receipt["status"] = status
    write_json(receipt_path, receipt)
    if status not in ("ok", "noop"):
        raise MetadataError(status, f"apply {result.get('status')}: {result.get('error', receipt.get('reason'))}")
    return receipt


def cmd_compare(pkg_path, actual, out=None, evidence_root=None):
    pkg = Package.load(pkg_path)
    actual = Path(actual)
    obs = read_json(actual / "observation.json" if actual.is_dir() else actual)
    report = compare(resolve(pkg, evidence_root), obs)
    if out:
        write_json(out, report)
    return report


def cmd_export(gpr, program, pkg_path, scope_path, out_dir, *, ghidra=None, java=None):
    """Scoped observations -> proposal records (origin analysis, review proposed)."""
    scope = read_json(scope_path)
    pkg = Package.load(pkg_path) if pkg_path else None
    out_dir = _work_dir(out_dir)
    paths = [type_path(k) for k in scope.get("types", [])]
    request = {"functions": [{"entry_rva": e} for e in sorted(scope.get("functions", []))], "types": paths,
               "comments": [{"address_rva": c["address_rva"], "kind": c["kind"]} for c in scope.get("comments", [])]}
    obs = observe(gpr, program, request, out_dir / "observation.json", log=out_dir / "export.log",
                  ghidra=ghidra, java=java)
    want_exe = (scope.get("target") or {}).get("executable_sha256") or (pkg.manifest["target"]["executable_sha256"] if pkg else None)
    if want_exe and want_exe != obs["program"]["executable_sha256"]:
        raise MetadataError("blocked", "the program is not the scope's executable")
    unsupported, written = [], []
    ts = TypeSet()
    for key, path in zip(scope.get("types", []), paths):
        proj = (obs["types"].get(path) or {}).get("projection")
        if proj is None:
            unsupported.append({"artifact": f"type {key}", "reason": "absent from the program"})
            continue
        if proj["kind"] not in ("struct", "enum", "typedef") or any(f.get("bitfield") for f in proj.get("fields", [])):
            unsupported.append({"artifact": f"type {key}", "reason": f"{proj['kind']} is outside the supported subset"})
            continue
        ts.types[key] = {"representation": proj["kind"], "layout": {"size": proj.get("size")}}
    observed_source = {}
    for entry in sorted(scope.get("functions", [])):
        o = obs["functions"][entry]
        if not o["exists"]:
            unsupported.append({"artifact": f"function {entry}", "reason": "no function at entry"})
            continue
        prov = {"origin": "analysis", "status": "observation", "review": "proposed"}
        sig = _sig_record(o["signature"])
        why = signature_problems(sig, ts)
        rec = {"schema": SCHEMA, "kind": "function", "entry_rva": entry,
               "observed_name": {"ghidra_name": o["name"]["name"], "namespace": o["name"]["namespace"],
                                 "provenance": dict(prov, observed_source=o["name_source"])},
               "body": {"ranges": o["body"], "provenance": dict(prov, observed_source="analysis")},
               "signature": dict(sig, provenance=dict(prov, observed_source=o["signature_source"]))}
        if why:
            unsupported.append({"artifact": f"function {entry} signature", "reason": "; ".join(why)})
        observed_source[entry] = o["name_source"]
        write_json(out_dir / "functions" / f"{entry}.json", rec)
        written.append(f"functions/{entry}.json")
    for key, path in zip(scope.get("types", []), paths):
        proj = (obs["types"].get(path) or {}).get("projection")
        if key not in ts.types:
            continue
        rec = {"schema": SCHEMA, "kind": "type", "key": key, "representation": proj["kind"],
               "observed_projection": proj, "provenance": {"origin": "analysis", "status": "observation",
                                                           "review": "proposed"}}
        write_json(out_dir / type_record_name(key), rec)
        written.append(type_record_name(key))
    for c in scope.get("comments", []):
        text = obs["comments"].get(f"{c['address_rva']}:{c['kind']}")
        rec = {"schema": SCHEMA, "kind": "observed_comment", "address_rva": c["address_rva"],
               "comment_kind": c["kind"], "text": text,
               "provenance": {"origin": "analysis", "status": "observation", "review": "proposed"}}
        write_json(out_dir / "comments" / f"{c['address_rva']}-{c['kind']}.json", rec)
        written.append(f"comments/{c['address_rva']}-{c['kind']}.json")
    report = {"status": "partial" if unsupported else "ok", "written": written, "unsupported": unsupported,
              "observation_sha256": digest({k: obs[k] for k in ("functions", "types", "comments")}),
              "program": obs["program"]}
    write_json(out_dir / "coverage.json", report)
    return report


def _sig_record(proj):
    """An observed signature projection in record spelling (named paths back to keys)."""
    def ref(r):
        if "ptr" in r:
            return {"ptr": ref(r["ptr"])}
        if "array" in r:
            return {"array": ref(r["array"]), "count": r["count"]}
        if "named" in r:
            return {"named": "::".join(r["named"][len(TYPE_ROOT) + 1:].split("/"))}
        return dict(r)
    return {"convention": proj["convention"], "variadic": proj["variadic"], "storage_mode": proj["storage_mode"],
            "return": {"type": ref(proj["return"]["type"]), "storage": proj["return"]["storage"]},
            "params": [{"name": p["name"], "type": ref(p["type"]), "storage": p["storage"]} for p in proj["params"]],
            "auto_params": proj["auto_params"]}


def cmd_rebuild(pkg_path, executable, gpr, program, receipt_path, *, evidence_root=None, ghidra=None,
                java=None, refdb_out=None, max_cpu=None):
    """Import, analyse, baseline, plan, apply, reopen, compare, re-apply, export refdb.

    Every step lands in the receipt as passed / failed / blocked / not_run."""
    started = time.monotonic()
    work = _work_dir(Path(receipt_path).parent / (Path(receipt_path).stem + ".work"))
    steps, receipt, launches = [], {"schema": RECEIPT_SCHEMA, "command": "metadata-rebuild"}, [0]
    names = ["validate", "new_project", "import_analyse_baseline", "recipe_check", "plan_apply", "reopen_observe",
             "compare", "second_apply", "refdb_export_queries"]

    def step(name, status, **detail):
        steps.append(dict({"step": name, "status": status}, **detail))

    def finish(status):
        for n in names:
            if n not in {s["step"] for s in steps}:
                step(n, "not_run")
        receipt.update(status=status, steps=steps, ghidra_launches=launches[0],
                       seconds=round(time.monotonic() - started, 1))
        write_json(receipt_path, receipt)
        return receipt

    def headless(**kw):
        launches[0] += 1
        return run_headless(ghidra=ghidra, java=java, **kw)

    pkg = Package.load(pkg_path)
    try:
        env = ghidra_versions(ghidra_refdb.ghidra_home(ghidra), ghidra_refdb.java_home(java))
    except SystemExit as exc:
        receipt["environment_error"] = str(exc)
        step("validate", "blocked", reason=str(exc))
        return finish("environment")
    recipe = pkg.manifest.get("recipe", {})
    receipt.update(package_id=pkg.manifest.get("package_id"), metadata_sha256=pkg.digest(),
                   recipe_sha256=pkg.recipe_digest(), tools=tool_digests(), environment=env,
                   inputs={i["path"]: i["sha256"] for i in pkg.manifest.get("inputs", [])},
                   operational={"executable": str(Path(executable).resolve()), "project": str(Path(gpr).resolve()),
                                "started": time.strftime("%Y-%m-%dT%H:%M:%SZ", time.gmtime())})
    report = validate(pkg, executable)
    env_problems = [f"{k} {env.get(k)} != recipe {recipe.get(k)}" for k in ("ghidra_version", "ghidra_revision",
                                                                             "java_version")
                    if recipe.get(k) and env.get(k) != recipe.get(k)]
    if report["status"] != "ok" or env_problems:
        step("validate", "failed", errors=report["errors"] + env_problems)
        return finish("environment" if env_problems and report["status"] == "ok" else "invalid")
    resolved = resolve(pkg, evidence_root)
    step("validate", "passed", executable_sha256=pkg.manifest["target"]["executable_sha256"],
         conflicts=resolved["conflicts"], unsupported=resolved["unsupported"], excluded=resolved["excluded"])
    project_dir, name = gpr_parts(gpr)
    if Path(gpr).exists() or (project_dir / f"{name}.rep").exists():
        step("new_project", "failed", reason=f"{gpr} already exists: a rebuild needs an unused path")
        return finish("invalid")
    step("new_project", "passed", project=str(Path(gpr).resolve()))
    request = observation_request(resolved, pkg)
    write_json(work / "request.json", request)
    write_json(work / "binding.json", {"executable_sha256": pkg.manifest["target"]["executable_sha256"],
                                       "metadata_sha256": pkg.digest(), "recipe_sha256": pkg.recipe_digest()})
    t = pkg.manifest["target"]
    import_args = ["-processor", t["language_id"], "-cspec", t["compiler_spec_id"], *recipe.get("import_args", [])]
    pre = [(s["script"], [ROOT / a if s.get("args_are_paths") else a for a in s.get("args", [])])
           for s in recipe.get("pre_scripts", [])]
    with project_lock(gpr):
        try:
            t0 = time.monotonic()
            text = headless(project_dir=project_dir, project_name=name, import_path=executable,
                            import_args=import_args, analysis=recipe.get("analysis", {}).get("mode", "auto") == "auto",
                            pre=pre, max_cpu=max_cpu, log=work / "1_import.log",
                            post=[("export_metadata.java", ["baseline", (work / "request.json").resolve(),
                                                            (work / "baseline.json").resolve(),
                                                            (work / "binding.json").resolve()])])
            baseline_obs = read_json(work / "baseline.json")
            step("import_analyse_baseline", "passed" if saved(text) else "failed", log=str(work / "1_import.log"),
                 seconds=round(time.monotonic() - t0, 1), saved=saved(text),
                 baseline_sha256=digest(baseline_obs["baseline"]))
            if not saved(text):
                return finish("execution")
            want = pkg.records.get(recipe.get("analysis", {}).get("effective_options", ""))
            have = baseline_obs["analysis_options"]
            if want is None:
                step("recipe_check", "failed", reason="the recipe records no effective analyzer options",
                     actual_sha256=digest(have))
                return finish("invalid")
            diff = sorted(k for k in set(want) | set(have) if want.get(k) != have.get(k))
            if diff:
                step("recipe_check", "failed", reason="effective analyzer options differ from the recipe",
                     differing=diff[:50])
                return finish("environment")
            program_identity = baseline_obs["program"]
            step("recipe_check", "passed", analysis_options_sha256=digest(have), program=program_identity)
            t0 = time.monotonic()
            plan = build_plan(pkg, resolved, baseline_obs)
            write_json(work / "plan1.json", plan)
            if plan["status"] not in ("ready", "noop"):
                step("plan_apply", "blocked", plan=str(work / "plan1.json"), conflicts=plan["conflicts"],
                     unsupported=plan["unsupported"])
                return finish(plan["status"])
            launches[0] += 1
            result, ok_save = apply_plan(gpr, program, work / "plan1.json", work / "apply1.json",
                                         pkg.evidence_root(evidence_root), log=work / "2_apply.log",
                                         ghidra=ghidra, java=java)
            good = result.get("status") in ("committed", "noop") and ok_save
            step("plan_apply", "passed" if good else "failed", plan_sha256=plan["plan_sha256"],
                 operations=len(plan["operations"]), noops=len(plan["noops"]), result=result, saved=ok_save,
                 seconds=round(time.monotonic() - t0, 1), log=str(work / "2_apply.log"))
            if not good:
                return finish("execution")
            launches[0] += 1
            obs = observe(gpr, program, request, work / "observation.json", log=work / "3_observe.log",
                          ghidra=ghidra, java=java)
            step("reopen_observe", "passed", observation_sha256=digest({k: obs[k] for k in ("functions", "types", "comments")}),
                 log=str(work / "3_observe.log"))
            comparison = compare(resolved, obs)
            write_json(work / "comparison.json", comparison)
            step("compare", "passed" if comparison["status"] == "pass" else "failed", counts=comparison["counts"],
                 compared_sha256=comparison["compared_sha256"], report=str(work / "comparison.json"),
                 failures=[f for f in comparison["fields"] if f["result"] != "pass"])
            plan2 = build_plan(pkg, resolved, obs)
            write_json(work / "plan2.json", plan2)
            launches[0] += 1
            result2, ok_save2 = apply_plan(gpr, program, work / "plan2.json", work / "apply2.json",
                                           pkg.evidence_root(evidence_root), log=work / "4_reapply.log",
                                           ghidra=ghidra, java=java)
            zero = (plan2["status"] == "noop" and not plan2["operations"] and result2.get("changed") == 0
                    and result2.get("before_sha256") == result2.get("after_sha256")
                    and result2.get("status") == "noop")
            step("second_apply", "passed" if zero else "failed", plan_status=plan2["status"],
                 operations=len(plan2["operations"]), noops=len(plan2["noops"]), result=result2,
                 log=str(work / "4_reapply.log"))
            t0 = time.monotonic()
            launches[0] += 1
            out_db = Path(refdb_out or work / f"{program}.sqlite")
            try:
                meta = ghidra_refdb.export(gpr, program, out_db, ghidra=ghidra, java=java)
            except SystemExit as exc:
                raise MetadataError("execution", f"refdb export failed: {exc}") from exc
            db = ghidra_refdb.connect(out_db)
            queries = []
            for entry, fn in sorted(resolved["functions"].items()):
                rows = ghidra_refdb.fn(db, entry)
                queries.append({"query": f"fn {entry}", "rows": rows})
                if "body" in fn:
                    for s, e in fn["body"]["desired"]["body"]:
                        last = rva_text(int(e, 16) - 1)
                        queries.append({"query": f"fn {last} (final byte)", "rows": ghidra_refdb.fn(db, last)})
                        queries.append({"query": f"fn {e} (end-exclusive)", "rows": ghidra_refdb.fn(db, e)})
                queries.append({"query": f"callers {entry}", "rows": ghidra_refdb.callers(db, entry)})
            for path in sorted(resolved["types"]):
                queries.append({"query": f"type {path}", "rows": ghidra_refdb.type_(db, path)})
            write_json(work / "refdb_queries.json", queries)
            checks = _refdb_checks(resolved, db)
            step("refdb_export_queries", "passed" if not checks else "failed", db=str(out_db),
                 content_sha256=meta["content_sha256"], schema_version=meta["schema_version"],
                 queries=str(work / "refdb_queries.json"), problems=checks,
                 seconds=round(time.monotonic() - t0, 1))
        except MetadataError as exc:
            current = next((n for n in names if n not in {s["step"] for s in steps}), "receipt")
            step(current, "failed", reason=str(exc), **exc.details)
            return finish(exc.category)
    receipt["exclusions"] = resolved["excluded"]
    receipt["unsupported"] = resolved["unsupported"]
    failed = [s for s in steps if s["status"] != "passed"]
    return finish("ok" if not failed else "mismatch")


def _refdb_checks(resolved, db):
    """Exact-range expectations the rebuilt refdb must answer for the replayed bodies."""
    problems = []
    for entry, fn in sorted(resolved["functions"].items()):
        rows = ghidra_refdb.fn(db, entry)
        if not rows or rows[0]["rva"].lower() != entry:
            problems.append(f"fn {entry}: exact entry lookup failed")
        if "body" not in fn:
            continue
        ranges = fn["body"]["desired"]["body"]
        for i, (s, e) in enumerate(ranges):
            for probe in (s, rva_text(int(e, 16) - 1)):
                got = ghidra_refdb.fn(db, probe)
                if not got or got[0]["rva"].lower() != entry or got[0].get("containment") != "exact":
                    problems.append(f"fn {probe}: expected exact containment in {entry}, got {got[:1]}")
            if i + 1 < len(ranges):
                gap = rva_text(int(e, 16))
                got = ghidra_refdb.fn(db, gap)
                if got and got[0]["rva"].lower() == entry:
                    problems.append(f"fn {gap}: a gap address resolved to {entry}")
        end = ranges[-1][1]
        got = ghidra_refdb.fn(db, end)
        if got and got[0]["rva"].lower() == entry:
            problems.append(f"fn {end}: the end-exclusive address resolved to {entry}")
    return problems


# ----------------------------------------------------------------- bound name sync

def name_sync_package(db, reverse, out_dir, target):
    """A metadata package holding every sync-plan rename as an evidence-bound name record.

    It replaces the unbound TSV plans the removed apply_names.java applied unchecked."""
    root = Path(reverse).resolve().parent
    records = {}
    for rva, have, name, tier in ghidra_refdb.sync_plan(db, reverse):
        entry = rva_text(int(rva, 16))
        row = next(r for r in evidence_rows(root, tier_file(tier))
                   if r.get(ghidra_refdb.TIER_RVA[tier]) and int(r[ghidra_refdb.TIER_RVA[tier]], 16) == int(rva, 16)
                   and r.get("name") == name and ghidra_refdb.admits(tier, r))
        ns, base = ghidra_name(name)
        records[f"functions/{entry}.json"] = {
            "schema": SCHEMA, "kind": "function", "entry_rva": entry,
            "name": {"raw": name, "namespace": ns, "ghidra_name": base,
                     "provenance": {"origin": "target", "status": "supported", "review": "accepted",
                                    "identity_tier": tier, "evidence_refs": [evidence_ref(tier, row)],
                                    "observed_source": None}}}
    manifest = {"schema": SCHEMA, "package_id": "name-sync", "target": target,
                "recipe": {"note": "name sync against an existing project; no rebuild recipe"},
                "capabilities": ["names"], "inputs": [], "evidence_root": rel(root)}
    pkg = Package(out_dir, manifest, records)
    pkg.manifest["metadata_sha256"] = pkg.digest()
    if Path(out_dir).exists():
        shutil.rmtree(out_dir)
    pkg.write()
    return pkg


def cmd_record_recipe(pkg_path, executable, scratch, *, ghidra=None, java=None, max_cpu=None):
    """Record the effective analyzer options and tool versions of an actual import.

    Imports the executable into a new scratch project with the manifest's language,
    compiler spec, import arguments and pre-scripts, then writes what Ghidra really
    used into recipe/analysis_options.json and the manifest's recipe. Review the
    diff: this changes the recipe every later rebuild is checked against."""
    pkg = Package.load(pkg_path)
    t = pkg.manifest["target"]
    if file_sha256(executable) != t["executable_sha256"]:
        raise MetadataError("invalid", "executable does not match the manifest")
    gpr = Path(scratch) / "recipe.gpr"
    if gpr.exists():
        raise MetadataError("invalid", f"{gpr} exists: use an empty scratch directory")
    recipe = pkg.manifest.setdefault("recipe", {})
    request = {"functions": [], "types": [], "comments": []}
    write_json(Path(scratch) / "request.json", request)
    pre = [(s["script"], [ROOT / a if s.get("args_are_paths") else a for a in s.get("args", [])])
           for s in recipe.get("pre_scripts", [])]
    run_headless(Path(scratch), "recipe", import_path=executable, log=Path(scratch) / "import.log",
                 import_args=["-processor", t["language_id"], "-cspec", t["compiler_spec_id"],
                              *recipe.get("import_args", [])],
                 analysis=recipe.get("analysis", {}).get("mode", "auto") == "auto", pre=pre, max_cpu=max_cpu,
                 post=[("export_metadata.java", ["observe", (Path(scratch) / "request.json").resolve(),
                                                 (Path(scratch) / "observation.json").resolve()])],
                 ghidra=ghidra, java=java)
    obs = read_json(Path(scratch) / "observation.json")
    env = ghidra_versions(ghidra_refdb.ghidra_home(ghidra), ghidra_refdb.java_home(java))
    recipe.update({k: env[k] for k in ("ghidra_version", "ghidra_revision", "java_version")})
    recipe.setdefault("analysis", {"mode": "auto"})["effective_options"] = "recipe/analysis_options.json"
    pkg.records["recipe/analysis_options.json"] = obs["analysis_options"]
    pkg.manifest["metadata_sha256"] = pkg.digest()
    pkg.write(pkg_path)
    return {"status": "ok", "analysis_options_sha256": digest(obs["analysis_options"]),
            "options": len(obs["analysis_options"]), "environment": env, "program": obs["program"]}
