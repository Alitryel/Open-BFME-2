"""tools/worktree_setup.py gives a linked worktree its own submodule gitdir that
borrows the main checkout's objects, and never touches the main checkout's store.

Each case builds a tiny local superproject with a file:// submodule at
reference/open-bfme-1, so nothing reaches the network.
"""
import os
import subprocess
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import worktree_setup as ws  # noqa: E402

SUB = ws.SUBMODULE


def run(cwd, *args):
    proc = subprocess.run(["git", *args], cwd=cwd, capture_output=True, text=True)
    assert proc.returncode == 0, f"git {' '.join(args)}: {proc.stderr}"
    return proc.stdout.strip()


@pytest.fixture(autouse=True)
def isolated_git(monkeypatch, tmp_path):
    # A hook runs these tests with GIT_DIR and friends set for the real repo.
    for name in list(os.environ):
        if name.startswith("GIT_"):
            monkeypatch.delenv(name)
    monkeypatch.setenv("GIT_CONFIG_NOSYSTEM", "1")
    monkeypatch.setenv("GIT_CONFIG_GLOBAL", str(tmp_path / "gitconfig"))
    (tmp_path / "gitconfig").write_text(
        "[user]\n\tname = t\n\temail = t@example.invalid\n"
        "[protocol \"file\"]\n\tallow = always\n[init]\n\tdefaultBranch = master\n",
        encoding="utf-8")


@pytest.fixture
def repos(tmp_path):
    """upstream (the BFME 1 stand-in) and main (a superproject pinning it)."""
    upstream = tmp_path / "upstream"
    upstream.mkdir()
    run(upstream, "init", "-q")
    (upstream / "inputs").mkdir()
    (upstream / "inputs" / "header.h").write_text("int x;\n", encoding="utf-8")
    (upstream / "game").mkdir()
    (upstream / "game" / "game.cpp").write_text("int y;\n", encoding="utf-8")
    run(upstream, "add", ".")
    run(upstream, "commit", "-qm", "one")
    main = tmp_path / "main"
    main.mkdir()
    run(main, "init", "-q")
    (main / "README").write_text("main\n", encoding="utf-8")
    run(main, "add", "README")
    run(main, "commit", "-qm", "root")
    run(main, "submodule", "add", "-q", upstream.as_uri(), SUB)
    run(main, "config", "core.hooksPath", str(main / ".githooks"))
    run(main, "commit", "-qm", "pin")
    return upstream, main


def store_state(main):
    store = main / ".git" / "modules" / SUB
    files = sorted((p.relative_to(store).as_posix(), p.stat().st_mtime_ns)
                   for p in store.rglob("*") if p.is_file())
    return files


def test_create_borrows_objects_and_isolates_the_gitdir(repos, tmp_path):
    upstream, main = repos
    before = store_state(main)
    wt = tmp_path / "wt"
    pin = ws.create(wt, branch="seat", base="HEAD", cwd=main)
    assert pin == run(main, "rev-parse", f"HEAD:{SUB}")
    sub = wt / SUB
    assert (sub / "game" / "game.cpp").read_text(encoding="utf-8") == "int y;\n"
    gitdir = Path(run(sub, "rev-parse", "--path-format=absolute", "--git-dir"))
    assert ws.posix(gitdir) == ws.posix(main / ".git/worktrees/wt/modules" / SUB)
    alternates = (gitdir / "objects/info/alternates").read_bytes()
    assert alternates == (ws.posix(main / ".git/modules" / SUB / "objects") + "\n").encode()
    assert not list((gitdir / "objects/pack").glob("*.pack"))
    assert run(wt, "config", "--get", "core.hooksPath") == ".githooks"
    assert run(main, "config", "--get", "core.hooksPath") == str(main / ".githooks")
    assert run(wt, "branch", "--show-current") == "seat"
    # Work in the worktree's submodule lands in its own gitdir only.
    (sub / "new.txt").write_text("n\n", encoding="utf-8")
    run(sub, "add", "new.txt")
    run(sub, "commit", "-qm", "seat edit")
    run(sub, "gc", "-q")
    assert store_state(main) == before
    assert run(main / SUB, "rev-parse", "HEAD") == pin


def test_prepare_is_idempotent_and_copies_the_narrow_refspec(repos, tmp_path):
    upstream, main = repos
    store = main / ".git" / "modules" / SUB
    run(main, "--git-dir", str(store), "config", "--replace-all", "remote.origin.fetch",
        "+refs/heads/master:refs/remotes/origin/master")
    wt = tmp_path / "wt"
    ws.create(wt, cwd=main)
    (wt / SUB / "game" / "game.cpp").write_text("seat change\n", encoding="utf-8")
    pin = ws.prepare(wt)
    # A rerun never resets the seat's own edits.
    assert (wt / SUB / "game" / "game.cpp").read_text(encoding="utf-8") == "seat change\n"
    gitdir = main / ".git/worktrees/wt/modules" / SUB
    assert run(wt / SUB, "config", "--get-all", "remote.origin.fetch") == \
        "+refs/heads/master:refs/remotes/origin/master"
    assert run(wt / SUB, "remote", "get-url", "origin") == upstream.as_uri()
    assert (gitdir / "objects/info/alternates").read_text(encoding="utf-8").count("\n") == 1
    assert ws.verify(wt) == pin


def test_refuses_a_pin_the_main_store_lacks(repos, tmp_path):
    upstream, main = repos
    (upstream / "game" / "game.cpp").write_text("int z;\n", encoding="utf-8")
    run(upstream, "commit", "-qam", "two")
    newer = run(upstream, "rev-parse", "HEAD")
    # Pin a commit the main checkout never fetched.
    run(main, "update-index", "--cacheinfo", f"160000,{newer},{SUB}")
    run(main, "commit", "-qm", "repin")
    with pytest.raises(ws.SetupError) as err:
        ws.create(tmp_path / "wt", cwd=main)
    message = str(err.value)
    assert newer in message and "main checkout" in message and "fetch" in message
    assert not (tmp_path / "wt").exists()


def test_refuses_the_main_checkout(repos):
    _, main = repos
    with pytest.raises(ws.SetupError, match="main checkout"):
        ws.prepare(main)


def test_refuses_a_link_into_another_checkout(repos, tmp_path, monkeypatch):
    _, main = repos
    wt = tmp_path / "wt"
    run(main, "-c", "submodule.recurse=false", "worktree", "add", "-q", "--detach", str(wt))
    sub = wt / SUB
    monkeypatch.setattr(ws, "is_link", lambda path: Path(path) == sub)
    with pytest.raises(ws.SetupError, match="junction"):
        ws.prepare(wt)


def test_refuses_a_gitdir_it_did_not_make(repos, tmp_path):
    _, main = repos
    wt = tmp_path / "wt"
    run(main, "-c", "submodule.recurse=false", "worktree", "add", "-q", "--detach", str(wt))
    (wt / SUB).mkdir(parents=True, exist_ok=True)
    (wt / SUB / ".git").write_text(f"gitdir: {ws.posix(main / '.git/modules' / SUB)}\n",
                                   encoding="utf-8")
    with pytest.raises(ws.SetupError, match="refusing to touch another gitdir"):
        ws.prepare(wt)


def test_inputs_only_checks_out_inputs(repos, tmp_path):
    _, main = repos
    wt = tmp_path / "wt"
    ws.create(wt, cwd=main, inputs_only=True)
    assert (wt / SUB / "inputs" / "header.h").exists()
    assert not (wt / SUB / "game").exists()


def test_merge_shallow_unions_and_writes_lf(tmp_path):
    store, gitdir = tmp_path / "store", tmp_path / "gitdir"
    store.mkdir()
    gitdir.mkdir()
    (store / "shallow").write_text("b" * 40 + "\n" + "a" * 40 + "\n", encoding="utf-8")
    (gitdir / "shallow").write_text("c" * 40 + "\n", encoding="utf-8")
    ws.merge_shallow(gitdir, store)
    assert (gitdir / "shallow").read_bytes() == \
        ("a" * 40 + "\n" + "b" * 40 + "\n" + "c" * 40 + "\n").encode()
