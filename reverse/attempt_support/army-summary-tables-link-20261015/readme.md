Army summary visitor-table link repair

Source base: 777e569ec616ad564bc5e614df94ce42c02fdbc7. The available census
index was measured at ac77c85054, 2026-10-15 14:25 UTC; proof.json records its
SHA256. No census, index, status, history or per-row data-back artifact changed.

ArmySummaryDescription.cpp previously referenced two undefined address-named
arrays. Native constructor 220B04 places BE6A68 at complete-object+0 and
BE6A64 at +4. Retail dwords are respectively 6206F9 and 620D1E; the string
ArmySummaryDescription begins at BE6A6C, proving the end of both single-entry
tables. Existing exact methods at 2206F9 and 220D1E establish their receiver
and argument ABIs: the latter already accepts the secondary-interface pointer.
Their original class/interface names remain unknown. No new identity or field
layout is claimed. The arrays use single-inheritance member pointers, which
MSVC emits as these four-byte code addresses without adjustment thunks.

Each table is defined alongside its existing method, with descriptive table
names replacing the unresolved names. Both new data_rows.csv rows pass sizeof,
raw-byte and code-relocation verification. No pins, aliases, code rows, compiler
flags, headers or gate baselines change. No new authored C++ bytes are claimed.

BFME1 donor linking repair 0dbe7e53e56a3e319104c52f9d59c13668158374 was reviewed:
its verified data-definition technique applies, its buff table and target ABI
do not. The verified clean submodule/gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
Fetched official master was af3fd9386a9f479fcbda9a9d87c4244920a7ef5a. Freshness
is overdue and its update is peer-claimed (file:reference/open-bfme-1); no
headers were substituted and no success timestamp advanced.

Acceptance:

- Strict reusable preparation passes 13/13 existing rows in the two changed
  units before and after. Normal ./build.sh passes all 13 rows and both data
  rows (8 bytes). Three literal checks pass with no baseline/skipped entries.
- EH verification: five EXACT, zero baseline entries. Enforced data_check:
  zero findings. check_csv, undeclared-definition checks and diff --check pass.
- proof.py compares every retained nondebug section's bytes and normalized
  relocations before/after. Only two constructor data symbol names change;
  the two new .rdata sections each hold one four-byte table. Both current
  objects have strict reusable receipts. Renumbered funclets remain bound
  by their exact parent EH graphs.
- The paired check refreshes exactly these same two objects in separate
  copies of the same frozen index using link_check.refresh/check_object.
  The summary consumer loses both unresolved names, with no other findings;
  the 82-byte object-visitor provider remains clear. Legacy local LINKED
  previews 82 -> 1145 bytes (+1063). These counts exclude padding and differ
  from raw ledger extents. Dependency closure was not prepared, so this is
  self-strict object evidence plus a legacy local preview, not closed-strict
  closure or a full-link measurement. Maintainer-only runners were not run.

The generated inventory has many missing unrelated objects (22644 sources);
its global output is not a full ownership measurement. After preparing the
unchanged neighboring string consumer Rva00220CD4Ctor.cpp (2/2 rows, one literal)
to preserve the known BE6A6C bound, data_ledger.py --out produced the two exact
owned rows in generated-owner-rows.csv. Only those complete generated rows
replace the old inventory rows. refresh-owner.py reproduces that narrow copy.
This read-only witness was not edited and is not counted as a linked gain.

Reproduction uses ignored snapshots and sources.json under
build/army-summary-tables-link-20261015; proof.py writes proof.json. The ordinary
unrefreshed CLI cannot see the newly defined cross-unit table until provider
slots are refreshed; the paired in-memory preview explicitly does so. Broader
provider currency and executable placement remain for the next authorized
measurement. File claims cover both edited source units and are released after
publication/session handoff.

Publication rebase onto 775b89b563: the earlier unpublished Drawable maximum
repair was already present upstream, so its redundant commit was dropped.
The original local batch is retained on session-before-army-publish-20261015.
A Cylinder trig comment conflict retains the upstream wording and identical
code. Both sources of this table repair are unchanged by the rebase; strict
preparation and the paired proof pass again against the same census index.
AGENTS.md and the verified donor gitlink were unchanged across that rebase.
