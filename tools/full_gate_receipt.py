#!/usr/bin/env python3
"""Carry a passed full gate to the rebased push that follows it (.githooks/pre-push).

WHY. A push whose range needs the full gate (a vendored, toolchain or unbounded
header change) spends 13-25 minutes byte-verifying every source. Master moves
meanwhile, git rejects the push, and the rebased push ran the whole gate again;
on 2026-10-12 one batch passed it ten times and never landed. The shared push
window that answered this (tools/push_lease.py) froze every other pusher for
the length of each full gate instead.

HOW. When the full gate passes for a commit C0, the hook records C0 here (in
the git common directory, so every worktree of the clone sees it). A later push
of C1 that would need the full gate asks `find C1`: a recorded C0 qualifies when
the verifier (tools/, .githooks/) is the same at both, and the change from C0
to C1 is one header_dependents.py can bound (no vendored, toolchain or BFME 1
pointer change, at most --limit dependents), and no tree-wide baseline changed. The hook then verifies the sources
that change from C0 to C1 can reach -- exactly the scope a push from C0 to C1
would verify -- instead of every source: C0's full gate already verified the
rest with the same inputs. The checks that compare sources with each other
(build.cross_source_checks) still run over every row, as do the exception-data
and converged-data audits when their lists changed. Nothing is trusted from
another clone or host.

  python3 tools/full_gate_receipt.py record SHA   # the full gate passed at SHA
  python3 tools/full_gate_receipt.py find SHA     # prints a usable C0, or nothing
  python3 tools/full_gate_receipt.py cross-checks # build.cross_source_checks (a script:
                                                  # the build's process pool re-imports it)
"""
import argparse
import subprocess
import sys
import time
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
KEEP_HOURS = 48
CANDIDATES = 3  # header_dependents runs per find, nearest receipts first
# What the full gate's verdicts depend on beyond the sources scope_from selects:
# the verifier itself and the baselines that excuse rows anywhere in the tree.
# reverse/eh_baseline.csv and reverse/data_converged.csv change often; the hook
# re-runs their audits over every source instead (.githooks/pre-push).
VERIFIER = ("tools", ".githooks", "reverse/gate_baseline.txt", "reverse/dup_defs_baseline.tsv",
            "reverse/unclaimed_sources_whitelist.txt")


def git(*args, check=True):
    return subprocess.run(["git", *args], cwd=ROOT, capture_output=True, text=True, check=check)


def receipts_dir():
    common = git("rev-parse", "--git-common-dir").stdout.strip()
    return (ROOT / common).resolve() / "bfme-full-gate"


def full_sha(rev):
    done = git("rev-parse", "--verify", "--quiet", f"{rev}^{{commit}}", check=False)
    return done.stdout.strip() if done.returncode == 0 else None


def record(sha, now=None):
    now = time.time() if now is None else now
    sha = full_sha(sha)
    if sha is None:
        raise SystemExit(f"full_gate_receipt: {sha} is not a commit")
    folder = receipts_dir()
    folder.mkdir(parents=True, exist_ok=True)
    (folder / sha).write_text(f"{int(now)}\n")
    for old in folder.iterdir():
        if old.is_file() and old.stat().st_mtime < now - KEEP_HOURS * 3600:
            old.unlink(missing_ok=True)
    return 0


def recorded(now=None):
    """Recorded commits still in the clone, newest first."""
    now = time.time() if now is None else now
    folder = receipts_dir()
    if not folder.is_dir():
        return []
    found = []
    for path in folder.iterdir():
        if path.is_file() and path.stat().st_mtime >= now - KEEP_HOURS * 3600 and full_sha(path.name) == path.name:
            found.append((path.stat().st_mtime, path.name))
    return [sha for _, sha in sorted(found, reverse=True)]


def changed_files(old, new):
    return git("diff", "--name-only", old, new).stdout.split()


def bounded(old, new):
    done = subprocess.run([sys.executable, str(ROOT / "tools" / "header_dependents.py"), "--range", old, new],
                          cwd=ROOT, capture_output=True, text=True)
    return done.returncode == 0


def find(sha, now=None):
    """A recorded C0 whose full gate carries to `sha`, or None."""
    target = full_sha(sha)
    if target is None:
        return None
    usable = [old for old in recorded(now)
              if not git("diff", "--name-only", old, target, "--", *VERIFIER).stdout.strip()]
    usable.sort(key=lambda old: len(changed_files(old, target)))
    for old in usable[:CANDIDATES]:
        if old == target or bounded(old, target):
            return old
    return None


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    sub = ap.add_subparsers(dest="cmd", required=True)
    sub.add_parser("record", help="the full gate passed at SHA").add_argument("sha")
    sub.add_parser("find", help="print a recorded commit whose full gate carries to SHA").add_argument("sha")
    sub.add_parser("cross-checks", help="the full gate's cross-source checks over every row")
    args = ap.parse_args(argv)
    if args.cmd == "cross-checks":
        sys.path.insert(0, str(ROOT / "tools"))
        import build
        return build.cross_source_checks()
    if args.cmd == "record":
        return record(args.sha)
    old = find(args.sha)
    if old:
        print(old)
    return 0


if __name__ == "__main__":
    sys.exit(main())
