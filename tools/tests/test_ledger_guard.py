"""ledger_guard: the byte gate must read the ledgers being committed or pushed."""
import re
import os
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import ledger_guard as G  # noqa: E402

LEDGER = G.LEDGERS[0]
ROW = "?f@@YAXXZ,,0x00401000,4,{src},matched,x\n"
HEAD = "name,export_rva,target_rva,target_size,source,status,notes\n"


def git(root, *args):
    env = dict(os.environ, GIT_CONFIG_NOSYSTEM="1", GIT_CONFIG_GLOBAL=os.devnull)
    # The real checkout's command-line hook configuration must not turn a
    # temporary fixture commit into a production-repository gate invocation.
    for name in list(env):
        if name == "GIT_CONFIG_COUNT" or name.startswith(("GIT_CONFIG_KEY_", "GIT_CONFIG_VALUE_")):
            env.pop(name)
    return subprocess.run(["git", *args], cwd=root, env=env, check=True,
                          capture_output=True, text=True).stdout


@pytest.fixture
def repo(tmp_path, monkeypatch):
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "user.name", "Fixture")
    git(tmp_path, "config", "user.email", "fixture@example.invalid")
    for path, text in ((LEDGER, HEAD + ROW.format(src="Unit.cpp")), (G.LEDGERS[1], "name,rva\n"),
                       ("Unit.cpp", "struct Coord2D { float x, y; };\nvoid f(Coord2D *) {}\n")):
        (tmp_path / path).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / path).write_bytes(text.encode())
    git(tmp_path, "add", "-A")
    git(tmp_path, "commit", "-qm", "base")
    monkeypatch.setattr(G, "ROOT", tmp_path)
    return tmp_path


def rename_row(repo):
    """The 2026-10-06 shape: the unit's view changes class-key, its row is renamed U->V."""
    (repo / "Unit.cpp").write_text('#include "Coord2D.h"\nvoid f(Coord2D *) {}\n')
    git(repo, "add", "Unit.cpp")
    (repo / LEDGER).write_text(HEAD + ROW.format(src="Unit.cpp").replace("?f@@", "?f@@V"))


def test_unstaged_ledger_rename_is_refused_at_commit(repo, capsys):
    rename_row(repo)                                  # positive control: passed the old hook
    assert G.main(["--staged"]) == 1
    assert LEDGER in capsys.readouterr().err


def test_staged_ledger_and_clean_trees_pass(repo):
    assert G.main(["--staged"]) == 0                  # nothing changed
    rename_row(repo)
    git(repo, "add", LEDGER)
    assert G.main(["--staged"]) == 0                  # rename staged with its unit
    (repo / "Other.cpp").write_text("int g;\n")       # unrelated unstaged edit
    assert G.main(["--staged"]) == 0


def test_windows_checkout_preserves_byte_bound_compiler_inputs(repo):
    """A clean autocrlf checkout must satisfy the guard without weakening it."""
    (repo / ".gitattributes").write_bytes((TOOLS.parent / ".gitattributes").read_bytes())
    git(repo, "config", "core.autocrlf", "true")
    git(repo, "config", "core.safecrlf", "false")
    for path in G.COMPILER_INPUTS:
        target = repo / path
        target.parent.mkdir(parents=True, exist_ok=True)
        target.write_bytes(b"fixture compiler input\nsecond line\n")
    git(repo, "add", ".gitattributes", *G.COMPILER_INPUTS)
    git(repo, "commit", "-qm", "compiler inputs")
    for path in G.COMPILER_INPUTS:
        (repo / path).unlink()
    git(repo, "checkout-index", "--", *G.COMPILER_INPUTS)

    assert G.main(["--staged"]) == 0
    assert G.main(["--commit", "HEAD"]) == 0
    for path in G.COMPILER_INPUTS:
        assert (repo / path).read_bytes() == b"fixture compiler input\nsecond line\n"

    # A real byte edit is still refused even when Git normalizes line endings.
    target = repo / G.COMPILER_INPUTS[0]
    target.write_bytes(target.read_bytes().replace(b"\n", b"\r\n"))
    assert G.main(["--staged"]) == 1
    assert G.main(["--commit", "HEAD"]) == 1


def test_push_refuses_a_ledger_that_is_not_the_pushed_commits(repo):
    head = git(repo, "rev-parse", "HEAD").strip()
    assert G.main(["--commit", head]) == 0
    rename_row(repo)
    assert G.main(["--commit", head]) == 1            # unstaged
    git(repo, "add", LEDGER)
    assert G.main(["--commit", head]) == 1            # staged but not in the pushed commit
    git(repo, "commit", "-qm", "rename")
    assert G.main(["--commit", git(repo, "rev-parse", "HEAD").strip()]) == 0


@pytest.mark.parametrize("path", ["tools/compiler_profiles.py", "vendor/clang23-x86/compiler.zip"])
def test_compiler_profile_inputs_are_bound_at_commit_and_push(repo, path):
    target = repo / path
    target.parent.mkdir(parents=True, exist_ok=True)
    target.write_bytes(b"original compiler input\n")
    git(repo, "add", path)
    git(repo, "commit", "-qm", "compiler input")
    assert G.main(["--staged"]) == 0
    target.write_bytes(b"changed compiler input\n")
    assert G.main(["--staged"]) == 1
    assert G.main(["--commit", "HEAD"]) == 1
    git(repo, "add", path)
    assert G.main(["--staged"]) == 0
    assert G.main(["--commit", "HEAD"]) == 1


DATA = "reverse/data_rows.csv"
DATA_HEAD = "name,address,address_kind,size,section,source,status,evidence,model\n"
DATA_ROW = "?g@@3HA,0x00403000,va,4,.data,Data.cpp,matched,ZH defines it,m\n"


def test_data_rows_staged_and_unstaged_divergence_is_refused(repo, capsys):
    """build.py byte-verifies a source's data rows from the working-tree
    data_rows.csv (tools/data_rows.py); the guard covered only functions.csv and
    symbols.csv, so an unstaged data row would have been proven instead."""
    (repo / DATA).write_text(DATA_HEAD)
    git(repo, "add", DATA)
    git(repo, "commit", "-qm", "data ledger")
    head = git(repo, "rev-parse", "HEAD").strip()
    (repo / DATA).write_text(DATA_HEAD + DATA_ROW)
    git(repo, "add", DATA)
    assert G.main(["--staged"]) == 0                  # the row is staged as it is on disk
    (repo / DATA).write_text(DATA_HEAD + DATA_ROW.replace("0x00403000", "0x00403004"))
    assert G.main(["--staged"]) == 1                  # and then moved, unstaged
    assert DATA in capsys.readouterr().err
    assert G.main(["--commit", head]) == 1            # not the pushed commit's either


@pytest.mark.parametrize("hook,call", [("pre-commit", "ledger_guard.py --staged"),
                                       ("pre-push", 'ledger_guard.py --commit "$local_sha"')])
def test_hooks_guard_before_any_build(hook, call):
    text = (TOOLS.parent / ".githooks" / hook).read_text(encoding="utf-8")
    assert call in text
    # A function definition (build_chunks) runs nothing where it stands; find the first
    # build the hook actually executes, inline or through the chunking helper.
    executed = re.sub(r"(?ms)^\w+\(\) \{\n.*?^\}\n", "", text)
    first_build = re.search(r"BUILD_POOL=|^\s*build_chunks ", executed, re.M)
    assert first_build and executed.index(call) < first_build.start()
