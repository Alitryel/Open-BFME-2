"""nightly_measure --actions: the hosted nightly (.github/workflows/nightly-measure.yml).

Fakes only: no build, link, gh or signing key. The handoff tests use real files; the
stage tests replace ActionsRun.run with a recorder and check what each stage would
start, with which secret, in which order; the workflow tests read the YAML itself."""
import json
import subprocess
import sys
from pathlib import Path

import pytest
import yaml

TOOLS = Path(__file__).resolve().parents[1]
REPO = TOOLS.parent
sys.path.insert(0, str(TOOLS))
import nightly_measure as nm

COMMIT = "0123456789abcdef0123456789abcdef01234567"
WORKFLOW = REPO / ".github" / "workflows" / "nightly-measure.yml"


def write(path, data=b"x"):
    path = Path(path)
    path.parent.mkdir(parents=True, exist_ok=True)
    path.write_bytes(data)
    return path


def boot_sources(tmp_path):
    match, boot = tmp_path / "co" / "build" / "match", tmp_path / "co" / "build" / "boot" / "nightly"
    write(match / "a.obj", b"obj")
    write(match / "a.deps.json", b"{}")
    write(boot / "relayout.json", b"{}")
    write(boot / "relayout.exe", b"MZ")
    write(boot / "branches.pkl", b"pickle")          # never handed over
    return {"match": match, "boot": boot}


def args_for(tmp_path, **kw):
    argv = ["--actions", kw.pop("stage", "validate"), "--commit", COMMIT, "--state-dir", str(tmp_path / "state"),
            "--snapshot-dir", str(tmp_path / "lcs"), "--repo", "example/repo"]
    for key, value in kw.items():
        argv += ["--" + key.replace("_", "-")] + ([] if value is True else [str(value)])
    return nm.parse(argv)


@pytest.mark.parametrize("kind,rel,ok", [
    ("boot", "match/a.obj", True), ("boot", "match/a.deps.json", True), ("boot", "boot/relayout.json", True),
    ("boot", "boot/relayout.exe", True), ("boot", "boot/branches.pkl", False), ("boot", "boot/evil.py", False),
    ("boot", "match/sub/a.obj", False), ("boot", "tools/build.py", False), ("boot", "match/a.dll", False),
    ("cycle", "bundle/manifest.json", True), ("cycle", "bundle/sub/x", False),
    ("cycle", "snapshot/build/link_cycle/receipt.json", True), ("cycle", "snapshot/build/match/a.obj", True),
    ("cycle", "snapshot/build/compiler_profiles/x/clang.exe", False), ("cycle", "snapshot/tools/link_cycle.py", False),
    ("cycle", "snapshot/build/link_cycle/x.py", False), ("cycle", "snapshot/SNAPSHOT.json", False),
])
def test_handoffs_carry_data_by_place_and_suffix_only(kind, rel, ok):
    assert nm.handoff_allowed(kind, rel) is ok


def test_a_handoff_round_trips_and_leaves_out_what_it_may_not_carry(tmp_path):
    files = nm.export_actions_handoff("boot", COMMIT, tmp_path / "h", boot_sources(tmp_path),
                                      report="boot/relayout.json")
    assert sorted(files) == ["boot/relayout.exe", "boot/relayout.json", "match/a.deps.json", "match/a.obj"]
    meta = nm.load_actions_handoff("boot", tmp_path / "h", COMMIT)
    assert meta["report"] == "boot/relayout.json" and meta["kind"] == "boot"


@pytest.mark.parametrize("fault", ["changed", "extra", "missing", "commit", "kind", "planted", "traversal"])
def test_a_tampered_or_foreign_handoff_is_refused(tmp_path, fault):
    out = tmp_path / "h"
    nm.export_actions_handoff("boot", COMMIT, out, boot_sources(tmp_path), report="boot/relayout.json")
    meta = json.loads((out / nm.HANDOFF).read_text())
    commit, kind = COMMIT, "boot"
    if fault == "changed":
        (out / "match" / "a.obj").write_bytes(b"other")
    elif fault == "extra":
        write(out / "match" / "b.obj")
    elif fault == "missing":
        (out / "boot" / "relayout.exe").unlink()
    elif fault == "commit":
        commit = "f" * 40
    elif fault == "kind":
        kind = "cycle"
    elif fault in ("planted", "traversal"):
        name = "boot/evil.py" if fault == "planted" else "match/../tools/x.obj"
        meta["files"][name] = nm.sha256_bytes(b"x")
        nm.write_json(out / nm.HANDOFF, meta)
    with pytest.raises(nm.Refused):
        nm.load_actions_handoff(kind, out, commit)


def test_install_never_merges_into_existing_content(tmp_path):
    write(tmp_path / "src" / "a.obj")
    write(tmp_path / "dest" / "old.obj")
    with pytest.raises(nm.Refused, match="fresh checkout"):
        nm.install_tree(tmp_path / "src", tmp_path / "dest")
    nm.install_tree(tmp_path / "src", tmp_path / "new")
    assert (tmp_path / "new" / "a.obj").read_bytes() == b"x"


def test_children_never_see_the_key_and_get_the_release_token_only_when_asked(tmp_path, monkeypatch):
    monkeypatch.setenv("BFME_OWNERSHIP_SIGNING_KEY", "secret-path")
    monkeypatch.setenv("BFME_RELEASE_TOKEN", "release-token")
    monkeypatch.setenv("GITHUB_TOKEN", "workflow-token")
    monkeypatch.setenv("GH_TOKEN", "other")
    monkeypatch.setenv(nm.SIGNERS_ENV, str(tmp_path / "pin"))
    monkeypatch.setattr(nm.shutil, "which", lambda name: str(tmp_path / f"{name}.exe"))
    r = nm.ActionsRun(args_for(tmp_path), REPO, out=lambda *_: None)
    plain, token = r.env(), r.env(token=True)
    for env in (plain, token):
        assert "BFME_OWNERSHIP_SIGNING_KEY" not in env and "GITHUB_TOKEN" not in env
        assert "BFME_RELEASE_TOKEN" not in env and env[nm.SIGNERS_ENV] == str(tmp_path / "pin")
    assert "GH_TOKEN" not in plain and token["GH_TOKEN"] == "release-token"
    monkeypatch.delenv("BFME_RELEASE_TOKEN")
    with pytest.raises(nm.Refused, match="BFME_RELEASE_TOKEN"):
        r.env(token=True)


def test_checker_bytecode_never_lands_in_the_checkout(tmp_path, monkeypatch):
    root = tmp_path / "root"
    write(root / "tools" / "probe_mod.py", b"VALUE = 1\n")
    monkeypatch.setattr(nm.shutil, "which", lambda name: str(tmp_path / f"{name}.exe"))
    r = nm.ActionsRun(args_for(tmp_path), root, out=lambda *_: None)
    r.work.mkdir(parents=True)
    assert r.run("import", r.checker("import sys\nsys.path.insert(0, sys.argv[1])\nimport probe_mod\n")) == 0
    assert not (root / "tools" / "__pycache__").exists() and list((r.work / "pycache").rglob("*.pyc"))


def test_a_guarded_checker_cannot_start_another_program(tmp_path, monkeypatch):
    monkeypatch.setattr(nm.shutil, "which", lambda name: str(tmp_path / f"{name}.exe"))
    r = nm.ActionsRun(args_for(tmp_path), REPO, out=lambda *_: None)
    r.work.mkdir(parents=True)
    with pytest.raises(nm.StepFailed):
        r.run("evil", r.checker("import subprocess, sys\nsubprocess.run([sys.executable, '-V'])\n"))
    assert "publisher refused executable" in (r.work / "logs" / "evil.log").read_text()
    assert r.run("fine", r.checker("print('ok')\n")) == 0


class Recorder:
    def __init__(self, r, fail=None, codes=None):
        self.calls, self.fail, self.codes = [], fail, dict(codes or {})
        r.run = self

    def __call__(self, name, argv, cwd=None, token=False, guarded=True, ok=(0,)):
        self.calls.append(dict(name=name, argv=[str(a) for a in argv], token=token, guarded=guarded))
        if name == self.fail:
            raise nm.StepFailed(name)
        rc = self.codes.get(name, 0)
        if rc not in ok:
            raise nm.StepFailed(name)
        return rc

    def names(self):
        return [c["name"] for c in self.calls]


def handoffs(tmp_path):
    nm.export_actions_handoff("boot", COMMIT, tmp_path / "hb", boot_sources(tmp_path), report="boot/relayout.json")
    snap = tmp_path / "builder-lcs" / COMMIT[:10]
    write(snap / "build" / "link_cycle" / "receipt.json", b"{}")
    write(snap / "build" / "match" / "s.obj")
    write(snap / nm.SNAPSHOT_MARK, b"{}")
    write(tmp_path / "bundle" / "manifest.json", b"{}")
    nm.export_actions_handoff("cycle", COMMIT, tmp_path / "hc", {"snapshot": snap, "bundle": tmp_path / "bundle"})


def publisher(tmp_path, monkeypatch, stage="validate", **kw):
    root = tmp_path / "root"
    root.mkdir(exist_ok=True)
    handoffs(tmp_path)
    monkeypatch.setattr(nm.ActionsRun, "check_checkout", lambda r: None)
    monkeypatch.setattr(nm, "clang_cache", lambda tree: None)
    monkeypatch.setattr(nm.PublisherRun, "check_artifact_paths", lambda view: None)
    monkeypatch.setattr(nm.ActionsRun, "recompute_rank", lambda r, bundle: r.run("rank", r.tool("data_back_rank.py")))
    monkeypatch.setattr(nm, "wait_cooldown", lambda clock, say, now=None, sleep=None: 0)
    r = nm.ActionsRun(args_for(tmp_path, stage=stage, boot_handoff=tmp_path / "hb", cycle_handoff=tmp_path / "hc",
                               **kw), root, out=lambda *_: None)
    return r, Recorder(r)


def test_validate_installs_data_exports_its_own_snapshot_and_checks_without_a_secret(tmp_path, monkeypatch):
    r, rec = publisher(tmp_path, monkeypatch)
    assert r.go("validate") == nm.EXIT_OK
    assert rec.names() == ["snapshot", "snapshot-proof", "handoff-validate", "rank", "ownership-measure"]
    snapshot, proof, checks, _, own = rec.calls
    assert nm.SNAPSHOT_PROOF in proof["argv"] and proof["argv"][-1] == str(r.snapshot())
    assert not snapshot["guarded"] and "export_snapshot" in snapshot["argv"][snapshot["argv"].index("-c") + 1]
    assert nm.PUBLISHER_CHECKS in checks["argv"] and checks["argv"][-1] == COMMIT
    assert own["argv"][-3:] == ["", "", "measure"] and nm.PUBLISHER_OWNERSHIP in own["argv"]
    assert not any(c["token"] for c in rec.calls) and all(c["guarded"] for c in rec.calls[1:])
    assert (r.root / "build" / "match" / "a.obj").is_file()
    assert (r.snapshot() / "build" / "link_cycle" / "receipt.json").is_file()
    assert not (r.snapshot() / nm.SNAPSHOT_MARK).exists()        # the export (faked) writes the marker
    assert not (r.root / nm.BOOT_OUT / "branches.pkl").exists()
    assert r.state()["validated_utc"]


def test_validate_refuses_a_reused_state_directory(tmp_path, monkeypatch):
    r, rec = publisher(tmp_path, monkeypatch)
    write(r.work / "leftover")
    with pytest.raises(nm.Refused, match="not empty"):
        r.go("validate")
    assert rec.calls == []


@pytest.mark.parametrize("fail", [None, "ownership-sign"])
def test_sign_deletes_the_key_whatever_happens(tmp_path, monkeypatch, fail):
    pin = write(tmp_path / "secrets" / "allowed_signers", b"publisher ...")
    key = write(tmp_path / "secrets" / "key", b"PRIVATE")
    monkeypatch.setenv(nm.SIGNERS_ENV, str(pin))
    r, rec = publisher(tmp_path, monkeypatch, stage="sign", signing_key=key)
    rec.fail = fail
    r.work.mkdir(parents=True)
    write(r.root / nm.HISTORY_CSV, b"row\n")
    r.save_state(commit=COMMIT, validated_utc="t", report=str(r.root / nm.BOOT_OUT / "relayout.json"))
    if fail:
        with pytest.raises(nm.StepFailed):
            r.go("sign")
    else:
        assert r.go("sign") == nm.EXIT_OK
        assert rec.calls[0]["argv"][-3:] == [str(key), str(pin), "record"]
        assert (r.work / "image_ownership_history.csv").read_bytes() == b"row\n"
    assert not key.exists()


@pytest.mark.parametrize("fault", ["unvalidated", "pin-inside", "no-pin"])
def test_sign_refuses_before_any_signature(tmp_path, monkeypatch, fault):
    key = write(tmp_path / "secrets" / "key", b"PRIVATE")
    r, rec = publisher(tmp_path, monkeypatch, stage="sign", signing_key=key)
    r.work.mkdir(parents=True)
    if fault != "unvalidated":
        r.save_state(commit=COMMIT, validated_utc="t", report="r")
    if fault == "pin-inside":
        monkeypatch.setenv(nm.SIGNERS_ENV, str(write(r.root / "pin")))
    else:
        monkeypatch.delenv(nm.SIGNERS_ENV, raising=False)
    with pytest.raises(nm.Refused):
        r.go("sign")
    assert rec.calls == [] and not key.exists()


@pytest.mark.parametrize("previous", [0, nm.EMPTY_STORE])
def test_publish_order_cooldowns_and_token_scope(tmp_path, monkeypatch, previous):
    monkeypatch.setenv("BFME_RELEASE_TOKEN", "t")
    r, rec = publisher(tmp_path, monkeypatch, stage="publish")
    rec.codes["previous"] = previous
    r.work.mkdir(parents=True)
    r.save_state(signed_utc="t", report=str(tmp_path / "report.json"))
    if previous == 0:
        nm.write_json(r.work / "cycle_bundles" / "current.json", {"latest_measurement": "m1"})
    nm.write_json(r.work / "bundle" / "manifest.json", {"tag": "link-cycle/abc-20261025T000000Z-def"})
    waits = []
    monkeypatch.setattr(nm, "wait_cooldown", lambda clock, say, now=None, sleep=None: waits.append(clock) or 0)
    monkeypatch.setattr(nm.ActionsRun, "executables", lambda r: {"git": "git", "gh": "gh", "ssh-keygen": "k"})
    assert r.go("publish") == nm.EXIT_OK
    assert rec.names() == ["validate", "closure", "previous", "bundle", "publish", "ownership-release"]
    assert [c["name"] for c in rec.calls if c["token"]] == ["previous", "publish", "ownership-release"]
    bundle = rec.calls[3]["argv"]
    assert ("--first" in bundle) == (previous == nm.EMPTY_STORE)
    assert "--rank" in bundle and bundle[bundle.index("--rank") + 1] == "run-dir"
    assert bundle[bundle.index("--snapshot-root") + 1] == str(r.snapshot())   # a changed tree refuses
    assert nm.PUBLISHER_PUBLISH in rec.calls[4]["argv"] and "--dry-run" not in rec.calls[4]["argv"]
    release = rec.calls[5]["argv"]
    assert nm.PUBLISHER_OWNERSHIP_RELEASE in release and rec.calls[5]["guarded"]
    i = release.index(nm.PUBLISHER_OWNERSHIP_RELEASE) + 2
    assert release[i:i + 3] == ["example/repo", "ownership-link-cycle-abc-20261025T000000Z-def", COMMIT]
    assert "gh" not in release and "release" not in release   # never a bare `gh release create --target`
    assert len(waits) == 2 and json.loads((r.work / "push_clock.json").read_text())["last_write"]


def test_the_ownership_release_child_takes_the_guarded_lifecycle(tmp_path, monkeypatch, capsys):
    """The child nightly_measure starts, run in-process against publish_cycle's fake GitHub:
    a planted tag at another commit is refused before anything is created."""
    sys.path.insert(0, str(Path(__file__).resolve().parent))
    import cycle_artifacts as ca
    import cycle_fixture as cf
    from test_cycle_artifacts import FakeGitHub
    tag = "ownership-link-cycle-abc-20261025T000000Z-def"
    files = [str(write(tmp_path / n, n.encode())) for n in ("image_ownership.json", "image_ownership_history.csv",
                                                             "relayout.json")]
    for planted in (True, False):
        gh = FakeGitHub()
        if planted:
            gh.tags[tag] = cf.OTHER
        monkeypatch.setattr(ca, "Gh", lambda gh=gh: gh)
        monkeypatch.setattr(sys, "argv", ["-c", str(TOOLS), "Open-BFME/Open-BFME-2", tag, cf.COMMIT, tag, "n", *files])
        if planted:
            with pytest.raises(SystemExit, match="ownership release refused: the git tag .* already exists"):
                exec(nm.PUBLISHER_OWNERSHIP_RELEASE, {})
            assert not [c for c in gh.calls if c[0] == "release"] and gh.tags[tag] == cf.OTHER
        else:
            exec(nm.PUBLISHER_OWNERSHIP_RELEASE, {})
            (release,) = gh.releases
            assert release["immutable"] and not release["draft"] and gh.tags[tag] == cf.COMMIT


def test_no_publish_is_a_dry_run_without_a_github_write(tmp_path, monkeypatch):
    monkeypatch.setenv("BFME_RELEASE_TOKEN", "t")
    r, rec = publisher(tmp_path, monkeypatch, stage="publish", no_publish=True)
    rec.codes["previous"] = nm.EMPTY_STORE
    r.work.mkdir(parents=True)
    r.save_state(signed_utc="t", report="r")
    assert r.go("publish") == nm.EXIT_OK
    assert rec.names()[-1] == "publish" and "--dry-run" in rec.calls[-1]["argv"]
    assert not (r.work / "push_clock.json").exists()


def test_publish_refuses_without_a_signed_row(tmp_path, monkeypatch):
    r, rec = publisher(tmp_path, monkeypatch, stage="publish")
    r.work.mkdir(parents=True)
    with pytest.raises(nm.Refused, match="sign has not passed"):
        r.go("publish")
    assert rec.calls == []


def git(cwd, *args):
    return subprocess.run(["git", "-C", str(cwd), *args], check=True, capture_output=True, text=True).stdout.strip()


@pytest.fixture
def history_repo(tmp_path, monkeypatch):
    root = tmp_path / "root"
    write(root / nm.HISTORY_CSV, b"header\n")
    write(root / "README", b"r\n")
    git(tmp_path, "init", "-q", str(root))
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "add", ".")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "base")
    monkeypatch.setattr(nm, "wait_cooldown", lambda clock, say, now=None, sleep=None: 0)
    r = nm.ActionsRun(args_for(tmp_path, stage="history"), root, out=lambda *_: None)
    r.work.mkdir(parents=True)
    r.save_state(published_utc="t")
    return r


def test_history_cleans_the_artifacts_and_commits_through_the_hooks(history_repo):
    r = history_repo
    (r.root / nm.HISTORY_CSV).write_bytes(b"header\nrow\n")
    write(r.root / "build" / "match" / "a.obj")
    write(r.snapshot() / "build" / "x")
    seen = []
    rec = Recorder(r)
    rec_call = rec.__call__

    def call(name, argv, **kw):
        if name == "history-commit":
            seen.append((r.root / "build" / "match").exists() or r.snapshot().exists())
        return rec_call(name, argv, **kw)
    r.run = call
    assert r.go("history") == nm.EXIT_OK
    assert seen == [False]
    assert rec.names() == ["history-add", "history-commit", "history-fetch-1", "history-rebase-1", "history-push-1"]
    for c in rec.calls[1:]:
        if c["name"] != "history-fetch-1":
            assert c["argv"][1:3] == ["-c", "core.hooksPath=.githooks"]
    assert rec.calls[-1]["argv"][-2:] == ["origin", "HEAD:master"]
    assert "--no-verify" not in " ".join(" ".join(c["argv"]) for c in rec.calls)


def test_history_retries_a_lost_push_race(history_repo):
    r = history_repo
    (r.root / nm.HISTORY_CSV).write_bytes(b"header\nrow\n")
    rec = Recorder(r)
    pushes = []
    rec_call = rec.__call__

    def call(name, argv, **kw):
        if name.startswith("history-push"):
            pushes.append(name)
            if len(pushes) == 1:
                raise nm.StepFailed(name)
        return rec_call(name, argv, **kw)
    r.run = call
    assert r.go("history") == nm.EXIT_OK
    assert pushes == ["history-push-1", "history-push-2"]


def test_history_refuses_any_change_but_the_row(history_repo):
    r = history_repo
    (r.root / nm.HISTORY_CSV).write_bytes(b"header\nrow\n")
    (r.root / "README").write_bytes(b"changed\n")
    rec = Recorder(r)
    with pytest.raises(nm.Refused, match="more than"):
        r.go("history")
    assert rec.calls == []


def test_check_checkout_refuses_another_commit_or_edited_tools(tmp_path):
    root = tmp_path / "root"
    write(root / "tools" / "a.py", b"print(1)\n")
    git(tmp_path, "init", "-q", str(root))
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "add", ".")
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "base")
    head = git(root, "rev-parse", "HEAD")
    args = nm.parse(["--actions", "validate", "--commit", head, "--state-dir", str(tmp_path / "s")])
    nm.ActionsRun(args, root).check_checkout()
    for planted in ("tools/__pycache__/a.cpython-312.pyc", "tools/planted.py"):
        write(root / planted)                                       # ignored or untracked: both refused
        with pytest.raises(nm.Refused, match="code differs"):
            nm.ActionsRun(args, root).check_checkout()
        (root / planted).unlink()
    args.commit = "f" * 40
    with pytest.raises(nm.Refused, match="not the measured"):
        nm.ActionsRun(args, root).check_checkout()


def test_cli_runs_actions_alone_and_publication_names_its_repository(tmp_path):
    quiet = lambda *_: None
    assert nm.main(["--actions", "publish", "--commit", COMMIT, "--state-dir", str(tmp_path)], root=tmp_path,
                   out=quiet) == nm.EXIT_SETUP
    assert nm.main(["--actions", "validate", "--role", "publisher"], root=tmp_path, out=quiet) == nm.EXIT_SETUP


# ---------------------------------------------------------------- the workflow itself

@pytest.fixture(scope="module")
def workflow():
    return yaml.safe_load(WORKFLOW.read_text(encoding="utf-8"))


def job_text(job):
    return json.dumps(job)


def test_workflow_is_scheduled_dispatchable_and_never_overlaps(workflow):
    on = workflow.get("on", workflow.get(True))                 # YAML 1.1 reads `on` as True
    assert "schedule" in on and "workflow_dispatch" in on
    assert workflow["concurrency"]["cancel-in-progress"] is False
    assert workflow["permissions"] == {"contents": "read"}


def test_build_jobs_hold_no_secret_and_publish_nothing(workflow):
    for name in ("boot", "cycle"):
        job = workflow["jobs"][name]
        text = job_text(job)
        assert job["runs-on"] == "windows-2025" and job["permissions"] == {"contents": "read"}
        assert "environment" not in job and "secrets." not in text and "github.token" not in text
        assert "boot_smoke" not in text and "game_smoke" not in text
        assert all(s.get("with", {}).get("persist-credentials") is False
                   for s in job["steps"] if str(s.get("uses", "")).startswith("actions/checkout"))
    boot = job_text(workflow["jobs"]["boot"])
    assert "--fetch-index" not in boot and "tools/build.py" in boot and "--relayout" in boot and "--own-data" in boot
    assert "image_ownership.py report" in boot and "--actions handoff-boot" in boot
    cycle = job_text(workflow["jobs"]["cycle"])
    assert "link_cycle.py --snapshot" in cycle and "--actions handoff-cycle" in cycle


def test_publish_job_is_the_only_secret_holder_and_deletes_the_key(workflow):
    job = workflow["jobs"]["publish"]
    assert set(job["needs"]) == {"boot", "cycle"} and job["environment"] == "nightly-publish"
    assert job["permissions"] == {"contents": "write"} and job["runs-on"] == "windows-2025"
    steps = job["steps"]
    names = [s.get("name", s.get("uses", "")) for s in steps]
    run = [s.get("run", "") for s in steps]
    stage = lambda word: next(i for i, text in enumerate(run) if f"--actions {word} " in text)
    key_written = next(i for i, s in enumerate(steps) if "secrets.BFME_OWNERSHIP_SIGNING_KEY" in job_text(s))
    key_deleted = next(i for i, n in enumerate(names) if n == "Delete the signing key")
    assert stage("validate") < key_written < stage("sign") < key_deleted < stage("publish") < stage("history")
    assert steps[key_deleted]["if"] == "always()"
    for i, s in enumerate(steps):            # each secret reaches exactly the step that uses it
        text = job_text(s)
        if "BFME_OWNERSHIP_SIGNING_KEY" in text and "secrets." in text:
            assert i == key_written
        if "BFME_RELEASE_TOKEN" in text:
            assert i == stage("publish")
        if "github.token" in text:
            assert i == stage("history")
    checkout = next(s for s in steps if str(s.get("uses", "")).startswith("actions/checkout"))
    assert checkout["with"]["persist-credentials"] is False and checkout["with"]["ref"] == "${{ github.sha }}"
    assert "--no-verify" not in job_text(job)


def test_every_action_is_pinned_to_a_full_commit_sha_with_its_version():
    import re
    uses = re.findall(r"^\s*(?:- )?uses: (\S+)(.*)$", WORKFLOW.read_text(encoding="utf-8"), re.M)
    assert uses
    for ref, comment in uses:
        assert re.fullmatch(r"[\w.-]+/[\w.-]+@[0-9a-f]{40}", ref), ref
        assert re.fullmatch(r"\s+# v\d+\.\d+\.\d+", comment), (ref, comment)


def test_all_jobs_resolve_one_exact_toolchain(workflow):
    constraints = REPO / workflow["env"]["CONSTRAINTS"]
    pins = dict(line.split("==") for line in constraints.read_text(encoding="utf-8").splitlines()
                if line and not line.startswith("#"))
    assert {"capstone", "pefile"} <= set(pins)
    for name, job in workflow["jobs"].items():
        assert job["runs-on"] == "windows-2025", name
        steps = job["steps"]
        python = [s["with"]["python-version"] for s in steps if "setup-python" in str(s.get("uses", ""))]
        assert len(python) == 1 and python[0].count(".") == 2, (name, python)
        installs = [s["run"] for s in steps if "pip install" in s.get("run", "")]
        assert installs and all("-c ${{ env.CONSTRAINTS }}" in r or "-c $env:CONSTRAINTS" in r for r in installs)


def test_build_jobs_upload_their_logs_even_when_they_fail(workflow):
    for name, wanted in (("boot", ["build/boot/nightly/*.json", "build/boot/nightly/*.log"]),
                         ("cycle", ["${{ runner.temp }}/lcs/*/build/link_cycle/*.log",
                                    "${{ runner.temp }}/lcs/*/build/link_cycle/receipt.json"])):
        logs = [s for s in workflow["jobs"][name]["steps"]
                if s.get("if") == "always()" and "upload-artifact" in str(s.get("uses", ""))]
        assert len(logs) == 1 and logs[0]["with"]["path"].splitlines() == wanted, name
    cycle = workflow["jobs"]["cycle"]
    step = next(s for s in cycle["steps"] if "link_cycle.py --snapshot" in s.get("run", ""))
    assert step["timeout-minutes"] < cycle["timeout-minutes"]


def test_the_workflow_runs_the_stages_this_tool_defines(workflow):
    text = WORKFLOW.read_text(encoding="utf-8")
    used = {stage for stage in nm.ACTIONS_STAGES if f"--actions {stage} " in text}
    assert used == set(nm.ACTIONS_STAGES)


def test_docs_mark_the_local_setup_superseded_and_name_the_hosted_setup():
    local = (REPO / "docs" / "nightly_setup.md").read_text(encoding="utf-8")
    hosted = (REPO / "docs" / "nightly_actions.md").read_text(encoding="utf-8")
    assert "Superseded" in local.split("\n\n")[0] + local.split("\n\n")[1]
    for word in ("nightly-publish", "BFME_OWNERSHIP_SIGNING_KEY", "BFME_OWNERSHIP_ALLOWED_SIGNERS",
                 "BFME_RELEASE_TOKEN", "PUBLISHERS", "immutable", "workflow_dispatch", "builder-attested"):
        assert word in hosted


@pytest.mark.parametrize("fault", ["none", "txt", "json"])
def test_validate_recomputes_the_rank_with_the_real_ranker_in_a_guarded_child(tmp_path, monkeypatch, fault):
    import shutil
    import data_back_rank
    root = tmp_path / "root"
    shutil.copytree(TOOLS, root / "tools", ignore=shutil.ignore_patterns("tests", "__pycache__", "audit"))
    monkeypatch.setattr(nm.shutil, "which", lambda name: str(tmp_path / f"{name}.exe"))
    r = nm.ActionsRun(args_for(tmp_path), root, out=lambda *_: None)
    r.work.mkdir(parents=True)
    run, base = r.cycle_dir(), r.snapshot()
    write(base / "reverse/data_ledger.csv", b"address,size,section,kind,name,source,status,names,defs,refs\n")
    write(base / "reverse/functions.csv", b"name,source\n")
    write(base / "reverse/exports.csv", b"name,rva\n")
    write(run / "link_status.csv", (",".join(data_back_rank.STATUS_COLUMNS) + "\n").encode())
    write(run / "data_fold_list.csv", b"address,verdict\n")
    bundle = tmp_path / "bundle"
    bundle.mkdir()
    args = ["--status", "link_status.csv", "--folds", "data_fold_list.csv", "--ledger", base / "reverse/data_ledger.csv",
            "--functions", base / "reverse/functions.csv", "--exports", base / "reverse/exports.csv", "--no-objects",
            "--json", bundle / "data_back_rank.json"]
    made = subprocess.run([sys.executable, "-I", "-c", nm.SCRIPT_BOOT, root / "tools", root / "tools/data_back_rank.py",
                           *map(str, args)], cwd=run, capture_output=True)
    assert made.returncode == 0, made.stderr
    (bundle / "data_back_rank.txt").write_bytes(made.stdout.replace(b"\r\n", b"\n"))
    if fault != "none":
        (bundle / f"data_back_rank.{fault}").write_text("{}" if fault == "json" else "forged ranking")
        with pytest.raises(nm.Refused, match=f"recomputed data_back_rank.{fault} differs"):
            r.recompute_rank(bundle)
        return
    r.recompute_rank(bundle)
    for name in ("data_back_rank.txt", "data_back_rank.json"):
        assert (run / name).read_bytes() == (bundle / name).read_bytes()


@pytest.mark.parametrize("fault", ["none", "touched", "commit"])
def test_the_snapshot_proof_probe_uses_the_real_publish_cycle(tmp_path, monkeypatch, fault):
    import link_cycle
    snap = tmp_path / "lcs" / COMMIT[:10]
    write(snap / "Code" / "a.cpp", b"int a;\n")
    manifest = link_cycle.tree_manifest(snap)
    write(snap / nm.SNAPSHOT_MARK, json.dumps({"commit": COMMIT, "tree_manifest": manifest}).encode())
    receipt = {"commit": "f" * 40 if fault == "commit" else COMMIT, "tree_manifest": manifest}
    write(snap / "build" / "link_cycle" / "receipt.json", json.dumps(receipt).encode())
    if fault == "touched":
        (snap / "Code" / "a.cpp").write_bytes(b"int b; // edited after the run\n")
    monkeypatch.setattr(nm.shutil, "which", lambda name: str(tmp_path / f"{name}.exe"))
    r = nm.ActionsRun(args_for(tmp_path), REPO, out=lambda *_: None)
    r.work.mkdir(parents=True)
    if fault == "none":
        assert r.run("snapshot-proof", r.checker(nm.SNAPSHOT_PROOF, snap)) == 0
    else:
        with pytest.raises(nm.StepFailed):
            r.run("snapshot-proof", r.checker(nm.SNAPSHOT_PROOF, snap))
