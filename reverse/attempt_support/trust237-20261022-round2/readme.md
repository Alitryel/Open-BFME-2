# 0x237D3D: range predicates and real loop-alignment control

Target: `?Rva00237D3DCheck@@YAHXZ`, RVA `0x00237D3D`, extent 226.
Inputs: BFME2 `9c7668fc281a5fe98b2c9652bc63a9e6d3c18e8e`, BFME1
`37c3022de1ab944c7ffe536440d637dc8199091c`, MSVC 7.1 RTM.
Model: GPT-6.1-sol. Continuation of
`../trust237-20261022/readme.md`; no Code source, ledger row or pin changed.

## Improved bank

The new bank is `best.cpp.txt` (partition variant p0408), compiled with
`/O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc`. It emits 219 bytes and matches the
relocation-masked retail prefix through +0xCC, including the previously
missing `mov ebx,eax` and `xor eax,eax`. First difference is now +0xCD,
versus +0xC3 for the previous 208-byte bank. Positional differences fell
from 27 to 21; aligned retail mnemonics rose from 68/86 to 69/86, with two
structural regions instead of three. Bank score: 69/86 = 0.802326.

It calls WinVerifyTrust once, keeps its status across LocalFree, and returns
1 through `(u & 1u) <= 1u`, an always-true predicate for the target's unsigned
32-bit long. This artificial expression is a compiler-shape diagnostic, not
an assertion about original source. The file/data sizes (16/44), GUID, calls
and accesses come from retail; the layout is unchanged from the prior bank.
The real SDK's newer 48-byte WINTRUST_DATA remains unsuitable, as the previous
session demonstrated. `base.cpp.txt` preserves the simpler 208-byte source.

`comparison.txt` records the remaining tail. Retail has sixteen 0x90 bytes
at +0xCD..+0xDC, then `inc eax; pop esi; pop ebx; leave; ret`. The candidate
has a live byte-sized range comparison, pops and sbb/inc instead. It has no
NOPs and is not an exact match. DIR32 relocations were masked from retail
for diagnosis; REL32 calls were mapped to memset=0x6291AE and the actual
WinVerifyTrust thunk=0x655652. No byte-admission or full conversion gate
passed, and none is claimed. `variant.py` independently recompiled both
saved sources and reproduced their measurements.

`branch-region.cpp.txt` (p0217) aligns 70/86 mnemonics but has an earlier
first difference (+0xCB), 23 positional differences and three structural
regions. Keep it as a regional alternative, not as the best prefix bank.
The chosen p0408 raw body hash is
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.

## Hypotheses tested; do not repeat unchanged

Before editing, read this RVA's history with `/opt/runner/pick-hard --rva
0x237D3D`, the preceding handoff and the relevant recipes. Earlier trials
had already rejected null volatile stores, equal-arm trust-call ternaries,
explicit assembly NOPs, SDK-layout substitution, ordinary flag changes and
many status/cleanup variations. This continuation's new hypothesis was that
narrow Boolean/range lowering and optimizer control-flow remnants could
retain the status and part of the unconditional return tail.

All 3,662 target matrix compilations succeeded, producing 316 distinct raw
bodies; none contained any NOP instruction. These are finite families, not
a proof that every C++ spelling is impossible. `summary.json` and
`grouped.tsv` retain counts and grouped scores.

| Family | Compiles | Distinct raw bodies | Choices |
| --- | ---: | ---: | --- |
| boolean | 1152 | 151 | 24 always-true predicates, 8 return/control shapes, predicate before/after LocalFree, direct/inline/forceinline |
| debug | 128 | 29 | Z7/Zi/Zd/ZI and related options, eight predicates, two timings; ZI uses Od |
| bitfield | 256 | 7 | eight signed/unsigned/bool representations, eight result shapes, two timings and scopes |
| assume | 150 | 26 | 15 valid always-true predicates, five assume/control shapes, two timings |
| context | 24 | 3 | baseline/OR1/narrow source before/after VersionDestructor.cpp or VersionInitGlobals.cpp, home flags/G7 |
| partitions | 1440 | 79 | 15 range predicates, eight branch/loop/goto forms, three result declaration timings, G6/G7, direct/forceinline |
| loops | 512 | 68 | 16 always-one-iteration loop shapes, O1/O2, G6/G7, four declaration timings, flat/nested scope |

The G6 range-test variant is the new regional winner. G7 changes scheduling
and loses the matching xor placement; p0409's forceinline version is equal
to p0408. The complete same-unit contexts did not improve the tail.
Declaration timing/scope, bitfield layout and callee visibility were tested
in combination rather than merely one at a time. Debug settings did not
expose a retained NOP region. An initial debug setup shared vc70.pdb and
combined O1 with incompatible ZI; the saved driver uses a private /Fd and
Od with ZI. Those setup errors are excluded from successful counts and are
not evidence against a source shape.

## Correction to the older NOP conclusion

Ninety-six separate control probes varied four real loops, G5/G6/G7,
O1/O2 and four arithmetic prefixes. `loop-alignment.cpp.txt` (loop088)
emits a single-byte 0x90 at +0x0F, preceding its loop head at +0x10.
The back edge targets +0x10. Thus MSVC 7.1 **can emit single-byte NOPs**
for loop alignment; the older blanket impossibility claim in
`../worker_237d3d_20261020.md` must not be carried forward. This witness
does not explain sixteen consecutive NOPs or the target's position.

A direct scan of the complete 8,096,994-byte retail .text found only one
run of at least eight 0x90 bytes: these sixteen bytes at RVA 0x237E0A.
Its successor is RVA 0x237E1A (address modulo 16 = 10), so this is not
ordinary padding to a 16-byte boundary. The exact scan result is in
`summary.json`; no target image was modified. A post-link edit remains a
possible interpretation, not a proven fact or permission for an assembly
hatch. The 512 semantically one-iteration target loop variants did not
reproduce this alignment effect.

## Reproduction and next continuation

Copy `*.py.txt` to `build/trust237-round2/` with the `.txt` suffix removed,
and copy `base.cpp.txt` there as `base.cpp`. Run from the BFME2 root:

```
python3 build/trust237-round2/search.py boolean
python3 build/trust237-round2/search.py debug
python3 build/trust237-round2/lowering.py bitfield
python3 build/trust237-round2/lowering.py assume
python3 build/trust237-round2/context.py
python3 build/trust237-round2/partitions.py
python3 build/trust237-round2/loops.py
python3 build/trust237-round2/loop_probe.py
python3 tools/variant.py build/trust237-round2/best.cpp '=?Rva00237D3DCheck@@YAHXZ' 0x237D3D 226 _memset=0x6291ae _WinVerifyTrust@12=0x655652
```

For the last command also copy `best.cpp.txt` as `best.cpp`. Each matrix
uses eight parallel isolated compiler_command/subprocess calls; none calls
build.compile_source or writes a shared match-cache object. Grouped scores
are diagnostic, not verification receipts.

Continue this assignment. The remaining concrete task is to explain the
sixteen-NOP span and return-tail order. The real loop-alignment witness is
new evidence for investigating compiler alignment conditions; no matching
target source has been found. Keep both region winners and the simple
baseline available rather than rerunning the same finite matrices.

Session checks: ledger integrity passed before work; BFME1 checkout was
clean and equal to the committed verified pointer. Freshness update was
skipped under the runner's live shared lock owned by claudec2; no success
timestamp was fabricated. Final checks and publication state are recorded
in the runner result. Release this claim after banking so another seat can
resume safely. Authored exact C++ growth remains zero.
