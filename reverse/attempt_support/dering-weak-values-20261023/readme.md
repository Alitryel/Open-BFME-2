# Weak de-ringing: consumed values recover the remaining C2 identities

Recovered `_DeringBlockWeak_C`, retail RVA `0x001C22C0..0x001C28B6`,
1526 bytes, into its existing strong sibling unit
`Code/Libraries/Source/VP6/DeringBlockStrongC.cpp`.

## Provenance and behavior

Only approved clean-room specs `001c22c0.md` and `001c1ad0.md`, retail,
the existing clean bank and its prior handoffs were read. No external VP6
implementation was consulted. The ABI, two short weight grids, threshold and
clamp rules and immediate per-pixel output behavior come from those specs and
retail. The retained bank supplied the already-close C++ loop structure; it is
preserved as `input-bank.cpp.txt` because add_match deletes a bank on landing.
The previous handoff is `../dering-weak-offset-20261021.md`.

Named sample loads, integer promotions and arithmetic intermediates now express
actual values consumed by the existing weight calculations. There are no dummy
locals, unused stores, padding branches or fabricated effects. The two grids
are still completed before output begins; output stores remain immediate and
in the same pixel order, including when source and destination overlap. Naming
the side-effect-free input expressions does not introduce a memory write or
callee into either weight loop. The source uses the existing canonical
`g_vp6SharpenModifier` global, not the old bank's second name for that address.

The temporary staging is a reconstruction choice. Byte equality does not prove
retail's original source declared these variables or used these identifiers.

## Experiments and result

The original bank emitted 1526 bytes with seven fixed differences. Prior work
had found that unused-local padding influenced the differences but correctly
refused that as recovery. This pass instead materialized genuine expression
values, preserving the rolled loops, arithmetic and actual reads.

Clang's AST supplied source ranges and original expression types, not codegen.
Nine initial controls covered arithmetic-only, sample and promotion staging;
the 64-value promotion control reduced the mismatch to two bytes. A finer
48..79-value interval was then tried around 64 (31 planned controls, excluding
64 already tested). It stopped at its 29th completed trial: 49 consumed values
produced the complete exact 1526-byte body. `initial-results.json` and
`fine-results.json` preserve every completed score and full COFF extent.
`materialize.py.txt` and `score.py.txt` preserve the source transformation and
isolated-object scorer. The winning isolated source SHA256 was
`8ecc20e6078c7129b70ae4f3b2ec76ee3d05ab0d3a825158d2521bb7f3779664`.

For replay, copy the input bank to
`build/local-vm/dering-weak-original.cpp.txt`, dump its JSON AST with
`clang++ -fms-extensions -target i686-pc-windows-msvc -Xclang -ast-dump=json
-fsyntax-only -x c++ INPUT`, and save that as
`build/local-vm/dering-weak-ast.json`. The generator's `generate('promotions',49)`
returns the winner before removal of obsolete bank comments and replacement of
its sharpen-table declaration with the canonical global. The fine scorer uses
private trial objects, never build.compile_source's shared cache.

## Current-checkout verification

Trials used the native-disk VM snapshot only as an experiment. Final admission
compiled the actual current host checkout through the local Linux x86/Wine VM,
with pinned MSVC 13.10.3077, existing `/O2 /G6 /DNDEBUG /MD`, and BFME 1 pointer
`42bba2ddbd5cb895d99293583891d3b7315fa49e`. `normal-gate.txt` records 2/2 exact
bodies (strong 2030 bytes and weak 1526 bytes). `current-proof.json` records the
full COFF extent, the one resolved canonical data relocation, no masking and no
unresolved relocations, and identical retail/resolved SHA256 values.

`link-check.txt` reports both bodies link cleanly: 2030 -> 3556 bytes in this
unit, against the published census. `find_declared_unmatched.py` reports every
definition matched. `place_bodies.py` found zero additional bodies or pins.
Clang's `-Wunused-variable -Werror` syntax check passed for the final source.
No pin, ABI, compiler, verifier, baseline or optimization changes were needed.
