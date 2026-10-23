Snapshot teardown binding repair, 2026-10-18

At BFME2 89a33d5f9c, Rva00426EB0Dtor.cpp had a private one-slot Snapshot
view whose explicit destructor store named g_00BBB554. Its seven code bytes
match the rowed Snapshot destructor at RVA 49B47C, but the relocation did not
name the canonical vtable. The existing canonical header supplies the proven
four-slot Snapshot ABI (table VA BBB554); no header or pin changes are needed.
The derived class already has novtable and only destroys its member, so it can
inherit this abstract interface without introducing concrete slot claims.

Paired current-object check against census c2c5ac8c27, 2026-10-18 11:36:
  before: Rva00426EB0Dtor 0/48 B, Snapshot.cpp 32/32 B; one Snapshot COMDAT finding
  after:  Rva00426EB0Dtor 48/48 B, Snapshot.cpp 32/32 B; zero findings
Net +48 existing authored bytes predicted linked, no new authored C++ bytes.
This is the legacy per-unit prediction, not a closed-strict/full-census result.

Acceptance: build.sh 2/2 rows exact; link_check --prepare-current provides one
self-strict reusable receipt and repeats 2/2 byte verification; eh_verify
EXACT 1; find_declared_unmatched passes. Paired checks use the same index and
current canonical provider. Scratch logs: build/snapshot-vtable-link-20261018/.

Same-cause sweep: Rva002105A6Dtor also loses only this inline Snapshot copy,
but embeds Snapshot concretely at +4. The canonical interface is abstract;
two direct named-vtable trials conflict with MSVC vftable synthesis even with
novtable. Restored that file, recorded blocked, released its claims. Other
private explicit Snapshot teardown consumers already link or retain additional
unresolved methods/vtable/layout blockers, so no unsupported view was adopted.
BFME1 64d369b9017 linking donor 67f4eab24 was reviewed: the corresponding
BFME2 DrawableDrawVeterancy unit already links; no repair/gain attributed.
