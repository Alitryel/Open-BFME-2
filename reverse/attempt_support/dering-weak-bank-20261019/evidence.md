# Weak deringing: improved complete bank, not a match

Target `_DeringBlockWeak_C`, RVA `0x001C22C0`, 1526 bytes through
`0x001C28B6`. Inputs are the approved clean-room specs `001c22c0.md` and
`001c1ad0.md`, retail disassembly and the existing bank. No external decoder
source was consulted. No production source, ledger row, pin or alias is added.

The previous complete bank emits 1485 bytes. Advancing vertical source and
weight row pointers, retaining the original samples in a conditional absolute
difference, and giving each row counter its own lifetime emit 1523 bytes.
The frame remains 0x160, and both vertical and horizontal weight loops now have
the retail unrolling structure. Ordered byte alignment improves from 1106 to
1358 of 1526 bytes (0.889908). This is a diagnostic alignment score, not exact
coverage. First difference is +0x40; stack-slot assignment, weight-pointer bias,
instruction ordering and final output scheduling still differ.

`trials.json` records 52 normal `explain_mismatch.py` trials. Direct versus late
neighbor pointers, row/weight pointer induction, signed versus unsigned indices,
absolute-difference forms, local lifetimes, output row pointers, clipping forms,
and equivalent blend/declaration orders were tested. None is exact. The bank
keeps the strongest complete body, without scheduling barriers, volatile accesses
or fabricated operations. The existing canonical sharpen-table name is reused.

`oracle-results.json` records 2560 passing comparisons among retail, compiled
bank and an independent implementation of the approved specification. All 64
sharpen indices, positive/negative pitches, flat/checkerboard/ramp/random inputs,
and disjoint, identical and partially overlapping buffers are covered. Each
output is stored immediately, preserving the weak filter's alias behavior.
Complete buffers/canaries, the cdecl stack pointer, preserved registers and the
unchanged quantizer table are checked. The oracle source accompanies this record;
it uses only approved specs and retail data. These cases are not an exhaustive
proof and do not replace the byte gate.

The bank was compiled and tested again after `re_log.py --stash` wrote it.
Compiler flags: `/O2 /G6 /DNDEBUG /MD`. Reference pointer:
`a18d9ed50607e9175de4d6568798d7d73119de09`. Base: `051fd9721f`.
