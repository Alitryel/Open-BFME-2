#!/usr/bin/env python3
"""Read-only Ghidra reference snapshots: one SQLite file per retail binary.

The shared analysed project (BFME1, BFME2 and RotWK in one Ghidra project) is the
best boundary/xref/type evidence the fleets have, but a Ghidra project cannot be
shared: it locks on open and every agent writing into it would make it drift.
So the project is exported once into immutable SQLite snapshots that any number
of agents read concurrently, and names flow back INTO the project only through
`sync-plan`, which admits evidence-tier names and nothing else.

  export   copy the project to a scratch dir (the owner's copy is never opened),
           run tools/ghidra/export_refdb.java headless, load the TSVs
  load     TSV directory -> SQLite (deterministic: sorted rows, content digest)
  verbs    fn, callers, callees, xrefs-to, xrefs-from, strings, switch, type
           -- the typed read interface agents call (JSON on stdout)
  sync-plan   evidence-tier ledger names that differ from the snapshot's names; with
              --project/--program and a .json --out, a bound, validated metadata plan
  sync-apply  apply a bound sync plan (tools/ghidra/apply_metadata.java); an unbound
              legacy TSV is refused with the command that regenerates it
  metadata-validate | -export | -plan | -apply | -compare | -rebuild | -recipe
              the curated RE metadata overlay (tools/re_metadata.py, docs/re_metadata.md)

Snapshots are not committed. They live at build/refdb/<program>.sqlite and are
published as release artifacts `refdb-<program>-<sha12>.sqlite` (docs/agent_tools.md).
A snapshot's `meta.content_sha256` covers every row, so two exports of the same
project state carry the same digest whatever SQLite version wrote the file.

Usage:
  python3 tools/ghidra_refdb.py export --project PATH.gpr --program NAME [--out DB]
  python3 tools/ghidra_refdb.py load TSV_DIR DB
  python3 tools/ghidra_refdb.py fn DB 0x0068AAB0
  python3 tools/ghidra_refdb.py callers DB 0x0068AAB0
  python3 tools/ghidra_refdb.py sync-plan DB [--out plan.tsv]
  python3 tools/ghidra_refdb.py sync-plan DB --project P.gpr --program NAME --out plan.json
  python3 tools/ghidra_refdb.py metadata-rebuild --metadata PKG --executable EXE \
      --project build/re_metadata/rebuilt.gpr --program NAME --receipt receipt.json
"""
import argparse
import csv
import glob
import hashlib
import json
import os
import re
import shutil
import sqlite3
import subprocess
import sys
import tempfile
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
REVERSE = (ROOT / "targets" / "game" / "reverse"
           if (ROOT / "targets" / "game" / "reverse").is_dir() else ROOT / "reverse")
DEFAULT_OUT = ROOT / "build" / "refdb"
SCHEMA_VERSION = 2
# Version 1 snapshots (no function_ranges table) stay readable: fn() then marks a
# containing-function answer as an unverified bounds candidate, never as exact.
SUPPORTED_VERSIONS = (1, 2)
RANGES = ("function_ranges", "function_ranges.tsv", ["func_rva", "start_rva", "end_rva_exclusive"],
          "func_rva, start_rva")

# (table, tsv, columns, primary order). Column order is the TSV field order.
TABLES = [
    ("functions", "functions.tsv",
     ["rva", "size", "max_rva", "ranges", "name", "source", "thunk", "convention", "signature"],
     "rva"),
    ("xrefs", "xrefs.tsv", ["from_rva", "to_rva", "kind", "operand", "from_func"],
     "from_rva, to_rva, kind, operand"),
    ("strings", "strings.tsv", ["rva", "length", "type", "value"], "rva"),
    ("data", "data.tsv", ["rva", "length", "type", "label"], "rva"),
    ("switches", "switches.tsv", ["func_rva", "jump_rva", "case_index", "target_rva"],
     "jump_rva, case_index"),
    ("types", "types.tsv", ["path", "ord", "kind", "length", "member", "member_type", "detail"],
     "path, ord, kind, member"),
]
INTEGER = {"size", "ranges", "thunk", "operand", "length", "case_index"}
RVA = {"rva", "max_rva", "from_rva", "to_rva", "from_func", "func_rva", "jump_rva", "target_rva",
       "start_rva", "end_rva_exclusive"}


# ----------------------------------------------------------------- load

def _unescape(text):
    return re.sub(r"\\(.)", lambda m: {"t": "\t", "n": "\n", "r": "\r"}.get(m[1], m[1]), text)


def _value(column, text):
    if column in RVA:
        if not text:
            return None
        value = int(text, 16)
        # A reference below the image base (absolute low addresses) is exported as a
        # negative 64-bit offset; keep it negative so it never aliases a real RVA.
        return value - (1 << 64) if value >= 1 << 63 else value
    if column in INTEGER:
        return int(text) if text else None
    return _unescape(text)


def _rows(path, columns):
    if not path.exists():
        return
    with path.open(encoding="utf-8", newline="") as handle:
        for line in handle:
            fields = line.rstrip("\r\n").split("\t")
            if len(fields) != len(columns):
                raise SystemExit(f"{path.name}: expected {len(columns)} fields, got "
                                 f"{len(fields)}: {line[:120]!r}")
            yield tuple(_value(c, f) for c, f in zip(columns, fields))


def load(tsv_dir, db_path):
    """Build the snapshot from export_refdb.java's TSVs. Returns the meta dict.

    An export with function_ranges.tsv makes a version-2 snapshot with exact body
    intervals (checked against each function's size and range count); one without
    it makes a version-1 snapshot, byte-compatible with what older tools wrote."""
    tsv_dir, db_path = Path(tsv_dir), Path(db_path)
    meta = {}
    with (tsv_dir / "meta.tsv").open(encoding="utf-8") as handle:
        for line in handle:
            key, _, value = line.rstrip("\r\n").partition("\t")
            meta[key] = _unescape(value)
    db_path.parent.mkdir(parents=True, exist_ok=True)
    partial = db_path.with_suffix(".partial")
    partial.unlink(missing_ok=True)
    digest = hashlib.sha256()
    exact = (tsv_dir / RANGES[1]).exists()
    db = sqlite3.connect(partial)
    try:
        for table, tsv, columns, order in TABLES + ([RANGES] if exact else []):
            db.execute(f"CREATE TABLE {table} ({', '.join(columns)})")
            rows = sorted(_rows(tsv_dir / tsv, columns),
                          key=lambda r: tuple((v is None, v if v is not None else 0) for v in r))
            db.executemany(f"INSERT INTO {table} VALUES ({', '.join('?' * len(columns))})", rows)
            digest.update(table.encode())
            for row in rows:
                digest.update(json.dumps(row).encode())
            meta[f"rows.{table}"] = str(len(rows))
        if exact:
            _check_ranges(db)
        meta["schema_version"] = str(SCHEMA_VERSION if exact else 1)
        meta["content_sha256"] = digest.hexdigest()
        db.execute("CREATE TABLE meta (key, value)")
        db.executemany("INSERT INTO meta VALUES (?, ?)", sorted(meta.items()))
        for statement in ("CREATE INDEX functions_name ON functions(name)",
                          "CREATE INDEX xrefs_to ON xrefs(to_rva)",
                          "CREATE INDEX xrefs_from ON xrefs(from_rva)",
                          "CREATE INDEX xrefs_func ON xrefs(from_func)",
                          "CREATE INDEX switches_func ON switches(func_rva)",
                          "CREATE INDEX types_path ON types(path)"):
            db.execute(statement)
        if exact:
            db.execute("CREATE INDEX function_ranges_start ON function_ranges(start_rva)")
        db.commit()
        db.execute("VACUUM")
    finally:
        db.close()
    os.replace(partial, db_path)
    return meta


def _check_ranges(db):
    """Every function's exact intervals must agree with its size and range count."""
    bad = db.execute(
        "SELECT f.rva FROM functions f LEFT JOIN (SELECT func_rva, COUNT(*) n, "
        "SUM(end_rva_exclusive - start_rva) total, MIN(start_rva) lo, MAX(end_rva_exclusive) hi "
        "FROM function_ranges GROUP BY func_rva) r ON r.func_rva = f.rva "
        "WHERE r.n IS NULL OR r.n != f.ranges OR r.total != f.size OR r.hi - 1 != f.max_rva "
        "LIMIT 5").fetchall()
    orphans = db.execute("SELECT func_rva FROM function_ranges WHERE func_rva NOT IN "
                         "(SELECT rva FROM functions) LIMIT 5").fetchall()
    if bad or orphans:
        raise SystemExit(f"function_ranges disagree with functions: {bad or orphans}")


# ----------------------------------------------------------------- export

def _find(env, patterns, what):
    if os.environ.get(env):
        return Path(os.environ[env])
    for pattern in patterns:
        found = sorted(glob.glob(str(pattern)))
        if found:
            return Path(found[-1])
    raise SystemExit(f"{what} not found: set {env} or unpack it under build/toolchains")


def ghidra_home(explicit=None):
    if explicit:
        return Path(explicit)
    return _find("GHIDRA_INSTALL_DIR", [ROOT / "build/toolchains/ghidra_*",
                                        ROOT / "inputs/toolchains/ghidra_*"], "Ghidra")


def java_home(explicit=None):
    if explicit:
        return Path(explicit)
    return _find("JAVA_HOME", [ROOT / "build/toolchains/jdk-*",
                               ROOT / "inputs/toolchains/jdk-*"], "JDK 21")


def headless(ghidra, java, project_dir, project_name, program, script, args, *, read_only):
    launcher = ghidra / "support" / ("analyzeHeadless.bat" if os.name == "nt" else "analyzeHeadless")
    command = [str(launcher), str(Path(project_dir).resolve()), project_name, "-process", program,
               "-noanalysis",
               "-scriptPath", str(ROOT / "tools" / "ghidra"), "-postScript", script, *map(str, args)]
    if read_only:
        command.insert(command.index("-noanalysis") + 1, "-readOnly")
    env = dict(os.environ, JAVA_HOME=str(java))
    proc = subprocess.run(command, env=env, capture_output=True, text=True, errors="replace")
    if proc.returncode != 0 or "SCRIPT ERROR" in proc.stdout or "ERROR REPORT" in proc.stdout:
        sys.stderr.write(proc.stdout[-4000:] + proc.stderr[-2000:])
        raise SystemExit(f"analyzeHeadless failed for {program} ({script})")
    return proc


def snapshot_project(gpr):
    """Copy <name>.gpr + <name>.rep into a fresh temp dir and return (dir, name).

    Ghidra takes a lock on the project it opens; the owner's project may be open
    in a GUI or an MCP server, so exports always read a private copy."""
    gpr = Path(gpr)
    work = Path(tempfile.mkdtemp(prefix="refdb-"))
    shutil.copy2(gpr, work / gpr.name)
    shutil.copytree(gpr.with_suffix(".rep"), work / (gpr.stem + ".rep"),
                    ignore=shutil.ignore_patterns("*.lock", "*.lock~"))
    return work, gpr.stem


def export(gpr, program, out=None, *, ghidra=None, java=None, copy=True, keep_tsv=None):
    ghidra, java = ghidra_home(ghidra), java_home(java)
    if copy:
        project_dir, name = snapshot_project(gpr)
    else:
        project_dir, name = Path(gpr).parent, Path(gpr).stem
    tsv = Path(keep_tsv) if keep_tsv else Path(tempfile.mkdtemp(prefix="refdb-tsv-"))
    try:
        headless(ghidra, java, project_dir, name, program, "export_refdb.java", [tsv],
                 read_only=True)
        meta = load(tsv, out or DEFAULT_OUT / f"{program}.sqlite")
    finally:
        if copy:
            shutil.rmtree(project_dir, ignore_errors=True)
        if not keep_tsv:
            shutil.rmtree(tsv, ignore_errors=True)
    return meta


# ----------------------------------------------------------------- verbs

def connect(db_path):
    path = Path(db_path)
    if not path.exists():
        raise SystemExit(f"{path}: no snapshot (python3 tools/ghidra_refdb.py export ...)")
    return sqlite3.connect(f"file:{path.as_posix()}?mode=ro", uri=True)


def schema_version(db):
    """The snapshot's declared schema version, checked against the tables it must have."""
    row = db.execute("SELECT value FROM meta WHERE key = 'schema_version'").fetchone()
    version = int(row[0]) if row else 1
    if version not in SUPPORTED_VERSIONS:
        raise SystemExit(f"refdb schema version {version} is newer than this tool ({SUPPORTED_VERSIONS})")
    has_ranges = db.execute("SELECT 1 FROM sqlite_master WHERE type = 'table' AND name = 'function_ranges'"
                            ).fetchone() is not None
    if version >= 2 and not has_ranges:
        raise SystemExit("refdb declares schema version 2 but has no function_ranges table")
    return version


def _dicts(cursor):
    names = [d[0] for d in cursor.description]
    return [{k: (f"{'-' if v < 0 else ''}0x{abs(v):08X}" if k in RVA and v is not None else v)
             for k, v in zip(names, row)} for row in cursor.fetchall()]


def parse_rva(text):
    return int(text, 16)


def fn(db, key):
    """The function at (or containing) an RVA, or every function with this name.

    Each row says how it was found in `containment`: `exact` (version 2: the RVA
    lies inside one of the function's recorded body intervals, listed in `body`),
    `entry` (the RVA is the function's entry), `bounds-candidate` (version 1 only:
    entry <= RVA <= max address, which a gap between body ranges also satisfies; not
    containment evidence) or `name`. A version-2 snapshot never reports a gap
    address or an end-exclusive address as contained."""
    if not re.fullmatch(r"(0x)?[0-9A-Fa-f]+", key):
        rows = _dicts(db.execute("SELECT * FROM functions WHERE name = ? ORDER BY rva", (key,)))
        return [dict(r, containment="name") for r in rows]
    rva = parse_rva(key)
    if schema_version(db) >= 2:
        rows = _dicts(db.execute(
            "SELECT f.* FROM function_ranges r JOIN functions f ON f.rva = r.func_rva "
            "WHERE r.start_rva <= ? AND r.end_rva_exclusive > ? ORDER BY f.rva", (rva, rva)))
        for row in rows:
            row["containment"] = "exact"
            row["body"] = [[f"0x{s:08X}", f"0x{e:08X}"] for s, e in db.execute(
                "SELECT start_rva, end_rva_exclusive FROM function_ranges WHERE func_rva = ? "
                "ORDER BY start_rva", (parse_rva(row["rva"]),))]
        if rows:
            return rows
        rows = _dicts(db.execute("SELECT * FROM functions WHERE rva = ?", (rva,)))
        return [dict(r, containment="entry") for r in rows]
    rows = _dicts(db.execute("SELECT * FROM functions WHERE rva = ?", (rva,)))
    if rows:
        return [dict(r, containment="entry") for r in rows]
    rows = _dicts(db.execute(
        "SELECT * FROM functions WHERE rva <= ? AND max_rva >= ? ORDER BY rva DESC LIMIT 1", (rva, rva)))
    return [dict(r, containment="bounds-candidate") for r in rows]


def callers(db, rva):
    return _dicts(db.execute(
        "SELECT DISTINCT x.from_func, f.name FROM xrefs x LEFT JOIN functions f ON f.rva = x.from_func "
        "WHERE x.to_rva = ? AND x.kind LIKE '%CALL%' ORDER BY x.from_func", (parse_rva(rva),)))


def callees(db, rva):
    return _dicts(db.execute(
        "SELECT DISTINCT x.to_rva, f.name FROM xrefs x LEFT JOIN functions f ON f.rva = x.to_rva "
        "WHERE x.from_func = ? AND x.kind LIKE '%CALL%' ORDER BY x.to_rva", (parse_rva(rva),)))


def xrefs_to(db, rva):
    return _dicts(db.execute("SELECT * FROM xrefs WHERE to_rva = ? ORDER BY from_rva",
                             (parse_rva(rva),)))


def xrefs_from(db, rva):
    """Every reference made from inside the function at this entry RVA."""
    return _dicts(db.execute("SELECT * FROM xrefs WHERE from_func = ? ORDER BY from_rva",
                             (parse_rva(rva),)))


def strings(db, rva):
    """Strings the function at this entry RVA references."""
    return _dicts(db.execute(
        "SELECT DISTINCT s.rva, s.value FROM xrefs x JOIN strings s ON s.rva = x.to_rva "
        "WHERE x.from_func = ? ORDER BY s.rva", (parse_rva(rva),)))


def switch(db, rva):
    return _dicts(db.execute(
        "SELECT jump_rva, case_index, target_rva FROM switches WHERE func_rva = ? "
        "ORDER BY jump_rva, case_index", (parse_rva(rva),)))


def type_(db, name):
    return _dicts(db.execute(
        "SELECT * FROM types WHERE path = ? OR path LIKE ? ORDER BY path, ord, kind, member",
        (name, f"%/{name}")))


VERBS = {"fn": fn, "callers": callers, "callees": callees, "xrefs-to": xrefs_to,
         "xrefs-from": xrefs_from, "strings": strings, "switch": switch, "type": type_}


# ----------------------------------------------------------------- name sync

PLACEHOLDER = re.compile(
    r"(?i)(?:^|[^A-Za-z])(?:fun|sub|thunk_fun|lab|dat|d|dup|uw|eh|tg|nullsub|loc|j)_[0-9a-f]{4,8}"
    r"|rva[0-9a-f]{4,8}|gen_?[0-9a-f]{3,8}|(?:^|[^a-z])bfme|[0-9A-F]{6,8}")


def placeholder(name):
    return bool(PLACEHOLDER.search(name))


def _csv(path):
    if not path.exists():
        return []
    with path.open(encoding="utf-8", newline="") as handle:
        return list(csv.DictReader(handle))


TIER_FILES = {"export": "exports.csv", "ilt": "functions.csv", "reloc": "reloc_names.csv"}
TIER_RVA = {"export": "rva", "ilt": "target_rva", "reloc": "target_rva"}


def admits(tier, row):
    """Whether one evidence row (a csv.DictReader dict) admits its name under `tier`.

    The single statement of the tier rules; evidence_names(), tools/re_metadata.py
    and its Java mirror (tools/ghidra/apply_metadata.java) all apply exactly this."""
    name = row.get("name")
    if not name or placeholder(name) or not row.get(TIER_RVA[tier]):
        return False
    if tier == "export":
        return row.get("kind") in ("code", "function", "func") and row.get("section", ".text") == ".text"
    if tier == "ilt":
        return row.get("status") == "matched" and "ilt-verified=" in (row.get("notes") or "")
    if tier == "reloc":
        return "identity=real" in (row.get("notes") or "")
    raise ValueError(f"unknown tier {tier}")


def evidence_names(reverse=None):
    """{rva: (name, tier)} for names the repo holds on evidence, not on assertion.

    Tiers, strongest first: `export` (the PE export table names it), `ilt` (the
    incremental-link-thunk oracle confirmed it; tools write `ilt-verified=` notes),
    `reloc` (a byte-true call site in matched code proved the mangled name,
    reverse/reloc_names.csv identity=real). A matched ledger row alone is NOT
    evidence: agents choose those names. Placeholders never sync.
    """
    reverse = Path(reverse or REVERSE)
    found = {}
    for tier in ("export", "ilt", "reloc"):
        for row in _csv(reverse / TIER_FILES[tier]):
            if admits(tier, row):
                found.setdefault(int(row[TIER_RVA[tier]], 16), (row["name"], tier))
    return found


MANGLED = re.compile(r"^\?(\?[0-9]|\?_[A-Z0-9])?([^@?]*)@((?:[^@?]+@)*)@")


def qualified(name):
    """'A::B::f' for a mangled '?f@B@A@@...' (ctors/dtors included), else the name.

    Ghidra stores demangled, qualified names; an evidence name that demangles to
    the name Ghidra already holds is not a rename."""
    m = MANGLED.match(name)
    if not m:
        return name
    special, base, scopes = m.groups()
    scopes = [s for s in scopes.split("@") if s][::-1]
    if special == "?0":
        base = (base or (scopes[-1] if scopes else "")) if not base else base
        scopes, base = scopes + [base], base
    elif special == "?1":
        scopes, base = scopes + [base], "~" + base
    elif special:
        return name
    return "::".join(scopes + [base])


def sync_plan(db, reverse=None):
    """Rows (rva, current, proposed, tier) where an evidence-tier name differs.

    Only entries of functions Ghidra already has are proposed, and only over a
    placeholder name unless the tier is `ilt`."""
    current = {rva: (name, source) for rva, name, source in
               db.execute("SELECT rva, name, source FROM functions")}
    plan = []
    for rva, (name, tier) in sorted(evidence_names(reverse).items()):
        if rva not in current:
            continue
        have, source = current[rva]
        if have == name or have == qualified(name):
            continue
        # New information only: a name Ghidra already holds from the export table or
        # its demangler is left alone (Ghidra stores it demangled, so the strings
        # differ). Only the ILT oracle may correct a name that is not a placeholder.
        if tier != "ilt" and not (source == "DEFAULT" or placeholder(have)):
            continue
        plan.append((f"0x{rva:08X}", have, name, tier))
    return plan


def write_plan(plan, out):
    with open(out, "w", encoding="utf-8", newline="") as handle:
        for row in plan:
            handle.write("\t".join(row) + "\n")


# ----------------------------------------------------------------- cli

def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__,
                                 formatter_class=argparse.RawDescriptionHelpFormatter)
    sub = ap.add_subparsers(dest="cmd", required=True)
    e = sub.add_parser("export")
    e.add_argument("--project", required=True, help="path to the analysed <name>.gpr")
    e.add_argument("--program", required=True, action="append",
                   help="program name inside the project (repeatable)")
    e.add_argument("--out-dir", default=str(DEFAULT_OUT))
    e.add_argument("--ghidra"), e.add_argument("--java")
    e.add_argument("--keep-tsv", help="keep the raw TSVs under this directory")
    lo = sub.add_parser("load")
    lo.add_argument("tsv_dir"), lo.add_argument("db")
    for verb in VERBS:
        v = sub.add_parser(verb)
        v.add_argument("db"), v.add_argument("key")
    sp = sub.add_parser("sync-plan")
    sp.add_argument("db"), sp.add_argument("--out"), sp.add_argument("--reverse")
    sp.add_argument("--project", help="bind the plan to this project's actual state (needs --program)")
    sp.add_argument("--program")
    sp.add_argument("--ghidra"), sp.add_argument("--java")
    sa = sub.add_parser("sync-apply")
    sa.add_argument("--project", required=True, help="the CANONICAL project, never a working copy")
    sa.add_argument("--program", required=True), sa.add_argument("--plan", required=True)
    sa.add_argument("--receipt")
    sa.add_argument("--ghidra"), sa.add_argument("--java")
    _metadata_parsers(sub)
    args = ap.parse_args(argv)
    if args.cmd.startswith("metadata-") or (args.cmd == "sync-plan" and args.project) \
            or args.cmd == "sync-apply":
        return _metadata_main(args)

    if args.cmd == "export":
        for program in args.program:
            keep = Path(args.keep_tsv) / program if args.keep_tsv else None
            meta = export(args.project, program, Path(args.out_dir) / f"{program}.sqlite",
                          ghidra=args.ghidra, java=args.java, keep_tsv=keep)
            print(f"{program}: {meta['rows.functions']} functions, {meta['rows.xrefs']} xrefs, "
                  f"content {meta['content_sha256'][:12]}")
    elif args.cmd == "load":
        meta = load(args.tsv_dir, args.db)
        print(json.dumps(meta, indent=2))
    elif args.cmd in VERBS:
        print(json.dumps(VERBS[args.cmd](connect(args.db), args.key), indent=2))
    elif args.cmd == "sync-plan":
        plan = sync_plan(connect(args.db), args.reverse)
        if args.out:
            write_plan(plan, args.out)
        tiers = {}
        for row in plan:
            tiers[row[3]] = tiers.get(row[3], 0) + 1
        print(json.dumps({"renames": len(plan), "by_tier": tiers}, indent=2))


def _metadata_parsers(sub):
    def common(p, project=True, metadata=True):
        if metadata:
            p.add_argument("--metadata", required=True, help="package directory (manifest.json)")
        if project:
            p.add_argument("--project", required=True, help="private project <name>.gpr")
            p.add_argument("--program", required=True, help="program name inside the project")
        p.add_argument("--evidence-root", help="directory holding reverse/*.csv (default: the manifest's)")
        p.add_argument("--ghidra"), p.add_argument("--java")
    v = sub.add_parser("metadata-validate", help="validate a package and its bound inputs")
    common(v, project=False)
    v.add_argument("--executable", help="also check the executable hash, image base and sections")
    v.add_argument("--update-digest", action="store_true", help="rewrite metadata_sha256 after review")
    e = sub.add_parser("metadata-export", help="scoped observations -> proposal records")
    common(e, metadata=False)
    e.add_argument("--metadata"), e.add_argument("--scope", required=True), e.add_argument("--out-dir", required=True)
    p = sub.add_parser("metadata-plan", help="read-only plan against a project's actual state")
    common(p)
    p.add_argument("--out", required=True)
    a = sub.add_parser("metadata-apply", help="apply a validated plan in one transaction")
    common(a)
    a.add_argument("--plan", required=True), a.add_argument("--receipt", required=True)
    a.add_argument("--fail-after", type=int, help=argparse.SUPPRESS)   # test hook: injected failure
    c = sub.add_parser("metadata-compare", help="compare an observation export with desired facts")
    common(c, project=False)
    c.add_argument("--actual", required=True), c.add_argument("--out")
    r = sub.add_parser("metadata-rebuild", help="fresh project: import, analyse, replay, compare, refdb")
    common(r)
    r.add_argument("--executable", required=True), r.add_argument("--receipt", required=True)
    r.add_argument("--refdb-out"), r.add_argument("--max-cpu", type=int)
    rr = sub.add_parser("metadata-recipe", help="record effective analyzer options from an actual import")
    common(rr, project=False)
    rr.add_argument("--executable", required=True), rr.add_argument("--scratch", required=True)
    rr.add_argument("--max-cpu", type=int)


def _metadata_main(args):
    """JSON summary on stdout, diagnostics on stderr, exit code by category (docs/re_metadata.md)."""
    import re_metadata as rm
    try:
        if args.cmd == "metadata-validate":
            out = rm.cmd_validate(args.metadata, args.executable, args.update_digest, args.evidence_root)
        elif args.cmd == "metadata-export":
            out = rm.cmd_export(args.project, args.program, args.metadata, args.scope, args.out_dir,
                                ghidra=args.ghidra, java=args.java)
        elif args.cmd == "metadata-plan":
            plan = rm.cmd_plan(args.metadata, args.project, args.program, args.out,
                               evidence_root=args.evidence_root, ghidra=args.ghidra, java=args.java)
            out = {k: plan[k] for k in ("status", "conflicts", "unsupported", "excluded", "plan_sha256")}
            out["counts"] = {"operations": len(plan["operations"]), "noops": len(plan["noops"]),
                             "conflicts": len(plan["conflicts"]), "unsupported": len(plan["unsupported"])}
            out["plan"] = args.out
        elif args.cmd == "metadata-apply":
            receipt = rm.cmd_apply(args.metadata, args.project, args.program, args.plan, args.receipt,
                                   evidence_root=args.evidence_root, fail_after=args.fail_after,
                                   ghidra=args.ghidra, java=args.java)
            out = {k: receipt.get(k) for k in ("status", "counts", "before_sha256", "after_sha256", "save")}
            out["receipt"] = args.receipt
        elif args.cmd == "metadata-compare":
            out = rm.cmd_compare(args.metadata, args.actual, args.out, args.evidence_root)
        elif args.cmd == "metadata-rebuild":
            receipt = rm.cmd_rebuild(args.metadata, args.executable, args.project, args.program, args.receipt,
                                     evidence_root=args.evidence_root, ghidra=args.ghidra, java=args.java,
                                     refdb_out=args.refdb_out, max_cpu=args.max_cpu)
            out = {"status": receipt["status"], "steps": {s["step"]: s["status"] for s in receipt["steps"]},
                   "receipt": args.receipt}
        elif args.cmd == "metadata-recipe":
            out = rm.cmd_record_recipe(args.metadata, args.executable, args.scratch,
                                       ghidra=args.ghidra, java=args.java, max_cpu=args.max_cpu)
        elif args.cmd == "sync-plan":
            if not args.out or not args.out.endswith(".json") or not args.program:
                raise rm.MetadataError("invalid", "a bound sync plan needs --project, --program and --out PLAN.json")
            db = connect(args.db)
            meta = dict(db.execute("SELECT key, value FROM meta"))
            reverse = Path(args.reverse or REVERSE)
            target = {"executable_sha256": meta.get("executable_sha256", "").lower(),
                      "image_base": meta.get("image_base", "").lower(), "address_space": "ram", "pointer_size": 4,
                      "language_id": meta.get("language", ""), "compiler_spec_id": meta.get("compiler_spec", "windows")}
            pkg_dir = Path(args.out).with_suffix(".package")
            pkg = rm.name_sync_package(db, reverse, pkg_dir, target)
            plan = rm.cmd_plan(pkg_dir, args.project, args.program, args.out, ghidra=args.ghidra, java=args.java)
            out = {"status": plan["status"], "renames": len(plan["operations"]), "package": str(pkg_dir),
                   "plan": args.out, "conflicts": plan["conflicts"][:20]}
        else:   # sync-apply
            if not args.plan.endswith(".json"):
                raise rm.MetadataError(
                    "invalid", "legacy unbound TSV plans are no longer applied: regenerate a bound plan with "
                    f"`python3 tools/ghidra_refdb.py sync-plan DB --project {args.project} --program "
                    f"{args.program} --out plan.json`, review it, then sync-apply --plan plan.json")
            pkg_dir = Path(args.plan).with_suffix(".package")
            receipt = rm.cmd_apply(pkg_dir, args.project, args.program, args.plan,
                                   args.receipt or str(Path(args.plan).with_suffix(".receipt.json")),
                                   ghidra=args.ghidra, java=args.java)
            out = {k: receipt.get(k) for k in ("status", "counts", "save")}
    except rm.MetadataError as exc:
        sys.stderr.write(f"{args.cmd}: {exc}\n")
        out = {"status": exc.category, "error": str(exc), **exc.details}
    print(json.dumps(out, indent=2, sort_keys=True))
    status = out.get("status")
    code = rm.EXIT.get(status, 0 if status in ("ok", "noop", "pass", "ready") else 1)
    if args.cmd == "metadata-plan" and status == "ready":
        code = 0
    if args.cmd == "metadata-export" and status == "partial":
        code = rm.EXIT["unsupported"]
    sys.exit(code)


if __name__ == "__main__":
    main()
