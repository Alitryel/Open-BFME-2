"""rename.py runs the pre-commit hook's path-sensitive checks (class_gate,
ledger_guard, code_identity_gate, link_debt, check_case_collisions,
hatch_counters, data_check, eh_verify, and with a ledger file pin_admission,
pin_consistency, name_dependents) against what the commit will contain, so a
plan that passes check_csv but would fail at commit is refused by the rename
and rolled back byte for byte. conversion_gate, tu_ownership, invented_names,
header_dependents and the baseline shrink-only assertions are not run: a
rename cannot change what they judge.

A miniature git tree. ledger_guard is the real tool (standard library only);
the other three are small stand-ins with the hook's contract (`--staged`: read
the index, exit 1 to refuse, name_dependents lists units on stdout), which is
what shows the checks see the private index and never the real one.
test_hook_drift.. reads .githooks/pre-commit itself, so a hook change that
this module's jobs do not follow fails here."""
import os
import re
import shlex
import shutil
import signal
import subprocess
import sys
import threading
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

OLD = "?Rva00401000@Widget@@QAEHH@Z"
NEW = "?countParts@Widget@@QAEHH@Z"
UNIT = "Code/Game/Widget.cpp"

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
{OLD},,0x00401000,40,{UNIT},matched,address-derived
?caller@Gadget@@QAEXXZ,,0x00402000,20,Code/Game/Gadget.cpp,matched,calls {OLD}
"""
SYMBOLS = f"name,address,notes\n{OLD},0x00401000,pin\n"
WIDGET = "// cl: /O2\nint Widget::Rva00401000(int n) { return n; }\n"
GADGET = "void Gadget::caller() {}\n"

# pin_admission stand-in: refuse when the INDEX holds two names at one address.
PIN_ADMISSION = '''import subprocess, sys
text = subprocess.run(["git", "show", ":reverse/symbols.csv"], capture_output=True, text=True).stdout
seen = {}
for line in text.splitlines()[1:]:
    name, address = line.split(",")[:2]
    seen.setdefault(address, set()).add(name)
bad = [a for a, names in seen.items() if len(names) > 1]
if bad:
    print("pin admission: FAIL 1\\n  second real name at " + bad[0])
    sys.exit(1)
print("pin admission: OK")
'''
# class_gate stand-in: refuse a staged unit that mentions `ForbiddenView`.
CLASS_GATE = '''import subprocess, sys
for path in subprocess.run(["git", "diff", "--cached", "--name-only"], capture_output=True, text=True).stdout.split():
    if path.endswith(".cpp") and "ForbiddenView" in subprocess.run(["git", "show", ":" + path],
                                                                   capture_output=True, text=True).stdout:
        print("  " + path + ": declares its own `ForbiddenView`", file=sys.stderr)
        sys.exit(1)
'''
# name_dependents stand-in: the plan removed a name that Gadget.cpp calls.
NAME_DEPENDENTS = '''print("Code/Game/Gadget.cpp")\n'''


def git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True, text=True).stdout


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/symbols.csv": SYMBOLS,
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        UNIT: WIDGET,
        "Code/Game/Gadget.cpp": GADGET,
        "tools/pin_admission.py": PIN_ADMISSION,
        "tools/class_gate.py": CLASS_GATE,
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    shutil.copy(TOOLS / "ledger_guard.py", tmp_path / "tools" / "ledger_guard.py")
    git(tmp_path, "init", "-q")
    git(tmp_path, "add", "-A")
    git(tmp_path, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "base")
    return tmp_path


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def snapshot(root):
    return {p.relative_to(root).as_posix(): p.read_bytes()
            for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}


def plan_of(root, **edits):
    ctx = ctx_of(root)
    plan = rename.Plan("function", OLD, NEW, "inferred", "", UNIT, 0x00401000, verify=[UNIT])
    for rel, data in edits.items():
        plan.edit(ctx, rel.replace("__", "/").replace("_csv", ".csv").replace("_cpp", ".cpp"), data)
    return plan


def renamed_functions():
    return FUNCTIONS.replace(OLD, NEW).encode()


def apply(root, plan, verify=lambda ctx, sources: True):
    return rename.apply_rename(plan, ctx=ctx_of(root), verify=verify, checks=rename.ledger_checks)


def real_index(root):
    return (root / ".git" / "index").read_bytes()


def test_clean_plan_passes_and_leaves_the_real_index_alone(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    plan.edit(ctx_of(tree), "reverse/symbols.csv", SYMBOLS.replace(OLD, NEW).encode())
    index = real_index(tree)
    apply(tree, plan)
    assert (tree / "reverse/functions.csv").read_bytes() == renamed_functions()
    assert real_index(tree) == index and git(tree, "diff", "--cached", "--name-only") == ""


def test_plan_pin_admission_would_refuse_is_refused_and_rolled_back(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    plan.edit(ctx_of(tree), "reverse/symbols.csv", (SYMBOLS + f"{NEW},0x00401000,alias pin\n").encode())
    before, index = snapshot(tree), real_index(tree)
    with pytest.raises(VerifyFailed, match=r"\[pin_admission\].*second real name"):
        apply(tree, plan)
    assert snapshot(tree) == before and real_index(tree) == index
    assert not rename.journals(ctx_of(tree))


def test_pin_admission_judges_the_plan_not_the_working_tree_alone(tree):
    """The same clashing pin edited into the tree by hand, outside the plan,
    is not what the commit will contain: it is unstaged, so not judged here
    (ledger_guard names it instead)."""
    (tree / "reverse/symbols.csv").write_bytes((SYMBOLS + f"{NEW},0x00401000,alias pin\n").encode())
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    with pytest.raises(VerifyFailed) as refused:
        apply(tree, plan)
    assert str(refused.value).split("[")[1].startswith("ledger_guard]")


def test_class_gate_refusal_is_reported_by_name(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), UNIT, (WIDGET + "struct ForbiddenView { int x; };\n").encode())
    before = snapshot(tree)
    with pytest.raises(VerifyFailed, match=r"\[class_gate\]"):
        apply(tree, plan)
    assert snapshot(tree) == before


def test_ledger_guard_refuses_a_ledger_edited_outside_the_plan(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    (tree / "reverse/data_rows.csv").write_bytes(b"name,address\nx,1\n")      # someone else's edit
    with pytest.raises(VerifyFailed, match=r"\[ledger_guard\]"):
        apply(tree, plan)


def test_every_refusing_check_is_named(tree):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    plan.edit(ctx_of(tree), "reverse/symbols.csv", (SYMBOLS + f"{NEW},0x00401000,alias pin\n").encode())
    plan.edit(ctx_of(tree), UNIT, (WIDGET + "struct ForbiddenView { int x; };\n").encode())
    with pytest.raises(VerifyFailed, match=r"\[class_gate, pin_admission\]|\[pin_admission, class_gate\]"):
        apply(tree, plan)


def stand_in_name_dependents(tree):
    (tree / "tools/name_dependents.py").write_text(NAME_DEPENDENTS)
    git(tree, "add", "tools/name_dependents.py")
    git(tree, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", "stand-in")


def test_name_dependents_units_are_built_before_success(tree, monkeypatch):
    stand_in_name_dependents(tree)
    built = []
    fake = lambda ctx, sources, cancel=None: built.append(list(sources)) or True      # noqa: E731
    monkeypatch.setattr(rename, "build_verify", fake)
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    apply(tree, plan, verify=fake)
    assert built == [[UNIT], ["Code/Game/Gadget.cpp"]]


def test_a_failing_name_dependent_build_refuses_and_restores(tree, monkeypatch):
    stand_in_name_dependents(tree)
    fake = lambda ctx, sources, cancel=None: sources == [UNIT]                         # noqa: E731
    monkeypatch.setattr(rename, "build_verify", fake)
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    before = snapshot(tree)
    with pytest.raises(VerifyFailed, match=r"\[name_dependents\]"):
        apply(tree, plan, verify=fake)
    assert snapshot(tree) == before and not rename.journals(ctx_of(tree))


def test_a_unit_the_plan_already_verifies_is_not_built_twice(tree, monkeypatch):
    stand_in_name_dependents(tree)
    built = []
    fake = lambda ctx, sources, cancel=None: built.append(list(sources)) or True      # noqa: E731
    monkeypatch.setattr(rename, "build_verify", fake)
    plan = plan_of(tree)
    plan.verify = [UNIT, "Code/Game/Gadget.cpp"]
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    apply(tree, plan, verify=fake)
    assert built == [[UNIT, "Code/Game/Gadget.cpp"]]


def test_the_pre_rename_call_runs_nothing(tree):
    (tree / "tools/pin_admission.py").write_text("raise SystemExit('always refuses')\n")
    assert rename.commit_checks(ctx_of(tree), rename.Plan("function", "a", "b", "x", "", None, None)) == []


def test_staged_index_is_private(tree):
    index = real_index(tree)
    (tree / "reverse/symbols.csv").write_bytes(b"name,address,notes\n")
    with rename.staged_index(ctx_of(tree), ["reverse/symbols.csv"]) as env:
        staged = subprocess.run(["git", "-C", str(tree), "diff", "--cached", "--name-only"], env=env,
                                capture_output=True, text=True).stdout
    assert staged.split() == ["reverse/symbols.csv"]
    assert real_index(tree) == index and git(tree, "diff", "--cached", "--name-only") == ""


def test_a_tree_that_is_no_repository_is_not_judged(tmp_path):
    (tmp_path / "tools").mkdir()
    (tmp_path / "tools/class_gate.py").write_text("raise SystemExit(1)\n")
    plan = rename.Plan("function", "a", "b", "x", "", None, None)
    plan.after["reverse/functions.csv"] = b"x"
    assert rename.commit_checks(ctx_of(tmp_path), plan) == []


# ------------------------------------------------ the rest of the hook's checks

def stand_in(tree, name, text):
    (tree / "tools").mkdir(exist_ok=True)
    (tree / f"tools/{name}.py").write_text(text)


# code_identity_gate / pin_consistency stand-ins: refuse when the INDEX holds the marker
INDEX_MARKER = '''import subprocess, sys
text = subprocess.run(["git", "show", ":reverse/symbols.csv"], capture_output=True, text=True).stdout
if "BAD" in text:
    print("%s: FAIL 1" % sys.argv[0])
    sys.exit(1)
'''


def renamed_plan(tree, symbols=None):
    plan = plan_of(tree)
    plan.edit(ctx_of(tree), "reverse/functions.csv", renamed_functions())
    if symbols is not None:
        plan.edit(ctx_of(tree), "reverse/symbols.csv", symbols.encode())
    return plan


def test_code_identity_gate_and_pin_consistency_are_run_and_named(tree):
    stand_in(tree, "code_identity_gate", INDEX_MARKER)
    stand_in(tree, "pin_consistency", INDEX_MARKER.replace("sys.argv[0]", "'pins'"))
    plan = renamed_plan(tree, SYMBOLS.replace(OLD, NEW) + "BAD,0x00999000,x\n")
    with pytest.raises(VerifyFailed, match=r"\[code_identity_gate, pin_consistency\]"):
        apply(tree, plan)


def test_pin_consistency_runs_only_when_a_ledger_file_is_written(tree):
    stand_in(tree, "pin_consistency", "raise SystemExit('always refuses')\n")
    plan = rename.Plan("function", "a", "b", "x", "", UNIT, None)
    plan.edit(ctx_of(tree), UNIT, (WIDGET + "// edit\n").encode())
    assert rename.commit_checks(ctx_of(tree), plan) == []
    plan.edit(ctx_of(tree), "reverse/symbols.csv", SYMBOLS.encode() + b"x,0x1,y\n")
    assert rename.commit_checks(ctx_of(tree), plan)[0].startswith("pin_consistency:")


def test_a_missing_hook_tool_fails_in_the_repository_and_is_skipped_in_a_fixture(tree, monkeypatch):
    plan = renamed_plan(tree)
    ctx = ctx_of(tree)
    assert rename.commit_checks(ctx, plan) == []                       # a fixture lacks the tools
    monkeypatch.setattr(rename, "ROOT", tree)                          # now it is "the repository"
    problems = rename.commit_checks(ctx, plan)
    missing = {p.split(":")[0] for p in problems}
    assert {"code_identity_gate", "link_debt", "hatch_counters", "data_check"} <= missing
    assert "class_gate" not in missing and "ledger_guard" not in missing        # present in the fixture
    assert all("is missing" in p for p in problems)
    assert rename.commit_checks(ctx, plan, missing_ok=True) == []
    assert not any(p.startswith("link_debt") for p in rename.commit_checks(ctx, plan, skip=("link_debt",)))


def test_a_moved_unit_is_judged_at_its_new_path(tree):
    new = "Code/Game/Gadget2.cpp"
    plan = plan_of(tree)
    plan.moves.append(("Code/Game/Gadget.cpp", new))
    plan.moved_bytes["Code/Game/Gadget.cpp"] = GADGET.encode()
    plan.before["Code/Game/Gadget.cpp"] = GADGET.encode()
    plan.after[new] = (GADGET + "struct ForbiddenView { int x; };\n").encode()
    before = snapshot(tree)
    with pytest.raises(VerifyFailed, match=r"\[class_gate\].*Gadget2.cpp"):
        apply(tree, plan)
    assert snapshot(tree) == before and git(tree, "diff", "--cached", "--name-only") == ""


def test_cancelling_kills_the_running_tool_at_once(tree):
    stand_in(tree, "code_identity_gate", "import time\ntime.sleep(60)\n")
    cancel = threading.Event()
    threading.Timer(0.5, cancel.set).start()
    started = time.time()
    assert rename.commit_checks(ctx_of(tree), renamed_plan(tree), cancel=cancel) == []
    assert time.time() - started < 10


def test_a_signal_in_the_main_thread_does_not_wait_for_the_tools(tree, monkeypatch):
    stand_in(tree, "code_identity_gate", "import time\ntime.sleep(60)\n")

    def interrupted(ctx, plan):
        time.sleep(0.5)
        raise KeyboardInterrupt
    monkeypatch.setattr(rename, "_csv_checks", interrupted)
    started = time.time()
    with pytest.raises(KeyboardInterrupt):
        rename.ledger_checks(ctx_of(tree), renamed_plan(tree))
    assert time.time() - started < 5


def alive(pid):
    try:
        os.kill(pid, 0)
    except ProcessLookupError:
        return False
    return True


def wait_gone(pid, seconds=5):
    deadline = time.time() + seconds
    while alive(pid) and time.time() < deadline:
        time.sleep(0.1)
    return not alive(pid)


def sleeper(tree, name):
    """Make tool `name` a stand-in that records its pid and sleeps."""
    stand_in(tree, name, "import os, time\nopen(os.environ.get('PIDFILE') or "
             f"{str(tree / 'pid')!r}, 'w').write(str(os.getpid()))\ntime.sleep(60)\n")


def test_a_signal_while_waiting_for_the_hook_tools_cancels_them(tree, monkeypatch):
    # check_csv is done (nothing to wait for); the slow tool is still running
    sleeper(tree, "code_identity_gate")
    monkeypatch.setattr(rename, "_csv_checks", lambda ctx, plan: [])
    # a real signal: it wakes the main thread out of the wait, which interrupt_main does not
    threading.Timer(1.5, signal.pthread_kill, (threading.main_thread().ident, signal.SIGINT)).start()
    started = time.time()
    with pytest.raises(KeyboardInterrupt):
        rename.ledger_checks(ctx_of(tree), renamed_plan(tree))
    assert time.time() - started < 6
    pid = int((tree / "pid").read_text())
    assert wait_gone(pid), "the hook tool outlived the interrupted ledger_checks"


def test_cancelling_kills_the_name_dependents_build(tree):
    # the extra unit's ./build.sh (and what it started) stops with the cancel
    stand_in_name_dependents(tree)
    (tree / "build.sh").write_text("#!/bin/sh\nsleep 60 &\necho $! > pid\necho $$ > started\nwait\n")
    (tree / "build.sh").chmod(0o755)
    cancel = threading.Event()

    def watch():
        while not (tree / "started").exists():
            time.sleep(0.05)
        cancel.set()
    threading.Thread(target=watch, daemon=True).start()
    started = time.time()
    assert rename.commit_checks(ctx_of(tree), renamed_plan(tree), cancel=cancel) == []
    assert time.time() - started < 15
    assert wait_gone(int((tree / "pid").read_text())), "the build's child outlived the cancel"


# --------------------------------------------- the hook and these jobs say the same

HOOK = TOOLS.parent / ".githooks" / "pre-commit"


def hook_invocations():
    """{tool: [argument tokens of each `python3 tools/<tool>.py ...` in the hook,
    shell variables left out]}."""
    text = HOOK.read_text().replace("\\\n", " ")
    found = {}
    for line in text.splitlines():
        for match in re.finditer(r"python3 tools/(\w+)\.py((?:[^|&;<>)]|\|(?!\|))*)", line):
            tokens = shlex.split(match.group(2), comments=True)
            found.setdefault(match.group(1), []).append([t for t in tokens if "$" not in t])
    return found


def test_every_commit_check_is_a_command_the_hook_runs_with_the_same_arguments(tree):
    ctx = ctx_of(tree)
    plan = rename.Plan("function", OLD, NEW, "inferred", "", UNIT, 0x00401000, verify=[UNIT])
    paths = sorted(set(rename.COMMIT_LEDGER_FILES) | set(rename.NAME_LEDGER_FILES) | {UNIT})
    jobs = rename._hook_jobs(ctx, plan, paths)
    assert set(jobs) >= {"class_gate", "ledger_guard", "code_identity_gate", "link_debt", "check_case_collisions",
                         "hatch_counters", "data_check", "pin_admission", "pin_consistency", "name_dependents",
                         "data_converged", "eh_verify"}
    hook = hook_invocations()
    for label, (tool, args, _stdin) in jobs.items():
        mine = [a for a in args if "{" not in a]
        assert mine in hook.get(tool, []), \
            f"{label}: .githooks/pre-commit never runs tools/{tool}.py {' '.join(mine)}; hook has {hook.get(tool)}"


def test_the_ledger_files_that_switch_on_the_ledger_checks_are_the_hooks():
    text = HOOK.read_text()
    cases = {tuple(m.split("|")) for m in re.findall(r"^\s*((?:reverse/[\w./]+\|)+reverse/[\w./]+)\) ledger_changed=1",
                                                      text, re.M)}
    assert cases == {tuple(rename.COMMIT_LEDGER_FILES)}, cases
