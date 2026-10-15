Publication reconciliation

Before publication, refreshed origin/master revealed bc319bf138 had already
fixed this same particle blocker using the existing Matrix3 owner shim. The
alternative source change tested below was removed while rebasing. Production
source retains upstream's const helper and owner shim. This directory records
an independently verified alternative against the earlier stated baseline;
it claims zero incremental linked bytes beyond current origin/master. Its
proof.py requires the archived trial objects/context in build/, rather than
the now-current upstream implementation. No redundant mutable accessor copies
are added to the published source.

RenderObjectDrawModule matrix-accessor link repair

RenderRotationProduct receives two mutable local Matrix3 values. Use the
existing mutable row accessors for this read-only computation. This removes
the competing const Matrix3 subscript emitter without changing the expression,
class layout, matrix storage, compiler settings, dependency inputs or caller
behavior. No header, pin, alias, import, baseline or ledger row is added.

Target evidence remains Native 0x00562DDB..0x005634F7, RET 12, the vtable slot
at 0x0081C454 and WorldBuilder 0x01428210. The existing source distinguishes
those target facts from matrix definitions at verified BFME1 donor
a7c38d3b2597121f178ab5190b3062478823257d. This repair introduces no new target
identity or layout claim. A direct row-pointer trial changed SSE scheduling
and failed byte verification; that trial was discarded. The accepted change
uses the donor header's ordinary overloads and preserves the complete body.

Measurement: base checkout 7e5e6a945d37deaa71436f5290877ed78e04b26b;
runner index ac77c85054, 2026-10-15 14:25 UTC, hash in proof.json. Strictly
current original and repaired objects were separately refreshed into copies
of this same index. Exactly one const-accessor COMDAT conflict becomes zero;
no unresolved, duplicate, address or selected-definition finding appears.
Ordinary link_check.py changes 0/1 -> 1/1 clean and predicts 0 -> 1,816 existing
nonpadding authored bytes (the matched extent is 1,820). Census status and
history are unchanged. New authored C++ bytes: zero. This is a legacy local
preview, with a strictly current and fully byte-verified consumer; placed
self-strict gain and closed-strict closure are unmeasured.

All 20 retained COMDATs, including the full matched particle loop, have identical
bodies, extents and relocation digests. The removed 12-byte const Matrix3
accessor is replaced by an identical 12-byte mutable accessor, matching its
one existing census provider in U4RotateYMatrix3. The additional 10-byte mutable
Vector3 accessor matches all 33 census copies and retail's row at 0x007173D0.
No retained nondebug relocation targets any of these accessors. All remaining
nondebug sections, symbolic relocations, external/weak bindings and linker
directives are unchanged; the only extra section is that 10-byte Vector3 body.
No existing caller edge or data binding changes. These comparisons preserve
other consumers' definitions; the two new copies add no distinct body variant.
Their census compatibility does not assert current closed provider linkage.
Saved original/repaired objects, sources and receipts remain under ignored
build/particle-matrix-link-20261015; proof.py is the executable comparison.

Acceptance:
- Bounded link_check.py --prepare-current before and after: 1/1 complete row
  exact with strict reusable compiler receipts. Independent ./build.sh passes
  the full row, two float literals and all string/import reference checks.
- link_check.py normal preview: 1/1 clean. --new-variants passes.
- EH: neither side has EH data; zero nonexact or missing objects.
- Frozen-definition, class and converged-data checks pass. data_check --enforce:
  zero findings. Converged list: eight addresses, zero second names/unjudged.
- place_bodies.py: zero additional bodies or pins. CSV and whitespace checks
  pass. No full census, link cycle, nightly, boot or scheduler runner was run.

Discovery used repair_queue.py link and link_rank.py help/top/near/file, then
confirmed the blocker on a current object. The file and parent RVA were claimed
before editing. No per-row data-back artifact was available or ranking invented.
Reviewed BFME1 linking repair 66b19a8e95a4add525ef808fcea088e306798e2b: avoiding
surplus helper emission is applicable, but its imported-forceinline technique
and Apt identities are not used here. No donor code is imported by this change.
Official BFME1 master was fetched at 95eeb3bef370a7cd730b0ad5f228c317c8756e72.
Advancing verified donor inputs is still blocked by another seat's live
file:reference/open-bfme-1 claim and requires comparative full verification.
The verified gitlink and stale success stamp are unchanged; no successful
freshness update is claimed.
