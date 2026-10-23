# Existing MatrixInverse import link repair

The existing six-byte C++ forwarding body referred to an undefined placeholder
global, `g_D3DXMatrixInverseImport`. VS2003 `__identifier` now spells the real
`__imp__D3DXMatrixInverse@12` pointer supplied by the import library. The public
stdcall entry and existing opaque pointer arguments remain unchanged.

All six bytes and the relocation target match retail. The independent PE slot
names d3dx9_27.dll!D3DXMatrixInverse. A non-executed focused DLL links the actual
production object against an IAT-only import library with exactly that export,
no test double and no substitute global. No pins, aliases or data definitions
are added. This repairs linking; the body was already C++ and earns zero new
coverage bytes. Full-game placement and runtime behavior are not asserted.
