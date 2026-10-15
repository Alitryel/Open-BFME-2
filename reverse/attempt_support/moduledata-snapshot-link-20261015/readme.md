# Module-data Snapshot dependency repair

Base revision: 26ad9b060fd387c512fad72efe4c356517c3b9dd.
Measurement index: a2839ea429, 2026-10-15 13:35, derived from census
5986a99448 at 04:52. before.json and object-proof.json pin its SHA256.

Three teardown views now inherit the existing canonical Snapshot header.
Their private bases incorrectly placed the entire inherited state in Snapshot
and declared non-pure virtual methods in a different order from its established
four-slot interface. The opaque inherited state now resides before each view's
owned members. Geometry and SpellRecharge keep their first members at +0x118;
ObjectCreation keeps its first string at +0x120 and its trivial tail through
+0x153. This preserves the existing limited teardown views; it does not recover
the intervening ModuleData fields or a complete derived class interface.

Target evidence is the already-rowed destructors at 004B6F81/114,
004B608A/75 and 004B45E8/84, their exact EH graphs, and the data ledger's
16-byte Snapshot table at RVA 007BB554 (VA 00BBB554). Its canonical destructor
provider is 0049B47C. Existing constructor/factory references in each source
support the member offsets independently of the header change. The old
address-named vtable external and linker alias are removed from all three units.

Donor review: BFME1 checkout a7c38d3b2597121f178ab5190b3062478823257d
already uses canonical Snapshot inheritance in LightningDrawModuleInfoCtorThunk.
Reviewed upstream repair 396401954929e227171233f0d106f0a204a2397c binds a
singleton teardown directly to its real vtable provider and reports scoped byte
and local legacy link checks. These are leads; BFME2's header, target bytes,
EH graph, and provider objects establish this repair. No donor source was copied.
The official BFME1 master fetch reported e082760734795655f086939df77b393f4b728375.
The freshness update remains blocked by another worker's live
file:reference/open-bfme-1 claim. The verified pointer and success stamp were
not advanced.

Acceptance: normal byte verification passes all six consumer rows; bounded
link_check.py --prepare-current on the three consumers plus
Common/System/Snapshot.cpp passes 10/10 with self-strict receipts. The receipts
resolve reference/shims/moduledata/Common/Snapshot.h explicitly. All three EH
graphs are EXACT without baseline use. Class, undeclared-definition, CSV and
converged-data checks pass; the latter reports eight addresses, zero second
names and zero unjudged rows. Enforced data identity reports zero findings.
The affected-unit placement rescan reports zero bodies and zero pins.

The paired preview replaces all four objects together in separate in-memory
copies of the same index. Each consumer's sole Snapshot COMDAT finding goes
from one to zero. The unchanged provider remains clean. Geometry gains 124,
SpellRecharge 85 and ObjectCreation 94 existing nonpadding ledger bytes:
the cohort goes from 32 to 335 linked bytes, or +303. All four units link in
the local preview. External providers retain legacy index currency; no
closed-strict, census, full-link or new authored-byte gain is claimed.

The commit hook also reports a shadow code-identity finding on Geometry
Upgrade's existing AsciiString destructor binding to 00036410 (divergent).
The paired section proof confirms that call and its named relocation are
unchanged by this repair. It remains a separate provider-identity concern;
the legacy preview is not proof of closed-strict resolution.

proof.py compares every retained non-debug section and its relocations after
normalizing the old vtable external to the canonical same-address name. The
only removed section content is the obsolete linker alias directive. The new
Snapshot table and scalar deleting destructor are whole byte-and-relocation
twins of the current provider. All retained code, data and EH sections remain
identical under that single vtable-name normalization.

Reproduction: at the base revision, strictly prepare the sources in sources.txt
and save their sources and objects under ignored
build/moduledata-snapshot-link-20261015 using each object's unchanged filename.
Save the paired pre-change findings and index hash as before.json. Apply the
repair, strictly prepare again, and run this directory's proof.py from the repo
root. It reads those scratch snapshots and writes object-proof.json there;
it never updates the index, census status or history. The committed JSON files
record this session's inputs and results. No full census, link cycle, nightly,
boot or scheduler runner was invoked.

The shared-cause sweep also inspected other private Snapshot families.
The single-slot 007C6F24 bases are a distinct unresolved identity and include
foreign-held files. SubObjectsUpgrade emits its own incomplete class table;
other views embed a concrete Snapshot or have separate vtable/provider
blockers. They require additional class evidence and were not changed here.
