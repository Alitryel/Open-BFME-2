# Drawable shroud module-array getter repair

DrawableSetFullyObscuredByShroud.cpp now reads its existing m_drawModules
member directly. The matched loop already inlined this +0x14C read, but its
private accessor also emitted an unused seven-byte getDrawModules COMDAT.
Removing that definition removes this consumer's dependence on the conflicting
selected definition. No class layout, compiler flag, pin, import, alias or
ledger row changes.

Base checkout: 7cb7d6830c35cd758729163aacb18d31dd9ae5db.
The unchanged runner index measures 28269d8e8d, 2026-10-15 09:31 UTC;
measurement.json records its SHA256. Before and after objects have strict
reusable compilation receipts. proof.json records source, object and receipt
hashes and the paired check_object results, refreshing each object separately
into copies of that same index.

The only removed section is the unused getter, 8b814c010000c3. The retained
caller COMDAT is identical in bytes, extent and relocation digest. Every other
nondebug section, symbolic relocation destination, external binding and link
directive is identical. No incoming relocation in the retained object targets
the getter. Saved source/object/receipt snapshots and the comparison script
remain under ignored build/drawable-shroud-getter-link-20261015.

The paired local legacy preview removes exactly the selected-body finding
for getDrawModules. The unresolved onComingOutOfShroud remains unchanged.
New authored bytes and newly linked bytes are both zero. Current self-strict
receipts establish the body gate; neither closed-strict closure nor a placed
self-strict gain is claimed. The census, index and link_status are untouched.

Target evidence is the unchanged complete 66-byte native body at
0x00278C29..0x00278C6B, the established module array at +0x14C and flag at
+0x440, and its existing byte-verified call relationships. The prior recovery
uses ZH Drawable::setFullyObscuredByShroud as its semantic guide; this repair
adds no target layout or identity claim.

Donor review: BFME 1 c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 removes unused
DamageInfo constructor copies, extending the imported-inline technique of
53d32d6b. Its general unused-emitter repair is applicable; its DamageInfo ABI,
layout and retail address are inapplicable here. Direct member access is the
smaller BFME 2 repair, preserving the existing target layout and caller bytes.
The six-consumer Player side repair and AIFollowPathStateMethods supply local
precedents for removing unused accessors while preserving matched callers.

BFME 1 upstream master was fetched as 86d49b09. The clean retained checkout
and gitlink stay a7c38d3b2597121f178ab5190b3062478823257d; their update is held
by another live seat (codex-6bc6-20261008). No pointer, checkout or successful
freshness stamp was changed. Comparative full verification of that update
remains outstanding.

Acceptance:

- check_csv passes; source is tracked; frozen-file and class gates pass.
- Before and after link_check --prepare-current: one current strict reusable
  receipt, complete 1/1 byte gate; string/float/import checks pass.
- ./build.sh: complete matched caller exact. EH verifier reports zero
  EH-bearing rows, missing objects or nonexact rows.
- Ordinary link_check reports only the unchanged unresolved shroud callback;
  --new-variants passes. Paired findings decrease from two to one.
- Enforced data check: zero findings. Converged data check: eight addresses,
  zero second names or unjudged rows.
- place_bodies: zero additional bodies or pins. git diff --check passes.

No census build/measure/history, full link cycle, nightly or boot runner was
started. A separate supported recovery of onComingOutOfShroud is still needed
before this unit can link. Other getter consumers were inspected; their
out-of-line retail calls or already repaired sources do not support applying
this direct-field change without further independent evidence.
