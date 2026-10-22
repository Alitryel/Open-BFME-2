# Mesh helper shape controls, 2026-10-22

Target: `MeshModelClass::get_deformed_vertices(Vector3 *, const HTreeClass *)`,
RVA `0x0016B680`, 2,237 bytes through the native RET 8 at `0x0016BF3D`.
BFME 2 input: `3c0234e9763`; BFME 1 input:
`37c3022de1ab944c7ffe536440d637dc8199091c`. Compiler flags and real WWMath
headers are retained in the replay input. No production source or ledger row
was changed by these trials.

## Basis and hypothesis

Read `../skin-0016b680-20261022-w12.md` and its compiler trace evidence before
testing. That trace proposes reducing expression-temporary allocation before
scalar replacement without moving the single-bone locals out of their existing
symbol-ID band. The trace is upstream evidence, not a locally repeated debugger
measurement. These tests measure emitted instructions, not internal Q chunks.

The whole-file target context and exact overload remain unchanged since
`48f4da98339`: `meshgeometry.cpp` and `Rva0016BF40DeformedVertices.cpp`.
Target/WB evidence supports the function relationship, matrix arithmetic and
single-bone behavior. The donor supplies reusable WWMath declarations. The
helper spellings and temporary lifetimes tested here are reconstruction
hypotheses; a byte match alone would not establish their original spelling.

## Tests and result

82 runs, including three controls, all compiled and resolved their relocations.
None is exact. There are 62 distinct compiled bodies; 19 runs reproduce the
banked body. `trials.tsv` records every extent, score and source/output hash.

- Seven subsets of component stores replacing nested vector indexing leave
  the banked bytes unchanged.
- Seven row-Set subsets, a full Matrix3D::Set call, six grouped product-inlining
  forms and four scalar/unrolled scaling forms do not improve the bank.
- Moving the existing SkinMatrix3D declaration, specializing Get_Matrix3D's
  parameter to that actual object type, and seven subsets of direct protected
  row access all leave the banked bytes unchanged. The scratch friend declaration
  permits legal access to the existing rows; it adds no fields or casts.
- Nine individual product substitutions and all 36 pairs change matrix-region
  code and do not improve the bank. No new dummy local or inert helper was used.

The best candidate remains `reverse/attempts/0x0016b680.cpp`, SHA-256
`31fdcbfd5c83c85f0b1314b06c31de160cad2304d11e53c2b26c02fca5024e13`.
It has the full 2,237-byte extent, no unresolved relocations, M0/B8/S8 differing
aligned instructions, 74 positional byte differences and 2,150 aligned matching
instruction bytes. Its patched SHA-256 remains
`7293255068a74acee356eb10bf650845114eaadad40eafa1eefb7443b631b7d1`.
The aligned diagnostic ignores jump encoding differences and is not a byte gate.
Exact admission requires full extent and complete relocated byte equality.

## Reproduce and continue

Copy each `replay-*.py.txt` into untracked `build/` and run from the repository
root with the normal toolchain environment. They read the tracked
`mesh-cross-context-20261021/cross-base.cpp.txt`, generate scratch sources and
invoke `tools/explain_mismatch.py`; they do not compile production sources by
hand. Each writes its detailed diagnostics and results under
`build/resume-eh-local/turn67-mesh-*`.

These results rule out the tested row-access and product substitutions as a
standalone fix. They do not disprove the upstream allocator explanation.
A useful next test would measure Q allocations/frees for actual helper variants
before expanding combinations, or find independent target evidence for a
different Get_Matrix3D expression/lifetime structure. Preserve the better bank;
do not replace it with these worse candidates or publish any as matched.
