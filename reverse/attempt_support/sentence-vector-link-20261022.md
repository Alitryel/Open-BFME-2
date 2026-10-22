# Sentence vector provider binding, 2026-10-22

BFME2 parent input 2865973a05; BFME1 checkout 37c3022de1ab;
published census 08160bc2c9 (2026-10-22 17:08). Only
Render2DSentenceBuildNotCenteredBFME2.cpp changes.

Declare the Render2D pointer vector Resize and base/dynamic destructors,
and PendingSurfaceStruct destructor, instead of instantiating conflicting
per-unit implementations. The source already declares Clear. The pending
surface destructor is the existing complete25B provider at native290D in
vector_class_resize.cpp; the dynamic vector destructor is rowed45B at1A3AB0
in render2dsentence.cpp. No new identity, pin, alias or class layout is
introduced. Renderer pointer naming remains donor provenance, as in the
existing providers; the full native sentence body independently verifies
all affected code, virtual-table references and calls.

Paired ordinary current-source link_check against the unchanged published
index: original source0/2240B links; final source2240/2240B links. Original
has8 losing/selected helpers. Final has none. Including the two current
provider units confirms the sentence unit still LINKS and vector_class_resize
stays368B; render2dsentence retains unrelated surface/font/surface-vector
debt. This is a LEGACY predicted gain of2240 nonpadding matched bytes, not
closed-strict or actual linker placement evidence. Authored C++ grows0B.

Acceptance: normal2/2 complete rows, five compiler float references and one
named import exact; strict reusable receipt prepared; frozen-source report
clean; no pin/ledger/header changes. Compiler /G7 /arch:SSE and all other
flags unchanged. Hook supplies remaining normal acceptance checks.

Cause sweep: Render2DSentenceBuildThaiBFME2.cpp has the same helper conflicts
plus independent BfmeWordVec::resize duplicate and short-vector fill/copy
conflicts; render2dsentence.cpp has unresolved surface Lock/Unlock, font and
other pending-surface providers. W3DGameClient and W3DTankTruckDraw also
have many independent blockers in the published ranking. No zero-gain edits
made to those units.

Scratch original/final candidates and before/after/strict logs:
build/seat-sentence-*. The baseline was restored temporarily and compiled
with the exact same single-source link_check command; the final source was
restored afterwards and strictly reverified before commit.

Final rebase validation: upstream fa9dc70e0a includes the independently
solved RefCountClass declaration in FamilyDeletingDtorsO2.cpp. Preserve
that complete upstream declaration when resolving the earlier queued
index-buffer repair. Normal scoped gates for that unit and both session
repairs pass18/18 after the rebase (build/seat-rebase-byte.log). The
session's newly repaired units retain the same legacy gain,1007+2240=3247B;
no census or closed-strict gain is claimed. progress.py origin/master
reports0 authored-C++ and frozen-census deltas, as expected for link repairs.

Read-only handoff: the paired current BlingList/lookup/award providers leave
only the award predicate's private spelling unresolved; its retail rows are
claimed by another worker, so no edit was attempted and the acquired file
claim was released. The shader-manager root arrays still need full data
reconstruction (prior77486), and the sort helper needs comparator identity
reconciliation (prior81638); neither unchanged blocker was retried. BFME1
freshness remains blocked by another worker's reference-submodule claim;
checkout37c3022de1ab is preserved, with upstream3cef00d2dd96 fetched and no
successful-freshness stamp written. Full census/link-cycle runners were not
started. Other queue probes and actual failed trials are recorded in the
session's existing logs and evidence.
