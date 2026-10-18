Tech-building selector link repair, 2026-10-18

At b058c05f4b, the current legacy link predictor reports the selector unit
blocked by an undefined g_tacticalAIRegistry and a non-retail ObjectID vector
copy constructor. Current provider objects are included in both measurements.

Target evidence: all three global DIR32 relocations in native 572EFF resolve
to VA DFEEF8. data_rows.csv already assigns that four-byte datum to
g_00DFEEF8 (Rva002A8F24*) in Rva005EEA20Find.cpp. The selector now uses that
existing owner, with the same private view and no new datum or pin.

The copy call targets native 54878E, whose owned row is the ScienceType vector
copy constructor in ProductionPrerequisiteCopyCtor.cpp. Use that declared
provider through the established three-pointer vector header representation,
keeping four-byte ObjectID values and converting them back at lookup. The
existing ArmySummaryCopyBFME2.cpp uses the same scalar-vector representation.
The modified selector and its handler both reproduce retail bytes exactly.
An earlier ObjectID specialization-only trial was rejected after the shadow
identity check found its selected copy differed from retail. The final source
has no divergent code binding in that check. Its unreferenced, unpinned
ScienceType allocator-rebind helper still has a shadow definition finding;
retail-truth-2 does not discard a unit for such an unused helper.

Legacy predictor: 166 -> 685 B across the same three current units, +519 B
in one newly linking unit. Self-strict byte verification passes all six rows
and the data row of these units; the modified selector is 2/2. The ScienceType
provider retains unrelated PrereqUnitRec COMDAT blockers. No closed-strict or
full link-cycle gain is claimed. No new authored C++ bytes or ledger rows.

The session also checked ranked blockers, private-class rankings, the donor
linking repair log, small COMDAT and unresolved-call candidates, row rehoming,
and name_globals dry-run. No zero-gain rehome was applied. Independent deque
and tribute blockers were recorded through re_log.py and their claims released.
