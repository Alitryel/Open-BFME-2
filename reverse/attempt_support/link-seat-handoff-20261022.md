Link repair seat handoff, 2026-10-22
==================================

Starting tree: 73df4683fb; published index: e20daa4e78, 2026-10-21 21:42.
BFME1 inputs reviewed at 37c3022de1ab944c7ffe536440d637dc8199091c;
freshness evidence remains 20261021-bfme1-freshness-link-review.md.

Verified repair commit 3c80faa5cd adds 2,088 nonpadding linked bytes in two
units, with nine byte-exact rows and self-strict reusable receipts. These
are legacy-preview gains; no closed-strict measurement was performed.
See tree-cleanup-link-20261022.md for paired measurements and acceptance.

Rejected AptRefArrayResize.cpp trial
----------------------------------

The four-source preview included AptHandleVectorDelete.cpp,
AptRefArrayResize.cpp, Rva004A9DF3ElementDtor.cpp and BfmeRefVGOCopyDtor.cpp.
Current providers already unblock the 112-byte HandleVectorDelete unit;
that inherited improvement is not credited to this session. Resize remains
at zero linked bytes (397 nonpadding bytes held out).

An inline element destructor using the existing DecRef/bfmeDropVGO calls,
plus the existing sized freeBlock scalar-delete form, preserves all four
Resize rows. Its synthetic vector-deleting destructor is nevertheless 125
bytes against retail's 112: the array arm inlines the header/freeBlock
cleanup instead of calling 0x006CD460, and the scalar drop uses different
registers. The folded array-delete pin at 0x006E31F0 must retain its entire
27-byte body. The earlier forced-outline Resize trial (388 -> 378 bytes)
remains refuted. Original source restored; all four rows reverified. The
blocked log entry records the result; file and RVA claims were released.

Queue review
------------

Used link_rank top 100 / near-two, class_views --blockers, and explicit
current-object probes of 96 near-link units plus 60 additional candidates.
Nineteen units in the first probe and six in the second already link with
current sources/providers. These are inherited improvements, not repairs
made here. Additional current probes confirm Object_Object_topple.cpp
(133 B), BfmeConv1456.cpp (153 B), SiegeEngineContainCtor.cpp (193 B), and
Rva007B4874Registrations.cpp (388 B) already link. No edits were retained.

Large shared lanes have live claims, or need the recorded provider/class
prerequisites. In particular:

* AssetManagerImplUpdate.cpp is claimed by another worker; its member-template
  specialization ICE is already documented.
* The Apt counted-key and allocator-guard provider repairs are already landed
  (log entries 81397 and 81399); do not repeat the old import-inline attempts.
* Pointer-vector consumers still fail with the current explicit
  stlport_vector_voidptr_alloc.cpp provider. That provider's vector/base
  destructor COMDAT verdicts are unknown, while the optimized consumer
  copies differ. Merely including the provider does not clear these blockers.
  Existing Rva000E0AE2 and BfmeObject476Copy trials document the inline/EH
  constraints; no further source variation was attempted here.
* VictoryConditions still needs its virtual contract and row names reconciled;
  current Rva004201FADtor.cpp additionally lacks reset@VictoryConditions.
  The preceding 81389 handoff remains applicable.
* Callback views around Rva00574EE9 / Rva005CE259 have incomplete tables;
  their real three-entry native tables cannot be replaced by the current
  one/two-slot private views.
* Remaining sole missing providers include AIPlayer::queueSupplyTruck,
  LANAPI::handleRequestJoin, W3DModelDraw::rva000BD6C2, CollisionManagerImpl::
  rva007586F0, and EA allocator rva00032B00. Prior banks/blockers remain open.

name_globals.py --dry-run reports zero files/edits. repair_queue.py link
uses the older committed source census and repeats these lanes.
rehome_rows.py cannot serve without build/link_census/census.log; no census
was started to manufacture that artifact. No matching data-back artifact
was available for a valid data_back_rank measurement. No full link cycle,
nightly, boot operation, census or verifier/baseline change was run.

Untracked diagnostics are under build/link-seat-*.txt / *.log. All source
trials were restored except the two committed verified repairs. The remaining
work depends on provider recovery, class identity reconciliation, or the
documented compiler/EH prerequisites; unchanged blocked trials were skipped.
