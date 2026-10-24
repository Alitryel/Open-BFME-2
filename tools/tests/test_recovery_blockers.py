"""Concurrent investigation leases preserve ownership and append-only evidence."""
from concurrent.futures import ThreadPoolExecutor
import json
from pathlib import Path
import sys
import threading

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
from recovery_blockers import BlockerQueue, QueueError, main


@pytest.fixture
def queue(tmp_path):
    return BlockerQueue(tmp_path / "blockers.sqlite3")


def add(queue, key="shift-codegen", **kwargs):
    return queue.add(key, "Native shift instruction", "Preserve native CL mask",
                     owner="coordinator", evidence="reverse/attempt_support/shifts.md", **kwargs)


def test_concurrent_connections_only_one_wins_lease(queue):
    add(queue)
    ready = threading.Barrier(8)

    def compete(index):
        worker = BlockerQueue(queue.path)
        ready.wait(timeout=10)
        try:
            worker.claim("shift-codegen", owner=f"worker-{index}")
            return f"worker-{index}"
        except QueueError:
            return None

    with ThreadPoolExecutor(max_workers=8) as pool:
        winners = [owner for owner in pool.map(compete, range(8)) if owner]
    assert len(winners) == 1
    row = queue.show("shift-codegen")
    assert row["owner"] == winners[0]
    assert [entry["action"] for entry in row["evidence"]] == ["add", "claim"]


def test_lease_blocks_other_edits_and_stale_release(queue):
    add(queue)
    queue.claim("shift-codegen", owner="one")
    for action in (
        lambda: queue.update("shift-codegen", owner="two", evidence="new", title="stolen"),
        lambda: queue.release("shift-codegen", owner="two", evidence="release"),
        lambda: queue.resolve("shift-codegen", owner="two", evidence="done"),
    ):
        with pytest.raises(QueueError):
            action()
    assert queue.show("shift-codegen")["title"] == "Native shift instruction"


def test_expiry_reclaim_renew_and_resolution(queue):
    now = [100.0]
    queue.clock = lambda: now[0]
    add(queue)
    queue.claim("shift-codegen", owner="one", lease_seconds=10)
    now[0] = 106
    assert queue.claim("shift-codegen", owner="one", lease_seconds=10)["lease_until"] == 116
    now[0] = 117
    assert queue.show("shift-codegen")["lease_expired"]
    assert queue.list(claimable=True)[0]["id"] == "shift-codegen"
    with pytest.raises(QueueError, match="required lease"):
        queue.resolve("shift-codegen", owner="one", evidence="expired")
    queue.claim("shift-codegen", owner="two", lease_seconds=10)
    with pytest.raises(QueueError):
        queue.release("shift-codegen", owner="one", evidence="stale")
    final = queue.resolve("shift-codegen", owner="two", evidence="tracked/native-proof.md")
    assert final["status"] == "resolved" and final["owner"] is None
    assert final["evidence"][-1]["text"] == "tracked/native-proof.md"


def test_dependencies_gate_claims_and_cycles_rejected(queue):
    add(queue, "compiler")
    add(queue, depends_on=["compiler"], affected_rvas=["0x629780", 0x6297A0])
    with pytest.raises(QueueError, match="unresolved dependencies"):
        queue.claim("shift-codegen", owner="one")
    with pytest.raises(QueueError, match="cycle"):
        queue.update("compiler", owner="coordinator", evidence="cycle", depends_on=["shift-codegen"])
    queue.claim("compiler", owner="one")
    queue.resolve("compiler", owner="one", evidence="compiler proof")
    row = queue.claim("shift-codegen", owner="two")
    assert row["affected_rvas"] == ["0x00629780", "0x006297A0"]


def test_updates_append_evidence_and_keep_affected_rvas(queue):
    add(queue, affected_rvas=["0x1000"])
    queue.update("shift-codegen", owner="one", evidence="second trial", affected_rvas=["0x2000"])
    row = queue.show("shift-codegen")
    assert row["affected_rvas"] == ["0x00001000", "0x00002000"]
    assert [entry["text"] for entry in row["evidence"]] == ["reverse/attempt_support/shifts.md", "second trial"]
    with pytest.raises(QueueError, match="already exists"):
        add(queue)
    assert len(queue.show("shift-codegen")["evidence"]) == 2


def test_blocked_requires_explicit_evidence_to_reopen(queue):
    add(queue)
    queue.claim("shift-codegen", owner="one")
    queue.release("shift-codegen", owner="one", evidence="remaining native CL mask", blocked=True)
    with pytest.raises(QueueError, match="blocked"):
        queue.claim("shift-codegen", owner="two")
    queue.update("shift-codegen", owner="two", evidence="new compiler prerequisite landed", status="open")
    assert queue.claim("shift-codegen", owner="two")["status"] == "in_progress"


@pytest.mark.parametrize("key", ["", "../escape", "Uppercase", "a b", "a" * 97])
def test_invalid_ids_rejected(queue, key):
    with pytest.raises(QueueError):
        add(queue, key)
    assert queue.list() == []


@pytest.mark.parametrize("address", ["oops", -1, 0, True, "0x100000000"])
def test_invalid_rvas_rejected(queue, address):
    with pytest.raises(QueueError):
        add(queue, affected_rvas=[address])
    assert queue.list() == []


@pytest.mark.parametrize("duration", [0, -1, float("nan"), float("inf"), 86401, "oops"])
def test_invalid_lease_rejected(queue, duration):
    add(queue)
    with pytest.raises(QueueError):
        queue.claim("shift-codegen", owner="one", lease_seconds=duration)
    assert queue.show("shift-codegen")["owner"] is None


def test_unknown_dependency_and_empty_evidence_rejected(queue):
    with pytest.raises(QueueError, match="unknown blocker"):
        add(queue, depends_on=["missing"])
    assert queue.list() == []
    add(queue)
    with pytest.raises(QueueError, match="evidence"):
        queue.update("shift-codegen", owner="one", evidence=" ")


def test_cli_uses_explicit_shared_database_and_reports_conflict(tmp_path, capsys):
    common = ["--db", str(tmp_path / "fleet.sqlite3")]
    assert main(common + ["add", "rounding", "--title", "x87", "--prerequisite", "PUSH ECX",
                          "--owner", "root", "--evidence", "rounding.md", "--rva", "0x15f520"]) == 0
    assert json.loads(capsys.readouterr().out)["id"] == "rounding"
    assert main(common + ["claim", "rounding", "--owner", "one"]) == 0
    capsys.readouterr()
    assert main(common + ["claim", "rounding", "--owner", "two"]) == 2
    assert "leased by one" in capsys.readouterr().err
