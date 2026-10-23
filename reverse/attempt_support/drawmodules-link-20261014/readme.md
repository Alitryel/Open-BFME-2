# Drawable getter selection repair

Base checkout: 4bc654e647. Local census index: 147cfae2cb, 2026-10-14
07:27; index SHA256 is in object-proof.json. The committed link_status queue
measures 67e1365aa9 and is discovery evidence only. No census/index/status,
ledger, pin, header, baseline or data owner changes.

W3DDisplayGatherAnimationDebuggingInfo.cpp defined Drawable::getDrawModules
as a forwarding call to the address-derived getter at 0x002B224B. Its emitted
COMDAT was a call/return wrapper, digest b390a730c92d, judged wrong against
retail. The census selected this first copy over
DrawableSetFullyObscuredByShroud.cpp's retail getter, digest 05f12d929450.
That selection blocked four otherwise-clean consumers.

Replace the forwarding definition with a declaration and remove its unused
callee-view declaration. The debugger now calls Drawable::getDrawModules
at the same proven native address, with the same ABI and behavior. The
existing pin resolves it to the seven-byte +0x14C dword getter. Target basis:
the matched native debugger call at body offset 732, the existing 0x002B224B
getter row, and the already-byte-verified Shroud provider's inline getter.
No new target identity or layout is inferred from donor source.

Reference review: clean verified BFME 1 gitlink
23b143233b5a8664a3bdf8572df6d905c310a5a1; reviewed linking repairs
d2e21369067f2f2c762c1c7ec2792c75f1ecf53d (replace non-retail forwarding
constructors with declarations) and de59a7e9f891b3ed2d4221d151ca881f4b75a583
(reconcile competing private helper COMDATs). The former cause is applicable;
the donor-specific aliases/pins and latter's predicate rewrite are inapplicable.
No donor code was imported. Official master fetch resolves to a7c38d3b2;
file:reference/open-bfme-1 remains claimed by another worker. Preserve the last
verified inputs pending that worker's comparative full verification; no successful
freshness stamp was written.

Acceptance:

- Bounded link_check.py --prepare-current before/after on six explicit safe
  sources: 13/13 ordinary byte matches and strict reusable compiler receipts.
  All 27 string literals, 20 empty-string references and two floats verified;
  zero baseline/skipped string or import checks.
- All 64 retained debugger COMDAT raw bodies and sizes are identical.
  63 relocation digests are identical. The sole changed parent REL32 symbol
  at offset 732 still resolves to 0x002B224B; full ordinary byte verification
  validates that target. One surplus wrapper disappears and no copies are added.
  Strong/weak bindings stay equal; only the old undefined getter name changes
  to Drawable::getDrawModules. Snapshots/backups and proof script are under
  build/drawmodules-link-20261014.
- EH graph: 1/1 EXACT, including the renumbered native cleanup funclet.
- Frozen-source check, class gate, new-variants admission, whitespace check,
  converged-data check (eight addresses, zero second names/unjudged rows),
  shadow data check (zero findings) pass.
- Affected source placement resweep: zero bodies, zero pins.
- Same-index local legacy preview: six-unit cohort goes 0/6 -> 4/6 clean,
  LINKED 0 -> 2368 existing bytes (0xCC excluded):
  AnimationSoundClientBehavior 864, SubObjectsUpgrade 631,
  AnimatedParticleSysBoneClientUpdate 56, GeometryUpgrade 817.
  Getter provider still needs Drawable::onComingOutOfShroud; debugger retains
  TheAnimDebugModeNames/TheWeaponStatusNames unresolved and the competing
  Rva0004224C constructor. Removing the getter finding alone leaves those units
  blocked. Other census getter consumers retain independent blockers.

New authored bytes: zero. Self-strict object currency is proven for six units;
closed-strict dependency closure, actual link.exe placement and a fresh census
were not measured. No census build/measure/history, full link cycle, nightly,
boot runner or shadow publisher was started.
