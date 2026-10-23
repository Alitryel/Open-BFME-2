# 0x002F83F5 — Pathfinder::rva002F83F5 link repair in the caller TU

Status: **blocked** (link repair, not a byte-recovery row).
Worktree: `7f76df1ff53` + the patch `002F83F5_sideways_link.patch` (this directory).
Model: deepseek-v4.1-flash-free. Time on target: ~240 min.

## Goal

`Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderSidewaysAttack.cpp` holds the
retail row `Pathfinder::FindAttackPathSideways` (0x002FC9B1, 1,566 B) and three
callee rows (0x002EBC7F, 0x002E6FDF, 0x002E6DC4/0x002E6BA1). It must also keep the
`Pathfinder::rva002F83F5` body visible for the caller's codegen, so the object
emits a duplicate COMDAT of that body (1,803 B) whose bytes are not retail's.
The retail body is rowed in `PathfinderRva002F83F5Neighbors.cpp` (0x002F83F5,
1,803 B, 45 relocations). The repair under test was to make the duplicate COMDAT
either byte-retail or absent.

## Findings

* With the canonical helper environment ported into the caller TU (see the patch),
  the duplicate body compiles to **exactly 1,803 B / 45 relocations**, frame
  `0x98`, prologue identical. The previous `__ftol2` relocation is gone: the unit
  had a stand-in `realToIntFloor` (`floor` + `(Int)` cast) that `nativeBurning`
  inherited; the canonical x87 `fld`/`fistp` form (`realToIntFloorNative`) fixed
  the size and reloc set.
* **1,556 bytes still differ; first diff at 0x54.** The first real difference is a
  3-byte store `89 55 e4` (`end.x` -> `[ebp-0x1C]`) that the unit emits once per
  `m_1C1CC.empty()` path at 0x8d/0x9e; the canonical body sinks/merges the store.
  The branch displacement at 0x54 is +3 as a result, and that shift propagates
  through the rest of the body (hence the large raw diff count even though the
  structure is close).
* `/Ow` is not the first-order cause. Removing it from this TU gives 1,803 B/45
  with 1,542 differing bytes and the same 0x54/0x8b pattern, and it breaks the
  caller row. Keeping `/Ow` is required.
* `#pragma optimize("w", off)` around the body is accepted but yields 1,777 B and
  a worse diff; `w` is not the `/Ow` switch. Do not use it.
* The `Rva002EAB6F` class was `char fields[0x34]` here; replacing it with the
  canonical explicit fields (same 0x34 size, 4-byte alignment) did not change the
  body bytes, but the explicit class is kept in the patch because it matches the
  canonical view.
* Layout/class comparison: `Pathfinder` and `PathfindCell` layouts agree up to
  the fields the body uses (`m_1C1CC` at +0x1C1CC); the unit's `Pathfinder` only
  adds trailing `m_searchWord,m_destMineshaft` and extra methods. `Object`,
  `AIUpdateInterface` and `PathfindZoneManager` differ only by methods.
  `PathfindCell::getType` is `__declspec(dllimport)` inline here vs plain inline
  in the canonical unit, but the body's two `getType()` calls still inline and add
  no relocation. `Rva002E8BCFSrc`, `Rva002F5925Info`, `Rva002E8BCF`,
  `Rva002E6C79`, `Rva002F35AFHop`, `Rva002E6DC4`, `Rva002E6FDF` all match.
* **Removing the body definition is not viable.** With the body replaced by its
  declaration only (an `aabtreecull`-style anchor attempt), the caller row fails
  (`FindAttackPathSideways` frame `0xa0` vs the target `0x98`, plus many bytes).
  The caller's codegen genuinely depends on the body source being present in this
  TU.
* `link_check --refresh` with the body present (build 5/5) reports
  `comdat ?rva002F83F5... (retail: not retail's body)` and `LINKED 0 -> 0`.
  The canonical unit's retail body exists, but the caller TU's non-retail COMDAT
  is still the blocker under the current link rules.

## Remaining mismatch / prerequisite

The same source compiled standalone in this TU (with the caller's class views and
`/Ow`) does not reproduce the canonical standalone body's store sinking, while the
caller's row requires both the body source and `/Ow`. The concrete prerequisite is
a way to keep the body source visible to the caller without emitting this TU's
standalone COMDAT, or a per-function `/Ow`-off context that does not disturb the
caller (a separate TU with the canonical context, or a compiler/link mechanism).
Do not retry the removed-body anchor or the `#pragma optimize("w")` variants.

## Best candidate / reproduction

* Patch: `002F83F5_sideways_link.patch` (apply to `7f76df1ff53`; the working file is
  currently restored to HEAD after saving it).
* Build: `bash build.sh Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderSidewaysAttack.cpp`
  (5/5, `Data rows: OK`).
* Body comparison: `python build/scratch/body_diff.py` (unit 1,803/45 vs canon
  1,803/45, 1,556 differing, first at 0x54); `body_hex.py` for the 0x40..0x104
  bytes.
* Link: `python tools/link_check.py --refresh Code/GameEngine/Source/GameLogic/Pathfinder/PathfinderSidewaysAttack.cpp`.
* Diagnostics used: `body_diff.py`, `body_hex.py`, `reloc_diff.py`,
  `compile_err.py`, `class_diff.py`/`class_diff2.py`/`class_diff3.py`,
  `ow_off.py`/`ow_on.py`, `rm_pragma.py`/`pragma_path_body.py`,
  `rm_path_body.py`/`restore_path_body.py` (untracked, under `build/scratch/`).

## Evidence separation

Target facts: retail row boundaries/sizes, the 45 relocations, the 0x98 frame,
the caller row's 5/5 and its `/Ow` requirement, and the link_check result.
Donor facts: the canonical body/helper source and the class views carried from
`PathfinderRva002F83F5Neighbors.cpp`. Inference: the `end.x` store-sinking is a
TU-context/optimizer difference, not a proven source-semantic difference.
