#!/usr/bin/env python3
"""Fleet command launcher and diagnostic experiments; never a landing gate."""
import argparse
import json
import os
from pathlib import Path
import subprocess
import sys


def worker_environment(manifest, entry):
    env = os.environ.copy()
    env.update(BFME_CLAIM_OWNER=entry["owner"], BFME_BLOCKER_DB=manifest["blocker_db"],
               PYTHONUTF8="1", PYTHONUNBUFFERED="1", BUILD_POOL="1",
               GIT_TERMINAL_PROMPT="0", GCM_INTERACTIVE="Never")
    python = Path(manifest["python"])
    if os.name == "nt":
        env["PYTHONHOME"] = str(python.parent)
    env["PYTHONPATH"] = manifest["python_deps"]
    if manifest.get("author_name") and manifest.get("author_email"):
        for role in ("AUTHOR", "COMMITTER"):
            env[f"GIT_{role}_NAME"] = manifest["author_name"]
            env[f"GIT_{role}_EMAIL"] = manifest["author_email"]
    env["PATH"] = manifest["host_bin"] + os.pathsep + str(python.parent) + os.pathsep + env.get("PATH", "")
    # Append to, rather than discard, any inherited process-scoped Git options.
    count = int(env.get("GIT_CONFIG_COUNT", "0"))
    env[f"GIT_CONFIG_KEY_{count}"] = "fetch.recurseSubmodules"
    env[f"GIT_CONFIG_VALUE_{count}"] = "false"
    env["GIT_CONFIG_COUNT"] = str(count + 1)
    return env


def run_worker(argv):
    parser = argparse.ArgumentParser(description="Run one explicit command in an isolated fleet worker")
    parser.add_argument("--manifest", type=Path, required=True)
    parser.add_argument("--worker", required=True)
    parser.add_argument("command", nargs=argparse.REMAINDER)
    args = parser.parse_args(argv)
    manifest = json.loads(args.manifest.read_text(encoding="utf-8"))
    entries = [w for w in manifest["workers"] if w.get("id") == args.worker]
    if len(entries) != 1:
        parser.error("worker ID must name exactly one prepared writer")
    entry = entries[0]
    root = Path(entry["path"]).resolve()
    own_root = Path(__file__).resolve().parents[1]
    if root != own_root:
        parser.error("invoke this command using the worker's own tools/recovery_lab.py")
    command = args.command
    if command[:1] == ["--"]:
        command = command[1:]
    if not command or command == ["status"]:
        print(json.dumps({"worker": args.worker, "root": str(root), "owner": entry["owner"],
                          "blocker_db": manifest["blocker_db"], "build_pool": 1}, indent=2))
        return 0
    action, *tail = command
    python = manifest["python"]
    if action == "python":
        cmd = [python, *tail]
    elif action == "git":
        cmd = ["git", *tail]
    elif action in ("experiment", "blockers"):
        cmd = [python, str(root / "tools/recovery_lab.py"), action, *tail]
    elif action == "verify":
        if not tail:
            parser.error("verify requires a whole source file; full gates stay coordinator-owned")
        sources = []
        for value in tail:
            path = (root / value).resolve()
            if (not path.is_relative_to(root) or not path.is_file()
                    or path.suffix.lower() not in (".cpp", ".cc", ".cxx", ".c", ".asm", ".lib")):
                parser.error("verify arguments must be existing source files within the worker")
            sources.append(path.relative_to(root).as_posix())
        cmd = [python, str(root / "tools/build.py"), *sources]
    else:
        parser.error("command must be status, python, git, experiment, blockers or verify")
    return subprocess.run(cmd, cwd=root, env=worker_environment(manifest, entry)).returncode


def main(argv=None):
    argv = list(sys.argv[1:] if argv is None else argv)
    if not argv or argv[0] in ("-h", "--help"):
        print("usage: recovery_lab.py {worker,experiment,blockers} ...\n"
              "Diagnostic cache and investigation leases never replace whole-file gates or retail claims.")
        return 0
    action, *tail = argv
    if action == "worker":
        return run_worker(tail)
    if action == "experiment":
        from recovery_experiments import main as experiment
        return experiment(tail)
    if action == "blockers":
        from recovery_blockers import main as blockers
        return blockers(tail)
    raise SystemExit("unknown recovery_lab command: " + action)


if __name__ == "__main__":
    sys.exit(main())
