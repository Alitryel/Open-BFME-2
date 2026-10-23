"""tools/rename.py collisions that are false rejects: each case below was a
real blocked rename, and each class is tested with its unsafe neighbours,
which stay refused. A miniature tree (a temporary git repository), so no
compiler is needed (verification is injected)."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal  # noqa: E402


@pytest.fixture(autouse=True)
def _evidence_gates_stubbed(monkeypatch):
    monkeypatch.setattr(rename, "check_agreement", lambda *a, **k: None)
    monkeypatch.setattr(rename, "check_canonical", lambda *a, **k: None)


def make_tree(root, files):
    for rel, text in files.items():
        path = root / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    subprocess.run(["git", "-C", str(root), "init", "-q"], check=True, capture_output=True)
    subprocess.run(["git", "-C", str(root), "add", "-A"], check=True, capture_output=True)
    return root


BASE_FILES = {
    "reverse/symbols.csv": "name,address,notes\n",
    "reverse/deleted_rows.csv": "name,target_rva,reason\n",
    "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
    "reverse/exports.csv": "ordinal,rva,target_rva,section,kind,name\n",
    "reverse/gate_baseline.txt": "",
}


def tree_of(tmp_path, functions, **sources):
    files = dict(BASE_FILES)
    files["reverse/functions.csv"] = "name,export_rva,target_rva,target_size,source,status,notes\n" + functions
    files.update(sources)
    return make_tree(tmp_path, files)


def plan_function(root, rva, new, **kwargs):
    ctx = rename.Context(root, object_scan=kwargs.pop("object_scan", False))
    return rename.plan_rename("function", ctx=ctx, rva=rva, new=new, basis="inferred",
                              evidence="agree:abc123", **kwargs)


# --------------------------------------------- name back-references (type digits)

@pytest.mark.parametrize("mangled", [
    # the same type again in argument 2: `0` is the TYPE table's first entry
    "?rva003BDE5D@ScriptActions@@QAEXABVAsciiString@@0@Z",
    "?Rva0032B389Join@@YA?AVAsciiString@@ABV1@0@Z",
    "?rva004D1C81@Rva004D1C81@@QAE?AURva004D1C81Iter@@PAURva004D1C81Node@@0@Z",
])
def test_type_table_digit_is_not_a_reference_to_the_identifier(mangled):
    _prefix, old, suffix = rename.split_function_name(mangled)
    assert not rename.refers_to_identifier(mangled, suffix)
    renamed = rename.rename_function_symbol(mangled, "Respelled")
    assert renamed == mangled.replace(old, "Respelled", 1)


@pytest.mark.parametrize("mangled", [
    "?rva00401000@@YAXPAV0@@Z",                       # the class is the identifier's fragment
    "?rva00401000@Widget@@QAEXAAV0@@Z",
    "?rva00401000@Widget@@QAEXPAVInner@0@@Z",         # a nested name continues from fragment 0
    "?rva00401000@Widget@@QAEPAU0@V0@@Z",
])
def test_name_reference_to_the_identifier_stays_refused(mangled):
    with pytest.raises(Refusal, match="back-reference"):
        rename.rename_function_symbol(mangled, "respelled")


def test_unreadable_symbol_keeps_the_textual_test():
    # outside the parser's subset (an unknown type letter): the textual test
    # still decides, and it cannot tell a type digit from a name reference
    odd = "?rva00401000@Widget@@QAEXPAUS@@0@Zq"
    with pytest.raises(rename.Unparsed):
        rename.fragments(odd)
    assert rename.refers_to_identifier(odd, odd.split("@", 1)[1])


def test_plan_clears_a_row_whose_signature_repeats_a_type(tmp_path):
    old = "?rva003BDE5D@ScriptActions@@QAEXABVAsciiString@@0@Z"
    tree = tree_of(
        tmp_path,
        f"{old},,0x003BDE5D,20,Code/Game/Actions.cpp,matched,address-derived\n",
        **{"Code/Game/Actions.cpp": "// cl: /O2\nvoid ScriptActions::rva003BDE5D(const AsciiString &a, const AsciiString &b) {}\n"})
    plan = plan_function(tree, 0x003BDE5D, "doIt")
    assert plan.new == "?doIt@ScriptActions@@QAEXABVAsciiString@@0@Z"
    assert "doIt" in plan.after["Code/Game/Actions.cpp"].decode()


# ------------------------------- game units that merely instantiate STLport

OWNER = "?rva00401000@Widget@@QAEHXZ"
STL_INST = ("?push_back@?$vector@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@_STL@@QAEXABQAUArmy@@@Z")
STL_PLAIN = "?_M_throw_length_error@?$_Vector_base@PAUArmy@@V?$allocator@PAUArmy@@@_STL@@@_STL@@QBEXXZ"
HOST_CPP = ("// cl: /O2\n// ?rva00401000@Widget@@QAEHXZ @ 0x00401000\n"
            "class Widget { public: int rva00401000(); };\nint Widget::rva00401000() { return 1; }\n")


def host_tree(tmp_path, *, source="Code/Game/Widget.cpp", extra_rows=(), notes="vendored=stlport-4.5.3; army vector",
              inst=STL_INST, own="address-derived"):
    rows = (f"{OWNER},,0x00401000,10,{source},matched,{own}\n"
            f"?count@Widget@@QAEHXZ,,0x00403000,6,{source},matched,real\n"
            f"{inst},,0x00402000,30,{source},matched,{notes}\n")
    rows += "".join(f"{name},,{addr},8,{source},matched,{n}\n" for name, addr, n in extra_rows)
    return tree_of(tmp_path, rows, **{source: HOST_CPP})


def test_unit_instantiating_stlport_over_its_own_types_is_not_vendored(tmp_path):
    tree = host_tree(tmp_path)
    ctx = rename.Context(tree, object_scan=False)
    assert not rename.is_vendored_path(ctx, "Code/Game/Widget.cpp")
    plan = plan_function(tree, 0x00401000, "countParts")
    assert plan.new == "?countParts@Widget@@QAEHXZ"
    assert plan.verify == ["Code/Game/Widget.cpp"]
    # the instantiation row itself is untouched
    assert STL_INST in plan.after["reverse/functions.csv"].decode()


@pytest.mark.parametrize("kwargs,why", [
    # nothing of the game's own in the file: upstream's unit
    (dict(own="vendored=stlport-4.5.3; the body"), "all rows vendored"),
    # another library's row keeps the whole unit vendored
    (dict(extra_rows=[("?gpConnect@@YAXXZ", "0x00404000", "vendored=gamespy-2004")]), "gamespy row"),
    # a plain (non-template) upstream function body is upstream's text
    (dict(extra_rows=[(STL_PLAIN, "0x00404000", "vendored=stlport-4.5.3")]), "plain stlport row"),
    # an STLport unit by name
    (dict(source="Code/Game/stlport_widget.cpp"), "stlport unit name"),
])
def test_other_vendored_mixes_stay_vendored(tmp_path, kwargs, why):
    if why == "plain stlport row":
        kwargs["extra_rows"] = [("?_M_foo@_Foo@_STL@@QAEXXZ", "0x00404000", "vendored=stlport-4.5.3")]
    tree = host_tree(tmp_path, **kwargs)
    source = kwargs.get("source", "Code/Game/Widget.cpp")
    ctx = rename.Context(tree, object_scan=False)
    assert rename.is_vendored_path(ctx, source), why
    with pytest.raises(Refusal, match="vendored"):
        plan_function(tree, 0x00401000, "countParts")


def test_vendored_dir_unit_stays_vendored_with_own_rows(tmp_path):
    tree = host_tree(tmp_path, source="Code/Libraries/Source/Lua/lvm.cpp")
    ctx = rename.Context(tree, object_scan=False)
    assert rename.is_vendored_path(ctx, "Code/Libraries/Source/Lua/lvm.cpp")


def test_a_word_the_instantiation_row_spells_is_still_shared(tmp_path):
    # renaming the class Army's helper would also respell `Army` in the vendored
    # template names; the shared-identifier test is what protects them
    inst = "?push_back@?$vector@PAUrva00401000@@V?$allocator@PAUrva00401000@@@_STL@@@_STL@@QAEXABQAUrva00401000@@@Z"
    tree = host_tree(tmp_path, inst=inst)
    with pytest.raises(Refusal, match="also spells"):
        plan_function(tree, 0x00401000, "countParts")
