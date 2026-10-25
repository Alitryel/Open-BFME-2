# MapMetaData link ownership partition, 2026-10-25

The same published retail-truth-4 index (a9f880ad06, 2026-10-24 07:31)
previews MapMetaDataCopy.cpp at zero before and 304 authored linked bytes
after. This is a legacy preview gain, not a closed-strict measurement.
The remaining 856 authored bytes move to MapMetaDataCopyDeferred.cpp;
that new unit is absent from the census and is not counted as linked.

The retained native destructor, PlayerPosition constructor/destructor and
Coord3D INI callbacks do not need the waypoint copy instantiations. The
copy constructor, assignments and their EH children move together, retaining
the original layout, flags and bodies. BFME1 donor 0bf534ea7ccde110c456edb9cd2dd5dae823c953
keeps MapMetaData_dtor.cpp independent as well; its layout is semantic
reference only. BFME2 layout evidence remains that of the existing source.

Acceptance: all 35 rows byte-exact across both units; bounded
--prepare-current receipts for both; both ledger parent EH graphs EXACT;
the existing replay proof now follows the split and verifies all four native
parent graphs, the two complete copy cleanups and the full typed-list destructor.
Frozen-definition check and new-variants check pass. No pin, identity,
compiler flag or shared header was changed. The enforced hatch register
was updated with hatch_counters.py --admit: the existing copy alias and
unpinned tree specialization move, and one explicit non-retail emission
anchor is admitted for the separated inline operations. The player
destructor alias stays only in its original provider; aliases do not grow.

The three shadow code-identity findings stay with the unchanged copy
operations: waypoint map/copy-constructor calls at 0x3025A5 and tree assignment
calling 0x301F9B. The pre-existing Coord3D versus TreeHintPayload003012F0
identity reconciliation remains necessary; see attempts 83507/83622 in
re_attempts.log. Splitting does not repair or claim those calls. The legacy
index cannot establish closed provider closure for the new unit.
