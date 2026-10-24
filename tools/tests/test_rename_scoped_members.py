"""A parameter/local cannot mean a named member of a proven unrelated class."""
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))

import rename
from test_rename_fixes import OK, agree, ctx_of, make_tree

UNIT = "Code/Game/Foo.cpp"


def plan(tmp_path, kind, text, function="f", headers=None):
    root = make_tree(tmp_path, {UNIT: "// cl: /O2\n" + text, **(headers or {})})
    old = "param_1" if kind == "param" else "iVar1"
    evidence = agree(root, "scope", kind, old, "value")
    result = rename.plan_rename(kind, ctx=ctx_of(root), source=UNIT,
                                function=function, name=old, new="value",
                                basis="inferred", evidence=evidence)
    return root, result


def method(kind):
    return ("\nint f(int param_1) { return param_1; }\n" if kind == "param" else
            "\nint f() { int iVar1 = 7; return iVar1; }\n")


@pytest.mark.parametrize("kind", ["param", "local"])
@pytest.mark.parametrize("shape", ["inline", "out_of_line", "free"])
def test_unrelated_named_member_is_untouched_and_revertible(tmp_path, kind, shape):
    old = "param_1" if kind == "param" else "iVar1"
    unrelated = f"struct S12 {{ int {old}; }};\n"
    body = method(kind)
    if shape == "inline":
        text, function = unrelated + f"struct Foo {{ {body} }};\n", "f"
    elif shape == "out_of_line":
        text = unrelated + "struct Foo { int f(" + ("int param_1" if kind == "param" else "") + "); };\n"
        text += body.replace("f(", "Foo::f(") + "\n"
        function = "Foo::f"
    else:
        text, function = unrelated + body + "\n", "f"
    root, result = plan(tmp_path, kind, text, function)
    changed = result.after[UNIT].decode()
    assert unrelated in changed
    assert "return value;" in changed
    rename.apply_rename(result, ctx=ctx_of(root), verify=OK, checks=None)
    assert rename.check_renames(ctx_of(root), rename.name_basis_rows(ctx_of(root))) == []
    rename.revert(ctx_of(root), "scope", "fixture inverse", claim=False, verify=OK, checks=None)
    assert (root / UNIT).read_text() == "// cl: /O2\n" + text


@pytest.mark.parametrize("kind", ["param", "local"])
def test_unrelated_member_with_known_base_chain_is_allowed(tmp_path, kind):
    old = "param_1" if kind == "param" else "iVar1"
    text = f"struct S12 {{ int {old}; }};\nstruct Base {{}};\nstruct Mid : Base {{}};\n"
    text += f"struct Foo : Mid {{ {method(kind)} }};\n"
    assert plan(tmp_path, kind, text)[1]


@pytest.mark.parametrize("kind", ["param", "local"])
@pytest.mark.parametrize("shape", ["own", "base", "missing_base", "dependent_base", "nested", "qualified_nested"])
def test_related_or_unresolved_class_members_stay_refused(tmp_path, kind, shape):
    old = "param_1" if kind == "param" else "iVar1"
    body = method(kind)
    function = "f"
    if shape == "own":
        text = f"struct Foo {{ int {old}; {body} }};\n"
    elif shape == "base":
        text = f"struct Base {{ int {old}; }};\nstruct Foo : Base {{ {body} }};\n"
    elif shape in ("missing_base", "dependent_base"):
        base = "Missing" if shape == "missing_base" else "T::Base"
        text = f"struct Other {{ int {old}; }};\nstruct Foo : {base} {{ {body} }};\n"
    elif shape == "nested":
        text = f"struct Outer {{ static int {old}; struct Foo {{ {body} }}; }};\n"
    else:
        text = f"struct Outer {{ static int {old}; struct Foo {{ int f(" + ("int param_1" if kind == "param" else "") + "); }; };\n"
        text += body.replace("f(", "Outer::Foo::f(") + "\n"
        function = "Outer::Foo::f"
    with pytest.raises(rename.Refusal, match="member of"):
        plan(tmp_path, kind, text, function)


@pytest.mark.parametrize("kind", ["param", "local"])
@pytest.mark.parametrize("prefix,match", [
    ("int OLD;\n", "global"),
    ("#define READ_OLD() OLD\n", "macro"),
    ("int value;\n", "already a name"),
    ("struct Other { int value; };\n", "already a name"),
    ("#define value 7\n", "already a name"),
])
def test_other_outer_meanings_and_new_name_collisions_stay_refused(tmp_path, kind, prefix, match):
    old = "param_1" if kind == "param" else "iVar1"
    text = prefix.replace("OLD", old) + f"struct Foo {{ {method(kind)} }};\n"
    with pytest.raises(rename.Refusal, match=match):
        plan(tmp_path, kind, text)


@pytest.mark.parametrize("access", ["this->param_1", "other.param_1", "Foo::param_1"])
def test_explicit_member_access_stays_refused(tmp_path, access):
    text = f"struct Other {{ int param_1; }}; struct Foo {{\nint f(int param_1) {{ return {access}; }}\n}};\n"
    with pytest.raises(rename.Refusal, match="after ->, . or ::"):
        plan(tmp_path, "param", text)


@pytest.mark.parametrize("kind", ["param", "local"])
@pytest.mark.parametrize("hazard", ["global", "own_member", "macro", "unknown_base"])
def test_revert_rechecks_new_outer_meanings(tmp_path, kind, hazard):
    old = "param_1" if kind == "param" else "iVar1"
    text = f"struct S12 {{ int {old}; }};\nstruct Foo {{ {method(kind)} }};\n"
    root, result = plan(tmp_path, kind, text)
    rename.apply_rename(result, ctx=ctx_of(root), verify=OK, checks=None)
    path = root / UNIT
    changed = path.read_text()
    if hazard == "global":
        changed += f"int {old};\n"
    elif hazard == "own_member":
        changed = changed.replace("struct Foo {", f"struct Foo {{ int {old};")
    elif hazard == "macro":
        changed += f"#define READ_OLD() {old}\n"
    else:
        changed = changed.replace("struct Foo {", "struct Foo : Missing {")
    path.write_bytes(changed.encode())
    with pytest.raises(rename.Refusal):
        rename.revert(ctx_of(root), "scope", "fixture inverse", claim=False, verify=OK, checks=None)
    assert path.read_text() == changed


def test_restored_basis_without_a_record_does_not_bypass_new_member_collision(tmp_path):
    text = "struct S12 { int value; };\nstruct Foo {" + method("param") + "};\n"
    root = make_tree(tmp_path, {UNIT: "// cl: /O2\n" + text})
    with pytest.raises(rename.Refusal, match="no landing|not found|record|inferred landing"):
        rename.plan_rename("param", ctx=ctx_of(root), source=UNIT, function="f",
                           name="param_1", new="value", basis=rename.RESTORED,
                           evidence="revert:missing: fixture")


@pytest.mark.parametrize("kind", ["param", "local"])
@pytest.mark.parametrize("inherited", [False, True])
def test_nested_owner_or_base_declared_in_a_header_stays_conservative(tmp_path, kind, inherited):
    old = "param_1" if kind == "param" else "iVar1"
    header = f"struct Outer {{ static int {old}; struct Base {{}}; struct Foo {{ int f(); }}; }};\n"
    if inherited:
        header += "struct Foo : Outer::Base { int f(); };\n"
        function = "Foo::f"
    else:
        function = "Outer::Foo::f"
    text = '#include "Owner.h"\n' + f"struct S12 {{ int {old}; }};\n"
    text += method(kind).replace("f(", function + "(")
    with pytest.raises(rename.Refusal, match="member of S12"):
        plan(tmp_path, kind, text, function, {"Code/Game/Owner.h": header})
