# queueSupplyTruck (0x4F37B0, 1537 B) — session 2026-10-23

Bank unchanged: `reverse/attempts/0x004f37b0.cpp` (0.7867). The clean base
(the bank with the real `KINDOFMASK_NONE` global, see 20261022) compiles to
1537 B, r=19 m=70 g=22. The residue is the same as in `../queue-supply-truck-20261022b/`.
The session ended early on the runner's wind-down signal.

Feature legend:
- `g`: whether the build-list loop is guarded and hoists the vft.
- `hv`: the register that holds the hoisted vftable 0xBC26E0.
- `it`/`cur`: the registers of the totalHarvesters iterator and of the team cursor.

Retail is `g=1 hv=esi it=esi cur=edi`; base is `g=0 hv=- it=edi cur=esi`.

## Finding: an empty block before the latch flips the allocation

Removal scan: delete one source line at a time from the base and read the features.

- **Without `m_player->setCanBuildUnits(canBuildUnits);`** (the restore after the
  tTemplate loop): 1534 B, `g=1 hv=esi it=esi cur=edi`. This is retail's whole
  register picture, identical to `build/q6a/b_0001` (canBuildUnits removed).
- **Without `info->setCurrentGatherers(curGatherers);`** (the last statement of the
  supplyCenter branch): 1535 B, `g=1` with no hoist.
- **Every other single-line removal stays `g=0`.**

Retail has both statements, so the cause is the block shape, not the variable.
When the restore is replaced by any other statement, the result stays `g=0`:
- `setCanBuildUnits(true)`
- `m_teamDelay = canBuildUnits`
- an info store
- a global store
- a doubled restore
- a bare `m_player` load

None of these is a natural source. What matters is whether a non-empty
block sits between the tTemplate loop exit and the build-list latch.

Explicit `continue;` edges (after setCurrentGatherers, after the restore, or
`if (!supplyCenter) continue;`) give `g=1` but grow the body to 1562 B with extra
jumps. That is also no source.

## Disproved this session (do not repeat)

- **canBuildUnits:** respellings v1-v11; a const `Bool&` setter or getter; `*&`;
  volatile.
- **Restore position:** the restore replacements above (x1, z1-z5).
- **tTemplate loop:** wrapping it in an `if`, or writing it as a `for` loop, gives identical bytes.
  Swapping the branches changes the layout.
- **Inert locals:** a positional inert-local k-scan, 113 positions, all inert.
- **Flags:** `/Zi`, `/Z7`, `/Zd`, and a `/Zi` with pdb variant, all inert.
- **Natural singles** (build/q6g), 13 of them, identical or worse:
  - truck/harvester initialisers;
  - `for(WorkOrder *order...)`;
  - `!isSupplyBuilding()`;
  - `supplySource == NULL`;
  - inline radius;
  - inline cash;
  - curGatherers first;
  - const cbu;
  - dock inline (two forms);
  - harvester if;
  - a second center temporary.
- **Retail keeps isSupplyTruck as a local** (stored to [ebp-0x25]). Inlining it
  drops the store (1533 B).

## Next leads

1. **Home TU (untested).** By the ledger, retail order is selectTeamToBuild
   0x4F35A5 (523 B, ends at 0x4F37B0), then queueSupplyTruck, then
   selectTeamToReinforce 0x4F3DB1. Both neighbours live in
   `Code/GameEngine/Source/GameLogic/AI/AIPlayerTeamBuild.cpp`. Compile the full
   body in a scratch copy of that file, in retail order, with its class views
   (recipe 0x6E5050 / same-unit context). Check
   `tools/find_declared_unmatched.py` and `tools/repair_queue.py dest 0x4F37B0` first.
2. **Why the empty pre-latch block flips the allocation.** Look for a source shape
   that ends the iteration with a block c2 treats as empty while keeping both
   statements:
   - the restore inside a scope whose destructor is trivial;
   - the restore hoisted into the tTemplate loop's exit test;
   - the build list walked as `while` with the advance at the top.
3. **Not yet tried:**
   - iterate_TeamInstanceList through a named temporary;
   - explicit inline virtual destructors on the filters;
   - ObjectID as an enum;
   - the WorldBuilder getAI double-temporary pattern.

Scratch generators for this session (untracked, `build/`): q6c (respellings),
q6d (removal scan, `res.txt`; replacement and CFG variants), q6e (k-scan),
q6f (flags), q6g (singles), q6h (continue edges).
