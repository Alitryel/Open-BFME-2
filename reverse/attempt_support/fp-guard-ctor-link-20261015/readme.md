# FP-mode guard constructor link repair, 2026-10-15

W3DDisplayGatherAnimationDebuggingInfo.cpp and LivingWorldEyeTowerXfer.cpp
emitted 12-byte forwarding constructors for Rva0004224C. The existing
constructor pin at RVA 0x0004224C and three other units identify a complete
22-byte constructor there. Both consumers now use that constructor body
instead of forwarding to the address-derived method.

The constructor remains visible and noinline: its unused receiver allows the
empty guard local to share the caller's existing frame slot. Declaring an
opaque constructor would lose that information. The display-debug unit keeps
its separately rowed rva0004224C method as an out-of-class definition, with
identical bytes and relocations; the unused inline copy disappears from the
eye-tower object. No ledger rows, pins, headers, class layouts or flags change.

## Verification and paired evidence

Work starts at BFME 2 18fb817571; both edited files were claimed. All three
explicit objects, including unchanged Rva0042CB81.cpp, have strict reusable
current receipts and pass the ordinary byte gates before and after (14/14
rows). The final constructors equal the unchanged provider's entire body and
every relocation, digest ae7c2d5e36a9. All other retained COMDATs are identical
except the caller relocation spelling from the method to the constructor;
both caller byte sequences and full EH graphs remain exact.

object-proof.json records source/object/receipt hashes, the constructor bodies,
relocations, and paired findings. Both sides refresh only those three explicit
objects into the same frozen index, SHA256 recorded in the proof:

- index commit 19a2565407, 2026-10-15 09:33;
- underlying census commit 5986a99448, 2026-10-15 04:52.

Exactly five local findings disappear: two wrong constructor copies and three
wrong-selected dependencies. None are added. In this paired legacy preview,
LivingWorldEyeTowerXfer becomes clean (229 non-padding matched bytes), as does
Rva0042CB81 (2,337 bytes), for LINKED 0 -> 2,566 bytes. The display-debug unit
retains unresolved TheAnimDebugModeNames and TheWeaponStatusNames arrays.
This is a local prediction, not a new census measurement. The explicit objects
are self-strict; unrelated census providers are not collectively proven current,
so closed-strict gain is unmeasured. Authored C++ byte gain is zero.

Acceptance checks:

- link_check.py --prepare-current on both edits and Rva0042CB81.cpp: 14/14,
  27 literals plus 19 empty-string references, seven float literals, no skips.
- eh_verify.py on both edits: EXACT 2/2, zero baselined parents.
- data_check.py on both edits: zero findings; --converged: eight addresses,
  zero second names or unjudged rows.
- find_declared_unmatched.py and class_gate.py on both edits: pass.
- link_check.py --new-variants on both edits: pass.
- Normal local link_check.py on all three: 2/3 clean, 0 -> 2,566 bytes;
  exit 1 only for the display-debug unit's two unchanged unresolved arrays.
- Assertion proof: two wrong12B -> retail22B, five findings removed, none added,
  unchanged provider, only the expected caller relocation renames.
- place_bodies.py on both edits: zero bodies, zero pins.
- check_csv.py, git diff --check and normal commit hooks: pass.
- Hook shadow reports retain the unchanged getContain code-identity finding
  and existing g_Va00DE1CAC address-global debt; neither is changed by this fix.

Before/after sources, objects, strict receipts, snapshots and assertion script
remain under ignored build/fp-guard-ctor-link-20261015/. No census, index,
link-status or measurement artifact was rewritten; no full link cycle was run.

## Donor review and remaining scope

Reviewed verified BFME 1 a7c38d3b2597121f178ab5190b3062478823257d,
constructor-emission repair d3f9000fe08615a100e844adfff57fa4a39cd615 and
COMDAT reconciliation de59a7e9f891b3ed2d4221d151ca881f4b75a583.
The supported principle is to reconcile copies to the existing complete body.
TileData's declaration-only technique is inapplicable here because the guard
body must remain visible for frame reuse. No donor body, layout or identity
was imported; BFME 2's existing pin, owned method and retail-equal constructor
copies establish this repair. Original class spelling remains unknown.

The same-cause search found the other constructor definitions in GameLogicInit,
LivingWorldLogic and Rva0042CB81 already use the complete direct body.
The destructor view only declares the constructor; the load-game view uses an
existing forceinline/dllimport wrapper and emits no constructor in this index.
No additional edit is needed for this constructor family.

Official BFME 1 master was fetched (e27a65cb6); freshness migration remains held
by another worker's file:reference/open-bfme-1 claim. The verified gitlink and
old success stamp are preserved; the update is not marked successful.

Model: gpt-6.1-sol.
