# 0x237D3D: duplicated cleanup and the return suffix

Continue only `?Rva00237D3DCheck@@YAHXZ`, RVA **0x237D3D**, extent **226**.
Previous handoff: `../trust237-20261023-round12/readme.md`. Inputs: BFME2
`973c5c9a95`, committed and checked-out BFME1 `42bba2ddbd5c`; model
GPT-6.1-sol. No game source, ledger, pin, compiler or verifier changed.

Read the scoped pick-hard history before these trials. Its earlier simple
equal-result branches, return carriers, source lifetime/layout/visibility,
compiler/frontend and observed A9-padding matrices remain finite negative
results. In particular, the actual native encoder was exercised in round12;
do not repeat the claim that this compiler never emits a single NOP.

## New hypothesis and source trials

Earlier equal-result branches placed a single LocalFree before the branch.
Duplicating cleanup in status-dependent arms gives late cleanup merging a
different opportunity to retain status and schedule the return restores.
This is a diagnostic source-shape hypothesis, not a recovered source identity.
Retail establishes the API order, GUID, file16/data44 accesses and constant
return; no new donor identity or layout claim is made.

Each family has **512 successful isolated compiles**, with eight workers:

| Family | Choices | Distinct raw bodies | Objects ending `40 5e 5b c9 c3` |
| --- | --- | ---: | ---: |
| funnels | Four status tests; duplicate return/assignment/goto/switch cleanup; four constant-one expressions; direct/forceinline throw() cleanup; O1/O2, G6/G7 | 51 | 16 |
| refine | Eight narrow/masked status tests; four predicates; assignment/goto; bound value/reference; cleanup exception specification; G6/G7 | 19 | 0 |
| compact | Eight full-width imm8 equality values; eight range expressions; assignment/goto; bound value/reference; equality direction | 82 | 288 |
| typed | Four mask types; four equality values; four typed/compound forms; mask 1/127; int/bool result; bound value/reference | 32 | 244 |

The combined **2,048 objects yield 166 distinct raw bodies**. None contains
even one decoded NOP. There are **38 distinct bodies** with retail's final
five-byte increment/restore suffix; this resolves that source-shape obstacle
in isolation, but does not reproduce its position or the NOP region.

`regional-k0166.cpp.txt` is the useful regional result: **227 bytes**, diagnostic
prefix **205**, **22 positional differences**, **70/86** equal mnemonics. Its
duplicate cleanup uses a const-reference bound and `u==2`. The final increment
starts at +DE instead of retail's +DD. Between +CD and that increment it has
17 bytes of branch/range arithmetic, including `and bl,1` (three bytes).
The typed matrix tests whether preserving the mask's type selects a two-byte
register AND; it does not. `tails.txt` retains the exact region comparison.
No trial established a producer for sixteen consecutive 90 bytes.

The original **219-byte bank remains the closest by positional differences**:
**21**, prefix **205**, **69/86 = 0.802326**. Regional winners have a higher
mnemonic score but more differing bytes and exceed the row. Preserve both
rather than replace the better positional bank. Bank raw SHA256:
`23875f743d6816184d590366a5617a42b8e18aedc479c4d75864e0f6d61de0c9`.

## Independent checks

`audit.py.txt` sequentially rereads all objects and checks complete disassembly,
raw hashes, relocations, mnemonic scores, positional differences and prefixes.
Its receipts are in `audit.json`. The diagnostic resolver fills DIR32 slots
from retail, as variant.py does; these are not full-byte admission receipts.

`emulate.py.txt` relocates calls by symbol to private emulator hooks, without
borrowing retail call operands. The 2,048 objects plus bank form **166 distinct
code/relocation groups**. All **110,224 executions pass**: 166 statuses times
four LocalFree-return/argc combinations per group. Checks cover return=1,
stack balance, callee-saved registers, caller-saved ECX/EDX/flags clobbers at
external calls, API order/counts, GUID and file16/data44 fields. These finite
behavior checks are not identity or byte-match proof. `summary.json` preserves
the checked counts, group-receipt digest, regional bytes, toolchain hashes and
matrix/script hashes without retaining disposable object matrices.

## Separate producer investigation

`producers.py.txt` scans overlapping decodes in executable sections of the
actual RTM c2/c1xx/c1/link binaries for MOV/PUSH/CMP immediates 90/9090/90909090.
Overlapping decoding is intentionally permissive and includes false code.
Two apparent c1xx MOV candidates at 1043C711 and 1044ACA1 are jump-table data
or a misdecoded jump followed by alignment, not established writers.

Three actual c1xx PUSH-90 sites (10416D0A, 10495808, 104DC25F) call abstract
frontend emitters; their numeric argument is not proven to be an x86 opcode.
`trace_frontend.py.txt` sets deferred breakpoints, observes them installed,
then completes compilation of the bank with **zero hits** and the same raw
body hash. `frontend-trace.json` retains the receipt. This finite search found
no additional producer; it does not exhaust compiler paths, prove a post-link
patch or justify an asm/emit escape hatch. The earlier linear-disassembly
scan lost alignment at tables and is superseded, not banked as evidence.

## Reproduction and continuation

Restore the eight saved scripts without `.txt` to `build/trust237-round13`.
Restore round9's `frontends.py.txt` under `build/trust237-round9` and leave
round5's tracked `base.cpp.txt` in place. Run funnels.py, refine.py, compact.py
and typed.py, each using `build.compiler_command` and unique object/PDB paths.
Never use `build.compile_source` for these scratch trials. Reproduce the bank
with variant.py as in round10, then run audit.py and emulate.py. The emulator
uses round4's scratch Unicorn install. For the optional frontend trace restore
`../a9f98-c2keys-20261022/wdbg.py.txt` under `build/trust237-round7/wdbg.py`,
setting its ROOT to `Path.cwd()` as described by the earlier trace handoff.

Ledger checks pass. The published link index fetch succeeds (0fa62a2841,
2026-10-22 23:07). Current link_check says VersionDestructor.cpp already links
its **1,275 bytes**; VersionInitGlobals.cpp has **200 bytes** withheld by this
unresolved check. Thus the assignment's older 1,584-byte destructor blocker
figure is stale. No new linking repair is claimed. BFME1 freshness update is
skipped under the live codexb updater lock, per runner instructions; no success
stamp is written here. Preserve unrelated untracked `reverse/zh_sweep/`.

No missing game callee is identified. The unresolved target remains the
internal NOP16 region and its exact return placement. Do not rerun these four
matrices or the three frontend breakpoints unchanged. Keep the regional body
for recombination if new evidence explains a producer or target source shape;
continue this assignment next session. Claim is released when banking.
