# Camera 0x102F83 continuation — 23 October, seat25

The existing bank remains best: weighted fitness **0.9807022095501403**,
**4,299 emitted bytes**, **200 differing fully resolved bytes**, **57 resolved
relocations**, and **56 normalized changed instructions** (29 structural and
27 operand differences). No new exact C++ bytes or production changes.
Fitness is not the percentage of equal bytes. The substantive new evidence is
a read-only trace of the ordinary compiler's translation scheduling decisions.

## Inputs and established constraints

Starting local revision: `420cbfca3582f74b8bfd645be12eecc1aa36e2c9`
(subsequently rebased by the publication workflow). The immutable input source
blob is `8f049066a3dd5397919c5a50d471cc2e01dfd991`.
Input bank SHA256:
`931e4b8a02c469cf3bf2aeead7b5523e53c0e594f03a3d004d36dbe6a41d68eb`.
BFME 1 pointer: `f890413e75e671748215ba2ef3304aa7953993e9`.
The fresh BFME 1 update lock belonged to `codex4`; this seat skipped the update
as directed and did not author a pointer update or alter the lock/success stamp.
The closing upstream pull brought in verified pointer
`f36a4db066aa61edeee90085a31d628eb829001d`; a separate ordinary compile after
that pull is recorded in `post-pull-verification.json`.
MSVC 7.1 13.10.3077, Wine, `/O1 /G7 /arch:SSE /DNDEBUG /MD`; full invocation
and body/relocation hashes are in `verification.json`. All objects were private
scratch objects; no shared build-cache object was written.

Read the seat24, seat23 and r66 handoffs before this one. The existing boundary
is `0x00102F83..0x0010404E` (RET4), with WB twin `0x007E3040..0x007E7303`.
Identity/layout qualifications and eventual production reconciliation remain
unchanged. No new target name, layout, pin or donor fact is asserted here.

Earlier evidence already ruled out direct component expressions (unwanted
enregistration), interleaved aggregate copies that lose the class-2 boundary,
ordinary scalar lifetime variants, broad compiler settings/builds, complete
Look_At visibility variants, and most matrix/constructor parenthesis choices.
The new hypotheses were interactions of float leaf nodes and copy ABI,
whole-arm inline ownership, reference lifetimes, and angle-specific product
grouping. Do not repeat these families on unchanged inputs.

## Trials

**5,120 generated cases compiled.** Of these, **5,048 resolved successfully**;
72 copy-ABI variants were rejected while applying relocations beyond the
4,299-byte row extent. For example `copyabi_0122` emits a Look_At REL32 at
offset 4,298, requiring bytes through 4,302. These are extent failures, not
missing-callee blockers. No accepted case improves the bank. Controls and
equivalent results recur: these are case counts, not distinct useful bodies.

| Family | Cases | Choices |
| --- | ---: | --- |
| `angle` | 1,024 | Nine product-grouping choices specifically in the angle matrix helper, crossed with reversed x/y/z declaration order. |
| `copies` | 1,024 | Float leaf grouping in copy constructor, assignment and Set, crossed with reversed component-copy order. |
| `zoomregion` | 512 | Inline the entire realZoom arm into a helper; by-value/reference source and target, parameter order, used temporaries, direct/returned pitch, translation form and matrix sums. |
| `copyabi` | 256 | Explicit, implicit, Set or memcpy copy operations; explicit return copies and const by-value input/local-copy ownership. |
| `value_nodes` | 1,024 | Unary-plus nodes on translation sums/operands, direct or returned translations, and pitch-expression grouping. |
| `lifetimes` | 1,024 | Real const-reference lifetimes for ratio, factor, matrix temporaries, scale and angle/pitch parameters; live-height temporary. |
| `matrix_aliases` | 256 | Used receiver, input, row and output references inside either/both matrix-vector helpers. |

`results.json` records family winners, region minima and outcome counts.
Some angle/lifetime/alias cases retain the known 4,298-byte, 53-instruction
alternate; it has worse full-body fitness. Region minima are approximate
alignment buckets, not independently verified matching subranges.

## New scheduling evidence

`schedule.py.txt` and `wdbg.py.txt` observe the stock compiler using breakpoints
and memory/register reads. They do not force costs, register choices, edges or
instructions. The debugged function's **complete raw body and all relocation
tuples equal the ordinary compile**, as recorded in `verification.json`.
Object files differ in other contents; the equality claim is for this function.

The trace captured 54 scheduling graphs and 683 cycle snapshots. Only graph 21
(the first matrix/XY translation region) and its 72 cycle snapshots are retained
in `translation-graph.json`. `translation-ready.json` extracts relevant nodes.

At cycle 59, both source-Y position load and source-X store have been ready
since cycle 58. The load's static/dynamic priority is `0xA000`, height 7;
the store's is `0x1C00`, height 5. The load issues, while the store remains
ready through cycle 62. At cycle 62, the Y add (`0x2400`) also outranks that
store. The target translation repeats this: at cycle 67, the Y load (`0x9400`,
height 4) outranks the already-ready X store (`0xC00`, height 2).

Thus an unavailable X result does **not** explain the delayed stores in this
bank. The scheduler is free to store X earlier but prioritizes the Y load/add.
The bank uses separate XMM registers for X and Y; retail reuses XMM0, which
requires the preceding X store before loading Y. This supports working on the
allocation/lifetime cause of the overlap, rather than repeating changes aimed
only at making the X result ready. It does not prove the original source form.

Trace decoding: graph nodes have tuple pointer at word 7, static/dynamic
priority at words 10/11, ready cycle at 12 and height in low 16 bits of 13.
Tuple source/destination operand lists are words 10/11; opcodes 293/516/524/532
are move/addss/mulss/subss. XMM0's descriptor is `0x108AB964`, stride `0x60`.
The script's absolute c2 addresses apply only to the recorded compiler build.

## Reproduction and next step

Copy the four `*.py.txt` files into an ignored `build/camera-repro/` directory,
dropping `.txt`; run from the repository root. `search.py` reads and hashes the
immutable input blob with `git cat-file blob`, never the mutable current bank
or a commit name that a publication rebase can replace. It always
recompiles and excludes extent/relocation failures from fitness ranking.

```sh
PYTHONPATH=build/camera-repro python3 -c 'import search as h; print(h.run_one(("baseline",h.BASE)))'
python3 build/camera-repro/families.py matrix_aliases
python3 build/camera-repro/schedule.py build/camera-repro/trials/baseline.cpp build/camera-repro/traced.obj
```

The other family names are in the table. Eight isolated compiler processes are
used. Diagnostic alignment normalizes relocation/branch operands; fitness and
differing-byte counts use complete resolved bytes without masking.

Remaining differences: pitch constructor/test scheduling (+0x40A..41D, 3),
angle adds (+0x4EA, 2), initial translations (+0x515..549, 9), live matrix
(+0x6EC, 2), live translation/Z join (+0x768..7C8, 23), and realZoom pitch
(+0x86B..8B3, 17). The shaker and final Rotate_Y/tail remain exact.

Next concrete angle: identify where source/target Y acquire separate live
XMM intervals while preserving the class-2 aggregate ownership that keeps their
fields in memory. Compare the ordinary allocation trace against a narrowly
scoped probe with sequential X/Y reuse; carry back only supported source shapes.
Direct-field, interleaved-copy and scalar-lifetime families already failed, so
the probe needs to retain the returned-aggregate ownership boundary. No
missing-function prerequisite was found. Resume this same body from the bank;
the claim is released when this session ends.
