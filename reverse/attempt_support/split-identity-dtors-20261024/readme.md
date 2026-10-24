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
