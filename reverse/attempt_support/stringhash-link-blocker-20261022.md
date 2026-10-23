String hash selected-copy blocker, 2026-10-22
===========================================

Inputs: BFME2 f01c130123, BFME1 retained 37c3022de1; published census
ae3b3e68e2, retail-truth-4. No full link or census run.

StlSweepW4Rva00056BFE.cpp is the first emitter of hash<string>::operator()
in link order. Its /O1 /G7 /Oy- copy is not retail's. The current copies in
stlport_hash_map_string_uint_resize.cpp and
XferBlockWriter_rva009D86E0_Rva0060CB97.cpp are retail-proven, but lose to it.
Paired current-object check of the first emitter and string/unsigned table
leaves both unlinked (197 and 382 nonpadding bytes respectively).
The Xfer helper separately needs node-allocator providers and base-dtor repair.

Two careful source trials in the first emitter failed its 197-byte resize row
at 0x00056BFE. A declaration-only hash<string>::operator() specialization
changes bucket-helper inlining, adds an EH prologue and changes allocation and
loop register choices. Imported forceinline with the stock body
return __stl_string_hash(s) restores the call to the bucket helper, but retains
the EH/stack changes and different EBX/EDI allocation. The native prologue is
55 8b ec 83 ec 1c 53 57 8d 59 04; the trial adds EH setup and uses
8d 79 04 / 8b 5f 04 for the bucket-vector register and end load.
No candidate is byte-exact or banked as partial; the original source is restored.

The first emitter also retains the allocator-proxy two-argument constructor,
__stl_string_hash and the two-argument bucket helper conflicts. Removing one
copy alone is insufficient to make that unit link. Further work must preserve
the /O1 inlining/EH relationships while removing the selected wrong hash copy.
Do not repeat these unchanged declaration/import trials.

Before trials, link_check.py --prepare-current verified strict receipts and
all eight matched rows across the first emitter and string/unsigned table.
Original source, two failed byte-gate logs and paired previews remain untracked
under build/link-seat-20261022e/. File/RVA claims are released after restoration.
