# AODHordeContain math-wrapper ownership

Existing row 0x0047AC8F, 1,563-byte extent, has 1,560 nonpadding matched bytes.
At unchanged census index 5366c4f808 (hash and full starting context in proof.json),
its only blockers are the surplus MSVC cos(float) and sin(float) COMDATs.
Apply the verified StrafeAreaUpdate pattern (strafe-sin-link-20261013): restrict
`inline` to `static inline` only while including math.h, then undefine the macro.
MSVC's original definitions still provide the same visible inline behavior;
this unit no longer exports their competing wrappers. No shared header, compiler
flags, class view, address, row, pin, alias or runtime dependency changes.

Before and after previews: 0 -> 1,560 existing matched bytes, 0/1 -> 1/1 units.
Paired comparison uses original pre-edit strict object and final strict object,
replacing only this unit in memory. Every common COMDAT digest/length is
unchanged; strong, undefined and weak bindings are unchanged. The removed
COMDAT names are listed in proof.json. Normal byte gate: 1/1, 14 float literals,
zero string/import refs. Final --prepare-current grants a strict self receipt;
class gate, converged globals, undeclared functions and new-variants pass.
This is a legacy index preview with a self-strict object. Closed-strict closure,
new census measurement and executable placement remain unmeasured.

The refreshed BFME1 pointer and donor ownership review are recorded in
shared-node-allocator-link-20261020; no donor addresses or layouts are imported.
The updated broad index lists no other unit blocked solely by these math
wrappers. Remaining math-emitting units have independent unresolved blockers;
they were not modified for a zero linked-byte gain.

The preceding allocator commit's identity shadow reports existing list-push
binding concerns in the Bridge/Flood views and Coord3D helper divergence.
The allocator proof records all common helper digests unchanged except the
explicit AnimateWindow allocator call; these concerns are not claimed repaired
or as evidence of closed-strict closure. Normal byte and enforced gates pass.

Recovery reconciliation (2026-10-20): upstream 0def49709b independently repaired this unit using local aodSin/aodCos names. Kept that implementation unchanged when the publication rebase encountered the overlap. This recovered commit retains the independent paired evidence only; its historical +1,560 B is not an additional gain over 0def49709b. The old inline macro trial is not added on top of upstream.
