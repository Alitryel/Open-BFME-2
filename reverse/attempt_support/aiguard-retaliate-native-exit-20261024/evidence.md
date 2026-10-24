# AIGuardRetaliate native exit: prepared same-RVA recovery

2026-10-24, Seat2. Verified and normally admitted; commit/publication pending.
No full-table or link-closure claim. Unique coverage gain: **0 bytes**.

## Inputs and scope

- Worktree: `/Users/mehmet/.t3/worktrees/Open-BFME-2/t3-7faf7255`.
- HEAD: `93dd8f341fdb4fc8d28ef8114e46558f10e5f8a7`.
- Clean donor checkout and HEAD gitlink: `138757e9b74645fbcbb7724a7af2764e34931e11`.
  This is this seat's measured PIN138 proof, not parent f514 verification.
- Consumer: `Code/GameEngine/Source/GameLogic/AI/AIGuardRetaliateStates.cpp`;
  HEAD blob `4fc2b0a6fa8c938da2f1b1c1fc97b0e8a6e46590`, trial blob
  `f8f283f2bf80b13eee3981ee0a7657e79386f022`.
- Unchanged physical owner: `Code/GameEngine/Source/GameLogic/AI/AIGuardStates.cpp`;
  HEAD/working blob `483424773ad8552e58ac84366c267f468b05b9ea`.
- Existing rows: consumer9/1529B + owner35/4402B = **44/5931B**.
  Admitted same-RVA76B row makes45 authored rows/6007B, not new coverage.
- Eleven claims held under `sol-team-supply-20261023`: consumer file plus
  `5452CB,54574D,54582A,5454D0,5453E2,54587A,797FE5,545A46,797FDB,542C87`.

## Identity: target, donor and inference

**Target:** named Retaliate AttackAggressor table VA `C69FA0` slot5 selects
`542C87/76B`, also selected by named AttackAggressor `C69890` and Inner
`C69780`. Native reads substate+3C, machine+18/owner+14; invokes substate
virtual exit(slot5) and deleting destructor(slot0, flags0), calls scalar delete,
clears substate, then clears the target through owner team pointer+304.
Established `Object::getTeam` at43A09D instead reads+1D0: it is NOT substituted.
Native Return table `C69F38` slot5 selects34BA5F, not this exit; no Return body
or override was invented.

**Donor:** pinned Zero Hour
`inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIGuardRetaliate.h`
declares the real derived `onExit(StateExitType)`; corresponding
`Source/GameLogic/AI/AIGuardRetaliate.cpp:823` supplies attack-state lifetime
then team target reset. Donor uses `deleteInstance()`/`getTeam()`; those exact
calls are not target facts.

**Adaptation/inference:** genuine typed derived override, target `::delete`,
and friend access to neutral `Team *m_team304`. Original +304 member name is
unknown. Padding preserves status+438 and other existing fields. Base typed
enum callback preserves slot5, thiscall ECX, 32-bit argument and ret4 ABI.
No Team provider body, synthetic getter, Return ctor/dtor/table/callback,
extra virtual slot or replacement allocation provider is emitted.

## Full76B and all relocations

Actual definition:
`?onExit@AIGuardRetaliateAttackAggressorState@@UAEXW4StateExitType@@@Z`.
Complete emitted section extent: **76B**. Resolved bytes equal all76 retail
bytes, with **zero masks and zero unresolved relocations**:

```text
568bf18b4e3c85c98b4618578b78147425ff74240c8b01ff50148b4e3c85c974088b016a00ff10eb0233c050e8a8d0aeff83663c00598b8f0403000085c95f5e74076a00e87aabe5ffc20400
```

SHA256 `f333ad37accb95e6e8bd179ded14b4d1bc4a56c0c735c53c5ebfee70ecb355fa`.
Exactly two COFF `IMAGE_REL_I386_REL32` records; both raw addends are zero:

| Operand offset | Actual symbol | Native target | Existing provider |
|---|---|---|---|
| +2D | `??3@YAXPAX@Z` | 2FD60 | `Code/Libraries/Source/WWVegas/WWLib/mem_ops.cpp` |
| +45 | `?setTeamTargetObject@Team@@QAEXPAVObject@@@Z` | 39D84A | `Code/GameEngine/Source/Common/RTS/TeamGetControllingPlayer.cpp` |

Provider identities are existing ledger/native evidence; neither provider was
edited or compiled in this trial.

## Observed normal gates

Authorized sole normal build, own env/grant, BUILD_POOL=1/BFME_OBJSTORE=off:

```sh
./build.sh Code/GameEngine/Source/GameLogic/AI/AIGuardRetaliateStates.cpp Code/GameEngine/Source/GameLogic/AI/AIGuardStates.cpp
```

Exit0: **44/44 exact**, references verified; 3 literals, 0 empty refs,
12 float literals, 0 named imports; no baselined/skipped string references.
Separate host-only existing-object full-row proof also passed all44 with zero
masks/unresolved; independently passed the new full76B and both native targets.

Normal noncompiling `tools/eh_verify.py` on these two sources reported
**7 parent rows EXACT; 0 nonexact, 0 baselined, 0 missing objects**:
Guard AttackAggressor543F58, Inner54379B, Outer5439F2;
Retaliate AttackAggressor54587A; GiantBird AttackAggressor36AA74,
Outer36A5BB; Rva0036A3E9GuardInner36A3E9.
Do not confuse seven raw EH results with the five explicitly inventoried
handler/unwind pairs `77E520/77E516,77E534/77E52A,797EC8/797EBE,
797EDC/797ED2,797FE5/797FDB`. All five placements passed; renumbered local
labels were resolved through the normal exact parent-EH proof. New exit has
no EH frame. Raw seven-result JSON remains preserved unchanged.

Fixed flags `-nologo -c -O2 -GR- -EHsc-`; consumer region/source
`-O1 -arch:SSE -G7 -DNDEBUG -MD`; unchanged owner additionally
`-EHsc -ICode/Libraries/Include/Lib`. NoFI/response/STLport/new flags.
Compiler SHA256 `2ecf86a3edfd3deae498e08298e210e984537ce9e11759930561e43f40bd2515`.
First headers resolve to own lookup view and Coord3DCtorView.h (consumer),
lookup view and Coord3D.h (owner); mapped toolchain/includes/env remain ownPIN138.

## Emitted audit and exact limits

Archived consumer/owner objects SHA256 respectively:
`78edfb5dc52c631ff45c0ab58cf0117845b4bc8fa5d99b1466b269a163d02ed0`,
`c49ae0bf5618ae5511affe46cde43c9d1d2a3db0e0bcbe30303dd3eaf85d885d`.
Their42/92 positive-section external definitions were fully inventoried.
All **10 shared definitions match bytes+relocations across the current pair**:
AttackExitConditionsInterface ctor/table; Object getAI/getBodyModule/
getPosition/testBfme438Bit0; AI getAiData; GameLogic getFrame;
State getMachine; StateMachine getOwner. This is NOT before/after equality.

Consumer table slot5 now has actual derived DIR32/addend0 to the emitted exit.
Other slots retain their existing weak deleting-dtor/placeholder contracts;
the audit does not resolve all native table identities or prove current link
closure. Ordinary compiler weak ??_E-to-??_G records are visible, not new source
aliases. Directives contain only MSVCRT/OLDNAMES default libraries.

No preserved pretrial COFF was found: cache and archived objects are this trial.
Therefore exhaustive binary before/after provider/reference-set equivalence is
unproven. Source diff adds only the intended authored exit; no unexpected new
provider was identified, but do not inflate that into baseline emission proof.

Actual consumer `/alternatename` count **1 -> 0**. Removed inherited int binding
was `?onExit@State@@UAEXH@Z` -> existing AttackAggressor enum exit. There is
**no exact-path hatch-baseline entry**: actual alias reduction is one, not a
registered allowance deletion. No pin/ledger/baseline change has been made.

## Normal ICF admission — executed after explicit parent grant

```sh
python3 tools/add_match.py \
  '?onExit@AIGuardRetaliateAttackAggressorState@@UAEXW4StateExitType@@@Z' \
  0x00542C87 76 \
  Code/GameEngine/Source/GameLogic/AI/AIGuardRetaliateStates.cpp \
  --icf-owner '?onExit@AIGuardAttackAggressorState@@UAEXW4StateExitType@@@Z' \
  --notes 'Native named Retaliate AttackAggressor table C69FA0 slot5 selects542C87. Genuine ZH typed derived exit adapted to target scalar-delete lifecycle and direct owner team field+304. Actual full76B and both relocations match existing physical owner. Original +304 field name unknown. Zero unique coverage; removes one source alternatename; no new pin or provider.'
```

Before admission the physical owner had exactly one matched76B row at542C87;
the proposed real name had no row. The exact command above returned0, normal
consumer gate10/10, and normal re_log landing/claim bookkeeping succeeded.
No gen-alias token, object-symbol, new pin, manual ledger or masked callee.

Post-admission normal two-TU build: **45/45 exact**, all refs,3 literals,
12 floats,0 imports. Host-only full45-row proof: zero masks/unresolved;
actual new76B extent and both real REL32 destinations independently rechecked.
Normal EH verification remains **7 EXACT,0 nonexact/baselined/missing**.
check_csv, whole-two-TU frozen-definition and class gates each returned0.

Explicit `tools/link_check.py --prepare-current` for only these two sources
returned0: **2 explicit providers byte-verified with strict reusable receipts**,
normal45/45 reuses both objects, census/index/status unchanged. This is strict
input currency, NOT a census/preview-universe or LINK closure assertion.
Staged normal derivation passed: name_dependents reports zero sources and
delta_sources names only AIGuardRetaliateStates.cpp. Explicit staged paths are
that consumer, functions.csv, re_attempts.log and this evidence only. No lost
name, new source/provider/header or compiler-input expansion is requested.
Hooks/commit/link preview/publication remain pending at evidence preparation.

Raw own-seat objects/receipts, full stdout/stderr/exits,76B proof, mappings,
seven-EH JSON and external/table inventory are retained ignored under
`build/orbstack/aiguard-preflight-20261024/main-trial*`.
