"""`rename.py carry`: a renamed-away spelling left in a functions.csv notes token
(a funclet's `parent=`, `icf-owner=`, ...) is respelled where the live ledger
proves it. Miniature git trees with small ledgers; verification is injected."""
import multiprocessing
import os
import signal
import subprocess
import sys
import time
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import ledger_io  # noqa: E402
import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402

OK = lambda ctx, sources: True  # noqa: E731

OLD = "?Rva00401000@Widget@@QAEHH@Z"
NEW = "?countParts@Widget@@QAEHH@Z"
MID = "?midName@Widget@@QAEHH@Z"
OLD2 = "?Rva00403000@Widget@@QAEHXZ"
NEW2 = "?count@Widget@@QAEHXZ"
UNIT = "Code/Game/Widget.cpp"

HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"
BASE_ROWS = [
    f"{NEW},,0x00401000,40,{UNIT},matched,real name",
    f"__ehhandler${NEW},,0x00790000,10,{UNIT},matched,gen-ehstub",
    f"Unwind@1,,0x00790010,8,{UNIT},matched,gen-funclet;parent={OLD};object-symbol=$L100",
    f'Unwind@2,,0x00790018,8,{UNIT},matched,"gen-funclet;parent={OLD};object-symbol=$L101;why, because"',
    f"?other@Gadget@@QAEXXZ,,0x00402000,20,Code/Game/Gadget.cpp,matched,icf-owner={OLD};see {OLD} in prose",
    "?unrelated@@YAXXZ,,0x00404000,6,Code/Game/Free.cpp,matched,vendored=zlib-1.1.4",
]
BASIS_HEADER = rename.NAME_BASIS_HEADER + "\n"
BASIS = f"function,{OLD},{NEW},inferred,agree:x,{UNIT},0x00401000\n"


def functions(*rows):
    return HEADER + "".join(r + "\n" for r in rows)


def _git(root, *args):
    subprocess.run(["git", "-C", str(root), "-c", "user.name=t", "-c", "user.email=t@t", *args],
                   check=True, capture_output=True)


def make_tree(tmp_path, rows=None, basis=BASIS, symbols="", data="", extra=None):
    files = {
        "reverse/functions.csv": functions(*(BASE_ROWS if rows is None else rows)),
        "reverse/symbols.csv": "name,address,notes\n" + symbols,
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n" + data,
        "reverse/body_owners.csv": "name,source\n",
        "reverse/name_basis.csv": BASIS_HEADER + basis,
        UNIT: "// cl: /O2\nclass Widget { public: int countParts(int n); };\n",
        "Code/Game/Gadget.cpp": "void gadget() {}\n",
        "Code/Game/Free.cpp": "void free() {}\n",
    }
    files.update(extra or {})
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    return tmp_path


@pytest.fixture
def tree(tmp_path):
    return make_tree(tmp_path)


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def snapshot(root):
    return {p.relative_to(root).as_posix(): p.read_bytes()
            for p in root.rglob("*") if p.is_file() and ".git" not in p.parts
            and p.name != ".add_match.lock"}


def lines_of(root):
    return (root / rename.FUNCTIONS).read_text().splitlines()


def carry(root, **kwargs):
    return rename.plan_carry(ctx_of(root), **kwargs)


def reasons(refusals):
    return " | ".join(why for _label, why in refusals)


# ------------------------------------------------------------ the basic case

def test_a_stale_parent_is_carried_and_nothing_else_moves(tree):
    before = snapshot(tree)
    plan, refusals = carry(tree)
    assert refusals == []
    assert list(plan.after) == [rename.FUNCTIONS]
    assert plan.spellings == [(OLD, NEW, 4)]
    assert plan.verify == ["Code/Game/Gadget.cpp", UNIT]
    assert plan.subject() == "Carry 1 renamed spelling(s) into ledger notes"
    assert snapshot(tree) == before                       # planning writes nothing

    rename.apply_rename(plan, ctx=ctx_of(tree), verify=OK, checks=None)
    after = snapshot(tree)
    assert {rel for rel in after if after[rel] != before[rel]} == {rename.FUNCTIONS}
    old_lines, new_lines = before[rename.FUNCTIONS].decode().splitlines(), lines_of(tree)
    assert len(old_lines) == len(new_lines)
    changed = [i for i, (a, b) in enumerate(zip(old_lines, new_lines)) if a != b]
    assert changed == [3, 4, 5]
    for i in changed:           # only the notes field changed: the first six fields are byte-identical
        a, b = ledger_io.fields(old_lines[i].encode()), ledger_io.fields(new_lines[i].encode())
        assert a[:6] == b[:6] and OLD in a[6] and OLD not in b[6] and NEW in b[6]
    assert new_lines[3] == f"Unwind@1,,0x00790010,8,{UNIT},matched,gen-funclet;parent={NEW};object-symbol=$L100"
    assert new_lines[4].endswith(f'"gen-funclet;parent={NEW};object-symbol=$L101;why, because"')
    assert new_lines[5].endswith(f"icf-owner={NEW};see {NEW} in prose")
    assert rename.check_renames(ctx_of(tree), rename.name_basis_rows(ctx_of(tree))) == []
    assert not rename.journals(ctx_of(tree))
    assert carry(tree) == (None, [])                     # idempotent


def test_dry_run_prints_the_plan_and_writes_nothing(tree, capsys):
    before = snapshot(tree)
    code = rename.main(["carry", "--all", "--dry-run", "--no-claim", "--root", str(tree)])
    out = capsys.readouterr().out
    assert code == 0
    assert f"{OLD} -> {NEW} (x4)" in out and "nothing written" in out
    assert "suggested subject: Carry 1 renamed spelling(s) into ledger notes" in out
    assert snapshot(tree) == before


def test_check_points_at_carry(tree, capsys):
    code = rename.main(["check", "--all", "--root", str(tree)])
    err = capsys.readouterr().err
    assert code == 1
    assert "python3 tools/rename.py carry --all" in err


def test_check_does_not_point_at_carry_for_a_pin(tmp_path, capsys):
    root = make_tree(tmp_path, rows=BASE_ROWS[:2], symbols=f"{OLD},0x00401000,stale pin\n")
    code = rename.main(["check", "--all", "--root", str(root)])
    assert code == 1
    assert "rename.py carry" not in capsys.readouterr().err


# ------------------------------------------------------------ replay

def test_a_chain_carries_the_first_spelling_to_the_last(tmp_path):
    basis = (f"function,{OLD},{MID},inferred,agree:x,{UNIT},0x00401000\n"
             f"function,{MID},{NEW},canonical:wb,w,{UNIT},0x00401000\n")
    root = make_tree(tmp_path, rows=BASE_ROWS[:3] + [f"Unwind@3,,0x00790020,8,{UNIT},matched,"
                                                    f"gen-funclet;parent={MID};object-symbol=$L102"], basis=basis)
    plan, refusals = carry(root)
    assert refusals == []
    assert sorted(plan.spellings) == sorted([(OLD, NEW, 1), (MID, NEW, 1)])


def test_a_restored_rename_leaves_the_restored_spelling_alone(tmp_path):
    basis = (f"function,{OLD},{NEW},inferred,agree:x,{UNIT},0x00401000\n"
             f"function,{NEW},{OLD},restored,revert:x r,{UNIT},0x00401000\n")
    rows = [f"{OLD},,0x00401000,40,{UNIT},matched,real name",
            f"__ehhandler${OLD},,0x00790000,10,{UNIT},matched,gen-ehstub",
            f"Unwind@1,,0x00790010,8,{UNIT},matched,gen-funclet;parent={OLD};object-symbol=$L100"]
    assert carry(make_tree(tmp_path, rows=rows, basis=basis)) == (None, [])


CLASS_OLD, CLASS_NEW = "Rva0040ADDD", "AwardView"


def class_rows(owner, parent):
    return [f"{owner},,0x00500000,40,{UNIT},matched,real name",
            f"__ehhandler${owner},,0x00790000,10,{UNIT},matched,gen-ehstub",
            f"Unwind@1,,0x00790010,8,{UNIT},matched,gen-funclet;parent={parent};object-symbol=$L100"]


def test_a_class_rename_is_carried(tmp_path):
    basis = f"class,{CLASS_OLD},{CLASS_NEW},inferred,agree:x,{UNIT},\n"
    root = make_tree(tmp_path, rows=class_rows("?f@AwardView@@QAEXXZ", "?f@Rva0040ADDD@@QAEXXZ"), basis=basis)
    plan, refusals = carry(root)
    assert refusals == [] and plan.spellings == [("?f@Rva0040ADDD@@QAEXXZ", "?f@AwardView@@QAEXXZ", 1)]


@pytest.mark.parametrize("order", ["function-then-class", "class-then-function"])
def test_function_and_class_renames_compose_in_either_order(tmp_path, order):
    owner = "?countParts@AwardView@@QAEHH@Z"
    function = lambda old, new: f"function,{old},{new},inferred,agree:x,{UNIT},0x00500000\n"  # noqa: E731
    klass = f"class,{CLASS_OLD},{CLASS_NEW},inferred,agree:x,{UNIT},\n"
    if order == "function-then-class":
        basis = function("?Rva00500000@Rva0040ADDD@@QAEHH@Z", "?countParts@Rva0040ADDD@@QAEHH@Z") + klass
    else:
        basis = klass + function("?Rva00500000@AwardView@@QAEHH@Z", owner)
    rows = class_rows(owner, "?Rva00500000@Rva0040ADDD@@QAEHH@Z")
    plan, refusals = carry(make_tree(tmp_path, rows=rows, basis=basis))
    assert refusals == [] and plan.spellings == [("?Rva00500000@Rva0040ADDD@@QAEHH@Z", owner, 1)]


def test_dup_of_and_object_symbol_and_prose_are_carried(tmp_path):
    rows = BASE_ROWS[:2] + [f"?dup_1@@YAXXZ,,0x00404100,6,Code/Game/Free.cpp,matched,dup-of={OLD};object-symbol={OLD};"
                            f"second copy of {OLD}."]
    plan, refusals = carry(make_tree(tmp_path, rows=rows))
    assert refusals == [] and plan.spellings == [(OLD, NEW, 3)]
    rename.apply_rename(plan, ctx=ctx_of(tmp_path), verify=OK, checks=None)
    assert lines_of(tmp_path)[-1].endswith(f"dup-of={NEW};object-symbol={NEW};second copy of {NEW}.")


@pytest.mark.parametrize("key", ["import", "target", "slot"])
def test_other_tokens_are_refused(tmp_path, key):
    rows = BASE_ROWS[:3] + [f"?imp@@YAXXZ,,0x00404100,6,Code/Game/Free.cpp,matched,{key}={OLD}"]
    plan, refusals = carry(make_tree(tmp_path, rows=rows))
    assert plan is None and f"`{key}=`" in reasons(refusals)


def test_a_longer_symbol_containing_the_spelling_is_untouched(tmp_path):
    rows = BASE_ROWS[:3] + [f"?near@@YAXXZ,,0x00404100,6,Code/Game/Free.cpp,matched,"
                            f"parent={OLD}2;object-symbol=x{OLD};prose {OLD}Z"]
    plan, refusals = carry(make_tree(tmp_path, rows=rows))
    assert refusals == [] and plan.spellings == [(OLD, NEW, 1)]   # only the funclet's parent=


# ------------------------------------------------------------ refusals

def test_a_spelling_that_is_still_a_live_row_is_not_carried(tmp_path):
    rows = BASE_ROWS[:3] + [f"{OLD},,0x00405000,40,Code/Game/Free.cpp,matched,resurrected owner"]
    plan, refusals = carry(make_tree(tmp_path, rows=rows))
    assert plan is None and "still names a live row" in reasons(refusals)


def test_a_new_spelling_that_names_no_row_is_refused(tmp_path):
    rows = [BASE_ROWS[1], BASE_ROWS[2]]          # the renamed owner row is gone
    plan, refusals = carry(make_tree(tmp_path, rows=rows))
    assert plan is None and "not exactly one" in reasons(refusals)


def test_a_new_spelling_at_another_address_is_refused(tmp_path):
    rows = [f"{NEW},,0x00401234,40,{UNIT},matched,real name"] + BASE_ROWS[1:3]
    plan, refusals = carry(make_tree(tmp_path, rows=rows))
    assert plan is None and "not the renamed function's 0x00401000" in reasons(refusals)


def test_a_funclet_whose_parent_is_in_another_source_is_refused(tmp_path):
    rows = BASE_ROWS[:2] + [f"Unwind@1,,0x00790010,8,Code/Game/Other.cpp,matched,"
                            f"gen-funclet;parent={OLD};object-symbol=$L100"]
    plan, refusals = carry(make_tree(tmp_path, rows=rows))
    assert plan is None and "not a row of the funclet's own source" in reasons(refusals)


def test_a_funclet_whose_parent_has_no_eh_row_in_its_source_is_refused(tmp_path):
    plan, refusals = carry(make_tree(tmp_path, rows=[BASE_ROWS[0], BASE_ROWS[2]]))
    assert plan is None and "__ehhandler$" in reasons(refusals)


def test_a_row_in_generated_source_is_refused(tmp_path):
    rows = BASE_ROWS[:2] + [f"Unwind@1,,0x00790010,8,Code/gen_asm/gen_0001.asm,matched,"
                            f"gen-funclet;parent={OLD};object-symbol=$L100"]
    plan, refusals = carry(make_tree(tmp_path, rows=rows))
    assert plan is None and "generated source" in reasons(refusals)


@pytest.mark.parametrize("where,kwargs", [
    ("a pin", dict(symbols=f"{OLD},0x00401000,pin\n")),
    ("a data row", dict(data=f"{OLD},0x00901000,rva,4,.data,{UNIT},matched,e,m\n")),
])
def test_a_spelling_outside_the_notes_refuses_only_its_record(tmp_path, where, kwargs):
    basis = BASIS + f"function,{OLD2},{NEW2},inferred,agree:y,{UNIT},0x00403000\n"
    rows = BASE_ROWS + [f"{NEW2},,0x00403000,6,{UNIT},matched,real name",
                        f"__ehhandler${NEW2},,0x00790100,10,{UNIT},matched,gen-ehstub",
                        f"Unwind@9,,0x00790110,8,{UNIT},matched,gen-funclet;parent={OLD2};object-symbol=$L9"]
    plan, refusals = carry(make_tree(tmp_path, rows=rows, basis=basis, **kwargs))
    assert plan is not None and plan.spellings == [(OLD2, NEW2, 1)]       # the independent record lands
    assert refusals and {label for label, _ in refusals} == {f"function {OLD} -> {NEW}"}
    assert "outside the notes" in reasons(refusals) or "live row" in reasons(refusals)


def test_a_late_eh_row_under_the_old_name_refuses_the_record(tmp_path):
    rows = BASE_ROWS + [f"__ehhandler${OLD},,0x00790200,10,{UNIT},matched,gen-ehstub"]
    plan, refusals = carry(make_tree(tmp_path, rows=rows))
    assert plan is None and "outside the notes" in reasons(refusals)


def test_a_spelling_a_later_rename_reuses_is_not_carried(tmp_path):
    basis = (f"function,{OLD},{NEW},inferred,agree:x,{UNIT},0x00401000\n"
             f"function,{OLD2},{OLD},inferred,agree:x,{UNIT},0x00403000\n")
    assert carry(make_tree(tmp_path, rows=BASE_ROWS[:3], basis=basis)) == (None, [])


def test_a_forked_chain_is_refused(tmp_path):
    basis = (f"function,{OLD},{NEW},inferred,agree:x,{UNIT},0x00401000\n"
             f"function,{OLD},{MID},inferred,agree:x,{UNIT},0x00401000\n")
    plan, refusals = carry(make_tree(tmp_path, rows=BASE_ROWS[:3], basis=basis))
    assert plan is None and "forked chain" in reasons(refusals)


def test_too_many_sources_is_refused(tree):
    with pytest.raises(Refusal, match="over --max-files 1"):
        carry(tree, max_files=1)


# ------------------------------------------------------------ apply, rollback, recovery

def test_a_failed_verification_restores_every_byte(tree):
    before = snapshot(tree)
    plan, _ = carry(tree)
    with pytest.raises(VerifyFailed):
        rename.apply_rename(plan, ctx=ctx_of(tree), verify=lambda ctx, sources: False, checks=None)
    assert snapshot(tree) == before and not rename.journals(ctx_of(tree))


def test_verification_runs_over_the_changed_rows_sources(tree):
    seen = []
    plan, _ = carry(tree)
    rename.apply_rename(plan, ctx=ctx_of(tree), verify=lambda ctx, sources: seen.append(list(sources)) or True,
                        checks=None)
    assert seen == [["Code/Game/Gadget.cpp", UNIT]]


def _apply_slowly(root):
    plan, _ = rename.plan_carry(ctx_of(root))
    rename.apply_rename(plan, ctx=ctx_of(root), verify=lambda ctx, sources: time.sleep(60) or True, checks=None)


def _wait_for_journal(root, process, timeout=30):
    deadline = time.time() + timeout
    while time.time() < deadline:
        if list((root / rename.JOURNAL_DIR).glob("*.json")) and NEW in (root / rename.FUNCTIONS).read_text():
            return
        time.sleep(0.05)
    process.kill()
    pytest.fail("the carry never reached verification")


def test_a_killed_carry_is_recovered_and_blocks_the_next_run(tree):
    before = snapshot(tree)
    process = multiprocessing.get_context("fork").Process(target=_apply_slowly, args=(tree,))
    process.start()
    _wait_for_journal(tree, process)
    os.kill(process.pid, signal.SIGKILL)
    process.join()
    with pytest.raises(Refusal, match="rename.py recover"):
        rename.run("carry", ctx_of(tree), claim=False, verify=OK, checks=None)
    restored, busy = rename.recover(ctx_of(tree), release_claims=False)
    assert len(restored) == 1 and not busy
    assert snapshot(tree) == before


# ------------------------------------------------------------ the command line

def fake_build(root, ok=True):
    script = "#!/bin/sh\necho 'Functions: OK 3/3 matched'\n" if ok else "#!/bin/sh\necho 'Functions: FAIL 1/3'\nexit 1\n"
    (root / "build.sh").write_text(script)
    (root / "build.sh").chmod(0o755)


def test_cli_applies_and_exits_zero(tree, capsys):
    fake_build(tree)
    code = rename.main(["carry", "--all", "--no-claim", "--root", str(tree)])
    out = capsys.readouterr().out
    assert code == 0
    assert "verified OK. Stage: git add reverse/functions.csv" in out
    assert "check --range origin/master..HEAD" in out
    assert OLD not in (tree / rename.FUNCTIONS).read_text()


def test_cli_restores_and_exits_one_when_the_build_fails(tree):
    fake_build(tree, ok=False)
    before = snapshot(tree)
    before.pop("build.sh", None)
    assert rename.main(["carry", "--all", "--no-claim", "--root", str(tree)]) == 1
    after = snapshot(tree)
    after.pop("build.sh")
    assert after == before


def test_cli_with_nothing_to_carry_exits_zero(tmp_path, capsys):
    root = make_tree(tmp_path, rows=[BASE_ROWS[0]])
    assert rename.main(["carry", "--all", "--no-claim", "--root", str(root)]) == 0
    assert "no notes token" in capsys.readouterr().out


def test_cli_exits_two_when_something_is_refused_after_carrying_the_rest(tmp_path, capsys):
    fake_build(tmp_path)
    basis = BASIS + f"function,{OLD2},{NEW2},inferred,agree:y,{UNIT},0x00403000\n"
    rows = BASE_ROWS[:3] + [f"{NEW2},,0x00403000,6,{UNIT},matched,real name",
                            f"__ehhandler${NEW2},,0x00790100,10,{UNIT},matched,gen-ehstub",
                            f"Unwind@9,,0x00790110,8,{UNIT},matched,gen-funclet;parent={OLD2};object-symbol=$L9",
                            f"?imp@@YAXXZ,,0x00404100,6,Code/Game/Free.cpp,matched,import={OLD}"]
    root = make_tree(tmp_path, rows=rows, basis=basis)
    assert rename.main(["carry", "--all", "--no-claim", "--root", str(root)]) == 2
    captured = capsys.readouterr()
    assert "carry refused: function" in captured.err and "`import=`" in captured.err
    text = (root / rename.FUNCTIONS).read_text()
    assert f"parent={NEW2}" in text and f"parent={OLD}" in text          # the refused record is untouched


def test_cli_range_considers_only_the_renames_the_range_added(tmp_path, capsys):
    basis_first = f"function,{OLD2},{NEW2},inferred,agree:y,{UNIT},0x00403000\n"
    rows = BASE_ROWS[:3] + [f"{NEW2},,0x00403000,6,{UNIT},matched,real name",
                            f"__ehhandler${NEW2},,0x00790100,10,{UNIT},matched,gen-ehstub",
                            f"Unwind@9,,0x00790110,8,{UNIT},matched,gen-funclet;parent={OLD2};object-symbol=$L9"]
    root = make_tree(tmp_path, rows=rows, basis=basis_first)
    _git(root, "commit", "-q", "-m", "first")
    with (root / rename.NAME_BASIS).open("a") as handle:
        handle.write(BASIS)
    _git(root, "add", "-A")
    _git(root, "commit", "-q", "-m", "second")
    code = rename.main(["carry", "--range", "HEAD~1..HEAD", "--dry-run", "--no-claim", "--root", str(root)])
    out = capsys.readouterr().out
    assert code == 0 and f"{OLD} -> {NEW}" in out and OLD2 not in out


# ------------------------------------------------------------ the real tree

@pytest.mark.skipif(not (rename.ROOT / rename.FUNCTIONS).exists(), reason="no real ledger")
def test_real_tree_plan_never_crashes_and_writes_only_functions_notes():
    ctx = rename.Context(rename.ROOT, object_scan=False)
    plan, refusals = rename.plan_carry(ctx)
    assert isinstance(refusals, list)
    if plan is None:
        return
    assert list(plan.after) == [rename.FUNCTIONS] and plan.spellings and plan.verify
    old = ledger_io.split_records(ctx.read(rename.FUNCTIONS))
    new = ledger_io.split_records(plan.after[rename.FUNCTIONS])
    assert len(old) == len(new)
    for (a, _), (b, _) in zip(old, new):
        if a != b:
            fa, fb = ledger_io.fields(a), ledger_io.fields(b)
            assert fa[:6] == fb[:6] and fa[6] != fb[6]
