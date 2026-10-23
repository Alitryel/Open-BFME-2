# Vector copy constructor link isolation trial

Baseline: 25074ab48a, published census e20daa4e78 (2026-10-21 21:42).
StlportVectorCopyCtorFamily.cpp: seven matched 96-byte constructors, 670
nonpadding bytes; legacy link preview remains 0. Strict reusable prepare and
normal byte checks initially pass 7/7. BFME1 pointer reviewed: 37c3022de1ab.

Target row/pin evidence distinguishes 38-byte uninitialized-copy loops and
45-byte placement-copy helpers from this TU's size-only empty-destructor views.
The application identities/layouts remain inferred, as in the existing rows.

Trial 1: move constructors 4244EE,52CBC5,52CE7D,52D417 unchanged to a deferred
TU, keep 2B9247,32BF6B,52CC64, and use import-forceinline placement-copy
specializations for Rva002B72C9 and Rva0052BE33. Normal byte gate passes7/7.
The two placement-copy losers disappear, but their const-input uninitialized
copy helpers are now nonretail and selected wrong; original unit still0B.
New-variants refuses the deferred copy of the 52D3F1 helper because the rowed
provider in Rva0052D3F1UninitializedCopy.cpp already exists.

Trial2: declaration-only placement copies instead of import-forceinline;
declaration-only 52D3F1 const-input helper in deferred TU. First six parents
still byte-match, but 52D417 changes its96B body: extra savedEBX, zero-initialized
tag with STOSB, changed ESI/EDI/EBX allocation and additional stack slot.
Original unit still0B, with the same two const-input helper losers.

The two source trials are preserved as a diagnostic patch alongside this note.
All production edits were restored; no new row or pin, baseline or gate edit.
Do not repeat this split or declaration trial unchanged. Next useful work is
real const-input helper/provider reconciliation (including target38B no-EH
loop shape and correct placement-copy calls), preserving the parent's callee
visibility and register summary. Source isolation alone does not settle it.

Scratch logs: build/link-copyctor-{current,before-prepare,gate1,gate2,variants,
after-family,after-family2}.txt. This is a link-only blocker, not a verdict
against the existing matched constructors. t=7 min.
