# CaveContain lifecycle receiver prerequisite

The mechanical-seat handoff recorded missing lifecycle members in the composed
CaveContain class. A fresh normal dry run reproduced that rejection. Current
in-memory routing approves the seed and lifecycle donor; mixed and protected
sources remain excluded. The scoped planner's currency check passed, and its
same-name donor/path hints were reviewed separately from routing approval.

The declarations describe different incoming receivers. The lifecycle donor
uses the constructor-installed +0x34 interface, with its flag at this+0xCC,
cave index at this+0xD0, owner at this-0x2C, module data at this-0x30, and
shouldDoOnBuildComplete through slot 3. Those target facts are already
documented in CaveContainOnBuildComplete.cpp and its ledger rows. They cannot
be replaced with the seed's other interface offsets by selecting a longer
class declaration.

The donor now names that operand contract CaveContainBuildCompleteView and
casts its incoming receiver to it inside the two existing rowed methods.
The module-data operand view gets a distinct TU-scoped name, avoiding an
unrelated die-interface view collision. The seed declares the two existing
lifecycle methods without altering its earlier virtual declarations. No
complete CaveContain layout, donor-derived offset or new function identity
is claimed. Implemented symbols and all target accesses remain unchanged.

Verification on 2026-10-25:

- Frozen checks pass before and after; the seed retains its pre-existing
  absent-from-retail marker and unclaimed-definition note unchanged.
- ./build.sh: seed 13/13 exact; lifecycle donor 2/2 exact (16+65 bytes),
  with its existing data row exact. Literal and import checks pass.
- Normal merge dry run now accepts the seed and lifecycle donor, 15 rows.
  Separate scratch Verifier confirms every one of those 15 ledger rows.
- check_csv.py, git diff --check and normal commit hooks verify the change.
  Local before/after/current-plan reports are build/cave-prerequisite-*.txt.

Leave the now-compatible donor for Luna. No merge, removed files, recovered
bytes, hatch change or debt retirement is claimed. Xfer operand/include
ordering, the constructor's complete-object contract and the removal/recalc
layout assertions remain separate prerequisites. Protected destructor/pool
and mixed sources are unchanged.

Publication audit covers both pending prerequisite commits plus this staged
repair. None moves an existing source path; the only new path is the earlier
GameWindowGlobal header. Active tools/hooks/workflows, includes, build inputs
and registries require no repointing; original EA paths are retained. Keep
the two CaveContain file claims until publication is confirmed. The earlier
MetaEvent commit's shadow data check reported its existing TheMessageStream
wrong-name finding; converged-data and byte gates passed, and no data register
was changed or debt retired.
