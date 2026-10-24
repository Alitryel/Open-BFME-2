# Integration check of nine queued ownership repairs

Upstream base: 1cdea68ab618b3021aff4ad140e10c2e64ac1583. All nine queued commits rebased cleanly;
AGENTS.md is unchanged. The five repairs from this session add 2,463 B in
paired legacy previews; the previous four queued repairs add 2,317 B.
No Code source, flag, donor pointer, pin or alias differs from current upstream.

Rechecked all 72 affected units after rebase: 1,963/1,963 byte gates,
233/233 EH graphs EXACT with zero baseline; strings/floats/imports pass.
link_check --refresh refreshed stale objects without a census or link cycle.
Then measured current upstream's ledger and the combined repaired ledger
against the same sources and refreshed provider inputs: 62/72 units link in
both cases, 100,475 -> 105,255 B, **+4,780 B linked**. The frozen index's
99,904 B includes a 571 B pre-existing difference, excluded from our gain.
The compact reports retain each unit's result; rebase-paths.txt supplies the
exact scope. Original aggregate owners still have independent blockers.

Code identity: 91 -> 90 existing findings, no new finding. Frozen definitions,
check_csv and git diff --check pass. No baseline changes. These are scoped
legacy ownership/availability measurements, not self-strict, closed-strict,
new unique code or full-image census gains.

progress.py origin/master after rebase: +0 byte-matched, game C++ and census
linking deltas; 7,978,500 non-padding bytes rebuilt (100.00%). The published
link census remains 11b3872700 dated 2026-10-23 23:06. No new census is claimed.

Shared publisher returned busy at each commit. Pending commits remain queued
for the runner; file claims are released and verified landing leases remain
until publication. Remaining independent causes include mutable narrow-string
compare/insert/initialize, owned-record lifetimes and opaque private base
destructors. The rejected swap transfer has its own log and released claim.
