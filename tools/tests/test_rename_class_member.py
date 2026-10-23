"""tools/rename.py's `class`, `member`, `param` and `local` kinds on a
miniature tree: a temporary git repository with small ledgers and sources, so
every rule runs without the real ledger or a compiler (verification is
injected). Real-tree --dry-run smokes for each kind close the file."""
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402


@pytest.fixture(autouse=True)
def _evidence_gates_stubbed(monkeypatch):
    """The agreement-record and canonical-evidence gates have their own tests
    (test_rename_fixes.py); these exercise everything else."""
    monkeypatch.setattr(rename, "check_agreement", lambda *a, **k: None)
    monkeypatch.setattr(rename, "check_canonical", lambda *a, **k: None)

OWNER = "Rva00401000Owner"
CTOR = f"??0{OWNER}@@QAE@XZ"

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
?count@{OWNER}@@QAEHXZ,,0x00401000,6,Code/Game/Widget.cpp,matched,
{CTOR},,0x00401010,8,Code/Game/Widget.cpp,matched,object-symbol={CTOR}
__ehhandler${CTOR},,0x00401020,4,Code/Game/Widget.cpp,matched,parent={CTOR}
?use@@YAHPAV{OWNER}@@@Z,,0x00402000,6,Code/Game/User.cpp,matched,
?lit@@YAXXZ,,0x00403000,6,Code/Game/Lit.cpp,matched,
?get@Rva00404000Exp@@QAEHXZ,,0x00404000,6,Code/Game/Exp.cpp,matched,
?sum@@YAHHH@Z,,0x00405000,6,Code/Game/Params.cpp,matched,
?slow@@YAHH@Z,,0x00406000,6,Code/Game/Slow.cpp,matched,
?other@@YAHPAUOther@@@Z,,0x00407000,6,Code/Game/Other.cpp,matched,
?reg@Rva00408000Reg@@QAEXXZ,,0x00408000,6,Code/Game/Reg.cpp,matched,
"""
DATA_ROWS = f"""name,address,address_kind,size,section,source,status,evidence,model
??_7{OWNER}@@6B@,0x00A01000,rva,4,.rdata,Code/Game/Widget.cpp,matched,vtable,m
"""
OWNER_H = f"""#pragma once
// {OWNER}: the widget's owner record.
struct {OWNER} {{
    {OWNER}();
    int count();
    int m_x2C;
    int health;
    static int s_00A02000;
}};
"""
WIDGET = f"""// cl: /O2
#include "Owner.h"
// ?count@{OWNER}@@QAEHXZ @ 0x00401000
int {OWNER}::count() {{ return m_x2C; }}
{OWNER}::{OWNER}() {{ m_x2C = 0; health = 1; }}
"""
USER = f"""#include "Owner.h"
int use({OWNER} *p) {{ return p->m_x2C; }}
"""
OTHER = """struct Other { int m_x2C; };
int other(Other *o) { return o->m_x2C; }
"""
PARAMS = """// cl: /O2
int g_total;
int sum(int param_1, int param_2) {
    // param_1 is the left operand
    int iVar3 = param_1 + param_2;
    return iVar3;
}
int twice(int param_1) { return param_1 * 2; }
"""
SLOW = """// cl: /Od
int slow(int param_1) {
    int iVar1 = param_1;
    return iVar1;
}
"""


def _git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True,
                          text=True).stdout


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/data_rows.csv": DATA_ROWS,
        "reverse/symbols.csv": f"name,address,notes\n?count@{OWNER}@@QAEHXZ,0x00801000,pin\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/exports.csv": "name,rva\n?get@Rva00404000Exp@@QAEHXZ,0x00404000\n",
        "reverse/canonical_classes.csv": "class,header,notes\nRva00408000Reg,Code/Game/Reg.h,registered\n",
        "reverse/flag_overrides.csv": "source,flags,rows,default_lost,reason\n",
        "Code/Game/Owner.h": OWNER_H,
        "Code/Game/Widget.cpp": WIDGET,
        "Code/Game/User.cpp": USER,
        "Code/Game/Other.cpp": OTHER,
        "Code/Game/Lit.cpp": 'struct Rva00403000Lit { int a; };\nvoid lit() { const char *s = "Rva00403000Lit"; }\n',
        "Code/Game/Exp.cpp": "struct Rva00404000Exp { int get(); };\nint Rva00404000Exp::get() { return 0; }\n",
        "Code/Game/Reg.cpp": "struct Rva00408000Reg { void reg(); };\nvoid Rva00408000Reg::reg() {}\n",
        "Code/Game/Params.cpp": PARAMS,
        "Code/Game/Slow.cpp": SLOW,
        "Code/gen_asm/gen_0001.asm": "x PROC\n",
    }
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    return tmp_path


def ctx_of(root):
    return rename.Context(root, object_scan=False)


def snapshot(root):
    files = {p.relative_to(root).as_posix(): p.read_bytes()
             for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}
    files.pop("reverse/.add_match.lock", None)
    return files


def read(root, rel):
    return (root / rel).read_text(encoding="utf-8")


def plan(root, kind, **kwargs):
    kwargs.setdefault("basis", "inferred")
    kwargs.setdefault("evidence", "agree:abc")
    return rename.plan_rename(kind, ctx=ctx_of(root), **kwargs)


# ---------------------------------------------------------------- mangled fragments

@pytest.mark.parametrize("symbol,expected", [
    ("??0Old@@QAE@XZ", "??0New@@QAE@XZ"),
    ("??1Old@@UAE@XZ", "??1New@@UAE@XZ"),
    ("??_GOld@@UAEPAXI@Z", "??_GNew@@UAEPAXI@Z"),
    ("??_7Old@@6B@", "??_7New@@6B@"),
    ("?f@Old@@QAEXXZ", "?f@New@@QAEXXZ"),
    ("?f@Inner@Old@@QAEXXZ", "?f@Inner@New@@QAEXXZ"),
    ("?f@@YAXPAVOld@@@Z", "?f@@YAXPAVNew@@@Z"),
    ("?f@@YAXABUOld@@@Z", "?f@@YAXABUNew@@@Z"),
    ("?f@@YAXW4Old@@@Z", "?f@@YAXW4New@@@Z"),
    ("?f@@YA?AVOld@@XZ", "?f@@YA?AVNew@@XZ"),
    ("?f@?$vector@PAVOld@@@@QAEXXZ", "?f@?$vector@PAVNew@@@@QAEXXZ"),
    ("?f@?$Old@H@@QAEXXZ", "?f@?$New@H@@QAEXXZ"),
    ("?OldX@@YAXXZ", "?OldX@@YAXXZ"),
    ("?f@XOld@@QAEXXZ", "?f@XOld@@QAEXXZ"),
    ("?f@Olden@@QAEXXZ", "?f@Olden@@QAEXXZ"),
])
def test_type_fragment_rewrite(symbol, expected):
    assert rename.type_fragment_re("Old").sub("New", symbol) == expected


def test_class_token_in_source_text():
    token = rename.class_token_re("Old")
    text = ('#include "Old.h"\nOld *p; // see ?f@@YAXPAVOld@@@Z\n'
            '#pragma comment(linker, "/alternatename:??0Old@@QAE@XZ=x")\nOlden q; "Old";\n')
    new, counts, strings, includes = rename.rewrite_tokens(text, token, "New")
    assert '#include "Old.h"' in new and "New *p;" in new and "PAVNew@@" in new
    assert "??0New@@QAE@XZ" in new and "Olden q" in new
    assert strings == ['"Old"'] and includes == ['#include "Old.h"']
    assert counts == {"code": 1, "comment": 1, "pragma": 1}


@pytest.mark.parametrize("mangled,scope", [
    ("?sum@@YAHHH@Z", "sum"),
    ("?count@Widget@@QAEHXZ", "Widget::count"),
    ("?f@Inner@Outer@@QAEXXZ", "Outer::Inner::f"),
    ("??0Widget@@QAE@XZ", "Widget::Widget"),
    ("??1Widget@@QAE@XZ", "Widget::~Widget"),
    ("_main", "main"),
    ("??_GWidget@@UAEPAXI@Z", None),
])
def test_scope_of(mangled, scope):
    assert rename.scope_of(mangled) == scope


# ---------------------------------------------------------------- class

def test_class_plan_rewrites_every_name_and_view(tree):
    p = plan(tree, "class", name=OWNER, new="WidgetOwner")
    assert sorted(o for o, _n, _a in p.renamed_rows) == sorted(
        [f"?count@{OWNER}@@QAEHXZ", CTOR, f"__ehhandler${CTOR}", f"?use@@YAHPAV{OWNER}@@@Z"])
    assert ("?use@@YAHPAVWidgetOwner@@@Z" in {n for _o, n, _a in p.renamed_rows})
    assert p.renamed_pins == [(f"?count@{OWNER}@@QAEHXZ", "?count@WidgetOwner@@QAEHXZ", "0x00801000")]
    assert p.renamed_data == [(f"??_7{OWNER}@@6B@", "??_7WidgetOwner@@6B@", 0x00A01000)]
    functions = p.after["reverse/functions.csv"].decode()
    assert "parent=??0WidgetOwner@@QAE@XZ" in functions and "object-symbol=??0WidgetOwner@@QAE@XZ" in functions
    assert OWNER not in functions
    assert sorted(p.source_counts) == ["Code/Game/Owner.h", "Code/Game/User.cpp", "Code/Game/Widget.cpp"]
    assert p.verify == ["Code/Game/User.cpp", "Code/Game/Widget.cpp"]
    deleted = p.after["reverse/deleted_rows.csv"].decode()
    assert deleted.count("Renamed to") == 5
    assert f'??_7{OWNER}@@6B@,0x00A01000,"Renamed to ??_7WidgetOwner@@6B@ by tools/rename.py (inferred)"' in deleted
    basis = p.after["reverse/name_basis.csv"].decode().splitlines()
    assert basis[0] == rename.NAME_BASIS_HEADER
    assert basis[1] == f"class,{OWNER},WidgetOwner,inferred,agree:abc,Code/Game/Owner.h,"
    assert f"class:{OWNER}" in p.claims and 0x00401000 in p.claims
    assert p.subject() == f"Rename {OWNER} to WidgetOwner (inferred)"


def test_class_apply_and_rollback(tree):
    before = snapshot(tree)
    p = plan(tree, "class", name=OWNER, new="WidgetOwner")
    with pytest.raises(VerifyFailed):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda _c, _s: False)
    assert snapshot(tree) == before
    p = plan(tree, "class", name=OWNER, new="WidgetOwner")
    seen = []
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda _c, s: seen.append(list(s)) or True)
    assert seen == [["Code/Game/User.cpp", "Code/Game/Widget.cpp"]]
    assert "struct WidgetOwner {" in read(tree, "Code/Game/Owner.h")
    assert "WidgetOwner::WidgetOwner()" in read(tree, "Code/Game/Widget.cpp")
    assert '#include "Owner.h"' in read(tree, "Code/Game/Widget.cpp")
    assert read(tree, "Code/Game/Other.cpp") == OTHER


def test_class_exception_restores(tree):
    before = snapshot(tree)
    p = plan(tree, "class", name=OWNER, new="WidgetOwner")

    def boom(_ctx, _sources):
        raise RuntimeError("compiler crashed")
    with pytest.raises(RuntimeError):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=boom)
    assert snapshot(tree) == before


@pytest.mark.parametrize("name,new,basis,match", [
    ("Rva00404000Exp", "Exporter", "inferred", "retail export"),
    ("Rva00403000Lit", "Literal", "inferred", "string literal"),
    ("Rva00408000Reg", "Registry", "inferred", "canonical_classes"),
    (OWNER, "Other", "inferred", "already"),
    (OWNER, "Rva00999999Thing", "inferred", "placeholder"),
    (OWNER, "WidgetOwner", "maybe", "--basis"),
    ("Other", "OtherThing", "inferred", "real name"),
    ("Nowhere00401000", "Somewhere", "inferred", "no class"),
    ("RTTI", "x", "inferred", "placeholder"),
])
def test_class_refusals(tree, name, new, basis, match):
    with pytest.raises(Refusal, match=match):
        plan(tree, "class", name=name, new=new, basis=basis)


def test_class_refuses_rtti_and_recorded_canonical(tree):
    with pytest.raises(Refusal, match="RTTI"):
        plan(tree, "class", name="INIException", new="IniError", basis="canonical:zh", evidence="zh")
    (tree / "reverse/name_basis.csv").write_text(
        rename.NAME_BASIS_HEADER + f"\nclass,Rva1,{OWNER},canonical:zh,zh header,x,\n")
    with pytest.raises(Refusal, match="recorded canonical"):
        plan(tree, "class", name=OWNER, new="WidgetOwner", basis="canonical:wb", evidence="wb")


def test_class_refuses_word_shared_with_a_function(tree):
    path = tree / "reverse/functions.csv"
    path.write_text(path.read_text() + f"?{OWNER}@@YAXXZ,,0x00409000,4,Code/Game/User.cpp,matched,\n")
    with pytest.raises(Refusal, match="identifier of"):
        plan(tree, "class", name=OWNER, new="WidgetOwner")


def test_class_refuses_generated_and_max_files(tree):
    with pytest.raises(Refusal, match="max-files"):
        plan(tree, "class", name=OWNER, new="WidgetOwner", max_files=2)
    (tree / "Code/gen_small/gen_x.cpp").parent.mkdir(parents=True)
    (tree / "Code/gen_small/gen_x.cpp").write_text(f"struct {OWNER};\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="generated"):
        plan(tree, "class", name=OWNER, new="WidgetOwner")


def test_class_refuses_frozen_key(tree):
    (tree / "reverse/dir32_whitelist.txt").write_text(f"??_7{OWNER}@@6B@\n")
    _git(tree, "add", "-A")
    with pytest.raises(Refusal, match="frozen"):
        plan(tree, "class", name=OWNER, new="WidgetOwner")


def test_canonical_basis_may_replace_inferred_class(tree):
    p = plan(tree, "class", name=OWNER, new="WidgetOwner")
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda _c, _s: True)
    with pytest.raises(Refusal, match="real name"):
        plan(tree, "class", name="WidgetOwner", new="Gadget")
    p = plan(tree, "class", name="WidgetOwner", new="Gadget", basis="canonical:wb", evidence="wb assert")
    assert p.renamed_rows


# ---------------------------------------------------------------- member

def test_member_rename_touches_views_and_users_only(tree):
    p = plan(tree, "member", cls=OWNER, member="m_x2C", new="m_count")
    assert sorted(p.source_counts) == ["Code/Game/Owner.h", "Code/Game/User.cpp", "Code/Game/Widget.cpp"]
    assert "Code/Game/Other.cpp" not in p.after
    assert p.verify == ["Code/Game/User.cpp", "Code/Game/Widget.cpp"]
    assert not any(rel.startswith("reverse/") and rel != "reverse/name_basis.csv" for rel in p.after)
    row = p.after["reverse/name_basis.csv"].decode().splitlines()[1]
    assert row == f"member,{OWNER}::m_x2C,{OWNER}::m_count,inferred,agree:abc,Code/Game/Owner.h,"
    assert p.claims == [f"class:{OWNER}"]
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda _c, _s: True)
    assert "p->m_count" in read(tree, "Code/Game/User.cpp")
    assert "return m_count;" in read(tree, "Code/Game/Widget.cpp")
    assert read(tree, "Code/Game/Other.cpp") == OTHER


@pytest.mark.parametrize("member,new,basis,match", [
    ("s_00A02000", "s_pool", "inferred", "static"),
    ("m_x30", "m_thing", "inferred", "no view"),
    ("health", "hitPoints", "inferred", "real name"),
    ("m_x2C", "health", "inferred", "already a name"),
    ("m_x2C", "field_44", "inferred", "placeholder"),
])
def test_member_refusals(tree, member, new, basis, match):
    with pytest.raises(Refusal, match=match):
        plan(tree, "member", cls=OWNER, member=member, new=new, basis=basis)


def test_member_refuses_ambiguous_file(tree):
    (tree / "Code/Game/User.cpp").write_text(USER + "struct Local { int m_x2C; };\n")
    with pytest.raises(Refusal, match="ambiguous"):
        plan(tree, "member", cls=OWNER, member="m_x2C", new="m_count")


# ---------------------------------------------------------------- params and locals

def test_param_rename_is_confined_to_one_function(tree):
    p = plan(tree, "param", source="Code/Game/Params.cpp", function="sum", name="param_1", new="lhs")
    assert p.rva == 0x00405000 and p.verify == ["Code/Game/Params.cpp"]
    text = p.after["Code/Game/Params.cpp"].decode()
    assert "int sum(int lhs, int param_2)" in text and "// lhs is the left operand" in text
    assert "int iVar3 = lhs + param_2;" in text
    assert "int twice(int param_1) { return param_1 * 2; }" in text
    row = p.after["reverse/name_basis.csv"].decode().splitlines()[1]
    assert row == "param,sum::param_1,sum::lhs,inferred,agree:abc,Code/Game/Params.cpp,0x00405000"
    assert p.claims == [0x00405000, "file:Code/Game/Params.cpp"]
    rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda _c, _s: True)
    with pytest.raises(Refusal, match="real name"):
        plan(tree, "param", source="Code/Game/Params.cpp", function="sum", name="lhs", new="left")


def test_param_by_rva_and_local(tree):
    p = plan(tree, "param", source="Code/Game/Params.cpp", rva=0x00405000, name="param_2", new="rhs")
    assert "int sum(int param_1, int rhs)" in p.after["Code/Game/Params.cpp"].decode()
    p = plan(tree, "local", source="Code/Game/Params.cpp", function="sum", name="iVar3", new="result")
    text = p.after["Code/Game/Params.cpp"].decode()
    assert "int result = param_1 + param_2;" in text and "return result;" in text
    before = snapshot(tree)
    with pytest.raises(VerifyFailed):
        rename.apply_rename(p, ctx=ctx_of(tree), verify=lambda _c, _s: False)
    assert snapshot(tree) == before


@pytest.mark.parametrize("kind,source,function,name,new,match", [
    ("local", "Code/Game/Slow.cpp", "slow", "iVar1", "value", "without optimisation"),
    ("param", "Code/Game/Slow.cpp", "slow", "param_1", "value", None),
    ("param", "Code/Game/Params.cpp", "sum", "param_1", "g_total", "already a name"),
    ("param", "Code/Game/Params.cpp", "sum", "param_1", "param_2", "placeholder"),
    ("param", "Code/Game/Params.cpp", "sum", "iVar3", "value", "not a parameter"),
    ("local", "Code/Game/Params.cpp", "sum", "param_1", "value", "is a parameter"),
    ("param", "Code/Game/Params.cpp", "nothing", "param_1", "value", "no function"),
    ("param", "Code/Game/Other.cpp", "other", "o", "target", None),
    ("param", "Code/gen_asm/gen_0001.asm", "x", "a", "b", "generated"),
    ("param", "Code/Game/Owner.h", "x", "a", "b", "owns no matched"),
])
def test_scoped_refusals(tree, kind, source, function, name, new, match):
    if match is None:
        assert plan(tree, kind, source=source, function=function, name=name, new=new).verify == [source]
        return
    with pytest.raises(Refusal, match=match):
        plan(tree, kind, source=source, function=function, name=name, new=new)


def test_local_flags_last_one_wins(tree):
    # build.py's base -O2 holds when the file has no `// cl:` line ...
    (tree / "Code/Game/Params.cpp").write_text(PARAMS.replace("// cl: /O2\n", ""))
    assert plan(tree, "local", source="Code/Game/Params.cpp", function="sum", name="iVar3", new="result")
    # ... and a flag_overrides.csv -Od row overrides it.
    (tree / "reverse/flag_overrides.csv").write_text("source,flags,rows,default_lost,reason\n"
                                                   "Code/Game/Params.cpp,-Od,1,1,region\n")
    with pytest.raises(Refusal, match="without optimisation"):
        plan(tree, "local", source="Code/Game/Params.cpp", function="sum", name="iVar3", new="result")
    assert not rename.optimized([]) and rename.optimized(["-O2", "-Od", "-O1"])


def test_scoped_refuses_outer_meaning(tree):
    (tree / "Code/Game/Params.cpp").write_text(PARAMS.replace("int g_total;", "int iVar3;"))
    with pytest.raises(Refusal, match="global"):
        plan(tree, "local", source="Code/Game/Params.cpp", function="sum", name="iVar3", new="result")
    # a member of an UNRELATED class that an included header declares is not what a free
    # function's parameter of that name means (test_rename_collisions has the cases) ...
    (tree / "Code/Game/Params.cpp").write_text('#include "Owner.h"\n' + PARAMS.replace("param_2", "m_x2C"))
    assert plan(tree, "param", source="Code/Game/Params.cpp", function="sum", name="m_x2C", new="rhs")
    # ... but it is, to a method of that class or of a derived one
    (tree / "Code/Game/Params.cpp").write_text(
        '#include "Owner.h"\nint Rva00401000Owner::count(int m_x2C) { return m_x2C; }\n' + PARAMS)
    with pytest.raises(Refusal, match="included header"):
        plan(tree, "param", source="Code/Game/Params.cpp", function="Rva00401000Owner::count",
             name="m_x2C", new="rhs")


# ---------------------------------------------------------------- CLI

@pytest.mark.parametrize("argv", [
    ["class", "--name", OWNER, "--new", "WidgetOwner"],
    ["member", "--class", OWNER, "--member", "m_x2C", "--new", "m_count"],
    ["param", "--source", "Code/Game/Params.cpp", "--function", "sum", "--name", "param_1", "--new", "lhs"],
    ["local", "--source", "Code/Game/Params.cpp", "--rva", "0x00405000", "--name", "iVar3", "--new", "result"],
])
def test_cli_dry_run_writes_nothing(tree, argv, capsys):
    before = snapshot(tree)
    code = rename.main(argv + ["--basis", "inferred", "--evidence", "agree:abc", "--dry-run",
                               "--no-claim", "--no-object-scan", "--root", str(tree)])
    assert code == 0, capsys.readouterr()
    assert "nothing written" in capsys.readouterr().out
    assert snapshot(tree) == before


def test_cli_refusal_exit_code(tree, capsys):
    code = rename.main(["class", "--name", "Rva00404000Exp", "--new", "Exporter", "--basis", "inferred",
                        "--evidence", "x", "--dry-run", "--no-claim", "--root", str(tree)])
    assert code == 2 and "retail export" in capsys.readouterr().err


# ---------------------------------------------------------------- real tree

REAL = rename.ROOT


def _real_dry_run(argv, capsys):
    code = rename.main(argv + ["--basis", "inferred", "--evidence", "smoke", "--dry-run", "--no-claim"])
    out = capsys.readouterr()
    assert code == 0, out.err
    assert "nothing written" in out.out
    return out.out


SMOKES = [
    (["class", "--name", "Rva0040ADDD", "--new", "AwardRecordView", "--no-object-scan"],
     "Code/GameEngine/Source/Common/AwardSystemManager.cpp"),
    (["member", "--class", "Rva00362EC7", "--member", "m_0C", "--new", "m_markerHandle"],
     "Code/GameClient/Drawable/Update/RadarMarkerClientUpdateCtor.cpp"),
    (["param", "--source", "Code/GameEngine/Source/Common/BfmeConv1173.cpp", "--rva", "0x0066DAE0",
      "--name", "a1", "--new", "target"], "Code/GameEngine/Source/Common/BfmeConv1173.cpp"),
    (["local", "--source", "Code/GameEngine/Source/Common/BfmeCombine1236.cpp", "--function",
      "bfmeCombine1236", "--name", "a4", "--new", "rowScale"], "Code/GameEngine/Source/Common/BfmeCombine1236.cpp"),
]


@pytest.mark.parametrize("argv,source", SMOKES, ids=[s[0][0] for s in SMOKES])
def test_real_tree_dry_run(argv, source, capsys):
    """One real candidate per kind, planned against the live ledger (the tree
    moves: a candidate someone already renamed is skipped, not failed)."""
    path = REAL / source
    words = [argv[i + 1] for i, arg in enumerate(argv) if arg in ("--name", "--member", "--class")]
    if not path.exists() or not all(word in path.read_text(errors="replace") for word in words):
        pytest.skip(f"smoke candidate in {source} is gone")
    out = _real_dry_run(argv, capsys)
    assert f"verify (1): ./build.sh {source}" in out
    assert "reverse/name_basis.csv" in out


# ------------------------------------- in-class prototypes (trial-1 finding)
# A param rename respelled only the definition, so the class's own prototype
# kept the old word (BfmeConv1173.cpp: `bool bfmeHit1173(void *a1, void *a2);`).

PROTO = """// cl: /O2
class Hitter {
public:
    bool hit(void *a1, void *a2);
    bool hit(void *a1);
    void take(int (*fn)(int), void *a1);
};
bool Hitter::hit(void *a1, void *a2) { return a1 == a2; }
"""


def _proto_tree(tree):
    (tree / "Code/Game/Proto.cpp").write_text(PROTO)
    with (tree / "reverse/functions.csv").open("a") as handle:
        handle.write("?hit@Hitter@@QAE_NPAX0@Z,,0x00409000,10,Code/Game/Proto.cpp,matched,\n")
    return tree


def test_param_rename_respells_the_matching_prototype(tree):
    p = plan(_proto_tree(tree), "param", source="Code/Game/Proto.cpp", function="Hitter::hit", name="a1",
             new="key")
    text = p.after["Code/Game/Proto.cpp"].decode()
    assert "bool hit(void *key, void *a2);" in text            # same arity: respelled
    assert "bool hit(void *a1);" in text                       # other overload: untouched
    assert "void take(int (*fn)(int), void *a1);" in text      # other method: untouched
    assert "bool Hitter::hit(void *key, void *a2) { return key == a2; }" in text
    assert p.source_counts["Code/Game/Proto.cpp"]["code"] == 3


def test_param_rename_leaves_a_prototype_with_another_name_at_that_position(tree):
    _proto_tree(tree)
    path = tree / "Code/Game/Proto.cpp"
    path.write_text(path.read_text().replace("bool hit(void *a1, void *a2);", "bool hit(void *p, void *a2);"))
    text = plan(tree, "param", source="Code/Game/Proto.cpp", function="Hitter::hit", name="a1",
                new="key").after["Code/Game/Proto.cpp"].decode()
    assert "bool hit(void *p, void *a2);" in text and "bool Hitter::hit(void *key, void *a2)" in text
