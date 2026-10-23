# Typed native import forwarding

The complete 26-entry D3DX assembly unit can be expressed as ordinary typed C++.
The VS2003 `__identifier` extension accepts the genuine decorated import-pointer
name containing `@`; C linkage supplies the usual leading underscore, giving
exactly the COFF `__imp__D3DXName@N` that the linker import library provides.
The function body calls that pointer with the public SDK arguments unchanged.
There is no runtime string, assembly, raw byte emission, symbol alias, pin or
substitute IAT datum. The linked DLL loader supplies the real imported pointer.

All 26 complete six-byte bodies match retail. Each DIR32 names its actual
import pointer; the independent import checker requires the corresponding
retail PE slot to name the expected D3DX export in d3dx9_27.dll. Public Microsoft
SDK documentation establishes argument types and order; native stdcall names
and 32-bit size checks independently agree on argument bytes. Only pointers to
COM/math/record types are forwarded, so no unproved object layout is defined.
CreateEffectFromFileA uses the ANSI signature selected by the retail export.

The current profile /O2 /G7 /Oy /Ob1 /MD is verified. The ordinary region
/O1 /arch:SSE /G7 expands float arguments through x87 loads/stores and fails
the six-byte scaling row. The official flag_defaults propose tool independently
compares the two profiles and creates the per-file override; no verifier is
disabled in any commit or push. One explicit current-flags trial was followed
by that proposal and an ordinary build. The full gate judges the override.

The compiler exception import also supports the same spelling. Its _ThrowInfo
is the compiler-predefined type, whose modifiers must not be replaced with a
new struct declaration. Its true public stdcall entry and two pointer arguments
forward to the retail msvcr71.dll!_CxxThrowException slot. It adds 6 C++ bytes.

A non-executed focused DLL forces all 27 public names and links through scoped
IAT-only import libraries. DATA import members avoid also providing callable
thunks that source already owns. The native CRT supplies its normal __fltused
data marker for the float signatures; there are no test doubles. The linked
PE import table contains exactly the 26 D3DX exports plus _CxxThrowException.
This is focused symbol/import closure, not full-game placement, census or
runtime verification. Only the scoped import-library helper is used.

The previous assembly comments claiming no C++ spelling are superseded by
actual VS2003 compilation, retail-byte comparison and independent PE identity
checks. Bank each verified body separately and remove the orphaned manual
assembly files after their last rows move. Existing generated dumps are untouched.

The recorded verification uses the final production objects, after all 26 D3DX
ledger rows and the exception row have moved to their C++ units. The obsolete
manual assembly sources are removed before publication, leaving one provider
per recovered name. The source SHA-256 values bind this evidence to those units.
The public signatures and import identities are evidence independent of a byte
placement; pointer-only declarations do not assert the pointees' class layouts.
