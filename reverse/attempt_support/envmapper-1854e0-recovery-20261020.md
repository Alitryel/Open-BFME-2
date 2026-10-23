# WSEnv mapper: 1174 exact C++ bytes in the approved home

Native 1854E0..185976, RET4. Existing constructor/vftable evidence identifies
WSEnvMapperClass slot +24; WB A361E0 independently confirms the operation and
the sixteen-float Matrix4 construction/Init interface. The implementation is
EA GeneralsMD mapper.cpp's body, unchanged apart from trailing whitespace.
The reference checkout used for discovery is BFME1
92f6bbe8e1dcdb46b5d27da0674313efc822b790; the ZH input is under that pinned
checkout's inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/ tree.

The actual headers of the now-exact GridWSEnv sibling close the old bank:
BFME2 Get_Transform (WORLD/VIEW/PROJECTION/default) and the Matrix4 Init16
view. Donor-verbatim source with those headers emits exactly 1174 bytes;
the old manually expanded bank with the same headers emits 1188. A previous
self-contained faithful model is not equivalent compiler input to the actual
headers; its earlier negative finding must not retire this reference path.
No assembly, volatile, barrier, inert padding or new pin is used.

The function remains in its approved mapper.cpp home. All seventy existing
rows remain exact. The whole-home test with Matrix4 included under the old
size-optimized math block instead gives 1201 bytes, so that was rejected.
The main caller needs its verified optimized inline context, while external
row-constructor and Transpose copies belong to the existing native providers.
The existing bfme_matrix4_rows_link/matrix4_zh_rows_link.h provides the
same sixteen-float interface and imported-forceinline declaration pattern.
BFME's existing Matrix3D/Matrix3 dependencies are included first, followed by
the established Matrix3x3/Matrix4x4 class-name mappings. The existing SSE
Vector4 link view suppresses its competing helper copies. No shared header
edit, new shim, or imported math call is needed. The final existing-header
control preserves the new 1174-byte body and all seventy previous rows.
The old vector-constructor iterator profile in mapper.cpp is retained.
Two obsolete virtual fallback aliases are removed
now that both environment virtuals have real providers.

The shared Matrix4 Init16 header is unchanged. Applying the same targeted
row-constructor suppression to GridWSEnv fails its byte gate, so that trial was reverted in
full. Its 1166-byte row still verifies. Its four pre-existing math COMDAT
blockers remain separate work; this recovery does not claim to repair them.

Acceptance before commit: ordinary full-byte/ref gates pass 75/75 rows across
mapper.cpp, GridWSEnvMapperCalculate.cpp and GridTextureMapperCalculate.cpp.
Strict prepare-current receipts were obtained for all three. The paired
current-object preview reports mapper.cpp LINKS with 6958 nonpadding bytes
and GridTextureMapperCalculate.cpp LINKS with 525. Its overall exit is 1
because the unchanged GridWSEnv sibling retains its four recorded blockers.
The mapper's sole Get_Transform diagnostic is unreferenced and not a blocker.
The census's zero for mapper.cpp is stale: the preceding duplicate repair
was already upstream. This change adds 1174 unique C++ bytes, not 6958.

Replay the normal build and prepare-current on those three explicit paths,
then pass all three paths to one link_check preview. Preparation proves the
objects current; a one-file preview still sees the other census-era copies.
No census, link_cycle, nightly runner or publisher was run. All trials used
normal explain_mismatch/build entry points and isolated build/ objects;
read-only compile_function comparisons never compiled or replaced an object.
Transient controls are in build/envmapper-family-oct20/ and
build/envmapper-home-oct20/ and build/envmapper-next-controls-oct20/.
The bank is retired by verified add_match.
