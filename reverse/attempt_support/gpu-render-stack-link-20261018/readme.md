# GPU particle renderer linking repair

Bind the renderer's two native stack calls (0x001688FF and 0x00168952)
to RenderingMethodLinkArray.cpp's existing Rva001688FFShift and
Rva00168952Clear providers. Their target-established contract is an array
of four-byte owners and an integer count. Cast only the array view; keep
the provider's opaque runtime element identity. Existing W3DRoadBufferDrawRoads,
Rva000E473F and Rva0017438BPerformRendering callers use this same contract.

The visible force-inlined DX8Wrapper::Set_Transform view also emitted an
unreferenced standalone copy containing undefined BFME2Set_Device_Transform.
Import the visible member to retain its constant-world-transform inline
code while suppressing that incomplete standalone copy. Seven helpers used
only by that copy consequently disappear. The proof checks that no retained
non-debug section refers to any removed helper, and that all retained bytes,
flags and symbolic relocations are identical after the two call-name changes.
This suppression removes an unresolved reference; no credit is assigned to
removing an unreferenced differing COMDAT by itself. It adds one import hatch;
no hatch baseline was edited.

Paired replacement of only the renderer in the published c2c5ac8c27 census
predicts legacy LINKED 0 -> 787 non-padding retail bytes. Both ledger rows
(779B parent and 10B EH handler) pass the byte gate with strict reusable
receipts; literal, float, import, converged-data, class and undeclared-definition
checks pass. This is self-strict byte evidence and a legacy link prediction.
Closed-strict closure and a new census are not measured; authored C++ coverage
is unchanged. proof.py requires the local baseline object under
build/link-seat-20261018b/gpu-before; proof.json records the paired results
and object/index hashes.

The commit hook's shadow identity check still reports the pre-existing
divergent RefCountPtr<FXShader::RenderingMethod> copy constructor. The paired
object proof includes that retained helper unchanged; this repair does not
claim to resolve its separate identity diagnostic.
