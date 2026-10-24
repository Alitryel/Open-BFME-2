"""Overload selectors survive the naming ledger, check, carry and revert.

The famgenDelete false reject (2026-10-24) selected #8/#9 correctly but
recorded neither selector, so check judged every unchanged overload.
"""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import rename
from test_rename_fixes import OK, _git, agree, append, ctx_of, make_tree

UNIT = "Code/Game/Foo.cpp"
SCOPE = "Rva00400000::rva00410000"
TEXT = f"""// cl: /O2
struct Rva00400000 {{ int rva00410000(int a); int rva00410000(float a); }};
int {SCOPE}(int param_1) {{ int iVar1 = param_1; return iVar1; }}
int {SCOPE}(float param_1) {{ int iVar1 = (int)param_1; return iVar1; }}
"""


@pytest.fixture
def tree(tmp_path):
    root = make_tree(tmp_path, {UNIT: TEXT})
    rows = (root / rename.FUNCTIONS).read_text().replace(
        "?f@Foo@@QAEHH@Z", "?rva00410000@Rva00400000@@QAEHH@Z").replace(
        "?f@Foo@@QAEHM@Z", "?rva00410000@Rva00400000@@QAEHM@Z")
    (root / rename.FUNCTIONS).write_bytes(rows.encode())
    _git(root, "add", "-A")
    return root


def apply(root, kind="param", selector="#2", rid="overload"):
    old, new = ("param_1", "ratio") if kind == "param" else ("iVar1", "result")
    evidence = agree(root, rid, kind, old, new)
    plan = rename.plan_rename(kind, ctx=ctx_of(root), source=UNIT,
                              function=SCOPE + selector, name=old, new=new,
                              basis="inferred", evidence=evidence)
    rename.apply_rename(plan, ctx=ctx_of(root), verify=OK, checks=None)
    return plan


def problems(root):
    ctx = ctx_of(root)
    return rename.check_renames(ctx, rename.name_basis_rows(ctx))


@pytest.mark.parametrize("kind", ["param", "local"])
def test_selected_overload_is_recorded_and_unchanged_sibling_passes(tree, kind):
    plan = apply(tree, kind)
    assert plan.old == f"{SCOPE}#2::{plan.old_word}"
    assert plan.new == f"{SCOPE}#2::{plan.new_word}"
    assert problems(tree) == []
    text = (tree / UNIT).read_text()
    assert TEXT.splitlines()[2] in text


@pytest.mark.parametrize("kind", ["param", "local"])
def test_resurrected_old_name_in_selected_overload_still_fails(tree, kind):
    plan = apply(tree, kind)
    (tree / UNIT).write_text(TEXT)
    findings = problems(tree)
    assert len(findings) == 1
    assert f"{SCOPE}#2 still declares {kind} {plan.old_word}" in findings[0]


@pytest.mark.parametrize("kind", ["param", "local"])
def test_lost_selected_overload_is_reported(tree, kind):
    apply(tree, kind)
    (tree / UNIT).write_text("\n".join(TEXT.splitlines()[:3]) + "\n")
    assert any(f"no function {SCOPE}#2" in p for p in problems(tree))


def test_missing_source_does_not_hide_a_selected_record(tree):
    apply(tree)
    (tree / UNIT).unlink()
    assert any(f"{UNIT}: source is missing" in p for p in problems(tree))


@pytest.mark.parametrize("kind", ["param", "local"])
def test_revert_uses_recorded_selector_without_manual_hint(tree, kind):
    apply(tree, kind)
    rename.revert(ctx_of(tree), "overload", "the inferred name was wrong",
                  claim=False, verify=OK, checks=None)
    assert (tree / UNIT).read_text() == TEXT
    restored = rename.name_basis_rows(ctx_of(tree))[-1]
    assert restored["basis"] == "restored" and "#2::" in restored["new"]
    assert problems(tree) == []


@pytest.mark.parametrize("kind", ["param", "local"])
def test_revert_cannot_redirect_a_recorded_selector(tree, kind):
    apply(tree, kind)
    before = (tree / UNIT).read_bytes()
    with pytest.raises(rename.Refusal, match="recorded overload"):
        rename.revert(ctx_of(tree), "overload", "wrong", function=SCOPE + "#1",
                      claim=False, verify=OK, checks=None)
    assert (tree / UNIT).read_bytes() == before


@pytest.mark.parametrize("kind", ["param", "local"])
def test_explicit_first_overload_has_its_own_scope(tree, kind):
    plan = apply(tree, kind, "#1")
    assert "#1::" in plan.old
    assert problems(tree) == []
    assert TEXT.splitlines()[3] in (tree / UNIT).read_text()


def test_legacy_unselected_record_keeps_checking_all_overloads(tree):
    append(tree, rename.NAME_BASIS, rename.NAME_BASIS_HEADER + "\n" +
           f"param,{SCOPE}::param_1,{SCOPE}::ratio,inferred,agree:old,{UNIT},\n")
    findings = problems(tree)
    assert len(findings) == 2
    assert any(f"{SCOPE}#2 still declares" in p for p in findings)


@pytest.mark.parametrize("selector", ["", "#2"])
def test_canonical_protection_applies_to_legacy_and_selected_records(tree, selector):
    append(tree, rename.NAME_BASIS, rename.NAME_BASIS_HEADER + "\n" +
           f"param,{SCOPE}{selector}::p,{SCOPE}{selector}::param_1,canonical:string,cited,{UNIT},\n")
    with pytest.raises(rename.Refusal, match="canonical name"):
        apply(tree)


def test_legacy_revert_with_manual_selector_still_uses_exact_inverse(tree):
    plan = apply(tree)
    basis = (tree / rename.NAME_BASIS).read_text().replace(f"{SCOPE}#2::", f"{SCOPE}::")
    (tree / rename.NAME_BASIS).write_bytes(basis.encode())
    rename.revert(ctx_of(tree), "overload", "wrong", function=SCOPE + "#2",
                  claim=False, verify=OK, checks=None)
    restored = rename.name_basis_rows(ctx_of(tree))[-1]
    assert restored["new"] == f"{SCOPE}::{plan.old_word}"
    assert (tree / UNIT).read_text() == TEXT
    assert problems(tree) == []


@pytest.mark.parametrize("kind", ["function", "class"])
def test_scope_carry_preserves_selector_and_revertibility(tree, kind):
    selector = "#2"
    if kind == "function":
        # Renaming one member of an overload set is deliberately refused.
        # A recorded explicit #1 still needs carrying when its sole function
        # is renamed; class scope changes can carry a real overload set.
        selector = "#1"
        (tree / UNIT).write_text("\n".join(TEXT.splitlines()[:3]) + "\n")
        rows = (tree / rename.FUNCTIONS).read_text().splitlines(keepends=True)
        (tree / rename.FUNCTIONS).write_bytes("".join(r for r in rows if "QAEHM@Z" not in r).encode())
    apply(tree, selector=selector)
    if kind == "class":
        kwargs = dict(name="Rva00400000", new="Counter")
        evidence = agree(tree, "owner", kind, "Rva00400000", "Counter")
        expected_scope = "Counter::rva00410000#2"
    else:
        kwargs = dict(rva=0x00410000, new="countItems")
        evidence = agree(tree, "owner", kind,
                         "?rva00410000@Rva00400000@@QAEHH@Z", "countItems", "0x00410000")
        expected_scope = "Rva00400000::countItems#1"
    plan = rename.plan_rename(kind, ctx=ctx_of(tree), basis="inferred", evidence=evidence, **kwargs)
    rename.apply_rename(plan, ctx=ctx_of(tree), verify=OK, checks=None)
    assert rename.landing(ctx_of(tree), "overload").current == f"{expected_scope}::ratio"
    ctx = ctx_of(tree)
    scoped_rows = [r for r in rename.name_basis_rows(ctx) if r["kind"] == "param"]
    assert rename.check_renames(ctx, scoped_rows) == []
    rename.revert(ctx_of(tree), "overload", "wrong", claim=False, verify=OK, checks=None)
    assert "ratio" not in (tree / UNIT).read_text()
    assert problems(tree) == []


def test_post_rebase_cli_uses_numbered_record(tree):
    _git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-qm", "base")
    apply(tree)
    _git(tree, "add", "-A")
    _git(tree, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-qm", "rename")
    assert rename.main(["check", "--range", "HEAD~1..HEAD", "--root", str(tree)]) == 0
    (tree / UNIT).write_text(TEXT)
    assert rename.main(["check", "--range", "HEAD~1..HEAD", "--root", str(tree)]) == 1


def test_recorded_file_moves_do_not_make_the_selected_source_go_missing(tree):
    apply(tree)
    new_source = "Code/Game/Readable.cpp"
    _git(tree, "mv", UNIT, new_source)
    path = tree / rename.NAME_BASIS
    path.write_bytes(path.read_bytes() + rename.csv_line([
        "file", UNIT, new_source, "inferred", "mechanical:fixture", new_source, ""]))
    path = tree / rename.FUNCTIONS
    path.write_bytes(path.read_bytes().replace(UNIT.encode(), new_source.encode()))
    _git(tree, "add", "-A")
    assert problems(tree) == []
    rename.revert(ctx_of(tree), "overload", "wrong", claim=False, verify=OK, checks=None)
    assert (tree / new_source).read_text() == TEXT
    assert problems(tree) == []
