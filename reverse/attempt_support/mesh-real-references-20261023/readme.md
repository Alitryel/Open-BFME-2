# Mesh single-stream deformation: real references, same 24-byte residue

Target: `MeshModelClass::get_deformed_vertices(Vector3 *, const HTreeClass *)`,
RVA `0x0016B680`, 2,237 bytes through the RET 8 ending at `0x0016BF3D`.
BFME 2 revision: `6b48d28f03c`. BFME 1 headers/toolchain input:
`42bba2ddbd5cb895d99293583891d3b7315fa49e`.

## Result and limits

The replacement bank retains the previous best complete compiled body:
2,237 bytes, zero unresolved relocations, M/B/S positional byte differences
**0/0/24**. It now has **no inert counter locals** and **no access-control
macro**. This is a partial diagnostic candidate, not a matched recovery;
no production source or ledger row changes.

Four references after `float w` are actually used in the output expressions:
`rotationZ`, `rotationW`, `translationX`, and `translationY`.
They refer to the original members, preserving reads and aliasing instead of
copying values across output stores. Moving `SkinMatrix3D` before `BoneTransform`,
exposing its inherited rows with `using Matrix3D::Row`, and accepting that actual
derived type in `Get_Matrix3D` preserves the same bytes without
`#define protected public`. The ordinary row-accessor alternatives lose the
blend match (0/50/24).

The four-reference set was trial `reference-subsets/refs_060`; other sets also
produce this body. These spellings are compiler-shape reconstruction hypotheses,
not claims about original variable names or source. The earlier upstream bank
and its allocator explanation are retained in `diagnostic-base.cpp.txt` as
replay input only; its inert locals and macro must not be promoted to source.

The final source was separately recompiled after comment cleanup. Its patched
body SHA-256 is
`7af1c9c37254347607de3be9a03eb161e5cd3ddebe3e352175a7709e1c1434d3`.
It is byte-identical to the previous diagnostic bank, not to retail.
The first retail difference remains +0x723 (RVA `0x0016BDA3`).
`remaining-diff.txt` records the differing aligned instructions: the first
cross-product pair's schedule/operand order and two later multiplication
operand orders. Score 0.9893 is a diagnostic byte ratio, not admission proof.

## Evidence basis

Read the whole-file context in `meshgeometry.cpp`, the exact 2,960-byte overload
in `Rva0016BF40DeformedVertices.cpp`, the prior attempt log, handoffs
`../skin-0016b680-20261022-w12.md`, `-w13.md`, `-w14.md`, and
`../mesh-helper-shape-20261022/readme.md` before these trials.
Target/WB evidence supports the function relationship, buffer/pivot offsets,
matrix arithmetic and quaternion transform. The pinned BFME 1 revision provides
the real WWMath declarations. No new identity or layout claim follows merely
from the compiled match. The upstream late-pass hash-variable model was used
to choose source experiments; it was not retraced locally.

## Trials

`trials.tsv` records all **291** runs: 61 distinct patched bodies, all complete
compiles with zero unresolved relocations, no exact result.

- 26 addressing controls: input/output indexing, references, input values,
  component dereferences, Set, and Vector3 result construction, with and without
  the old diagnostic locals. Index/dereference forms are inert. The input
  reference changes late product ordering but emits 2,236 bytes and changes a
  later multiply sequence; apparent positional improvements are not an exact S.
- 49 component controls: used scalar values/references, quaternion/translation
  values/references, before input products or output stores; input-component
  references. A single used output reference can reduce the no-shim control
  from 74 to 49 differing bytes.
- 118 further subsets of the seven used output-component references. Four
  references can recover exact M/B without the dummy locals. No S is exact.
- 94 existing Vector3/Quaternion indexing-helper variants, component subsets
  and complete-group combinations, with and without the diagnostic locals.
  These reproduce the respective control bytes; accessor inlining alone does
  not fix the residue.
- Four legal-access controls: the selected reference candidate, ordinary row
  indexing, scalar indexing, and the derived public using-declaration. The
  derived declaration retains 0/0/24.

## Replay and next step

Copy each `replay-NAME.py.txt` to `build/resume-eh-local/turn68-mesh-NAME.py`
and run from the repository root with its normal compiler environment, in the
order listed above. `addressing` is the shared runner; `legal-access` uses the
generated `reference-subsets/refs_060.cpp`. The runner reads the saved diagnostic
baseline rather than the newly improved bank. Every trial uses
`tools/explain_mismatch.py` with a distinct scratch source; subsequent scoring
reads that object. No direct shared-cache compilation is used.

The remaining useful direction is the late single-bone induction/hash-variable
creation described in w14, now using the no-shim bank. Trace the input reference
case and this bank before expanding another product-order grid; source operand
swaps and the tested indexing helpers do not solve it. This session ended at
the user's instruction to publish the next commit and stop, not a conclusion
that all viable hypotheses are exhausted.
