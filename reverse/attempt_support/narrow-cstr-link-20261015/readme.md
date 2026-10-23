# Narrow c-string constructor link repair

At BFME 2 commit 2a46a4801de86e9daa104a4b0d0d8a79b28e6537, the 108-byte
constructor at RVA 0x9100 byte-matched but failed the local link check: its
private zeroing `_String_base` constructor was not retail's body at the same
name. The retail-proven owner remains `stlport_narrow_string.cpp`, RVA 0x689600.

Make the private constructor `__declspec(dllimport) __forceinline`. Its existing
inlining is unchanged, while MSVC stops emitting the unused base constructor
and its unused allocator-proxy constructor. No replacement definition, thunk,
import, address pin, or new fallback is introduced. The two retained COMDATs,
all remaining nondebug sections and relocations, EH records, external bindings,
and linker directives compare identically after normalizing COFF symbol indices.
Neither removed helper has an incoming nondebug relocation in the old object.
`proof.json` records removed bytes/digests, retained count, object/source/receipt
hashes, measurement context, and paired findings.

Technique lead: BFME 1 commit 66b19a8e95a4add525ef808fcea088e306798e2b
(dllimport/forceinline suppression of unused allocator copies). This is a local
adaptation to target-proven string code; the donor establishes neither BFME 2
identity nor layout. Reviewed BFME 1 checkout a7c38d3b2597121f178ab5190b3062478823257d.
Freshness fetch found upstream 98f9c4fc7a457bb4c754231e0ed5b073c41db06e, but the
reference-pointer claim is held by another seat; verified inputs were retained.

Acceptance checks:

- `./build.sh Code/Libraries/Source/WWVegas/WWLib/stlport_narrow_string_cstr_ctor.cpp`: 1/1 matched, string/float/import references pass.
- `link_check.py --prepare-current` before and after: strict reusable receipts, 1/1 byte-verified; no closure check implied.
- Ordinary `link_check.py` and independent deep copies of the same index with `link_check.refresh` applied to the saved before/current objects: one retail-wrong COMDAT finding becomes zero; local legacy linked bytes 0 -> 108.
- `link_check.py --new-variants`: none.
- `eh_verify.py`: EXACT 1/1; `data_check.py --enforce` and `--converged`: zero findings; `class_gate.py` and `find_declared_unmatched.py --fail`: pass.
- `place_bodies.py`: no additional bodies or pins.

The index is commit 825b86983f, underlying census 5986a99448. Objects were compared
using the normalized-section method in the existing shader-copy-link-20261015
proof, extended to the two removed constructor COMDATs. Scratch reproduction
and original objects remain under `build/narrow-cstr-link-20261015/` locally.
No census/status/index was published or changed. New authored bytes: zero.
This establishes a local legacy link repair and strict byte validity only;
self-strict and closed-strict gains are not claimed. Full link-cycle verification
remains a maintainer operation.
