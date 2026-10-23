# EVA reset/temporary overlap, s6 (2026-10-23)

Input BFME2 `4b322c60ee`, BFME1 pinned `138757e9b746`.
Status: blocked; no production source or row changes. Both existing sources
remain byte-exact separately (Eva.cpp 16/16, EvaRva001DF42D.cpp 5/5).
Current-object link preview still refuses both only for the duplicate reset
`?rva001DCD3C@Rva001DCD3C@@QAEXXZ`: zero of 3,016 owned bytes link.

## New hypotheses tested

The previous evidence already excludes removing either reset, inline/COMDAT
suppression, volatile/barrier fixes, store-order searches, and common lifetime
spelling changes. The new test was whether the cast-based status wrapper hid
its actual subobject from MSVC's escape summary.

Starting with the tracked parser TU, isolated copies tested:

- Original cast wrapper; `BfmePod52 : public Rva001DCD3C` with the 13-dword
  payload removed and an inherited reset call; and a `Rva001DCD3C status`
  member replacing that payload, reset through `status.rva001DCD3C()`.
- Each model with direct writes, only `m_24.zero()`, or all three coordinate
  `zero()` calls. The last coordinate form is the smallest existing variant
  reproducing the reset's real instruction order.
- Base/member models with reset in the base/member default constructor and
  an empty outer constructor, for last/all-coordinate zero forms.
- `__declspec(nothrow)` on reset declaration and definition, in all three
  models; `__declspec(noalias)` was rejected with C2485, not a codegen result.
- Direct-write controls with `-Op`, `-Op-`, `-Ow`, and `-Og-`; and changed
  tail-field representation (pointer, float, byte) / 8-bit enum flags. These
  are diagnostic type controls, not inferred target types. In particular
  the byte tail writes only one byte and is not a valid implementation.

27 trials: 24 compile, three unsupported-attribute failures. None matches
all three bodies. Results and source hashes are in `results.json`; isolated
sources, objects, compiler output and driver remain in `build/eva-s6/`.
The script uses compiler_command with the real parser source's flags and a
separate scratch object, never compile_source/shared match-cache mutation.
It resolves relocations with production compile_function; every compiled
trial has zero unresolved references in all three measured bodies.

## Exact remaining mismatch

The direct-write controls retain both exact parsers (635 and 484 bytes), but
reset is 80 bytes with 13 positional differences: `xor eax,eax` moves before
the two -1.0 stores, rather than after `xorps xmm0,xmm0` at retail 1DCD50.
Base/member representation and constructor dispatch do not change this.
The natural zero-method variants produce exact reset bytes, but parsers grow
to 638 and 487 bytes: frame 0x7C/status at -0x88 instead of 0x4C/-0x58.
All `nothrow` variants retain that larger frame. `-Op`/`-Op-`/`-Ow` do not
change the baseline; `-Og-` changes all bodies substantially.

Target instruction order was independently read from retail. The supplied
BFME1/Zero Hour Eva sources are semantic context, not byte proof; they do not
establish a changed target layout. No artificial stack overlay, invented
provider, code masking, or source-side alias bypass was used.

Model gpt-6-astra; seat s6. Next useful evidence must explain the real reset's
callee escape summary together with parser temporary reuse, or justify a
shared home preserving both. Repeating the type-subobject matrix adds nothing.
