"""tu_skeleton --merge carries protected-register debt with the code: every absorbed
donor's key is re-keyed to the TU in the merge commit, the hooks read that as a
transfer (not growth, not a vanished-source retirement), and register totals hold."""
import collections
import csv
import importlib
import io
import os
import shutil
import subprocess
import sys
from pathlib import Path

import pytest

TOOLS = Path(__file__).resolve().parents[1]
sys.path.insert(0, str(TOOLS))
import tu_skeleton as T  # noqa: E402
import protected_paths  # noqa: E402

A, B, C, TU = "Code/A.cpp", "Code/B.cpp", "Code/C.cpp", "Code/T.cpp"
HEADER = "name,export_rva,target_rva,target_size,source,status,notes\n"
TEXTS = {A: '#pragma optimize("", off)\nint a() { return 1; }\n#pragma optimize("", on)\n',
         B: "int b() { return 2; }\n",
         C: "int c() { return 3; }\n"}
IDENTITY = ("# Wrong code bindings, keyed source<TAB>row<TAB>symbol<TAB>retail target<TAB>class.\n# mode: shadow\n"
            f"{A}\t?a@@YAHXZ\t?x@@YAXXZ\t0x00005000\twrong\n"
            f"{B}\t?b@@YAHXZ\t?x@@YAXXZ\t0x00005000\tunowned\n"
            f"{C}\t?c@@YAHXZ\t?x@@YAXXZ\t0x00005000\twrong\n")
DATA = ("# source\tcheck\tsymbol\taddress -- shrink-only; written by tools/data_check.py\n"
        f"{A}\twrong-name\t?g_00A00000@@3HA\t0x00A00000\n"
        f"{B}\twrong-name\t?g_00A00000@@3HA\t0x00A00000\n"      # the same key under two donors: kept once
        f"{B}\tduplicate-def\t?TheX@@3HA\t0x00A00004\n"
        f"{C}\twrong-name\t?g_00A00000@@3HA\t0x00A00000\n")
OVERRIDES = ("source,flags,rows,default_lost,reason\n"
             f"{A},-O2,2,1,region default loses rows\n"
             f"{C},-O2,1,1,region default loses rows\n")
LEDGER = ("address,size,section,kind,name,source,status,names,defs,refs\n"
          f"0x00A00000,4,.data,global,?g@@3HA,{A},provisional,?g@@3HA;?s@@3HA@{B},1,2\n"
          f"0x00A00004,4,.data,global,?TheX@@3HA,{C},owned,,1,1\n")
HATCH = ("# Escape-hatch register, shrink-only. hatch\tpath\ttoken\tcount\n# mode: enforce\n"
         f'pragma_optimize\t{A}\t"",off\t1\n'
         f'pragma_optimize\t{A}\t"",on\t1\n')


def git(root, *args, check=True):
    return subprocess.run(["git", "-C", str(root), *args], capture_output=True, text=True, check=check)


@pytest.fixture
def repo(tmp_path, monkeypatch):
    files = {**TEXTS,
             "reverse/functions.csv": HEADER + f"?a@@YAHXZ,,0x00001000,8,{A},matched,\n"
                                               f"?b@@YAHXZ,,0x00001010,8,{B},matched,\n"
                                               f"?c@@YAHXZ,,0x00001020,8,{C},matched,\n",
             "reverse/code_identity_baseline.tsv": IDENTITY, "reverse/data_check_baseline.txt": DATA,
             "reverse/flag_overrides.csv": OVERRIDES, "reverse/data_ledger.csv": LEDGER,
             "reverse/hatch_baseline.tsv": HATCH}
    for rel, text in files.items():
        (tmp_path / rel).parent.mkdir(parents=True, exist_ok=True)
        (tmp_path / rel).write_text(text, encoding="utf-8", newline="\n")
    (tmp_path / "tools").mkdir()
    shutil.copy(TOOLS / "hatch_counters.py", tmp_path / "tools")   # stdlib only; ROOT is the fixture
    git(tmp_path, "init", "-q")
    git(tmp_path, "config", "core.autocrlf", "false")
    git(tmp_path, "add", ".")
    git(tmp_path, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-qm", "init")
    monkeypatch.chdir(tmp_path)          # protected_paths' git runs where the hook does
    protected_paths._LEDGERS.clear()
    return tmp_path


def merged_text():
    return "".join(TEXTS[f] for f in (A, B))


def keys(text):
    return [line for line in text.splitlines() if line and not line.startswith("#")]


def tails(text):
    return collections.Counter(line.split("\t", 1)[1] for line in keys(text))


def hatch_totals(text):
    out = collections.Counter()
    for line in keys(text):
        hatch, _path, token, count = line.split("\t")[:4]
        out[(hatch, token)] += int(count)
    return out


def override_totals(text):
    rows = list(csv.DictReader(io.StringIO(text)))
    return sum(int(r["rows"]) for r in rows), sum(int(r["default_lost"]) for r in rows)


def test_a_merge_carries_every_protected_key_to_the_tu(repo):
    before = {rel: (repo / rel).read_text() for rel in T.rename.PROTECTED_PATH_KEYED}
    carry = T.Carry(repo, TU, [A, B], TEXTS, merged_text(), "-O2")
    assert carry.problems == [] and carry.collapsed == []
    assert carry.moved == {"reverse/code_identity_baseline.tsv": 2, "reverse/data_check_baseline.txt": 3,
                           "reverse/flag_overrides.csv": 1, "reverse/data_ledger.csv": 1,
                           "reverse/hatch_baseline.tsv": "hatch_counters --update"}
    assert carry.trailer().startswith("Verifier-Change: tu_skeleton --merge carried")
    moved = T.apply(TU, [A, B], merged_text(), root=repo, carry=carry)
    assert moved["reverse/hatch_baseline.tsv"] == "updated"
    after = {rel: (repo / rel).read_text() for rel in T.rename.PROTECTED_PATH_KEYED}

    # zero keys left on a deleted donor
    assert T.vanished({rel: text.encode() for rel, text in after.items()}, {A, B}) == []
    assert not (repo / A).exists() and not (repo / B).exists()
    # totals: every distinct key survives under the TU; counts and hatch totals are kept
    for rel in T.KEYED_LINES:
        assert set(tails(after[rel])) == set(tails(before[rel]))
    assert f"{TU}\t?a@@YAHXZ\t?x@@YAXXZ\t0x00005000\twrong" in after["reverse/code_identity_baseline.tsv"]
    assert keys(after["reverse/data_check_baseline.txt"]).count(f"{TU}\twrong-name\t?g_00A00000@@3HA\t0x00A00000") == 1
    assert hatch_totals(after["reverse/hatch_baseline.tsv"]) == hatch_totals(before["reverse/hatch_baseline.tsv"])
    assert f"\t{TU}\t" in after["reverse/hatch_baseline.tsv"]
    assert override_totals(after["reverse/flag_overrides.csv"]) == override_totals(before["reverse/flag_overrides.csv"])
    assert f"{TU},-O2,2,1,region default loses rows" in after["reverse/flag_overrides.csv"]
    assert f"?g@@3HA,{TU},provisional,?g@@3HA;?s@@3HA@{TU}," in after["reverse/data_ledger.csv"]

    # the hooks: verify-removed reads a transfer, no vanished-source accounting is needed
    os.environ["REPAIR_ROOT"] = str(repo)
    try:
        import repair_queue
        rq = importlib.reload(repair_queue)
    finally:
        del os.environ["REPAIR_ROOT"]
    for kind in ("data", "identity"):
        removed, staged = rq.removed_keys(kind)
        assert removed and all(rq._debt_transferred(kind, src, ks, staged) for src, ks in removed.items())
    assert rq.verify_removed_debt(build_cmd=[sys.executable, "-c", "raise SystemExit(1)"],
                                  header_verdict=lambda *a: ["unexpected"]) == []
    assert rq.verify_missing_debt("") == []
    # the shrink-only gates read the re-keyed lines as a move, not growth
    staged = set(git(repo, "diff", "--cached", "--name-only").stdout.split())
    assert protected_paths.growth(["HEAD"], ":", staged, set()) == []
    head, index = (git(repo, "show", f"{r}reverse/code_identity_baseline.tsv").stdout for r in ("HEAD:", ":"))
    grown = set(keys(index)) - set(keys(head))
    assert grown and protected_paths.transferred("HEAD", ":", grown, set(keys(head)) - set(keys(index))) == grown


def test_a_key_the_tu_already_holds_collapses_and_prints_its_debt_retired_line(repo):
    path = repo / "reverse/data_check_baseline.txt"
    path.write_text(DATA + f"{TU}\tduplicate-def\t?TheX@@3HA\t0x00A00004\n", newline="\n")
    (repo / TU).write_text("int t() { return 0; }\n")
    carry = T.Carry(repo, TU, [TU, A, B], {**TEXTS, TU: "int t() { return 0; }\n"}, merged_text(), "-O2")
    line = f"{B}\tduplicate-def\t?TheX@@3HA\t0x00A00004"
    assert carry.collapsed == [("reverse/data_check_baseline.txt", line)]
    assert carry.retired() == [f"Debt-Retired: {line} {B} merged into {TU}, which already holds this key"]
    assert line not in carry.new["reverse/data_check_baseline.txt"].decode()


def test_a_merge_that_would_leave_a_key_on_a_deleted_donor_is_refused(repo):
    # a register line naming the donor in a column carry() does not rewrite
    path = repo / "reverse/data_check_baseline.txt"
    path.write_text(DATA + f"{C}\twrong-name\t{A}\t0x00A00008\n", newline="\n")
    carry = T.Carry(repo, TU, [A, B], TEXTS, merged_text(), "-O2")
    assert any("would still key a deleted donor" in p for p in carry.problems)


def test_hatch_growth_in_the_merged_text_is_refused(repo):
    text = merged_text() + '#pragma optimize("", off)\n'
    carry = T.Carry(repo, TU, [A, B], TEXTS, text, "-O2")
    assert any("escape-hatch" in p for p in carry.problems)


def test_overrides_disagreeing_with_the_verified_flags_are_refused(repo):
    carry = T.Carry(repo, TU, [A, B], TEXTS, merged_text(), "-O1")
    assert any("disagree" in p for p in carry.problems)


def test_without_protected_keys_nothing_is_carried(repo):
    for rel in T.rename.PROTECTED_PATH_KEYED:
        text = (repo / rel).read_text()
        (repo / rel).write_text("".join(l for l in text.splitlines(True) if A not in l and B not in l),
                                newline="\n")
    carry = T.Carry(repo, TU, [A, B], {A: "int a();\n", B: "int b();\n"}, "int a();\nint b();\n", "-O2")
    assert carry.moved == {} and carry.problems == [] and carry.trailer() is None
