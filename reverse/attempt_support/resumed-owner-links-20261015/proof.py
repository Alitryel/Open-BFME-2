"""Read-only local link preview for the resumed owner/declaration repairs.

The published census is left unchanged. A deleted split provider is removed
from an in-memory copy using link_check's normal index-update operation.
This is a per-object prediction, not a whole-program link/placement proof.
"""
import hashlib
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[3]
sys.path.insert(0, str(ROOT / "tools"))
import build
import link_check as ck
import link_census as lc

sources = [
    "Code/GameEngine/Source/Common/BfmeConv815.cpp",
    "Code/GameEngine/Source/GameLogic/ScriptEngine/ScriptActions_playerOwnershipOfTypeCounter.cpp",
    "Code/GameEngine/Source/GameLogic/Object/Behavior/GettingBuiltBehaviorRva0045479A.cpp",
    "Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioCache.cpp",
    "Code/GameEngineDevice/Source/MilesAudioDevice/MilesAudioManagerRva00059EAE.cpp",
]
providers = [
    "Code/GameEngine/Source/GameLogic/ScriptEngine/Rva00376C50TemplateCollect.cpp",
    "Code/GameEngine/Source/GameLogic/Object/Behavior/CastleMemberBehaviorFind.cpp",
    "Code/GameEngine/Source/GameLogic/Object/ObjectGetShroudStatusForPlayer.cpp",
    "Code/GameEngine/Source/GameLogic/Object/Behavior/BfmeItemE63CheckValid.cpp",
]
deleted = "Code/Libraries/Source/WWVegas/WWLib/Rva00051ADARef.cpp"
assert not (ROOT / deleted).exists()
rows = lc.ledger()
assert not any(row["source"] == deleted for row in rows)
idx = ck.load_index()
index_sha = hashlib.sha256(ck.INDEX.read_bytes()).hexdigest()
truth = lc.RetailTruth(rows)
ck.forget(idx, [build.obj_path(ROOT / deleted).name])
objects = {s: build.obj_path(ROOT / s) for s in sources + providers}
for s in sources:
    assert build.compile_is_current(ROOT / s, objects[s], strict=True), s
for s in providers:
    assert build.compile_is_current(ROOT / s, objects[s]), s
ck.refresh(idx, list(objects.values()), truth)
sizes = ck.source_bytes(set(sources))
checks = {}
for s in sources:
    checks[s] = ck.check_object(objects[s], idx, truth, s)
    ck.report(s, objects[s], checks[s], idx, sizes[s])
assert all(not any(v.values()) for v in checks.values()), checks
assert hashlib.sha256(ck.INDEX.read_bytes()).hexdigest() == index_sha
print(json.dumps({
    "index_sha256": index_sha,
    "retained_source_objects_strict_current": True,
    "removed_stale_provider": deleted,
    "local_predicted_linked_bytes": sum(sizes.values()),
    "closed_strict_link_gain_measured": False,
    "authored_byte_gain": 0,
    "checks": checks,
}, indent=2))
