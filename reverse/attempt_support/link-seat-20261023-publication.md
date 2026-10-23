# Publication blocker after link repair, 2026-10-23

The retained wide-record list repair is +116 B in the legacy current-object
preview. Its ordinary and self-strict checks pass, with an EXACT native parent
EH graph. The alternative DieModule repair was removed in favor of upstream
4321ed9ff6. Three verified commits remain local until publication succeeds.

The second publication attempt, rebased on 7aae99cc67, passed 98,109/98,109
function rows across 23,425 sources, 31,535 literals, 2,257 empty references,
9,084 floats, 6,408 imports and 2,140 data rows. The no-op patch also passed.
Its only failing full-gate check was DIR32 consistency:

    ??_7FireWeaponWhenDeadBehavior@@6BUpdateModule@@@
    bases 0x00C496E8, 0x00C497B4

This is an existing upstream class-view discrepancy made visible by the rename
in 712d5ce6d6, not a BFME 1 update regression. The two source files are unchanged
from upstream, use only their local declarations, and contain no donor includes.
The rename's attempt-log entry already records the differing vtable views.

Read-only object inspection establishes:

* Rva00589079Derived.cpp: destructor 0x00482E96 +2 references this symbol
  with addend zero, retail value 0x00C497B4 (primary subobject).
* FireWeaponWhenDeadBehaviorCtor.cpp: constructor 0x00482D80 +0x45 references
  the same symbol with addend zero, retail value 0x00C496E8 (update interface).
  Its primary store at +0x37 instead uses the ObjectModule-qualified symbol.

Paired `link_check.py` reports derived unit 311 -> 311 B, constructor 0 -> 0 B,
with this COMDAT as the constructor's blocker. No corrective source trial was
made and no claim was taken: reconciliation requires the actual inheritance
and virtual-slot contract, not another symbol spelling or whitelist entry.

Next seat: resolve that concrete class-view prerequisite, retain the upstream
DieModule provider, and rerun the ordinary full gate before publishing the
verified list/reference/evidence commits. Do not rebuild the census or repeat
the banked MpCombo and Pod88 visibility trials without new evidence. No gate
was bypassed. Remaining claims were released at handoff.
