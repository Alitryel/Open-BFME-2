# Runtime linkage and provider consolidation

## Runtime/import setup

The whole-tree diagnostic at 5308e3397a passed `/NODEFAULTLIB` but supplied no
MSVC runtime archives. `msvcrt.lib` actually provides `__fltused`, the security
cookie and exception machinery; `oldnames.lib` supplies legacy CRT aliases.
Use these shipped providers rather than synthetic game data or symbol stubs.

A short CODE import member also defines a callable thunk. Where a source object
already defines that name, generate a DATA import member to provide only its IAT
cell. This does not change the DLL/function imported through that cell. Preserve
COFF `_name@N` while setting the short import's UNDECORATE name type: lib.exe's
DEF output otherwise imports `name@N` rather than the DLL's `name`.

The real-toolchain regression links without FORCE or unresolved-symbol stubs.
Its control reports both a duplicate native thunk and unresolved CRT markers;
after repair it links and pefile verifies an actual `kernel32.dll!Sleep` import.
It also references the security cookie, exception handler and `_stricmp` alias.
All link-cycle and gate-exploit regressions: 108 passed, 1 skipped under Wine.
No byte, data, relocation, closure, baseline or exploit-admission rule changed.

Reference review: committed BFME1 a0e8f345a9b22b4b42088e402962287d7015e3c2
`tools/link_cycle.py` and `tools/import_binding.py`: explicit oldnames handling
is applicable; the former still has the same generated-library/runtime setup.
No donor source was imported. The changes are checked against BFME2's shipped
compiler/linker and native import identities.

## GDI+ native providers

The Bitmap destructor unit copied twelve Image/Bitmap definitions from the main
SDK unit. Both existing Bitmap constructors belong with the native 36-byte
Bitmap deleting destructor: their vtable emission is needed to emit that body.
Move the constructor rows and retain their bodies there; remove the copied
Image methods. Store the constructor's native image field directly, preserving
the SDK setter's inlined operation without emitting another setter definition.
Image's out-of-line destructor remains in the main unit to preserve its own
27-byte deleting destructor. No new class identity, body extent or pin.

Normal byte gates: 14/14 bodies across both units. A strict real LINK invocation
of the same two sources plus shipped GdiPlus/MSVC archives gives:

- Before: 12 LNK2005 errors, no image.
- After: exit 0, no duplicates, fixture DLL produced.
- MAP selects Image deleting destructor from the main object and Bitmap deleting
  destructor from the constructor/destructor object, their byte-verified owners.

This is a scoped link proof, not a full game link or closure certificate.
`place_bodies.py` found 0 additional bodies and 0 pins in the repaired pair.

## Animation factory cleanup

The complete 94-byte AnimationAsset::Get and its EXACT EH graph independently
bind the returned-owner cleanup to RVA 0x7668E4. Its actual emitted owner
pointer destructor is an entire 12-byte and relocation twin of the existing
physical RefCountPtr<TextureClass> destructor at 0x17098D. Record that real
emitted twin, then replace the separate MASM cleanup by the parent's local C++
label. The 25-byte interval includes its shared RET; no separate one-byte body
is claimed. Source-carried owner/prototype names remain structural ABI views.

48/48 bodies across the C++ and remaining ASM units pass; parent EH EXACT;
source code-identity shadow reports 0 new findings. ASM-only to C++ exact: 25B.
Placement rescan: 0 additional bodies/pins. No new address pin or object-symbol
alias. The old assembly row has a union-merge tombstone.

## Deferred constructor investigation

ConnectionManagerInit2 still has a duplicate constructor. Deleting it alone
strands the cleanup of its mapped-value member at offset 0x12138. Reconciliation
can pass the 15 local bodies, but broader checks expose divergent allocator and
container providers; the emitted mapped tree-base allocation sequence is not the
native one. The entire source/pin/ledger trial was reverted. The blocked attempt
is recorded in re_attempts.log; none of its source or pin changes are published.

Ignored command logs and controls: build/local-macos/runtime-link/.
