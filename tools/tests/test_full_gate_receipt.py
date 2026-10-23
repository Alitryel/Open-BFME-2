"""A passed full gate carries to a later push only from a commit of this
clone, while the verifier is unchanged and header_dependents can bound the
change between them (tools/full_gate_receipt.py)."""
import os
import subprocess
import sys
import time
from pathlib import Path

import pytest
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import full_gate_receipt as R


def git(root, *args):
    return subprocess.run(["git", *args], cwd=root, capture_output=True, text=True, check=True).stdout.strip()


def commit(root, path, text):
    (root / path).parent.mkdir(parents=True, exist_ok=True)
    (root / path).write_text(text)
    git(root, "add", path)
    git(root, "-c", "user.name=t", "-c", "user.email=t@t", "commit", "-q", "-m", path)
    return git(root, "rev-parse", "HEAD")


@pytest.fixture
def repo(tmp_path, monkeypatch):
    root = tmp_path / "repo"
    root.mkdir()
    git(root, "init", "-q")
    monkeypatch.setattr(R, "ROOT", root)
    monkeypatch.setattr(R, "bounded", lambda old, new: True)
    return root


def test_a_rebased_push_carries_the_full_gate_it_passed(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    assert R.find(c0) == c0
    c1 = commit(repo, "Code/b.cpp", "2")  # master moved: the rebased push
    assert R.find(c1) == c0


def test_no_carry_across_a_verifier_change(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    assert R.find(commit(repo, "tools/build.py", "changed")) is None
    c2 = commit(repo, "Code/c.cpp", "3")
    R.record(c2)
    assert R.find(commit(repo, ".githooks/pre-push", "changed")) is None


def test_no_carry_when_the_change_is_unbounded(repo, monkeypatch):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    c1 = commit(repo, "vendor/stlport/x.h", "2")
    monkeypatch.setattr(R, "bounded", lambda old, new: False)
    assert R.find(c1) is None


def test_expired_or_foreign_receipts_carry_nothing(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    stale = time.time() - (R.KEEP_HOURS + 1) * 3600
    os.utime(R.receipts_dir() / c0, (stale, stale))
    assert R.find(commit(repo, "Code/b.cpp", "2")) is None
    (R.receipts_dir() / ("f" * 40)).write_text("0\n")  # not a commit of this clone
    assert R.recorded() == []


def test_the_nearest_receipt_is_tried_first(repo, monkeypatch):
    far = commit(repo, "Code/a.cpp", "1")
    R.record(far)
    commit(repo, "Code/b.cpp", "2")
    near = commit(repo, "Code/c.cpp", "3")
    R.record(near)
    os.utime(R.receipts_dir() / near, (time.time() - 60, time.time() - 60))  # older record, nearer tree
    tried = []
    monkeypatch.setattr(R, "bounded", lambda old, new: tried.append(old) or True)
    assert R.find(commit(repo, "Code/d.cpp", "4")) == near and tried == [near]


def test_no_carry_across_a_tree_wide_baseline_change(repo):
    c0 = commit(repo, "Code/a.cpp", "1")
    R.record(c0)
    assert R.find(commit(repo, "reverse/gate_baseline.txt", "one debt line fewer")) is None
    c2 = commit(repo, "Code/b.cpp", "2")
    R.record(c2)
    # the exception-data and converged lists are re-audited by the hook instead
    assert R.find(commit(repo, "reverse/eh_baseline.csv", "shrunk")) == c2


def test_cross_checks_byte_verify_what_they_had_to_rebuild(monkeypatch):
    import build
    import check_module_registry
    a, b = build.ROOT / "Code" / "a.cpp", build.ROOT / "Code" / "b.cpp"
    rows = [{"source": "Code/a.cpp"}, {"source": "Code/b.cpp"}]
    stale = {"calls": 0}

    def stale_sources(sources, outputs, workers=1, **kw):
        stale["calls"] += 1
        return [a] if stale["calls"] == 1 else []   # a was not current; the compile fixed it
    verified = []
    monkeypatch.setattr(build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "stale_sources", stale_sources)
    monkeypatch.setattr(build, "compile_rows", lambda rows, sources, **kw: None)
    monkeypatch.setattr(build, "main", lambda only=None, **kw: verified.append(kw["exact_sources"]))
    monkeypatch.setattr(build, "verify_dir32_consistency", lambda rows: None)
    monkeypatch.setattr(check_module_registry, "verify", lambda: None)
    assert build.cross_source_checks() == 0
    assert verified == [{"Code/a.cpp"}]

    def mismatch(only=None, **kw):
        raise SystemExit(1)
    stale["calls"] = 0
    monkeypatch.setattr(build, "main", mismatch)
    assert build.cross_source_checks() == 1


@pytest.mark.parametrize("failure", [None, "bytes", "restore", "moved", "compile-race", "dir32", "module"])
def test_large_restored_scope_stays_exact_and_fail_closed(monkeypatch, failure):
    import build
    import check_module_registry
    # Crossing the former 1,024 threshold must not request a full gate. One
    # unchanged source still participates in the global checks and final currency.
    rows = [{"source": f"Code/part{i}.cpp"} for i in range(1026)]
    sources = [build.ROOT / row["source"] for row in rows]
    rebuilt = sources[:-1]
    calls = []
    moved_during_compile = []
    def compile_rows(rows, scope, **kw):
        assert scope == rebuilt
        if failure == "compile-race":
            # Inputs of the initially current TU moved after the snapshot. It
            # must not be silently restored outside the captured byte scope.
            moved_during_compile.append(sources[-1])
    def stale_sources(scope, outputs, workers=1, **kw):
        calls.append(list(scope))
        if len(calls) == 1:
            return rebuilt
        if failure == "restore" and len(calls) == 2:
            return [rebuilt[0]]
        if failure == "moved" and len(calls) == 3:
            return [sources[-1]]
        if moved_during_compile and sources[-1] in scope:
            return moved_during_compile
        return []
    verified, global_rows, modules = [], [], []
    def verify(only=None, *, exact_sources=None):
        assert only is None and exact_sources is not None
        verified.append(exact_sources)
        if failure == "bytes":
            raise SystemExit(1)
    def dir32(scope):
        global_rows.append(scope)
        if failure == "dir32":
            raise SystemExit(1)
    def module():
        modules.append(True)
        if failure == "module":
            raise SystemExit(1)
    monkeypatch.setattr(build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "stale_sources", stale_sources)
    monkeypatch.setattr(build, "compile_rows", compile_rows)
    monkeypatch.setattr(build, "main", verify)
    monkeypatch.setattr(build, "verify_dir32_consistency", dir32)
    monkeypatch.setattr(check_module_registry, "verify", module)
    assert build.cross_source_checks() == (0 if failure is None else 1)
    if failure == "restore":
        assert verified == []
    else:
        assert verified == [{row["source"] for row in rows[:-1]}]
    if failure not in ("restore", "bytes"):
        assert global_rows == [rows] and modules == [True]
        assert calls[-1] == sources


def test_exact_scope_runs_every_scoped_reference_gate(monkeypatch):
    import build
    import data_rows
    rows = [{"source": "Code/a.cpp", "name": "a"},
            {"source": "Code/nested/Code/a.cpp", "name": "b"},
            {"source": "Code/other.cpp", "name": "Code/a.cpp"}]
    scope = {"Code/a.cpp"}
    calls = []
    monkeypatch.setattr(build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "verify_source_claims", lambda only, **kw: calls.append(("claims", kw["exact_sources"])))
    monkeypatch.setattr(build, "verify_functions", lambda only, **kw: calls.append(("functions", kw["exact_sources"])))
    monkeypatch.setattr(data_rows, "load", lambda: rows)
    monkeypatch.setattr(data_rows, "verify", lambda **kw: calls.append(("data", kw["sources"])))
    for label in ("string", "float", "import"):
        monkeypatch.setattr(build, f"verify_{label}_refs", lambda scope, label=label: calls.append((label, scope)))
    build.main(exact_sources=scope)
    assert calls == [("claims", scope), ("data", ["Code/a.cpp"]), ("functions", scope),
                     ("string", rows[:1]), ("float", rows[:1]), ("import", rows[:1])]
    with pytest.raises(SystemExit, match="empty exact source scope"):
        build.main(exact_sources=set())


def test_exact_function_scope_checks_bytes_without_rewriting_full_derived_file(tmp_path, monkeypatch):
    import build
    source = tmp_path / "Code/a.cpp"
    source.parent.mkdir()
    source.write_text("// fixture\n")
    rows = [{"source": "Code/a.cpp", "name": "a", "target_rva": "0x1000"},
            {"source": "Code/else.cpp", "name": "Code/a.cpp", "target_rva": "0x2000"}]
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "load_all_function_rows", lambda: rows)
    monkeypatch.setattr(build, "load_symbol_map", lambda: {})
    monkeypatch.setattr(build, "compile_rows", lambda rows, sources: {})
    monkeypatch.setattr(build, "row_object", lambda row: None)
    monkeypatch.setattr(build, "body_extent_problems", lambda *a, **kw: [])
    def no_derived_write(patches):
        pytest.fail("exact source scope must not overwrite the full derived index")
    monkeypatch.setattr(build, "write_reloc_names", no_derived_write)
    patch = {"target": b"\xc3", "bytes": b"\xc3", "masked": False,
             "note": "", "verified_folds": set(), "unresolved": []}
    visited = []
    def compile_function(row, symbols, obj):
        visited.append(row["source"])
        return patch
    monkeypatch.setattr(build, "compile_function", compile_function)
    assert build.verify_functions(exact_sources={"Code/a.cpp"}) == [patch]
    assert visited == ["Code/a.cpp"]
    patch["bytes"] = b"\xcc"
    with pytest.raises(SystemExit):
        build.verify_functions(exact_sources={"Code/a.cpp"})


@pytest.mark.parametrize("unchanged_funclet", [False, True])
def test_cross_source_global_proof_still_checks_unchanged_owners(tmp_path, monkeypatch, capsys, unchanged_funclet):
    import build
    import check_module_registry
    import struct
    (tmp_path / "reverse").mkdir()
    (tmp_path / "reverse/dir32_consistency_whitelist.txt").write_text("")
    objects = [tmp_path / "a.obj", tmp_path / "b.obj"]
    for obj in objects:
        obj.write_bytes(b"fixture")
    rows = [{"source": f"Code/{letter}.cpp", "name": f"function{i}",
             "target_rva": hex(0x1000 + i * 0x10), "target_size": "7", "notes": ""}
            for i, letter in enumerate("ab")]
    if unchanged_funclet:
        rows[1]["notes"] = "gen-funclet;object-symbol=$L123;parent=parent"
    sources = [tmp_path / row["source"] for row in rows]
    currency_calls = []
    def stale(scope, outputs, workers=1, **kw):
        currency_calls.append(list(scope))
        return sources[:1] if len(currency_calls) == 1 else []
    def bounded(only=None, *, exact_sources):
        assert only is None and exact_sources == {"Code/a.cpp"}
    visited = []
    def object_for(row):
        visited.append(row["source"])
        return objects[0 if row["source"] == "Code/a.cpp" else 1]
    collisions = []
    def unchanged_owner_collision(row, symbol, obj, retail):
        assert row is rows[1]
        collisions.append(symbol)
        raise SystemExit(1)
    monkeypatch.setattr(build, "ROOT", tmp_path)
    monkeypatch.setattr(build, "ensure_case_shims", lambda: None)
    monkeypatch.setattr(build, "ensure_reference_current", lambda: None)
    monkeypatch.setattr(build, "load_function_rows", lambda: rows)
    monkeypatch.setattr(build, "stale_sources", stale)
    monkeypatch.setattr(build, "compile_rows", lambda rows, sources, **kw: None)
    monkeypatch.setattr(build, "main", bounded)
    monkeypatch.setattr(build, "require_row_object", object_for)
    monkeypatch.setattr(build, "read_target_bytes", lambda rva, size:
                        b"\xd9\x05" + struct.pack("<I", 0x402000 + (rva - 0x1000) * 0x10) + b"\xc3")
    monkeypatch.setattr(build, "read_object_symbol_bytes", lambda *args:
                        (b"\xd9\x05\x00\x00\x00\x00\xc3", [(2, 6, "_shared_global")]))
    monkeypatch.setattr(build, "_object_layout", lambda *args: (b"", [], []))
    monkeypatch.setattr(build, "read_funclet", unchanged_owner_collision)
    monkeypatch.setattr(check_module_registry, "verify", lambda: None)
    assert build.cross_source_checks() == 1
    assert {"Code/a.cpp", "Code/b.cpp"} <= set(visited)
    assert collisions == (["$L123"] if unchanged_funclet else [])
    if not unchanged_funclet:
        assert "NEW inconsistent symbol" in capsys.readouterr().out
