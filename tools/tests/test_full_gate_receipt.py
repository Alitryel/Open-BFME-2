"""A passed full gate carries to a later push only from a commit of this
clone, while the verifier is unchanged and header_dependents can bound the
change between them (tools/full_gate_receipt.py)."""
import os
import subprocess
import sys
import time
from pathlib import Path

import pytest
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import full_gate_receipt as R


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, check=True).stdout.strip()


def commit(root, path, text):
    (root / path).parent.mkdir(parents=True, exist_ok=True)
    (root / path).write_text(text)
    git(root, "add", path)
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", path)
    return git(root, "rev-parse", "HEAD")


@pytest.fixture
def repo(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    root.mkdir()
    git(root, "init", "-q")
    monkeypatch.setattr(R, "ROOT", root)
    monkeypatch.setattr(R, "bounded", lambda old, new: True)
    return root


def test_a_rebased_push_carries_the_full_gate_it_passed(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    assert R.find(c0) == c0
    c1 = commit(repo, "Code/b.cpp", "2")  # master moved: the rebased push
    assert R.find(c1) == c0


def test_no_carry_across_a_verifier_change(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    assert R.find(commit(repo, "tools/build.py", "changed")) is None
    c2 = commit(repo, "Code/c.cpp", "3")
    R.record(c2)
    assert R.find(commit(repo, ".githooks/pre-push", "changed")) is None


def test_no_carry_when_the_change_is_unbounded(repo, monkeypatch):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    c1 = commit(repo, "vendor/stlport/x.h", "2")
    monkeypatch.setattr(R, "bounded", lambda old, new: False)
    assert R.find(c1) is None


def test_expired_or_foreign_receipts_carry_nothing(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    stale = time.time() - (R.KEEP_HOURS + 1) * 3600
    os.utime(R.receipts_dir() / c0, (stale, stale))
    assert R.find(commit(repo, "Code/b.cpp", "2")) is None
    (R.receipts_dir() / ("f" * 40)).write_text("0\n")  # not a commit of this clone
    assert R.recorded() == []


def test_the_nearest_receipt_is_tried_first(repo, monkeypatch):
    far = commit(repo, "Code/a.cpp", "1")
    R.record(far)
    commit(repo, "Code/b.cpp", "2")
    near = commit(repo, "Code/c.cpp", "3")
    R.record(near)
    os.utime(R.receipts_dir() / near, (time.time() - 60, time.time() - 60))  # older record, nearer tree
    tried = []
    monkeypatch.setattr(R, "bounded", lambda old, new: tried.append(old) or True)
    assert R.find(commit(repo, "Code/d.cpp", "4")) == near and tried == [near]


def test_no_carry_across_a_tree_wide_baseline_change(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    assert R.find(commit(repo, "reverse/gate_baseline.txt", "one debt line fewer")) is None
    c2 = commit(repo, "Code/b.cpp", "2")
    R.record(c2)
    # the exception-data and converged lists are re-audited by the hook instead
    assert R.find(commit(repo, "reverse/eh_baseline.csv", "shrunk")) == c2
