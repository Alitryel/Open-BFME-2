# RadiusDecal clear/destructor prerequisite

The GameClient mechanical-seat handoff reported C2600 when composing the
existing clear/destructor donor. A fresh normal dry run reproduced it.
The scoped planner's original-path alternatives and prerequisites were
reviewed and its currency check passed; current in-memory routing separately
approves both sources. The committed TU map is not regenerated.

The destination now declares its already-rowed clear and destructor methods.
The donor uses the destination's existing m_decalTemplate, m_shadow and
m_empty spellings, retaining the target stores at +0, +4 and +8. The holder
is still accessed through the original RadiusDecalObject slot-2 Release
operand view, with a cast from the existing opaque Shadow pointer. No Shadow
layout or new original field name is claimed. The donor's 28-byte clear and
5-byte destructor retain their complete bytes and relocation targets.

Verification on 2026-10-25:

- ./build.sh on both sources: 10/10 matched, four float literals checked.
- Declared-unmatched checks pass before and after for both sources.
- Normal merge dry run accepts the destination and clear/destructor donor,
  preserving all ten rows. A separate scratch Verifier confirms 10/10.
- check_csv.py, git diff --check and normal commit hooks verify the change.
- Local before/after reports: build/radius-prerequisite-{before,after}.txt.

Leave the now-compatible donor for Luna. No merge, removed files, recovered
bytes, escape hatch or identity-debt retirement is claimed. The update and
xfer donors still have no destination-context baseline; the three mixed
sources are untouched. Retain both file claims until publication is confirmed.

The publication audit includes all three earlier pending prerequisite commits
plus this repair. None moves an existing source path. The earlier new
GameWindowGlobalView.h include was verified from both source directories;
active tools/hooks/workflows, includes, build inputs and registries need no
repointing. Historical EA paths and evidence are preserved. No protected
register changes are included.
