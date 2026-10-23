AI state invalid-position setter emission repair

AIStatesBfmeOnExit.cpp marks its existing Locomotor::setAllowInvalidPosition
inline definition imported and forceinline, matching AIStatesSmallUpdates,
AIEnterStateOnEnter, AIEnterStateOnExit and AIStatesDerivedOnExit. The inline
flag operations are unchanged: member +0x44, bit 1. No new import reference,
external dependency, pin, alias, header, compiler option or ledger row is added.
The source no longer emits an unused 20-byte external COMDAT whose body
conflicts with the first census copy. This removes one diagnosed link blocker.

Target evidence: complete byte verification of AIEnterAndAttackState::onEnter
at 0x0034FD0D (259 bytes) and AIMoveToPositionAndDieState::update at
0x003513C9 (214 bytes) preserves their inline flag updates and ABI. The
existing state identities are grounded in named target vtables, with ZH/BFME1
semantics retained in source/ledger evidence. This repair asserts no new
standalone setter identity or class-layout fact from the donor.

Measurement: base checkout 3ee061a31f082cc5429133df904fcb16e95b6359;
runner index commit 4b7e7091c4, 2026-10-15 12:36 UTC. measurement.json records
its SHA256. proof.json compares original and repaired objects independently
refreshed into copies of that identical index. Exactly one COMDAT finding is
removed (six findings become five), with no added finding. All 97 retained
COMDAT bodies, extents and relocation digests remain identical. Every other
nondebug section, symbolic relocation destination, external binding, weak
external and linker directive stays identical; SafeSEH indices compare by
symbol name. No retained nondebug relocation targets the removed setter.
The original source/object/strict receipt and executable proof.py remain in
ignored build/ai-bfme-invalid-link-20261015.

Acceptance:
- ./build.sh: 26/26 complete rows exact, five string literals and 18 compiler
  float literals verified, no named imports or skipped/baselined references.
- Bounded link_check.py --prepare-current passes before and after with a
  strictly current reusable compiler receipt. EH verifier: zero EH-bearing
  rows, zero nonexact/baselined/missing objects.
- Ordinary local link_check.py reports the five remaining findings:
  unresolved Pathfinder::Rva002F1BA2, AIChargeTargetState::rva003468F5,
  AIChargeTargetState::rva0034BFFF, WeaponTemplate::rva0049CB57 and the
  pre-existing nonretail Coord3D::scale COMDAT. It exits 1 as expected.
- Frozen-definition and class checks pass; new-variants admission passes.
  Enforced data check retains one baselined finding and has zero findings
  outside baseline; converged-data check: eight addresses, zero second names
  or unjudged rows. Retained sections/relocations prove data bindings unchanged.
- place_bodies.py finds zero additional bodies and zero pins. Ledger and
  whitespace checks pass.

The file holds 5,952 existing nonpadding authored bytes, but still does not
link. New authored C++ bytes and LEGACY predicted linked-byte gain are zero.
Strict compilation currency and complete body verification are measured;
placed self-strict gain and closed-strict linkage are unmeasured. The index,
link_status and census history are unchanged. No full link cycle, census,
nightly, boot or scheduler runner was started.

Cohort review: the four census setter consumers are AIStatesBfmeOnExit,
AIStatesSmallUpdates, DeliverPayloadAIUpdate and SpectreGunshipUpdate. The
small-updates unit already has the repair. The latter two include shared GameLogic/Locomotor.h shim headers rather
than defining the local setter. Their getters bfmeDeliverPayloadLoco and
bfmeSpectreLoco return Locomotor pointers; a shared-shim emitter repair
requires its own dependency scope and full byte gate. It is not performed
under this file claim. The paired
COFF proof shows this emission-only change adds no caller or provider
relationship, and all other consumers/providers stay unchanged. No unresolved
callee or Coord3D reconstruction was retried.

Donor review: retained clean verified BFME1 gitlink/checkout
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed upstream patch and
verification message 66b19a8e95a4add525ef808fcea088e306798e2b: imported
forceinline removes surplus allocator copies without new imports. The emitter
technique applies; Apt identities, target addresses, ABI and layouts do not.
Local matched AI siblings establish this same setter spelling. The official
master fetched during initial pull is 3a5eb7a2; file:reference/open-bfme-1 is
still claimed by codex-6bc6-20261008. Retain verified inputs; no pointer advance
or freshness stamp is claimed. Comparative full-byte verification and affected
donor refresh remain outstanding for that update.
