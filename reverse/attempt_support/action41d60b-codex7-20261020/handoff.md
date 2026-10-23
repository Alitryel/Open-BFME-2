# ActionManager 0x0041D60B: provider refresh and stack-allocation trials

Input: BFME2 `d5f3f0415231815c63cde4426e3997582f7713f8`, BFME1 checkout
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`; MSVC 7.1, bank's
`/O1 /arch:SSE /G7 /MD /GX` settings. Owner `yasinschroeder-codex7`,
model `gpt-6.1-sol`, 2026-10-20. This remains an unrowed partial.

The assigned Apt body 0x006EFBC0 and first fallback 0x0043003C were held by
other contributors. This seat claimed 0x0041D60B and read its history through
`/opt/runner/pick-hard --rva 0x41D60B`. The initial ledger check passed. BFME1
freshness was deferred under the runner's active update lock owned by codex5;
no submodule update or successful-freshness timestamp was invented. Published
link index fetch succeeded. Broad sweeps were skipped under the assigned lane.

## Verified bank maintenance

The initial bank has four unresolved helper declarations against the current
ledger. The bank now calls existing providers, without adding pins:

| Former declaration | Existing provider | Target evidence |
| --- | --- | --- |
| `Rva001E46E1::rva001E46E1(Object*)` | `Locomotor::getMaxSpeed(Object*) const` | direct call 0x001E46E1; 356B row and WB identity |
| `Object::rva002615E3(Coord3D*) const` | canonical `Rva000CBA20::distSq(Rva000CBA20Point*)` | 0x002615E3 reads this+0x38/+0x3C and argument's X/Y prefix; canonical XYDistanceCallView.h |
| `TerrainLogic::rva0027F108(Coord3D*,float,bool,int)` | `BfmeThingCME::rva0027F108(void*,float,int,int)` | direct call 0x0027F108, existing 52B provider; pushed arguments remain loc/5.0f/1/1 |
| `BfmeFixedStorage0004543D(int,int,int)` | `Rva0006EE7A(int,int,int)` | direct call 0x0006EE7A, existing 66B two-bit ctor; fixed 28B storage |

The 32-way provider-control sweep leaves each baseline's raw primary body
unchanged (including its size, frame and instruction sequence). The fully
refreshed bank has zero unresolved references with `allow_weak=False`, no
relocation masking, and all 90 direct callees in retail order. Diagnostic
fitness is **0.96751**. This is a declaration/continuation repair, **zero matched
C++ bytes**. It does not establish complete data, switch or byte identity.

## Baselines and metric limits

| Source | Actual symbol extent | Instructions | Frame | Diagnostic mnemonic-aligned differences |
| --- | ---: | ---: | --- | ---: |
| Initial farm bank; refreshed bank | 3709 | 1033 | 0x2D8 | 51, including 40 stack references and 4 structural edits |
| Pre-farm bank at a5a009c0fd | 3709 | 1034 | 0x2C4 | 51 |
| Natural bank at 125d7a88ce | 3712 | 1035 | 0x2C4 | 43: frame plus 42 stack references |
| Retail | 3709 | 1035 | 0x2B4 | 0 |

The natural source has no initial compiler barrier or equal-arm ternary. Its
prior call/branch/table/EH audit is in crack-e/crack-j; that audit must not be
silently attributed to the later farm source. Farm's nominal score 0.937 and
earlier scores were measured differently. The refreshed score uses
`variant_search.non_exact_fitness` after strict relocation resolution.
`compile_function` returns only the requested 3709B, so the receipt's raw
object-symbol extent must also be checked. No source longer than retail was
treated as exact, and no padding was introduced.

## New experiments: 408 isolated compile trials

All generators and receipts are preserved here. No production source or shared
compile-cache object was changed. Unique scratch objects were compiled with
`build.compiler_command`, eight concurrent compiler processes, no helper agents.

- 64 factorial special-member controls: explicit Alive ctor/dtor, relationship
  dtor, mask copy ctor, base copy ctor and filter copy ctor. All emit the same
  primary bytes as the initial bank.
- 18 inline-origin controls: whole healing/terrain cases and the third switch;
  whole-function inline wrappers were refused by the compiler (9B entry), not
  successes. Smaller case helpers really inline and change frame packing.
- 254 factorial combinations of seven whole-case helpers on both farm and
  natural baselines: geometry, placement, closest65, closest140, healing,
  terrain63 and terrain72. No exact result or retail 0x2B4 frame. Some natural
  combinations preserve all 1035 mnemonics with frames 0x2A8, 0x268 or 0x24C,
  but still 42 wrong stack references. A smaller frame alone is not progress.
- Seven compiler-build controls: RTM baseline, hash-pinned VC71 SP1 and DDK
  4035 on farm/pre-farm/natural. DDK matches RTM; SP1 is inert on natural and
  worse on farm/pre-farm. Retail's Rich header supports RTM, as recipes.md says.
- 32 mask/filter factory controls: direct six-argument ctor versus initializer
  protocol; named/unnamed return-by-value filter factories at individual/all
  sites. No improvement. The alternate ctor's unresolved symbol is diagnostic
  only and was not added to the bank or ledger.
- 32 provider-declaration controls described above. This resolves the current
  bank's concrete declaration drift, without changing native instructions.

## Do not repeat; next investigation

The prior history already disproved broad scope/declaration permutations,
uniform mask types, visible helper/geometry/query bodies, named healing Alive,
whole-function EH changes/dead throw, and the Coord3D member-mutator lever.
This session additionally rules out special-member visibility alone and the
seven independent whole-case inline origins tested in combination.

The precise unresolved problem remains selective stack coalescing: retail
shares the placement Alive with healing Alive, placement two-bit mask with
healing one-bit mask, and placement filter with the late case72 filter temp.
Current compiler source shapes do not reproduce that partition. Control flow
and loop-entry alternatives, local lifetime/scope, type/layout, callee
visibility/inlining and compiler settings have each received concrete trials
across the recorded sessions; none is an impossibility proof. The tested
whole-case inline origins do affect allocation, so a narrower inline-origin
model based on original WB call boundaries remains a possible next direction.
Do not restart the same 254 combinations or claim a missing callee now.

To reproduce these experiments, copy the `*.py.txt` files to their `.py` names
in `build/action41d60b-codex8/`. Seed `trial.seed` from this input commit's bank,
not a later farm edit; materialize `pre-farm.cpp` from a5a009c0fd before the
profile controls. The generators retrieve the natural bank at 125d7a88ce.
`receipts.json` maps labels to deduplicated result objects and includes the
strict final audit. The scorer's masking/alignment is explicitly diagnostic;
only a full gate can admit a matched body.


## Preparation recovery (2026-10-20)

The replay conflicted with upstream `3abdb07125`, which restores the cleaner
1035-instruction candidate with audited branch/table/EH relationships. The
ActionManager claim is now held by another seat, so recovery keeps that upstream
bank byte-for-byte and preserves this commit's refreshed farm candidate as
`farm-refreshed.cpp.txt` beside its receipts. The provider fixes and all trial
evidence remain available; this replay does not replace the cleaner canonical
bank or claim an exact body. Compare candidates by their actual instruction
sequence and strict relocation audit, not the historical scores alone.
