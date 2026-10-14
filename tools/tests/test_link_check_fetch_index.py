"""--fetch-index: the published census index replaces a missing or older local
one, never a newer one, and a download that is not an index replaces nothing."""
import io
import pickle
import sys
from pathlib import Path

import pytest
sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import link_check as C


def index(date, commit="abc1234567"):
    return pickle.dumps({"meta": {"date": date, "commit": commit}, "blockers": {}})


@pytest.fixture
def served(tmp_path, monkeypatch):
    out = tmp_path / "build" / "link_census"
    monkeypatch.setattr(C, "ROOT", tmp_path)
    monkeypatch.setattr(C, "INDEX", out / "link_index.pkl")
    monkeypatch.setattr(C.link_census, "OUT", out)
    body = {}
    monkeypatch.setattr("urllib.request.urlopen", lambda url, timeout: io.BytesIO(body["data"]))
    monkeypatch.setattr(C, "contains", lambda commit, ref="HEAD": not commit.startswith("future"))
    return out / "link_index.pkl", body


def leftovers(path):
    return [p.name for p in path.parent.iterdir() if p.suffix == ".download"]


def test_missing_index_is_downloaded(served):
    path, body = served
    body["data"] = index("2026-10-14 15:43")
    assert C.fetch_index() == 0
    assert C.index_meta(path)["date"] == "2026-10-14 15:43"
    assert leftovers(path) == []


def test_older_local_index_is_replaced_and_newer_kept(served):
    path, body = served
    path.parent.mkdir(parents=True)
    path.write_bytes(index("2026-10-13 16:47", "old0000000"))
    body["data"] = index("2026-10-14 15:43", "new0000000")
    C.fetch_index()
    assert C.index_meta(path)["commit"] == "new0000000"
    body["data"] = index("2026-10-12 08:00", "older00000")
    C.fetch_index()
    assert C.index_meta(path)["commit"] == "new0000000"


def test_a_download_that_is_not_an_index_replaces_nothing(served):
    path, body = served
    path.parent.mkdir(parents=True)
    path.write_bytes(index("2026-10-13 16:47", "old0000000"))
    body["data"] = b"<html>Not Found</html>"
    with pytest.raises(SystemExit):
        C.fetch_index()
    assert C.index_meta(path)["commit"] == "old0000000"
    assert leftovers(path) == []


def test_an_index_of_a_commit_the_checkout_lacks_replaces_nothing(served):
    path, body = served
    path.parent.mkdir(parents=True)
    path.write_bytes(index("2026-10-13 16:47", "old0000000"))
    body["data"] = index("2026-10-14 15:43", "future0000")
    with pytest.raises(SystemExit, match="lacks census commit"):
        C.fetch_index()
    assert C.index_meta(path)["commit"] == "old0000000"
    assert leftovers(path) == []


def test_only_a_clean_history_census_is_published(served, monkeypatch):
    path, _ = served
    path.parent.mkdir(parents=True)
    path.write_bytes(index("2026-10-14 15:43"))
    monkeypatch.setattr(C, "_git", lambda *a, **k: "")
    calls = []
    monkeypatch.setattr(C.subprocess, "run", lambda *a, **k: calls.append(a) or C.subprocess.CompletedProcess(a, 0))
    with pytest.raises(SystemExit, match="clean tree"):
        C.publish_index()
    assert calls == []
    path.write_bytes(pickle.dumps({"meta": {"date": "2026-10-14 15:43", "commit": "abc1234567",
                                            "clean_tree": True}, "blockers": {}}))
    assert C.publish_index() == 0
    assert any(cmd[0][:3] == ["gh", "release", "upload"] for cmd in calls)
