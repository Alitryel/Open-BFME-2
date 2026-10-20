# gatherDebugStats: two-definition joins and late store removal

Continue only `?gatherDebugStats@W3DDisplay@@UAEXXZ`, RVA `0x0004826C`,
4101 B. **Not exact.** The stronger canonical bank remains byte-for-byte
unchanged, score 0.9968: 4101 B, 1237 instructions, zero structural regions,
13 nonrelocation displacement bytes. The sol10 alternate remains 4101 B,
1239 instructions, 11 diagnostic bytes in one region, with all stack slots
correct. No Code, ledger, pin, compiler or verifier changes.

## Inputs and scope

Started after pull at BFME 2 `818acf7f77`, with preserved sol10 evidence
rebased to `9bf9188053`. AGENTS.md, served RVA history, relevant earlier
handoffs and recipes read; claim acquired. Ledger validation passed:
97648 functions, 15922 symbols, 1133 data rows. Published link index fetched,
23209 objects. Clean BFME 1 verified pointer:
`68c5ce2789e974f36b6c742d57437d157bc159e9`; today's 15:49 UTC successful
verification receipt was within 24 hours, so no pointer update was due.

Bank SHA256:
`543c60098a558083c8e25ac900f5643eea7c1b5e42eb3e4b4bf286b26aa3454c`.
Original c2 13.10.3077 SHA256:
`bcd28f39b1798b07989c30a1df471cf87fc20e3802d130901a08f83800e6b81e`.
Flags `/O1 /arch:SSE /G7 /MD /EHsc`. Eight isolated compiler outputs per
batch, without experimental writes to the shared object cache. Scratch:
`build/gather-sol11-20261020/`. Model gpt-6.1-sol.

Earlier sessions already ruled out ordinary declaration/scope/temporary
permutations, fire-output lifetimes, basic types/layouts, ordinary accessors,
exception contracts and compiler profiles. Sol10 tested two-definition join
contexts, null carriers, getter interactions and flags. This session tested
new interactions that could defer null facts until after stack packing.
These are compiler experiments, not new claims about the original source.

## 4544 successful source trials

Every generated source was compared to its compiled scratch input and its
string-literal set compared to the bank. All compiled successfully. Relocation
masking is diagnostic only, never an acceptance gate. Counts include duplicate
instruction streams. Each grid crosses the char releaseBuffer contract on/off.

| Family | Count | Hypothesis and result |
| --- | ---: | --- |
| factjoin | 1024 | Two-definition joins followed by twelve final pointer/object guards, four initial predicates, three null-initialization forms, assignment/arm order. Uninitialized obj allowed only behind a safe short-circuit p guard. Actual additional guards keep extra code; controls reproduce 11 bytes/one region. |
| widejoin | 576 | Twelve equivalent 64-bit predicates and three extension/truncation copy forms in four join contexts, null zero/pointer. Best unchanged 11/one region. |
| unionjoin | 512 | Actual four-byte pointer/integer union, four tests, four load and copy representations, two contexts, null zero/pointer. Diagnostic MSVC union extension; no padding. Best unchanged 11/one region. |
| joinhelper | 768 | Carry the two-definition CFG through whole inline helper boundaries: object return, bool/output refs, void/output refs, early return; pointer value/ref, lookup inside/outside, inline/forceinline, three predicates, null and assignment order. Prior getter-only tests did not cover this interaction. Best unchanged 11/one region. |
| arithjoin | 256 | Sixteen equivalent unsigned bijective, sign-bit, rotation and partition predicates, two contexts, null and assignment order. No improvement. A partition predicate gives 4102 B, correct slots, but retains a full-mask TEST and extra null join. |
| switchjoin | 256 | Direct signed/unsigned 32/64-bit selector, rather than prior Boolean switch; case order, labels, initialization and assignment order. Best unchanged 11/one region. |
| partitionjoin | 1152 | The late full-mask TEST suggested crossing eight complementary bit partitions and three spellings with final obj/p guards, two contexts, null and assignment order. Best 4102 B/one region; final guards did not remove the join. |

`validated-results.json` preserves counts, source-stream hashes, best cases and
result histograms. `controls.json` independently recompiles the bank (13),
throwing base (44), and sol10 alternate (11/one region). Official align_diff
also confirms the alternate's 4101/4101 B, 1239/1237 instructions and one
structural region. Raw shifted-byte counts such as 1271 for 4102 B bodies
include the downstream offset shift; they are not 1271 independent defects.

## Native c2 evidence

Read-only Wine debugger traces of unmodified c2 confirm the prior Claude
head-merge explanation on these exact inputs. All three runs reach compiler
termination. Each uses a unique object output and the same two breakpoints:
pre-pack `0x10790b19`, tuple free `0x107af9d3`, filtering instruction nodes
with `*(unsigned char*)($ecx+8) == 13`.

| Input | draw weight/index before packing | Instruction frees | draw frees |
| --- | --- | ---: | ---: |
| bank | 2/40 | 169 | 0 |
| truebase (char contract removed) | 2/40 | 169 | 0 |
| carry081200 (sol10 alternate) | 3/18 | 170 | 1 |

The alternate's extra removed instruction is opcode 1 in block 193, register
source and memory destination `_draw`, displacement zero. It is a **store**,
not a reload. Operand decoding was checked against c2's constructors:

- `CmdInsertExit` at `0x1078c9b3` creates register type 1 and memory type 2
  operands, then calls `TupCreate` at `0x1078ca26` with opcode `0x26b` (store).
- `TupCreate` at `0x1075a5e9` places the first operand at +0x2c (destination),
  second at +0x28 (source). The capture lists source before destination.
- Memory operand +0x18 points to a stack-element record, not directly to the
  symbol. Decode name with `*(uint32*)(*(uint32*)record + 4)`; +0x1c is offset.
- Tuple free's first return `0x1079728c` is verified statically: the call to
  `0x107af9d3` is at `0x10797287`, inside `TupRemoveRange` (`0x1079724c`).
  The merge helper at `0x10739c27` calls that range remover at `0x10739cc9`.

`native-evidence.json` records packing fields, removed draw store, input and
normalized event-stream hashes. Other code-looking raw stack words are
preserved as clues only: c2 omits frame pointers, and they are not a proven
full unwind. No compiler patch, extra source read, padding or assembly was used.

## Resume without repeating these grids

The unresolved source problem is still the late null join at +0x912..+0x91f.
The alternate has the correct third reference and does remove a duplicate
draw store, but retains `jbe; load; jmp; mov edi,eax` instead of retail's
direct `je TERRAIN; load`. From +0x926 onward the alternate is at retail's
positions with correct frame operands. Preserve the canonical zero-region
bank and the sol10 alternate patch; these grids produced no better source.

A concrete next investigation is to capture the alternate's null-arm tuples
before and after the early flow passes and find the exact pass which keeps
the obj carry/join, comparing the ordinary pointer predicate with unsigned
ordering. Test a new source form only when that comparison identifies a new
pass-timing distinction. Repeating the predicate/guard/inline/union grids above
has no evidence behind it. The existing three-byte allocator fold admission
blocker also remains; do not repeat its disproven pin/alias workarounds.

To reproduce, copy the sibling `*.py.txt` files into a new directory directly
under build, removing `.txt`. The scripts assert the bank hash. Run
`python3 build/DIR/<family>.py` for a grid, then
`python3 build/DIR/validate.py`. They import the repository's compiler command
builder, but compile into unique scratch files rather than its shared cache.
For native captures prepare bank.cpp from the bank, truebase.cpp by removing
only the char releaseBuffer throw specialization, and carry081200.cpp from
the prior sol10 zero-context patch (`git apply --unidiff-zero` in an isolated
copy). Run `frees_cond_final.py TAG --before`. The debugger capture is slow
because it inspects every freed instruction; do not launch duplicate runs.
