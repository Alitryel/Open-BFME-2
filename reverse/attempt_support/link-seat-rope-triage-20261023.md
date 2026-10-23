# Link-seat follow-up, 2026-10-23

Inputs: BFME 2 `47b0299f54`, verified BFME 1 pointer
`96c88c73a5cd1a58fc2f8db691beea50acd996db`, published index
`b711de3634` (2026-10-23 14:28, retail-truth-4). Fetching the published
index imported 22,760 objects but did not advance its measurement commit.
No production edits or new linked-byte gain. No claims retained.

## Rope class prerequisite

Paired current-object command:

```
python3 tools/link_check.py Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/W3DRopeDrawDtor.cpp Code/GameEngineDevice/Source/W3DDevice/GameClient/Drawable/Draw/W3DRopeDrawCtor.cpp
```

Both units remain blocked, respectively 0/128 and 0/164 authored bytes in
the legacy preview. The destructor's primary
`??_7W3DRopeDraw@@6BDrawModule@@@` differs from the first copy, with no
retail address assigned to that table name. Its private DrawModule view has
only a destructor; the constructor includes the donor's fuller DrawModule
and W3DRopeDraw declarations. The destructor emits a public deleting destructor
(`UAE`), whereas the donor constructor emits a protected one (`MAE`).

The existing target row independently identifies native table VA BCBD60:
slot 0 is deleting destructor CA9D5 calling the 90-byte destructor CA8BC;
slot 4 is the class-name getter CA7F6. These facts establish ownership but
do not establish the donor table's complete BFME 2 contract. There is no
canonical W3DRopeDraw/DrawModule header registration to resolve the views.

The constructor also needs DrawModule::crc and a new_alloc deallocation
provider, and loses COMDATs for DrawModule's table/destructor/memory-pool
lookup, SegInfo vector teardown, W3DRopeDraw's module-name and rope-interface
getters, and its deleting destructor. Blindly copying the first table or
adding novtable would not prove a repair. No source trial was made. Resume
with a target-backed class contract and check both providers together.
The unreferenced alloc-proxy deallocation diagnostic is not a blocker.

## Other checks and limits

* `check_csv.py` passed. Initial pull was current; unrelated untracked
  `reverse/zh_sweep/` was preserved.
* Reviewed `link_rank.py --top 30`, `--near 2`, `--near 3`, `--near 5`,
  `class_views.py --blockers`, and `repair_queue.py link --limit 12`.
  Existing handoffs already cover the high-ranked string, vector, module,
  FireLogicSystem and W3DGhostObject prerequisites. Existing source repairs
  must be paired with their current providers, rather than credited again
  against this older census.
* The current resolve-phase destructor plus
  StrategicInGameUIResolveBattlesBehavior.cpp preview still leaves the former
  at 0/482 bytes, needing Impl::rva0057556D and Impl::rva00576ACB. The latter
  already links 382 bytes. This agrees with the existing codex3 final handoff.
* `name_globals.py --dry-run` on Rva00066A9ABody and the two address-getter
  units kept zero edits. Shader/filter roots still need real data providers.
* PeerDefs' g_bfmeEmptyF9 lead remains coupled to the independently documented
  SavedIgnoreMap value-type/insert-chain mismatch. An empty-string declaration
  change alone would not link that unit; no trial repeated.
* `rehome_rows.py --limit 12` reads `build/link_census/census.log`, dated
  October 13 03:59, while the index measures October 23. Stopped this probe
  after four negative candidates; its limit counts successful rehomes, not
  candidates. Do not interpret this interrupted probe as queue exhaustion or
  use that mismatched log as current ranking evidence. No apply mode used.
* Reviewed BFME 1's current-pointer linking repairs and existing tracked
  inheritance audits; preserved the verified pointer and another seat's
  pointer claim. No census, link cycle, nightly or boot runner was started.

These are legacy scoped previews, not self-strict or closed-strict gains.
No byte gate was required for production changes because none were made.
The final progress report and runner metadata record zero local recovery.
