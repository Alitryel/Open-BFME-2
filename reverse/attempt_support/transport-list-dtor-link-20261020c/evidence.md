TransportContainModuleDataDtor.cpp now calls the already pinned list-base
teardown at retail 0x002FECBC through its existing declaration. The specialization
removes the local non-retail destructor and four now-unused helper COMDATs.
Paired current objects against the unchanged retail-truth-2 census index
5366c4f808 change this consumer from one losing COMDAT to LINKS: legacy
0 -> 114 nonpadding bytes. Its 104-byte destructor and 10-byte EH handler remain
exact. Retained nondebug COFF bytes, definitions, flags and relocations are
identical, with no new COMDAT. The unchanged current STL list provider and all
its findings are included identically in both phases. This is a legacy preview
with self-strict inputs, not a closed-strict gain or whole-census measurement.
The existing folded pin is unchanged; the ledger owner at 0x002FECBC is the
AsciiString list-base destructor in Rva002FED8DDtor.cpp. No new identity is
asserted for the POD placeholder.

Cause sweep: ten census emitters reviewed. Only the SaveGame Rva0022C987Ctor
also has a wrong copy. Its current object has three unresolved names plus a
separate wrong list-base constructor; this declaration alone cannot link it.
Other copies are unknown rather than retail-proven wrong. The visible-inline /
single-owner donor repair at BFME1 92f6bbe8 (51b97cd796) supplies the lane,
while addresses, current row checks and the measured gain are BFME2 evidence.

proof.py replays the paired check using original objects in ignored
build/link-seat-20261020c/transport/before; proof.json preserves hashes/verdicts.

Acceptance: `./build.sh` verifies both consumer rows. Before/after `link_check.py --prepare-current` verifies 43/43 rows with strict reusable receipts. Ordinary before/after CLI checks return 1 in both phases because the unchanged provider remains blocked; the consumer changes from blocked to LINKS. The paired proof refreshes both current objects against the same immutable index and verifies the provider findings are identical. No closed-strict closure is claimed. The BFME 1 reference update to 4483e88d changed no provider headers or compiler inputs; paired full/EH reference verification is preserved in the accompanying reference record.

Revalidated after upstream advanced to `6c433a3d2f`: 43/43 rows exact with strict reusable receipts; retained nondebug bytes/relocations still identical, same current provider findings in both phases, legacy 0 -> 114 B. `rebased-proof.json` and rebased CLI/strict receipts preserve the updated-ledger result. The accompanying ScienceType evidence is historical because upstream independently landed that fix; the incremental session gain over this upstream is 114 B.
