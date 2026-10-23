#!/usr/bin/env python3
"""Shared runner for mechanical passes: apply, verify per file, keep what
holds, revert the rest, commit in batches.

A pass hands over, per source file, a list of independent edits (each a
label and a text -> text function). For every file the runner applies all of
them and byte-verifies the file with ./build.sh. When that fails, it does not
throw the file away: it tries each edit alone on the original, keeps the ones
that verify, and verifies the kept set together (shrinking it greedily if
two good edits interfere). A file ends either verified with its edits or
restored byte-for-byte. Only ./build.sh decides; the runner never loosens a
gate, and commits go through the hooks like any other.

Library use:

    import bulk_pass
    bulk_pass.run({"Code/A.cpp": [("g_00BFDF8C", fn), ...], ...},
                  label="name_globals", commit_every=20)
"""
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]


def _read(path):
    with path.open(encoding="latin-1", newline="") as handle:
        return handle.read()


def _write(path, text):
    with path.open("w", encoding="latin-1", newline="") as handle:
        handle.write(text)


def verify(source):
    """True when ./build.sh byte-verifies every row of `source`."""
    command = ([sys.executable, str(ROOT / "tools" / "build.py"), source]
               if sys.platform == "win32" else ["./build.sh", source])
    done = subprocess.run(command, cwd=ROOT, capture_output=True, text=True)
    return done.returncode == 0 and "Functions: OK" in done.stdout


def _apply(text, edits):
    for _label, edit in edits:
        text = edit(text)
    return text


def settle(source, edits, check=verify):
    """Apply as many of `edits` to `source` as verify; return the kept labels."""
    path = ROOT / source
    original = _read(path)
    candidate = _apply(original, edits)
    if candidate == original:
        return []
    _write(path, candidate)
    if check(source):
        return [label for label, _ in edits]
    good = []
    if len(edits) > 1:
        for edit in edits:
            alone = _apply(original, [edit])
            if alone == original:
                continue
            _write(path, alone)
            if check(source):
                good.append(edit)
    kept = []
    for edit in good:  # greedy: two edits that verify alone can still collide
        trial = _apply(original, [e for e in kept + [edit]])
        _write(path, trial)
        if check(source):
            kept.append(edit)
    _write(path, _apply(original, kept) if kept else original)
    return [label for label, _ in kept]


def _commit(paths, message):
    subprocess.run(["git", "add", "--", *paths], cwd=ROOT, check=True)
    done = subprocess.run(["git", "commit", "-q", "-m", message], cwd=ROOT, text=True)
    return done.returncode == 0


def run(edits_by_file, label, commit_every=0, message=None, check=verify, log=print):
    """Settle every file; optionally commit every `commit_every` changed files.
    Returns {source: kept labels} for the files that changed."""
    changed, pending = {}, []
    for source, edits in edits_by_file.items():
        kept = settle(source, edits, check)
        if kept:
            changed[source] = kept
            pending.append(source)
            log(f"OK {source} {sorted(kept)}")
        else:
            log(f"REVERTED {source} {sorted(l for l, _ in edits)}")
        if commit_every and len(pending) >= commit_every:
            _commit(pending, (message or f"{label}: verified batch") + f" ({len(pending)} files)")
            pending = []
    if commit_every and pending:
        _commit(pending, (message or f"{label}: verified batch") + f" ({len(pending)} files)")
    log(f"{label}: {len(changed)} file(s) changed, {sum(map(len, changed.values()))} edit(s) kept")
    return changed


if __name__ == "__main__":
    sys.exit("bulk_pass is a library; see its docstring")
