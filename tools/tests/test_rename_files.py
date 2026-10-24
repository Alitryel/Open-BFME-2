"""tools/rename_files.py (the mechanical file lane) on a miniature tree: a
temporary git repository with small ledgers and sources, verification
injected, so the proposals, every refusal, batching, rollback and the
journal run without the real ledger or a compiler. A real-tree plan smoke
closes the file."""
import json
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))

import rename  # noqa: E402
import rename_files as rf  # noqa: E402
from rename import Refusal, VerifyFailed  # noqa: E402
import posixpath  # noqa: E402

D = "Code/Game"
FUNCTIONS = f"""name,export_rva,target_rva,target_size,source,status,notes
?count@Widget@@QAEHXZ,,0x00401000,6,{D}/WidgetRva00401000.cpp,matched,
?a@Gadget@@QAEXXZ,,0x00402000,6,{D}/Rva00402000Pair.cpp,matched,
?b@Gadget@@QAEXXZ,,0x00402100,6,{D}/Rva00402000Pair.cpp,matched,
??_GGadget@@UAEPAXI@Z,,0x00402200,6,{D}/Rva00402000Pair.cpp,matched,
$L100,,0x00402300,6,{D}/Rva00402000Pair.cpp,matched,gen-funclet;parent=?b@Gadget@@QAEXXZ
?freeFn@@YAHXZ,,0x00403000,6,{D}/Bfme5FreeThing.cpp,matched,
??0Gizmo@@QAE@XZ,,0x00404000,6,{D}/Rva00404000Ctor.cpp,matched,
?rva00405000@Widget@@QAEXXZ,,0x00405000,6,{D}/Rva00405000.cpp,matched,
??4Gadget@@QAEAAV0@ABV0@@Z,,0x00406000,6,{D}/Rva00406000Assign.cpp,matched,
?get@Inner@Outer@@QAEHXZ,,0x00407000,6,{D}/Rva00407000Nested.cpp,matched,
?x@Widget@@QAEXXZ,,0x00408000,6,{D}/Rva00408000Mixed.cpp,matched,
?y@Gadget@@QAEXXZ,,0x00408100,6,{D}/Rva00408000Mixed.cpp,matched,
?f1@@YAXXZ,,0x00409000,6,{D}/Rva00409000Frees.cpp,matched,
?f2@@YAXXZ,,0x00409100,6,{D}/Rva00409000Frees.cpp,matched,
$L200,,0x0040A000,6,{D}/Rva0040A000Orphan.cpp,matched,gen-funclet;parent=?count@Widget@@QAEHXZ
?flagged@Flag@@QAEXXZ,,0x0040B000,6,{D}/FlagRva0040B000.cpp,matched,
?filed@File@@QAEXXZ,,0x0040C000,6,{D}/FileRva0040C000.cpp,matched,
?inc@Inc@@QAEXXZ,,0x0040D000,6,{D}/IncRva0040D000.cpp,matched,
?appr@Appr@@QAEXXZ,,0x0040E000,6,{D}/ApprRva0040E000.cpp,matched,
?taken@Taken@@QAEXXZ,,0x0040F000,6,{D}/TakenRva0040F000.cpp,matched,
?vend@Vend@@QAEXXZ,,0x00410000,6,{D}/VendRva00410000.cpp,matched,vendored=zlib-1.1.4
?real@Real@@QAEXXZ,,0x00411000,6,{D}/RealName.cpp,matched,
?inf@Inf@@QAEXXZ,,0x00412000,6,{D}/InfRva00412000.cpp,matched,
?free2@@YAXXZ,,0x00413000,6,{D}/Rva00413000.cpp,matched,
?free2@@YAXH@Z,,0x00413100,6,{D}/Sub/Rva00413100.cpp,matched,
?dup@Twice@@QAEXXZ,,0x00414000,6,{D}/Rva00414000.cpp,matched,
?dup@Twice@@QAEXH@Z,,0x00414100,6,{D}/Rva00414100.cpp,matched,
"""
TU_MAP = f"""rva,size,kind,tu,confidence,by,evidence,source
0x0040E000,6,code,{D}/ApprRva0040E000.cpp,approved,F,F,{D}/ApprRva0040E000.cpp
"""
EASY = (f"{D}/WidgetRva00401000.cpp", f"{D}/Rva00402000Pair.cpp", f"{D}/Bfme5FreeThing.cpp",
        f"{D}/Rva00404000Ctor.cpp")


def _git(root, *args):
    return subprocess.run(["git", "-C", str(root), *args], check=True, capture_output=True,
                          text=True).stdout


@pytest.fixture
def tree(tmp_path):
    files = {
        "reverse/functions.csv": FUNCTIONS,
        "reverse/data_rows.csv": "name,address,address_kind,size,section,source,status,evidence,model\n",
        "reverse/symbols.csv": "name,address,notes\n",
        "reverse/deleted_rows.csv": "name,target_rva,reason\n",
        "reverse/tu_map.csv": TU_MAP,
        "reverse/flag_overrides.csv": "source,flags,rows,default_lost,reason\n"
                                      f"{D}/FlagRva0040B000.cpp,-O2,1,1,region\n",
        "reverse/name_basis.csv": rename.NAME_BASIS_HEADER + "\n"
                                  "function,?rva00412000@Inf@@QAEXXZ,?inf@Inf@@QAEXXZ,inferred,agree:x,,0x00412000\n",
        f"{D}/FileRva0040C000.cpp": 'const char *f() { return __FILE__; }\n',
        f"{D}/Other.cpp": '#include "IncRva0040D000.cpp"\n',
        f"{D}/Taken_taken.cpp": "// already here\n",
        "Code/gen_asm/gen_0001.asm": "x PROC\n",
    }
    for line in FUNCTIONS.splitlines()[1:]:
        source = line.split(",")[4]
        files.setdefault(source, f"// {line.split(',')[0]}\nvoid body() {{}}\n")
    for rel, text in files.items():
        path = tmp_path / rel
        path.parent.mkdir(parents=True, exist_ok=True)
        path.write_bytes(text.encode("utf-8"))
    _git(tmp_path, "init", "-q")
    _git(tmp_path, "add", "-A")
    _git(tmp_path, "-c", "user.email=t@t", "-c", "user.name=t", "commit", "-q", "-m", "fixture")
    return tmp_path





def ctx_of(root):
    return rename.Context(root, object_scan=False)


def snapshot(root):
    files = {p.relative_to(root).as_posix(): p.read_bytes()
             for p in root.rglob("*") if p.is_file() and ".git" not in p.parts}
    files.pop("reverse/.add_match.lock", None)
    status = [line for line in _git(root, "status", "--porcelain").splitlines() if ".add_match.lock" not in line]
    return files, status


def ok(ctx, sources):
    return True


def row(name, notes=""):
    return {"name": name, "notes": notes, "status": "matched"}


# ------------------------------------------------------------ proposals

@pytest.mark.parametrize("names, stem", [
    (["?count@Widget@@QAEHXZ"], "Widget_count"),
    (["?freeFn@@YAHXZ"], "freeFn"),
    (["_cfunc@8"], "cfunc"),
    (["??0Gizmo@@QAE@XZ"], "Gizmo"),
    (["??1Gizmo@@UAE@XZ"], "Gizmo"),
    (["?a@Gadget@@QAEXXZ", "?b@Gadget@@QAEXXZ"], "Gadget"),
    (["??_GGadget@@UAEPAXI@Z", "?a@Gadget@@QAEXXZ"], "Gadget"),
    (["?a@Gadget@@QAEXXZ", "?free@@YAXXZ"], "Gadget"),
])
def test_proposal(names, stem):
    assert rf.proposal([row(n) for n in names]) == (stem, None)


def test_proposal_skips_funclets_of_owned_parents():
    rows = [row("?count@Widget@@QAEHXZ"), row("$L1", "gen-funclet;parent=?count@Widget@@QAEHXZ"),
            row("Unwind@00b96a34", "gen-funclet;parent=?count@Widget@@QAEHXZ;object-symbol=$L2"),
            row("__ehhandler$?count@Widget@@QAEHXZ"), row("__unwindfunclet$?count@Widget@@QAEHXZ$0")]
    assert rf.proposal(rows) == ("Widget_count", None)


@pytest.mark.parametrize("names, reason", [
    (["?rva00405000@Widget@@QAEXXZ"], "placeholder-named"),
    (["?count@Rva00401000@@QAEXXZ"], "placeholder-named"),
    (["??0Rva006D51B0@@QAE@II@Z"], "placeholder-named"),
    (["??4Gadget@@QAEAAV0@ABV0@@Z"], "operator, template"),
    (["??4Rva005E7198@@QAEAAV0@ABV0@@Z"], "placeholder-named"),
    (["??$for_each@PAH@_STL@@YAXPAH0@Z"], "operator, template"),
    (["?get@Inner@Outer@@QAEHXZ"], "nested scope"),
    (["?x@Widget@@QAEXXZ", "?y@Gadget@@QAEXXZ"], "span 2 classes"),
    (["?f1@@YAXXZ", "?f2@@YAXXZ"], "several free functions"),
    (["$L1"], "funclet"),
    (["??_GGadget@@UAEPAXI@Z"], "no row names the file"),
])
def test_proposal_refusals(names, reason):
    rows = [row(n, "gen-funclet;parent=?elsewhere@@YAXXZ" if n.startswith("$L") else "") for n in names]
    stem, why = rf.proposal(rows)
    assert stem is None and reason in why


def test_funclet_of_a_foreign_parent_is_refused():
    stem, why = rf.proposal([row("?a@Gadget@@QAEXXZ"), row("$L9", "gen-funclet;parent=?z@Other@@QAEXXZ")])
    assert stem is None and "parent this file does not own" in why


# ------------------------------------------------------------ candidates

def test_candidates_pick_and_refuse(tree):
    picked, refused = rf.candidates(ctx_of(tree), basis="mechanical")
    got = {s: t.rsplit("/", 1)[1] for s, t, _rows in picked}
    assert got == {f"{D}/WidgetRva00401000.cpp": "Widget_count.cpp", f"{D}/Rva00402000Pair.cpp": "Gadget.cpp",
                   f"{D}/Bfme5FreeThing.cpp": "freeFn.cpp", f"{D}/Rva00404000Ctor.cpp": "Gizmo.cpp",
                   f"{D}/InfRva00412000.cpp": "Inf_inf.cpp", f"{D}/Rva00413000.cpp": "free2.cpp",
                   f"{D}/Sub/Rva00413100.cpp": "free2.cpp", f"{D}/Rva00414000.cpp": "Twice_dup.cpp"}
    why = dict(refused)
    assert "placeholder-named" in why[f"{D}/Rva00405000.cpp"]
    assert "operator" in why[f"{D}/Rva00406000Assign.cpp"]
    assert "nested scope" in why[f"{D}/Rva00407000Nested.cpp"]
    assert "span" in why[f"{D}/Rva00408000Mixed.cpp"]
    assert "several free" in why[f"{D}/Rva00409000Frees.cpp"]
    assert "funclet" in why[f"{D}/Rva0040A000Orphan.cpp"]
    assert "protected path-keyed" in why[f"{D}/FlagRva0040B000.cpp"]
    assert "__FILE__" in why[f"{D}/FileRva0040C000.cpp"]
    assert "#included" in why[f"{D}/IncRva0040D000.cpp"]
    assert "approved retail TU" in why[f"{D}/ApprRva0040E000.cpp"]
    assert "already exists" in why[f"{D}/TakenRva0040F000.cpp"]
    assert "vendored" in why[f"{D}/VendRva00410000.cpp"]
    # Two proposals for one target in one directory: the second waits.
    assert "already exists" in why[f"{D}/Rva00414100.cpp"]
    # A real stem is not a candidate at all.
    assert f"{D}/RealName.cpp" not in why and f"{D}/RealName.cpp" not in got


def test_a_row_recorded_inferred_still_gives_an_inferred_stem(tree):
    """The stem is inferred like the row it is read from (review fix-2 finding 5)."""
    picked, refused = rf.candidates(ctx_of(tree), basis="mechanical")
    assert f"{D}/InfRva00412000.cpp" in {s for s, _t, _r in picked}


def test_target_collision_is_case_insensitive(tree):
    (tree / D / "WIDGET_COUNT.cpp").write_text("// x\n")
    _git(tree, "add", "-A")
    picked, refused = rf.candidates(ctx_of(tree), basis="mechanical")
    assert "already exists" in dict(refused)[f"{D}/WidgetRva00401000.cpp"]


def test_under_filters(tree):
    picked, _refused = rf.candidates(ctx_of(tree), under=f"{D}/Sub", basis="mechanical")
    assert [s for s, _t, _r in picked] == [f"{D}/Sub/Rva00413100.cpp"]


def test_every_proposal_is_a_stem_rename_py_accepts(tree):
    ctx = ctx_of(tree)
    picked, _refused = rf.candidates(ctx, basis="mechanical")
    for source, target, rows in picked:
        stem = target.rsplit("/", 1)[1][:-4]
        assert stem.lower() in rename.mechanical_stems(ctx, source)
        assert rf.dry_plan(ctx, source, target, rows, "mechanical") is None


# ------------------------------------------------------------ apply

def picks_of(root, sources=EASY, basis="mechanical"):
    picked, _refused = rf.candidates(ctx_of(root), basis=basis)
    return [p for p in picked if p[0] in sources]


def test_apply_batch_renames_records_and_stages(tree):
    picks = picks_of(tree)
    plans, failed, _kept = rf.run_batches(ctx_of(tree), picks, "mechanical", batch=10, claim=False,
                                         verify=ok, checks=None, out=lambda *_: None)
    assert len(plans) == 4 and not failed
    functions = (tree / "reverse/functions.csv").read_text()
    assert f"{D}/Widget_count.cpp,matched" in functions and "WidgetRva00401000" not in functions
    assert f"{D}/Gadget.cpp,matched,gen-funclet" in functions
    basis = (tree / "reverse/name_basis.csv").read_text().splitlines()
    added = [line for line in basis if line.startswith("file,")]
    assert len(added) == 4
    assert f"file,{D}/Rva00402000Pair.cpp,{D}/Gadget.cpp,inferred,mechanical:?a@Gadget@@QAEXXZ;" \
           f"?b@Gadget@@QAEXXZ;??_GGadget@@UAEPAXI@Z,{D}/Gadget.cpp," in added
    status = _git(tree, "status", "--porcelain")
    assert f"R  {D}/WidgetRva00401000.cpp -> {D}/Widget_count.cpp" in status
    assert not list((tree / rename.JOURNAL_DIR).glob("*.json"))


def test_failed_batch_restores_then_isolates_the_bad_unit(tree):
    before = snapshot(tree)
    calls = []

    def verify(ctx, sources):
        calls.append(list(sources))
        return f"{D}/Gizmo.cpp" not in sources

    picks = picks_of(tree)
    plans, failed, _kept = rf.run_batches(ctx_of(tree), picks, "mechanical", batch=10, claim=False,
                                         verify=verify, checks=None, out=lambda *_: None)
    assert len(calls) == 5 and len(calls[0]) == 4
    assert [f[0] for f in failed] == [f"{D}/Rva00404000Ctor.cpp"]
    assert len(plans) == 3
    assert (tree / D / "Rva00404000Ctor.cpp").read_bytes() == before[0][f"{D}/Rva00404000Ctor.cpp"]
    assert not (tree / D / "Gizmo.cpp").exists()


def test_failed_single_batch_is_byte_identical(tree):
    before = snapshot(tree)
    with pytest.raises(rename.VerifyFailed):
        rf.apply_batch(ctx_of(tree), picks_of(tree), "mechanical", claim=False,
                       verify=lambda ctx, s: False, checks=None)
    assert snapshot(tree) == before
    assert not list((tree / rename.JOURNAL_DIR).glob("*.json"))


def test_hook_check_failure_restores(tree):
    before = snapshot(tree)
    with pytest.raises(rename.VerifyFailed):
        rf.apply_batch(ctx_of(tree), picks_of(tree), "mechanical", claim=False, verify=ok,
                       checks=lambda ctx, plan: ["check_csv: boom"] if plan.moves else [])
    assert snapshot(tree) == before


def test_interrupt_mid_batch_restores(tree):
    before = snapshot(tree)
    with pytest.raises(KeyboardInterrupt):
        rf.apply_batch(ctx_of(tree), picks_of(tree), "mechanical", claim=False,
                       verify=lambda ctx, s: (_ for _ in ()).throw(KeyboardInterrupt()), checks=None)
    assert snapshot(tree) == before


def test_batch_journal_is_recoverable_by_rename_py(tree):
    """A batch killed outright leaves one journal; `rename.py recover` undoes
    the whole batch from it."""
    before = snapshot(tree)
    saved = tree / "saved.json"

    def verify(ctx, sources):
        journals = list((tree / rename.JOURNAL_DIR).glob("*.json"))
        assert len(journals) == 1
        record = json.loads(journals[0].read_text())
        assert len(record["moves"]) == 4
        shutil.copy(journals[0], saved)
        return True

    rf.apply_batch(ctx_of(tree), picks_of(tree), "mechanical", claim=False, verify=verify, checks=None)
    assert not (tree / D / "WidgetRva00401000.cpp").exists()
    shutil.copy(saved, tree / rename.JOURNAL_DIR / "dead.json")
    saved.unlink()
    restored, busy = rename.recover(ctx_of(tree), release_claims=False)
    assert len(restored) == 1 and not busy
    files, status = snapshot(tree)
    assert files == before[0]
    assert status == before[1]


def test_pending_journal_refuses(tree):
    (tree / rename.JOURNAL_DIR).mkdir(parents=True)
    (tree / rename.JOURNAL_DIR / "x.json").write_text("{}")
    with pytest.raises(Refusal, match="recover"):
        rf.apply_batch(ctx_of(tree), picks_of(tree), "mechanical", claim=False, verify=ok, checks=None)


def test_failing_checks_before_the_batch_refuse(tree):
    before = snapshot(tree)
    with pytest.raises(Refusal, match="already fail"):
        rf.apply_batch(ctx_of(tree), picks_of(tree), "mechanical", claim=False, verify=ok,
                       checks=lambda ctx, plan: ["check_csv: stale"])
    assert snapshot(tree) == before


# ------------------------------------------------------------ CLI

def test_cli_plan_writes_nothing(tree, capsys):
    before = snapshot(tree)
    assert rf.main(["--root", str(tree), "--no-object-scan", "--basis", "mechanical", "--show", "2"]) == 0
    out = capsys.readouterr().out
    assert "8 renameable" in out and out.count(" -> ") == 2
    assert snapshot(tree) == before


def test_there_is_no_canonical_rows_basis(tree, capsys, monkeypatch):
    """Review fix-2 finding 5: a stem derived from rows is never canonical,
    and nothing upgrades `auto` to a canonical basis, whatever rename.py accepts."""
    assert rf.BASES == {"mechanical": "inferred"}
    monkeypatch.setattr(rename, "CANONICAL_KINDS", rename.CANONICAL_KINDS | {"rows"})
    assert rf.resolve_basis("auto") == "mechanical"
    with pytest.raises(SystemExit):
        rf.main(["--root", str(tree), "--no-object-scan", "--basis", "rows"])
    assert rf.evidence_for("mechanical", [{"name": "?count@Widget@@QAEHXZ", "notes": ""}]) == \
        "mechanical:?count@Widget@@QAEHXZ"


def test_cli_default_basis_applies_mechanical(tree, capsys, monkeypatch):
    monkeypatch.setattr(rename, "build_verify", ok)
    assert rf.main(["--root", str(tree), "--no-object-scan", "--apply", "--limit", "1", "--no-claim"]) == 0
    out = capsys.readouterr().out
    assert "basis: inferred" in out and "applied: 1 renamed, 0 refused" in out
    added = [line for line in (tree / "reverse/name_basis.csv").read_text().splitlines()
             if line.startswith("file,")]
    assert len(added) == 1 and ",inferred,mechanical:" in added[0]


FAKE_CHECK = """import pathlib, sys
lines = [l for l in pathlib.Path("reverse/check_lines.txt").read_text().splitlines() if l]
lines += [p.name for p in pathlib.Path("Code").rglob("*.cpp") if p.name.startswith("Widget_")]
print("\\n".join(lines))
sys.exit(1 if lines else 0)
"""


def fake_check(tree, preexisting):
    (tree / "tools").mkdir(exist_ok=True)
    (tree / "tools/check_csv.py").write_text(FAKE_CHECK)
    (tree / "reverse/check_lines.txt").write_text(preexisting)


def test_tolerant_checks_ignore_preexisting_failures(tree):
    fake_check(tree, "functions.csv line 7: someone else's unstaged rename\n")
    picks = [p for p in picks_of(tree) if not posixpath.basename(p[1]).startswith("Widget_")][:2]
    assert picks
    ctx = ctx_of(tree)
    with pytest.raises(Refusal, match="already fail"):
        rf.apply_batch(ctx, picks, "mechanical", claim=False, verify=ok, checks=rename.ledger_checks)
    plans, _claimed = rf.apply_batch(ctx, picks, "mechanical", claim=False, verify=ok,
                                     checks=rf.tolerant_checks(ctx))
    assert len(plans) == len(picks)


def test_tolerant_checks_refuse_what_the_batch_adds(tree):
    fake_check(tree, "functions.csv line 7: someone else's unstaged rename\n")
    picks = [p for p in picks_of(tree) if posixpath.basename(p[1]).startswith("Widget_")][:1]
    assert picks
    ctx = ctx_of(tree)
    before = snapshot(tree)
    with pytest.raises(VerifyFailed, match="Widget_"):
        rf.apply_batch(ctx, picks, "mechanical", claim=False, verify=ok, checks=rf.tolerant_checks(ctx))
    assert snapshot(tree) == before


GATE_STAND_IN = """import subprocess, sys
paths = subprocess.run(["git", "diff", "--cached", "--name-only"], capture_output=True, text=True).stdout.split()
bad = [p for p in paths if p.rsplit("/", 1)[-1].startswith("Widget_")]
if bad:
    print("  " + bad[0] + ": declares its own view", file=sys.stderr)
    sys.exit(1)
"""


def test_tolerant_checks_still_run_the_hook_gates_but_not_ledger_guard(tree):
    # the moved unit is judged by the hook's class_gate on a private index; an unstaged ledger edit
    # another worker left (ledger_guard's finding) is the dirt this lane tolerates
    (tree / "tools").mkdir(exist_ok=True)
    (tree / "tools/class_gate.py").write_text(GATE_STAND_IN)
    shutil.copy(TOOLS / "ledger_guard.py", tree / "tools/ledger_guard.py")
    (tree / "reverse/data_rows.csv").write_text("name,address\nx,1\n")        # unstaged, someone else's
    picks = [p for p in picks_of(tree) if posixpath.basename(p[1]).startswith("Widget_")][:1]
    assert picks
    ctx = ctx_of(tree)
    before = snapshot(tree)
    with pytest.raises(VerifyFailed, match=r"the commit hooks would refuse the batch \[class_gate\]"):
        rf.apply_batch(ctx, picks, "mechanical", claim=False, verify=ok, checks=rf.tolerant_checks(ctx))
    assert snapshot(tree) == before
    other = [p for p in picks_of(tree) if not posixpath.basename(p[1]).startswith("Widget_")][:1]
    assert other
    plans, _claimed = rf.apply_batch(ctx, other, "mechanical", claim=False, verify=ok,
                                     checks=rf.tolerant_checks(ctx))
    assert len(plans) == 1
    with pytest.raises(VerifyFailed, match=r"\[ledger_guard\]"):      # the strict lane names that dirt
        rf.apply_batch(ctx, picks_of(tree)[:1], "mechanical", claim=False, verify=ok,
                       checks=rename.ledger_checks)


def test_cli_check_reports_rename_py_verdicts(tree, capsys):
    assert rf.main(["--root", str(tree), "--no-object-scan", "--basis", "mechanical", "--check"]) == 0
    assert "8 planned OK, 0 refused" in capsys.readouterr().out


# ------------------------------------------------------------ real tree

@pytest.mark.skipif(not (rename.ROOT / rename.FUNCTIONS).exists(), reason="no real ledger")
def test_real_tree_plan_smoke():
    ctx = rename.Context()
    picked, refused = rf.candidates(ctx, basis="mechanical")
    assert picked and refused
    for source, target, rows in picked[:5]:
        stem = target.rsplit("/", 1)[1].rsplit(".", 1)[0]
        assert not rename.is_placeholder(stem, "file")
        assert stem.lower() in rename.mechanical_stems(ctx, source)


def test_cli_json_plan_report(tree, tmp_path):
    out = tmp_path / "plan.json"
    assert rf.main(["--root", str(tree), "--no-object-scan", "--basis", "mechanical", "--show", "2", "--check",
                    "--json", str(out)]) == 0
    report = json.loads(out.read_text())
    assert report["lane"] == "files" and report["mode"] == "plan" and report["exit"] == 0
    assert report["basis"] == "inferred" and report["renameable"] == 8
    assert sum(report["refusal_reasons"].values()) == report["refused"] > 0
    assert len(report["proposals"]) == 2 and report["applied"] == [] and report["stage"] == []
    assert all(p["refused_by_rename_py"] is None for p in report["proposals"])


def test_cli_json_apply_report(tree, tmp_path, monkeypatch):
    monkeypatch.setattr(rename, "build_verify", ok)
    out = tmp_path / "apply.json"
    assert rf.main(["--root", str(tree), "--no-object-scan", "--apply", "--limit", "2", "--no-claim",
                    "--json", str(out)]) == 0
    report = json.loads(out.read_text())
    assert report["mode"] == "apply" and len(report["applied"]) == 2 and report["failed"] == []
    for item in report["applied"]:
        assert (tree / item["new"]).exists() and not (tree / item["old"]).exists()
    assert "reverse/name_basis.csv" in report["stage"]


def test_cli_json_records_the_inferred_basis(tree, tmp_path):
    out = tmp_path / "plan.json"
    assert rf.main(["--root", str(tree), "--no-object-scan", "--basis", "auto", "--json", str(out)]) == 0
    report = json.loads(out.read_text())
    assert report["basis"] == "inferred" and report["basis_note"] is None

