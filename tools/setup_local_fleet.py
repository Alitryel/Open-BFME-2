#!/usr/bin/env python3
"""Create isolated local Open-BFME writer clones."""
import argparse
import json
import os
import shutil
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
DEFAULT_FLEET = Path.home() / "Projects" / "open-bfme2-local-fleet"
DEFAULT_ORIGIN = "https://github.com/Open-BFME/Open-BFME-2.git"
GH_EXE = Path("/mnt/c/Program Files/GitHub CLI/gh.exe")
GENERATED_INPUTS = (
    "reverse/exports.csv",
    "reverse/ghidra_functions.csv",
    "reverse/string_xrefs.tsv",
)
# tools/setup_hooks.sh's merge.union.driver, character for character.
UNION_DRIVER = (
    "if [ -f tools/merge_rows.py ] && [ -f .githooks/run-python3 ]; "
    "then sh .githooks/run-python3 tools/merge_rows.py %O %A %B %P; "
    "else echo 'merge.union.driver: tools/merge_rows.py or .githooks/run-python3 is not in "
    "this checkout; using git merge-file --union for' %P >&2; "
    "git merge-file --union --diff-algorithm=histogram '%A' '%O' '%B' || { echo 'merge.union.driver: "
    "git merge-file --union --diff-algorithm=histogram failed (it needs git 2.44 or newer); "
    "leaving a conflict in' %P >&2; exit 1; }; fi")


def git(repo, *args, capture=False):
    proc = subprocess.run(
        ["git", "-C", str(repo), *args],
        check=True, text=True, capture_output=capture,
    )
    return proc.stdout.strip() if capture else ""


def git_dir(repo):
    return Path(git(repo, "rev-parse", "--path-format=absolute", "--git-dir",
                    capture=True))


def configure_repo(repo, origin):
    git(repo, "remote", "set-url", "origin", origin)
    git(repo, "config", "--local", "pull.rebase", "true")
    git(repo, "config", "--local", "rebase.autoStash", "true")
    git(repo, "config", "--local", "core.hooksPath", ".githooks")
    git(repo, "config", "--local", "merge.union.driver", UNION_DRIVER)
    git(repo, "config", "--local",
        f"lfs.{origin}/info/lfs.locksverify", "false")
    if GH_EXE.exists():
        git(repo, "config", "--local", "credential.helper",
            f'!"{GH_EXE}" auth git-credential')
    # Older setup versions installed deterministic queue sharding here. Remove
    # stale private configuration so every clone uses the randomized queue.
    (git_dir(repo) / "openbfme-worker.json").unlink(missing_ok=True)


def copy_generated_inputs(source, target):
    copied = []
    for rel in GENERATED_INPUTS:
        src, dst = source / rel, target / rel
        if src.exists() and not dst.exists():
            dst.parent.mkdir(parents=True, exist_ok=True)
            shutil.copy2(src, dst)
            copied.append(rel)
    return copied


def ensure_clone(source, target, branch):
    if target.exists():
        git(target, "rev-parse", "--is-inside-work-tree", capture=True)
        return False
    target.parent.mkdir(parents=True, exist_ok=True)
    subprocess.run([
        "git", "clone", "--shared", "--single-branch", "--branch", branch,
        str(source), str(target),
    ], check=True)
    return True


def preflight_short(source, fleet_root, targets):
    """Check every destination before creating or configuring any worker."""
    if fleet_root == source or fleet_root.is_relative_to(source):
        raise ValueError("short-path fleet must be outside the source checkout")
    manifest = fleet_root / "fleet.json"
    if manifest.exists() and json.loads(manifest.read_text(encoding="utf-8")).get("source") != str(source):
        raise ValueError(f"refusing unrelated existing fleet manifest: {manifest}")
    if os.name == "nt" and (str(fleet_root).startswith("\\\\") or
                            any(len(str(p)) > 32 for p in targets)):
        raise ValueError("use a local short root such as D:/b2 (worker path <=32 characters)")
    for target in targets:
        if not target.exists():
            continue
        marker = git_dir(target) / "openbfme-fleet.json"
        if (not marker.is_file() or
                json.loads(marker.read_text(encoding="utf-8")).get("source") != str(source)):
            raise ValueError(f"refusing unrelated existing worker: {target}")
        if git(target, "status", "--porcelain", capture=True):
            raise ValueError(f"preserve dirty worker before refreshing setup: {target}")


def prepare_reference(source, target):
    """Local clone of the exact gitlink; never initialize nested references."""
    rel = "reference/open-bfme-1"
    tree = git(target, "ls-tree", "HEAD", "--", rel, capture=True).split()
    if len(tree) < 3 or tree[0] != "160000":
        raise ValueError(f"{target}: no pinned BFME 1 gitlink")
    pin = tree[2]
    donor, destination = source / rel, target / rel
    git(donor, "cat-file", "-e", pin + "^{commit}", capture=True)
    if (destination / ".git").exists():
        if git(destination, "rev-parse", "HEAD", capture=True) != pin:
            raise ValueError(f"{destination}: stale reference; update explicitly without recursion")
        if git(destination, "status", "--porcelain", capture=True):
            raise ValueError(f"{destination}: reference has local changes")
        return pin
    if destination.exists() and any(destination.iterdir()):
        raise ValueError(f"{destination}: refusing nonempty unrecognized reference")
    subprocess.run(["git", "clone", "--shared", "--no-checkout", "--no-recurse-submodules",
                    str(donor), str(destination)], check=True)
    git(destination, "-c", "submodule.recurse=false", "checkout", "--detach", pin)
    url = git(target, "config", "-f", ".gitmodules", "--get",
              'submodule.reference/open-bfme-1.url', capture=True)
    git(destination, "remote", "set-url", "origin", url)
    return pin


def track_master(source, target):
    """A clone of a private source branch must still fetch the publication branch."""
    git(target, "config", "--local", "remote.origin.fetch",
        "+refs/heads/master:refs/remotes/origin/master")
    known = subprocess.run(["git", "-C", str(target), "show-ref", "--verify", "--quiet",
                            "refs/remotes/origin/master"]).returncode
    if known:
        master = git(source, "rev-parse", "--verify", "origin/master", capture=True)
        git(target, "update-ref", "refs/remotes/origin/master", master)
    branch = git(target, "branch", "--show-current", capture=True)
    if not branch:
        raise ValueError(f"{target}: detached worker needs an explicit working branch")
    git(target, "branch", "--set-upstream-to=origin/master", branch)


def short_fleet(args, source, fleet_root, branch):
    targets = [fleet_root / f"w{i + 1:02d}" for i in range(args.workers)]
    preflight_short(source, fleet_root, targets)
    python = args.python.resolve()
    if not python.is_file():
        raise ValueError(f"Python executable missing: {python}")
    reference = source / "reference/open-bfme-1"
    if not (reference / ".git").exists():
        raise ValueError("initialize the source BFME 1 reference explicitly first")
    # Input repositories and generated worker trees remain independent. Only the
    # immutable Git object stores are borrowed; no build/match junctions.
    runtime = fleet_root / "runtime"
    host_bin = runtime / "host-bin"
    host_bin.mkdir(parents=True, exist_ok=True)
    if os.name == "nt":
        shim = host_bin / "python3.exe"
        if not shim.exists():
            shutil.copy2(python, shim)
    deps = source / "build/python-deps"
    runtime_deps = runtime / "python-deps"
    if deps.is_dir() and not runtime_deps.exists():
        shutil.copytree(deps, runtime_deps)
    entries = [{"role": "primary", "path": str(source)}]
    for index, target in enumerate(targets):
        created = ensure_clone(source, target, branch)
        # Record identity immediately so an interrupted first setup can resume.
        (git_dir(target) / "openbfme-fleet.json").write_text(
            json.dumps({"source": str(source)}) + "\n", encoding="utf-8")
        configure_repo(target, args.origin)
        track_master(source, target)
        git(target, "config", "--local", "fetch.recurseSubmodules", "false")
        git(target, "config", "--local", "submodule.recurse", "true")
        git(target, "config", "--local", "user.name", args.author_name)
        git(target, "config", "--local", "user.email", args.author_email)
        pin = prepare_reference(source, target)
        copied = copy_generated_inputs(source, target)
        worker = f"w{index + 1:02d}"
        entry = {"role": "writer", "id": worker, "path": str(target),
                 "created": created, "copied": copied, "reference": pin,
                 "owner": f"{args.owner_prefix}-{worker}"}
        entries.append(entry)
        launcher = fleet_root / (worker + ".ps1")
        quote = lambda value: "'" + str(value).replace("'", "''") + "'"
        launcher.write_text(
            "# Generated explicit-command launcher; starts no agent on its own.\n"
            "param([Parameter(ValueFromRemainingArguments=$true)][string[]]$WorkerArgs)\n"
            f"& {quote(python)} {quote(target / 'tools/recovery_lab.py')} worker "
            f"--manifest {quote(fleet_root / 'fleet.json')} --worker {worker} -- @WorkerArgs\n"
            "exit $LASTEXITCODE\n", encoding="utf-8")
    manifest = fleet_root / "fleet.json"
    manifest.write_text(json.dumps({
        "version": 1, "branch": branch, "origin": args.origin, "source": str(source),
        "python": str(python), "host_bin": str(host_bin),
        "author_name": args.author_name, "author_email": args.author_email,
        "python_deps": str(runtime_deps), "blocker_db": str(fleet_root / "blockers.sqlite3"),
        "workers": entries,
    }, indent=2) + "\n", encoding="utf-8")
    print(f"fleet: {manifest} ({args.workers} prepared workers; no agents started)")
    print("one coordinator publishes; normal hooks and whole-file gates remain required")
    return manifest


def main():
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument("--source", type=Path, default=ROOT)
    parser.add_argument("--root", type=Path, default=DEFAULT_FLEET)
    parser.add_argument("--workers", type=int, default=2,
                        help="additional writer clones (default 2; primary makes 3)")
    parser.add_argument("--origin", default=DEFAULT_ORIGIN)
    parser.add_argument("--branch")
    parser.add_argument("--short-path", action="store_true",
                        help="prepare short isolated workers with pinned references and PowerShell launchers")
    parser.add_argument("--python", type=Path, default=Path(sys.executable))
    parser.add_argument("--owner-prefix", default="codex-wumbo")
    parser.add_argument("--author-name", default="WumboJet")
    parser.add_argument("--author-email", default="60122146+WumboJet@users.noreply.github.com")
    args = parser.parse_args()

    source = args.source.resolve()
    fleet_root = args.root.resolve()
    if args.workers < 0:
        parser.error("--workers must be non-negative")
    branch = args.branch or git(source, "branch", "--show-current", capture=True)
    if not branch:
        parser.error("source is detached; pass --branch")
    if args.short_path:
        try:
            short_fleet(args, source, fleet_root, branch)
        except (ValueError, OSError, subprocess.CalledProcessError) as exc:
            parser.exit(1, f"fleet setup refused: {exc}\n")
        return

    entries = [{"role": "primary", "path": str(source)}]
    configure_repo(source, args.origin)

    for index in range(args.workers):
        number = index + 2
        target = fleet_root / f"writer-{number}"
        created = ensure_clone(source, target, branch)
        copied = copy_generated_inputs(source, target)
        configure_repo(target, args.origin)
        entries.append({
            "role": "writer",
            "path": str(target), "created": created, "copied": copied,
        })

    fleet_root.mkdir(parents=True, exist_ok=True)
    manifest = fleet_root / "fleet.json"
    manifest.write_text(json.dumps({
        "branch": branch,
        "origin": args.origin,
        "source": str(source),
        "workers": entries,
    }, indent=2) + "\n", encoding="utf-8")

    print(f"fleet: {manifest}")
    for entry in entries:
        print(f"  {entry['role']}: {entry['path']}")
    print("full build gate: run in one writer at a time")


if __name__ == "__main__":
    main()
