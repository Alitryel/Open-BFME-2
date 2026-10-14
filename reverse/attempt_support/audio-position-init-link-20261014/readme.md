# Redundant audio-position initialization link repair

BFME2 base: 2e69cdffb3db1e6912fea7600255b7bcf0708932.
Local runner index: 147cfae2cb, 2026-10-14 07:27; SHA256 is in
object-proof.json. The committed repair queue measures 67e1365aa9 and was
used for discovery only. No census, status, history or data-back ranking
was generated or changed.

The two complete Rva0059E242 audio-update bodies at 0x0059DF60 (155 bytes)
and 0x0059DFFB (148 bytes) initialized a position to zero and then
unconditionally overwrote x, y and z before constructing the audio event.
Their incidental BfmeEventPositionView(float,float,float) SSE COMDATs lost
to the index's first same-name copy; the constructor has no retail address.

Default-construct the position and retain the existing complete XYZ stores.
No uninitialized coordinate is read: the header's empty default constructor
reads no fields, and every field is assigned before the event constructor.
Both full matched routines have identical raw bytes, extents, relocation
digests and dependencies before and after. The only ordinary object-section
change replaces each surplus float constructor with the empty three-byte
constructor 8bc1c3; this agrees with all eight existing indexed copies.
All other strong, undefined and weak bindings remain identical. No target
identity, layout, compiler setting, pin, alias, global or ledger row changes.

Acceptance:

- Bounded link_check.py --prepare-current before and after: strict reusable
  receipts current, normal byte gates 2/2 exact, zero baselined/skipped
  string, float or import checks. Separate ./build.sh also passes 2/2.
- Object comparison checks full retained bodies and relocation digests,
  all bindings and all nondebug sections (EH symbol indices normalized).
  Tracked object-proof.json records hashes; backups and reproducible proof.py
  stay under build/audio-position-init-link-20261014/.
- Same-index local legacy preview: 0/2 -> 2/2 clean; LINKED 0 -> 303 existing
  bytes (155 + 148). Both original losing constructor findings disappear.
- EH graph 2/2 EXACT; frozen-source, class, new-variant admission,
  converged-data (eight addresses, zero second names/unjudged rows), shadow
  data (zero findings), CSV and whitespace checks pass.
- Affected-source placement resweep: zero bodies, zero pins.

The same constructor finding appears in BfmeAudioEventOwnerPosition.cpp.
Its invalid-position return needs actual zero coordinates, so the redundant
initialization repair does not apply. It also depends on the still-unrowed
position worker at 0x003FA835; its recorded SSE return-register wall was
reviewed without another compile attempt. No claim was taken for that file.

Dedicated donor review reused the prior broad link scan and inspected
BFME1 d2e21369067f2f2c762c1c7ec2792c75f1ecf53d (remove incidental forwarding
constructor definitions) and de59a7e9f891b3ed2d4221d151ca881f4b75a583
(reconcile private helper copies). Their competing-copy repair principles
apply; their bodies, alias scaffolds, identities and layouts are unrelated.
No donor source was imported. The clean committed BFME1 checkout is
23b143233b5a8664a3bdf8572df6d905c310a5a1, verified by BFME2 pointer-update
commit 9b6bf3e581 (new-input full gate green, 88151/88151). This supersedes
older handoffs describing a pending update to that pointer. The ignored
success stamp predates this committed verification; official master fetch
now resolves to a7c38d3b2597121f178ab5190b3062478823257d. Existing verified
inputs were retained; no later pointer update or fresh full-gate result is
claimed by this session.

Authored C++ coverage grows by zero. The improvement is 303 existing bytes
unblocked in a local legacy preview. Strict receipts prove object currency
and byte verification; placed self-strict linkage, closed-strict dependency
closure and a fresh measured census remain unmeasured. No maintainer-only
link cycle, nightly, boot runner or shadow publisher was started.
