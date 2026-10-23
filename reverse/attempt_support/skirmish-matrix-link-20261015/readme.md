# Skirmish AI matrix constructor emission repair

Base checkout: 4b7e7091c4dd659f6f123ec7f25cb75a1a178344. Paired index:
19a2565407, 2026-10-15 09:33, built from census 5986a99448. Its SHA256 is
recorded in object-proof.json. The discovery link_status.csv measurement
28269d8e8d is different and was used only to select work. No census index,
status/history, ledger, pin, baseline, header, ABI or compiler flags changed.

W3DDisplayDrawSkirmishAIStats.cpp emitted a surplus 93-byte
Matrix3D(const Vector3&) constructor, digest d7c133222ca1. The local constructor
delegated to Set, while the other two indexed copies have a 112-byte body,
digest 9ec9e58d0816. The ledger assigns the constructor at 0x0004563C to
Matrix3DO1Inlines.cpp. Retail-truth judges the surplus copy wrong; it reports
the two other copies unknown, not proven-retail. This repair does not promote
that unknown verdict or change either provider.

The two native debug-drawing call sites already inline all matrix stores.
Remove the local wrapper constructor and invoke the same Set body explicitly
on the trivial local matrix. Both call sites, including matrix setup, retain
every byte and relocation. This changes emission ownership, with no new
identity/layout inference. An initial dllimport/forceinline constructor trial
made MSVC emit calls and failed the byte gate; it was replaced with the direct
setter form, which passes without import annotations or other escape hatches.

Acceptance and measured result:

- The full 524-byte drawing row passes ./build.sh. Bounded strict preparation
  passes 2/2 rows across the consumer and the unchanged
  W3DShadowMapManagerTextureMatrix.cpp constructor witness, with six verified
  compiler float literals and no skipped literal/import references. The
  original consumer also passed strict preparation before editing.
- Complete COFF comparison removes exactly the unreferenced constructor
  section. All ten retained COMDAT bodies/extents/digests, every other
  nondebug section and symbolic relocation, and external strong/undefined/weak
  sets agree. No nondebug relocation targets the removed constructor. The
  witness object is byte-identical and retains the indexed 112-byte copy.
- Paired previews refresh only those two explicit strict-current objects in
  memory against the identical saved index on both sides. The consumer loses
  its sole COMDAT finding and becomes clean: LEGACY existing linked bytes
  0 -> 520, using upstream source-byte accounting. Authored C++ growth is zero.
  The provider witness's findings are identical before and after.
- Ordinary local link_check.py confirms the consumer LINKS; its combined
  invocation exits 1 because the unchanged witness still lacks
  Rva0007DA23ResourceManager::rva0007BB4B and CameraClass::rva00134A80 providers.
  These independent blockers were not attempted or hidden.
- Frozen definitions, class gate, converged-data, CSV and whitespace checks
  pass. EH has no applicable rows or missing objects. Placement resweep finds
  zero bodies and zero pins. Normal commit hooks also verify the staged source.
  Code-identity shadow still reports the existing divergent Vector3 copy
  constructor; the full-object proof establishes its body and bindings unchanged.

Strict reusable receipts establish the two checked objects' currency. The
canonical owner's cached object is not strict-current and was not compiled or
refreshed into this bounded comparison; its legacy digest is corroborated by
the current witness. This is a self-strict byte check plus a paired LEGACY link
preview gain. Closed-strict closure, actual link.exe placement, a fresh full
census and runtime verification remain unmeasured. No maintainer-only runner
was started.

The entire indexed constructor family contains just these three copies, with
this consumer the only wrong copy. No other same-cause losing copy remains in
that index. Other queue leads (HordeTransportContain construction, subobject
record destruction, river/transition record destruction and UV allocation)
remain available for separate repairs; no unchanged blocked body was retried.

Reference review: verified BFME1 gitlink/checkout
a7c38d3b2597121f178ab5190b3062478823257d, unchanged. Read donor repairs
4966496c5ae401ec877a044e1ae6dd04f9d9f65c and
6b9800e65dc6f0e7e4660ac55f27b44094f9e590: avoiding incidental wrappers and
private surplus COMDAT emission applies here. No donor layout or source body
was imported. Official master was fetched read-only, reaching f91e595b. Another
worker holds the reference-submodule claim. The previously documented
comparative full-gate freshness blocker (thousands of stale units/compiler
stalls) was not repeated, the verified pointer was retained, and no freshness
success stamp was written.

proof.py reproduces the object invariants and same-index paired findings from
the preserved source/object/receipt snapshots in
build/skirmish-matrix-link-20261015. Checked outputs and object-proof.json are
committed alongside this note. The witness was claimed for its bounded provider
check and released. The initial consumer claim was held by a peer: losing the
first command's captured output led to incorrectly continuing that investigation.
After the peer claim disappeared, an explicit consumer claim was obtained under
this seat and final verification repeated following a clean rebase onto
e2148e6666, with no overlapping source edit. Earlier exclusive ownership is not
asserted. All claims are released at handoff.
