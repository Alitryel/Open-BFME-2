# POD deque slow-path binding

At census b711de3634 (2026-10-23 14:28),
`stlport_pod_deque_bodies.cpp` has 244 unique matched bytes and does not
link. Its only blocking name is the private
`deque<BfmePod16>::_M_push_back_aux_v` definition. That definition is not
retail's string-aware implementation.

Target evidence: native push_back at 0x0041AB95 calls 0x0041A9E8 on the
same receiver. The complete 135-byte slow path is already recovered as
`Rva0041A9E8::rva0041A9E8(const BfmeNarrowRecord0041A617 &)`. Its native
copy and construction calls establish the record view. The POD name
still records only the established 16-byte extent; this change makes no
new claim about its original class name.

An inline specialization forwards the slow call to that existing row,
preserving its receiver, reference argument, and native call target. It
removes the competing POD implementation. No pins or aliases are added.

Checks: before and after use current objects against the same published
index. The unit changes from 0 to 244 linked bytes in the legacy scoped
preview. All seven matched bodies and string/float/import checks pass;
`find_declared_unmatched.py` accepts every definition. Strict reusable
receipts are prepared separately. A paired current-object preview also
accepts the unchanged 135-byte slow-path provider: together 135 -> 379
linked bytes. Historical string-cleanup blocker records therefore do not
describe that provider's current legacy preview. No closed-strict link
gain is claimed. The index contains no other blocked consumer of the
removed POD helper.

Recovery reconciliation: upstream 3c44410e40 independently landed the same
binding before this checkout's saved 34ff2a4a1c could publish. Retain the
upstream source unchanged. The +244 B above is the original saved measurement,
not a new gain over recovery's origin/master. Preserve this independent evidence
and the associated blocked STL investigation records for handoff.
