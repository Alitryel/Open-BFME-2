# Locomotor goal helper link repair

Source base: ca4fd002cc6d7ff34102c8e039c056e399022fa7.
Measurement index: 147cfae2cb, 2026-10-14 07:27; SHA256 is in
object-proof.json. The committed link_status.csv (67e1365aa9) was used only
for discovery. No census, status, history or per-row artifact was changed.

AIUpdateInterfaceLocomotorDistanceToGoal.cpp's private StateMachine view
stores its goal at +0x24. Its inline getGoalPosition emits 8d4124c3 (four
bytes, no relocations), digest 80c9c5883cb8. The first generic copy in the
index, MobMemberSlavedUpdate.cpp, emits 8d4128c3 (+0x28), digest
5d8d322110a2. AIUpdate.cpp's next copy agrees with that keeper; both current
cached copies reproduce their indexed digest. The generic getter has no
retail address. These incompatible views cannot share an out-of-line helper.
The existing matched parent independently proves its local loads at native
0x0026435E..0x00264558; Zero Hour remains its documented semantic guide.

Rename the implementation helper to locomotorGoalPosition and update its
single use. This assigns no new retail identity, layout, alias, pin or global.
The local view, compiler settings and matched row stay unchanged.

Acceptance:

- Bounded link_check.py --prepare-current before and after: strict reusable
  receipts and 1/1 exact byte verification. Separate ./build.sh: 1/1 exact,
  three compiler float literals, no skipped/baselined string or import refs.
- All nondebug object sections (including directives), extents, flags and
  relocation facts are identical after normalizing only the helper name.
  External definitions and undefined symbols also agree. Ten retained
  COMDATs are identical; the renamed four-byte helper keeps its entire bytes
  and relocation facts. Source/object/receipt backups and the comparison
  script remain under build/locomotor-goal-link-20261014. JSON records hashes.
- Same unchanged index: ordinary legacy link preview improves this consumer
  from one losing getter COMDAT to clean, LINKED 0 -> 506 existing bytes.
  Self-strict object currency is proven. The original copy was not selected;
  removing it cannot change the selected generic provider. The new helper
  has no other providers or consumers in the index.
- Frozen definitions, class gate, new-variants admission, converged-data
  check (eight addresses, zero second names), shadow data, EH, CSV and
  whitespace checks pass. Affected-unit placement resweep: zero bodies/pins.

New authored C++ bytes: zero. Closed-strict dependency closure, actual
link.exe placement and fresh census gains remain unmeasured. No maintainer
verification runner was started. Other losing getter consumers have separate
blockers or are held by other workers; this change does not claim their gains.

Reference review: clean verified BFME 1 gitlink
23b143233b5a8664a3bdf8572df6d905c310a5a1. Reviewed available donor repair
de59a7e9f891b3ed2d4221d151ca881f4b75a583: fixing conflicting inline helper
emissions while preserving matched parents is applicable as a principle.
Its Apt predicate and layouts are unrelated; no donor code was imported.
Target offsets and code identity rely on BFME 2 evidence and byte verification.

Freshness: fetched official BFME 1 master to a7c38d3b2. Another worker holds
file:reference/open-bfme-1; its checkout and verified pointer were preserved.
Comparative old/new full-gate verification remains with that owner. No success
stamp was written. Queue probes: repair_queue link, link_rank top/near/U/L;
name_globals dry-run retained zero edits; rehome_rows dry-run found ten
movable units, no changes applied. Stale ranked repairs and unchanged blocked
shared dependencies were not retried.
