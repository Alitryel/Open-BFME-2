# Cylinder emission trig-wrapper link repair

At source base 9df7119f49, the current cylinder emission object fails solely
on its cos(float) and sin(float) COMDATs. Discovery and the supplied index
both measure ac77c85054, 2026-10-15 14:25 UTC. context.json records the full
base, frozen index hash and donor review. No census, status/history or
per-row data-back artifact was generated or changed.

The unit now scopes MSVC math.h's existing inline definitions static, restoring
the inline token immediately after the include. This follows the established
ObjectRva00291A8C and W3DView emitter repair. The target's existing algorithm,
float narrowing, compiler flags, layouts, literals, names and ledger remain
unchanged. Existing donor provenance is retained.

Target object evidence in proof.json establishes:

- All nondebug sections, complete bytes, flags and normalized relocations are
  identical. All five retained external COMDATs are identical in bytes, extent
  and relocation digest. No new external body is emitted.
- Four unreferenced external bindings become local: cos(float), sin(float),
  cosf and sinf. Their local section bytes remain identical. There is no
  nondebug relocation to these wrappers before the change. All other external
  bindings and linker directives are identical, with no new import.
- The unchanged, strict-current AptMathCallbacksBFME2 object supplies the two
  verified seven-byte callable float overloads. Its object hash and both
  witness bodies are recorded. Its source was only read/verified, not edited.
- In-memory refresh of exactly those two before/after objects against the same
  frozen index changes the consumer findings 2 -> 0. Provider findings remain
  zero; data findings remain zero. Local legacy LINKED changes 1,332 -> 1,544
  bytes for the pair (consumer 0 -> 212). This is a prediction, not a new census.

Acceptance: bounded strict preparation passes 21/21 rows across the pair before
editing and 1/1 for the edited consumer afterward. Final explicit ./build.sh
passes 21/21 with one string, five floats, no skipped/baselined references.
EH verification finds no EH rows or missing objects. Enforced data checking
passes with zero findings across both sources; converged-data admission checks
eight addresses with no second name or unjudged row. New-variants, class gate,
declared-function and whitespace checks pass. place_bodies reports zero bodies
and zero pins. Backups, dependency receipts and the comparison script remain in
build/cylinder-math-link-20261015. The script reuses the existing scratch COFF
normalizer from build/pathfind-round-link-20261015/proof.py.

Self-strict byte evidence is established; closed-strict closure and executable
placement remain unmeasured. Authored C++ gain is zero. No full census, link
cycle, nightly, runtime or scheduler runner was started.

Donor linking repairs reviewed: de59a7e9f8 (converge incidental helper copies),
d003077f0b (use a matched provider), and fea964f854 (native allocator bindings).
The first two principles apply; no donor source/layout was imported. Verified
checkout/gitlink a7c38d3b2597 remains unchanged. Official master was fetched at
8fd286029cee; the pre-existing comparative full-baseline blocker remains
(recorded old-input baseline needed 2,982 stale TUs, interrupted with 2,806
remaining). No unchanged multi-hour baseline was repeated, pointer advanced,
or freshness success stamp written.

Other discovery: several top-ranked blockers already link with current source
(AIHuntStateUpdate, PathRva00363FA4, HordeMeleeHoldGroundRva005D7011 and
HordeMeleeAmoeba). SpawnBehavior's canonical lookup adoption remains deferred
by the existing byte/codegen evidence in spawn-lookup-link-20261015; it was
not retried. GiantBirdSlowDeathBehavior's file claim is held by another worker,
so that otherwise similar candidate was left untouched. Remaining broader
provider/census freshness is not claimed repaired here.
