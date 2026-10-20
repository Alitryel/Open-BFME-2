POD340 instantiation scope, 2026-10-20
====================================

Baseline d0551407f0; unchanged BFME1 inputs92f6bbe8e1dcdb46b5d27da0674313efc822b790.
The rowed no-EH vector<BfmePod340>::_M_allocate_and_copy<const BfmePod340 *>
provider owns45B at004D9C1C. stlport_pod_vector_bodies emitted a competing
EH-enabled wrong copy, selected first, blocking the126B reserve at004DA039.
Replace this one whole-vector instantiation with the explicit matched push_back,
const-copy/fill helpers and allocator. These retain every151 row in the unit
while dropping unused vector bodies, including the losing allocation/copy.
This changes instantiation scope only; no new type identity is asserted.

Checks: before strict155/155 across the emitter and four related providers/
consumers; after emitter151/151 (ordinary byte gate plus strict receipts).
Paired same-index proof uses strict-current objects in both phases; retained
nondebug sections and symbolic relocations are identical, with no rebinding.
EH10graphsEXACT. The reserve alone becomes clean: LEGACY predicted0->126B,
self-strict objects. Closed-strict closure/gain is unmeasured. Other four units
stay blocked; the emitter has independent debt. Provider's full blocker lists
are condensed to counts in proof.json; removed COMDATs retain their hashes.
Class, declared-definition and data/converged checks pass.

Blocked sibling: Pod24. A declaration-only _M_allocate_and_copy member-template
specialization under the whole-class instantiation triggers VC7.1 C1001 at
vendor/stlport/stl/_vector.c:95, P2/main.c148. Selective Pod24 members plus an
external rowed overflow declaration avoid the ICE but change push_back BDAAA
from retail55B to58B (REL32 at54 needs58 bytes). The original native extent
is correct. Failed diagnostic patch is retained; all Pod24 edits reverted.
Do not repeat these visibility/whole-class trials without new evidence.
The Pod44 copy-ctor blocker is already banked as identity/layout reconciliation
(re_attempts57844), and Pod172 has independent alias/visibility blockers.
No zero-gain edits were kept for these siblings.
