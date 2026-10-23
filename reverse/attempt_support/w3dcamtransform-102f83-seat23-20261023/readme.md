# W3DCamTransform camera body 0x102F83 — 23 October continuation

The bank improves from **0.9570679011** to **0.9741961629**. It now emits
exactly **4,299 bytes**, with **228 differing bytes**, all 57 relocations
resolved, and no weak-call masking. It is still partial. No production source,
identity, pin, canonical header or matched row was changed for this body.

The only winning source change is a used intermediate for the existing ratio:

```cpp
float groundFraction = v->groundLevel / sourcePos.Z;
float factor = 1.0 - groundFraction;
```

The incoming bank calculated both in one statement. This is a compiler-shape
adaptation of the same operations, not evidence of an original local name.
Retail remains `0x00102F83..0x0010404E`, RET4. The parent identity/layout and
WB `0x7E3040` evidence remain as qualified in r66 and its linked causal notes.
The score includes a byte-position term: exact length substantially raises it.
Do not mistake that for solving most remaining instruction differences.

## Inputs and reproducibility

Experiment base: local `040f647a54`, published after rebase as `080384f1c9`
(the preceding exact FXShaderGeometry::Init recovery). The original bank at
the published revision has the identical SHA256 below.
Incoming bank SHA256:
`b8594a3f29cceeb0dbcea8d7bef9a85eb58bc09f3641dee7fac4a2fad7448b6c`.
BFME 1 pointer: `f890413e75e671748215ba2ef3304aa7953993e9`.
Flags remain `/O1 /G7 /arch:SSE /DNDEBUG /MD`, with the bank's actual include
paths and WWMath header. All experiments used ordinary MSVC 7.1 and private
objects in `build/camera-102f83-seat23/`; no compiler patches or shared-cache
compiles. A second independent private compile reproduces the winning result.

Copy `search.py.txt` to an ignored build directory as `search.py`, and run from
the repository root, e.g. `python3 build/camera-repro/search.py namedvalues`.
It obtains the original input using `git show 080384f1c9:reverse/attempts/0x00102f83.cpp`,
so rebanking cannot silently alter the experiment. It uses eight worker
processes. `recombine.py.txt` takes a family and namedvalues bit string; run
`namedvalues` first. Its helpers intentionally remain diagnostic/reconstruction
experiments, not newly established donor identities.

`results.json` preserves each family's best, least instruction divergence and
factor means/maxima. `best-recheck-diff.json` compares the bank's full ordinary
object to retail. Normalization ignores relocation/branch destinations for
diagnosis only; resolved byte differences are recorded independently.

## Trials closed on this input

1. **Donor context, 256 combinations.** Vector3 constructor markings and
   assignment/Set markings, Vector4/Matrix3D default/array accessor markings,
   the ZH kind-of chain, actual Matrix3D constructor-to-Set forwarding,
   row-wise Make_Identity, named near distance, and the slaved Get_Translation
   form. No improvement. Repeated all 256 on the winning ratio baseline:
   no further improvement. This is not a blanket rejection of real headers;
   it closes these particular combinations on these two banks.
2. **Component boundaries, 256 combinations.** Separate real scalar addition
   helpers independently at the four initial/live source/target sites,
   WB source-XYZ-before-target-XYZ ordering, ground-arm Z order, scalar pitch
   return and template/non-template helpers. No improvement; many restore
   unwanted X/Y register candidates. Repeated all 256 on the alternate
   live-target-height baseline below: no further improvement.
3. **Complete Look_At provider, 24 combinations.** Actual body from
   `Code/Libraries/Source/WWVegas/WWMath/Matrix3DUnmatchedSSE.cpp`, its real
   two-argument Rotate_X dependency, before/after parent, ordinary/noinline,
   direct/banked translations and direct/banked pitch. Full visible provider
   best was 0.8707066376/4,250 bytes. Unlike older reduced/stub trials this
   tests the actual body. No helper provider was rehomed or admitted.
4. **Shaker overload/lifetime, 72 combinations.** Six real call forms (including
   angle/receiver captures and sequential sine/cosine results), six orders of
   actual helper locals, and call-block scope. No improvement. Repeated on
   both new baselines (another 144 variants): no improvement. Final Rotate_Y
   stays solved; the shaker cannot inherit that fix by the same spelling alone.
5. **Used expression values, 256 combinations.** Bits in order: ground ratio,
   object height, squared distance, shaker frame time, ground target height,
   live target height, shake X/Y inputs, adjusted pitch. Best minimal choice
   is `10000000`, only the ground ratio. No unused declarations, artificial
   calls, padding, barriers, volatility or compiler-option changes.
6. **Bounded permute on incoming bank:** 1,106 trials, five minutes, no gain.
   `permute.txt` records the result. The new ratio baseline has not had another
   random permutation run; do not misreport this as a test of the new bank.

Total: 1,520 generated factorial cases plus the bounded permuter. All factorial
cases compiled. Do not repeat these combinations without a new interaction.
Previous compiler-build/flag, class layout, alias escape and faithful-WB
explanations are recorded in r53–r66; those were read, not blindly rerun here.

## Remaining work and alternate

Our mnemonic-aligned diagnostic counts 74 changed instructions (33 structural,
41 operand), versus 75 on the incoming bank. This metric is different from
r66's alignment script; compare within the provided harness. Regions remain:
pitch-matrix scheduling around +0x40A; angle additions around +0x4EA; delayed
initial XY stores +0x515..549; live matrix/translation scheduling +0x6EC..7C8;
realZoom pitch lifetime/store order +0x86B..8B3; shaker Rotate_X ordering
+0xC02..C92. The ground arm's load ordering and the 1.0 reload improved, but the
live arm still has a different schedule. Final rotation and the tail stay exact.

`fewer-instructions.patch` changes the new bank to the alternate using only
the named live target height (no ground-ratio local). That emits 4,298 bytes,
score 0.9628554444, and 70 normalized changed instructions (24 structural,
46 operand). It is worth retaining for regional recombination; its lower
instruction count does not make it an exact recovery. The adjusted-pitch local
is unnecessary for this alternate. Its complete diagnostic is retained too.

Continue this same body. A useful next target is the actual instruction owner
and scheduling dependence behind the translation/pitch stores, using these
new expression-lifetime baselines. The current score-best bank still has r66's
compensating by-value vector helpers. There is no missing callee blocking work.
Before production admission, reconcile the known neutral descriptor/caller
name and the canonical Coord3D::lengthSqr declaration as earlier notes require;
neither issue justifies pretending this partial body is matched.

t=22 model=gpt-6-astra
