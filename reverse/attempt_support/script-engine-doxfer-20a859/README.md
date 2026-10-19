# ScriptEngine::DoXfer 0x0020A859 (6131 B), seat run 2026-10-20

## Result

Partial, re-banked. `reverse/attempts/0x0020a859.cpp` now holds the 2026-10-14 body (score 0.75) plus a two-argument `XferVersion` constructor. It replaces the unreviewed farm body (score 0.86), which is semantically wrong. All earlier comment lines of the bank are kept.

## Measurements

All with `python tools/align_diff.py <file> '?DoXfer@ScriptEngine@@UAEXPAVXfer@@@Z' 0x0020A859 6131`; "differing lines" counts structural lines plus memory and register operand lines, leaving out relocation and branch lines.

| body | size | structural regions | memory | register | differing lines of 2027 |
|---|---|---|---|---|---|
| farm bank (before this run) | 6193 B | 13 | 96 | 150 | 267 |
| 2026-10-14 body | 6137 B | 6 | 191 | 159 | 359 |
| this bank | 6137 B | 6 | 191 | 159 | 359 |

## Why the farm body was replaced

Its counters load loop is `i = 0; while (i < countersSize)` with no increment, so loading any save with script counters never ends. Retail increments the counter (`inc dword ptr [ebp+8]` at +0x2CB, `jl` back to +0x222 at +0x2D1), and the farm body's own diff shows the missing increment as structural regions at +0x215 and +0x2C7. Its lower memory count comes from `struct { XferVersion v; unsigned char pad[14]; }`, a padded local that only steers the frame, and its players loop test is the equal-arm `(1 ? (pit != pend) : (pit != pend))`.

## Retail facts checked in this run

- The players store loop advancing `it` instead of `pit` is retail's own behaviour: retail +0x67F loads `lea esi, [edi+0x10]` once and +0x6C6 jumps back to +0x682 unconditionally, so the loop never advances and never exits. Keep `++it`.
- Apart from the three loop entries, every remaining difference is a frame slot. All other operand differences outside `[ebp±x]` are relocations; no member offset, callee or non-frame register differs.
- Loop entries: retail enters the CRC conversion loops 1, 3 and 4 (+0x932, +0xA5F, +0xAFE) by `jmp` to the bottom test and loops 2 and 5 by a guard. All other loops of the function already agree with retail, including the jmp-entered vector loops, the `while (count > 0)` loops and the guarded map loops.
- The orphan `push 0; jmp +0x1298` after loop 1's entry jump is the cross-jumped tail shared by the named-object throw (+0x836) and the named-reveal throw (+0x11C5). It sits after the first unconditional jump that follows its origin, in both builds, so it is a consequence of the loop entry and not its cause.
- Frame: retail keeps the function-scope `i` in the dead `xfer` argument slot `[ebp+8]` (counters +0x219, flags +0x2EB, attack priorities +0x716) and also the cached `end` of the living-world store loops (+0x586, +0x5F9); it keeps the living-world `count` at -0x10. This body has `count` at `[ebp+8]` and `i` at -0x10. `slot-map.txt` lists every retail slot against this bank's slots with reference counts.
- WorldBuilder twin (`python tools/wb_show.py 0x0020A859`, WB 0xB42700, ScriptEngine.cpp 4309..4923): the version object is built from two materialized arguments, 5 first and then 1, which is a two-argument constructor call; WB's object is 8 bytes with more fields than retail's two stored bytes. WB destroys loop 1's name list out of line and inlines the destructor in loops 2 to 5, which does not follow retail's 1, 3, 4 pattern, so it does not explain the loop entries. WB compares and advances the list iterators without calls.

## Ruled out in this run

Each trial was measured against the 2026-10-14 body (6 regions, 191 memory, 159 register).

- `namedObjectsCount` declared after the three named-object locals (the farm's one source change besides the hacks): 9 regions.
- `countersSize` and `flagsSize` declared before `sequentialScriptCount`: identical bytes.
- Every counter loop with its own loop-scoped `Int i`: 6, 203, 159. Loop-scoped `i` only in the per-player loops, only in the counters and flags loops, or only in the attack loop: 6/191/159, 6/203/159 and 6/191/159. `Int i` declared at the counters section: identical.
- Living-world counts: one scoped `count` per load loop is identical; also splitting the store branch into initialized declarations gives 10 regions and +35 B; a function-scope `count` keeps 6 regions but grows the frame to 0xE8 and the body to 6166 B.
- Loop 1 as an `inline` helper is not expanded (worse); as `__forceinline` it is identical.
- `it._M_node != names.end()._M_node` in loops 1 to 5: identical.
- `/EHa`: 178 regions. `/EHsc`: identical.
- `XferVersion version(1, 5)` through a constructor: counts identical, but version moves from -0x1C (third slot) to -0x30, next to retail's -0x34. Kept in the bank because the WB twin supports it.

## What is left

The exact landing needs two things: retail's loop entries for loops 1, 3 and 4, and retail's frame assignment. No source spelling tried so far changes the loop entries; the prior bank lists the earlier loop trials (const_iterator, postfix, reversed compare, while, outer iterator, `(*it)`, dropping the local list `operator!=`). For the frame, the constructor result shows that how a local is initialized moves its slot while declaration order does not; the next candidates are the remaining member-store initializations (the timer and topple records, the counter key and value) and whatever decides that `i`, not `count`, takes `[ebp+8]`. The four ICF callee addresses the bank header names now have ledger rows; whether this body's own instantiation names resolve to them was not checked.
