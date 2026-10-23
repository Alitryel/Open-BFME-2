# queueSupplyTruck (0x4F37B0, 1537 B), third session of 2026-10-23

The bank is unchanged: `reverse/attempts/0x004f37b0.cpp`, official score 0.7867.
The clean base (bank plus the real `KINDOFMASK_NONE` global,
`../queue-supply-truck-20261022/`) compiles to 1537 B with r=19 m=70 g=22.
The feature legend (retail `GHZT-`, base `----L`) and the allocation table are
in `../queue-supply-truck-20261023b/readme.md`. This session ended on the runner's
wind-down signal before the gen11 factorial below was compiled.
Model: claude-opus-5-5.

## New findings (target evidence)

- **Causal chain T, then Z, then H.**
  - **Base:** the zero constant is CSE'd into one web that includes the
    `supplySource` null compare (`cmp [ebp-0x1c],esi`). That stretches the web
    across calls, so it takes callee-saved esi. The 0xBC26E0 vft web loses esi
    and is rematerialised locally (`mov eax,0` / per-store immediates).
  - **Retail:** tests the call result directly (`test eax,eax`), so the zero web
    ends before the call at +0x198. The zero lives in ecx (the byte store uses
    cl), and esi is free for the hoisted `mov esi,0xbc26e0` at +0xf0.
  - **Target:** a source shape whose null test is not the shared zero literal.
- **Retail shares zero across blocks more aggressively than base.**
  - It uses `xor edx,edx` for `curGatherers = 0` and reuses edx for the hoisted
    adjustor store `mov [ebp-0x40],edx` in the recount iterator-loop preheader.
    The back edge goes to +0x29f, so the stores at +0x294..0x29c are loop
    invariant.
  - Base emits `and [ebp-0x20],0` and a fresh `xor ecx,ecx`.
- **The info reload `mov eax,[ebp-0x18]` at +0x10a has no jump target.**
  - Every branch target was checked: the latch +0x5c8 has 8 jumps, plus +0x229,
    +0x26e and others. None lands at +0x10a.
  - So the reload marks an IR block boundary, or a cache kill, that survived into
    register allocation but not into the final layout. A then-arm-top boundary
    (scope, label, or a call that kills the `[ebp-0x18]` cache) is the matching
    lever.
- **Loose loop:**
  - Retail keeps obj in edi, defined at the latch
    (`mov edi,[ebp-0xac]; test edi,edi; jne +0x3b3`), so the source's
    `if (!obj) continue;` test is merged away.
  - Base homes obj at [ebp-0x20] and keeps the redundant
    `test eax,eax; mov [ebp-0x20],eax; je` at +0x3aa.
  - Loop 1 and the recount loop merge the test in both builds.
- **getAI register form:** `mov ecx,[obj+0x258]; test ecx,ecx; mov eax,[ecx];
  call [eax+0x17c]` appears only when obj is in a callee-saved register.
- **aiDock identity:** the real name is
  `?aiDock@AICommandInterface@@QAEXPAVObject@@W4CommandSourceType@@@Z` at
  0x26C3AC (base calls it through the shim `rva0026C3AC`). BFME 1's own version
  (`reference/open-bfme-1/game/GameEngine/Source/GameLogic/AI/AIPlayer.cpp:239`,
  candidate 0x165D50) is present-unmatched there and gives no shape lead.

## WorldBuilder twin (target evidence, unoptimised build)

- **Location:** RVA 0xCF6160 (VA 0x10F6160), 3853 B, frame 0x4F8.
  `python3 wbdis.py.txt 0xcf6160 3853` (it takes an RVA, not a VA).
- **EH state 0 is set right after the centre copy** and holds through the whole
  then-arm:
  - the filter temporaries are states 1-3;
  - each `continue` sets -1;
  - the static guard is 4;
  - the inline aiDock `AICommandParms` is 5;
  - new-expressions are 6 and 7.
  Retail's FuncInfo has five states and no surviving centre cleanup; an empty
  destructor could have been optimized out. **Correction (2026-10-23):** WB
  state 0 cleans the center at `[ebp-0x80]` through an empty destructor; the
  parms object is state 5 at `[ebp-0x364]`. See the
  [direct unwind-table evidence](../queue-supply-truck-20261023-resumed/wb-eh-correction.md).
- **WB frame slots by scope:**
  - function scope: -0x10 loop-1 it, -0x14 totalHarvesters, -0x15 truckInQueue,
    -0x20 iter;
  - build-list loop: -0x68 info, -0x6c cur, -0x70 desired;
  - then-arm: -0x74 supplyCenter, -0x80 center, -0x84 recount it, -0x88 radius,
    -0x8c curGatherers, -0x90 supplySource, -0x94 warehouse, -0x98 availableCash;
  - else-arm: canBuildUnits -0xd9, it -0xe0, tTemplate -0xe4, ...,
    isSupplyTruck -0x125, factory -0x12c.

  The order within a scope does not follow declaration order, so do not derive
  declaration order from it.

## Tried this session (no change from the bank)

- gen7 and gen8 families: inert.
- gen9, a 1024-variant declaration factorial (`../queue-supply-truck-20261023b`
  factors A-K). Only two factors change bytes, and both are worse:
  - B (isSupplyBuilding as an if-wrapper): 1551 B, r=23 m=88 g=21. It gives G
    without H.
  - H (radius before center): r=21 m=76 g=22.
  Everything else is canonicalised by c2.
- gen10 (prototype-local spellings): identical to base.
- The rescore of q6a/b_0001: 1534 B, r=22 m=78 g=27, worse.
- The permuter is exhausted on this residue.

## Disproved (cumulative; do not repeat)

Everything listed in `../queue-supply-truck-20261023b/readme.md`, plus gen7-gen10
above. Declaration order and scope alone do not move this body. Only edits that
change the IR do: block boundaries, tests, temporaries, expression forms.

## Next: gen11, IR-changing factorial (not yet compiled)

Factors against the clean base, one letter each:

- **a** Drop `if (!obj) continue;` in the loose loop only. This is safe: the
  DLINK loop condition `!done()` already guarantees `obj != 0`.
- **b** Drop it in loop 1, or in the recount loop (two letters).
- **c** Cache `AIUpdateInterface *ai = obj->getAI(); if (!ai) continue;` before
  `getSupplyTruckAIInterface()`, with aiDock still through `obj->getAI()`.
- **d** `if (!sta) continue;` instead of `if (sta) { ... }`.
- **e** `3*desiredGatherers`, or the reversed comparison.
- **i** The supplySource null test spelled so that it does not join the zero
  web: an assignment inside the condition, `== NULL` on the call, a Bool temp.
- **j** `curGatherers = 0` shapes that let zero share a register with the
  adjustor store.
- **k** Arm inversion: `if (cur < desired) { loose } else { recount }`.
- **f** A then-arm-top block boundary (nested scope, label, or a call that kills
  the info cache) for the +0x10a reload.

## Tools

- `bh.py.txt OBJ...`: groups objects by the md5 of the function bytes. The base
  hash is `9c6e9635 1537`.
- `wbdis.py.txt RVA SIZE`: disassembles the WorldBuilder twin.
- Compile with the probe harness from earlier handoffs (`build/qAj/probe.py`,
  `xargs -P 30`). Score with
  `BFME_OBJSTORE=off tools/align_diff.py` (r/m/g counts).
