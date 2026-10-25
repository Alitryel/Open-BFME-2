"""Global rewrites must emit declarations even when prose mentions extern."""
import sys
import unittest
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import name_globals

INDEX = {0x00E23300: ['?SharedGlobal@@3HA']}



class TestGlobalDeclarations(unittest.TestCase):
    def test_comment_before_initializer_does_not_supply_declaration(self):
        source = '// The extern spellings above use a different shape.\nstatic int *const p = (int *)0x00E23300;\n'
        rewritten, _ = name_globals.rewrite(source, INDEX)
        assert 'extern int SharedGlobal;' in rewritten
        assert '(int *)&SharedGlobal' in rewritten


    def test_block_comment_does_not_supply_declaration(self):
        source = '/* extern int SharedGlobal; */\nstatic int *p = (int *)0x00E23300;\n'
        rewritten, _ = name_globals.rewrite(source, INDEX)
        assert rewritten.startswith('extern int SharedGlobal;\n')


    def test_quoted_declaration_does_not_supply_declaration(self):
        source = 'const char *note = "extern int SharedGlobal;";\nstatic int *p = (int *)0x00E23300;\n'
        rewritten, _ = name_globals.rewrite(source, INDEX)
        assert rewritten.startswith('extern int SharedGlobal;\n')
        assert '"extern int SharedGlobal;"' in rewritten


    def test_existing_declaration_survives_comment_markers_in_literals(self):
        source = 'const char *note = "https://example.test/*path*/";\nextern int SharedGlobal;\nstatic int *p = (int *)0x00E23300;\n'
        rewritten, _ = name_globals.rewrite(source, INDEX)
        assert rewritten.count('extern int SharedGlobal;') == 1
        assert '"https://example.test/*path*/"' in rewritten
        assert '(int *)&SharedGlobal' in rewritten


import os
import subprocess

import pytest

import hatch_counters

VTABLE_INDEX = {0x00C5EE80: ['??_7Foo@@6B@'], 0x00E23300: ['?g_Va00E23300@@3HA']}
UNIT = "Code/GameEngine/a.cpp"


def _git(root, *args):
    env = dict(os.environ, GIT_AUTHOR_NAME="t", GIT_COMMITTER_NAME="t", GIT_AUTHOR_EMAIL="",
               GIT_COMMITTER_EMAIL="")
    got = subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, env=env)
    assert got.returncode == 0, got.stderr
    return got.stdout


@pytest.fixture
def enforced(tmp_path, monkeypatch):
    """A tree with one unit and an ENFORCED hatch register that grants it nothing."""
    (tmp_path / "Code/GameEngine").mkdir(parents=True)
    (tmp_path / "reverse").mkdir()
    (tmp_path / UNIT).write_bytes(b"void f(int *v) { *v = (int)0x00C5EE80; *v = *(int *)0x00E23300; }\n")
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "config", "core.autocrlf", "false")
    monkeypatch.setattr(hatch_counters, "ROOT", tmp_path)
    monkeypatch.setattr(name_globals, "ROOT", tmp_path)
    _git(tmp_path, "add", ".")
    hatch_counters.write(hatch_counters.tree_scan(), mode="enforce")
    _git(tmp_path, "add", ".")
    _git(tmp_path, "commit", "-qm", "init")
    return tmp_path


def _land(root, need_only=None):
    """What name_globals.main does for UNIT once bulk_pass verified the rewrite."""
    original = (root / UNIT).read_bytes()
    new, need = name_globals.rewrite(original.decode("latin-1"), VTABLE_INDEX, need_only)
    (root / UNIT).write_bytes(new.encode("latin-1"))
    return name_globals.admit_written(UNIT, set(need), original), need


def _gate(root):
    _git(root, "add", ".")
    errors, _, hard = hatch_counters.check_staged()
    return errors + hard


def test_name_globals_admits_the_hatches_it_writes(enforced):
    ok, need = _land(enforced)
    assert ok and set(need) == {"vtbl_00C5EE80", "g_Va00E23300"}
    text = (enforced / UNIT).read_text()
    assert '/alternatename:_vtbl_00C5EE80=??_7Foo@@6B@' in text and "extern int g_Va00E23300;" in text
    assert _gate(enforced) == []                                          # the enforced gate grants them


def test_a_hand_alias_beside_the_tools_is_still_refused(enforced):
    ok, _ = _land(enforced)
    assert ok
    with (enforced / UNIT).open("a", newline="\n") as handle:
        handle.write('#pragma comment(linker, "/alternatename:?h@@YAXXZ=?g@@YAXXZ")\n')
    problems = _gate(enforced)
    assert any("alternatename +1" in p and "?h@@YAXXZ" in p for p in problems)
    # the edit made the tool's stamps stale; --restamp renews them and admits nothing new
    assert any("admitted before" in p and "--restamp" in p for p in problems)
    assert hatch_counters.main(["--restamp", UNIT]) == 1                  # the hand alias: not re-stamped
    problems = _gate(enforced)
    assert any("alternatename +1" in p and "?h@@YAXXZ" in p for p in problems)
    assert not any("_vtbl_00C5EE80" in p or "g_Va00E23300" in p for p in problems)


def test_rewrite_preserves_prior_blob_allowance_but_never_admits_a_hand_alias(enforced):
    # Mutants 36 + 37: admitting every token can conceal losing before=, because re-admitting
    # the old tool alias makes up for forgetting its prior blob. Include an unadmitted alias
    # in that SAME input: only the earlier tool allowance may survive the rewrite.
    source = enforced / UNIT
    with source.open("a", newline="\n") as handle:
        handle.write('#pragma comment(linker, "/alternatename:?prior@@YAXXZ=?g@@YAXXZ")\n'
                     '#pragma comment(linker, "/alternatename:?hand@@YAXXZ=?g@@YAXXZ")\n')
    hatch_counters.admit(UNIT, "fixture: checked prior alias", tokens={"?prior@@YAXXZ"})
    # The valid allowance is tied to this blob. --allow/imported allowances have no local
    # admission record; before= must preserve them while this tool changes the blob.
    hatch_counters._record_file().unlink()
    ok, _ = _land(enforced)
    assert ok
    problems = _gate(enforced)
    assert any("alternatename +1" in p and "?hand@@YAXXZ" in p for p in problems)
    assert not any("?prior@@YAXXZ" in p for p in problems)
    assert not any("_vtbl_00C5EE80" in p or "g_Va00E23300" in p for p in problems)


def test_a_rewrite_the_register_will_not_grant_is_restored(enforced, monkeypatch):
    original = (enforced / UNIT).read_bytes()
    register = (enforced / hatch_counters.BASELINE).read_bytes()

    def frozen(*args, **kwargs):
        raise SystemExit("hatch_counters: hatch 'alternatename' is frozen")
    monkeypatch.setattr(hatch_counters, "admit", frozen)
    ok, _ = _land(enforced)
    assert not ok
    assert (enforced / UNIT).read_bytes() == original
    assert (enforced / hatch_counters.BASELINE).read_bytes() == register


def test_a_rewrite_admit_wrote_but_the_gate_would_not_grant_is_restored(enforced, monkeypatch):
    # admit() really writes the register; ungranted(), the independent check, then disagrees:
    # the unit AND the register lines admit() wrote are put back
    original = (enforced / UNIT).read_bytes()
    register = (enforced / hatch_counters.BASELINE).read_bytes()
    real_admit = hatch_counters.admit
    wrote = []

    def admit(*args, **kwargs):
        got = real_admit(*args, **kwargs)
        wrote.append((enforced / hatch_counters.BASELINE).read_bytes())
        return got
    monkeypatch.setattr(hatch_counters, "admit", admit)
    monkeypatch.setattr(hatch_counters, "ungranted",
                        lambda path: {("alternatename", UNIT, "_vtbl_00C5EE80"): (1, 0)})
    ok, _ = _land(enforced)
    assert not ok
    assert wrote and wrote[0] != register                                 # admit() did write lines
    assert (enforced / UNIT).read_bytes() == original
    assert (enforced / hatch_counters.BASELINE).read_bytes() == register


def test_hatch_tokens_name_only_what_the_rewrite_writes():
    assert name_globals.hatch_tokens({"vtbl_00C5EE80", "g_Va00E23300", "TheGameLogic"}) == \
        {"_vtbl_00C5EE80", "g_Va00E23300"}


if __name__ == "__main__":
    unittest.main()
