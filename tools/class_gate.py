#!/usr/bin/env python3
"""Refuse new private copies of classes that have a shared header.

reverse/canonical_classes.csv names the shared header for a class once one
exists. From then on a unit that declares its own body for that class
re-creates the problem the header solved: its inline members are COMDATs
that differ from everyone else's, and members it leaves out are unresolved
when the unit links. This gate stops that at commit time.

Only what the commit introduces is checked. A staged unit is checked
against HEAD's copy of its own path or, for a staged rename (git's R status,
never a copy), of the path it was moved from: a unit that did not declare a
body for the class there (a new unit, a copy, or an edit that adds the
declaration) is refused. Units that already carry a private copy are the
reconciliation backlog (tools/class_views.py --class NAME), not a reason to
refuse unrelated edits to them or a pure move of them.

A unit that genuinely needs its own layout for a registered class (a
deliberately different codegen view, proved by its bytes) can say so on any
line:

    // class-gate: allow AsciiString <reason>

Usage:
  python3 tools/class_gate.py --staged     the commit gate
  python3 tools/class_gate.py FILE...      check files against HEAD
"""
import argparse
import re
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import class_views  # noqa: E402

ALLOW = re.compile(r"//\s*class-gate:\s*allow\s+(\w+)\s+\S")


def git_text(spec):
    result = subprocess.run(["git", "show", spec], cwd=ROOT, capture_output=True)
    if result.returncode != 0:
        return None
    return result.stdout.decode("latin-1")


def gated(path):
    """A path this gate vets: a unit under Code/, never a generated one."""
    return (path.startswith("Code/") and path.lower().endswith((".cpp", ".c"))
            and not path.startswith(("Code/gen_asm/", "Code/gen_small/")))


def staged_sources():
    # -z: a path with a space or a non-ASCII byte must not be split or quoted,
    # or git show fails on it and the unit would go unchecked.
    out = subprocess.run(["git", "diff", "--cached", "--name-only", "-z", "--diff-filter=ACMR", "--", "Code/"],
                         cwd=ROOT, capture_output=True).stdout.decode("utf-8", "surrogateescape")
    return [p for p in out.split("\0") if p and gated(p)]


def staged_renames():
    """{new path: old path} for each gated unit the index moves from a gated path.

    Only git's R status counts, at its own 50% default made explicit so that
    diff.renames cannot change it. Never -C or -B: a copy leaves the old path
    in the index, so it is a new private view and gets no credit, and HEAD's
    one copy of a path is credited to at most the one path that replaced it.
    Any git failure (no HEAD) gives {}: no credit, as before this existed.
    """
    result = subprocess.run(["git", "diff", "--cached", "-M50%", "--name-status", "-z", "--diff-filter=R",
                             "HEAD", "--", "Code/"], cwd=ROOT, capture_output=True)
    if result.returncode != 0:
        return {}
    fields = result.stdout.decode("utf-8", "surrogateescape").split("\0")
    renames = {}
    for i in range(0, len(fields) - 2, 3):
        status, old, new = fields[i:i + 3]
        if status.startswith("R") and gated(old) and gated(new):
            renames[new] = old
    return renames


def introduced(path, text, canon, renamed_from=None):
    """Registered classes `text` declares a body for that HEAD's copy of `path` did not.

    `renamed_from` is the HEAD path the index moves to `path`: its bodies are
    the unit's own, not new ones (a rename plus an edit equals a pure rename
    then the in-place edit, both admitted).
    """
    now = set(class_views.class_bodies(text)) & set(canon)
    if not now:
        return []
    had = set()
    # In a merge, a body either parent already carried is not introduced by
    # this commit: the other side's files are new to HEAD but not new code.
    for parent in ("HEAD", "MERGE_HEAD"):
        before = git_text(f"{parent}:{path}")
        if before:
            had |= set(class_views.class_bodies(before))
    if renamed_from:
        before = git_text(f"HEAD:{renamed_from}")
        if before:
            had |= set(class_views.class_bodies(before))
    allowed = set(ALLOW.findall(text))
    return sorted(now - had - allowed)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("--staged", action="store_true")
    parser.add_argument("files", nargs="*")
    args = parser.parse_args(argv)
    canon = class_views.canonical_classes()
    if not canon:
        return 0
    if args.staged:
        renames = staged_renames()
        checks = [(p, git_text(f":{p}"), renames.get(p)) for p in staged_sources()]
    else:
        checks = [(p, (ROOT / p).read_text(encoding="latin-1"), None) for p in args.files]
    bad = 0
    for path, text, renamed_from in checks:
        if text is None:
            # An unreadable staged unit is unchecked, not clean.
            print(f"  {path}: staged content unreadable; refusing rather than skipping it", file=sys.stderr)
            bad = 1
            continue
        for name in introduced(path, text, canon, renamed_from):
            print(f"  {path}: declares its own `{name}`; include {canon[name]} instead "
                  f"(or `// class-gate: allow {name} <reason>` for a proved codegen view)", file=sys.stderr)
            bad = 1
    return bad


if __name__ == "__main__":
    sys.exit(main())
