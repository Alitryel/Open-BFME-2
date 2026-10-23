IngameNoticeDisplay link repair, 2026-10-22
==========================================

Base HEAD 71e7f85a0c; census 08160bc2c9, 2026-10-22 17:08.
Current paired baseline: IngameNoticeDisplay.cpp 0/169 B and the split
FamilyDeletingDtors_Rva004E61C8.cpp 0/28 B linked. The current destructor
unit emitted a 31-byte frame-pointer deleting wrapper, selected ahead of
the retail 28-byte wrapper. The split emitter also emitted a different
one-slot class vtable.

Removing /Oy- preserves every existing EH parent/handler/funclet byte and
emits the retail 28-byte wrapper directly from the real class. Rehome its
row with add_match and remove the obsolete split emitter, following the
rehome_rows lane. No new name, pin, alias, private class or body is added.
The init/dtor class view itself is unchanged; this is not full class or
vtable reconciliation.

Acceptance: normal byte gate 7/7, literal/import/float checks pass;
find_declared_unmatched accepts the source; --prepare-current gives strict
reusable receipts (self-strict). Legacy link_check on the surviving unit
reports 197 B linked, against paired baseline 0 B: +197 B. The removed
emitter contributes no object in a new link. No closed-strict or full link
cycle measurement was performed.
