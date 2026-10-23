# Giant-bird guard call bindings, 2026-10-13

BFME 2 base: `08e91a25b0b93d2cfb57e128d0fb4ad5db83bb57`.
The local census index measures `cb660e4d97`, 2026-10-13 04:02 UTC,
SHA-256 `4bc4fd38c27a025c8545b51f02fd25445391b93e51e964dfb8077a45aea9244e`.
The committed repair queue measures a different commit, `67e1365aa9`;
it supplied leads only. No per-row data-back ranking was manufactured.
Neither census index nor status was changed.

## Target evidence

The complete 239-byte guard tick at `0x0036A88A` has direct REL32
destinations `0x00369217`, `0x00369064` and `0x0036914D`, independently
computed from retail displacements at body offsets 214, 221 and 230.
The corresponding already matched owners are
GiantBirdNormalFlightState::onExit, ::onEnter and ::update. Their native
vtable/name and donor evidence is recorded in their existing ledger rows.
The argument at the exit call is zero; the receiver is unchanged at all
three calls. The two update paths converge on the same emitted call site.

The consumer formerly named those calls as undefined members of
Rva0036A88AOwner. Its declaration-only call view now uses the existing
provider signatures, including their enum types and virtual mangling.
Explicit qualification emits direct calls. No virtual slot or class layout
is inferred from that view. The guard owner's identity and field view stay
address-derived. Provider implementations, compiler settings, ledger rows,
pins, extents and baselines are unchanged.

objects-before.json and objects-after.json capture strict-current objects
for the guard consumer, GiantBirdStateSlots.cpp,
GiantBirdNormalFlightStates.cpp and TeamDidPartialEnter.cpp. They establish
identical complete consumer body bytes with exactly the three relocation
names changed. All three complete provider objects are unchanged. The
ordinary byte gate verifies the resulting native destinations as well.

## Local acceptance

- Ordinary consumer gate: 1/1 exact, no skipped references.
- Bounded before/after `link_check.py --prepare-current` on those four
  explicit sources: 19/19 exact, six compiler literals, no skipped or
  baselined references; all four objects have strict reusable receipts.
  This is self-strict preparation, not closed-strict link closure.
- The same four-source legacy preview changes from 2/4 to 3/4 clean
  units, 1,985 to 2,224 existing authored bytes: **+239 local predicted
  linked bytes**. The repaired consumer reports LINKS. Both previews exit
  1 because the normal-flight enter/update provider retains two independent
  COMDAT losers (StateMachine::isInIdleState and ::getGoalPosition) and
  wrong-selected AIUpdateInterface::getNextMoodTarget.
- The census baseline printed by both previews is 1,818 bytes. The extra
  167 bytes already present in both current previews belong to the newer
  TeamDidPartialEnter.cpp provider; they are not credited to this repair.
- Converged-data check: four sources, eight addresses, zero second names
  or unjudged rows. Consumer data audit: zero findings.
- Ledger, declared-definition and diff checks pass. The affected consumer
  placement rescan reports zero bodies and zero pins. A source sweep finds
  no other remaining uses of these three opaque call spellings.

No full link.exe cycle, maintained census, nightly or boot runner was
started. No maintained or closed-strict linking gain is claimed. New
authored C++ coverage is zero.

## Donor review and reference freshness

Retained clean BFME 1 checkout/gitlink:
`cee35b7d8ca077d7255f1c39cb69e9fd9627aa85`.
Official freshness fetch reached
`11ecc89cfdb0e0253e48595230c168bddac08309`.
Reviewed donor repair `4b5d71a18c76439243dc5c641bdcc7890177c863`:
replace an unsupported private call name with the independently matched
clear owner. Its call-binding principle is applicable; its addresses,
classes, implementation and layout are inapplicable and were not imported.
This repair uses BFME 2's own branch destinations and existing providers.

The reference pointer update remains outstanding. Prior comparative
verification was interrupted at the shared compiler lock, documented in
../record-assignment-link-20261013/readme.md. The previous verified inputs
and last-check stamp are preserved. This session neither substitutes
unverified upstream headers nor marks freshness successful. Comparative
gates and affected donor sweeps need the separate reference-update pass.

## Deferred lead

DynamicAutoResolveDialog's ClosingStateHandler::Startup at `0x005EA46F`
still refers to Rva005FC19E::rva005FC1A6. Retail's final REL32 at offset 137
reaches the newly rowed Rva005FC1A6::rva005FC1A6 at `0x005FC1A6` on the same
receiver. Bounded strict preparation of the consumer and the `005FC1A6`
and `005FC02A` providers passed 18/18, but the census predates `005FC1A6`.
The prescribed preview refuses that absent provider (captured in
deferred-autoresolve-link.txt). No source trial was made. The blocker was
recorded with re_log.py and all four claims released. Revisit when the
census includes that provider; do not repeat the unchanged preview.

MapCacheWriteCacheINI's concat lead was also reviewed against the existing
concat-team-map-base-link-20261013 evidence. Its unchanged compiler-shape
blocker remains; no trial was repeated and its file claim was released.
