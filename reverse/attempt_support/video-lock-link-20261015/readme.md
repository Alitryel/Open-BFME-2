# Video-buffer device-lock binding repair

Base: `1041f1635f76708c383e0522e0d092ea6b29df3d`. Frozen runner census:
`ac77c85054`, 2026-10-15 14:25 UTC. Its SHA256 and all 57 indexed guard
constructor copies are recorded in `proof.json`. Index, census status and
history are unchanged.

The video-buffer factory's private `BFMEDX8DeviceLock` constructor referenced
`W3DRadarResetLock`, the legacy pin for 0x0011F520. That address already has
the matched `BFME_DX8_Thread_Lock` provider. Declare and call the provider
instead. Both pins resolve to the same native lock body; the complete factory
and its native EH graph independently establish the call and guard lifetime.
The constructor's new digest matches all 56 other indexed copies. No new
identity, ABI, layout, flags, pin, alias or import is introduced.

The before object and source are preserved under ignored
`build/video-lock-link-20261015/before`. Both before and after have strict
reusable receipts. The ignored `proof.py` compares every retained nondebug
section's complete bytes, size, flags, symbolic relocations and external
bindings, normalizing only the old lock name to its existing provider.
They are identical. Linker directives are unchanged. Only the constructor and
the factory COMDAT digests change, through that relocation name; their whole
machine-code bytes remain identical. There is no helper suppression or new
body. Source/object/receipt hashes and unchanged provider witnesses are recorded.

Paired previews refresh the owned consumer and two strict-current provider
witnesses into independent in-memory copies of the same frozen index. The
consumer's sole COMDAT finding disappears; the witnesses retain zero findings.
Ordinary `link_check.py` on all three sources reports 3/3 LINKS and legacy
local LINKED 330 -> 588 bytes, a 258-byte improvement. The factory contributes
248 bytes and its rowed EH handler 10; the generated cleanup is excluded.
Consumer currency and the two witnesses are strict; the wider provider closure
is legacy. No closed-strict, whole-game placement or runtime gain is claimed.
Authored C++ growth is zero, and the committed census totals are unchanged.

Acceptance (`checks.json`): complete byte gate 10/10 across the consumer,
BfmeDX8ThreadLock.cpp and BfmeStrVM0Rva0025C4A4.cpp; one string and six named
imports verified; EH 1 EXACT with no missing objects; class, declarations,
new variants, ledger and whitespace pass. Placement resweep finds zero bodies
or pins. Enforced data check passes with its existing baselined wrong-name
finding for `TheW3DRadarFormatCaps` at 0x009EDA7C unchanged before/after;
converged data has zero second names or unjudged rows at eight addresses.
That data binding remains separate debt.

Shared-cause sweep: this is the only divergent constructor among the 57
indexed copies. A bounded source search also finds the legacy spelling in
Render2DSentenceDestructorBFME2.cpp's differently named guard, plus unused
declarations in W3DRadar.cpp and dx8indexbuffer.cpp. Those do not produce this
constructor conflict; no other repair is claimed. The existing provider's
legacy /alternatename and shared pins are retained for their other consumers.
File and factory RVA were claimed before editing.

Donor review: verified BFME1 `a7c38d3b2597121f178ab5190b3062478823257d` still
uses the old spelling in W3DDisplayCreate.cpp; its private guard has a different
name and does not supply a ready-made version of this repair. Reviewed donor
link repairs `53d32d6b` and `66b19a8e`: inline suppression is inapplicable here
because the existing target provider binding reconciles all copies directly.
BFME2's native call, existing provider and whole-object comparison establish
the adaptation independently; donor semantics are provenance, not target proof.

Official BFME1 master was fetched, reaching `8fd28602` during this session.
The clean verified checkout/pointer was preserved. At startup another worker
held `file:reference/open-bfme-1`; its lease was absent at the final probe.
Comparative full-gate verification of the newer pointer remains outstanding;
no update or freshness-success stamp is claimed. No full census, full link
cycle, nightly, boot or scheduler runner was started.

Reproduce: strictly prepare the three named sources at the base, save the
consumer's source/object/receipt, apply the patch, and prepare again. Compare
complete nondebug object facts modulo the one documented name and refresh
only these three objects into paired copies of the recorded census index.
Run the normal byte gate, EH/data/class/declaration/variant/placement checks
listed in checks.json and the prescribed three-source local link check.
