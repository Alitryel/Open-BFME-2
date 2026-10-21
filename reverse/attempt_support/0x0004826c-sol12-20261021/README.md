# gatherDebugStats: identify early null substitution

Continue only `?gatherDebugStats@W3DDisplay@@UAEXXZ`, RVA `0x0004826C`,
retail boundary `0x4826C..0x49271`, 4101 B. **Not exact.** The canonical bank
still emits 4101 B / 1237 instructions / zero structural regions, with 13
nonrelocation stack-displacement bytes. Its substantive source is unchanged;
rebaking updates only the date. Preserve it over the slot-correct sol10
alternate (4101 B / 1239 instructions / 11 diagnostic bytes / one region).
No Code, ledger, pin, header, compiler or verifier changes; no padding.

## Inputs and checks

Session started 2026-10-20 23:53 UTC after pull at BFME 2 `ebfb4fa883`.
AGENTS.md, served RVA history, relevant handoffs and recipes read; claim
acquired. Ledger passed: 97648 functions, 15929 symbols, 1136 data rows.
Published link index fetched: 23174 objects. Clean BFME 1 verified pointer
`68c5ce2789e974f36b6c742d57437d157bc159e9`, successful freshness receipt
2026-10-20 15:49:03 UTC, within 24 hours; no update due.

Input bank SHA256 before date-only rebanking:
`543c60098a558083c8e25ac900f5643eea7c1b5e42eb3e4b4bf286b26aa3454c`.
Original c2 13.10.3077 SHA256:
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
Flags `/O1 /arch:SSE /G7 /MD /EHsc`; model gpt-6.1-sol.
Scratch `build/gather-sol12-20261020/`. Eight isolated compiler outputs per
grid, using compiler_command rather than compile_source/shared-cache writes.

Fresh official explain_mismatch reproduces 4101 B and the unresolved
MemoryPool REL32 classification; first nonrelocation difference +0x64.
Official align_diff reproduces 1237/1237 instructions, zero structural
regions and zero size delta. Neither is a successful full byte gate.
Separate completed control compiles reproduce bank 13 bytes, throwing base
44 bytes, alternate 11 bytes/one region, pointer control 4104 B/two regions.
Relocation masking and mnemonic alignment are diagnostics, not acceptance.

## New finding: exact early pass and operand write

Prior sol11 native evidence already proved the alternate's third draw reference
is a duplicate spill store removed after stack packing. This continuation
locates why the plain pointer control fails to preserve both identical copies.
The control differs from the alternate only in `if(p)` versus
`if((unsigned)p>0)`; it has the same two assignments to draw and obj.

Read-only Wine debugger captures of unmodified c2 show:

1. Current function context is at global `0x108a9128`; context +8 points to
   the block-list container. Block next +0, first tuple +0x1c, last +0x20.
   Operand lists link through +0. Tuple source +0x28, destination +0x2c.
   The third tuple field is opcode-specific and must not be treated as a
   generic operand. Symbol name is through record -> SYM -> name (+4).
2. Before early flow construction `0x10760539` (call `0x107afff2`), both
   sources have one flat list of 1806 tuples. After return `0x107afff7`,
   both have 153 blocks / 1740 tuples, and both null-arm copies still read p.
3. During the optimizer driver `0x1075f923` (call `0x107b0001`), its first
   pass `0x10766afb` (call `0x1075f94b`, return `0x1075f950`) substitutes
   literal zero into the pointer control's null-arm copies. The unsigned
   alternate keeps register p. After the driver both have 154 blocks /
   1583 tuples; before allocation both have 153 blocks / 1761 tuples.
4. A hardware watch on the null-arm draw tuple's source root confirms the
   actual write: tuple `0x00c35954`, source field `0x00c3597c`, old operand
   `0x00c35934` referencing p, new operand `0x00d5d008`, type 7 and value 0.
   Store instruction `0x1075ac02: mov [edi+0x28],ecx`; debugger stops just
   after it at `0x1075ac05`. EBP and EDI both identify the tuple. The driver
   discovers this tuple by names rather than assuming these heap addresses.

Raw watch registers and stack words are retained in native-evidence.json.
The static caller at `0x10763847` invokes `0x10761d9e`; instruction walking
through `0x10761f11` / `0x10761e41` and replacement through `0x1076dac9`
are useful next disassembly leads. Raw code-looking stack words are clues,
not a proven full unwind. Pass roles are inferred from observed effects;
there is no c2 PDB. Snapshots intentionally quit at the requested boundary;
completed control compiles separately verify emitted results.

The exact pointer control retains different-register draw stores and a join:
`je null; load obj; store eax; jmp join; null: store ebx; xor edi,edi`.
It is 4104 B. Do not generalize prior statements about other plain-pointer
contexts removing the join to this exact control. The unsigned alternate
keeps identical stores, but still has `jbe; load; jmp; mov edi,eax` where
retail has direct `je TERRAIN; load`. Its residue is +0x912..+0x91f;
from +0x926 onward it is at retail's positions with correct stack slots.

## 2048 successful regenerated source trials

New hypothesis from the native finding: copies lowered after early facts
might keep the needed p reference through packing without extra emitted code.
Every generated source was checked against its compiled input and its literal
set against the bank (excluding the added linkage-language string C).

| Family | Count | New interactions and result |
| --- | ---: | --- |
| copylower | 512 | Four true 4-byte copies independently direct versus intrinsic memcpy; lookup/selection copy temporaries, final guard, initial test and char contract. All 64 copy choices inert for a given remaining context. Best unchanged 11 bytes/one region. |
| lateintrinsic | 1024 | Eight invertible unsigned rotate/byteswap word expressions, four independent copy positions, initial test, final guard and char contract. Best unchanged 11/one region; some forms retain extra instructions. |
| typedcopy | 512 | Four object-representation paths through float memcpy, MSVC float union, two shorts or four bytes; four copy positions crossed with test/guard/contract. Best unchanged 11/one region. Float union is a diagnostic MSVC extension, not a target layout claim. |

No new zero-region candidate. Source-stream hashes, histograms and best cases
are in validated-results.json; completed control bytes/instruction windows in
controls-evidence.json. Counts include repeated instruction streams. Raw counts
for bodies with length changes include downstream shifts, not independent bugs.
Prior declaration, loop/scope, type/layout, inline/callee, EH and compiler grids
remain disproven as documented in earlier handoffs; none is reopened here.

## Continue from here

The task remains an unfinished compiler-layout/source-shape investigation.
Trace the exact predicate-to-fact distinction in `0x10766afb`, especially
`0x10761e41` / compare handling around `0x10760ebe`, and the later null-join
simplifier before proposing another source grid. A useful hypothesis must
explain both preserving the third draw reference before packing and eliminating
the null join afterwards. Do not repeat these copy grids or the sol10/sol11
predicate, guard, union, inline and switch grids without new evidence.

The independent two unresolved MemoryPool allocator calls remain: retail
folds the wrapper to the 3-byte xor/ret at 0x65CE90; fold admission's 8-byte
floor and occupied names prevent the prior pin/alias proposals. No new
pin or verifier change was attempted. Do not repeat those workarounds.

Reproduce by copying sibling *.py.txt into a new directory directly under
build, removing .txt. Run prepare.py first: it explicitly loads the input
bank at ebfb4fa883 and asserts its hash, so later date-only banking cannot
silently alter the controls. Run copylower.py, lateintrinsic.py, typedcopy.py,
validate.py, then controls.py. Run chains.py carry081200 and chains.py
carrypointer, and watch_first.py carrypointer for native captures; then
summarize_native.py. Drivers inspect only proven source/destination fields.
Use c2inspect.py dis ADDRESS LENGTH to inspect a known instruction boundary.
The scripts do not modify the compiler or shared build cache.
