# Living-world unit upgrade predicate link repair

Checkout base: b8d467533ddcc67fbf59165b52abc461ed0c76ac. The runner's
local census index measures 147cfae2cb, 2026-10-14 07:27. Its SHA256 is
recorded in object-proof.json. The older committed link_status.csv is only
a discovery queue; no census index, status or history was updated.

Rva0059B5A3Describe.cpp emitted a five-byte UpgradeMaskType::any forwarding
COMDAT, a tail jump to _STL::_Base_bitset<32>::_M_is_any. The index selects
SpawnBehavior_update.cpp's different same-name implementation first; neither
private helper has its own retail address. This was the description unit's
only local link blocker. The description already calls the rowed storage
predicate directly: its unchanged relocation at body offset 382 corresponds
to the CALL opcode at retail RVA 0x0059B720, targeting 0x000454A6. The
predicate's existing owner is stlport_BaseBitset32IsAny.cpp (20 bytes).

Remove the private forwarding definition and call the existing inherited
storage predicate explicitly. No new identity, layout, pin, provider, global,
compiler flag or ledger row is introduced. The caller's 552-byte extent,
all 13 retained COMDATs, their raw bytes and relocation facts, strong
definitions, undefined names and weak bindings remain identical. Paired
object facts and the before/after object hashes are included. Source/object
backups and the executed comparison script remain in the ignored
build/unit-upgrade-any-link-20261014 directory.

Acceptance:

- Bounded link_check.py --prepare-current passed before and after: strict
  reusable compiler receipt, 1/1 exact function, eight verified strings,
  two named imports, no skipped/baselined string or import references.
- ./build.sh on the touched source passed 1/1 exact. EH verification is
  EXACT 1, zero missing objects or baseline exceptions.
- Same-index ordinary link_check.py changes this consumer from one losing
  COMDAT finding (LINKED 0 bytes) to clean (LINKED 552 bytes). The removed
  copy was not selected, so no other consumer's chosen provider changes.
  The index contains only the first provider and this losing copy for the
  removed name; this repair has no additional same-cause consumer to sweep.
- Frozen-definition, canonical-class, new-variants admission, converged-data
  (eight addresses, no second names), shadow-data, CSV and whitespace checks
  pass. Placement resweep finds zero bodies and zero pins.

New authored C++ bytes: zero. The improvement is 552 existing bytes in a
legacy local link preview, with self-strict object currency proven. No
closed-strict dependency closure, actual link.exe placement or fresh census
gain is claimed. No full link cycle, census build/measure/history, nightly
or boot runner was started.

Reference review: BFME 1's verified gitlink is
23b143233b5a8664a3bdf8572df6d905c310a5a1. Reviewed donor linking repair
de59a7e9f891b3ed2d4221d151ca881f4b75a583, which reconciles competing
private Apt predicates while keeping native callers identical. The private
helper-emission cause is applicable here; its Apt-specific expressions and
layouts are inapplicable. This repair imports no donor code. Identity and
call relationship evidence comes from the existing BFME 2 row and unchanged
native relocation, rather than a donor name inferred from matching bytes.

BFME 1 freshness remains pending: official master fetched successfully to
a7c38d3b2597121f178ab5190b3062478823257d, ahead of the verified gitlink.
Another worker holds file:reference/open-bfme-1. Its clean checkout and
committed pointer were preserved; comparative old/new full byte verification
and the update remain with that claim owner. No freshness success stamp was
written.

Preparation recovery (2026-10-14)

The runner rebased original commit 8de34c5cc92c1155da5343a1e3e115ccb035c110
onto 45cb2f9aa2de2a256a7c31d37d6d6cb900c9ebbb. Upstream commit
2e69cdffb3db1e6912fea7600255b7bcf0708932 already contains the same source
repair, with an explanatory comment. The conflict was confined to that
comment. Kept the upstream source exactly and continued the rebase; the
recovered commit contains only this seat's evidence and attempt-log record.
The 552-byte legacy preview improvement above is the same repair already
landed upstream, not an additional gain from recovery.

The preparation record names no stash or resync stash. All eight saved
evidence/log paths are retained; the source matches the synchronized upstream
blob exactly, and there are no other staged, unstaged or untracked edits.
The preparation backup ref refs/runner/preparation/1791974618800842576 and
all ignored build/unit-upgrade-any-link-20261014 source/object backups remain
intact. No new task or claim was taken.

Recovery acceptance at the synchronized revision:

- check_csv.py passes; git diff --check and the conflict index are clear.
- link_check.py --prepare-current passes strict scoped verification: 1/1
  exact function, eight strings, two imports, no skipped references.
- ./build.sh on the source passes 1/1 exact; find_declared_unmatched.py
  reports all definitions matched; link_check.py --new-variants passes.
- Ordinary local link_check.py reproduces LINKED 0 -> 552 on the same
  147cfae2cb index, whose SHA256 still matches object-proof.json.
- Current compiled object SHA256 is
  549bab931a481f89b55b4aa55e2f21c7651e7f8fde60127232c6d3e5998cf7ae.
  Its whole-file hash differs from the saved object, but an explicit read-only
  comparison confirms all 13 COMDAT bytes and relocations, strong definitions,
  undefined names and weak bindings equal after-facts.json exactly.

No additional authored bytes or closed-strict gains are claimed. Broader
link-cycle/census verification and the previously pending BFME 1 freshness
update were not started during this recovery-only session.
