#!/usr/bin/env python3
"""Create or prepare a linked worktree with its own cheap reference/open-bfme-1.

A bare `git submodule update --init` in a new worktree re-downloads Open-BFME-1:
.gitmodules asks for a shallow clone, the depth-1 clone of upstream's tip
lacks the pinned commit, and the follow-up `git fetch origin <pin>` pulls the
whole history (580k objects, ~4 GB RAM, ~50 CPU-minutes per worktree).
`--reference` cannot help: git refuses a shallow reference repository, and
`submodule.alternateErrorStrategy=info` turns that refusal into an unshared
clone. `git clone --shared` from the shallow modules dir silently drops to a
packing transfer (2.5 GB RAM).

This tool gives the worktree its own submodule gitdir, in the worktree's own
`modules/` (where git itself would put it), that borrows the main checkout's
objects through objects/info/alternates and copies its shallow list. Nothing
is fetched or packed; the cost is writing the checkout. Git never writes into
an alternate object store, so commits, gc and fetches in the worktree's
submodule stay in the worktree's gitdir; nothing links into another checkout.

The main checkout must already hold the pinned commit; otherwise the tool
refuses and names the one-time fetch for the main checkout.

  python3 tools/worktree_setup.py create .claude/worktrees/NAME --branch NAME [--base origin/master]
  python3 tools/worktree_setup.py prepare [WORKTREE]
  python3 tools/worktree_setup.py check [WORKTREE]

--inputs-only checks out only inputs/ (toolchains, reference headers, vendor):
enough for ./build.sh, not for tools that read Open-BFME-1's game/ or targets/.
"""
import argparse
import subprocess
import sys
from pathlib import Path

SUBMODULE = "reference/open-bfme-1"
INPUTS_ONLY = ("inputs",)


class SetupError(Exception):
    pass


def git(cwd, *args, check=True, git_dir=None, configs=()):
    cmd = ["git"]
    for item in configs:
        cmd += ["-c", item]
    if git_dir is not None:
        cmd.append(f"--git-dir={git_dir}")
    cmd += list(args)
    proc = subprocess.run(cmd, cwd=cwd, capture_output=True, text=True)
    if check and proc.returncode != 0:
        raise SetupError(f"`{' '.join(cmd)}` failed in {cwd}:\n{proc.stderr.strip()}")
    return proc


def out(cwd, *args, **kwargs):
    return git(cwd, *args, **kwargs).stdout.strip()


def posix(path):
    return str(Path(path).resolve()).replace("\\", "/")


def is_link(path):
    """A symlink or (Windows) directory junction: never let git run through one."""
    path = Path(path)
    if path.is_symlink():
        return True
    is_junction = getattr(path, "is_junction", None)
    if is_junction is not None:
        return is_junction()
    return False


def layout(worktree):
    """Paths for one linked worktree: its submodule dir, gitdir and the main store."""
    worktree = Path(worktree).resolve()
    top = Path(out(worktree, "rev-parse", "--show-toplevel"))
    git_dir = Path(out(top, "rev-parse", "--path-format=absolute", "--git-dir"))
    common = Path(out(top, "rev-parse", "--path-format=absolute", "--git-common-dir"))
    if posix(git_dir) == posix(common):
        raise SetupError(
            f"{top} is the main checkout, not a linked worktree; it gets "
            f"{SUBMODULE} the normal way (tools/setup_hooks.sh).")
    modules = Path(out(top, "rev-parse", "--path-format=absolute",
                       "--git-path", f"modules/{SUBMODULE}"))
    return {
        "top": top,
        "sub": top / SUBMODULE,
        "gitdir": modules,
        "main_store": common / "modules" / SUBMODULE,
        "main_top": common.parent,
    }


def pinned_commit(top, rev="HEAD"):
    entry = out(top, "ls-tree", rev, "--", SUBMODULE).split()
    if len(entry) < 3 or entry[0] != "160000" or entry[1] != "commit":
        raise SetupError(f"{rev} has no submodule entry at {SUBMODULE}")
    return entry[2]


def fetch_hint(paths, pin):
    main_top = paths["main_top"]
    if not (paths["main_store"] / "objects").is_dir():
        how = (f"  git -C {posix(main_top)} submodule update --init --depth 1 {SUBMODULE}\n"
               f"(--depth 1 matters: without it git fetches the pin with its whole "
               f"history, 580k objects, ~4 GB RAM.)")
    else:
        how = (f"  git -C {posix(main_top / SUBMODULE)} fetch origin\n"
               f"(incremental: its narrow refspec fetches upstream master past what it "
               f"has). If the pin is not on upstream master:\n"
               f"  git -C {posix(main_top / SUBMODULE)} fetch --depth 1 origin {pin}")
    return (f"Fetch it once in the main checkout ({posix(main_top)}), not here:\n"
            f"{how}\nThen rerun this tool.")


def missing_objects(store, pin):
    """Objects of the pinned tree the main store cannot supply (empty: all there)."""
    if git(store, "cat-file", "-e", f"{pin}^{{commit}}", check=False,
           git_dir=store).returncode != 0:
        return [pin]
    proc = git(store, "rev-list", "--objects", "--no-walk", "--missing=print", pin,
               check=False, git_dir=store)
    if proc.returncode != 0:
        return [proc.stderr.strip() or pin]
    return [line[1:] for line in proc.stdout.splitlines() if line.startswith("?")]


def require_main_objects(paths, pin):
    store = paths["main_store"]
    if not (store / "objects").is_dir():
        raise SetupError(
            f"the main checkout has no {SUBMODULE} object store ({store}).\n"
            + fetch_hint(paths, pin))
    missing = missing_objects(store, pin)
    if missing:
        raise SetupError(
            f"the main checkout's {SUBMODULE} store lacks {len(missing)} object(s) of "
            f"the pinned commit {pin} (first: {missing[0]}).\n" + fetch_hint(paths, pin))


def own_gitdir(paths):
    """The gitdir the worktree's submodule .git file names, or None if absent."""
    dotgit = paths["sub"] / ".git"
    if not dotgit.exists():
        return None
    if dotgit.is_dir():
        raise SetupError(f"{dotgit} is a directory; this tool only manages a gitdir "
                         f"under the worktree's modules/. Move it aside first.")
    text = dotgit.read_text(encoding="utf-8").strip()
    if not text.startswith("gitdir:"):
        raise SetupError(f"{dotgit} is not a gitdir file")
    target = Path(text[len("gitdir:"):].strip())
    if not target.is_absolute():
        target = paths["sub"] / target
    return target


def check_target(paths):
    """Refuse links and any submodule state this tool did not make."""
    sub = paths["sub"]
    for parent in (sub.parent, sub):
        if is_link(parent):
            raise SetupError(
                f"{parent} is a symlink or junction; git commands through it act on "
                f"another checkout. Remove the link itself (Windows: `rmdir` the "
                f"junction, never a recursive delete) and rerun.")
    gitdir = own_gitdir(paths)
    if gitdir is not None and posix(gitdir) != posix(paths["gitdir"]):
        raise SetupError(f"{sub}/.git names {gitdir}, not this worktree's "
                         f"{paths['gitdir']}; refusing to touch another gitdir.")
    if gitdir is None and sub.is_dir() and any(sub.iterdir()):
        raise SetupError(f"{sub} is not empty but has no .git; move it aside first.")


def write_alternates(gitdir, store):
    alternates = gitdir / "objects" / "info" / "alternates"
    alternates.parent.mkdir(parents=True, exist_ok=True)
    wanted = posix(store / "objects")
    lines = []
    if alternates.exists():
        lines = [l.strip() for l in alternates.read_text(encoding="utf-8").splitlines() if l.strip()]
    if wanted not in lines:
        lines.append(wanted)
    alternates.write_text("\n".join(lines) + "\n", encoding="utf-8", newline="\n")


def merge_shallow(gitdir, store):
    """Borrowed history ends where the main store's does: share its shallow list."""
    source = store / "shallow"
    if not source.exists():
        return
    target = gitdir / "shallow"
    have = set(target.read_text(encoding="utf-8").split()) if target.exists() else set()
    have |= set(source.read_text(encoding="utf-8").split())
    target.write_text("".join(f"{oid}\n" for oid in sorted(have)), encoding="utf-8",
                      newline="\n")


def submodule_url(top):
    return out(top, "config", "-f", ".gitmodules", f"submodule.{SUBMODULE}.url")


def enable_worktree_hooks(top):
    """core.hooksPath=.githooks for this worktree only (config.worktree)."""
    if out(top, "config", "--bool", "--get", "extensions.worktreeConfig", check=False) != "true":
        if out(top, "config", "--local", "--bool", "--get", "core.bare", check=False) == "true":
            raise SetupError("the shared config sets core.bare=true; move it to the main "
                             "worktree's config.worktree before enabling extensions.worktreeConfig")
        if out(top, "config", "--local", "--get", "core.worktree", check=False):
            raise SetupError("the shared config sets core.worktree; move it to the main "
                             "worktree's config.worktree before enabling extensions.worktreeConfig")
        git(top, "config", "--local", "extensions.worktreeConfig", "true")
    git(top, "config", "--worktree", "core.hooksPath", ".githooks")


def prepare(worktree, inputs_only=False):
    paths = layout(worktree)
    top, sub, gitdir, store = paths["top"], paths["sub"], paths["gitdir"], paths["main_store"]
    pin = pinned_commit(top)
    check_target(paths)
    require_main_objects(paths, pin)
    enable_worktree_hooks(top)
    sub.mkdir(parents=True, exist_ok=True)
    # A gitdir whose HEAD never resolved is a failed earlier run: redo it.
    existing = (gitdir / "HEAD").exists() and git(
        sub, "rev-parse", "--verify", "--quiet", "HEAD^{commit}", check=False,
        git_dir=gitdir).returncode == 0
    if not existing:
        gitdir.parent.mkdir(parents=True, exist_ok=True)
        git(top, "init", "-q", f"--separate-git-dir={gitdir}", str(sub))
    write_alternates(gitdir, store)
    merge_shallow(gitdir, store)
    git(sub, "config", "core.worktree", posix(sub), git_dir=gitdir)
    url = submodule_url(top)
    if git(sub, "remote", "get-url", "origin", check=False, git_dir=gitdir).returncode == 0:
        git(sub, "remote", "set-url", "origin", url, git_dir=gitdir)
    else:
        git(sub, "remote", "add", "origin", url, git_dir=gitdir)
    # The main store's narrow refspec (master only). The default refs/heads/*
    # makes every `git pull` (submodule.recurse=true) fetch upstream's other
    # branches below the shallow boundary: 600k objects, 7.5 GB RAM.
    refspecs = out(store, "config", "--get-all", "remote.origin.fetch",
                   check=False, git_dir=store).splitlines()
    if not refspecs:
        raise SetupError(f"{store} has no remote.origin.fetch to copy")
    git(sub, "config", "--replace-all", "remote.origin.fetch", refspecs[0], git_dir=gitdir)
    for refspec in refspecs[1:]:
        git(sub, "config", "--add", "remote.origin.fetch", refspec, git_dir=gitdir)
    if not existing:
        git(sub, "update-ref", "--no-deref", "HEAD", pin)
        if inputs_only:
            git(sub, "sparse-checkout", "set", "--cone", *INPUTS_ONLY)
        git(sub, "reset", "-q", "--hard", pin)
    elif out(sub, "rev-parse", "HEAD", check=False) != pin:
        # An existing checkout may hold the seat's own edits: never reset it.
        git(sub, "checkout", "-q", "--detach", pin)
    return verify(worktree)


def verify(worktree):
    paths = layout(worktree)
    top, sub = paths["top"], paths["sub"]
    pin = pinned_commit(top)
    problems = []
    for parent in (sub.parent, sub):
        if is_link(parent):
            problems.append(f"{parent} is a link")
    if not problems:
        gitdir = out(sub, "rev-parse", "--path-format=absolute", "--git-dir", check=False)
        if posix(gitdir or sub) != posix(paths["gitdir"]):
            problems.append(f"{SUBMODULE} uses gitdir {gitdir or '(none)'}, "
                            f"not {paths['gitdir']}")
        head = out(sub, "rev-parse", "HEAD", check=False)
        if head != pin:
            problems.append(f"{SUBMODULE} HEAD is {head or '(none)'}, pin is {pin}")
        status = git(top, "submodule", "status", "--", SUBMODULE, check=False).stdout
        if not status.startswith(" "):
            problems.append(f"git submodule status: {status.strip()!r}")
    hooks = out(top, "config", "--get", "core.hooksPath", check=False)
    if hooks != ".githooks":
        problems.append(f"core.hooksPath is {hooks!r}, not .githooks")
    if problems:
        raise SetupError("worktree not ready:\n  " + "\n  ".join(problems))
    return pin


def create(path, branch=None, base="HEAD", inputs_only=False, cwd=None):
    """`git worktree add` without touching submodules, then prepare()."""
    cwd = Path(cwd or Path.cwd())
    path = Path(path)
    if not path.is_absolute():
        path = cwd / path
    if path.exists() and any(path.iterdir()):
        raise SetupError(f"{path} exists and is not empty")
    # LF checkouts: tu_skeleton refuses CRLF ledgers, and system git on the
    # seats sets core.autocrlf=true. The submodule is set up by prepare().
    configs = ("core.autocrlf=false", "submodule.recurse=false")
    start = base
    if branch is not None and git(cwd, "rev-parse", "--verify", "--quiet",
                                  f"refs/heads/{branch}", check=False).returncode == 0:
        start = branch
    # Refuse before `worktree add`, not after it leaves a half-made worktree.
    common = Path(out(cwd, "rev-parse", "--path-format=absolute", "--git-common-dir"))
    require_main_objects({"main_store": common / "modules" / SUBMODULE,
                          "main_top": common.parent}, pinned_commit(cwd, start))
    args = ["worktree", "add"]
    if branch is None:
        args += ["--detach", str(path), base]
    elif start == branch:
        args += [str(path), branch]
    else:
        args += ["-b", branch, str(path), base]
    git(cwd, *args, configs=configs)
    return prepare(path, inputs_only=inputs_only)


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n")[0])
    sub = parser.add_subparsers(dest="cmd", required=True)
    c = sub.add_parser("create", help="git worktree add, then prepare it")
    c.add_argument("path")
    c.add_argument("--branch", help="branch to check out (created from --base if new)")
    c.add_argument("--base", default="HEAD", help="start point (default HEAD)")
    c.add_argument("--inputs-only", action="store_true",
                   help=f"check out only {', '.join(INPUTS_ONLY)}/ of {SUBMODULE}")
    p = sub.add_parser("prepare", help="set up hooks and the submodule in an existing worktree")
    p.add_argument("path", nargs="?", default=".")
    p.add_argument("--inputs-only", action="store_true",
                   help=f"check out only {', '.join(INPUTS_ONLY)}/ of {SUBMODULE}")
    k = sub.add_parser("check", help="verify a worktree's hooks, gitdir and pin")
    k.add_argument("path", nargs="?", default=".")
    args = parser.parse_args(argv)
    try:
        if args.cmd == "create":
            pin = create(args.path, args.branch, args.base, args.inputs_only)
        elif args.cmd == "prepare":
            pin = prepare(args.path, args.inputs_only)
        else:
            pin = verify(args.path)
    except SetupError as exc:
        print(f"worktree_setup: {exc}", file=sys.stderr)
        return 1
    print(f"worktree_setup: {args.cmd} OK: {SUBMODULE} at {pin}, own gitdir, "
          f"objects borrowed from the main checkout, core.hooksPath=.githooks")
    return 0


if __name__ == "__main__":
    sys.exit(main())
