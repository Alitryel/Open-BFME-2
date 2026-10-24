"""dx_migration: queue classes, and build.py's DirectX SDK manifest check."""
import hashlib
import sys
from pathlib import Path
from types import SimpleNamespace

import pytest

sys.path.insert(0, str(Path(__file__).resolve().parents[1]))
import build  # noqa: E402
import dx_migration  # noqa: E402

SOURCE = dx_migration.ROOT / "Code" / "Libraries" / "Source" / "WWVegas" / "WW3D2" / "DX8ConvertColorVector4O1.cpp"
ROWS = [{"name": "?f@@YAXXZ"}]


def _classify(monkeypatch, trials):
    """classify() with the untouched trials returning `trials` in order (as-is,
    then as-is+psdk), every compiled row byte-true and no rewrite to try."""
    monkeypatch.setattr(dx_migration, "sidecar_deps", lambda build, output: [])
    monkeypatch.setattr(dx_migration, "compare_rows",
                        lambda build, rows, output, symbol_map, rename=False: (len(rows), None))
    calls = iter(trials)
    monkeypatch.setattr(dx_migration, "trial_compile", lambda *args, **kwargs: next(calls))
    monkeypatch.setattr(dx_migration, "sdk_headers", lambda includes: list(includes))
    monkeypatch.setattr(dx_migration, "prepare_rewrite", lambda source, deps, names, overlay: (None, []))
    fake = SimpleNamespace(obj_path=lambda source: "baseline")
    return dx_migration.classify(fake, SOURCE, ROWS, {}, set())


def test_dx8_match_is_served_for_assessment_not_dismissed(monkeypatch):
    record = _classify(monkeypatch, [(False, [], "C2146"),
                                     (True, ["d3d8.h", "d3d8types.h", "d3d9.h"], None)])
    assert record["class"] == "dx8-observed"
    assert record["detail"].startswith("DX8 headers observed; compatibility unresolved")
    assert "coincid" not in record["detail"] and "agreement" not in record["detail"]
    assert record["edits"] == "+platformsdk"
    assert "dx8-observed" in dx_migration.SERVED


def test_dx9_only_match_is_as_is(monkeypatch):
    record = _classify(monkeypatch, [(True, ["d3d9.h", "d3dx9math.h"], None)])
    assert record["class"] == "as-is" and record["sdk"] == "d3d9.h,d3dx9math.h"


def test_servable_order_and_classes(tmp_path, monkeypatch):
    queue = tmp_path / "q.tsv"
    monkeypatch.setattr(dx_migration, "QUEUE", queue)
    dx_migration.write_queue([
        {"source": "a.cpp", "class": "blocked", "matched_rows": 9},
        {"source": "b.cpp", "class": "dx8-observed", "matched_rows": 5},
        {"source": "c.cpp", "class": "mechanical", "matched_rows": 1},
        {"source": "d.cpp", "class": "mismatch", "matched_rows": 3},
    ])
    assert [r["source"] for r in dx_migration.servable()] == ["c.cpp", "b.cpp"]
    assert dx_migration.serve()["source"] == "c.cpp"


# ------------------------------------------------------------ SDK manifest

def _sdk(tmp_path):
    root = tmp_path / "sdk"
    files = {"Include/d3d9.h": b"// d3d9\n", "Lib/x86/d3dx9.lib": b"!<arch>\n"}
    lines = ["# header"]
    for rel, data in files.items():
        (root / rel).parent.mkdir(parents=True, exist_ok=True)
        (root / rel).write_bytes(data)
        lines.append(f"{hashlib.sha256(data).hexdigest()}  {len(data):>9}  {rel}")
    manifest = tmp_path / "manifest.txt"
    manifest.write_text("\n".join(lines) + "\n")
    return root, manifest


def test_verify_dxsdk_accepts_listed_files(tmp_path):
    root, manifest = _sdk(tmp_path)
    assert build.verify_dxsdk(root, build.dxsdk_manifest(manifest)) == []


def test_verify_dxsdk_refuses_missing_changed_and_unlisted(tmp_path):
    root, manifest = _sdk(tmp_path)
    (root / "Lib" / "x86" / "d3dx9.lib").unlink()
    (root / "Include" / "d3d9.h").write_bytes(b"// edited\n")
    (root / "Include" / "windows.h").write_bytes(b"")
    problems = build.verify_dxsdk(root, build.dxsdk_manifest(manifest))
    assert problems == ["differs Include/d3d9.h", "missing Lib/x86/d3dx9.lib", "unlisted Include/windows.h"]


def test_dxsdk_root_fails_loudly_on_a_damaged_sdk(tmp_path, monkeypatch):
    root, manifest = _sdk(tmp_path)
    (root / "Include" / "d3d9.h").write_bytes(b"// edited\n")
    monkeypatch.setattr(build, "DXSDK_DIR", root)
    monkeypatch.setattr(build, "DXSDK_MANIFEST", manifest)
    build.dxsdk_root.cache_clear()
    try:
        with pytest.raises(SystemExit, match="differs Include/d3d9.h"):
            build.dxsdk_root()
    finally:
        build.dxsdk_root.cache_clear()


def test_committed_sdk_matches_its_provenance():
    rows = build.dxsdk_manifest()
    paths = {rel for rel, _, _ in rows}
    assert "Include/d3d9.h" in paths and "Include/d3dx9core.h" in paths
    assert all(rel.startswith(("Include/", "Lib/x86/", "License/")) for rel in paths)
    assert build.verify_dxsdk(build.DXSDK_DIR, rows) == []
    build.dxsdk_root.cache_clear()
    try:
        assert build.dxsdk_include_arg() == "vendor/dxsdk-aug2005/Include"
    finally:
        build.dxsdk_root.cache_clear()
