#!/usr/bin/env python3
"""Commit gate for code identity: what staged code binds to, not only its bytes.

The byte gate proves a call's displacement reproduces retail; it cannot see
that the name called is defined in the tree by different code, or by several
objects, so the linked image runs something else (research 20, 29). This gate,
on the rows of every staged or delta source (after the byte gate built them):

  1. every REL32/DIR32 reference into retail .text binds to a symbol in its
     target's allowed set (allowed_symbols.py: owner row, own label or EH
     funclet, certified fold, or an undefined name the tool aliases to the
     owner). Other bindings are keyed (source, row, symbol, target, class);
  2. no name the staged objects define is a new duplicate definition or a new
     divergent COMDAT whose kept copy is not retail's (dup_defs.py);
  3. an added `/alternatename:A=B` pragma must say what the tool would emit:
     A is referenced at one retail address and B owns it. Only the tool
     decides an alias (allowed_symbols.py --alternatenames); a hand-written
     pragma that binds A elsewhere is refused;
  4. reverse/name_tiers.csv, when staged, equals what the tool writes;
  5. the baselines only shrink against HEAD.

Keys already present are debt in reverse/code_identity_baseline.tsv and
reverse/dup_defs_baseline.tsv, shrink-only. The register starts in shadow mode
(`# mode: shadow` in code_identity_baseline.tsv): findings print, the commit
passes. `# mode: enforce` refuses a commit with a finding outside the
registers; the mode is read from the STAGED register, and enforce never goes
back to shadow (refused in either mode).

A shadow register drifts (findings it never refused). `--reseed` rewrites it
from the whole ledger, adding keys as well as dropping them, only while the
committed register is in shadow, and only from a complete tree: every matched
row's object must exist and be current (build.compile_is_current), since a
missing object scans as no findings at all. `--reseed --mode enforce` is the
flip; the gate accepts a register that grew, or flipped, only while HEAD's is
in shadow and only when both staged registers are exactly what a complete
scan of the staged tree writes (nothing the scan reads unstaged, every object
current), so the reseed and the flip land as ONE commit (`Verifier-Change:
code-identity-reseed <why>`). Once enforced it only shrinks. A deleted
register, a downgrade and an unverified reseed are refused in either mode.

  python3 tools/code_identity_gate.py --staged          the pre-commit hook
  python3 tools/code_identity_gate.py --full            whole ledger, report new keys
  python3 tools/code_identity_gate.py --write-baseline  (shrink-only once it exists)
  python3 tools/code_identity_gate.py --reseed [--mode enforce]   (shadow only; see above)
"""
import argparse
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(ROOT / "tools"))
import allowed_symbols as allowed  # noqa: E402
import dup_defs  # noqa: E402

BASELINE = ROOT / "reverse" / "code_identity_baseline.tsv"
HEADER = ("# Wrong code bindings, keyed source<TAB>row<TAB>symbol<TAB>retail target<TAB>class.\n"
          "# Shrink-only: written by tools/code_identity_gate.py --write-baseline; a line leaves\n"
          "# only by `tools/repair_queue.py retire identity SOURCE` (the pre-commit hook refuses a\n"
          "# hand deletion), never added. See tools/allowed_symbols.py for the classes.\n")


def git(*args):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True).stdout


def read_register(text):
    keys, mode = set(), "shadow"
    for line in text.splitlines():
        if line.startswith("# mode:"):
            mode = line.split(":", 1)[1].strip()
        elif line.strip() and not line.startswith("#"):
            keys.add(line.rstrip("\n"))
    return keys, mode


def dup_keys(text):
    return {line for line in text.splitlines() if line.strip() and not line.startswith("#")}


def show(spec):
    """Text of a git object spec (`HEAD:path`, `:path`), or None when it does not exist."""
    got = subprocess.run(["git", "show", spec], cwd=ROOT, capture_output=True, text=True,
                         encoding="utf-8", errors="replace")
    return got.stdout if got.returncode == 0 else None


def registers(staged):
    """(register text, dup_defs text, HEAD's register text or None): what the commit holds --
    the index when STAGED, else the working tree -- and what it is judged against."""
    def rel(path):
        return path.relative_to(ROOT).as_posix()
    if staged:
        reg, dup = show(":" + rel(BASELINE)), show(":" + rel(dup_defs.BASELINE))
    else:
        reg = BASELINE.read_text(encoding="utf-8") if BASELINE.exists() else None
        dup = dup_defs.BASELINE.read_text(encoding="utf-8") if dup_defs.BASELINE.exists() else None
    return reg or "", dup or "", show("HEAD:" + rel(BASELINE))


def staged_sources():
    """(sources to scan, every staged path): the paths include deletions, so a deleted
    register is seen (and refused) rather than read as an empty shadow one."""
    names = git("diff", "--cached", "--name-only", "--no-renames").split()
    live = set(git("diff", "--cached", "--name-only", "--no-renames", "--diff-filter=ACM").split())
    out = {p for p in live if p.startswith("Code/") and p.endswith((".cpp", ".c"))}
    delta = subprocess.run([sys.executable, str(ROOT / "tools" / "delta_sources.py"), "--staged"], cwd=ROOT,
                           capture_output=True, text=True).stdout.split()
    return sorted(out | set(delta)), names


def added_alternatenames():
    """[(path, alias, target)] on lines the staged diff adds."""
    out = []
    path = None
    for line in git("diff", "--cached", "-U0", "--", "Code", "reference/shims").splitlines():
        if line.startswith("+++ "):
            path = line[6:] if line.startswith("+++ b/") else None
        elif line.startswith("+") and path:
            for m in allowed.ALTERNATENAME.finditer(allowed.join_linker_literals(line[1:])):
                out.append((path, m.group(1), m.group(2)))
    return out


def check(sources, staged_names, *, full=False, staged=False, notes=None):
    """(problems, mode, seconds, rows, found) for the given sources (every matched row when
    full). The registers are the index's when STAGED; NOTES (a list) collects what is said
    but not refused."""
    t0 = time.time()
    notes = [] if notes is None else notes
    ident, rows = allowed.load(None if full else sources or ["<none>"])
    found = allowed.scan(ident, rows)
    reg_text, dup_text, head_text = registers(staged)
    base, mode = read_register(reg_text)
    head_mode = read_register(head_text)[1] if head_text is not None else "shadow"
    problems, hard = [], False               # hard: refused whatever the mode (a register's integrity)
    if head_mode == "enforce" and mode != "enforce":
        problems.append(f"{BASELINE.relative_to(ROOT).as_posix()}: '# mode: enforce' may not go back to "
                        f"'{mode}'")
        hard = True
    for reg in (BASELINE, dup_defs.BASELINE):
        rel = reg.relative_to(ROOT).as_posix()
        if staged and rel in staged_names and show(f":{rel}") is None and show(f"HEAD:{rel}") is not None:
            problems.append(f"{rel} deleted; a register shrinks line by line, it never disappears")
            hard = True
    keys = {allowed.key(rec) for rec in found if rec[5] in allowed.WRONG}
    for k in sorted(keys - base):
        problems.append("binding: " + k.replace("\t", " | "))
    # 2) duplicates / divergent COMDATs among names these objects define
    # A .lib source names no object by itself: row_object needs a row's member=
    # note to pick the extracted member, which load() put in ident.defs under the
    # same path. Its rows (in `rows` unless full) scope their members; only
    # non-library sources are scoped by path alone.
    objs = {str(allowed.row_object(r)) for r in rows} | {
        str(allowed.row_object({"source": s})) for s in sources
        if not s.lower().endswith(allowed.build.LIB_SUFFIX)}
    names = {n for n, copies in ident.defs.items() if full or any(c[0] in objs for c in copies)}
    sub = {n: ident.defs[n] for n in names}
    dkeys = dup_defs.debt(dup_defs.analyse(rows if full else allowed.census.ledger(), sub, ident.truth))
    for k in sorted(dkeys - dup_keys(dup_text)):
        problems.append("definition: " + k.replace("\t", " | "))
    # 3) alternatename pragmas added by this commit
    alts = added_alternatenames() if not full else allowed.pragma_alternatenames(
        sorted({r["source"] for r in allowed.census.ledger()}))
    if alts:
        targets = {}
        everything = allowed.census.ledger()
        if not full:                         # only the rows whose objects reference an alias
            objs = set().union(*(ident.defs.referrers.get(a, set()) for _, a, _ in alts))
            everything = [r for r in everything if str(allowed.row_object(r)) in objs]
        for rec in allowed.scan(ident, everything):
            targets.setdefault(rec[3], set()).add(rec[4])
        for path, a, b in alts:
            verdict = allowed.judge_alternatename(ident, a, b, targets)
            if verdict != "ok":
                problems.append(f"alternatename ({verdict}): {path}: /alternatename:{a}={b}")
    # 4) name tiers are tool output
    if "reverse/name_tiers.csv" in staged_names:
        want = allowed.tiers_text(allowed.census.ledger())
        if (ROOT / "reverse" / "name_tiers.csv").read_text(encoding="utf-8") != want:
            problems.append("reverse/name_tiers.csv differs from tools/allowed_symbols.py --tiers")
    # 5) shrink-only registers. While HEAD's register is in shadow they may grow: that is the
    # reseed, which lands with the flip to enforce in one commit (--reseed --mode enforce), and
    # is taken only when the staged registers are exactly a complete scan of the staged tree.
    grew = False
    for reg, reader in ((BASELINE, lambda t: read_register(t)[0]), (dup_defs.BASELINE, dup_keys)):
        rel = reg.relative_to(ROOT).as_posix()
        if rel in staged_names:
            head = show(f"HEAD:{rel}")
            if head:
                new = reader(show(f":{rel}") or "")
                grown = new - reader(head)
                if grown and reg == BASELINE:   # a vanished unit's key carried to the unit holding its rows
                    import protected_paths
                    grown -= protected_paths.transferred("HEAD", ":", grown, reader(head) - new)
                if grown and head_mode == "enforce":
                    problems.append(f"{rel} grew by {len(grown)} key(s); an enforced register only shrinks "
                                    "(fix the binding instead; tools/allowed_symbols.py explains the classes)")
                elif grown:
                    grew = True
                    notes.append(f"{rel} grew by {len(grown)} key(s) while HEAD's register is in shadow "
                                 "(a reseed: tools/code_identity_gate.py --reseed)")
    if staged and head_mode != "enforce" and (grew or mode == "enforce"):
        bad = reseed_problems(reg_text, dup_text, mode)
        problems += bad
        hard = hard or bool(bad)
    return problems, "enforce" if hard else mode, time.time() - t0, len(rows), found


SCANNED = ("Code/", "reference/shims/", "reverse/")   # what a full scan reads from the work tree


def full_scan():
    """(binding keys, definition keys) of the whole ledger, from the current objects."""
    ident, rows = allowed.load()
    keys = {allowed.key(rec) for rec in allowed.scan(ident, rows) if rec[5] in allowed.WRONG}
    return keys, dup_defs.debt(dup_defs.analyse(rows, ident.defs, ident.truth))


def register_text(keys, mode):
    return HEADER + f"# mode: {mode}\n" + "".join(k + "\n" for k in sorted(keys))


def dup_text_of(dkeys):
    return dup_defs.HEADER + "".join(k + "\n" for k in sorted(dkeys))


def reseed_problems(reg_text, dup_text, mode):
    """Why staged registers that grow, or flip to enforce, while HEAD's is in shadow are not
    a reseed ([] when they are): the scan must read the staged tree (nothing it reads differs
    from the index), every matched row's object must be current (a missing object scans as no
    findings), and both registers must be exactly what --reseed writes from that scan."""
    what = "a register that grows, or flips to enforce, while HEAD's is in shadow is a reseed"
    dirty = [p for p in git("diff", "--name-only", "-z").split("\0") if p.startswith(SCANNED)]
    if dirty:
        return [f"{what}, and the scan reads the work tree: {len(dirty)} file(s) differ from the index "
                f"({', '.join(dirty[:5])}{', ...' if len(dirty) > 5 else ''}); stage or revert them"]
    bad = unreadable_sources(allowed.census.ledger())
    if bad:
        return [f"{what}, and {len(bad)} source(s) have no current object ({', '.join(sorted(bad)[:5])}); "
                "run ./build.sh, then --reseed"]
    keys, dkeys = full_scan()
    out = []
    for reg, staged_text, want in ((BASELINE, reg_text, register_text(keys, mode)),
                                   (dup_defs.BASELINE, dup_text, dup_text_of(dkeys))):
        if staged_text != want:
            out.append(f"{what}: {reg.relative_to(ROOT).as_posix()} is not exactly the staged tree's scan; "
                       "write both registers with tools/code_identity_gate.py --reseed")
    return out


def unreadable_sources(rows):
    """{source: why} for the compiled sources of matched rows whose objects a scan cannot read
    as current: a missing object scans as no references, so as no findings at all."""
    out, seen = {}, set()
    for row in rows:
        src = row["source"]
        if src in seen or src.lower().endswith((".asm", allowed.build.LIB_SUFFIX)):
            continue                         # row_refs reads neither (allowed_symbols.Identity)
        seen.add(src)
        obj = allowed.row_object(row)
        try:
            if not obj.exists():
                out[src] = "no object"
            elif not allowed.build.compile_is_current(ROOT / src, obj):
                out[src] = "stale object"
        except (OSError, ValueError, SystemExit) as error:
            out[src] = f"cannot judge ({error})"
    return out


def write_registers(keys, dkeys, mode):
    BASELINE.write_text(register_text(keys, mode), encoding="utf-8", newline="\n")
    if dkeys is not None:
        dup_defs.BASELINE.write_text(dup_text_of(dkeys), encoding="utf-8", newline="\n")


def reseed(mode=None):
    """Rewrite both registers from the whole ledger while they are in shadow (keys added and
    dropped), in MODE (None: keep shadow; 'enforce': the flip). Refused once the working or
    HEAD's register is enforced, and on an incomplete tree."""
    reg_text, dup_text, head_text = registers(False)
    old, current = read_register(reg_text)
    head_mode = read_register(head_text)[1] if head_text is not None else "shadow"
    if "enforce" in (current, head_mode):
        sys.exit("code identity: the register is enforced; it is never reseeded, only shrunk "
                 "(--write-baseline drops fixed keys)")
    t0 = time.time()
    bad = unreadable_sources(allowed.census.ledger())
    if bad:
        for src, why in sorted(bad.items())[:20]:
            print(f"  {why}: {src}", file=sys.stderr)
        sys.exit(f"code identity: {len(bad)} source(s) have no current object, and a scan reads them as "
                 "having no findings; run the full byte gate (./build.sh) first, then --reseed again")
    keys, dkeys = full_scan()
    olddup = dup_keys(dup_text)
    mode = mode or "shadow"
    write_registers(keys, dkeys, mode)
    print(f"code identity: reseeded (mode {mode}, {time.time() - t0:.0f}s): bindings {len(old)} -> {len(keys)} "
          f"(+{len(keys - old)} -{len(old - keys)}), definitions {len(olddup)} -> {len(dkeys)} "
          f"(+{len(dkeys - olddup)} -{len(olddup - dkeys)}); commit both registers, alone, with "
          "'Verifier-Change: code-identity-reseed <why>'")
    return 0


REFUSAL = """\
code identity: REFUSED -- {n} finding(s) above are outside reverse/code_identity_baseline.tsv and
reverse/dup_defs_baseline.tsv (enforced). Keys are never added to them; fix the finding:
  binding:       the reference binds a name the tree defines with other code, inside a row, at an
                 unowned address, or to a divergent copy. Call the owner row's own name (declare
                 it; for a global use reverse/data_ledger.csv's), or row the target; `python3
                 tools/allowed_symbols.py --source FILE` lists each reference with its class.
  definition:    a second definition of a name another object owns, or a divergent COMDAT whose kept
                 copy is not retail's: make the extra copy a declaration (`python3 tools/dup_defs.py
                 --candidates`) or make the copies agree.
  alternatename: write exactly the line `python3 tools/allowed_symbols.py --alternatenames` emits
                 (build/allowed_symbols/alternatename.txt), or none.
Debt the registers already list is not refused. A finding your change did not cause (the source is
untouched, HEAD shows it too) is a false reject: record it with `python3 tools/re_log.py record
<symbol> <rva> <size> blocked "false-reject code_identity_gate: <evidence> t=<min> model=<model>"`."""


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    ap.add_argument("--staged", action="store_true")
    ap.add_argument("--full", action="store_true")
    ap.add_argument("--write-baseline", action="store_true")
    ap.add_argument("--reseed", action="store_true", help="rewrite the SHADOW registers from the whole ledger")
    ap.add_argument("--mode", choices=("shadow", "enforce"), help="--reseed: the registers' mode (enforce: the flip)")
    args = ap.parse_args(argv)
    if args.mode and not args.reseed:
        ap.error("--mode goes with --reseed")
    if args.reseed:
        return reseed(args.mode)
    if args.write_baseline:
        ident, rows = allowed.load()
        keys = {allowed.key(rec) for rec in allowed.scan(ident, rows) if rec[5] in allowed.WRONG}
        base, mode = read_register(BASELINE.read_text(encoding="utf-8") if BASELINE.exists() else "")
        if base and keys - base:
            print(f"refusing to add {len(keys - base)} key(s); fix them instead", file=sys.stderr)
            keys &= base
        # A source whose object is missing or stale scanned as no findings: keep its keys, or the
        # next seat to touch it is refused for debt that was never fixed.
        unread = unreadable_sources(rows) if base else {}
        kept = {k for k in base - keys if k.split("\t", 1)[0] in unread}
        if kept:
            print(f"kept {len(kept)} key(s) of {len({k.split(chr(9), 1)[0] for k in kept})} source(s) with no "
                  "current object (build them to drop fixed keys)", file=sys.stderr)
        write_registers(keys | kept, None, mode)
        print("code identity baseline:", len(keys | kept))
        return 0
    if args.staged:
        sources, names = staged_sources()
        if not sources and not any(n in names for n in ("reverse/name_tiers.csv", "reverse/code_identity_baseline.tsv",
                                                         "reverse/dup_defs_baseline.tsv")):
            return 0
        # this hook line runs before the byte gate; compiling here leaves the
        # objects current, so the byte gate after it reuses them
        claimed = [r for r in allowed.census.ledger() if r["source"] in set(sources)]
        allowed.build.compile_rows(claimed, sorted({ROOT / r["source"] for r in claimed}))
    else:
        sources, names = [], []
    notes = []
    problems, mode, secs, nrows, _ = check(sources, names, full=args.full, staged=args.staged, notes=notes)
    for n in notes:
        print("  code identity: note: " + n, file=sys.stderr)
    for p in problems:
        print("  code identity: " + p, file=sys.stderr)
    print(f"code identity: {nrows} row(s), {len(problems)} new finding(s), {secs:.1f}s, mode {mode}", file=sys.stderr)
    if problems and mode == "enforce":
        print(REFUSAL.format(n=len(problems)), file=sys.stderr)
        return 1
    return 0


if __name__ == "__main__":
    sys.exit(main())
