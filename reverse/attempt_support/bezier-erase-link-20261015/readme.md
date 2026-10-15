Bezier projectile constructor: use the existing twelve-byte erase provider

Base checkout efa93a5f66d968f64238c3199873fe8b9d6ae1db. Discovery used
repair_queue.py link, link_rank.py --top / --near and current receipt-backed
objects; several high-ranked blockers were already repaired in current sources.
The paired measurement uses index 19a2565407 (2026-10-15 09:33), based on
census 5986a99448, rather than committed link_status.csv at 28269d8e8d.
object-proof.json records the exact index hash and all object hashes.
No census, index, status, ledger, pin or baseline was changed.

Target evidence: the 265-byte BezierProjectileBehavior constructor at
0x0045C850 calls 0x002A133B at opcode offset +0x9A (REL32 field +0x9B).
Its old vector<Coord3D>::erase spelling belongs to the distinct 38-byte
body at 0x00081A24. An additive pin permits the ordinary byte gate to
reproduce the other address, but the identity-aware link check correctly
rejects that constructor relocation. The existing verified provider at
0x002A133B is vector<Gen_p12pod>::erase in Rva007D85C0FilterShutdown.cpp.
The provider's twelve-byte trivial carrier and its declaration are already
established in that unit; this repair makes no claim about its original name.

Use that existing carrier for the range erase through a temporary vector
view. Coord3D vector construction, storage, layout and lifetime remain as
before. This operation removes/copies trivial twelve-byte elements; the
provider and native call establish its ABI. No arithmetic interpretation
of the carrier elements is introduced. No new alias or pin is needed.

Acceptance and measured effect:

- Before and after --prepare-current: all 12 rows across the four explicit
  providers/consumers byte-exact, with strict reusable receipts; string,
  float and import checks pass with no skipped/unverified references.
- Paired in-memory refreshes against the same index remove the wrong erase
  edge. Constructor identity verdict changes wrong -> unknown, not retail:
  other unresolved references still prevent a complete identity judgment.
  Its findings improve from 3 unresolved / 2 COMDAT / 1 selected to
  3 unresolved / 1 COMDAT / 0 selected. No findings are added in any unit.
- MissileUpdateCtor (512 nonpadding bytes) and BezierProjectileBehaviorFriendNew
  (59) each lose their sole wrong-selected-constructor finding. The normal
  local link preview reports 1 -> 3 clean units and 143 -> 714 linked bytes:
  +571 existing bytes. This is a LEGACY local prediction with self-strict
  byte acceptance. New authored C++ bytes: zero. No closed-strict, executable
  placement or runtime gain is claimed; no maintainer-only runner was used.
- The constructor's 35 retained COMDATs differ only in that erase referent.
  All retained nondebug sections are identical after substituting that name,
  including bytes, data, directives, extents and other relocations. Three
  unused Coord3D begin/end/clear copies vanish; the two emitted carrier
  iterator copies exactly match the removed begin/end body digests and sizes.
  New-variant admission passes. The other three objects are byte-identical.
- Before/after EH: two graphs, EXACT both. Declared-definition, class, CSV,
  enforced data and converged-data checks pass (four sources, zero findings,
  zero second names). Placement resweep finds zero bodies or pins.

Remaining constructor blockers are Rva0029FB3BMember construction,
BehaviorModuleInterface::getBody, BezierProjectileBehavior::slot00 and the
UpdateModule vtable copy. The dependent consumers pass the legacy check;
this does not establish closed dependency closure through those blockers.

Dedicated reference review: donor pointer a7c38d3b2597121f178ab5190b3062478823257d
remains verified and unchanged. Reviewed upstream reconciliation
66b19a8e95a4add525ef808fcea088e306798e2b (Apt string-value allocation copies).
Its existing-provider principle applies, but no donor ABI/layout or source
is imported here. Official fetch found 86d49b09744d9dfb7896d0d1b6e621d3536f30d2.
Another worker owns file:reference/open-bfme-1, so comparative full verification
and the pointer update remain outstanding. No freshness stamp was written.

Scratch before objects, dependency receipts, source snapshot and proof script
are preserved in ignored build/bezier-erase-link-20261015. A trial retaining
Coord3D begin/end calls changed instruction ordering and was discarded;
the accepted carrier-view source is the verified version described above.
