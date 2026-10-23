# Locomotor 0x001E7ECA: source-boundary trials, 22 October

The existing 0.975 bank remains the best starting point, unchanged. No Code
body, pin or function row was added. The standing assignment is still this
1563-byte body, not another queue. Model: gpt-6.1-sol.

Inputs: BFME 2 e347d0a5d661bcd5293c4f4c9281440063625c43; committed and checked-out
BFME 1 37c3022de1ab944c7ffe536440d637dc8199091c. The updater lock belonged to
claudeb3 and was under six hours old, so the runner's freshness exception
applied. This seat neither updated the pointer nor wrote a freshness-success
marker. The existing marker still names cea1e9734dc0c5355613b61226fe3cc2faab4aa4.

Read the previous verdicts with `pick-hard --rva 0x1E7ECA` and the linked
20/22 October handoffs before these trials. In particular, scalar NULL
spellings, local-numbering scans, terrain throw/const, ordinary helper
visibility, compiler profiles/settings and the MI receiver shape were already
refuted and were not treated as new independent hypotheses here.

## Results

2315 variant attempts: 2067 successful compiles, 248 compiler failures.
Scratch compiles used `build.compiler_command` with distinct output objects;
none called `build.compile_source` or modified the compiler. Eight workers
compiled each family. `families.json` records actual counts; some inherited
scratch family labels overstate their counts.

The inherited scorer ignores relocated values and branch displacement changes,
stops at RET 8, and compares 1527 code bytes. It is a diagnostic, not a byte
gate. Baseline: 1567 bytes including switch table, score 12, comprising case 1
score 8, case 6 score 4, everything else zero. Baseline raw symbol SHA-256
prefix: e1e741da4121.

| Family | Attempts | Compile failures | Best score | New hypothesis |
| --- | ---: | ---: | ---: | --- |
| pointer-paths | 123 | 12 | 12 | Null-preserving MI/virtual-base pointer adjustments, template conversions and __noop boundaries |
| pointer-paths-rtti | 12 | 0 | 17 | Repair the nonpolymorphic dynamic-cast probe with a polymorphic base |
| receivers768 | 192 | 0 | 12 | Receiver reference aliases combined with pointer-to-virtual-member call forms and scope |
| once128 | 128 | 0 | 12 | Once-only loop and switch boundaries around the sea arm/layer query and ground/query arm |
| querylife512 | 512 | 0 | 12 | Reference-bound result temporary, highest/position aliases, range and loop/geometry lifetimes, factorial combinations |
| dispatch192 | 96 | 96 | — | Native free-function __thiscall callbacks are rejected by VC7.1 (C4234); not evidence against dispatch lowering |
| dispatchsi96 | 96 | 12 | 14 | Supported single-inheritance member-pointer union adapters for explicit vtable dispatch |
| zerobits300 | 300 | 0 | 7 | Floating storage gives NULL a different optimizer type/alias path |
| annotations256 | 256 | 128 | 12 | Global receiver cv, nothrow/noinline, return types and __w64 combined; __unaligned/__restrict rejected (C4235) |
| raiizero216 | 216 | 0 | 12 | Empty, throw(), clearing and virtual destructors around the normal NULL, before/inside each query |
| zeroassume192 | 192 | 0 | 7 | True zero facts on floating storage, pointer aliases and inline helper boundaries |
| casefacts144 | 144 | 0 | 12 | Derive zero from the selected mode, including conditional/switch expressions and true assumptions |
| virtualvis48 | 48 | 0 | 12 | Visible ZH default ground/layer bodies, inline/noinline, before/after parent, merged terrain class |

Every successful pointer-path, querylife, casefacts and virtualvis variant
except the RTTI subfamily is raw-byte identical to baseline. Receiver and
once-only-control-flow variants can change other instructions, but neither
affected region improves. Empty RAII lifetimes likewise do not split the web.
Case-derived zero values fold back into the same web; keeping a saved mode
alias does not defer that folding far enough.

This covers control flow/loop entry, variable lifetime, types/layout and
callee visibility concretely. Existing compiler settings/profile trials from
the earlier handoff remain refuted; the command used here was checked to be
the bank's /O1 /G7 /arch:SSE /MD /EHsc with the same header paths.

## Useful diagnostic, not a better bank

`float-zero-diagnostic.patch` reconstructs zerobits_01_100 from base.cpp
(zero context; use `git apply --unidiff-zero` if applying with git). A
union's float member is initialized to +0.0f and its pointer member is passed
as the sea layer normal. The two underwater zeros then become literal
pushes and the layer vptr stays in EDI, matching those retail decisions.
However, the normal itself is pushed from memory: c2 emits XORPS plus a
MOVSS store for the union. Total body 1571 bytes, eight over retail. Its
score 7 (case 1 = 3, case 6 = 4) is lower only because the scorer counts
instructions rather than penalizing those longer replacements. Do not
replace the straightforward 1567-byte bank with this storage-punning probe.
True __assume facts either retain this extra storage or fold back to the
original web; none produces retail's three immediate pushes.

`baseline-align.txt` and `float-align.txt` are fresh `align_diff.py` results
with BFME_OBJSTORE=off. They confirm raw sizes 1567 and 1571, respectively.
The tool disassembles the trailing jump table as code and reports an aggregate
delta one byte larger than the raw length difference; use the raw sizes.
Relocation and branch noise in those logs is not an additional defect.

An independently matched analog was also inspected: ParticleSystemFXNugget
reallyDoFX 0x001E19E8, 2804 bytes. Retail 0x001E211A and 0x001E21A8 each
zero ESI and push it three times before terrain slot 19, then retain it
across the call. Its rowed source passes three literal zeros. This refutes
a general rule that a terrain virtual call cannot share a zero register;
it does not explain this Locomotor function's allocation.

The visible default terrain bodies came from the ZH source at
GameEngine/Source/GameLogic/Map/TerrainLogic.cpp:1438 and :1450, corroborated
by the BFME 2 rows 0x0027CE9A and 0x0027CEBC. This is callee-visibility
evidence only: the normal virtual dispatch remains, and the default body
does not establish the dynamic receiver's behavior.

## Resume

All 22 direct callees were already resolved. There is no missing-function
prerequisite to claim. Remaining differences are unchanged: case 1 globally
allocates zero to EDI and spills/reloads the vptr; case 6 defines EDI zero
before ground's NULL instead of at the mask ctor. The earlier allocator
trace explains the costs but not a source-level way to split those uses.

The next concrete diagnostic is to trace the earlier split/reload decisions
joining case-6 BB79 (ground NULL) to BB81 (mask/query zeros), using the
unchanged baseline and the preserved 22 October debugger scripts. For case 1,
compare the floating-storage probe's operand identities and the baseline's
zero piece; the probe proves that excluding one use yields the right vptr
allocation, but its memory traffic still needs an explanation in real source.
Do not repeat the families above or patch allocator costs as a solution.

To reproduce: copy these .py.txt files to build/locomotor-zero-cfg/ without
the .txt suffix; copy the current bank to base.cpp; extract retail.bin with
build.read_target_bytes(0x1E7ECA,1563); then run a selected generator. The
scorer's short hash is of raw, unresolved symbol bytes. The claim was
released at handoff; claim again before continuing.

## Checks

`tools/check_csv.py` passed both before and after the trials: 97957 function
rows, 15928 pins and 1386 data rows. The unchanged LocomotorHeight.cpp passed
`find_declared_unmatched.py`; the published link index was fetched. Fresh
`align_diff.py` runs confirmed both diagnostic object sizes. No source body
was accepted as matched, so no byte-gate success is claimed.

`tools/progress.py origin/master` reported +0 byte-matched, authored C++, and
linking bytes. This commit preserves the failed hypotheses and the useful
allocation diagnostic, rather than claiming coverage or link improvement.
