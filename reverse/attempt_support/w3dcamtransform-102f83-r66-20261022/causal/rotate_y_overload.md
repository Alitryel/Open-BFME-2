# Final Rotate_Y source and compiler proof

Current isolated result: `cached.cpp`,4310B, fitness0.9222813862,57 resolved
relocations. The209-byte native region+F44..1015 matches candidate+F4F..1020
after relocating only the two calls. Both call destinations are independently
equal: sin RVA629216, cos RVA62920A. Post-call174B is raw exact and unique.
See `cached-region-proof.json` and the source-only delta `cached.patch`.
The whole camera function is not exact; unrelated earlier matrix keys changed.

The source uses the actual donor Matrix3D::Rotate_Y(float s,float c), copied
from the verified BFME1 matrix3d.h, and final-site angle/receiver captures plus
sequential real sine and cosine results. Native already captures the angle and
receiver before either call. The two-arg donor establishes the helper semantics;
the exact helper boundary in the retail source remains inferred.

The causal path is documented under ../rotate_y_order. The original reduced
helper's inline locals share a32-record local-symbol pool. In row_assignment,
sine fills its last record1855; cosine begins2176 because ten temporary pools
were allocated while that named-local pool remained active. All four values are
ordinary floats; their kind, origin and consecutive local ordinals agree.

A direct final Rotate_Y(sinf(angle),cosf(angle)) did not fix this: both math
wrapper __X formals remain live during argument lowering, consuming two reused
local slots. The resulting argument locals still straddle the boundary. It
emits4306B/.902207 with the same mixed sine-first/cosine-second operand order.

Sequential caller locals make both trig values ordinary earlier caller symbols
(532/533 in that isolated context), while the row values are later inline locals
(2180/2181). Their FactCanonSort keys both outrank the row-value keys, producing
the exact native SSE arithmetic and register allocation. That intermediate
`sequential.cpp` emits4297B/.930760; only receiver EAX vs ESI and angle-loading
setup differ in this region. Capturing the real angle and receiver before trig
calls restores the complete209-byte native region.

This is a structural explanation, not a requirement to reproduce those absolute
IDs. The exact key is0x10000|ROL16(Fold16(symbolID),5). Named caller results and
inline row locals occupy different symbol windows; canonical-header/name/context
changes can move them. Recheck final keys and the full native region after such
integration. No padding, unused locals, compiler flag changes, binary patching,
or production edits were used. Read-only diagnostic objects are separately
compared byte-for-byte and relocation-for-relocation with ordinary objects in
../rotate_y_order/overload-comparison.json and overload-cached-proof.json.
