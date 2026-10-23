# Vector range-destroy ownership, 2026-10-18

Base 5d0705ab72; census c2c5ac8c27, 2026-10-18 11:36.

The vector overflow/clear family for the opaque 48-byte element calls the
24-byte _Destroy wrapper at 0x00414508. Its byte-verified owner is
StlportDestroyRva00414508.cpp. Declare that specialization in the overflow
unit instead of emitting the different STLport default implementation.
The native target relationship was already recorded in the clear row's
call-site evidence; no new identity, pin or layout claim is made.

Removing the default wrapper's instantiation also drops the existing
25-byte __destroy_aux loop at 0x001DEEE0 and 28-byte scalar deleting
destructor at 0x001DE6C5. Explicitly instantiate the loop, retaining both
whole rowed bodies. First byte gate failed only on those missing emissions;
the completed change passes all six unit rows.

Acceptance: identical two-provider local LEGACY previews 0 -> 365 bytes
(341-byte overflow unit plus 24-byte wrapper owner). Strict reusable byte
receipts pass 7/7 rows; EH verification finds zero graphs and zero missing
objects; reference checks, new-variants and declared-definition checks pass.
No self-strict LINK, closed-strict or full-link gain is claimed. No full
runner, reference update, gate change or coverage row was needed.

Sweep: the 55-byte push-back sibling already declares the range wrapper,
but emits a divergent overflow copy. Both declaration-specialization and
extern-template suppression change its body to at least 58 bytes (the
overflow REL32 displacement moves to offset 54). Neither attempt passes
the byte gate. Restore its original source and verify it; record the
blocker and release its claims. Its bytes are excluded from this gain.
The much larger vector-dtor-family unit has 37 indexed blockers and needs
a separate provider reconciliation, rather than another local attempt.

BFME1 donor survey/freshness blocker remains documented in
../peek-shader-link-20261018/readme.md; no reference inputs changed.
