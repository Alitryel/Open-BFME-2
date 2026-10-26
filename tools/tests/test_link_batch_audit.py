"""Outgoing shadow link audit: selected provider, retirement and stale evidence."""
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_batch_audit as A


def index():
    return {
        "objects": ["retail.obj", "ini.obj"],
        "comdat": {"insert_unique": [(0, "good", "retail"), (1, "bad", "wrong")]},
        "strong": {}, "common": {}, "alternates": {}, "digests": {},
        "blockers": {"Code/retail.cpp": {"object": "retail.obj", "linked": True},
                     "Code/INI.cpp": {"object": "ini.obj", "linked": True}},
        "bytes": {"Code/retail.cpp": 120, "Code/INI.cpp": 80},
        "selection": {"exceptions": {}, "owners": {}},
        "common_schema": A.link_check.COMMON_SCHEMA,
        "meta": {"commit": "a" * 40, "date": "today", "clean_tree": True},
    }


def test_existing_wrong_copy_can_become_first():
    saved = index()
    before = A.selected(saved, "insert_unique", {"retail.obj": 0, "ini.obj": 1})
    after = A.selected(saved, "insert_unique", {"ini.obj": 0, "retail.obj": 1})
    assert before == ("retail.obj", "ok")
    assert after == ("ini.obj", "wrong")


def test_retired_donor_removes_its_provider():
    saved = index()
    updated = A.overlay(saved, [], {"retail.obj"}, None)
    assert A.selected(saved, "insert_unique", {"retail.obj": 0, "ini.obj": 1}) == ("retail.obj", "ok")
    assert A.selected(updated, "insert_unique", {"ini.obj": 0}) == ("ini.obj", "wrong")
    assert "Code/retail.cpp" not in updated["blockers"]


def test_batch_reports_selection_loss_and_stale_baseline(monkeypatch, tmp_path, capsys):
    saved = index()
    marker = tmp_path / "index.pkl"
    marker.touch()
    current = tmp_path / "ini.obj"
    current.touch()
    monkeypatch.setattr(A.link_check, "INDEX", marker)
    monkeypatch.setattr(A.link_check, "load_index", lambda: saved)
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: {"ini.obj": 0, "retail.obj": 1})
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: {"Code/INI.cpp"})
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/INI.cpp"}])
    monkeypatch.setattr(A.link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(A.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(A.link_census, "ledger_owners", lambda rows: {})
    monkeypatch.setattr(A.build, "obj_path", lambda source: current)
    monkeypatch.setattr(A.link_census, "object_current", lambda source, obj: True)
    monkeypatch.setattr(A.link_census, "object_facts", lambda obj, truth: ([
        ("insert_unique", "bad", 10, "wrong")], [], [], []))
    monkeypatch.setattr(A, "overlay", lambda ix, objects, removed, truth: ix)
    monkeypatch.setattr(A.link_check, "check_object", lambda obj, ix, truth, source: {"unresolved": []})

    A.audit("a" * 40, "b" * 40, ["Code/INI.cpp"])
    output = capsys.readouterr().out
    assert "REVIEW wrong selected provider: insert_unique; selected retail.obj -> ini.obj" in output
    assert "INCONCLUSIVE baseline" not in output

    A.audit("c" * 40, "b" * 40, ["Code/INI.cpp"])
    output = capsys.readouterr().out
    assert "INCONCLUSIVE baseline" in output
    assert "REVIEW wrong selected provider" in output


def test_changed_unit_unresolved_reports_prior_bytes(monkeypatch, tmp_path, capsys):
    saved = index()
    marker = tmp_path / "index.pkl"
    marker.touch()
    current = tmp_path / "ini.obj"
    current.touch()
    monkeypatch.setattr(A.link_check, "INDEX", marker)
    monkeypatch.setattr(A.link_check, "load_index", lambda: saved)
    monkeypatch.setattr(A.link_check, "link_rank", lambda rows: {"retail.obj": 0, "ini.obj": 1})
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: {"Code/INI.cpp"})
    monkeypatch.setattr(A.link_census, "ledger", lambda: [{"source": "Code/INI.cpp"}])
    monkeypatch.setattr(A.link_census, "data_ledger", lambda: [])
    monkeypatch.setattr(A.link_census, "RetailTruth", lambda rows: None)
    monkeypatch.setattr(A.link_census, "ledger_owners", lambda rows: {})
    monkeypatch.setattr(A.build, "obj_path", lambda source: current)
    monkeypatch.setattr(A.link_census, "object_current", lambda source, obj: True)
    monkeypatch.setattr(A.link_census, "object_facts", lambda obj, truth: ([], [], ["__assert"], []))
    monkeypatch.setattr(A, "overlay", lambda ix, objects, removed, truth: ix)
    monkeypatch.setattr(A.link_check, "check_object", lambda obj, ix, truth, source: {"unresolved": ["__assert"]})
    A.audit("a" * 40, "b" * 40, ["Code/INI.cpp"])
    assert "LOST 80 previously linked source bytes: unresolved in Code/INI.cpp: __assert" in capsys.readouterr().out


def test_no_index_is_inconclusive(monkeypatch, tmp_path, capsys):
    monkeypatch.setattr(A, "changed_sources", lambda base, tip: {"Code/INI.cpp"})
    monkeypatch.setattr(A.link_check, "INDEX", tmp_path / "missing.pkl")
    A.audit("a", "b", [])
    assert "INCONCLUSIVE: census index missing" in capsys.readouterr().out
