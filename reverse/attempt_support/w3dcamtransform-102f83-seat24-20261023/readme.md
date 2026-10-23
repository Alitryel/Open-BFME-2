# Camera 0x102F83 continuation — 23 October, seat24

The bank improves from **0.9741961629 to 0.9807022096**. Its complete emitted
body remains **4,299 bytes**; differing resolved bytes fall **228 → 200** and
normalized changed instructions **74 → 56**. All **57 relocations resolve**.
This is a partial reconstruction, not a matched row. The fitness is a weighted
similarity metric, not a percentage of exact bytes. No production C++, pins,
canonical headers or ledger rows changed.

## Winning change and evidence

In all three rows of `Matrix3D::Rotate_X(float)`, change only:

```cpp
Row[n][1] = (float)( c*tmp1 + (s*tmp2));
```

The incoming spelling had no parentheses around `s*tmp2`. The other row
expression stays unchanged. This removes all 18 differing instructions in the
shaker region (+0xC02..C92) without changing other regions. Final Rotate_Y and
the tail stay exact. The operation order and behavior are preserved; this is
an evidence-backed compiler-shape adaptation, not proof of the original spelling.
The relevant compiler recipe is `docs/recipes.md`, "FP parentheses are IL nodes",
with its linked `fp-paren-nodes-20261020.md` evidence.

All eight row subsets were compiled. Row 0 alone leaves 8 shaker differences;
rows 0+1 or 0+2 leave 4; all three remove them. Altering only rows 1 and/or 2
leaves the incoming 18. Thus all three edits are necessary on this input.
`results.json` includes every minimization result. Independent private compiles
of incoming and winning sources reproduce both measurements; `verification.json`
records commands, complete-body hashes, counts and all relocation results.
No patched compiler, masked calls, padding, barriers, volatility or dummy uses.

Retail boundary and RET4 remain `0x00102F83..0x0010404E`. WB twin remains
`0x007E3040..0x007E7303`. Parent/descriptor identities and layouts retain the
qualifications in the seat23 and r66 handoffs. This session read their evidence,
including the faithful WB source and compiler ownership/cost traces. It did not
repeat the closed compiler-build/flag or complete Look_At provider searches.

## Inputs and reproduction

Input bank: published commit `ce76006fa6`, SHA256
`f585abbaa3d1d5ef987cdfd827deebefca3c10b4a332114a9145f93f9f7ffb03`.
Starting checkout `cf8e30f57c` had this same bank; its preceding reproduction-note
commit was still unpublished. BFME 1 pointer:
`f890413e75e671748215ba2ef3304aa7953993e9`.
Flags: `/O1 /G7 /arch:SSE /DNDEBUG /MD` and the bank's explicit include paths.
Compiler: ordinary MSVC 7.1 (13.10.3077), through Wine and `build.compiler_command`.
Objects are private scratch paths; the shared build cache was not written.

Copy the three `*.py.txt` files here into an ignored `build/` directory, dropping
`.txt`. Run from the repository root:

```sh
python3 build/camera-repro/search.py parens
python3 build/camera-repro/families.py matrix
python3 build/camera-repro/minimal.py
```

The harness obtains and hashes the immutable incoming bank with `git show`.
`families.py` applies the three-row winner first. Its accepted family names are
listed below; `minimal.py` starts from incoming. Eight private worker processes
compile each family. Diagnostic alignment normalizes branch/relocation operands;
`nd` and fitness independently use the complete resolved bytes without masking.
Region buckets are approximate: a large alignment hunk can straddle buckets,
so an absent bucket is not proof that the region matches.

## Trials closed on these inputs

**5,824 generated cases plus 8 row-minimization controls; all compiled.**
The families explore interactions, so controls and equivalent emitted bodies
recur. Counts are compile cases, not distinct useful source shapes.

| Family | Cases | Choices and result |
| --- | ---: | --- |
| `parens` | 256 | Rotate_X product grouping, outer grouping, negation form, used sine/cosine references and receiver reference. Only the second positive product grouping is needed; winning edit above. |
| `matrix` | 1024 | Six matrix products, angle sum grouping, complete dot-sum grouping and x/y declaration order. No fitness improvement; sum grouping gives a 4,298-byte/53-instruction alternate. |
| `valuepaths` | 256 | Returned-vector constructor/local-copy/scalar expressions, pitch division/reciprocal spellings, const-reference input and actual Set(copy) output. No improvement. |
| `ctor` | 1024 | Six axis-constructor sine products, trigonometric result grouping, used one-minus-c and Set forwarding. No improvement. |
| `refs` | 256 | Selected source/target XY reference aliases at four scopes and four pitch reference forms. No improvement. |
| `recombine` | 1024 | Matrix sum grouping, actual two-argument in/out overload forwarding, named row fields, angle grouping, used live/ground heights, ground ratio, adjusted pitch and constructor locals. No fitness improvement. Retains the least-instruction alternate below. |
| `depth` | 512 | Zero to three extra grouping levels around explicit float translation/pitch sums, with/without matrix sum grouping. No improvement. |
| `xy` | 256 | Genuine two-component returned values instead of a full Vector3, copy/constructor forms and direct/member output copies. No improvement; direct expression returns often restore unwanted enregistration. No new class identity is asserted. |
| `indexed` | 512 | Actual Vector3 operator[] spelling at the four translation sites, pitch arms, remaining main component uses and helper components. No improvement. |
| `scalar_lifetime` | 320 | One/two/four real scalar temporaries reused across translation paths versus block locals; shared/separate pitch temporaries, declaration scope, chained assignments and sum grouping. No improvement. This closes the proposed cross-block scalar ownership alternative on this bank. |
| `lookup` | 128 | First live-camera lookup condition captured at eight positions with value/reference/pointer forms. Later post-call condition still reloads the descriptor. No improvement in constructor/test scheduling. |
| `trig` | 256 | Actual float cos/sin overloads versus cosf/sinf, direct double CRT calls narrowed to float, expression grouping and constructor→Set→Set forwarding. No improvement. |

`results.json` retains family winners, least-divergent results and distinct
outcome counts. The scripts preserve exact choices; do not repeat these same
factorials without new evidence or a changed input interaction.

## Remaining differences and continuation

The bank has 56 normalized changed instructions: 29 structural/scheduling and
27 operand differences, in these buckets:

- pitch constructor +0x40A..41D: 3, including placement of the live-camera test;
- angle additions around +0x4EA: 2;
- initial XY translations +0x515..549: 9, delayed copies/Y register;
- live matrix +0x6EC: 2;
- live translations and Z join +0x768..7C8: 23;
- realZoom pitch +0x86B..8B3: 17, inverse register and delayed stores.

`alternate.patch` changes the winning bank to the previous used-live-target-height
alternative without the ground-ratio local. With the shaker fix it emits
**4,298 bytes**, score **0.9693616047**, and **52 changed instructions** (20
structural/32 operand). It has 2 pitch-constructor, 2 angle, 9 initial-translation,
4 live-matrix, 18 live-translation and 17 pitch differences. Its full diagnostic
is retained. It is not better overall and does not replace the bank.

Continue this same body. There is **no missing-function prerequisite**. The open
problem is still the arithmetic-owner/lifetime distinction behind sequential XY
stores, plus the independent matrix schedules. Current scalar/aggregate and
indexing trials did not reproduce the retail ownership. A useful further step
is a small translation/pitch probe with scoped compiler tracing of the current
best and faithful direct-field source; earlier r66 traces used different inputs.
Use ordinary full-body recompiles to validate any new explanation. Do not revert
the solved shaker or repeat old flag/escape/visibility trials by themselves.

Before production admission, reconcile the neutral descriptor/caller identity,
the canonical Coord3D::lengthSqr declaration, and the current named live-camera
string global as earlier handoffs require. These are integration obligations,
not a reason to claim that this partial body is exact.

Session checks: pull/rebase up to date; check_csv passed. BFME 1 freshness update
was skipped under the runner rule because the fresh shared lock belongs to
`codex4`; neither the reference pointer nor success stamp was changed.

model=gpt-6-astra
