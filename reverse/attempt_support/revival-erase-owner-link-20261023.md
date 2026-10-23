# Bind revival transfer to the existing range-erase owner

2026-10-23, gpt-6.1-sol; parent 01fffd90c7. Published census b711de3634,
2026-10-23 14:28, retail-truth-4; verified BFME1 input 96c88c73 unchanged.

UnitRevivalTrackerXfer.cpp emits a non-retail vector<UnitRevivalEntry>
range-erase copy that references the undefined private element assignment.
The exact whole 290-byte transfer at 0x0037F39E calls native erase 0x002E2690
from 0x0037F435. That complete 51-byte operation is already rowed under
vector<Rva002E2690Element> in StlportVectorEraseRangeFamily.cpp. Both views
use the same three-pointer vector ABI and the same D8-byte entry stride;
the target transfer's vector access and its existing entry lifetimes establish
that connection. Neighbor LivingWorldPlayerExtractRevival.cpp already calls
this exact erase owner directly for its revival records.

A declaration-only erase removes the local COMDAT and assignment dependency
while preserving all three matched rows, but leaves the typed erase name
undefined. Instead use an imported force-inline specialization that casts
the vector and iterators to the existing neutral element view and calls its
declaration-only erase. It emits the original native call with the rowed
owner name and no forwarding COMDAT, pin, alias, or additional body.
No new element field identity or layout is inferred by the casts.

Same-index legacy current-object preview: **0 -> 290 B linked**, LINKS.
Five related consumers were swept: LivingWorldPlayerExtractRevival (531 B),
LivingWorldPlayerCreateRevival (1165 B), tracker constructor (69 B), finish
(111 B), and army summary (174 B) already link, unchanged total 2050 B.
They need no edits and contribute no claimed session gain.

Acceptance: all three source rows pass the byte gate; --prepare-current
verifies them with strict reusable receipts; find_declared_unmatched and
--new-variants pass. The transfer's cleanup label is naturally renumbered
and its existing parent EH graph resolves it. Normal commit hooks verify EH.
The measured improvement is a legacy preview, not self-strict or closed-strict
closure. In particular the multi-family erase provider has unrelated blockers;
no whole-program closure is claimed. Census/index/status remain unchanged.
Diagnostics: ignored build/link-seat-revival-{before,after,gate,owner-gate,
owner-after,strict,variants,peers}.log.
