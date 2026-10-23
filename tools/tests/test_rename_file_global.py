"""tools/rename.py's `file` and `global` kinds on a miniature tree: a temporary
git repository with small ledgers and sources, so every rule runs without the
real ledger or a compiler (verification is injected). A real-tree --dry-run
smoke for each kind closes the file."""
import re
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

UNIT = "Code/Game/WidgetRva00401000.cpp"
MOVED = "Code/Game/Widget_count.cpp"
DATA = "?g_00A01000@@3HA"
DATA_NEW = "?g_widgetCount@@3HA"

FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
?count@Widget@@QAEHXZ,,0x00401000,6,{UNIT},matched,reads {DATA}
?use@@YAHXZ,,0x00402000,6,Code/Game/User.cpp,matched,
?inc@@YAHXZ,,0x00403000,6,Code/Game/Inc.cpp,matched,
?flagged@@YAXXZ,,0x00404000,6,Code/Game/FlagRva00404000.cpp,matched,
?filed@@YAXXZ,,0x00405000,6,Code/Game/FileRva00405000.cpp,matched,
?real@@YAXXZ,,0x00406000,6,Code/Game/RealName.cpp,matched,
?lit@@YAXXZ,,0x00407000,6,Code/Game/LitRva00407000.cpp,matched,
"""
DATA_ROWS = f"""name,address,address_kind,size,section,source,status,evidence,model
{DATA},0x00A01000,rva,4,.data,{UNIT},matched,"only ref, {DATA} pushed",m
?g_00A02000@@3HA,0x00E02000,va,4,.data,{UNIT},matched,converged one,m
?g_00A03000@@3HA,0x00A03000,rva,4,.data,Code/Game/LitRva00407000.cpp,matched,lit,m
?g_00A04000@@3HA,0x00A04000,rva,4,.data,Code/Game/RealName.cpp,matched,frozen,m
"""
TU_MAP = f"""rva,size,kind,tu,confidence,by,evidence,source
0x00401000,6,code,Code/Game/Widget.cpp,approved,S,"S={UNIT}",{UNIT}
0x00406000,6,code,Code/Game/RealName.cpp,approved,F,F,Code/Game/RealName.cpp
0x00402000,6,code,,,-,,Code/Game/User.cpp
"""
SOURCES = f"""# guide inputs
INPUT += {UNIT}
INPUT += Code/Game/User.cpp
"""
WIDGET = f"""// cl: /O2
// ?count@Widget@@QAEHXZ @ 0x00401000
int g_00A01000;
int g_00A02000;
struct Widget {{ int count(); }};
int Widget::count() {{ return g_00A01000; }}
"""
USER = """extern int g_00A01000;
int use() { return g_00A01000 + 1; }
"""
HEADER = "extern int g_00A01000;\n"
INC = '#include "Globals.h"\nint inc() { return 0; }\n'
LIT = 'int g_00A03000;\nvoid lit() { const char *s = "g_00A03000"; }\n'


def _git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True,
                          text=True).stdout


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/data_rows.csv": DATA_ROWS,
        "reverse/symbols.csv": f"name,address,notes\n{DATA},0x00E01000,data pin\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/tu_map.csv": TU_MAP,
        "reverse/data_converged.csv": "address,name,evidence\n0x00A02000,?g_00A02000@@3HA,link\n",
        "reverse/flag_overrides.csv": "source,flags,rows,default_lost,reason\n"
                                      "Code/Game/FlagRva00404000.cpp,-O2,1,1,region\n",
        "reverse/data_check_baseline.txt": "# source\tcheck\tsymbol\taddress\n"
                                           "Code/Game/RealName.cpp\twrong-name\t?g_00A04000@@3HA\t0x00A04000\n",
        "reverse/link_status.csv": f"source,linked\n{UNIT},yes\n",
        "docs/doxygen/sources.cfg": SOURCES,
        UNIT: WIDGET,
        "Code/Game/User.cpp": USER,
        "Code/Game/Globals.h": HEADER,
        "Code/Game/Inc.cpp": INC,
        "Code/Game/FlagRva00404000.cpp": "void flagged() {}\n",
        "Code/Game/FileRva00405000.cpp": 'const char *f() { return __FILE__; }\nvoid filed() {}\n',
        "Code/Game/RealName.cpp": "int g_00A04000;\nvoid real() {}\n",
        "Code/Game/LitRva00407000.cpp": LIT,
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
    status = [line for line in _git(root, "status", "--porcelain").splitlines() if ".add_match.lock" not in line]
    return files, status


def plan_file(root, **overrides):
    args = dict(source=UNIT, new="Widget_count", basis="inferred", evidence="mechanical: sole row")
    args.update(overrides)
    return rename.plan_rename("file", ctx=ctx_of(root), **args)


def plan_global(root, **overrides):
    args = dict(name=DATA, new="g_widgetCount", basis="inferred", evidence="agree:abc")
    args.update(overrides)
    return rename.plan_rename("global", ctx=ctx_of(root), **args)


def ok(ctx, sources):
    return True


# ------------------------------------------------------------ csv field surgery

def test_repoint_column_keeps_every_other_byte():
    raw = (b'a,source,notes\n1,Code/X.cpp,"see Code/X.cpp, twice"\n2,"Code/X.cpp",x\n'
           b'3,Code/X.cppz,x\n4,Code/Y.cpp,Code/X.cpp\n')
    out, count = rename.repoint_column(raw, "t", "source", "Code/X.cpp", "Code/Z.cpp")
    assert count == 2
    assert out == (b'a,source,notes\n1,Code/Z.cpp,"see Code/X.cpp, twice"\n2,"Code/Z.cpp",x\n'
                   b'3,Code/X.cppz,x\n4,Code/Y.cpp,Code/X.cpp\n')


def test_field_spans_handle_quotes():
    text = 'a,"b,""c""",,d'
    assert [text[s:e] for s, e in rename.field_spans(text)] == ["a", '"b,""c"""', "", "d"]


# ------------------------------------------------------------ file kind

def test_file_plan_repoints_every_path_keyed_column(tree):
    p = plan_file(tree)
    assert p.moves == [(UNIT, MOVED)]
    assert p.verify == [MOVED]
    assert p.path_rows == {"reverse/functions.csv": 1, "reverse/data_rows.csv": 2,
                           "reverse/tu_map.csv": 1, "docs/doxygen/sources.cfg": 1}
    tu = p.after["reverse/tu_map.csv"].decode()
    assert f'"S={UNIT}",{MOVED}\n' in tu     # the evidence column is history, not a key
    assert f"INPUT += {MOVED}\n" in p.after["docs/doxygen/sources.cfg"].decode()
    assert p.after["reverse/name_basis.csv"].decode().splitlines() == [
        rename.NAME_BASIS_HEADER, f"file,{UNIT},{MOVED},inferred,mechanical: sole row,{MOVED},"]
    assert 0x00401000 in p.claims and f"file:{UNIT}" in p.claims and f"file:{MOVED}" in p.claims
    assert "reverse/link_status.csv" in p.mentions
    assert "reverse/deleted_rows.csv" not in p.after   # no (name, rva) changed
    assert p.subject() == "Rename WidgetRva00401000 to Widget_count (inferred)"


def test_file_apply_moves_with_git_and_keeps_the_bytes(tree):
    rename.apply_rename(plan_file(tree), ctx=ctx_of(tree), verify=ok)
    assert not (tree / UNIT).exists()
    assert (tree / MOVED).read_text() == WIDGET
    tracked = _git(tree, "ls-files").splitlines()
    assert MOVED in tracked and UNIT not in tracked     # the move is staged, as git mv stages it
    rows = (tree / "reverse/functions.csv").read_text()
    assert f"?count@Widget@@QAEHXZ,,0x00401000,6,{MOVED},matched" in rows and UNIT not in rows


@pytest.mark.parametrize("failure", ["verify", "exception"])
def test_file_rollback_restores_bytes_and_index(tree, failure):
    before = snapshot(tree)

    def verify(ctx, sources):
        assert sources == [MOVED] and (tree / MOVED).exists()
        if failure == "exception":
            raise KeyboardInterrupt
        return False

    with pytest.raises((VerifyFailed, KeyboardInterrupt)):
        rename.apply_rename(plan_file(tree), ctx=ctx_of(tree), verify=verify)
    assert snapshot(tree) == before


@pytest.mark.parametrize("overrides,message", [
    (dict(new="Code/Other/Widget_count.cpp"), "within one directory"),
    (dict(new="Widget_count.h"), "file type"),
    (dict(new="FileRva00405000"), "placeholder"),
    (dict(new="widgetrva00401000x", source="Code/Game/Globals.h"), "renames .cpp/.c"),
    (dict(source="Code/Game/FlagRva00404000.cpp", new="Flagged"), "flag_overrides.csv line 2"),
    (dict(source="Code/Game/FileRva00405000.cpp", new="Filed"), "__FILE__"),
    (dict(source="Code/Game/RealName.cpp", new="RealerName"), "approved retail TU"),
    (dict(source="Code/gen_asm/gen_0001.asm", new="x"), "generated"),
    (dict(source="Code/Game/Missing.cpp", new="Found"), "does not exist"),
    (dict(new="User"), "already exists"),
    (dict(new="user"), "already exists"),            # case-insensitive
    (dict(evidence=" "), "--evidence"),
])
def test_file_refusals(tree, overrides, message):
    with pytest.raises(Refusal, match=re.escape(message)):
        plan_file(tree, **overrides)


def test_file_inferred_may_not_replace_a_real_stem(tree):
    (tree / "reverse/tu_map.csv").write_text(TU_MAP.replace("approved,F", "candidate,F"))
    with pytest.raises(Refusal, match="real name"):
        plan_file(tree, source="Code/Game/RealName.cpp", new="RealerName")


def test_file_refuses_a_unit_another_file_includes(tree):
    (tree / "Code/Game/Bundle.cpp").write_text('#include "WidgetRva00401000.cpp"\n')
    _git(tree, "add", "Code/Game/Bundle.cpp")
    with pytest.raises(Refusal, match="#included"):
        plan_file(tree)


def test_file_refuses_a_canonical_recorded_stem(tree):
    (tree / "reverse/name_basis.csv").write_text(
        f"{rename.NAME_BASIS_HEADER}\nfile,Code/Game/Old.cpp,{UNIT},canonical:file,assert path,{UNIT},\n")
    with pytest.raises(Refusal, match="recorded canonical"):
        plan_file(tree)


def test_file_cli_dry_run_writes_nothing(tree, capsys):
    before = snapshot(tree)
    code = rename.main(["file", "--source", UNIT, "--new", "Widget_count", "--basis", "inferred",
                        "--evidence", "mechanical", "--dry-run", "--no-claim", "--root", str(tree)])
    assert code == 0
    out = capsys.readouterr().out
    assert f"git mv {UNIT} {MOVED}" in out and "nothing written" in out
    assert snapshot(tree) == before


def test_file_cli_apply_restores_on_build_failure(tree):
    (tree / "build.sh").write_text("#!/bin/sh\necho 'Functions: FAIL 1/1'\nexit 1\n")
    (tree / "build.sh").chmod(0o755)
    _git(tree, "add", "build.sh")
    before = snapshot(tree)
    code = rename.main(["file", "--source", UNIT, "--new", "Widget_count", "--basis", "inferred",
                        "--evidence", "mechanical", "--no-claim", "--root", str(tree)])
    assert code == 1
    assert snapshot(tree) == before


# ------------------------------------------------------------ global kind

def test_global_plan_rewrites_row_consumers_notes_and_pins(tree):
    p = plan_global(tree)
    assert p.new == DATA_NEW and p.rva == 0x00A01000
    assert p.renamed_data == [(DATA, DATA_NEW, 0x00A01000)]
    rows = p.after["reverse/data_rows.csv"].decode()
    assert f'{DATA_NEW},0x00A01000,rva,4,.data,{UNIT},matched,"only ref, {DATA_NEW} pushed",m' in rows
    assert f"reads {DATA_NEW}" in p.after["reverse/functions.csv"].decode()
    assert p.notes_rows == [("?count@Widget@@QAEHXZ", 0x00401000)]
    assert p.renamed_pins == [(DATA, DATA_NEW, "0x00E01000")]
    assert sorted(p.source_counts) == ["Code/Game/Globals.h", "Code/Game/User.cpp", UNIT]
    assert "g_widgetCount" in p.after["Code/Game/User.cpp"].decode()
    assert p.verify == ["Code/Game/Inc.cpp", "Code/Game/User.cpp", UNIT]   # Inc includes Globals.h
    assert p.after["reverse/deleted_rows.csv"].decode().endswith(
        f'{DATA},0x00A01000,"Renamed to {DATA_NEW} by tools/rename.py (inferred)"\n')
    assert p.after["reverse/name_basis.csv"].decode().splitlines()[-1] == \
        f"global,{DATA},{DATA_NEW},inferred,agree:abc,{UNIT},0x00A01000"
    assert 0x00A01000 in p.claims and f"file:{UNIT}" in p.claims
    assert p.subject() == "Rename g_00A01000 to g_widgetCount (inferred)"


def test_global_found_by_bare_identifier_and_full_mangled_new(tree):
    assert plan_global(tree, name="g_00A01000", new=DATA_NEW).new == DATA_NEW


def test_global_apply_and_rollback(tree):
    before = snapshot(tree)
    with pytest.raises(VerifyFailed):
        rename.apply_rename(plan_global(tree), ctx=ctx_of(tree), verify=lambda ctx, sources: False)
    assert snapshot(tree) == before
    rename.apply_rename(plan_global(tree), ctx=ctx_of(tree), verify=ok)
    assert "g_00A01000" not in (tree / "Code/Game/User.cpp").read_text()
    assert DATA_NEW in (tree / "reverse/data_rows.csv").read_text()
    # the new name is now inferred: inferred may not replace it, canonical may
    with pytest.raises(Refusal, match="real name"):
        plan_global(tree, name=DATA_NEW, new="g_widgetTotal")
    p = plan_global(tree, name=DATA_NEW, new="g_widgetTotal", basis="canonical:string", evidence="retail")
    assert p.new == "?g_widgetTotal@@3HA"


@pytest.mark.parametrize("overrides,message", [
    (dict(name="?g_00A02000@@3HA", new="g_converged"), "converged"),
    (dict(name="?g_00A03000@@3HA", new="g_literal"), "string literal"),
    (dict(name="?g_00A04000@@3HA", new="g_frozen"), "frozen"),
    (dict(name="?g_nothing@@3HA"), "no reverse/data_rows.csv row"),
    (dict(new="g_00B00000"), "placeholder"),
    (dict(new="?g_widgetCount@@3MA"), "beyond the identifier"),
    (dict(new="g_00A01000"), "placeholder"),
    (dict(new="int"), "keyword"),
    (dict(basis="canonical:hunch"), "unknown canonical evidence kind"),
])
def test_global_refusals(tree, overrides, message):
    with pytest.raises(Refusal, match=re.escape(message)):
        plan_global(tree, **overrides)


def test_global_converged_by_address_alone(tree):
    (tree / "reverse/data_converged.csv").write_text("address,name,evidence\n0x00A01000,?TheWidgets@@3HA,x\n")
    with pytest.raises(Refusal, match="converged address"):
        plan_global(tree)


def test_global_refuses_a_new_name_already_spelled(tree):
    with (tree / "reverse/data_rows.csv").open("a") as handle:
        handle.write("?g_widgetCount@Other@@2HA,0x00A05000,rva,4,.data,Code/Game/User.cpp,matched,x,m\n")
    with pytest.raises(Refusal, match="already spells"):
        plan_global(tree)


def test_global_inferred_may_not_replace_a_real_name(tree):
    with (tree / "reverse/data_rows.csv").open("a") as handle:
        handle.write("?TheWidgets@@3HA,0x00A06000,rva,4,.data,Code/Game/User.cpp,matched,x,m\n")
    with pytest.raises(Refusal, match="real name"):
        plan_global(tree, name="?TheWidgets@@3HA", new="TheGadgets")


def test_global_refuses_a_generated_consumer(tree):
    (tree / "Code/gen_small/gen_x.cpp").parent.mkdir(parents=True)
    (tree / "Code/gen_small/gen_x.cpp").write_text("extern int g_00A01000;\n")
    _git(tree, "add", "Code/gen_small/gen_x.cpp")
    with pytest.raises(Refusal, match="generated"):
        plan_global(tree)


def test_global_data_ledger_mention_is_a_warning(tree):
    (tree / "reverse/data_ledger.csv").write_text(f"address,size,section,kind,name,source\n"
                                                  f"0x00A01000,4,.data,global,{DATA},{UNIT}\n")
    _git(tree, "add", "reverse/data_ledger.csv")
    p = plan_global(tree)
    assert any("data_ledger.csv" in w for w in p.warnings)
    assert "reverse/data_ledger.csv" not in p.after


def test_global_cli(tree, capsys):
    before = snapshot(tree)
    code = rename.main(["global", "--name", "g_00A01000", "--new", "g_widgetCount", "--basis", "inferred",
                        "--evidence", "agree:abc", "--dry-run", "--no-claim", "--root", str(tree)])
    assert code == 0 and "nothing written" in capsys.readouterr().out
    assert snapshot(tree) == before


# ------------------------------------------------------------ the real tree

REAL = pytest.mark.skipif(not (rename.ROOT / rename.FUNCTIONS).exists(), reason="no real ledger")


@REAL
def test_real_tree_file_dry_run_smoke():
    """Plan (never apply) renaming a live address-named unit whose rows are
    real-named: the planner must plan one or refuse with a reason."""
    ctx = rename.Context(rename.ROOT, object_scan=False)
    owned = {}
    for row in ctx.rows():
        owned.setdefault(row["source"], []).append(row["name"])
    tried = 0
    for source, names in sorted(owned.items()):
        stem = Path(source).stem
        if not source.endswith(".cpp") or rename.is_generated(source) or not rename.is_placeholder(stem, "file"):
            continue
        if any(rename.name_metric.placeholder(t) for n in names for t in re.findall(r"[A-Za-z_]\w*", n)):
            continue
        tried += 1
        try:
            p = rename.plan_rename("file", ctx=ctx, source=source, new="SmokeTestUnitName",
                                   basis="inferred", evidence="smoke")
        except Refusal:
            assert tried < 60, "no live address-named unit could be planned"
            continue
        assert p.moves and p.verify == [p.moves[0][1]] and p.path_rows["reverse/functions.csv"] >= 1
        assert p.after["reverse/name_basis.csv"].endswith(b"\n")
        return
    pytest.fail("no live address-named unit could be planned")


@REAL
def test_real_tree_global_dry_run_smoke():
    """Plan (never apply) renaming a live address-named, non-converged global."""
    ctx = rename.Context(rename.ROOT, object_scan=False)
    tried = 0
    for row in ctx.dicts(rename.DATA_ROWS):
        word = rename._identifier(row["name"])
        if not word or not rename.is_placeholder(word, "global") or rename.is_generated(row["source"]):
            continue
        tried += 1
        try:
            p = rename.plan_rename("global", ctx=ctx, name=row["name"], new="smokeTestGlobal",
                                   basis="inferred", evidence="smoke")
        except Refusal:
            assert tried < 60, "no live address-named global could be planned"
            continue
        assert p.renamed_data and p.verify and row["source"] in p.verify
        assert any(b"smokeTestGlobal" in data for rel, data in p.after.items() if rel.startswith("Code/"))
        return
    pytest.fail("no live address-named global could be planned")
