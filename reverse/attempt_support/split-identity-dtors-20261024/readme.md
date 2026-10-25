# Split-identity destructors hold out link units (2026-10-24)

Model claude-opus-5-5, BFME2 master 605cde0e4a, census index 2026-10-24 09:13
(903a1d4281) refreshed with `link_check.py --refresh` over all 687 units the
census lists as not linking (164 already link on current master).

## Finding

Many units fail the link only (or mainly) on an unresolved virtual destructor
`??1X@@UAE@XZ` of a class `X` whose constructor is matched under `X`, while
retail's destructor body is **already matched** under a second, address-derived
class name. Retail proves the pairing mechanically: the constructor installs
vtable VT, VT slot 0 is the scalar deleting destructor W, and W calls the
destructor D. One class, two ledger names; the link never sees `??1X`.

`scan.txt` is the output of `split_ident.py.txt` (copy to `build/`, run from the
repo root with a `link_check --refresh` log as argument). It follows each
unresolved `??1X@@UAE@XZ` to its retail destructor row. The heuristic takes the
constructor's **last** vtable store; rows whose "dtor" is an ICF stub or an
unrelated name (`Format@StringClass`, `__EH_prolog`, `getDrawable@Thing`, ...) are
false matches and should be ignored.

Clear cases (constructor class -> destructor row, units held out):

| Class | Destructor row (placeholder) | VT | Units |
|---|---|---|---|
| GameLogic | ??1Rva00243BA0 (0x243BA0, ??_G 0x246213) | 0xBEE130 | GameLogicInit.cpp 28,041 B, sole blocker |
| DozerPrimaryStateMachine | ??1Rva0048898C | | DozerAIUpdateCtor.cpp 7,916 B (3 blockers) |
| WorkerStateMachine | ??1Rva004A9964 | | WorkerAIUpdateCtor.cpp 4,697 B (2 blockers) |
| BaseHeightMapRenderObjClass | ??_GRva006D0D7 | | BaseHeightMapConstructor.cpp 1,166 B, Rva000E3BFEConstructor.cpp |
| ExperienceTracker | ??1Rva0039AD56 | 0xC1AD20 | ExperienceTrackerXfer_ExperienceTracker.cpp 208 B, ExperienceTrackerAutoResolve.cpp 113 B |
| GameSpyInfo | ??1Rva00386374 | 0xC19500 | GameSpyInfoCtor.cpp 280 B, sole |
| GlobalWeatherSystem | ??_GRva00318637 | | GlobalWeatherSystemCtorDeferred.cpp 133 B |
| Rva0022BD9ASubsystem | ??1Rva0041F042 | 0xC3AF78 | 67 B, sole |
| Rva0022C0CDSubsystem | ??1Rva002E0427 | 0xBE7628 | 81 B, sole |
| Rva0022BE0FSubsystem | ??1Rva003ED1FC | 0xC36100 | 65 B, sole |
| Rva0022BD25Subsystem | ??1Rva0041F94A | 0xC3B8C8 | 55 B, sole |
| Rva0022A809Subsystem | ??1Rva00415CAB | | Rva00415704Ctor.cpp 59 B |

## Why it was not fixed here

- `tools/rename.py class` refuses both directions: a placeholder-to-placeholder
  merge ("new name is itself a placeholder") and a placeholder-to-real merge
  where the real class already exists ("collides").
- `docs/naming.md` lists vtable-slot evidence as a hint, not a canonical basis,
  so a hand rename to `GameLogic`, `GameSpyInfo`, ... is not admitted either,
  although here the evidence is the compiler-generated ctor -> VT -> slot 0
  deleting dtor -> dtor chain, not slot position.
- After a merge, every unit emitting the class's vtable must share one view.
  For GameLogic that is blocked on SubsystemInterface: GameLogicInit.cpp uses a
  private 14-slot SubsystemInterface, the destructor unit the canonical
  dtor-only header (class_gate forbids a second private copy). See the
  0x00243BA0 entry in re_attempts.log.

## Suggested next step

A maintainer decision (or a `rename.py` "identity merge" mode) for unifying a
placeholder class into the class its retail constructor/vtable proves, with
tombstones for the placeholder rows. That would turn this list into mostly
mechanical link repairs; GameLogic additionally needs the canonical
SubsystemInterface to carry retail's 13 virtual slots.

## 2026-10-25 addendum: alias trial links 661 bytes, but the hatch policy blocks it

Inspected BFME 2 `4e835ab16a6`, census index 2026-10-24 10:28 at `2fbdec0868`,
`reference/open-bfme-1` `0bf534ea7c` (the pinned revision). Current-input
`link_check.py` reproduces the six single-destructor units and their sizes:

| Unit | Bytes | Sole unresolved name |
|---|---|---|
| GameSpyInfoCtor.cpp | 280 | `??1GameSpyInfo@@UAE@XZ` |
| ExperienceTrackerAutoResolve.cpp | 113 | `??1ExperienceTracker`, `??1ExperienceTrackerAutoResolve` |
| Rva0022BD9ASubsystem.cpp | 67 | `??1Rva0022BD9ASubsystem@@UAE@XZ` |
| Rva0022C0CDSubsystemCtor.cpp | 81 | `??1Rva0022C0CDSubsystem@@UAE@XZ` |
| Rva0022BE0FSubsystemCtor.cpp | 65 | `??1Rva0022BE0FSubsystem@@UAE@XZ` |
| Rva0022BD25SubsystemCtor.cpp | 55 | `??1Rva0022BD25Subsystem@@UAE@XZ` |

Trial (not landed): binding each spelling to the already-matched body with a
full-form `/alternatename` directive made all six units link, `LINKED 0 -> 661`
bytes, with every row still byte-verified (`./build.sh`: 28/28 rows matched).
Two of the pairs are independently anchored by layout as well as the vtable:
`0x0041EFFF` + 67 is exactly `0x0041F042`, and `0x0041F913` + 55 is exactly
`0x0041F94A`. The experience-tracker pair is `??1ExperienceTracker` ->
`0x0039AD56` and `??1ExperienceTrackerAutoResolve` -> `0x005DB100`; the other
two are `0x002E0427` (vtable `0xBE7628`) and `0x003ED1FC` (vtable `0xC36100`).

The trial was reverted, not landed. The current repository rules forbid adding
`/alternatename` by hand: hatch counts may rise only through the admitted tools,
and `hatch_counters.py --allow/--admit` run by the worker is itself hand-adding.
No admission tool covers this hatch, so the alias route is unavailable as
things stand. The change would also have been seven new hatches with no debts
retired.

Remaining admissible routes, in preference order:

1. Identity merge: rename the placeholder destructor class into the class the
   constructor and vtable prove, with one shared class view. That is what the
   original handoff asked for; it needs `rename.py` support for a
   placeholder-to-real merge, and every unit emitting the class vtable must
   agree on its slots (the GameLogic/SubsystemInterface and
   ExperienceTrackerXfer vtable-COMDAT cases above).
2. A maintainer decision to admit a scoped alias tool for proved split
   identities, with the vtable chain recorded as the reason.

Do not repeat the alias trial unchanged; the blocker is policy, not evidence.
