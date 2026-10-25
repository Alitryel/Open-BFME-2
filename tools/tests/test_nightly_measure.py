"""nightly_measure: step order, stop-on-failure, the approval, the lock, the cooldown and
the snapshot leases; the ownership step against the REAL image_ownership.measure().

The runner's subprocesses are mocked (FakeTools): nothing here runs a gate, a
link or gh. The fake writes what each real tool leaves behind (the cycle
receipt, the boot report, the store pointer) so the runner's own checks see it.
The lock tests use real processes; the ownership test the real module."""
import copy
import hashlib
import json
import os
import shlex
import subprocess
import sys
import tempfile
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import nightly_measure as nm

COMMIT = "0123456789abcdef0123456789abcdef01234567"
RUNNER_BYTES = nm.RUNNER.read_bytes()
IDENT = {"tools_tree": "t" * 40, "githooks_tree": "h" * 40, "vendor_tree": "v" * 40, "submodule": "s" * 40,
         "runner_sha256": hashlib.sha256(RUNNER_BYTES).hexdigest()}
MASTER2 = "m" * 40                                   # origin/master as the history step resolves it
BLOCKING = ["fetch", "checkout", "submodule", "clean", "gate", "cycle", "receipt", "validate", "closure", "previous",
            "bundle", "publish", "install"]
AFTER = ["boot", "ownership", "history-add", "history-commit", "history-fetch-1", "history-rebase-1",
         "history-push-1"]
FULL = BLOCKING + AFTER


def tail(argv):
    """What a Python child runs, past the isolated interpreter and its import dir: a tool as
    ["tools/<name>.py", args...], the ownership probe as its arguments."""
    i = argv.index("-c")
    if argv[i + 1] == nm.OWNERSHIP_PROBE:
        return argv[i + 3:]
    return ["tools/" + Path(argv[i + 3]).name, *argv[i + 4:]]


def name_of(argv):
    """The logical step a mocked command belongs to."""
    if argv[0] == "git":
        while len(argv) > 2 and argv[1] == "-c":
            argv = [argv[0], *argv[3:]]
        return {"add": "history-add", "commit": "history-commit", "rebase": "history-rebase",
                "push": "history-push"}.get(argv[1], argv[1])
    i = argv.index("-c")
    if argv[i + 1] == nm.OWNERSHIP_PROBE:
        return "ownership"
    t = tail(argv)
    tool, sub = Path(t[0]).name, (t[1] if len(t) > 1 else "")
    return {"build.py": "gate", "link_cycle.py": "cycle", "boot_image.py": "boot", "closure_report.py": "closure",
            "cycle_artifacts.py": "fetch-store"}.get(tool) or sub


def git_args(argv):
    while len(argv) > 2 and argv[1] == "-c":
        argv = [argv[0], *argv[3:]]
    return argv[1:]


class FakeTools:
    """subprocess.run for the runner: git queries answered, every other command recorded."""

    def __init__(self, run, codes=None, receipt=None, boot_report=None, store_latest=None):
        self.run, self.codes = run, dict(codes or {})
        self.receipt = {"commit": COMMIT, "authoritative": True, "core_sha256": "c" * 64, **(receipt or {})}
        self.boot_report = {"link_exit": 0} if boot_report is None else boot_report
        self.store_latest = store_latest
        self.calls, self.names, self.fetches = [], [], 0
        self.ident, self.by_rev = dict(IDENT), {}         # HEAD's (and any rev's) identity; per-rev overrides
        self.symbolic_ref, self.dirty, self.code_dirty, self.hooks = 1, "", "", ".githooks"
        self.history_changed = True
        self.history_master, self.resolves, self.merge_base = None, 0, 0
        self.fail_query = lambda args: False
        self.log = []                                      # ("q", git args) and ("run", step name), in order

    def query(self, args):
        while len(args) > 2 and args[0] == "-c":
            args = args[2:]
        self.log.append(("q", args))
        if self.fail_query(args):
            return 1, ""
        if args[0] == "rev-parse" and args[-1] == "origin/master^{commit}":
            self.resolves += 1
            return 0, (self.history_master or COMMIT) if self.resolves > 1 else COMMIT
        if args[0] == "rev-parse" and ":" in args[-1]:
            rev, path = args[-1].split(":", 1)
            ident = self.by_rev.get(rev, self.ident)
            return 0, {"tools": ident["tools_tree"], ".githooks": ident["githooks_tree"],
                       "vendor": ident["vendor_tree"]}.get(path, ident["submodule"])
        if args[0] == "rev-parse":
            return 0, COMMIT
        if args[0] == "merge-base":
            return self.merge_base, ""
        if args[0] == "show":
            ident = self.by_rev.get(args[1].split(":", 1)[0], self.ident)
            return 0, RUNNER_BYTES if ident["runner_sha256"] == IDENT["runner_sha256"] else b"other runner"
        if args[0] == "status":
            if "--untracked-files=no" in args:
                return 0, self.dirty
            if nm.HISTORY_CSV in args and "tools" not in args:
                return 0, f" M {nm.HISTORY_CSV}" if self.history_changed else ""
            return 0, self.code_dirty
        if args[0] == "symbolic-ref":
            return self.symbolic_ref, ""
        if args[0] == "config":
            return (1, "") if "--get-regexp" in args else (0, self.hooks)
        if args[0] == "ls-tree":
            return 0, b""
        if args[0] == "ls-files":
            return 0, b""
        return 0, ""

    def __call__(self, argv, cwd=None, capture_output=False, text=False, env=None, **kw):
        argv = [str(a) for a in argv]
        if capture_output:
            code, out = self.query(argv[1:])
            out = out if isinstance(out, bytes) else (out + "\n")
            if not text and isinstance(out, str):
                out = out.encode()
            return subprocess.CompletedProcess(argv, code, out, "")
        name = name_of(argv)
        if name == "fetch-store":
            self.fetches += 1
            name = "previous" if self.fetches == 1 else "install"
        self.calls.append(argv)
        self.names.append(name)
        self.log.append(("run", name))
        code = self.codes.get(name, 0)
        if code == "interrupt":
            raise KeyboardInterrupt
        self.side_effect(name, argv, code)
        return subprocess.CompletedProcess(argv, code)

    def side_effect(self, name, argv, code):
        r = self.run
        if name == "worktree":
            r.checkout.mkdir(parents=True)
        if name == "cycle" and code == 0:
            r.cycle_dir().mkdir(parents=True, exist_ok=True)
            (r.snapshot() / nm.SNAPSHOT_MARK).write_text("{}")
            (r.cycle_dir() / "receipt.json").write_text(json.dumps(self.receipt))
        if name == "boot" and self.boot_report != "none":
            out = Path(argv[argv.index("--out") + 1])
            out.mkdir(parents=True, exist_ok=True)
            report = out / f"{argv[argv.index('--tag') + 1]}.json"
            report.write_text(json.dumps(self.boot_report))
            # Fake filesystem timestamps need not share Python's precision.
            os.utime(report, (time.time() + 1, time.time() + 1))
        if name == "previous" and code == 0:
            r.store.mkdir(parents=True, exist_ok=True)
            (r.store / "current.json").write_text(json.dumps({"latest_measurement": self.store_latest}))
        if name == "ownership" and code == 0:
            (r.checkout / nm.HISTORY_CSV).parent.mkdir(parents=True, exist_ok=True)
            (r.checkout / nm.HISTORY_CSV).write_text("date\nrow\n")

    def ran(self, name):
        return [a for a, n in zip(self.calls, self.names) if n == name]

    def queries_between(self, after, before):
        """The git queries made after the step `after` ran and before `before` ran."""
        i = self.log.index(("run", after))
        j = self.log.index(("run", before), i)
        return [q for kind, q in self.log[i + 1:j] if kind == "q"]


@pytest.fixture
def env(tmp_path, monkeypatch):
    """A clone root with an approval, a runner-made checkout, the push clock cold, sleep recorded."""
    root = tmp_path / "repo"
    checkout = root / "build" / "nightly_measure_wt"
    (checkout / "build").mkdir(parents=True)
    (checkout / "build" / nm.MARK).write_text("x")
    (checkout / "tools").mkdir()
    (checkout / "tools" / "image_ownership.py").write_text("def measure(path):\n    return {}\n")
    nm.write_json(root / "build" / "nightly_measure" / "approved.json", {"commit": "a" * 40, **IDENT})
    slept = []
    monkeypatch.setattr(nm.time, "sleep", slept.append)
    monkeypatch.delenv("BFME_PUSH_CLOCK", raising=False)
    return {"root": root, "checkout": checkout, "snap": root / "build" / "nm", "slept": slept, "tmp": tmp_path,
            "clock": tmp_path / "clock.json"}


def run(env, monkeypatch, *extra, tweak=None, **fake):
    """Legacy component harness: exercise Run helpers independently of role policy.

    The production CLI uses BuilderRun/PublisherRun, tested separately below.
    Keeping these former single-role sequences exercises approval/cooldown/lease
    regressions without relaxing the new account boundary in production.
    """
    holder = {}
    real_init = nm.Run.__init__

    def init(self, *a, **k):
        real_init(self, *a, **k)
        holder["fake"] = f = FakeTools(self, **fake)
        if tweak:
            tweak(f)
        monkeypatch.setattr(nm.subprocess, "run", f)
    monkeypatch.setattr(nm.Run, "__init__", init)
    monkeypatch.setattr(nm, "BuilderRun", nm.Run)
    code = nm.main(["--role", "builder", "--install-dir", "unused", "--state-dir", "unused-state",
                    "--handoff-dir", "unused-handoff", "--push-clock", str(env["clock"]), *extra], root=env["root"], out=lambda *_: None)
    monkeypatch.undo()
    last = env["root"] / "build" / "nightly_measure" / "last_run.json"
    return code, holder.get("fake"), (json.loads(last.read_text()) if last.exists() else None)


def names(summary):
    return [s["step"] for s in summary["steps"]]


def status(summary):
    return {s["step"]: s["status"] for s in summary["steps"]}


# ---------------------------------------------------------------- order and arguments

def test_every_step_runs_in_order_with_the_tools_exact_arguments(env, monkeypatch):
    code, fake, summary = run(env, monkeypatch, store_latest="b1")
    assert code == nm.EXIT_OK and summary["status"] == "ok" and summary["commit"] == COMMIT
    assert names(summary) == FULL
    a = {name_of(x): x for x in fake.calls}
    t = {k: tail(v) for k, v in a.items() if v[0] != "git"}
    assert t["gate"] == ["tools/build.py"]
    assert t["cycle"] == ["tools/link_cycle.py", "--snapshot", COMMIT, "--snapshot-dir", str(env["snap"].resolve()),
                          "--build", "--reuse-quarantine", "--reuse-stubs"]
    boot_out = env["checkout"].resolve() / "build" / "boot" / Path(summary["run_dir"]).name
    assert t["boot"] == ["tools/boot_image.py", "link", "--overlay", "Code/", "--relayout", "--own-data",
                         "--out", str(boot_out), "--tag", "relayout"]
    # ownership measures the ORIGINAL report, beside its image, and records
    assert t["ownership"] == [str(boot_out / "relayout.json"), str(boot_out / "relayout.exe"),
                              str(Path(summary["run_dir"]) / "image_ownership.json"), "record"]
    run_dir = env["snap"].resolve() / COMMIT[:10] / "build" / "link_cycle"
    assert t["validate"] == ["tools/publish_cycle.py", "validate", str(run_dir)]
    assert t["closure"] == ["tools/closure_report.py", "graph", str(run_dir), "--out", str(run_dir)]
    # every Python child is isolated, its one import dir the checkout's (approved) tools/
    for x in fake.calls:
        if x[0] != "git":
            i = x.index("-c")
            assert x[1] == "-I" and x[i + 2] == str(env["checkout"].resolve() / "tools"), x
            if name_of(x) != "ownership":
                assert x[i + 1] == nm.SCRIPT_BOOT and Path(x[i + 3]) == env["checkout"].resolve() / tail(x)[0]
    assert a["bundle"][-2:] == ["--previous", str(env["checkout"].resolve() / "build" / "cycle_bundles" / "b1" / "bundle")]
    assert "--dry-run" not in a["publish"]
    assert git_args(a["history-push"]) == ["push", "--quiet", "origin", "HEAD:master"]
    # no census, no index publication: the workflow owns them
    assert not any("link_census.py" in " ".join(x) or "link_check.py" in " ".join(x) for x in fake.calls)
    for s in summary["steps"]:
        if "argv" in s:
            assert "seconds" in s and Path(s["log"]).exists()
    assert json.loads((Path(summary["run_dir"]) / "run.json").read_text()) == summary


@pytest.mark.parametrize("failing", ["fetch", "gate", "cycle", "validate", "closure", "bundle", "publish"])
def test_a_blocking_failure_stops_the_run_and_nothing_after_it_runs(env, monkeypatch, failing):
    code, fake, summary = run(env, monkeypatch, codes={failing: 1})
    assert code == nm.EXIT_FAILED and summary["status"] == "failed" and summary["failed_step"] == failing
    assert names(summary) == BLOCKING[:BLOCKING.index(failing) + 1]
    assert not fake.ran("boot") and not fake.ran("history-push") and not fake.ran("install")
    if failing != "publish":
        assert not fake.ran("publish")


def test_a_receipt_that_is_not_authoritative_or_not_this_commit_publishes_nothing(env, monkeypatch):
    for receipt in ({"authoritative": False}, {"commit": "f" * 40}):
        code, fake, summary = run(env, monkeypatch, receipt=receipt)
        assert code == nm.EXIT_FAILED and summary["failed_step"] == "receipt"
        assert not fake.ran("validate") and not fake.ran("publish")


def test_a_stale_receipt_from_an_earlier_run_is_refused(env, monkeypatch):
    real = FakeTools.side_effect

    def old_receipt(self, name, argv, code):
        real(self, name, argv, code)
        if name == "cycle":
            os.utime(self.run.cycle_dir() / "receipt.json", (time.time() - 3600, time.time() - 3600))
    monkeypatch.setattr(FakeTools, "side_effect", old_receipt)
    code, _, summary = run(env, monkeypatch)
    assert code == nm.EXIT_FAILED and "before this run" in summary["steps"][-1]["note"]


# ---------------------------------------------------------------- after the bundle: loud, never blocking

def test_boot_exit_1_with_a_linked_report_is_a_measurement(env, monkeypatch):
    code, _, summary = run(env, monkeypatch, codes={"boot": 1}, boot_report={"link_exit": 0})
    assert code == nm.EXIT_OK and status(summary)["boot"] == "measured"
    assert (Path(summary["run_dir"]) / "relayout.json").exists()


@pytest.mark.parametrize("report", [{"link_exit": 1120}, "none"])
def test_a_failed_boot_comes_after_the_published_bundle_and_degrades_the_run(env, monkeypatch, report):
    code, fake, summary = run(env, monkeypatch, codes={"boot": 1}, boot_report=report)
    assert code == nm.EXIT_DEGRADED and summary["status"] == "degraded"
    assert fake.ran("publish") and fake.ran("install")                 # the bundle went out first
    assert summary["failures_after_bundle"] == ["boot"] and status(summary)["ownership"] == "skipped"
    assert not fake.ran("history-push")


@pytest.mark.parametrize("rc,why", [(nm.NOT_VERIFIED, "NOT VERIFIED"), (nm.NOT_RECORDED, "refused the row"),
                                    (1, "did not import")])
def test_an_unverified_unrecorded_or_unimportable_ownership_fails_loudly(env, monkeypatch, rc, why):
    code, fake, summary = run(env, monkeypatch, codes={"ownership": rc})
    assert code == nm.EXIT_DEGRADED and summary["failures_after_bundle"] == ["ownership"]
    rec = {s["step"]: s for s in summary["steps"]}["ownership"]
    assert rec["status"] == "failed" and why in rec["note"]
    assert fake.ran("publish") and not fake.ran("history-commit")


def test_a_tree_without_image_ownership_skips_the_step(env, monkeypatch):
    (env["checkout"] / "tools" / "image_ownership.py").unlink()
    code, fake, summary = run(env, monkeypatch)
    assert code == nm.EXIT_OK and status(summary)["ownership"] == "skipped" and not fake.ran("ownership")


def test_the_history_row_is_pushed_only_while_origin_master_is_approved(env, monkeypatch):
    def moved(f):
        f.history_master = MASTER2
        f.by_rev[MASTER2] = dict(IDENT, tools_tree="x" * 40)
    code, fake, summary = run(env, monkeypatch, tweak=moved)
    assert code == nm.EXIT_DEGRADED and summary["failures_after_bundle"] == ["history"]
    assert fake.ran("history-commit") and not fake.ran("history-rebase") and not fake.ran("history-push")
    assert (Path(summary["run_dir"]) / "image_ownership_history.csv").exists()


def test_the_history_push_retries_under_the_cooldown(env, monkeypatch):
    pushes = []
    real = FakeTools.__call__

    def lose_once(self, argv, *a, **k):
        res = real(self, argv, *a, **k)
        if name_of([str(x) for x in argv]) == "history-push":
            pushes.append(1)
            return subprocess.CompletedProcess(argv, 1 if len(pushes) == 1 else 0)
        return res
    monkeypatch.setattr(FakeTools, "__call__", lose_once)
    # A slow CI worker must not consume the cooldown between stamped attempts.
    monkeypatch.setattr(nm.time, "time", lambda frozen=time.time(): frozen)
    code, _, summary = run(env, monkeypatch)
    assert code == nm.EXIT_OK and names(summary)[-3:] == ["history-fetch-2", "history-rebase-2", "history-push-2"]
    assert len(env["slept"]) == 2                     # publish stamped the clock; each push waited for it


def test_inactive_hooks_never_commit_the_row(env, monkeypatch):
    code, fake, summary = run(env, monkeypatch, tweak=lambda f: setattr(f, "hooks", ""))
    assert code == nm.EXIT_OK and fake.ran("history-commit")
    assert f"core.hooksPath={env['root'] / 'build' / 'nightly_measure' / 'hooks' / IDENT['githooks_tree']}" in fake.ran("history-commit")[0]


def test_no_publish_makes_no_github_write_and_records_nothing(env, monkeypatch):
    code, fake, summary = run(env, monkeypatch, "--no-publish")
    assert code == nm.EXIT_OK
    assert fake.ran("publish")[0][-1] == "--dry-run" and not fake.ran("install") and not fake.ran("history-commit")
    assert fake.ran("ownership")[0][-1] == "measure" and not env["clock"].exists() and env["slept"] == []


def test_skip_leaves_steps_out_and_says_so(env, monkeypatch):
    code, fake, summary = run(env, monkeypatch, "--skip", "gate", "--skip", "boot")
    assert code == nm.EXIT_OK and not fake.ran("gate") and not fake.ran("boot")
    assert status(summary)["gate"] == status(summary)["boot"] == status(summary)["ownership"] == "skipped"


# ---------------------------------------------------------------- the approval

def test_unapproved_code_on_origin_master_runs_nothing(env, monkeypatch):
    def changed(f):
        f.ident["githooks_tree"] = "y" * 40
    code, fake, summary = run(env, monkeypatch, tweak=changed)
    assert code == nm.EXIT_UNAPPROVED and summary["status"] == "unapproved"
    assert [name_of(a) for a in fake.calls] == ["fetch"]               # no checkout: no hook of it ran
    note = {s["step"]: s for s in summary["steps"]}["approval"]["note"]
    assert "githooks_tree" in note and f"--approve {COMMIT}" in note and "git diff" in note


def test_a_runner_that_is_not_the_installed_approved_one_refuses(env, monkeypatch):
    approved = env["root"] / "build" / "nightly_measure" / "approved.json"
    nm.write_json(approved, {"commit": "a" * 40, **IDENT, "runner_sha256": "0" * 64})
    code, fake, summary = run(env, monkeypatch)
    assert code == nm.EXIT_UNAPPROVED and fake.calls == []


def test_no_approval_refuses(env, monkeypatch):
    (env["root"] / "build" / "nightly_measure" / "approved.json").unlink()
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_UNAPPROVED and fake.calls == []


def test_code_edited_on_disk_refuses_the_publish(env, monkeypatch):
    real = FakeTools.side_effect

    def tamper(self, name, argv, code):
        real(self, name, argv, code)
        if name == "bundle":
            self.code_dirty = " M tools/publish_cycle.py"
    monkeypatch.setattr(FakeTools, "side_effect", tamper)
    code, fake, summary = run(env, monkeypatch)
    assert code == nm.EXIT_UNAPPROVED and not fake.ran("publish")


def test_approve_records_the_identity_and_installs_the_runner(env, monkeypatch):
    fake = FakeTools(type("R", (), {})())
    monkeypatch.setattr(nm.subprocess, "run", fake)
    assert nm.main(["--approve", "origin/master"], root=env["root"], out=lambda *_: None) == nm.EXIT_OK
    work = env["root"] / "build" / "nightly_measure"
    approved = json.loads((work / "approved.json").read_text())
    assert approved["commit"] == COMMIT and {k: approved[k] for k in IDENT} == IDENT
    assert (work / "runner" / "nightly_measure.py").read_bytes() == RUNNER_BYTES


# ---------------------------------------------------------------- the checkout

def test_the_checkout_is_created_without_files_then_marked(env, monkeypatch):
    import shutil
    shutil.rmtree(env["checkout"])
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_OK and name_of(fake.calls[0]) == "worktree"
    assert git_args(fake.calls[0]) == ["worktree", "add", "--no-checkout", "--detach",
                                      str(env["checkout"].resolve()), "origin/master"]
    assert (env["checkout"] / "build" / nm.MARK).is_file()


def test_a_checkout_this_tool_did_not_make_is_never_reset(env, monkeypatch):
    (env["checkout"] / "build" / nm.MARK).unlink()
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_SETUP and fake.calls == []


def test_the_main_tree_a_branch_checkout_and_a_long_snapshot_dir_are_refused(env, monkeypatch):
    code, fake, _ = run(env, monkeypatch, "--checkout", str(env["root"]))
    assert code == nm.EXIT_SETUP and fake.calls == []
    code, fake, _ = run(env, monkeypatch, tweak=lambda f: setattr(f, "symbolic_ref", 0))
    assert code == nm.EXIT_SETUP and fake.calls == []
    code, fake, _ = run(env, monkeypatch, "--snapshot-dir", str(env["root"] / "build" / ("d" * 40)))
    assert code == nm.EXIT_SETUP and fake.calls == []


def test_a_dirty_checkout_after_the_reset_measures_nothing(env, monkeypatch):
    code, fake, summary = run(env, monkeypatch, tweak=lambda f: setattr(f, "dirty", " M Code/x.cpp"))
    assert code == nm.EXIT_FAILED and summary["failed_step"] == "clean" and not fake.ran("gate")


def test_children_get_a_runner_pycache_and_no_redirects(env, monkeypatch):
    monkeypatch.setenv("LINK_CYCLE_ROOT", "/elsewhere")
    monkeypatch.setenv("PYTHONPATH", "/elsewhere")
    for key in ("CL", "_CL_", "ML", "_ML_", "LINK", "_LINK_", "VC71_ROOT", "STLPORT_ROOT"):
        monkeypatch.setenv(key, "unapproved compiler or flags")
    e = nm.Run(nm.parse([]), env["root"]).env()
    assert "LINK_CYCLE_ROOT" not in e and "PYTHONPATH" not in e
    assert not any(k in e for k in ("CL", "_CL_", "ML", "_ML_", "LINK", "_LINK_", "VC71_ROOT", "STLPORT_ROOT"))
    assert e["PYTHONPYCACHEPREFIX"].startswith(str(env["root"] / "build" / "nightly_measure"))


# ---------------------------------------------------------------- snapshots

def test_prune_removes_only_released_snapshots_this_runner_created(env, monkeypatch):
    snap = env["snap"]
    reg = {}
    for i, (name, created, released) in enumerate([("aaaaaaaaaa", True, True), ("bbbbbbbbbb", True, True),
                                                   ("cccccccccc", False, True), ("dddddddddd", True, False)]):
        (snap / name).mkdir(parents=True)
        (snap / name / nm.SNAPSHOT_MARK).write_text("{}")
        reg[str((snap / name).resolve())] = {"created_by": "run" if created else None, "registered": 1000 + i,
                                              "released": released, "lease_until": time.time() + 3600}
    (snap / "eeeeeeeeee").mkdir()                                            # someone else's: not registered
    (snap / "eeeeeeeeee" / nm.SNAPSHOT_MARK).write_text("{}")
    nm.write_json(env["root"] / "build" / "nightly_measure" / "snapshots.json", reg)
    code, _, summary = run(env, monkeypatch, "--keep-snapshots", "2")
    assert code == nm.EXIT_OK
    # kept: this run's, the newest other one this runner created (dddddddddd: leased, so kept anyway),
    # the adopted one and the unregistered one; removed: the older released ones it created
    assert sorted(p.name for p in snap.iterdir()) == [COMMIT[:10], "cccccccccc", "dddddddddd", "eeeeeeeeee"]
    entry = json.loads((env["root"] / "build" / "nightly_measure" / "snapshots.json").read_text())[
        str((snap / COMMIT[:10]).resolve())]
    assert entry["created_by"] and entry["released"] is True


def test_a_registered_marked_snapshot_is_reused_and_stays_adopted(env, monkeypatch):
    dest = env["snap"] / COMMIT[:10]
    dest.mkdir(parents=True)
    (dest / nm.SNAPSHOT_MARK).write_text("{}")
    registry = env["root"] / "build" / "nightly_measure" / "snapshots.json"
    nm.write_json(registry, {str(dest.resolve()): {"created_by": None, "registered": 1, "released": True,
                                                   "lease_until": 0}})
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_OK and fake.ran("cycle")
    assert json.loads(registry.read_text())[str(dest.resolve())]["created_by"] is None


@pytest.mark.parametrize("case", ["unregistered", "unmarked"])
def test_an_existing_destination_unowned_or_unmarked_is_refused_before_the_export(env, monkeypatch, case):
    """link_cycle deletes an existing destination without SNAPSHOT.json: never hand it one."""
    dest = env["snap"] / COMMIT[:10]
    (dest / "keep").mkdir(parents=True)
    (dest / "keep" / "data").write_text("precious")
    if case == "unregistered":
        (dest / nm.SNAPSHOT_MARK).write_text("{}")
    else:
        nm.write_json(env["root"] / "build" / "nightly_measure" / "snapshots.json",
                      {str(dest.resolve()): {"created_by": "an earlier run", "registered": 1}})
    code, fake, summary = run(env, monkeypatch, "--skip", "gate")
    assert code == nm.EXIT_SETUP and summary["status"] == "refused" and not fake.ran("cycle")
    assert (dest / "keep" / "data").read_text() == "precious"


def test_the_snapshot_is_leased_before_link_cycle_creates_it(env, monkeypatch):
    seen = {}
    real = FakeTools.side_effect

    def look(self, name, argv, code):
        if name == "cycle":
            reg = nm.read_json(self.run.registry, {})
            seen.update(reg.get(str(self.run.snapshot()), {}), existed=self.run.snapshot().exists())
        real(self, name, argv, code)
    monkeypatch.setattr(FakeTools, "side_effect", look)
    code, _, _ = run(env, monkeypatch)
    assert code == nm.EXIT_OK and seen["existed"] is False
    assert seen["created_by"] and seen["released"] is False and seen["lease_until"] > time.time()


# ---------------------------------------------------------------- the lock, across processes

HOLD = ("import sys, time\nsys.path.insert(0, sys.argv[1])\nimport nightly_measure as nm\n"
        "h = nm.try_lock(sys.argv[2])\nprint('held' if h else 'busy', flush=True)\ntime.sleep(600)\n")


def hold_lock(path):
    proc = subprocess.Popen([sys.executable, "-c", HOLD, str(TOOLS), str(path)], stdout=subprocess.PIPE, text=True)
    assert proc.stdout.readline().strip() == "held"
    return proc


def test_a_lock_held_by_another_process_refuses_a_second_run(env, monkeypatch):
    lock = env["root"] / "build" / "nightly_measure" / "lock"
    proc = hold_lock(lock)
    try:
        assert nm.try_lock(lock) is None
        code, fake, summary = run(env, monkeypatch)
        assert code == nm.EXIT_LOCKED and fake.calls == [] and summary is None
    finally:
        proc.kill()                                  # this test's own child, by its handle
        proc.wait()


def test_a_crashed_holder_leaves_no_stale_lock(env, monkeypatch):
    lock = env["root"] / "build" / "nightly_measure" / "lock"
    proc = hold_lock(lock)
    nm.write_json(lock.parent / "holder.json", {"pid": proc.pid, "since": "then"})   # the crash leaves this
    proc.kill()
    proc.wait()
    code, _, _ = run(env, monkeypatch)
    assert code == nm.EXIT_OK


def test_the_lock_is_released_after_a_failed_run(env, monkeypatch):
    run(env, monkeypatch, codes={"gate": 1})
    handle = nm.try_lock(env["root"] / "build" / "nightly_measure" / "lock")
    assert handle is not None
    nm.unlock(handle)


# ---------------------------------------------------------------- cooldown

def test_github_writes_wait_for_the_cooldown_and_stamp_it(env, monkeypatch):
    nm.stamp_clock(env["clock"], "an earlier push", now=lambda: time.time() - 60)
    code, _, summary = run(env, monkeypatch)
    assert code == nm.EXIT_OK
    assert {s["step"] for s in summary["steps"] if "cooldown_waited" in s} == {"publish", "history-push-1"}
    assert 230 <= env["slept"][0] <= 240 and len(env["slept"]) == 2
    assert json.loads(env["clock"].read_text())["what"] == "nightly_measure history-push-1"


# ---------------------------------------------------------------- ownership, with the REAL measure()

def ownership_fixture():
    """The real module and its own test fixture (a tiny retail, built image, map and report)."""
    import importlib.util
    io_mod = pytest.importorskip("image_ownership")
    path = Path(io_mod.__file__).parent / "tests" / "test_image_ownership.py"
    if not path.is_file():
        pytest.skip(f"no {path}")
    spec = importlib.util.spec_from_file_location("io_fixture", path)
    fx = importlib.util.module_from_spec(spec)
    spec.loader.exec_module(fx)
    return io_mod, fx


def test_the_real_measure_proves_the_original_report_and_refuses_a_copy(tmp_path):
    io_mod, fx = ownership_fixture()
    fixture = fx.Fixture()
    fixture.setUp()
    boot = tmp_path / "checkout" / "build" / "boot"
    boot.mkdir(parents=True)
    for name, data in (("retail.dat", fx.RETAIL), ("items.csv", fx.DATA_ITEMS.encode()),
                       ("rows.csv", fx.ROWS_CSV.encode())):
        (tmp_path / name).write_bytes(data)
    report = fx.overlay_report()
    report["measurement_attestation"] = {
        "schema": 1, "basis": "builder-attested", "statement": nm.BUILDER_ATTESTATION}
    report["provenance"] = fixture.provenance(fx.OVERLAY_IMAGE, fx.OVERLAY_MAP.encode())
    (boot / "relayout.exe").write_bytes(fx.OVERLAY_IMAGE)
    (boot / "relayout.map").write_bytes(fx.OVERLAY_MAP.encode())
    (boot / "relayout.json").write_text(json.dumps(report))
    kw = {"retail": tmp_path / "retail.dat", "ledger": fx.LEDGER, "naked": frozenset(),
          "data_items_path": tmp_path / "items.csv", "rows_csv": tmp_path / "rows.csv"}
    out = tmp_path / "receipt.json"
    assert nm.measure_ownership(io_mod, boot / "relayout.json", boot / "relayout.exe", out, record=False,
                                measure_kw=kw) == 0
    receipt = json.loads(out.read_text())
    assert receipt["verified"] and receipt["image"]["bound"] and receipt["totals"]["ours"] == 0x20
    # round 1's bug: the report copied into the run directory measures an image that is not there
    run_dir = tmp_path / "runs" / "x"
    run_dir.mkdir(parents=True)
    (run_dir / "relayout.json").write_text(json.dumps(report))
    out.unlink()
    assert nm.measure_ownership(io_mod, run_dir / "relayout.json", run_dir / "relayout.exe", out, record=False,
                                measure_kw=kw) == nm.NOT_VERIFIED
    assert not out.exists()
    fixture.tearDown()


def test_measure_is_given_the_image_beside_the_report():
    """image= is passed, never left to the module's default."""
    seen = {}

    class Mod:
        @staticmethod
        def measure(report, image=None, **kw):
            seen.update(report=report, image=image)
            return {"verified": False, "refusals": ["x"]}
    assert nm.measure_ownership(Mod, "r.json", "elsewhere/i.exe", os.devnull, record=False) == nm.NOT_VERIFIED
    assert seen == {"report": "r.json", "image": "elsewhere/i.exe"}


def test_the_ownership_child_fails_on_an_unimportable_module(tmp_path):
    (tmp_path / "tools").mkdir()
    (tmp_path / "tools" / "image_ownership.py").write_text("import a_module_that_is_not_there\n")
    args = [sys.executable, "-I", "-c", nm.OWNERSHIP_PROBE, str(tmp_path / "tools"), "r.json", "r.exe", "out.json",
            "record"]
    res = subprocess.run(args, cwd=tmp_path, capture_output=True, text=True)
    assert res.returncode == 1 and "ModuleNotFoundError" in res.stderr       # a failure, never a skip
    (tmp_path / "tools" / "image_ownership.py").write_text(
        "def measure(p, image=None):\n    return {'verified': False, 'refusals': ['image missing']}\n")
    res = subprocess.run(args, cwd=tmp_path, capture_output=True, text=True)
    assert res.returncode == nm.NOT_VERIFIED and "image missing" in res.stdout


# ---------------------------------------------------------------- isolation of the Python children (real processes)

def planted_checkout(tmp_path):
    """A checkout whose root carries json.py and csv.py that leave a marker when imported."""
    co = tmp_path / "co"
    (co / "tools").mkdir(parents=True)
    marker = tmp_path / "shadow-ran"
    for mod in ("json", "csv"):
        (co / f"{mod}.py").write_text(f"open({str(marker)!r}, 'w').write({mod!r})\nraise SystemExit(99)\n")
    run_ = nm.Run(nm.parse(["--checkout", str(co)]), tmp_path / "repo")
    no_safe = {k: v for k, v in os.environ.items() if k != "PYTHONSAFEPATH"}   # -I alone must hold
    return co, marker, run_, no_safe


def test_the_ownership_probe_never_imports_a_root_level_stdlib_shadow(tmp_path):
    co, marker, r, env = planted_checkout(tmp_path)
    (co / "tools" / "image_ownership.py").write_text(
        "import csv, json\ndef measure(p, image=None):\n    return {'verified': False, 'refusals': [json.dumps('iso')]}\n")
    probe = [nm.OWNERSHIP_PROBE, co / "tools", "r.json", "r.exe", tmp_path / "o.json", "measure"]
    control = subprocess.run([sys.executable, "-c", *map(str, probe)], cwd=co, env=env, capture_output=True)
    assert control.returncode == 99 and marker.exists()                 # the plant is real without isolation
    marker.unlink()
    res = subprocess.run([str(a) for a in r.python("-c", *probe)], cwd=co, env=env, capture_output=True, text=True)
    assert res.returncode == nm.NOT_VERIFIED and not marker.exists(), res.stderr
    assert '"iso"' in res.stdout


def test_a_tool_runs_as_main_with_only_the_checkouts_tools_added(tmp_path):
    co, marker, r, env = planted_checkout(tmp_path)
    (co / "tools" / "helper.py").write_text("X = 'sibling'\n")
    (co / "tools" / "hello.py").write_text("import sys, json, csv, helper\nif __name__ == '__main__':\n"
                                           "    print(helper.X, json.dumps(sys.argv[1:]))\n")
    res = subprocess.run([str(a) for a in r.tool("tools/hello.py", "a", "b")], cwd=co, env=env,
                         capture_output=True, text=True)
    assert res.returncode == 0 and not marker.exists(), res.stderr
    assert res.stdout.strip() == 'sibling ["a", "b"]'


def test_an_isolated_tool_keeps_its_process_pool(tmp_path):
    """build.py fans out with ProcessPoolExecutor: spawned workers re-import the runpy'd __main__."""
    co, marker, r, env = planted_checkout(tmp_path)
    (co / "tools" / "helper.py").write_text("K = 1\n")
    (co / "tools" / "pool.py").write_text(
        "import concurrent.futures, json, helper\ndef sq(x):\n    return x * x + helper.K\n"
        "if __name__ == '__main__':\n    with concurrent.futures.ProcessPoolExecutor(2) as p:\n"
        "        print(json.dumps(sorted(p.map(sq, range(4)))))\n")
    res = subprocess.run([str(a) for a in r.tool("tools/pool.py")], cwd=co, env=env, capture_output=True, text=True,
                         timeout=120)
    assert res.returncode == 0 and res.stdout.strip() == "[1, 2, 5, 10]" and not marker.exists(), res.stderr


def test_grandchildren_and_hooks_get_no_cwd_on_their_path(tmp_path):
    """A hook's `python3 -c` at the checkout root, with the runner's environment."""
    co, marker, r, _ = planted_checkout(tmp_path)
    assert r.env()["PYTHONSAFEPATH"] == "1"
    res = subprocess.run([sys.executable, "-c", "import json, csv"], cwd=co, env=r.env(), capture_output=True)
    assert res.returncode == 0 and not marker.exists()


# ---------------------------------------------------------------- round 3: approval timing and targets

def test_the_code_is_proven_after_the_cooldown_wait_immediately_before_the_write(env, monkeypatch):
    nm.stamp_clock(env["clock"], "an earlier push", now=lambda: time.time() - 60)

    def tamper_during_wait(f):
        monkeypatch.setattr(nm.time, "sleep", lambda s: setattr(f, "code_dirty", " M tools/publish_cycle.py"))
    code, fake, summary = run(env, monkeypatch, tweak=tamper_during_wait)
    assert code == nm.EXIT_UNAPPROVED and not fake.ran("publish")


def test_the_history_rebases_onto_the_commit_it_approved_not_the_moving_ref(env, monkeypatch):
    def moving(f):
        f.history_master = MASTER2
        f.by_rev["origin/master"] = dict(IDENT, githooks_tree="z" * 40)   # the ref, read again, has moved on
    code, fake, summary = run(env, monkeypatch, tweak=moving)
    assert code == nm.EXIT_OK and fake.ran("history-push")
    assert fake.ran("history-rebase")[0][-1] == MASTER2
    qs = fake.queries_between("history-commit", "history-rebase")
    assert ["rev-parse", f"{MASTER2}:tools"] in qs and not any(q[-1].startswith("origin/master:") for q in qs)


def test_head_code_changed_after_the_rebase_is_never_pushed(env, monkeypatch):
    real = FakeTools.side_effect

    def swap(self, name, argv, code):
        real(self, name, argv, code)
        if name == "history-rebase":
            self.ident = dict(IDENT, tools_tree="r" * 40)
    monkeypatch.setattr(FakeTools, "side_effect", swap)
    code, fake, summary = run(env, monkeypatch)
    assert code == nm.EXIT_DEGRADED and summary["failures_after_bundle"] == ["approval"]
    assert not fake.ran("history-push")


def test_code_left_behind_by_the_measuring_tools_never_reaches_the_commit_hooks(env, monkeypatch):
    real = FakeTools.side_effect

    def plant(self, name, argv, code):
        real(self, name, argv, code)
        if name == "ownership":
            self.code_dirty = "?? .githooks/pre-commit.local"
    monkeypatch.setattr(FakeTools, "side_effect", plant)
    code, fake, summary = run(env, monkeypatch)
    assert code == nm.EXIT_DEGRADED and summary["failures_after_bundle"] == ["history"]
    assert not fake.ran("history-add") and not fake.ran("history-commit")


def test_head_code_changed_before_the_publish_is_never_published(env, monkeypatch):
    real = FakeTools.side_effect

    def swap(self, name, argv, code):
        real(self, name, argv, code)
        if name == "bundle":
            self.ident = dict(IDENT, vendor_tree="r" * 40)
    monkeypatch.setattr(FakeTools, "side_effect", swap)
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_UNAPPROVED and not fake.ran("publish")


def test_the_code_dirs_are_cleaned_before_every_proof(env, monkeypatch):
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_OK
    clean = ["clean", "-q", "-f", "-d", "-x", "--", "tools", ".githooks", "vendor"]
    for after, before in (("submodule", "gate"), ("bundle", "publish"), ("history-rebase", "history-push")):
        assert clean in fake.queries_between(after, before), (after, before)


def test_code_dirty_after_the_checkout_runs_nothing(env, monkeypatch):
    real = FakeTools.side_effect

    def dirty(self, name, argv, code):
        real(self, name, argv, code)
        if name == "submodule":
            self.code_dirty = "?? tools/csv.py"
    monkeypatch.setattr(FakeTools, "side_effect", dirty)
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_UNAPPROVED and not fake.ran("gate")


@pytest.mark.parametrize("directive", [
    "// compiler: clang23-x86 -load evil.dll",
    "// cl: /B1 C:\\evil.exe",
    "// cl: /B2 C:\\evil.exe",
    "// cl: /Bx C:\\evil.exe",
    "// cl: -Xclang -load evil.dll",
    "// cl: -fplugin=evil.dll",
    "// cl: /analyze:plugin evil.dll",
    "// cl: /I evil.dll",
    "// cl: /O2\n// cl: /B1evil.exe",
    "// cl: /DNEW_UNREVIEWED_FLAG",
    "// cl: /FIunreviewed.h",
    "// cl: /O2 /MD /Ireference/shims/bfme2_ascii",
])
def test_source_directives_are_checked_before_any_compilation(env, monkeypatch, directive):
    src = env["checkout"] / "Code" / "bad.cpp"
    src.parent.mkdir()
    src.write_text(directive + "\n")
    real = FakeTools.query

    def listed(self, args):
        if "ls-files" in args:
            return 0, b"Code/bad.cpp\0"
        return real(self, args)
    monkeypatch.setattr(FakeTools, "query", listed)
    code, fake, summary = run(env, monkeypatch)
    if "/O2 /MD /I" in directive:
        assert code == nm.EXIT_OK
    else:
        assert code == nm.EXIT_UNAPPROVED
        assert not fake.ran("gate") and "source compiler directive" in summary["steps"][-1]["note"]


@pytest.mark.parametrize("flag", ["-B1", "-B2", "-Bx", "-Xclang", "-fplugin=bad", "-load",
                                 "-analyze:plugin", "tool.exe", "library.dll"])
def test_dangerous_flags_are_refused_even_if_added_to_the_allowlist(monkeypatch, flag):
    monkeypatch.setattr(nm, "CL_FLAGS", nm.CL_FLAGS | {flag})
    assert nm.cl_problems("// cl: " + flag)


def test_pinned_profiles_markers_and_existing_flag_forms_are_allowed(tmp_path):
    source = tmp_path / "unit.cpp"
    for profile in ("vc71-sp1", "vc71-ddk-4035", "clang23-x86"):
        source.write_text("// compiler: " + profile + "\n// stlport\n// platformsdk\n"
                          '// cl: /O2 /MD /I"relative include" /DWIN32 /FIzh_ascii.h '
                          '/clang:-mllvm /clang:-branch-folder-reorder-blocks=false\n')
        assert not nm.directive_problems(tmp_path, ["unit.cpp"])


def test_unapproved_region_option_is_refused_before_the_gate(env, monkeypatch):
    regions = env["checkout"] / "reverse" / "retail_inventory" / "flag_regions.csv"
    regions.parent.mkdir(parents=True)
    regions.write_text("opt\nB2evil.exe\n")
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_UNAPPROVED and not fake.ran("gate")


@pytest.mark.parametrize("directive", ['#import "evil.dll"', '#using "evil.dll"'])
def test_source_cannot_load_a_type_library(tmp_path, directive):
    (tmp_path / "header.h").write_text(directive + "\n")
    assert nm.directive_problems(tmp_path, ["header.h"])


def test_build_children_have_no_publisher_credentials(env, monkeypatch):
    for key in ("GH_TOKEN", "GITHUB_TOKEN", "GIT_ASKPASS", "SSH_ASKPASS", "GIT_CONFIG_COUNT"):
        monkeypatch.setenv(key, "sensitive")
    seen = {}
    real = FakeTools.__call__

    def capture(self, argv, **kw):
        if not kw.get("capture_output"):
            seen[name_of(argv)] = kw["env"]
        return real(self, argv, **kw)
    monkeypatch.setattr(FakeTools, "__call__", capture)
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_OK
    for name in ("checkout", "submodule", "gate", "cycle", "validate", "closure", "bundle", "boot", "ownership"):
        child = seen[name]
        assert not any(k in child for k in ("GH_TOKEN", "GITHUB_TOKEN", "GIT_ASKPASS", "SSH_ASKPASS"))
        assert child["GH_CONFIG_DIR"] == str(fake.run.gh_dir) and fake.run.gh_dir.is_dir()
        assert child["GIT_TERMINAL_PROMPT"] == "0"
        assert any(child.get(f"GIT_CONFIG_KEY_{i}") == "credential.helper"
                   and child.get(f"GIT_CONFIG_VALUE_{i}") == "" for i in range(int(child["GIT_CONFIG_COUNT"])))
        assert child["GIT_CONFIG_GLOBAL"] == os.devnull
    assert seen["publish"]["GH_TOKEN"] == "sensitive"


def test_checkout_and_history_ignore_planted_hooks_and_fsmonitor(env, monkeypatch):
    hooks = env["checkout"] / ".githooks"
    hooks.mkdir()
    (hooks / "post-checkout").write_text("echo malicious\n")
    original = FakeTools.query

    def planted_config(self, args):
        while args and args[0] == "-c":
            args = args[2:]
        if args[:3] == ["config", "--null", "--get-regexp"]:
            return 0, b"filter.bad driver.process\n!echo malicious\0merge.bad driver.driver\n!echo malicious\0"
        return original(self, args)
    monkeypatch.setattr(FakeTools, "query", planted_config)
    seen = {}
    original_run = FakeTools.__call__

    def capture(self, argv, **kw):
        if not kw.get("capture_output"):
            seen[name_of(argv)] = (argv, kw["env"])
        return original_run(self, argv, **kw)
    monkeypatch.setattr(FakeTools, "__call__", capture)
    code, _, _ = run(env, monkeypatch)
    assert code == nm.EXIT_OK
    for step in ("checkout", "history-rebase", "history-commit", "history-push"):
        argv, environ = seen[step]
        assert "core.fsmonitor=" in argv
        assert any(environ.get(f"GIT_CONFIG_KEY_{i}") == "core.fsmonitor"
                   and environ.get(f"GIT_CONFIG_VALUE_{i}") == "" for i in range(int(environ["GIT_CONFIG_COUNT"])))
        hook_option = next(a for a in argv if a.startswith("core.hooksPath="))
        hook_path = Path(hook_option.split("=", 1)[1])
        if step == "checkout":
            assert hook_path.name.startswith("empty-hooks-") and not list(hook_path.iterdir())
        else:
            assert hook_path == env['root'] / 'build' / 'nightly_measure' / 'hooks' / IDENT['githooks_tree']
        assert str(hooks) not in " ".join(argv)
        inherited = {environ[f"GIT_CONFIG_KEY_{i}"]: environ[f"GIT_CONFIG_VALUE_{i}"]
                     for i in range(int(environ["GIT_CONFIG_COUNT"]))}
        assert inherited["core.hooksPath"] == str(hook_path)
        assert "filter.bad driver.process=" in argv and "merge.bad driver.driver=false" in argv


def test_hooks_are_copied_from_approved_blobs_not_the_checkout(env, monkeypatch):
    unsafe = env["checkout"] / ".githooks"
    unsafe.mkdir()
    (unsafe / "post-checkout").write_text("malicious")
    data = b"#!/bin/sh\nexit 0\n"
    oid = nm.blob_id(data, "0" * 40)
    real = FakeTools.query

    def approved_tree(self, args):
        while args and args[0] == "-c":
            args = args[2:]
        if args[:2] == ["ls-tree", "-rz"]:
            return 0, f"100755 blob {oid}\tpost-checkout\0".encode()
        if args[:2] == ["cat-file", "blob"]:
            return 0, data
        return real(self, args)
    monkeypatch.setattr(FakeTools, "query", approved_tree)
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_OK
    assert (fake.run.hooks / "post-checkout").read_bytes() == data
    assert (unsafe / "post-checkout").read_text() == "malicious"


def test_modified_approved_hook_copy_never_reaches_history_push(env, monkeypatch):
    real = FakeTools.side_effect

    def tamper(self, name, argv, code):
        real(self, name, argv, code)
        if name == "history-rebase":
            hook = self.run.hooks / "post-checkout"
            hook.chmod(0o666)
            hook.write_text("malicious")
    monkeypatch.setattr(FakeTools, "side_effect", tamper)
    data = b"#!/bin/sh\nexit 0\n"
    oid = nm.blob_id(data, "0" * 40)
    real_query = FakeTools.query

    def approved_tree(self, args):
        while args and args[0] == "-c":
            args = args[2:]
        if args[:2] == ["ls-tree", "-rz"]:
            return 0, f"100755 blob {oid}\tpost-checkout\0".encode()
        if args[:2] == ["cat-file", "blob"]:
            return 0, data
        return real_query(self, args)
    monkeypatch.setattr(FakeTools, "query", approved_tree)
    code, fake, summary = run(env, monkeypatch)
    assert code == nm.EXIT_DEGRADED and not fake.ran("history-push")


def test_stale_boot_report_half_a_second_old_is_not_reused(env, monkeypatch):
    real = FakeTools.side_effect

    def stale(self, name, argv, code):
        real(self, name, argv, code)
        if name == "boot":
            path = Path(argv[argv.index("--out") + 1]) / "relayout.json"
            os.utime(path, (time.time() - .5, time.time() - .5))
    monkeypatch.setattr(FakeTools, "side_effect", stale)
    code, _, summary = run(env, monkeypatch)
    assert code == nm.EXIT_DEGRADED and status(summary)["boot"] == "failed"


def test_boot_never_adopts_an_existing_output_directory_even_with_a_future_mtime(env, monkeypatch):
    effect = FakeTools.side_effect

    def plant(self, name, argv, code):
        effect(self, name, argv, code)
        if name == "install":
            old = self.run.checkout / "build" / "boot" / self.run.dir.name
            old.mkdir(parents=True)
            path = old / "relayout.json"
            path.write_text('{"link_exit": 0}')
            os.utime(path, (time.time() + 60, time.time() + 60))
    monkeypatch.setattr(FakeTools, "side_effect", plant)
    code, fake, _ = run(env, monkeypatch, boot_report="none")
    assert code == nm.EXIT_DEGRADED and not fake.ran("ownership")


def test_prune_deletion_failure_degrades_and_preserves_the_registration(env, monkeypatch):
    seed(env, newest={"at": 3}, old={"at": 1})

    def cannot_delete(path, ignore_errors=False):
        if not ignore_errors:
            raise OSError("cannot delete snapshot")
    monkeypatch.setattr(nm.shutil, "rmtree", cannot_delete)
    code, _, summary = run(env, monkeypatch, "--keep-snapshots", "2")
    assert code == nm.EXIT_DEGRADED and "prune" in summary["failures_after_bundle"]
    registry = nm.read_json(env["root"] / "build" / "nightly_measure" / "snapshots.json")
    assert str((env["snap"] / "old").resolve()) in registry


@pytest.mark.parametrize("stage", ["release", "prune_snapshots", "save"])
@pytest.mark.parametrize("error", [OSError, nm.StepFailed])
def test_post_publish_finalization_io_errors_degrade(env, monkeypatch, stage, error):
    original = getattr(nm.Run, stage)

    def fail(self):
        if self.bundle_out and (stage != "save" or self.summary["status"] in ("ok", "degraded")):
            raise error("disk full")
        return original(self)
    monkeypatch.setattr(nm.Run, stage, fail)
    code, _, summary = run(env, monkeypatch)
    assert code == nm.EXIT_DEGRADED
    if stage != "save":
        assert stage.replace("_snapshots", "") in summary["failures_after_bundle"]


@pytest.mark.parametrize("where", ["clock", "summary"])
def test_bookkeeping_failure_after_the_publish_command_has_exit_four(env, monkeypatch, where):
    original_save, original_clock = nm.Run.save, nm.stamp_clock

    def save(self):
        if self.summary["status"] == "running" and self.summary["steps"] and self.summary["steps"][-1]["step"] == "publish":
            raise OSError("cannot save the publish record")
        return original_save(self)

    def clock(path, what, **kwargs):
        if what == "nightly_measure publish":
            raise OSError("cannot stamp the successful publication")
        return original_clock(path, what, **kwargs)
    monkeypatch.setattr(nm.Run, "save", save if where == "summary" else original_save)
    monkeypatch.setattr(nm, "stamp_clock", clock if where == "clock" else original_clock)
    code, fake, summary = run(env, monkeypatch)
    assert code == nm.EXIT_DEGRADED and summary["status"] == "degraded"
    assert fake.ran("publish") and "post-publish" in summary["failures_after_bundle"]


@pytest.mark.parametrize("step", ["cycle", "boot", "history-commit", "history-push"])
def test_sources_are_rescanned_before_each_compile_or_hook(env, monkeypatch, step):
    previous = {"cycle": "gate", "boot": "install", "history-commit": "ownership", "history-push": "history-rebase"}[step]
    src = env["checkout"] / "Code" / "unit.cpp"
    src.parent.mkdir()
    src.write_text("// cl: /O2\n")
    query, effect = FakeTools.query, FakeTools.side_effect

    def listed(self, args):
        if "ls-files" in args:
            return 0, b"Code/unit.cpp\0"
        return query(self, args)

    def tamper(self, name, argv, code):
        effect(self, name, argv, code)
        if name == previous:
            src.write_text("// cl: /B2evil.exe\n")
    monkeypatch.setattr(FakeTools, "query", listed)
    monkeypatch.setattr(FakeTools, "side_effect", tamper)
    code, fake, _ = run(env, monkeypatch)
    assert code == (nm.EXIT_UNAPPROVED if step == "cycle" else nm.EXIT_DEGRADED)
    assert not fake.ran(step)


@pytest.mark.parametrize("tamper", ["source", "hook"])
def test_sources_and_hooks_are_reverified_after_the_push_cooldown(env, monkeypatch, tamper):
    src = env["checkout"] / "Code" / "unit.cpp"
    src.parent.mkdir()
    src.write_text("// cl: /O2\n")
    query = FakeTools.query

    def listed(self, args):
        if "ls-files" in args:
            return 0, b"Code/unit.cpp\0"
        return query(self, args)

    def tweak(fake):
        def wait(_seconds):
            if tamper == "source":
                src.write_text("// cl: /B1evil.exe\n")
            else:
                (fake.run.hooks / "pre-push").write_text("unapproved hook\n")
        monkeypatch.setattr(nm.time, "sleep", wait)
    monkeypatch.setattr(FakeTools, "query", listed)
    code, fake, _ = run(env, monkeypatch, tweak=tweak)
    assert code == nm.EXIT_DEGRADED and not fake.ran("history-push")


@pytest.mark.parametrize("path", ["Code/header.h", "outside/unit.c", "outside/unit.asm", "outside/ledger.source"])
def test_every_source_path_is_scanned_including_ledger_sources(env, monkeypatch, path):
    source = env["checkout"] / path
    source.parent.mkdir(parents=True, exist_ok=True)
    source.write_text("\ufeff" + "// comment\n" * 300 + "// compiler: unpinned\n", encoding="utf-8")
    ledger = env["checkout"] / "reverse" / "functions.csv"
    ledger.parent.mkdir(exist_ok=True)
    ledger.write_text("source\n" + path + "\n")
    original = FakeTools.query

    def listed(self, args):
        if "ls-files" in args:
            return 0, path.encode() + b"\0"
        return original(self, args)
    monkeypatch.setattr(FakeTools, "query", listed)
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_UNAPPROVED and not fake.ran("gate")


@pytest.mark.parametrize("target_path,target_data", [
    ("Code/new.cpp", "// cl: /B1evil.exe\n"),
    ("reverse/retail_inventory/flag_regions.csv", "opt\nB1evil.exe\n"),
    ("reverse/functions.csv", "source\nCode/new.cpp\n"),
])
def test_rebase_target_source_controls_are_scanned_before_its_hooks(env, monkeypatch, target_path, target_data):
    original = FakeTools.query

    def target(self, args):
        while args and args[0] == "-c":
            args = args[2:]
        if args[0] == "diff":
            return 0, target_path.encode() + b"\0"
        if args[:2] == ["show", f"{COMMIT}:{target_path}"]:
            return 0, target_data
        if args[:2] == ["show", f"{COMMIT}:Code/new.cpp"]:
            return 0, b"// compiler: unpinned\n"
        return original(self, args)
    monkeypatch.setattr(FakeTools, "query", target)
    code, fake, _ = run(env, monkeypatch)
    assert code == nm.EXIT_DEGRADED and not fake.ran("history-rebase") and not fake.ran("history-push")


def small_git_repo(tmp_path):
    """Real Git in a disposable repository, with harmless hooks; never the project hooks."""
    repo, empty = tmp_path / "git-fixture", tmp_path / "setup-hooks"
    repo.mkdir()
    empty.mkdir()

    def git(*args):
        result = subprocess.run(["git", "-c", f"core.hooksPath={empty}", "-c", "core.fsmonitor=",
                                 "-c", "user.name=Test", "-c", "user.email=test@example.invalid", *args],
                                cwd=repo, env=nm.git_environment(), capture_output=True, text=True)
        assert result.returncode == 0, result.stderr
        return result.stdout.strip()
    git("init", "-q")
    (repo / "Code").mkdir()
    (repo / "Code" / "safe.cpp").write_text("// cl: /O2\n")
    (repo / ".gitattributes").write_text("Code/safe.cpp filter=plant\n")
    hooks = repo / ".githooks"
    hooks.mkdir()
    marker = tmp_path / "approved-hook-ran"
    for hook in ("pre-commit", "post-checkout"):
        path = hooks / hook
        path.write_text("#!/bin/sh\nprintf approved > " + shlex.quote(marker.as_posix()) + "\n", encoding="utf-8")
        path.chmod(0o755)
    git("add", "--", "Code/safe.cpp", ".gitattributes", ".githooks")
    git("commit", "-qm", "fixture")
    return repo, git, marker


def test_real_git_disables_absolute_checkout_hook_fsmonitor_filters_and_aliases(tmp_path, monkeypatch):
    repo, git, approved_marker = small_git_repo(tmp_path)
    r = nm.Run(nm.parse(["--checkout", str(repo)]), tmp_path / "runner", out=lambda *_: None)
    r.open_run_dir()
    r.hooks.mkdir(parents=True)
    r.approved = {"githooks_tree": git("rev-parse", "HEAD:.githooks")}
    marker = tmp_path / "unapproved-hook-or-config-ran"
    plant = tmp_path / "planted.sh"
    plant.write_text("#!/bin/sh\nprintf planted > " + shlex.quote(marker.as_posix()) + "\ncat\n")
    plant.chmod(0o755)
    # Mimic this host's absolute core.hooksPath, pointing outside the measured tree.
    outside_hooks = tmp_path / "main-hooks"
    outside_hooks.mkdir()
    for name in ("post-checkout", "pre-commit"):
        (outside_hooks / name).write_bytes(plant.read_bytes())
        (outside_hooks / name).chmod(0o755)
    git("config", "core.hooksPath", str(outside_hooks.resolve()))
    git("config", "core.fsmonitor", shlex.quote(plant.as_posix()))
    git("config", "filter.plant.smudge", "sh " + shlex.quote(plant.as_posix()))
    git("config", "alias.nightly-test", "!sh " + shlex.quote(plant.as_posix()))
    # Positive control: the configured post-checkout really does execute in plain Git.
    control = subprocess.run(["git", "-c", "core.fsmonitor=", "checkout", "--detach", "--force", "HEAD"],
                             cwd=repo, env=nm.git_environment(), capture_output=True)
    assert control.returncode == 0 and marker.exists()
    marker.unlink()
    (repo / "Code" / "safe.cpp").write_text("changed\n")
    r.step("checkout", ["git", "checkout", "--detach", "--force", "HEAD"])
    assert not marker.exists() and not approved_marker.exists()
    assert (repo / "Code" / "safe.cpp").read_text() == "// cl: /O2\n"
    # Isolate hook/config precedence from approval tests: the real runner proof is
    # tested above with FakeTools, and this fixture has no full approved toolchain.
    monkeypatch.setattr(r, "prove_code", lambda *_: None)
    r.approved_hooks()
    assert r.hooks.is_relative_to(r.work) and not r.hooks.is_relative_to(repo)
    monkeypatch.setenv("GIT_AUTHOR_NAME", "Test")
    monkeypatch.setenv("GIT_AUTHOR_EMAIL", "test@example.invalid")
    monkeypatch.setenv("GIT_COMMITTER_NAME", "Test")
    monkeypatch.setenv("GIT_COMMITTER_EMAIL", "test@example.invalid")
    r.step("history-commit", ["git", "commit", "--allow-empty", "-qm", "fixture history"])
    assert approved_marker.read_text() == "approved" and not marker.exists()
    config = nm.driver_overrides(repo)
    assert "alias.nightly-test=" in config and "filter.plant.smudge=" in config


def test_real_git_credential_helpers_cannot_run_in_a_build_environment(tmp_path, monkeypatch):
    repo, git, _ = small_git_repo(tmp_path)
    marker = tmp_path / "credential-helper-ran"
    helper = "!printf called > " + shlex.quote(marker.as_posix())
    git("config", "credential.helper", helper)
    git("config", "credential.https://example.invalid.helper", helper)
    control = subprocess.run(["git", "credential", "fill"], cwd=repo, env=nm.git_environment(),
                             input="protocol=https\nhost=example.invalid\n\n", capture_output=True, text=True)
    assert control.returncode != 0 and marker.exists()
    marker.unlink()
    r = nm.Run(nm.parse(["--checkout", str(repo)]), tmp_path / "runner")
    r.work.mkdir(parents=True)
    r.gh_dir = Path(tempfile.mkdtemp(dir=r.work))
    for key in ("GH_TOKEN", "GITHUB_TOKEN", "GIT_ASKPASS", "SSH_ASKPASS"):
        monkeypatch.setenv(key, "sensitive")
    child = r.env(git_config=nm.driver_overrides(repo))
    result = subprocess.run(["git", "credential", "fill"], cwd=repo, env=child,
                            input="protocol=https\nhost=example.invalid\n\n", capture_output=True, text=True)
    assert result.returncode != 0 and not marker.exists()
    assert not list(r.gh_dir.iterdir()) and not any(k in child for k in nm.CRED_ENV)
    # The publisher keeps its own authentication settings; a build never gets them.
    publisher = r.env(credentialed=True)
    assert publisher["GH_TOKEN"] == "sensitive" and publisher.get("GIT_CONFIG_GLOBAL") == os.devnull
    assert "credential.helper" not in [publisher.get(f"GIT_CONFIG_KEY_{i}")
                                        for i in range(int(publisher["GIT_CONFIG_COUNT"]))]


@pytest.mark.parametrize("key", list(IDENT))      # the test's own list: never the module's, which could shrink
def test_every_part_of_the_identity_is_approved(env, monkeypatch, key):
    code, fake, summary = run(env, monkeypatch, tweak=lambda f: f.ident.update({key: "q" * 40}))
    assert code == nm.EXIT_UNAPPROVED and [name_of(a) for a in fake.calls] == ["fetch"]
    assert key in {s["step"]: s for s in summary["steps"]}["approval"]["note"]


def test_approve_refuses_a_commit_not_on_origin_master(env, monkeypatch):
    fake = FakeTools(type("R", (), {})())
    fake.merge_base = 1
    monkeypatch.setattr(nm.subprocess, "run", fake)
    work = env["root"] / "build" / "nightly_measure"
    before = (work / "approved.json").read_text()
    assert nm.main(["--approve", "somebranch"], root=env["root"], out=lambda *_: None) == nm.EXIT_SETUP
    assert (work / "approved.json").read_text() == before and not (work / "runner").exists()


def test_the_clones_main_tree_is_refused_even_marked_and_detached(env, monkeypatch, tmp_path):
    root = tmp_path / ("r" * 40)                    # long enough that the snapshot length check passes
    (root / "build").mkdir(parents=True)
    (root / "build" / nm.MARK).write_text("x")
    nm.write_json(root / "build" / "nightly_measure" / "approved.json", {"commit": "a" * 40, **IDENT})
    code, fake, _ = run(dict(env, root=root), monkeypatch, "--checkout", str(root), "--snapshot-dir",
                        str(tmp_path / "s"))
    assert code == nm.EXIT_SETUP and fake.calls == []


# ---------------------------------------------------------------- round 3: the exit contract after the publish

@pytest.mark.parametrize("where", ["install", "history-status", "history-identity", "push-clean", "copy-boot",
                                   "copy-history"])
def test_a_failure_after_the_publish_degrades_and_never_exits_1(env, monkeypatch, where):
    real_copy = nm.shutil.copyfile

    def tweak(f):
        if where == "history-status":
            f.fail_query = lambda a: a[0] == "status" and nm.HISTORY_CSV in a and "tools" not in a
        elif where == "history-identity":
            f.history_master = MASTER2
            f.fail_query = lambda a: a[-1] == f"{MASTER2}:vendor"
        elif where == "push-clean":
            f.fail_query = lambda a: a[0] == "clean" and bool(f.ran("history-rebase"))

    def copy(src, dst, *a, **k):
        if (where == "copy-boot" and Path(dst).name == "relayout.json") or \
                (where == "copy-history" and Path(dst).name == "image_ownership_history.csv"):
            raise OSError(28, "No space left on device")
        return real_copy(src, dst, *a, **k)
    monkeypatch.setattr(nm.shutil, "copyfile", copy)
    code, fake, summary = run(env, monkeypatch, codes={"install": 1} if where == "install" else {}, tweak=tweak)
    assert code == nm.EXIT_DEGRADED and summary["status"] == "degraded" and fake.ran("publish")
    stage = {"install": "install", "copy-boot": "boot"}.get(where, "history")
    assert stage in summary["failures_after_bundle"]
    if where == "install":
        assert fake.ran("boot") and fake.ran("history-push")            # install never blocks what follows
    if where != "install":
        assert not fake.ran("history-push")


@pytest.mark.parametrize("rc", [0, 1])
def test_a_stale_boot_report_is_never_measured(env, monkeypatch, rc):
    boot = env["checkout"] / "build" / "boot"
    boot.mkdir(parents=True)
    stale = boot / "relayout.json"
    stale.write_text(json.dumps({"link_exit": 0}))
    os.utime(stale, (time.time() - 3600, time.time() - 3600))
    code, fake, summary = run(env, monkeypatch, codes={"boot": rc}, boot_report="none")
    assert code == nm.EXIT_DEGRADED and status(summary)["boot"] == "failed" and not fake.ran("ownership")


# ---------------------------------------------------------------- round 3: the prune guards

def seed(env, **specs):
    """Registered snapshots: name -> registered order, released, lease (seconds from now), marked, parent."""
    reg = {}
    for name, kw in specs.items():
        d = kw.get("parent", env["snap"]) / name
        d.mkdir(parents=True)
        if kw.get("marked", True):
            (d / nm.SNAPSHOT_MARK).write_text("{}")
        reg[str(d.resolve())] = {"created_by": kw.get("created_by", "an older run"), "registered": kw["at"],
                                 "released": kw.get("released", True), "lease_until": time.time() + kw.get("lease", 3600)}
    nm.write_json(env["root"] / "build" / "nightly_measure" / "snapshots.json", reg)


def left(env):
    return sorted(p.name for p in env["snap"].iterdir())


def test_prune_keeps_a_live_lease_outside_the_window_and_takes_an_expired_one(env, monkeypatch):
    seed(env, newest={"at": 3000}, leased={"at": 2000, "released": False},
         expired={"at": 1000, "released": False, "lease": -3600})
    code, _, _ = run(env, monkeypatch, "--keep-snapshots", "2")
    assert code == nm.EXIT_OK and left(env) == sorted([COMMIT[:10], "newest", "leased"])


def test_prune_never_takes_an_unmarked_snapshot_or_one_in_another_dir(env, monkeypatch):
    foreign = env["tmp"] / "foreign"
    seed(env, newest={"at": 3000}, unmarked={"at": 2000, "marked": False}, elsewhere={"at": 1000, "parent": foreign})
    code, _, _ = run(env, monkeypatch, "--keep-snapshots", "2")
    assert code == nm.EXIT_OK and left(env) == sorted([COMMIT[:10], "newest", "unmarked"])
    assert (foreign / "elsewhere" / nm.SNAPSHOT_MARK).is_file()


def test_prune_never_takes_this_runs_snapshot_however_old(env, monkeypatch):
    seed(env, **{COMMIT[:10]: {"at": 1}, "new2": {"at": 3000}, "new1": {"at": 2000}})
    code, _, _ = run(env, monkeypatch, "--keep-snapshots", "2")
    assert code == nm.EXIT_OK and left(env) == sorted([COMMIT[:10], "new2"])


def test_prune_keeps_n_when_the_run_made_no_snapshot(env, monkeypatch):
    seed(env, a={"at": 3000}, b={"at": 2000}, c={"at": 1000})
    code, _, _ = run(env, monkeypatch, "--keep-snapshots", "2", codes={"gate": 1})
    assert code == nm.EXIT_FAILED and left(env) == ["a", "b"]


def test_prune_never_runs_after_an_unapproved_or_interrupted_run(env, monkeypatch):
    seed(env, a={"at": 2000}, b={"at": 1000})
    code, _, _ = run(env, monkeypatch, "--keep-snapshots", "1", tweak=lambda f: f.ident.update(tools_tree="u" * 40))
    assert code == nm.EXIT_UNAPPROVED and left(env) == ["a", "b"]
    with pytest.raises(KeyboardInterrupt):
        run(env, monkeypatch, "--keep-snapshots", "1", codes={"gate": "interrupt"})
    assert left(env) == ["a", "b"]

# ---------------------------------------------------------------- round 4: production role boundary

@pytest.fixture
def split(tmp_path, monkeypatch):
    root = tmp_path / 'repo'
    install, handoff = tmp_path / 'install', tmp_path / 'handoff'
    builder_state, publisher_state = tmp_path / 'bs', tmp_path / 'ps'
    for p in (root, install, handoff, builder_state, publisher_state):
        p.mkdir()
    checker = install / 'checkers'
    checker.mkdir()
    for name in ('image_ownership.py', 'publish_cycle.py', 'closure_report.py', 'cycle_artifacts.py', 'link_cycle.py',
                 'data_back_rank.py'):
        (checker / name).write_text('# pinned checker\n')
    runner = install / 'runner/nightly_measure.py'
    runner.parent.mkdir()
    runner.write_bytes(nm.RUNNER.read_bytes())
    monkeypatch.setattr(nm, 'RUNNER', runner)
    monkeypatch.setattr(nm, 'TRUSTED_COMMANDS', {})
    monkeypatch.setattr(nm, 'TRUSTED_CWD', None)
    policy = dict(builder_sid='builder-sid', publisher_sid='publisher-sid', publisher_profile=str(tmp_path/'publisher'),
                  publisher_state=str(publisher_state), builder_state=str(builder_state), signing_key=str(tmp_path/'secret/key'),
                  allowed_signers=str(tmp_path/'secret/signers'), repository='example/repo',
                  repository_url='https://example.invalid/repo.git', bfme1_url='https://example.invalid/bfme1.git',
                  python=sys.executable, executables={name:str(tmp_path/'trusted'/f'{name}.exe')
                                                     for name in ('git', 'gh', 'ssh-keygen')})
    (install/'retail.dat').write_bytes(b'trusted retail fixture')
    policy['retail_sha256']=nm.sha256_bytes((install/'retail.dat').read_bytes())
    nm.write_json(install/'security.json', policy)
    nm.write_json(install/'approved.json', dict(IDENT, commit=COMMIT, checker_files=nm.tree_hashes(checker)))
    args = lambda role: nm.parse(['--role',role,'--root',str(root),'--install-dir',str(install),
                                 '--state-dir',str(builder_state if role=='builder' else publisher_state),
                                 '--handoff-dir',str(handoff)])
    return dict(root=root, install=install, handoff=handoff, bs=builder_state, ps=publisher_state,
                policy=policy, args=args)


def split_run(split, role):
    cls = nm.BuilderRun if role == 'builder' else nm.PublisherRun
    return cls(split['args'](role), split['root'], out=lambda *_: None)


def fake_isolation(monkeypatch, split, role):
    monkeypatch.setattr(nm, 'current_sid', lambda: split['policy'][role+'_sid'])
    monkeypatch.setattr(nm, 'readable', lambda p: False)
    monkeypatch.setattr(nm, 'writable', lambda p: False)
    monkeypatch.setattr(nm, 'directory_writable', lambda p: False)


def test_roles_are_mandatory_and_missing_configuration_is_refused(tmp_path):
    assert nm.main([], root=tmp_path, out=lambda *_:None) == nm.EXIT_SETUP
    assert nm.main(['--role','builder'], root=tmp_path, out=lambda *_:None) == nm.EXIT_SETUP


@pytest.mark.parametrize('role', ['builder','publisher'])
def test_role_rejects_the_other_windows_account(split, monkeypatch, role):
    r = split_run(split, role)
    monkeypatch.setattr(nm, 'current_sid', lambda: split['policy'][('publisher' if role=='builder' else 'builder')+'_sid'])
    with pytest.raises(nm.Refused, match='distinct configured'):
        r.preflight()


@pytest.mark.parametrize('location', ['.ssh','AppData/Roaming/GitHub CLI','.git-credentials',
                                    'AppData/Local/Microsoft/Credentials','AppData/Roaming/Microsoft/Credentials',
                                    'secret/key','ps'])
def test_builder_refuses_readable_publisher_credentials(split, monkeypatch, location):
    fake_isolation(monkeypatch, split, 'builder')
    monkeypatch.setattr(nm,'readable',lambda p: str(p).replace('\\','/').endswith('/'+location))
    with pytest.raises(nm.Refused, match='read publisher credential'):
        split_run(split,'builder').preflight()


def test_probes_distinguish_access_denial_from_missing_files(tmp_path, monkeypatch):
    absent = tmp_path/'no-credentials-here'
    with pytest.raises(nm.Refused, match='inconclusive'):
        nm.readable(absent)
    def denied(*a, **kw):
        raise PermissionError('fake ACL denied')
    monkeypatch.setattr(Path,'open',denied)
    assert not nm.readable(absent) and not nm.writable(absent)


@pytest.mark.parametrize('target',['approved.json','runner/nightly_measure.py','checkers/image_ownership.py'])
def test_builder_cannot_use_a_writable_installation(split, monkeypatch, target):
    fake_isolation(monkeypatch,split,'builder')
    monkeypatch.setattr(nm,'writable',lambda p: p == split['install']/target)
    with pytest.raises(nm.Refused,match='rewrite'):
        split_run(split,'builder').preflight()


def test_builder_refuses_parent_rename_and_delete_access(split,monkeypatch):
    fake_isolation(monkeypatch,split,'builder')
    monkeypatch.setattr(nm,'directory_writable',lambda p:p==split['install'].parent)
    with pytest.raises(nm.Refused,match='rewrite'):
        split_run(split,'builder').preflight()


@pytest.mark.parametrize('role',['builder','publisher'])
def test_pinned_bundle_tampering_is_refused_for_both_roles(split,monkeypatch,role):
    fake_isolation(monkeypatch,split,role)
    (split['install']/'checkers/image_ownership.py').write_text('raise SystemExit(99)')
    with pytest.raises(nm.Refused,match='checker bundle'):
        split_run(split,role).preflight()


def test_builder_child_environment_and_command_boundary(split):
    r=split_run(split,'builder')
    assert r.env()['BUILD_POOL']=='2'
    with pytest.raises(nm.Refused,match='credentials'):
        r.env(True)
    for name in ('publish','history-push-1','previous','install'):
        with pytest.raises(nm.Refused,match='cannot publish'):
            r.step(name,['git','push'])


def test_builder_orchestration_measures_before_handoff_and_never_publishes(split,monkeypatch):
    r=split_run(split,'builder')
    r.checkout.mkdir(parents=True)
    (r.checkout/'build').mkdir()
    (r.checkout/'build'/nm.MARK).write_text('owned')
    r.open_run_dir()
    r.commit=COMMIT
    events=[]
    monkeypatch.setattr(r,'prove_sources',lambda:events.append('sources'))
    monkeypatch.setattr(r,'cycle',lambda:events.append('cycle'))
    monkeypatch.setattr(r,'step',lambda name,*a,**kw:events.append(name))
    monkeypatch.setattr(r,'boot',lambda:events.append('boot') or r.checkout/'build/boot/x.json')
    monkeypatch.setattr(r,'ownership',lambda report:events.append('ownership'))
    monkeypatch.setattr(r,'export_handoff',lambda report:events.append('handoff'))
    r.measure()
    assert events==['sources','gate','cycle','validate','closure','bundle','boot','ownership','handoff']
    assert list((r.checkout/'build').iterdir())==[r.checkout/'build'/nm.MARK]


def test_builder_ownership_requests_measure_only(split,monkeypatch):
    r=split_run(split,'builder')
    r.open_run_dir()
    (r.checkout/'tools').mkdir(parents=True)
    (r.checkout/'tools/image_ownership.py').write_text('# fake')
    calls=[]
    monkeypatch.setattr(r,'step',lambda *a,**kw:calls.append(a) or {'status':'ok'})
    r.ownership(r.checkout/'build/boot/x.json')
    assert calls[0][1][-1]=='measure' and not r.args.no_publish


@pytest.mark.parametrize('name',['git.exe','compiler_profiles/clang23-x86/hash/clang-cl.cfg',
                                  'compiler_profiles/clang23-x86/hash/version.dll'])
def test_preexisting_build_content_including_ignored_files_is_refused(tmp_path,name):
    co=tmp_path/'checkout'
    p=co/'build'/name
    p.parent.mkdir(parents=True)
    p.write_bytes(b'planted')
    with pytest.raises(nm.Refused,match='pre-existing'):
        nm.reject_build_inputs(co)


def test_target_cannot_force_track_build_in_any_case(tmp_path,monkeypatch):
    monkeypatch.setattr(nm,'git',lambda *a,**kw:subprocess.CompletedProcess(a,0,'Code/a.cpp\nbUiLd/plugin.dll\n',''))
    with pytest.raises(nm.Refused,match='tracked path'):
        nm.reject_build_inputs(tmp_path,COMMIT)


@pytest.mark.parametrize('extra',['clang-cl.cfg','version.dll','nested/clang-cl.cfg'])
def test_clang_cache_extras_are_wiped_and_reextracted(tmp_path,extra):
    import zipfile
    root=tmp_path/'co'
    (root/'tools').mkdir(parents=True)
    archive=root/'vendor/clang23-x86/compiler.zip'
    archive.parent.mkdir(parents=True)
    files={'clang-cl.exe':b'pinned compiler','libLLVM-23.dll':b'pinned library'}
    with zipfile.ZipFile(archive,'w') as z:
        for name,data in files.items():
            z.writestr('bin/'+name,data)
    archive_sha=nm.sha256_bytes(archive.read_bytes())
    hashes={n:nm.sha256_bytes(d) for n,d in files.items()}
    (root/'tools/compiler_profiles.py').write_text('CLANG23_FILES = '+repr(hashes)+'\nCLANG23_ARCHIVE_SHA256 = '+repr(archive_sha))
    dest=root/'build/compiler_profiles/clang23-x86'/archive_sha
    dest.mkdir(parents=True)
    for name,data in files.items():
        (dest/name).write_bytes(data)
    plant=dest/extra
    plant.parent.mkdir(parents=True,exist_ok=True)
    plant.write_bytes(b'-Xclang -load plugin.dll')
    nm.clang_cache(root)
    assert nm.tree_hashes(dest)==hashes and not plant.exists()
    # Existing expected file corruption also forces extraction, not a hash-only refusal.
    (dest/'clang-cl.exe').write_bytes(b'changed')
    nm.clang_cache(root)
    assert nm.tree_hashes(dest)==hashes


def test_ccc_override_and_external_diff_cannot_reach_children(split,monkeypatch):
    r=nm.Run(nm.parse([]),split['root'])
    monkeypatch.setenv('CCC_OVERRIDE_OPTIONS','+-Xclang +-load +plugin.dll')
    monkeypatch.setenv('GIT_EXTERNAL_DIFF','malicious.exe')
    monkeypatch.setenv('GIT_CONFIG_GLOBAL','malicious-global')
    monkeypatch.setenv('GIT_CONFIG_SYSTEM','malicious-system')
    for creds in (False,True):
        env=r.env(creds)
        assert 'CCC_OVERRIDE_OPTIONS' not in env and 'GIT_EXTERNAL_DIFF' not in env
        assert env['GIT_CONFIG_GLOBAL']==os.devnull and env['GIT_CONFIG_SYSTEM']==os.devnull
        assert env['GIT_CONFIG_NOSYSTEM']=='1'


def test_credentialed_git_ignores_global_drivers_and_neutralizes_repo_diff(tmp_path,monkeypatch):
    repo,git,_=small_git_repo(tmp_path)
    global_config=tmp_path/'malicious-global'
    global_config.write_text('[alias]\n  planted = !echo planted\n[filter "planted"]\n  process = evil.exe\n')
    monkeypatch.setenv('GIT_CONFIG_GLOBAL',str(global_config))
    monkeypatch.setenv('GIT_CONFIG_SYSTEM',str(global_config))
    git('config','diff.planted.textconv','evil.exe')
    git('config','diff.planted.command','evil.exe')
    pairs=nm.driver_overrides(repo)
    assert 'diff.planted.textconv=' in pairs and 'diff.planted.command=' in pairs
    r=nm.Run(nm.parse([]),tmp_path/'runner')
    env=r.env(True,pairs)
    query=subprocess.run(['git','config','--get','alias.planted'],cwd=repo,env=env,capture_output=True)
    assert query.returncode==1
    for name in ('textconv','command'):
        q=subprocess.run(['git','config','--get','diff.planted.'+name],cwd=repo,env=env,capture_output=True,text=True)
        assert q.returncode==0 and q.stdout.strip()==''


def make_handoff(split):
    source=split['handoff']/'20261024T010000Z'
    for rel in ('workspace/build/boot/x.json','workspace/build/boot/x.exe','workspace/build/boot/x.map',
                'workspace/tools/evil.py','snapshot/build/link_cycle/receipt.json','bundle/manifest.json',
                'bundle/data_back_rank.txt','bundle/data_back_rank.json'):
        p=source/rel
        p.parent.mkdir(parents=True,exist_ok=True)
        p.write_text('{}' if p.suffix=='.json' else 'untrusted')
    meta={'schema':1,'commit':COMMIT,'created':time.time(),'report':'build/boot/x.json','files':nm.tree_hashes(source)}
    nm.write_json(source/'handoff.json',meta)
    nm.write_json(split['handoff']/'latest.json',{'id':source.name,'sha256':nm.sha256_bytes((source/'handoff.json').read_bytes())})
    return source


def fake_rank_outputs(r):
    # Orchestration-only bytes; the rank regression tests use the real ranker.
    (r.dir/'rank.log').write_text('untrusted')
    (r.dir/'rank/data_back_rank.json').write_text('{}')


def prepared_publisher(split,monkeypatch):
    r=split_run(split,'publisher')
    r.open_run_dir()
    def policy():
        r.policy=split['policy']
        r.load_approval()
        r.verify_bundle()
    monkeypatch.setattr(r,'preflight',policy)
    monkeypatch.setattr(r,'private_git',lambda *a:None)
    monkeypatch.setattr(r,'bind_inputs',lambda:None) # No Git objects in this orchestration-only fixture.
    monkeypatch.setattr(r,'step',lambda *a,**kw: {'status':'ok'})
    monkeypatch.setattr(nm,'identity',lambda *a:dict(IDENT))
    monkeypatch.setattr(r,'prove_sources',lambda:None)
    r.prepare()
    return r


def test_publisher_freezes_handoff_and_replaces_all_builder_tools(split,monkeypatch):
    source=make_handoff(split)
    before=nm.tree_hashes(split['handoff'])
    r=prepared_publisher(split,monkeypatch)
    assert nm.tree_hashes(r.staged_tools)==r.approved['checker_files']
    assert not (r.staged_tools/'evil.py').exists()
    (source/'workspace/build/boot/x.exe').write_text('changed after freeze')
    assert r.report.with_suffix('.exe').read_text()=='untrusted'
    # Release/prune never touch builder state or handoff.
    r.release(); r.prune_snapshots()
    assert (source/'handoff.json').is_file() and before['latest.json']==nm.tree_hashes(split['handoff'])['latest.json']


@pytest.mark.parametrize('change',['artifact','manifest','stale','replay'])
def test_publisher_refuses_tampered_stale_or_replayed_handoffs(split,monkeypatch,change):
    source=make_handoff(split)
    if change=='artifact':
        (source/'workspace/build/boot/x.exe').write_text('tampered')
    elif change=='manifest':
        # Keep a valid schema and inventory: only the old pointer hash can reject this edit.
        meta=nm.read_json(source/'handoff.json')
        meta['created']-=10
        nm.write_json(source/'handoff.json',meta)
    elif change=='stale':
        monkeypatch.setattr(nm.time,'time',lambda frozen=time.time()+90000:frozen)
    else:
        nm.write_json(split['ps']/'processed.json',[nm.sha256_bytes((source/'handoff.json').read_bytes())])
    with pytest.raises(nm.Refused):
        prepared_publisher(split,monkeypatch)


@pytest.mark.parametrize('path',['../approved.json','C:/Users/publisher/.ssh/key','bad:stream','tools/../key','NUL.txt','build\\evil'])
def test_handoff_paths_cannot_escape_or_use_windows_aliases(path):
    with pytest.raises(nm.Refused):
        nm.safe_relative(path)


def test_publisher_cannot_execute_build_boot_or_git_hooks(split,monkeypatch):
    r=split_run(split,'publisher')
    for script in ('tools/build.py','tools/link_cycle.py','tools/boot_image.py'):
        with pytest.raises(nm.Refused,match='cannot execute'):
            r.tool(script)
    for argv in (['git','commit','-m','x'],['git','push'],['C:/co/build/boot/game.exe']):
        with pytest.raises(nm.Refused):
            r.step('renamed-to-validate',argv)


def test_publisher_revalidates_ownership_before_any_publication(split,monkeypatch):
    make_handoff(split)
    r=prepared_publisher(split,monkeypatch)
    calls=[]
    def step(name,argv,**kw):
        calls.append((name,argv))
        if name=='rank':
            fake_rank_outputs(r)
        if name=='ownership-verify':
            raise nm.StepFailed('bound artifact mismatch')
        return {'status':'ok'}
    monkeypatch.setattr(r,'step',step)
    monkeypatch.setattr(r,'publish',lambda:pytest.fail('publication before ownership verification'))
    with pytest.raises(nm.StepFailed):
        r.measure()
    assert [name for name,_ in calls]==['handoff-validate','rank','ownership-verify']
    own=calls[-1][1]
    assert own[-3:]==[split['policy']['signing_key'],split['policy']['allowed_signers'],'record']
    assert nm.PUBLISHER_CHECKS in calls[0][1] and nm.PUBLISHER_OWNERSHIP in own


def test_publisher_refuses_external_artifact_references(split,monkeypatch):
    make_handoff(split)
    r=prepared_publisher(split,monkeypatch)
    nm.write_json(r.report,{'provenance':{'objects':{'entries':[['C:/Users/publisher/key','hash','Code/a.cpp']]}}})
    with pytest.raises(nm.Refused,match='unsafe'):
        r.check_artifact_paths()


def test_publisher_native_guard_uses_pinned_executables_and_private_cwd(tmp_path,monkeypatch):
    calls=[]
    def launch(argv,**kw):
        calls.append((argv,kw))
        return 'fake process'
    monkeypatch.setattr(subprocess,'Popen',launch)
    monkeypatch.setenv('NM_PUBLISHER_EXECUTABLES',json.dumps({'git':'C:/trusted/git.exe','gh':'C:/trusted/gh.exe',
                                                          'ssh-keygen':'C:/trusted/ssh-keygen.exe'}))
    monkeypatch.setenv('NM_PUBLISHER_SAFE_CWD',str(tmp_path/'private'))
    nm.publisher_process_guard()
    assert subprocess.Popen(['git','status'],cwd=tmp_path/'untrusted')=='fake process'
    assert calls[0][0]==['C:/trusted/git.exe','-C',str((tmp_path/'untrusted').absolute()),'status']
    assert calls[0][1]['cwd']==str(tmp_path/'private')
    for command in (['C:/co/build/boot/game.exe'],[sys.executable,'evil.py'],'git status'):
        with pytest.raises(RuntimeError,match='publisher refused'):
            subprocess.Popen(command)

@pytest.mark.parametrize('role', ['builder','publisher'])
def test_cli_dispatches_only_to_the_requested_role(split,monkeypatch,role):
    calls=[]
    monkeypatch.setattr(nm.SplitRun,'preflight',lambda r:calls.append(('preflight',type(r))))
    monkeypatch.setattr(nm.BuilderRun,'go',lambda r:calls.append(('go',type(r))) or 0)
    monkeypatch.setattr(nm.PublisherRun,'go',lambda r:calls.append(('go',type(r))) or 0)
    args=split['args'](role)
    assert nm.main(['--role',role,'--install-dir',str(split['install']),'--state-dir',args.state_dir,
                    '--handoff-dir',str(split['handoff'])],root=split['root'],out=lambda *_:None)==0
    expected=nm.BuilderRun if role=='builder' else nm.PublisherRun
    assert calls==[('preflight',expected),('go',expected)]


def test_builder_cannot_approve_an_installation(split,monkeypatch):
    monkeypatch.setattr(nm,'approve',lambda *a,**kw:pytest.fail('builder approval'))
    assert nm.main(['--role','builder','--approve',COMMIT],root=split['root'],out=lambda *_:None)==nm.EXIT_SETUP


@pytest.mark.parametrize('fault',['none','unverified','image-unbound','map-unbound','record-refusal','signature'])
def test_publisher_ownership_probe_rechecks_bound_artifacts_and_signature(tmp_path,fault):
    tools=tmp_path/'pinned'
    tools.mkdir()
    events=tmp_path/'events.json'
    receipt={'verified':fault!='unverified','image':{'bound':fault!='image-unbound'},
             'map':{'bound':fault!='map-unbound'}}
    (tools/'image_ownership.py').write_text(
        'import json\nfrom pathlib import Path\nEVENTS=Path('+repr(str(events))+')\n'
        'def event(name,**kw):\n    data=json.loads(EVENTS.read_text()) if EVENTS.exists() else []\n'
        '    EVENTS.write_text(json.dumps(data+[[name,kw]]))\n'
        'def measure(report,image=None):\n    event("measure",report=report,image=str(image))\n    return '+repr(receipt)+'\n'
        'def record_refusals(receipt):\n    event("refusals")\n    return '+repr(['stale object'] if fault=='record-refusal' else [])+'\n'
        'def record(receipt,path=None,key=None,signers=None):\n    event("sign",key=key,signers=signers)\n'
        'def check_history(path=None,signers=None):\n    event("verify-signature",signers=signers)\n    return '+repr(['bad signature'] if fault=='signature' else [])+'\n')
    report=tmp_path/'relayout.json'
    report.write_text('{}')
    command=[sys.executable,'-I','-c',nm.PUBLISHER_OWNERSHIP,str(tools),str(report),str(tmp_path/'out.json'),
             str(tmp_path/'history.csv'),'publisher-key','external-pin','record']
    result=subprocess.run(command,cwd=tmp_path,capture_output=True,text=True)
    called=json.loads(events.read_text())
    assert called[0]==['measure',{'report':str(report),'image':str(report.with_suffix('.exe'))}]
    if fault=='none':
        assert result.returncode==0, result.stderr
        assert [name for name,_ in called]==['measure','refusals','sign','verify-signature']
        assert called[2][1]=={'key':'publisher-key','signers':'external-pin'}
        document=json.loads(report.read_text())
        assert document['measurement_attestation']=={
            'schema':1,'basis':'builder-attested','statement':nm.BUILDER_ATTESTATION}
        assert json.loads((tmp_path/'out.json').read_text())['measurement_attestation']==document['measurement_attestation']
    else:
        assert result.returncode!=0
        if fault!='signature':
            assert not any(name=='sign' for name,_ in called)


def test_publisher_native_queries_also_use_the_private_cwd(split,monkeypatch):
    r=split_run(split,'publisher')
    fake_isolation(monkeypatch,split,'publisher')
    r.preflight()
    calls=[]
    monkeypatch.setattr(nm.subprocess,'run',lambda argv,**kw:calls.append((argv,kw)) or subprocess.CompletedProcess(argv,0,'',''))
    nm.git(split['root'],'status')
    argv,kw=calls[0]
    assert argv[:3]==[split['policy']['executables']['git'],'-C',str(split['root'])]
    assert kw['cwd']==split['ps']/'native-cwd'


def test_builder_compile_steps_prepare_the_exact_clang_cache(split,monkeypatch):
    r=split_run(split,'builder')
    r.checkout.mkdir(parents=True)
    r.open_run_dir()
    events=[]
    monkeypatch.setattr(nm,'clang_cache',lambda co:events.append(('cache',co)))
    monkeypatch.setattr(r,'prove_sources',lambda:events.append(('sources',r.checkout)))
    monkeypatch.setattr(nm,'driver_overrides',lambda cwd:[])
    monkeypatch.setattr(nm.subprocess,'run',lambda *a,**kw:events.append(('child',r.checkout)) or subprocess.CompletedProcess(a,0))
    r.step('gate',r.python('-c','pass'))
    assert events==[('cache',r.checkout),('sources',r.checkout),('child',r.checkout)]


def test_builder_checks_existing_and_target_build_inputs_before_measurement(split,monkeypatch):
    r=split_run(split,'builder')
    events=[]
    monkeypatch.setattr(r,'preflight',lambda:None)
    monkeypatch.setattr(nm,'reject_build_inputs',lambda co,target=None:events.append(('guard',target)))
    def prepare(self):
        events.append(('prepare',None))
        self.commit=COMMIT
    monkeypatch.setattr(nm.Run,'prepare',prepare)
    r.prepare()
    assert events==[('guard',None),('prepare',None),('guard',COMMIT)]


def test_publisher_rejects_counterfeit_checker_with_an_allowed_basename(split,monkeypatch):
    make_handoff(split)
    r=prepared_publisher(split,monkeypatch)
    # Invoke the production boundary, not the fake step installed by the fixture.
    argv=r.python('-c',nm.SCRIPT_BOOT,r.staged_tools,r.checkout/'publish_cycle.py','validate','data')
    with pytest.raises(nm.Refused,match='checkout tool'):
        nm.PublisherRun.step(r,'validate',argv)
    argv=r.python('-c',nm.SCRIPT_BOOT,r.checkout/'untrusted',r.staged_tools/'publish_cycle.py','validate','data')
    with pytest.raises(nm.Refused,match='import checkout'):
        nm.PublisherRun.step(r,'validate',argv)


def test_publisher_preflight_rejects_a_builder_writable_state_selection(split,monkeypatch):
    fake_isolation(monkeypatch,split,'publisher')
    r=split_run(split,'publisher')
    r.work=split['bs']
    with pytest.raises(nm.Refused,match='state directory'):
        r.preflight()


def test_only_the_installed_runner_can_use_a_pinned_bundle(split,monkeypatch):
    fake_isolation(monkeypatch,split,'publisher')
    r=split_run(split,'publisher')
    r.runner=TOOLS/'nightly_measure.py'
    with pytest.raises(nm.Refused,match='installed runner'):
        r.preflight()


def test_publisher_succeeds_through_validation_signature_and_separate_evidence_release(split,monkeypatch):
    make_handoff(split)
    r=prepared_publisher(split,monkeypatch)
    events=[]
    def step(name,argv,**kw):
        events.append(name)
        if name=='rank':
            fake_rank_outputs(r)
        if name=='previous':
            return {'status':'ok','exit':nm.EMPTY_STORE}
        if name=='ownership-verify':
            history=r.checkout/nm.HISTORY_CSV
            history.parent.mkdir(parents=True,exist_ok=True)
            history.write_text('signed-history-fake')
        if name=='bundle':
            nm.write_json(r.dir/'bundle/manifest.json',{'tag':'cycle-fake'})
        return {'status':'ok','exit':0}
    monkeypatch.setattr(r,'step',step)
    monkeypatch.setattr(r,'publish_ownership',lambda tag:events.append('ownership-release:'+tag))
    r.measure()
    assert events==['handoff-validate','rank','ownership-verify','validate','closure','previous','bundle','publish','install',
                    'ownership-release:cycle-fake']
    assert r.handoff_digest in nm.read_json(r.work/'processed.json')
    assert (r.dir/'image_ownership_history.csv').read_text()=='signed-history-fake'
    assert (r.cycle_dir()/'data_back_rank.txt').read_text()=='untrusted'
    assert nm.tree_hashes(r.staged_tools)==r.approved['checker_files']


def test_builder_flattens_link_cycles_hardlinks_but_publisher_refuses_incoming_links(tmp_path):
    source=tmp_path/'snapshot'
    source.mkdir()
    (source/'original.obj').write_bytes(b'coff data')
    os.link(source/'original.obj',source/'zzobj.obj')
    dest=tmp_path/'handoff'
    nm.copy_data_tree(source,dest,flatten_hardlinks=True)
    assert (dest/'original.obj').read_bytes()==(dest/'zzobj.obj').read_bytes()==b'coff data'
    assert (dest/'original.obj').stat().st_nlink==(dest/'zzobj.obj').stat().st_nlink==1
    with pytest.raises(nm.Refused,match='hardlinked'):
        nm.copy_data_tree(source,tmp_path/'publisher-copy')


def test_reused_snapshot_clang_cache_is_guarded_before_cycle(split,monkeypatch):
    r=split_run(split,'builder')
    r.commit=COMMIT
    r.snapshot().mkdir(parents=True)
    r.checkout.mkdir(parents=True)
    r.open_run_dir()
    caches=[]
    monkeypatch.setattr(nm,'clang_cache',lambda path:caches.append(path))
    monkeypatch.setattr(r,'prove_sources',lambda:None)
    monkeypatch.setattr(nm,'driver_overrides',lambda path:[])
    monkeypatch.setattr(nm.subprocess,'run',lambda *a,**kw:subprocess.CompletedProcess(a,0))
    r.step('cycle',r.python('-c','pass'))
    assert caches==[r.checkout,r.snapshot()]


def test_publisher_rejects_a_changed_protected_retail_baseline(split,monkeypatch):
    make_handoff(split)
    (split['install']/'retail.dat').write_bytes(b'substituted truth')
    with pytest.raises(nm.Refused,match='protected retail'):
        prepared_publisher(split,monkeypatch)


def test_publisher_rechecks_the_staged_bundle_before_each_use(split,monkeypatch):
    make_handoff(split)
    r=prepared_publisher(split,monkeypatch)
    (r.staged_tools/'image_ownership.py').write_text('print("planted")')
    with pytest.raises(nm.Refused,match='private checker copy changed'):
        r.prove_code('before publication')


@pytest.mark.parametrize('root',['.','..'])
def test_publisher_inventory_roots_allow_the_workspace_but_never_its_parent(split,monkeypatch,root):
    make_handoff(split)
    r=prepared_publisher(split,monkeypatch)
    nm.write_json(r.checkout/'build/match/a.deps.json',{'deps':{},'search_roots':[root]})
    if root=='.':
        r.check_artifact_paths()
    else:
        with pytest.raises(nm.Refused,match='unsafe'):
            r.check_artifact_paths()


# ---------------------------------------------------------------- round 5: commit binding and attestation

def binding_fixture(tmp_path):
    repo, git, _ = small_git_repo(tmp_path)
    (repo/'reverse').mkdir()
    (repo/'reverse/functions.csv').write_text('name,source\ngood,Code/safe.cpp\n')
    (repo/'.gitattributes').write_text('reverse/functions.csv text eol=lf\nbinary.dat -text\n')
    (repo/'binary.dat').write_bytes(b'a\r\nb\r\n')
    (repo/'.gitignore').write_text('build/\nhidden/\n')
    git('add','--','.gitattributes','.gitignore','reverse/functions.csv','binary.dat')
    git('commit','-qm','binding inputs')
    commit = git('rev-parse','HEAD')
    snapshot = tmp_path/'snapshot'
    nm.copy_data_tree(repo, snapshot)
    (snapshot/nm.SNAPSHOT_MARK).write_text('{}')
    r = object.__new__(nm.PublisherRun)
    r.dir = tmp_path/'private-index'
    r.dir.mkdir()
    r.checkout, r.snapshot_path = repo, snapshot
    return r, repo, snapshot, commit, git


@pytest.mark.parametrize('which', ['workspace','snapshot'])
@pytest.mark.parametrize('fault', ['ledger','attributes','missing','binary','same-stat'])
def test_commit_binding_refuses_forged_inputs_even_with_consistent_receipts(tmp_path,which,fault):
    r, repo, snapshot, commit, _ = binding_fixture(tmp_path)
    tree = repo if which=='workspace' else snapshot
    r.bind_tree(repo,tree,commit,snapshot=which=='snapshot')
    target = tree/'reverse/functions.csv'
    st = target.stat()
    if fault=='attributes':
        (tree/'.gitattributes').write_text('* -text\n')
    elif fault=='missing':
        target.unlink()
    elif fault=='binary':
        (tree/'binary.dat').write_bytes(b'a\nb\n')
    else:
        target.write_text('name,source\nevil,Code/safe.cpp\n') # Same byte length.
        if fault=='same-stat':
            os.utime(target,ns=(st.st_atime_ns,st.st_mtime_ns))
        nm.write_json(tree/'build/link_cycle/receipt.json',{'commit':commit,
            'functions_sha256':nm.sha256_bytes(target.read_bytes())})
    with pytest.raises(nm.Refused,match='tracked path differs'):
        r.bind_tree(repo,tree,commit,snapshot=which=='snapshot')


@pytest.mark.parametrize('extra', ['rogue.py','hidden/plugin.py','build/unknown/payload.py',
                                 'build/match/plugin.py','build/link_cycle/cache.pkl'])
def test_snapshot_rejects_untracked_and_ignored_extras(tmp_path,extra):
    r, repo, snapshot, commit, _ = binding_fixture(tmp_path)
    path = snapshot/extra
    path.parent.mkdir(parents=True,exist_ok=True)
    path.write_text('raise RuntimeError("must not import")')
    if extra.startswith('build/'):
        r.commit, r.approved = commit, {'submodule':commit}
        r.bind_tree = lambda *a,**kw: None
        with pytest.raises(nm.Refused,match='unexpected untracked'):
            r.bind_inputs()
    else:
        with pytest.raises(nm.Refused,match='unexpected untracked'):
            r.bind_tree(repo,snapshot,commit,snapshot=True)


def test_commit_binding_uses_pinned_attributes_and_accepts_expected_products(tmp_path,monkeypatch):
    r, repo, snapshot, commit, _ = binding_fixture(tmp_path)
    monkeypatch.setenv('GIT_ATTR_SOURCE','does-not-exist')
    monkeypatch.setenv('GIT_INDEX_FILE',str(tmp_path/'hostile-index'))
    calls = []
    real_git = nm.git
    def query(*a,**kw):
        calls.append(kw['env'])
        return real_git(*a,**kw)
    monkeypatch.setattr(nm,'git',query)
    (snapshot/'build/match').mkdir(parents=True)
    (snapshot/'build/match/unit.obj').write_bytes(b'object')
    (snapshot/'build/link_cycle').mkdir()
    (snapshot/'build/link_cycle/imp_test.exp').write_bytes(b'import export file')
    for tree in (repo,snapshot):
        r.bind_tree(repo,tree,commit,snapshot=tree==snapshot)
    assert not list(r.dir.glob('*.index'))
    assert not (tmp_path/'hostile-index').exists()
    assert all(env['GIT_ATTR_SOURCE']==commit for env in calls)
    assert len({env['GIT_INDEX_FILE'] for env in calls})==2


def test_commit_binding_refuses_unchecked_nested_gitlinks(tmp_path):
    r,repo,snapshot,commit,git = binding_fixture(tmp_path)
    git('update-index','--add','--cacheinfo',f'160000,{commit},unreviewed-submodule')
    git('commit','-qm','unreviewed gitlink')
    with pytest.raises(nm.Refused,match='unvalidated submodule'):
        r.bind_tree(repo,repo,git('rev-parse','HEAD'))


def test_prepare_binds_original_inputs_before_replacing_tools_or_scanning_sources(split,monkeypatch):
    source = make_handoff(split)
    retail = 'workspace/baselines/bfme2/workshop-vanilla-1.06/files/game.dat'
    (source/retail).parent.mkdir(parents=True)
    (source/retail).write_bytes(b'forged builder baseline')
    meta = nm.read_json(source/'handoff.json')
    meta['files'][retail] = nm.sha256_bytes((source/retail).read_bytes())
    nm.write_json(source/'handoff.json',meta)
    nm.write_json(split['handoff']/'latest.json',{'id':source.name,
        'sha256':nm.sha256_bytes((source/'handoff.json').read_bytes())})
    r = split_run(split,'publisher')
    r.open_run_dir()
    events = []
    def preflight():
        r.policy = split['policy']
        r.load_approval()
    monkeypatch.setattr(r,'preflight',preflight)
    monkeypatch.setattr(r,'private_git',lambda *a:events.append('fetch:'+a[-1]))
    monkeypatch.setattr(r,'step',lambda *a,**kw:None)
    monkeypatch.setattr(nm,'identity',lambda *a:dict(IDENT))
    def binding():
        assert (r.checkout/'tools/evil.py').read_text()=='untrusted'
        assert (r.checkout/retail.removeprefix('workspace/')).read_bytes()==b'forged builder baseline'
        events.append('bind')
        raise nm.Refused('tracked path differs from approved commit')
    monkeypatch.setattr(r,'bind_inputs',binding)
    monkeypatch.setattr(r,'prove_sources',lambda:pytest.fail('used source before binding'))
    with pytest.raises(nm.Refused,match='tracked path differs'):
        r.prepare()
    assert events==['fetch:workspace','fetch:bfme1','bind']


def test_bind_inputs_checks_workspace_snapshot_and_pinned_submodule(split,monkeypatch):
    make_handoff(split)
    r = prepared_publisher(split,monkeypatch)
    seen = []
    r.bind_tree = lambda *a,**kw:seen.append((a,kw))
    nm.PublisherRun.bind_inputs(r)
    assert [(a[0],a[1],a[2],kw['snapshot']) for a,kw in seen]==[
        (r.checkout,r.checkout,r.commit,False),
        (r.checkout/nm.SUBMODULE,r.checkout/nm.SUBMODULE,r.approved['submodule'],False),
        (r.checkout,r.snapshot_path,r.commit,True),
        (r.checkout/nm.SUBMODULE,r.snapshot_path/nm.SUBMODULE,r.approved['submodule'],True)]


@pytest.mark.parametrize('missing',['image_ownership.py','data_back_rank.py'])
def test_missing_landing_dependency_is_explicit(split,missing):
    r = split_run(split,'publisher')
    assert 'after the north-star commit' in nm.__doc__ and 'agent-a0b594' in nm.__doc__
    r.load_approval()
    del r.approved['checker_files'][missing]
    with pytest.raises(nm.Refused,match='north-star commit.*agent-a0b594' if missing=='image_ownership.py'
                       else 'checker bundle is missing'):
        r.verify_bundle()


def test_setup_document_names_the_publisher_and_isolation_prerequisites():
    doc = (TOOLS.parent/'docs/nightly_setup.md').read_text()
    assert "$publisherProfile = 'C:\\Users\\Jonathan'" in doc
    assert '$env:USERPROFILE' not in doc and '$env:APPDATA' not in doc and '$env:LOCALAPPDATA' not in doc
    assert 'default profile ACLs plus the runner' in doc
    assert 'protected\nACLs' in doc
    assert 'numpy machine-wide' in doc and '-I' in doc
    assert 'after the north-star commit' in doc
    assert 'report_sha256' in doc and 'builder-attested' in doc


@pytest.fixture
def real_rank(split,monkeypatch):
    make_handoff(split)
    r = prepared_publisher(split,monkeypatch)
    # Actual pinned source in a disposable bundle, rather than a fake ranker.
    shutil = __import__('shutil')
    for p in TOOLS.glob('*.py'):
        shutil.copyfile(p,r.staged_tools/p.name)
    r.approved['checker_files'] = nm.tree_hashes(r.staged_tools)
    monkeypatch.setattr(r,'prove_code',lambda when:None)
    run, base = r.cycle_dir(),r.snapshot_path
    (base/'reverse').mkdir()
    (base/'reverse/data_ledger.csv').write_text('address,size,section,kind,name,source,status,names,defs,refs\n')
    (base/'reverse/functions.csv').write_text('name,source\n')
    (base/'reverse/exports.csv').write_text('name,rva\n')
    (run/'link_status.csv').write_text(','.join(__import__('data_back_rank').STATUS_COLUMNS)+'\n')
    (run/'data_fold_list.csv').write_text('address,verdict\n')
    commands = []
    def step(name,argv,**kw):
        commands.append((name,argv,kw))
        result = subprocess.run(list(map(str,argv)),cwd=kw['cwd'],capture_output=True)
        assert result.returncode==0, result.stderr.decode(errors='replace')
        (r.dir/'rank.log').write_bytes(result.stdout)
    monkeypatch.setattr(r,'step',step)
    bundle = r.dir/'frozen/bundle'
    args = ['--status','link_status.csv','--folds','data_fold_list.csv',
            '--ledger',str(base/'reverse/data_ledger.csv'),'--functions',str(base/'reverse/functions.csv'),
            '--exports',str(base/'reverse/exports.csv'),'--no-objects','--json',str(bundle/'data_back_rank.json')]
    result = subprocess.run([sys.executable,'-I','-c',nm.SCRIPT_BOOT,str(r.staged_tools),
                             str(r.staged_tools/'data_back_rank.py'),*args],cwd=run,capture_output=True)
    assert result.returncode==0,result.stderr
    (bundle/'data_back_rank.txt').write_bytes(result.stdout.replace(b'\r\n',b'\n'))
    return r,bundle,commands


@pytest.mark.parametrize('fault',['none','txt','json'])
def test_publisher_recomputes_rank_and_rejects_each_forged_report(real_rank,fault):
    r,bundle,commands = real_rank
    if fault!='none':
        path = bundle/('data_back_rank.'+fault)
        path.write_text('{}' if fault=='json' else 'forged ranking')
    if fault=='none':
        r.recompute_rank(bundle)
        for name in ('data_back_rank.txt','data_back_rank.json'):
            assert (r.cycle_dir()/name).read_bytes()==(bundle/name).read_bytes()
    else:
        with pytest.raises(nm.Refused,match='recomputed data_back_rank.'+fault+' differs'):
            r.recompute_rank(bundle)
        assert not (r.cycle_dir()/'data_back_rank.txt').exists()
    assert commands[0][0]=='rank'
    assert Path(commands[0][1][commands[0][1].index(nm.SCRIPT_BOOT)+2]).parent==r.staged_tools
    assert commands[0][2]['cwd']==r.cycle_dir()


def test_rank_cache_is_fresh_and_publisher_private_not_builder_pickle(split,monkeypatch):
    make_handoff(split)
    r = prepared_publisher(split,monkeypatch)
    (r.snapshot_path/'build/match').mkdir()
    malicious = r.snapshot_path/'build/match/rank_objects.pkl'
    malicious.write_bytes(b'not a trusted cache')
    calls = []
    def step(name,argv,**kw):
        calls.append(argv)
        fake_rank_outputs(r)
    monkeypatch.setattr(r,'step',step)
    r.recompute_rank(r.dir/'frozen/bundle')
    args = calls[0]
    cache = Path(args[args.index('--cache')+1])
    assert cache==r.dir/'rank_objects.pkl' and cache.is_relative_to(r.work)
    assert not cache.exists() and malicious.read_bytes()==b'not a trusted cache'
    assert args[args.index('--objects')+1]=='../match'


def test_cycle_release_notes_are_qualified_in_the_actual_publisher_entrypoint(tmp_path):
    tools = tmp_path/'checkers'
    tools.mkdir()
    notes = tmp_path/'notes.txt'
    (tools/'publish_cycle.py').write_text(
        'from pathlib import Path\n'
        'def release_notes(manifest): return "credit: 123\\n"\n'
        'def main(argv):\n'
        '    assert argv[0]=="publish"\n'
        '    Path(argv[1]).write_text(release_notes({}))\n'
        '    return 0\n')
    result = subprocess.run([sys.executable,'-I','-c',nm.PUBLISHER_PUBLISH,str(tools),'publish',str(notes)],
                            cwd=tmp_path,capture_output=True,text=True)
    assert result.returncode==0,result.stderr
    assert notes.read_text()==nm.BUILDER_ATTESTATION+'\n\ncredit: 123\n'


def test_publisher_tool_routes_publication_through_qualified_notes(split,monkeypatch):
    make_handoff(split)
    r = prepared_publisher(split,monkeypatch)
    argv = r.tool('tools/publish_cycle.py','publish','bundle')
    assert nm.PUBLISHER_PUBLISH in argv and nm.SCRIPT_BOOT not in argv


def test_ownership_attestation_is_bound_by_the_existing_signed_report_hash(tmp_path):
    own, _ = ownership_fixture()
    report = tmp_path/'relayout.json'
    report.write_text(json.dumps({'measurement_attestation':{
        'schema':1,'basis':'builder-attested','statement':nm.BUILDER_ATTESTATION}}))
    receipt = {'totals':{'ours_by_lane':{},'bridged':1,'unproven':1,'ours':1,'linker':1,'filler':1},
               'sections':{},'measured_utc':'2026-10-24 01:00:00','rules':own.RULES,
               'report':{'mode':'relayout','sha256':nm.sha256_bytes(report.read_bytes())},
               'image_bytes':5,'content_bytes':3,'north_star':2,
               'image':{'sha256':'a'*64},'map':{'sha256':'b'*64},'retail':{'sha256':'c'*64},
               'tools_sha256':'d'*64}
    prov = {'built_utc':'2026-10-24 01:00:00','commit':'e'*40,'ledger_sha256':'f'*64,
            'objects':{'digest':'1'*64},'inputs_end':'2'*64,'build_tools_sha256':'3'*64}
    row = own.history_row(receipt,prov)
    message = own.row_message(row)
    assert row['report_sha256'] in message.decode()
    doc = json.loads(report.read_text())
    doc['measurement_attestation']['basis'] = 'publisher-relinked'
    report.write_text(json.dumps(doc))
    row['report_sha256'] = nm.sha256_bytes(report.read_bytes())
    assert own.row_message(row)!=message


def test_ownership_release_labels_attestation_and_includes_the_bound_report(split,monkeypatch):
    make_handoff(split)
    r = prepared_publisher(split,monkeypatch)
    calls = []
    monkeypatch.setattr(nm,'wait_cooldown',lambda *a:None)
    monkeypatch.setattr(nm,'stamp_clock',lambda *a:None)
    monkeypatch.setattr(nm.subprocess,'run',lambda argv,**kw:calls.append(argv) or
                        subprocess.CompletedProcess(argv,0,'',''))
    r.publish_ownership('cycle-test')
    argv = calls[0]
    assert nm.BUILDER_ATTESTATION in argv[argv.index('--notes')+1]
    assert str(r.report) in argv


def test_publisher_rank_script_allowlist_retains_isolated_native_cwd(split,monkeypatch):
    make_handoff(split)
    r = prepared_publisher(split,monkeypatch)
    calls = []
    monkeypatch.setattr(nm.Run,'step',lambda self,name,argv,**kw:calls.append((argv,kw)) or {})
    nm.PublisherRun.step(r,'rank',r.tool('tools/data_back_rank.py','--status','link_status.csv'),cwd=r.cycle_dir())
    argv,kw = calls[0]
    assert kw['cwd']==r.work/'native-cwd'
    assert nm.PUBLISHER_GUARD in argv[argv.index('-c')+1]
    assert 'os.chdir('+repr(str(r.cycle_dir()))+')' in argv[argv.index('-c')+1]
