# Camera overlap Vector3 linkage, 2026-10-18

Current-object link_check against published retail-truth-2 census c2c5ac8c27
(2026-10-18 11:36) changes Rva0007BEDAOverlap.cpp from 0/1 units and 0 bytes
linked to 1/1 and 128 bytes. This is +128 legacy LINKED bytes, no new authored
bytes, and no closed-strict claim.

The native 128-byte camera-plane scan already establishes the component
subtraction and the Vector3 helper identity. Import the existing Vector3 class
before its donor header, retaining inlined arithmetic while suppressing the
non-retail external Subtract COMDAT. Existing providers remain unchanged.
This extends the established Vector3 consumer pattern in layer.cpp; it adds no
new class view or copied implementation.

Acceptance: build.sh 1/1 whole-body byte and relocation match; link_check
--prepare-current verifies the explicit source with strict reusable receipts;
current-object link_check links 128 bytes. Class gate, frozen-definition check,
data enforcement, converged data ownership, EH verification and diff checks pass.
No shared headers, pins, baselines or verification tools changed.

The BFME 1 linking-repair pass reviewed upstream through c3847f08 (including
UnicodeString repair 95ca17f1). The verified committed donor stays 64d369b9;
another seat owns the submodule freshness update, so this repair does not change
the pointer or certify its freshness. The applicable source guide is the
existing BFME 2 Vector3 consumer repair, confirmed independently by retail bytes.

The accompanying GDI+ blocked-attempt record contributes no linked-byte gain:
member import preserved all three Bitmap rows but did not suppress Image's
competing deleting destructor. Sources were restored and all four claims released.
