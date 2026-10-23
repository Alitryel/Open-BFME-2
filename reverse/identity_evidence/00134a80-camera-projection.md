# Camera projection/view helper at 0x00134A80

Native 0x00134A80..0x00134AB0 is a complete 48-byte nonvirtual member ending in RET 4. It calls CameraClass::Get_D3D_Projection_Matrix (0x001348C0), then Matrix4::Multiply (0x00715BC0), passing a 64-byte projection temporary and the receiver's Matrix3D at +0x3CC. WorldBuilder 0x009BD3A0 independently shows the same operation. The original member name is unknown.

The existing caller in W3DShadowMapManagerTextureMatrix.cpp and its existing symbol pin name the member rva00134A80. Preserve that spelling; the older standalone bank's capital-R spelling is not a second identity. The complete owning camera.cpp uses the existing CameraClass header and Matrix3D/Matrix4 declarations, including the established CameraInvTransform layout. No new pin, private class, compiler override or optimization pragma is needed.

Verification: the new body is exact 48/48; all 58 earlier owning-unit rows remain exact (59/59 total), 43 float references pass, and both EH graphs are EXACT. The emitted-body placement scan finds zero additional bodies or pins. The camera unit has 24 existing link diagnostics; comparison against the untouched source/header confirms the diagnostic list is identical. This recovery does not resolve those pre-existing linking issues.

The old standalone attempt was blocked by an unrelated TheDisplay DIR32 consistency error. Publication of this owning-unit integration uses the current unmodified full gate; no exception or baseline change is requested.
