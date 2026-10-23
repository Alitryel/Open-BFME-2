Object-pointer vector teardown link sweep, 2026-10-20

Keep STLport 4.5.3 vector<Object*> teardown visible and forceinline, importing
its external copy so these units do not emit a conflicting destructor. The body
is the existing vendor header's _Destroy(start, finish), with the existing
per-unit _Vector_base specializations unchanged. No new layout or identity.

Paired legacy-index preview e7a7769fe5 (2026-10-20 18:36): group ctor 0 -> 65
and 004DFF2C group merge 0 -> 316 nonpadding bytes: +381 total. Retained COMDAT
byte/relocation digests unchanged, and neither successful object gains any
unresolved reference. These sources had only the vector destructor blocker.
All retained COMDAT digests unchanged in the final six-unit probe. The ctor is
included in the same-cause sweep despite its small size.

Strict preparation before: 42/42 rows across seven initial units (one was then
excluded for another worker's live claim). Strict after: 12/12 across five
trial units, including both kept units. Normal full byte gate on the final two
units passes. Strings, floats, imports, new-variants, class gate, undeclared
definitions, data converged and diff checks pass. Self-strict receipts plus a
legacy index preview; no closed-strict closure or executable gain claimed.
Authored C++ bytes +0.

Deferrals (original sources restored; trial patches and blocker facts saved):
- External declaration only changes inline cleanup/control flow in five units.
- Import-forceinline defined before base specialization fails C2908: place it
  after the already-existing base specialization instead.
- ManTheWalls still changes 4C78AF/4C799B register/lifetime shape and loses the
  7902E2 element-cleanup callee under import-forceinline; three byte rows fail.
- ProductionUpdateClearUpgrades, SiegeDeployHordeInitiate, AIRva005D8B0BCheck
  preserve all row bytes but retain EH cleanup references to the imported vector
  destructor, leaving __imp_??1vector<Object*> unresolved. They gain no link bytes
  and are restored. A proper non-imported EH cleanup provider strategy is needed.
  No import alias or pin workaround added. GroupMerge 00283114 was never edited:
  its shared row 002DFCF6 is claimed by another worker.

Donor linking repair review remains 4483e88da1c2 as in the earlier frame-global
and inline-owner evidence. The direct body here is the same vendored STLport
header, not a donor layout transplant. t=18 model=gpt-6.1-sol.
