"""Scoped locals may trust an explicitly quoted header in the pinned BFME1
gitlink, and nothing else. A miniature superproject with a real gitlink keeps
the pin, checkout, dirty, untracked and symlink cases honest; the source and
header fixtures mirror the blocked DiscreteCircle offsets.
"""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal  # noqa: E402
from test_rename_fixes import agree, ctx_of, make_tree  # noqa: E402

UNIT = "Code/Game/Foo.cpp"
FUNCTION = "DiscreteCircle::generateEdgePairs"
DONOR_REL = "game/GameEngine/Source/Common/discrete_circle.h"
DONOR_INCLUDE = "../../reference/open-bfme-1/" + DONOR_REL
FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
?generateEdgePairs@DiscreteCircle@@QAEXHHH@Z,,0x00401000,40,{UNIT},matched,address-derived
"""
SOURCE = f"""// cl: /O2
#include "{DONOR_INCLUDE}"
#include "windows.h"
void DiscreteCircle::generateEdgePairs(int xCenter, int yCenter, int radius)
{{
    int x = 0;
    int y = radius;
    xCenter += x;
    yCenter += y;
}}
"""
WINDOWS = "struct tagPOINT { int x; int y; };\n"
DONOR_HEADER = """#pragma once
class DiscreteCircle
{
public:
    void generateEdgePairs(int xCenter, int yCenter, int radius);
};
"""


def _git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True,
                          capture_output=True, text=True).stdout


def _commit(root, message="fixture"):
    return _git(root, "-c", "user.email=fixture@example.invalid",
                "-c", "user.name=Fixture", "commit", "-qm", message)


def _init_donor(root, headers, module=rename.DONOR_GITLINK):
    donor = root / module
    donor.mkdir(parents=True)
    _git(donor, "init", "-q")
    for rel, text in headers.items():
        path = donor / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode())
    _git(donor, "add", "-A")
    _commit(donor)
    return _git(donor, "rev-parse", "HEAD").strip()


def donor_tree(tmp_path, headers=None, extra=None):
    """A committed superproject with DONOR_GITLINK at a clean donor checkout."""
    files = {
        "reverse/functions.csv": FUNCTIONS,
        UNIT: SOURCE,
        "reference/shims/sweep/windows.h": WINDOWS,
    }
    files.update(extra or {})
    root = make_tree(tmp_path, files)
    pin = _init_donor(root, headers if headers is not None else {DONOR_REL: DONOR_HEADER})
    _git(root, "add", rename.DONOR_GITLINK)
    _commit(root)
    return root, pin


def local_plan(root, old="x", new="xOffset", function=FUNCTION):
    evidence = agree(root, f"scope-{old}-{new}", "local", old, new)
    return rename.plan_rename("local", ctx=ctx_of(root), source=UNIT, function=function,
                              name=old, new=new, basis="inferred", evidence=evidence)


def refused(root, old="x", new="xOffset", match="member of tagPOINT"):
    with pytest.raises(Refusal, match=match):
        local_plan(root, old, new)


# ------------------------------------------------------- the trusted donor header

def test_pinned_explicit_donor_header_proves_the_owner_class(tmp_path):
    root, _pin = donor_tree(tmp_path)
    ctx = ctx_of(root)
    assert rename.DONOR_GITLINK + "/" + DONOR_REL in rename.header_closure(ctx, UNIT)
    assert rename.class_ancestors(ctx, UNIT, "DiscreteCircle") == {"DiscreteCircle"}
    plan = local_plan(root)
    assert "int xOffset = 0;" in plan.after[UNIT].decode()
    assert "xCenter += xOffset;" in plan.after[UNIT].decode()


def test_a_nested_relative_donor_include_uses_the_actual_includer(tmp_path):
    # <vector> widens to reference/shims/vector first; the quoted include must
    # still resolve beside the donor header, not beside that widened path.
    donor_header = """#pragma once
#include <vector>
#include "detail/base.h"
class DiscreteCircle : CircleBase
{
public:
    void generateEdgePairs(int xCenter, int yCenter, int radius);
};
"""
    headers = {
        DONOR_REL: donor_header,
        "game/GameEngine/Source/Common/detail/base.h": "#pragma once\nclass CircleBase { };\n",
    }
    root, _pin = donor_tree(tmp_path, headers,
                            {"reference/shims/vector": "// basename-widened shim\n"})
    ctx = ctx_of(root)
    assert rename.class_ancestors(ctx, UNIT, "DiscreteCircle") == {"DiscreteCircle", "CircleBase"}
    assert "int xOffset = 0;" in local_plan(root).after[UNIT].decode()


def test_two_donor_headers_keep_their_own_relative_includes(tmp_path):
    a = "game/GameEngine/Source/Common/a/outer.h"
    b = "game/GameEngine/Source/Common/b/outer.h"
    headers = {
        a: ('#pragma once\n#include "shared.h"\n'
            'class DiscreteCircle : BaseA\n{\npublic:\n'
            '    void generateEdgePairs(int xCenter, int yCenter, int radius);\n};\n'),
        "game/GameEngine/Source/Common/a/shared.h": "class BaseA { };\n",
        b: '#pragma once\n#include "shared.h"\nclass Other : BaseB { };\n',
        "game/GameEngine/Source/Common/b/shared.h": "class BaseB { };\n",
    }
    source = SOURCE.replace(f'#include "{DONOR_INCLUDE}"',
                            f'#include "../../reference/open-bfme-1/{a}"\n'
                            f'#include "../../reference/open-bfme-1/{b}"')
    root, _pin = donor_tree(tmp_path, headers, {UNIT: source})
    ctx = ctx_of(root)
    assert rename.class_ancestors(ctx, UNIT, "DiscreteCircle") == {"DiscreteCircle", "BaseA"}
    assert rename.class_ancestors(ctx, UNIT, "Other") == {"Other", "BaseB"}
    assert "int xOffset = 0;" in local_plan(root).after[UNIT].decode()


def test_only_an_explicitly_quoted_include_uses_the_donor(tmp_path):
    source = SOURCE.replace(f'#include "{DONOR_INCLUDE}"', f"#include <{DONOR_REL}>")
    root, _pin = donor_tree(tmp_path, extra={UNIT: source})
    assert rename.DONOR_GITLINK + "/" + DONOR_REL not in rename.header_closure(ctx_of(root), UNIT)
    refused(root)


# ------------------------------------------------------------- failed trust cases

def test_a_mismatched_index_pin_is_ignored(tmp_path):
    root, pin = donor_tree(tmp_path)
    donor = root / rename.DONOR_GITLINK
    (donor / "game/README").write_bytes(b"second\n")
    _git(donor, "add", "-A")
    _commit(donor, "second")
    other = _git(donor, "rev-parse", "HEAD").strip()
    assert other != pin
    _git(root, "update-index", "--cacheinfo", "160000", other, rename.DONOR_GITLINK)
    refused(root)


def test_a_submodule_checkout_away_from_the_pin_is_ignored(tmp_path):
    root, pin = donor_tree(tmp_path)
    donor = root / rename.DONOR_GITLINK
    (donor / "game/README").write_bytes(b"second\n")
    _git(donor, "add", "-A")
    _commit(donor, "second")
    assert _git(donor, "rev-parse", "HEAD").strip() != pin
    refused(root)


def test_a_missing_gitlink_or_pin_is_ignored(tmp_path):
    root, _pin = donor_tree(tmp_path)
    _git(root, "rm", "--cached", rename.DONOR_GITLINK)
    refused(root)


def test_another_gitlink_is_not_trusted(tmp_path):
    other = "reference/other-module"
    source = SOURCE.replace(DONOR_INCLUDE, "../../" + other + "/" + DONOR_REL)
    root = make_tree(tmp_path, {
        "reverse/functions.csv": FUNCTIONS,
        UNIT: source,
        "reference/shims/sweep/windows.h": WINDOWS,
    })
    _init_donor(root, {DONOR_REL: DONOR_HEADER}, module=other)
    _git(root, "add", other)
    _commit(root)
    assert other + "/" + DONOR_REL not in rename.header_closure(ctx_of(root), UNIT)
    refused(root)


def test_a_dirty_donor_header_is_ignored(tmp_path):
    root, _pin = donor_tree(tmp_path)
    header = root / rename.DONOR_GITLINK / DONOR_REL
    header.write_bytes(header.read_bytes() + b"\n// dirty\n")
    refused(root)


def test_a_dirty_tracked_donor_worktree_is_ignored(tmp_path):
    root, _pin = donor_tree(tmp_path, {DONOR_REL: DONOR_HEADER, "game/README": "clean\n"})
    (root / rename.DONOR_GITLINK / "game/README").write_bytes(b"dirty\n")
    refused(root)


def test_an_untracked_donor_header_is_ignored(tmp_path):
    root, _pin = donor_tree(tmp_path, {"game/README": "donor\n"})
    header = root / rename.DONOR_GITLINK / DONOR_REL
    header.parent.mkdir(parents=True, exist_ok=True)
    header.write_bytes(DONOR_HEADER.encode())
    refused(root)


def test_a_symlinked_donor_header_is_ignored(tmp_path):
    root, _pin = donor_tree(tmp_path)
    header = root / rename.DONOR_GITLINK / DONOR_REL
    outside = tmp_path / "outside.h"
    outside.write_bytes(header.read_bytes())
    header.unlink()
    header.symlink_to(outside)
    refused(root)


def test_a_relative_include_leaving_the_donor_gitlink_is_ignored(tmp_path):
    donor_header = """#pragma once
#include "../../../../reference/other-module/owner.h"
"""
    root, _pin = donor_tree(tmp_path, {DONOR_REL: donor_header},
                            {"reference/other-module/owner.h": "class DiscreteCircle { };\n"})
    assert rename.DONOR_GITLINK + "/" + DONOR_REL in rename.header_closure(ctx_of(root), UNIT)
    refused(root)


# ---------------------------------------------------- the existing capture guards

@pytest.mark.parametrize("shape,match", [
    ("own", "member of DiscreteCircle"),
    ("base", "member of CircleBase"),
    ("macro", "a macro"),
    ("missing_base", "member of tagPOINT"),
])
def test_donor_ancestry_keeps_member_and_macro_captures(tmp_path, shape, match):
    body = """public:
    void generateEdgePairs(int xCenter, int yCenter, int radius);
"""
    if shape == "own":
        donor_header = "class DiscreteCircle {\npublic:\n    int x;\n" + body + "};\n"
    elif shape == "base":
        donor_header = ("struct CircleBase { int x; };\n"
                        "class DiscreteCircle : CircleBase {\n" + body + "};\n")
    elif shape == "macro":
        donor_header = "#define READ_X() x\nclass DiscreteCircle {\n" + body + "};\n"
    else:
        donor_header = "class DiscreteCircle : Missing {\n" + body + "};\n"
    root, _pin = donor_tree(tmp_path, {DONOR_REL: donor_header})
    refused(root, match=match)


def test_an_unrelated_member_beside_a_trusted_owner_is_still_allowed(tmp_path):
    root, _pin = donor_tree(tmp_path)
    plan = local_plan(root, "x", "xOffset")
    assert "struct tagPOINT { int x; int y; };" in (
        root / "reference/shims/sweep/windows.h").read_text()
    assert "int xOffset = 0;" in plan.after[UNIT].decode()


def test_replaced_donor_commit_cannot_substitute_header_evidence(tmp_path):
    root, pin = donor_tree(tmp_path, {DONOR_REL: DONOR_HEADER.replace("public:", "public:\n    int x;")})
    donor = root / rename.DONOR_GITLINK
    (donor / DONOR_REL).write_bytes(DONOR_HEADER.encode())
    _git(donor, "add", "-A")
    _commit(donor, "replacement")
    replacement = _git(donor, "rev-parse", "HEAD").strip()
    _git(donor, "reset", "--hard", pin)
    _git(donor, "replace", pin, replacement)
    _git(donor, "read-tree", "--reset", "-u", pin)
    assert not _git(donor, "status", "--porcelain").strip()
    refused(root)


def test_replaced_superproject_commit_cannot_change_the_recorded_pin(tmp_path):
    root, pin = donor_tree(tmp_path)
    original = _git(root, "rev-parse", "HEAD").strip()
    donor = root / rename.DONOR_GITLINK
    (donor / "game/README").write_bytes(b"second\n")
    _git(donor, "add", "-A")
    _commit(donor, "second")
    _git(root, "add", rename.DONOR_GITLINK)
    _commit(root, "new pin")
    replacement = _git(root, "rev-parse", "HEAD").strip()
    _git(root, "reset", "--soft", original)
    _git(root, "replace", original, replacement)
    refused(root)


def test_header_bytes_are_checked_against_the_frozen_pin(tmp_path):
    root, pin = donor_tree(tmp_path)
    ctx = ctx_of(root)
    assert rename._pinned_donor_checkout(ctx) == root / rename.DONOR_GITLINK
    donor = root / rename.DONOR_GITLINK
    (donor / DONOR_REL).write_bytes((DONOR_HEADER + "\n// later commit\n").encode())
    _git(donor, "add", "-A")
    _commit(donor, "moved during plan")
    assert rename.trusted_donor_header(ctx, UNIT, DONOR_INCLUDE) is None
