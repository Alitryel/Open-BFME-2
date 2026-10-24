"""Isolation and environment invariants of the optional fleet launcher."""
import json
import os
from pathlib import Path
import subprocess
import sys

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import recovery_lab
import setup_local_fleet as fleet


def git(repo, *args):
    return subprocess.run(["git", "-c", "core.longpaths=true", "-C", str(repo), *args], check=True,
                          text=True, capture_output=True).stdout.strip()


def repo(path):
    path.mkdir()
    git(path, "init", "-b", "test")
    git(path, "config", "user.name", "Fixture")
    git(path, "config", "user.email", "fixture@example.invalid")
    (path / "readme").write_text("fixture\n")
    git(path, "add", "readme")
    git(path, "commit", "-m", "fixture")
    return path


def test_environment_preserves_git_options_and_stable_owner(monkeypatch, tmp_path):
    monkeypatch.setenv("GIT_CONFIG_COUNT", "1")
    monkeypatch.setenv("GIT_CONFIG_KEY_0", "example.existing")
    monkeypatch.setenv("GIT_CONFIG_VALUE_0", "keep")
    manifest = {"python": sys.executable, "python_deps": str(tmp_path / "deps"),
                "host_bin": str(tmp_path / "bin"), "blocker_db": str(tmp_path / "queue.sqlite3")}
    env = recovery_lab.worker_environment(manifest, {"owner": "fleet-w01"})
    assert env["GIT_CONFIG_COUNT"] == "2"
    assert env["GIT_CONFIG_VALUE_0"] == "keep"
    assert env["GIT_CONFIG_KEY_1"] == "fetch.recurseSubmodules"
    assert env["GIT_CONFIG_VALUE_1"] == "false"
    assert env["BFME_CLAIM_OWNER"] == "fleet-w01"
    assert env["BUILD_POOL"] == "1"
    assert env["BFME_BLOCKER_DB"] == manifest["blocker_db"]
    assert "GIT_CONFIG_KEY_1" not in os.environ


def test_worker_refuses_wrong_checkout(tmp_path):
    manifest = tmp_path / "fleet.json"
    manifest.write_text(json.dumps({"workers": [{"id": "w01", "path": str(tmp_path)}]}))
    with pytest.raises(SystemExit):
        recovery_lab.run_worker(["--manifest", str(manifest), "--worker", "w01", "--", "status"])


def test_verify_requires_file_and_cannot_trigger_accidental_full_gate(tmp_path):
    root = Path(recovery_lab.__file__).resolve().parents[1]
    manifest = tmp_path / "fleet.json"
    manifest.write_text(json.dumps({"python": sys.executable,
                                   "workers": [{"id": "w01", "path": str(root)}]}))
    for args in (["verify"], ["verify", "../outside.cpp"], ["verify", "--help"]):
        with pytest.raises(SystemExit):
            recovery_lab.run_worker(["--manifest", str(manifest), "--worker", "w01", "--", *args])


def test_rejects_foreign_and_dirty_workers(tmp_path):
    source = repo(tmp_path / "source")
    worker = repo(tmp_path / "foreign")
    with pytest.raises(ValueError):
        fleet.preflight_short(source, tmp_path, [worker])
    # Test the identity/dirty checks independent of Windows path-length policy.
    marker = fleet.git_dir(worker) / "openbfme-fleet.json"
    marker.write_text(json.dumps({"source": str(source)}))
    (worker / "local.txt").write_text("preserve me")
    with pytest.raises(ValueError):
        fleet.preflight_short(source, tmp_path, [worker])
    assert (worker / "local.txt").read_text() == "preserve me"


def test_exact_local_reference_and_no_nested_initialization(tmp_path):
    source = repo(tmp_path / "source")
    (source / "reference").mkdir()
    nested = source / "reference" / "open-bfme-1"
    repo(nested)
    pin = git(nested, "rev-parse", "HEAD")
    git(source, "update-index", "--add", "--cacheinfo", f"160000,{pin},reference/open-bfme-1")
    (source / ".gitmodules").write_text(
        '[submodule "reference/open-bfme-1"]\npath = reference/open-bfme-1\nurl = https://example.invalid/reference.git\n')
    git(source, "add", ".gitmodules")
    git(source, "commit", "-m", "pin fixture")
    target = tmp_path / "worker"
    git(tmp_path, "clone", "--shared", str(source), str(target))
    assert fleet.prepare_reference(source, target) == pin
    assert git(target / "reference/open-bfme-1", "rev-parse", "HEAD") == pin
    assert fleet.prepare_reference(source, target) == pin
    (target / "reference/open-bfme-1" / "changed").write_text("dirty")
    with pytest.raises(ValueError, match="local changes"):
        fleet.prepare_reference(source, target)


def test_private_branch_clones_track_master_without_resetting_work(tmp_path):
    source = repo(tmp_path / "source")
    master = git(source, "rev-parse", "HEAD")
    git(source, "update-ref", "refs/remotes/origin/master", master)
    target = tmp_path / "worker"
    git(tmp_path, "clone", "--shared", "--single-branch", "--branch", "test", str(source), str(target))
    git(target, "config", "user.name", "Fixture")
    git(target, "config", "user.email", "fixture@example.invalid")
    (target / "own-work").write_text("preserve local commit")
    git(target, "add", "own-work")
    git(target, "commit", "-m", "local unpublished work")
    local = git(target, "rev-parse", "HEAD")
    fleet.track_master(source, target)
    assert git(target, "rev-parse", "origin/master") == master
    assert git(target, "rev-parse", "HEAD") == local
    assert git(target, "rev-parse", "--abbrev-ref", "--symbolic-full-name", "@{upstream}") == "origin/master"
    assert git(target, "config", "remote.origin.fetch") == "+refs/heads/master:refs/remotes/origin/master"
    # Re-running setup does not rewind a newer fetched remote tip.
    git(target, "update-ref", "refs/remotes/origin/master", local)
    fleet.track_master(source, target)
    assert git(target, "rev-parse", "origin/master") == local
