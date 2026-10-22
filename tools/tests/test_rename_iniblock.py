"""canonical:iniblock: the retail INI block registration names exactly the
parse callback registered for a token, under the documented name, and nothing
else (tools/ini_blocks.py, reverse/ini_blocks.tsv)."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
sys.path.insert(0, str(Path(__file__).resolve().parent))

import rename  # noqa: E402
from rename import Refusal  # noqa: E402
from test_rename_fixes import make_tree, function_plan, ctx_of  # noqa: E402

HEADER = "token\ttoken_rva\tentry_rva\tparse_rva\tcurrent_name\tname\tname_source\n"


def blocks(*rows):
    return {rename.INI_BLOCKS: HEADER + "".join("\t".join(r) + "\n" for r in rows)}


ROW = ("Widget", "0x00700000", "0x00800000", "0x00401000", "?Rva00401000@Widget@@QAEHH@Z",
       "countParts", "derived")


def test_iniblock_is_a_canonical_kind():
    assert "iniblock" in rename.CANONICAL_KINDS


def test_iniblock_accepts_the_registered_callback_under_its_name(tmp_path):
    root = make_tree(tmp_path, blocks(ROW))
    plan = function_plan(root, basis="canonical:iniblock", evidence="retail INI block Widget")
    assert plan.basis == "canonical:iniblock"


def test_iniblock_refuses_another_name(tmp_path):
    root = make_tree(tmp_path, blocks(ROW))
    with pytest.raises(Refusal, match="its name is countParts"):
        function_plan(root, new="partCount", basis="canonical:iniblock", evidence="block Widget")


def test_iniblock_refuses_an_unregistered_address(tmp_path):
    row = ROW[:3] + ("0x00403000",) + ROW[4:]
    root = make_tree(tmp_path, blocks(row))
    with pytest.raises(Refusal, match="registers no block parser"):
        function_plan(root, basis="canonical:iniblock", evidence="block Widget")


def test_iniblock_refuses_without_the_record(tmp_path):
    root = make_tree(tmp_path)
    with pytest.raises(Refusal, match="registers no block parser"):
        function_plan(root, basis="canonical:iniblock", evidence="block Widget")


def test_iniblock_needs_the_token_cited(tmp_path):
    root = make_tree(tmp_path, blocks(ROW))
    with pytest.raises(Refusal, match="naming the block token"):
        function_plan(root, basis="canonical:iniblock", evidence="the INI table")
    with pytest.raises(Refusal, match="naming the block token"):
        function_plan(root, basis="canonical:iniblock", evidence="block WidgetSet")


def test_iniblock_refuses_a_duplicate_registration(tmp_path):
    root = make_tree(tmp_path, blocks(ROW, ("Gadget",) + ROW[1:]))
    with pytest.raises(Refusal, match="registers no block parser"):
        function_plan(root, basis="canonical:iniblock", evidence="block Widget")


def test_iniblock_names_functions_only(tmp_path):
    root = make_tree(tmp_path, blocks(ROW))
    with pytest.raises(Refusal):
        rename.plan_rename("class", ctx=ctx_of(root), name="Rva00500000", new="Barrier",
                           basis="canonical:iniblock", evidence="block Widget")


def test_committed_ini_blocks_reproduce_from_game_dat():
    import ini_blocks
    if not ini_blocks.EXE.exists():
        pytest.skip("retail game.dat not present")
    assert subprocess.run([sys.executable, str(TOOLS / "ini_blocks.py"), "--check"]).returncode == 0


def test_iniblock_refuses_a_stale_record(tmp_path):
    row = ROW[:4] + ("?Rva00401000Other@@YAXPAVINI@@@Z",) + ROW[5:]
    root = make_tree(tmp_path, blocks(row))
    with pytest.raises(Refusal, match="regenerate"):
        function_plan(root, basis="canonical:iniblock", evidence="block Widget")


def test_iniblock_replaces_only_a_placeholder(tmp_path):
    row = ("Widget", "0x00700000", "0x00800000", "0x00403000", "?count@Widget@@QAEHXZ", "countAll", "derived")
    root = make_tree(tmp_path, blocks(row))
    with pytest.raises(Refusal, match="only a placeholder"):
        function_plan(root, rva=0x00403000, new="countAll", basis="canonical:iniblock", evidence="block Widget")


# ------------------------- a real name the reference block tables contradict

ZH = rename.INI_REFERENCE_TABLES[0][0]
B1 = rename.INI_REFERENCE_TABLES[1][0]
REAL = ("Widget", "0x00700000", "0x00800000", "0x00403000", "?count@Widget@@QAEHXZ", "countAll", ZH + ":2")


def contradicted(row=REAL, zh='{ "Gadget", Widget::count },\n{ "Widget", Widget::countAll },\n', b1=None):
    extra = blocks(row)
    extra[ZH] = zh
    if b1 is not None:
        extra[B1] = b1
    return extra


def real_plan(root):
    return function_plan(root, rva=0x00403000, new="countAll", basis="canonical:iniblock",
                         evidence="retail INI block Widget; ZH INI.cpp gives count to Gadget")


def test_iniblock_replaces_a_real_name_the_tables_give_another_token(tmp_path):
    assert real_plan(make_tree(tmp_path, contradicted())).basis == "canonical:iniblock"


def test_iniblock_contradiction_needs_a_cited_not_derived_name(tmp_path):
    root = make_tree(tmp_path, contradicted(row=REAL[:6] + ("derived",)))
    with pytest.raises(Refusal):
        real_plan(root)


def test_iniblock_contradiction_needs_the_cited_table_to_name_the_target(tmp_path):
    root = make_tree(tmp_path, contradicted(zh='{ "Gadget", Widget::count },\n'))
    with pytest.raises(Refusal):
        real_plan(root)


def test_iniblock_contradiction_needs_the_old_name_given_to_another_token(tmp_path):
    root = make_tree(tmp_path, contradicted(zh='{ "Widget", Widget::countAll },\n'))
    with pytest.raises(Refusal):
        real_plan(root)


def test_iniblock_contradiction_refuses_when_any_table_gives_the_old_name_this_token(tmp_path):
    root = make_tree(tmp_path, contradicted(b1='REGISTER_BLOCK( Widget, "Widget", Widget::count );\n'))
    with pytest.raises(Refusal):
        real_plan(root)
