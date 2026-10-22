# FXShaderGeometry::Init: locate the four edge reloads

2026-10-22, codexb2. Target `0x0018C84E..0x0018D16B`, 2333 bytes.
BFME 2 input `913f4cec96`; verified BFME 1 pointer and clean checkout
`42bba2ddbd5cb895d99293583891d3b7315fa49e`.
Flags: `/I. /O1 /G7 /arch:SSE /MD /DNDEBUG /EHsc`.

The best bank is unchanged: **2333 bytes, nine differing bytes in seven
instructions at +0x707..+0x721, EH EXACT, zero unresolved calls**, score
`0.9961423060437206`. Only its handoff comment changes. A fresh private
compile reproduces the previous bank's bytes and relocations. This is
compiler evidence for the unfinished assignment, not an exact recovery.

## Continue here

The previous handoff's splitting/rebuild question is answered. C2 inserts
the diagnostic's extra values on an edge into a successor with multiple
predecessors. They are not globally removed from the bank's active set.
Next map the diagnostic successor's **five predecessor blocks to source
paths**, and isolate this join in a small probe. Seek a spelling that
retains the edge liveness through allocation while keeping the native
two-bone P/N stores in their arm. Mapping those five paths and a minimal
probe have **not** been done. Complementary reduction of the remap base's
priority remains another angle. Do not repeat the families below.

There is no identified missing-callee prerequisite. The short-vector
constructor is solved. WorldBuilder supports P/N inside the two-bone arm;
see the prior `fxinit-live-20261022` and `fxinit-wbinline-20261020` handoffs.

## New compiler evidence

All observations use stock MSVC 13.10.3077 c2, base `0x10700000`, with
read-only breakpoints/watchpoints. Eight completed traced objects reproduce
their ordinary controls' complete Init bytes **and relocations**. The
diagnostic is still `pn_300000`, from
`../fxinit-schedule-20261022/pn_300000.patch`: P/N at the common tail,
2326 bytes, incorrect scope and unsuitable for landing.

1. The pointer split is **created and priced in round 1**, then colored in
   round 14. Bank candidate 175/serial 647 gets cost 36 (6 times 6);
   diagnostic 174/647 gets 54 (6 times 9). The initial remap-base priorities
   remain 60 versus 48, as established in the earlier cost handoff.
2. At c2 RVA `0x8AB54`, the reconstruction's active set is empty;
   `0x8B2AA` rebuilds it to 53 bank / 52 diagnostic candidates by `0x8AB66`.
   `0xAFAC0` adds none by `0x8AB85`. Both T/B cursor records are already
   globally active in both builds before the split is priced. Their absence
   from the bank's remap-block list is a local liveness difference.
3. The selected remap block (`C726E0` in these runs) has identical bitsets
   at offsets +48/+4C/+50 on the first split entry in both controls.
   Before rebuilding, only an opcode `0x2C7` marker is added. Rebuilding
   adds actual reload tuples: the bank ends with its P-null conditional;
   the diagnostic ends with a jump to shared successor `C727A8`.
4. A watch on the diagnostic tangent reload's opcode catches its creation
   at `0x5A611`, called through `0x7C28A <- 0x8BB3F <- 0x8B9C6 <-
   0x8AD34 <- 0x8AB66`. The call at `0x8BB3A` invokes `0x7C20C`.
   These are observed RVAs, not claimed original compiler function names.
5. Four calls at that site occur for edge `C726E0 -> C727A8`; the bank
   has none for the selected block. Before insertion, predecessor live-out
   is `[7,27,131,146]`; successor live-in is
   `[7,27,109,128,129,130,131,146]`. The difference is exactly:

   | Candidate | Meaning from the previous same-run IR identification |
   | --- | --- |
   | 109, serial 0 | literal 2 |
   | 128, serial 645 | tangent Y cursor, initialized from tangents + 4 |
   | 129, serial 0 | literal 0 |
   | 130, serial 644 | binormal cursor |

   The successor's predecessor blocks are `CA4CF8`, `CA4C08`, `C72550`,
   `C72230`, `C726E0`. C2 `0x7C1DF` returns for zero/one predecessor,
   otherwise visits predecessor edges, computes missing values around
   `0x7C313..0x7C334`, and reaches the reload emitter above.

The extra loads therefore enter before the cost calculation and explain
the enlarged list. This does not prove that reproducing one load alone
will fix allocation. Candidate IDs are reused: compare event, round and
serial together. Raw symbol word 7 in `show_blocks.py` is **not** a
candidate serial. `observations.json` preserves selected timeline events,
block tails/new tuples, operands and all four edge events.

## Source trials and exclusions

Private objects, normally eight workers per family. Counts are generated
combinations, not unique bodies. Total **11,232 attempts, 11,020 compiling
and resolving within the scoring row, 140 compile failures, 72 extent or
relocation refusals**. None improves the bank. Per-family byte, alignment
and remap-region scores are in `measurements.json`.

| Family | Attempts | Tested explanation |
| --- | ---: | --- |
| branchprep | 4080 | Stable address preparations on both normal/basis branch paths; eight-choice subsets, placement, order, pointer/integer types |
| pnselect | 432 | Nullable selected P/N pointers, prebiased pointers, scope and initialization; deferred copies preserve the original condition |
| earlyadvance | 432 | Advance vertex/index before UV, basis or bone dispatch while preserving old values |
| midadvance | 864 | Advance within the two-bone arm at four boundaries and bypass the tail |
| midadvancefix | 864 | Corrected version of the same family; all compile and resolve |
| desctypes | 2048 | Nine descriptor getters as signed values or const references, plus signed offset fields |
| loopentry | 1728 | Factorial forms for texture, vertex and pass loops: for, while, guarded do, break, explicit increment, goto; scope and comparison polarity |
| branchmerge | 720 | Remap/weights on two equivalent-expression paths under T/B/P/N/basis/FVF tests, seeking a join that later collapses |
| recombine | 64 | Selected-pointer regional winner crossed with offset references, four remap spellings and moving each P/N copy back into the arm |

The first midadvance generator applied its label insertion too broadly:
140 variants failed C2045, `AdvancedVertex` redefined. Those failures do
not exclude a hypothesis. `midadvancefix` inserts the tail label before
adding the new arm and reruns all 864 successfully; the best is unchanged.

`pnselect_010101` obtains the desired remap register roles, but is 2300 B,
changes frame homes and has 1038 differing bytes overall. Its two remaining
aligned remap differences are frame offsets. Recombination keeps those
large surrounding changes and does not improve the bank. The selected
pointers can be null on skipped dispatch paths, so this diagnostic differs
from the older unconditional-tail diagnostic.

`desctypes_002_10` returns the location offset by const reference. It keeps
2333 B but has 26 differing bytes / 12 operand lines. One remap SIB operand
now agrees; the remap-base/link register roles remain wrong. The nominal
six-line remap score in branchmerge comes from a changed block alignment
and is not evidence of correct roles. Patches retain the two useful
regional candidates without replacing the better bank.

Control flow/loop entry, lifetime/advance placement and descriptor types
received concrete trials here. Earlier callee-visibility, compiler flags,
WB/source-shape and layout trials remain recorded in the linked handoffs;
there is no basis to repeat them unchanged.

## Checks and reproduction

Startup `check_csv.py` passed (98,064 functions, 15,855 symbols, 2,128 data).
Published-object fetch completed. BFME 1 freshness was skipped under the
runner's active lock owned by `claudec2`; the clean verified pointer was
retained. No success stamp or another seat's lock was changed.

`verify_bank.py` checked fresh resolved bytes, EH EXACT and all eight trace
controls; see `bank-verification.json` and `bank-align.json`. No production
source, pins, compiler or gates changed; this partial cannot pass the
exact-body gate and is not placed in `Code/`.

Restore `*.py.txt` here into ignored `build/fxinit-split22/`. They use
`../fxinit-schedule-20261022/search.py.txt` restored as
`build/fxinit-seat22/search.py`, and that handoff's `wdbg.py.txt` restored
under `build/netpacket-20261022e/`. Generators run with no arguments;
tracers take source and private object paths. `recombine.py` needs the
pnselect generator's selected source first. Fresh traces depend on the
recorded inputs and memory layout; rediscover block addresses if they move.
`verify_bank.py` additionally expects the preceding ordinary control objects
under `build/fxinit-live22/` and `build/fxinit-seat22/`; recreate controls
from the bank and recorded diagnostic if starting in a clean checkout.
