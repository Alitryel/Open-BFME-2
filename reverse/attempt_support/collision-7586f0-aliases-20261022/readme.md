# Collision sort: unchanged address-generation residue

Native `?rva007586F0@CollisionManagerImpl@@QAEXXZ`, 0x007586F0..0x007588BC,
460 bytes. Existing bank `reverse/attempts/0x007586f0.cpp` is preserved unchanged.
Actual measured fitness is 0.9904730653541154, full emitted extent 460 bytes,
33 differing byte positions, frame 0x4c. No production body or ledger row added.
Model gpt-6.1-sol; approximately 10 minutes on this fallback after landing
0x00525CC5. BFME2 input c52128d210; verified BFME1 pointer
37c3022de1ab944c7ffe536440d637dc8199091c. Flags `/O2 /G6 /DNDEBUG /MD`.

Target evidence and prior failures were read before editing. The UpdateSort
caller, native body and identical optimized WorldBuilder twin establish receiver,
layout and merge behavior, but not an original method name. Prior handoffs
`../007586f0-20261021.md` and
`../collision-7586f0-profiles-20261021/readme.md` already rule out ordinary
declaration permutations, pass-loop forms, inline list accessors, pair views,
owner integration, compiler flags and three authentic compiler builds. They
were not repeated. This is a leaf body: no missing callee can block visibility.

The new hypothesis was that aggregate ownership, aliases or cross-phase local
identity could retain retail's register coloring while giving B its independent
array-index address. Four factorial families tested it:

| Family | Trials | Compiled | Choices |
| --- | ---: | ---: | --- |
| aliases | 1536 | 1536 | index/reference/pointer aliases; array references, struct and union ownership; const pointers; output/run references; function-scope axis counter |
| accesspaths | 2592 | 2592 | B initializer crossed with independent A/B count, head and selected-list access paths, using only existing semantic uses |
| construction | 960 | 960 | field ownership through inheritance; empty/zeroing constructors and destructor; volatile members; both B initializers |
| phase-reuse | 240 | 168 | reuse the distribution counter in later nonoverlapping phases; reuse endpoint cursors; flattened declarations; both B initializers |

All four families retain the same best body. The 72 rejected phase-reuse trials
have out-of-scope reused locals; the corresponding flattened variants compile.
No exact result and no better bank were found. Pointer/reference ownership,
types/layout and lifetime each received concrete trials. Control-flow, callee
visibility/context and compiler-setting explanations remain covered by the
reviewed prior experiments. No assembly, artificial uses or compiler changes.

Remaining difference is exactly the prior address calculation and loop padding:
retail computes `lea ebx,[esp+eax+38h]` immediately after A; bank computes
`lea ebx,[edi+0ch]` after output-count stores and their comparison. Both streams
realign at 0x007587A0 and match thereafter. The independent-index alternative
still changes register allocation and emits 470 bytes. The raw COFF extent is
checked separately because the row-sized scorer truncates excess bytes.

`search.py.txt` plus each generator preserves reproducible trials and compact
`results.json` records full sizes and best scores. Copy to an ignored build
directory, adapt ROOT/OUT if necessary, and run each generator with Python. Each
uses unmodified `compiler_command` and isolated scratch objects, eight workers;
no shared build cache is overwritten. Existing better bank and prior diff stay
the starting point. A future trial needs a distinct source-shape explanation,
not another index spelling or declaration-order scan.
