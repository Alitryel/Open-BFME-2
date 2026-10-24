"""next_work.py --tier dx: ledger check first, and --claim takes file scopes."""
import json
import sys
from pathlib import Path

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import dx_migration  # noqa: E402
import next_work  # noqa: E402

QUEUE = [
    {"source": "Code/A.cpp", "class": "mechanical", "matched_rows": "4", "edits": "d3d8.h->d3d9.h"},
    {"source": "Code/B.cpp", "class": "dx8-observed", "matched_rows": "2", "edits": "+platformsdk"},
]


@pytest.fixture
def run(monkeypatch):
    def main(argv, claim=None, ledger=lambda: "ledger healthy"):
        monkeypatch.setattr(sys, "argv", ["next_work.py", "--tier", "dx", *argv])
        monkeypatch.setattr(next_work, "check_ledger", ledger)
        monkeypatch.setattr(dx_migration, "read_queue", lambda: [dict(r) for r in QUEUE])
        monkeypatch.setattr(next_work.claims, "settle", lambda *a, **k: [])
        if claim:
            monkeypatch.setattr(next_work.claims, "claim", claim)
        else:
            def no_claim(*args, **kwargs):
                raise AssertionError("claimed without --claim")
            monkeypatch.setattr(next_work.claims, "claim", no_claim)
        return next_work.main()
    return main


def test_red_ledger_stops_the_dx_tier(run):
    def red():
        raise SystemExit(2)
    with pytest.raises(SystemExit) as exit_info:
        run([], ledger=red)
    assert exit_info.value.code == 2


def test_unclaimed_serves_first_unit(run, capsys):
    assert run([]) == 0
    assert "dx tier: Code/A.cpp  [mechanical] 4 row(s)" in capsys.readouterr().out


def test_claim_takes_a_file_scope(run, capsys):
    calls = []

    def claim(keys, note=""):
        calls.append((list(keys), note))
        return list(keys), []
    assert run(["--claim"], claim=claim) == 0
    out = capsys.readouterr().out
    assert calls == [(["file:Code/A.cpp"], "next_work dx")]
    assert "claim: file:Code/A.cpp held on origin" in out
    assert "dx tier: Code/A.cpp" in out


def test_claim_contention_moves_to_the_next_unit(run, capsys):
    calls = []

    def claim(keys, note=""):
        calls.append(keys[0])
        key = next_work.claims.key_of(keys[0])
        return ([], [key]) if keys[0] == "file:Code/A.cpp" else ([key], [])
    assert run(["--claim", "--json"], claim=claim) == 0
    out = json.loads(capsys.readouterr().out)
    assert calls == ["file:Code/A.cpp", "file:Code/B.cpp"]
    assert out["selection"]["source"] == "Code/B.cpp"
    assert out["claim"] == "claim: file:Code/B.cpp held on origin"


def test_claim_skips_peer_held_unit_when_origin_fails(run, capsys):
    def claim(keys, note=""):
        key = next_work.claims.key_of(keys[0])
        raise next_work.claims.ClaimsUnavailable(
            "claims: offline", refused=[key] if keys[0] == "file:Code/A.cpp" else [])
    assert run(["--claim"], claim=claim) == 0
    captured = capsys.readouterr()
    assert "dx tier: Code/B.cpp" in captured.out
    assert "without a shared claim" in captured.err


def test_everything_held_serves_nothing(run, capsys):
    def claim(keys, note=""):
        return [], [next_work.claims.key_of(keys[0])]
    assert run(["--claim"], claim=claim) == 0
    assert "dx tier: nothing queued" in capsys.readouterr().out
