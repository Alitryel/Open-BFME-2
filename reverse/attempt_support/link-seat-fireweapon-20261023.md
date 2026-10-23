# FireWeapon link repair: base identity prerequisite

Seat codex6, gpt-6.1-sol, 2026-10-23. Inputs: BFME 2
`88983ceb42b0e29f233a0e1c6bd3cc75c2357212`, verified BFME 1 pointer
`138757e9b74645fbcbb7724a7af2764e34931e11`, published retail-truth-4
census `456ce161c5` (2026-10-23 06:28). No source, ledger, pin or verifier
change retained. This is a blocked experiment, not a linked-byte repair.

## Target and experiment

Claimed the two source files and retail RVAs 0x00482D80 (203 B constructor)
and 0x0078BBDF (10 B destructor helper), then released all four claims:

* `Code/GameEngine/Source/GameLogic/Object/Behavior/FireWeaponWhenDeadBehaviorCtor.cpp`
* `Code/GameEngine/Source/Common/Rva00589079Derived.cpp`

The constructor declares the actual ObjectModule / BehaviorModule /
UpdateModule multiple-inheritance hierarchy. The destructor unit instead
declares a 12-byte primary UpdateModule plus opaque secondary bases.
The latter unit also owns two other derived families, Rva00589079 and
Rva00481F82; a repair must preserve all three families.

Tested adding the missing native primary virtual slots (loadPostProcess,
s02, xfer and getModuleNameKey) to the constructor view and the missing
key slot to the destructor view. The slot-only trial preserved every row:

```
./build.sh <both sources>
Source claims: OK (2 sources, scoped byte-verified)
Functions: OK 10/10 matched across 2 source file(s)
String-ref verify: OK (0 literals + 0 empty-string refs verified)
Float-ref verify: OK (1 compiler literals verified)
Import-ref verify: OK (0 named imports verified)

python3 tools/link_check.py <both sources>
FireWeaponWhenDeadBehaviorCtor.cpp: does not link; LINKED 0 -> 0 bytes (own 203)
  comdat ??_7FireWeaponWhenDeadBehavior@@6BUpdateModule@@@
  differs from the first copy in link order (no retail address)
Rva00589079Derived.cpp: LINKS; LINKED 311 -> 311 bytes
Total LINKED 311 -> 311 bytes

python3 tools/link_check.py --prepare-current <both sources>
Functions: OK 10/10 matched across 2 source file(s)
2 explicit providers byte-verified with strict reusable receipts;
census/index/status unchanged, LINK closure not yet checked
```

These are legacy scoped link previews and strict self byte receipts. No
closed-strict gain was measured. Restored both sources after the zero-gain
trial; no nonmatching reconstruction is left in Code/.

## Exact remaining mismatch

COFF inspection establishes the cause beyond slot count. In the constructor
object, `??_7FireWeaponWhenDeadBehavior@@6BUpdateModule@@@` is the 4-byte
secondary update-interface table at object +0x10. In the destructor object,
the identical symbol names the 20-byte primary table. The constructor's
primary table instead has basename `6BObjectModule`.

Retail primary table RVA 0x008497B4 starts with VAs 0x00882EBD,
0x00882C39, 0x00882E4B, 0x00882BDB and 0x00882E51. The die-interface
table at RVA 0x00849698 starts with VA 0x00882C4A. These retail slots and
constructor offsets support the native hierarchy; matching table bytes
under the wrong base name cannot reconcile the two definitions.

Next useful work is a complete, evidence-backed UpdateModule MI
reconciliation in Rva00589079Derived.cpp, checking its other derived
families together. Another slot-only trial will not address the blocker.
No alias, address pin, suppression or new placeholder was introduced.

## Other session checks and handoff

`check_csv.py` passed (98,112 functions, 15,853 symbols, 2,140 data rows).
Reviewed `link_rank.py --top 30`, near/sole rankings, and
`class_views.py --blockers`; several ranked units already link with current
objects. Examples: narrow money-get, boxrobj, MP setup slots, HordeContain,
AptError and the owned deque. Apt builtins and script-function units also
link when their already-repaired current provider is included. These are
upstream repairs, with no gain credited to this seat.

`name_globals.py --dry-run` retained zero edits. A read-only
`rehome_rows.py --limit 20` probe was stopped at wind-down, before completion;
its Eva placement lead was not accepted or measured as a repair. The
remaining private-vtable, STL helper and compiler-summary blockers were
reviewed against existing handoffs rather than repeating unchanged trials.

Reviewed BFME 1 linking repair commits c20e733a and 54493f97; their inline
and declaration patterns are already inherited or require target-specific
class work. BFME 1 upstream was fetched to
`38cba658aa0945145c3c8afd422a921f44636c2b`; the clean committed pointer was
preserved because another seat owns the shared update lock. No successful
freshness stamp or pointer update is claimed here.

The runner signaled wind-down before another candidate was claimed. No
measured link or C++ byte gain; all trial edits restored and all claims
released. Resume from fresh rankings and current providers, preserving
the class-identity prerequisite above.
