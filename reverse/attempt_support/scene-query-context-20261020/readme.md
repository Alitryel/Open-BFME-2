# Scene query context controls

Target: `?rva00142170@BfmeSceneVector@@QAEXPAPAUGen_00943CF0_Node@@PAUSceneCollectCell@@IHHHHHHH@Z`,
retail `0x00142170..0x0014232B`, **443 bytes**, `RET 40`.
Input revision `34a366c11e`; BFME 1 donor `92f6bbe8e1`.
Model: GPT-6 Astra (investigation seat); Codex (root coordination). The existing primary bank
`reverse/attempts/0x00142170.cpp` remains unchanged.

The baseline reproduces the previous handoff's 443 bytes and 160 instructions,
with zero structural regions. The sole non-relocation difference remains:

```text
retail +0xEB: mov edx,[esp+0x28]   ; ymin
       +0xEF: mov ecx,[esp+0x24]   ; xmin
candidate: the same two loads in the opposite order
```

The first patched byte difference is `+0xEC`, RVA `0x0014225C`. These loads
follow the first recursive call at `+0xE2`. No rectangle parameter's address
is taken; the native comparisons are signed. Input list traversal copies
object pointers to the output list; it does not drain the input list.

## Pool and construction controls

Scratch sources, preparation script, normal `explain_mismatch` output and
`align_diff` reports are under ignored `build/loop-scene/`.
Each source has a distinct cache path; compilation used the normal mismatch
entry point, `BFME_OBJSTORE=off`, and workspace temporary directories.

| Control | Result |
|---|---|
| 00: baseline | 443 bytes; two loads reversed |
| 01: actual member pool-pop receiver | Identical residue |
| 02: natural placement construction | Identical residue |
| 03: member pop plus placement construction | Identical residue |
| 04: actual STLport `_Construct` | Identical residue |
| 05: real `slist<void*>` and pool allocator | 436 bytes; `_M_create_node` outlined |
| 06: visible force-inlined node body | Same outlined result; body contains EH |
| 07: donor signed count with unsigned quartering | 443 bytes; same residue |
| 08: member pop plus signed count | Same |
| 09: real slist with donor `_STLP_NO_EXCEPTIONS` | 443 bytes; full chain inlines; same residue |
| 10: visible node body with donor no-exception setting | Same |

Controls 02–06 initially failed because CRT `new` and WWLib `always.h` both
defined placement-array operators. The established
`__PLACEMENT_VEC_NEW_INLINE` guard from BFME 1's recurse source and BFME 2's
`SceneSpatialRescale.cpp` repaired the scratch include context. No shared
header changed. The table reports corrected results.

The pool semantics are independently established by grow/pop
`0x0006EFC8`/`0x00141800` and allocation/create/push helpers
`0x00141CB0`/`0x00141D60`/`0x00141DC0`. Existing
`SceneNodeListProviders.cpp` also proves the STLport list-base destruction
family at `0x0006FABF`/`0x0006FB50`. Thus controls 09–10 establish a genuine
library allocation/construction chain equivalent to the manual bank's whole
parent shape. They do not close its final scheduling difference.

## Independent caller controls

Root controls in ignored `build/loop-scene-root/` reproduced the same residue
when composing the candidate into the actual
`SceneSpatialCollectBFME2.cpp` owner, using the equivalent `Get_Obj` accessor,
moving the iterator into the `for` initializer, resetting the iterator,
changing the object pointer's const lifetime, and decomposing the first
recursive argument list through four fully inlined helpers.

`/G5`, `/G6`, and the default processor setting produced 457-byte bodies with
earlier allocation changes. Size scheduling produced 322 bytes with the pop
helper outlined. Diagnostic barriers before/after the first call and at its
join left the two-load residue unchanged; a barrier before the quadrants
introduced an earlier difference. These barriers are diagnostics only.

## Remaining prerequisite

The missing explanation is the caller-saved parameter reload ordering at
the first recursive join. Current target evidence and genuine source
contexts do not reproduce it. Another register-spelling permutation is not
justified by these results. No body, pin, ledger row or production source
was changed, and no coverage is claimed.

Helper ownership must also be handled if a future candidate lands:
the actual member pop control emits a complete retail-exact 46-byte copy,
but its existing provider is strong. The free helper emits a 50-byte
unreferenced copy with no whole-body native occurrence; it is
reconstruction-only code, not another recovered function.
