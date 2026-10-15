# ParticleSystemID range-erase link repair

Source base: d14c2d564bab19b9f4cc0ed82e00067723dec946. The runner index
measures 19a2565407, 2026-10-15 09:33 UTC (underlying census 5986a99448,
04:52). The committed older link_status.csv served discovery only.
object-proof.json records the unchanged index hash, strict-current objects,
paired same-index local previews, and remaining findings. No census, status,
history, index, baseline, pin, ledger, class or shared header was changed.

BoneFXUpdate.cpp and Rva0040DB52Ctor.cpp each emitted a 41-byte vector
ParticleSystemID range erase, rejected against retail's 38-byte body at
0x00532803. Each now declares that specialization without defining it,
reusing the existing external provider. Their calls were already out of line.
The dedicated BoneFXUpdate_eraseParticleSystemID.cpp provider is independently
byte-verified and unchanged. SkirmishAIManagerReset also has a retail copy
in the index. There are no other losing emitters of this specialization in
that measurement after these two repairs. All three files were claimed.

Target evidence is the existing matched rows and their unchanged call-site
relocations to the provider. The enum and erase semantics come from the
existing source; no new identity or layout inference is made. Compiler
receipts resolve vendor/stlport/stl/_vector.h and _vector.c, and the
BoneFXUpdate header under BFME1's inputs/reference/CnC_Generals_Zero_Hour/
GeneralsMD/Code/GameEngine/Include/GameLogic/Module, rather than silently
substituting a missing old-layout include directory.

BFME1 linking repairs reviewed at verified donor
 a7c38d3b2597121f178ab5190b3062478823257d:
6b9800e65 (surplus VictorySystem emitter) supports the incidental-emitter
mechanism, but its class repair has no direct BFME2 counterpart;
f906985e4 and 6cf837364 (BoneFXDamage/Update name-key fixes) are already
inherited by these BFME2 bodies; 94f453a51 (vector helper repair) imports
BFME2's own 5fbd298178 and provides no new target change. Existing BFME2
NATUpdateBfme.cpp has a declaration-only erase-specialization precedent.
Official BFME1 master was fetched at
9bbab7963c3dac0ef8da8c46860e972ecbafe29d. The overdue comparative full-gate
pointer update remains under another worker's file:reference/open-bfme-1
claim. Clean verified inputs and the previous success stamp are retained;
no successful freshness update is claimed.

Acceptance:

- Ordinary ./build.sh and bounded link_check.py --prepare-current pass
  for both consumers and the provider: nine complete matched rows across
  three units, two literals verified, no skipped or baselined references.
  All three have strict reusable self receipts. No LINK closure is inferred.
- Each consumer loses the rejected erase and six now-unused helper COMDATs.
  All 560 and 24 retained COMDATs respectively keep raw bodies, extents,
  normalized relocations, digests and verdicts. Ordinary sections/directives,
  strong definitions and weak bindings are unchanged. The sole new undefined
  name is the existing erase provider. The provider's eight COMDATs and entire
  object are unchanged. One removed helper itself has retail verdict: its
  declaration is not rowed here and no undefined reference to it is introduced.
- Same-index paired legacy preview: BoneFXUpdate findings 3 -> 2 and
  Rva0040DB52Ctor findings 12 -> 11, no added finding. Ordinary link_check
  agrees; it returns 1 for each consumer's remaining independent blockers.
  Provider LINKS remains 38 -> 38 bytes. New-variant admission passes.
- Declared-definition, class, converged-data (eight addresses, no second
  names or unjudged rows), EH (one exact row, no debt), CSV and whitespace
  checks pass. Shadow data still reports the same pre-existing static-guard
  wrong-name at 0x00A038C4 in BoneFXUpdate::onObjectCreated; saved before/after
  objects give identical findings. Rva0040DB52Ctor has no data finding.
- place_bodies.py rescans both changed units: zero new bodies or pins.

Authored C++ gain +0. Legacy LINKED stays 0 -> 0 for both consumers; no
closed-strict, measured census or actual link.exe placement gain is claimed.
BoneFXUpdate retains unresolved UpdateModule::crc and a wrong selected
NAMEKEY definition. Rva0040DB52Ctor retains eleven unrelated vector,
Snapshot and vtable/provider conflicts, listed in object-proof.json.
These need separate provider/class evidence, not repeated erase work.
Broader verification remains with the maintainer runner; no full census,
link cycle, nightly or boot operation was started. Reproducible paired
source/object/receipt snapshots and proof script are under
build/bonefx-erase-link-20261015. Unrelated untracked work is preserved.
