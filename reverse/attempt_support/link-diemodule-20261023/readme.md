# DieModule deleting-destructor provider repair

Target revision before this repair: 90d5d2a583. Published census: 0fa62a2841,
2026-10-22 23:07, retail-truth-4. Reviewed BFME1 donor f36a4db066aa61edeee90085a31d628eb829001d;
upstream 54493f975 was inspected without changing the verified submodule pointer.
Its string COMDAT sweep reports no link gain and is not the basis of this repair.

## Evidence and scope

The indexed first DieModule deleting-wrapper copy is in CreateObjectDie.cpp;
SpecialPowerCompletionDie.cpp and InstantDeathBehavior.cpp also emitted wrong
copies. The protected wrapper row at RVA 0x0045CEF4 (28 B) was verified in
FamilyDeletingDtors_0021C7e.cpp, whose incomplete class emitted a competing table.
Retail's whole wrapper calls the rowed complete destructor at 0x0045CE54 and
conditionally calls global operator delete. ZH's abstract-pool macro supplies an
empty ordinary delete, and its inline destructor supplies a second destructor.
These are target-proven call relationships; the full class/interface layout and
other helpers remain donor-derived, with no new target naming claim.

A scoped copy of the donor DieModule header preserves its class, interfaces,
constructor and pool operations, except that the complete destructor is declared
out of line and ordinary delete calls global operator delete. The expanded pool
macro retains its other operations and access. Only the three competing provider
units opt into this header. All their matched caller and constructor bytes stay
exact. Their resulting whole deleting-wrapper bytes and relocations also match,
so its row is moved to CreateObjectDie.cpp and the synthetic provider is removed.

A preceding novtable declaration trial was rejected: it removed the DieModule
constructor stores of the primary and secondary vtable addresses. That trial
was reverted; novtable is not appropriate to this retail constructor.

## Acceptance

The recorded paired legacy link_check previews use the same four original
providers and census index. Before: 0/4 and 0 B linked. After the three header
adoptions: 3/4 and 246 B linked; only the synthetic table still lost. After
rehoming its 28 B row and removing the synthetic unit: 3/3 and 274 B linked.
All nine matched rows pass ordinary byte/reference verification, including the
rehomed wrapper's full body and relocations. Explicit providers are additionally
prepared with strict reusable compile receipts. The link preview remains a
legacy census-overlay result: no closed-strict gain or fresh census is claimed.
No full link cycle, nightly or boot runner was started.

Commands:

```
python3 tools/link_check.py <CreateObjectDie.cpp> <SpecialPowerCompletionDie.cpp> <InstantDeathBehavior.cpp> <FamilyDeletingDtors_0021C7e.cpp>
./build.sh <each touched source>
python3 tools/add_match.py '??_GDieModule@@MAEPAXI@Z' 0x0045CEF4 28 Code/GameEngine/Source/GameLogic/Object/Die/CreateObjectDie.cpp --replace-existing
python3 tools/link_check.py --prepare-current <the three remaining providers>
python3 tools/link_check.py <the three remaining providers>
```

The raw paired previews are kept alongside this note. Source changes retain the
existing compiler settings and the new include directory precedes donor headers.
