Attack-aim goal accessor emission repair

AIAttackAimAtTargetStateOnExit.cpp marks its existing
StateMachine::getGoalPosition definition imported forceinline. The matched
update already inlines the embedded goal address. This removes an unused
standalone COMDAT competing with other class views, without introducing an
import reference, pin, alias, compiler flag, header, data owner or ledger row.

Identity and layout remain the existing target evidence, not a new accessor
claim: vtable C11008 names AIAttackAimAtTargetState, onExit occupies slot 5,
update slot 6, and WorldBuilder E1F050 identifies updateInternal. The private
StateMachine view embeds the goal at +0x24. The already recovered caller
establishes the access; this change supplies no standalone retail identity
for getGoalPosition. Zero Hour remains the semantic donor for onExit.

Measurement base: f1fcb8bc2d84ba0c46810a5bd21b81bc6914835a.
The unchanged index is a2839ea429, 2026-10-15 13:35, based on census
5986a99448, 04:52. measurement.json records its SHA256. Strictly current
original and repaired objects were substituted separately into copies of
that same index using link_check.refresh and check_object. COMDAT findings
fall from one to zero. The unresolved updateInternal method is unchanged;
no other finding changes. Legacy local LINKED bytes remain 0 -> 0, with
565 existing unique authored bytes in the unit. This is a conflict repair;
no self-strict placement or closed-strict closure gain is measured or claimed.
The committed census, status, history and local index remain untouched.

proof.json records source, object and strict-receipt hashes. All 17 retained
COMDAT bodies, sizes and relocation digests are identical. Every other
nondebug section, relocation target, external binding and linker directive
is identical. The only definition removed is the four-byte goal getter;
no retained relocation refers to it and no import binding appears.
peer-inventory.json lists the three indexed getter copies and absence of an
updateInternal provider. Peers were neither edited nor rebuilt/certified.
Their independent issues are not claimed fixed.

Acceptance:
- link_check.py --prepare-current before and after: strict reusable receipts;
  all 3/3 matched rows exact, one float literal, zero skipped/baselined refs.
- Independent ./build.sh: 3/3 exact, one float literal, zero named imports.
- eh_verify.py: zero EH-bearing rows, zero missing objects and zero failures.
- Frozen-definition, class, CSV, new-variants and whitespace checks pass.
- Shadow data: zero findings; converged-data enforcement: eight addresses,
  zero second names and zero unjudged rows.
- place_bodies.py: zero bodies and zero pins.
- Local link_check.py: only the known updateInternal unresolved name remains.

Donor review: rechecked BFME 1 repair
66b19a8e95a4add525ef808fcea088e306798e2b and its source diff and verification
message. Its imported-forceinline emission mechanism applies here; its Apt
identities, layouts, addresses and linked-byte gains do not transfer. No donor
source is imported. This extends the preceding guard-accessor repair pattern.
Official BFME 1 master was fetched during pull and now names
e082760734795655f086939df77b393f4b728375. The clean verified gitlink and
checkout remain a7c38d3b2597121f178ab5190b3062478823257d because another seat
holds file:reference/open-bfme-1. Comparative update verification and affected
donor refresh remain outstanding; no freshness-success stamp was written.

Discovery: repair_queue.py link and link_rank.py help/top/near/kind, then
bounded current-object link probes. RTS3DSceneFlushOccludedObjectsIntoStencil,
ParticleSystemDebugDisplayBody, Rva000C4069PristineQuery and
ScriptEngineRva00205D5D already pass locally and were not edited. The attack-aim
file and all three RVAs were claimed before editing. No unavailable data-back
artifact was used to manufacture a ranking.

Remaining handoff: updateInternal at 003508C5..00350D15 (1104 bytes) has a
corrected bank and existing compiler-shape blockers; this session did not retry
it. Preserve that bank and recorded evidence. Saved original/repaired source,
objects, strict receipts and executable comparison remain in ignored
build/aim-goal-accessor-link-20261015. New authored C++ bytes: zero.
No full link cycle, census build/measure/history, nightly, boot or scheduler
operation was started.
