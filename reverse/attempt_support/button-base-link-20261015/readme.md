Button-record private base view link repair

Discovery: repair_queue.py link and link_rank.py --near, followed by current
local previews. Base checkout ff2bf0e89ac325d8f10e9dc372dfcb9529cbc4c2.
The exact index hash, measurement commit 19a2565407 (2026-10-15 09:33),
census ancestry 5986a99448 and paired findings are in object-proof.json.
Committed link_status.csv measures a different tree and is not the basis
for this before/after result.

Rva005E92F7Dtor.cpp's only current blocker was the out-of-line virtual
Rva005F5C77Base0 destructor. Five units emit that name in three different
forms. This unit's seven-byte destructor stores Rva005E92F7Base's vtable;
the first selected copy in Rva005E91A9Dtor.cpp stores Rva005E91A9Base's
vtable; three other copies store Rva005F5C77Base0's vtable. Identical raw
instruction bytes have different DIR32 referents, so these are not twins.
The indexed first provider wins by link order, not by the three-copy majority.

Target evidence already establishes the constructor/destructor pairing,
prefix extents, vtable bindings and cleanup graphs; see
reverse/identity_evidence/button-record-base-constructor.md. The record-base
inheritance is explicitly an inferred codegen model, not an established
application identity. Retain that uncertainty and give this private base
view the distinct neutral name Rva005E92F7RecordBase. This reconciles its
emitted constructor, destructor and tables coherently. No original class
name, new layout, provider body, pin or data address is claimed.

Acceptance (full output in checks.json):

- build.sh and link_check.py --prepare-current pass all 8 rows, two string
  literals, zero compiler float literals and zero named imports. The touched
  unit has a strict reusable current receipt. EH verification is EXACT 3/3.
- Frozen-definition, canonical-class, data shadow, enforced converged-data,
  CSV and new-COMDAT-variant checks pass. Hatch counts stay empty/unchanged.
- proof.py compares all nondebug sections, bytes, flags, external names and
  symbolic relocations after only the private class name substitution.
  Every COMDAT retains its complete raw instruction/data bytes. Five COMDAT
  names change; two retained parent bodies change only relocation names.
- Paired same-index local previews refresh the explicit candidate plus the
  five peer objects in memory. The candidate's sole COMDAT finding disappears;
  LEGACY predicted linked bytes rise 0 -> 369. The old destructor family loses
  this incompatible copy (three digests -> two) with its selected provider
  unchanged. Every peer's findings stay unchanged. Peer objects are recorded
  by hash; their receipts are not claimed strict.
- place_bodies.py resweeps the unit; see checks.json for its result.

This is self-strict byte verification and a LEGACY local link prediction.
No closed-strict gain, new authored C++ bytes, full-link placement, census
update or runtime verification is claimed. No maintainer-only runner was
started. Baseline source/object/receipt and post-change object/receipt remain
under ignored build/button-base-link-20261015 for paired reproduction.

Same-cause sweep: Rva005E91A9Dtor, Rva005F589ECtor, Rva005F5C77Ctor and
Rva005F5F2BCtor define the other private views; Rva005CC3C0Permuted only
declares the old base. Renaming the selected first provider would change
the provider used by other consumers, including that declaration-only unit.
That requires separate target identity and lifecycle evidence. Other peers
also retain missing holder/global/destructor providers and unrelated COMDAT
conflicts. This repair does not claim to resolve those units.

BFME1 linking review: retained verified pointer
a7c38d3b2597121f178ab5190b3062478823257d; official master fetched read-only
at eab55866b6a39aa54797b2d687f705c99e834b43. Reviewed donor repair
4966496c5ae401ec877a044e1ae6dd04f9d9f65c: surplus private inline COMDAT
reconciliation is applicable in principle. Here the referenced base must
remain emitted, and BFME2 proves a distinct private view instead. No donor
source, layout, flags or dependencies are imported. Another worker holds
file:reference/open-bfme-1, and the previously recorded comparative-full-gate
freshness blocker remains; no pointer update or freshness success stamp.

Queue triage: current local previews already link TerrainLogicWaypointLookups,
AIIdleStateUpdate, GapBodiesSeat1B, AptMpGameSetupRefreshMapList and
Rva005D18E2Child despite stale census rows. Higher-ranked ActiveBody,
particle/debug and display work has peer claims. Other inspected candidates
retain unrelated record-destructor, UV buffer, texture-pointer or GPU vtable
conflicts; no changes or claims were made for those units.
