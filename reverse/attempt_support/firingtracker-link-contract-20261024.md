# FiringTracker link prerequisite, 2026-10-24

Inputs: BFME 2 `9dac27055e`, verified BFME 1 checkout `f5140c1c`,
published census `11b3872700` (retail-truth-4). No production source changes,
new authored bytes, or newly linked bytes. These are legacy previews;
no self-strict or closed-strict improvement is claimed.

## Target evidence

The native destructor at RVA `0x004DEA0C`, extent 86, installs vptrs
`0x00C61530`, `0x00BEFF90`, `0x00C61524` at object offsets 0, C, 10.
The 149-byte constructor at `0x004DEB10` installs the same tables. The
update table at C61524 has three code entries, ending before the primary
table at C61530. The primary table has thirteen entries, ending at C61564
where the FiringTracker string starts. Its first four code addresses are
8DEBA5 (deleting destructor), 897805, 8DEA62 (GetSnapshotName), and
8DEBC1 (xfer).

## Current class views and acceptance

FiringTrackerDtor.cpp and FiringTrackerCtor.cpp each emit three one-entry
tables: a purecall update entry, a purecall BehaviorModuleInterface entry,
and a deleting-destructor ObjectModule entry. The full donor emitter in
FiringTracker.cpp instead emits an 8-byte update table, a 136-byte behavior
table, and a 60-byte ObjectModule table. Its ObjectModule table starts with
crc/xfer/loadPostProcess/deleting-destructor, unlike the native ordering.
These are observations of compiled views, not proof that either view gives
the native class contract. Copying the donor declarations or merely removing
its tables would not establish that contract.

Before and after this read-only investigation, link_check on the native
constructor, destructor and Xfer providers reports 1543 -> 1543 B: Xfer
already links; constructor (149 B) and destructor unit (124 B including
deleting wrapper and EH handler) each fail on the three competing tables.
The byte gate passes 4/4 rows across the constructor and destructor units;
find_declared_unmatched also passes. No compiler variants were attempted.
Reopen with a native Module/Snapshot/UpdateModule contract and reconcile
the table emitters together. The file and parent-RVA claims were released.

## Other checked lanes

link_rank top 30, near 2, expanded near 8 and owner gaps, class_views
--blockers, and repair_queue link were checked. A read-only refresh of the
30 receipt-current authored candidates with 1..15 census blockers retained
the known native-class, missing-provider and destructor/STL-codegen causes;
it is triage, not a whole-repository exhaustion proof. Many larger shared
families remain foreign-claimed. ObjectCreationNuggetParse and its donor
ObjectCreationList preview both remain at zero, with missing nugget
destructors/tables and further donor layout/STL/provider blockers.
name_globals --dry-run offers zero edits. A fresh rehome --limit 1 scan
checks the first five pairs: four fail and the known EntryCtor placement
matches. Prior evidence already establishes that this placement adds no
linked bytes. The fresh paired preview confirms both units already link:
EntryCtor 29 -> 29 B; the current home unit 2441 -> 2496 B, an inherited
55-byte change relative to the census, not this seat's repair.
No matching data-back measurement
artifact was available. No maintainer-only runner was started.

Official BFME 1 master was fetched at `32774ab033`; reviewed the recent
StringBase/topple/online-callback/GeometryInfo/terrain repairs. Their relevant
BFME 2 patterns are already present or retain the documented target-specific
prerequisites. The submodule scope is foreign-claimed; the verified pointer
was preserved and no successful freshness stamp was written. Earlier
handoffs under link-seat-provider-recheck-20261024.md and
link-seat-current-recheck-20261023b.md remain applicable; no unchanged failed
variant was repeated.
