# 0x0041F369 ArmyDefinition weight normalizer (200 B), 2026-10-20

## Result

Recorded as blocked; the bank `reverse/attempts/0x0041f369.cpp` is unchanged. The new body, kept as `candidate-200b.cpp.txt` in this folder, emits 200 of 200 bytes and `tools/align_diff.py` reports 0 structural regions, 3 memory and 7 register differences. The bank emits 207 bytes with 1 structural region (the missing in-place `addss xmm4, dword ptr [eax + 8]` in the first loop), 2 memory and 1 register differences. The candidate gains the region but adds register differences, so it does not replace the bank; it is the starting point for the next attempt.

## Remaining mismatch

Only the XMM colouring of two variables differs. Retail keeps `totals[0]` in xmm3 and the block-1 scale in xmm2 (with the block-1 loop temporary in xmm3); the bank gives `totals[0]` xmm2 and the scale xmm3. Every instruction, operand order, memory operand and integer register is otherwise retail's, including the folded middle sum and all three multiply orientations.

## What was established

1. The weight accessor is retail 0x0041F28C (already rowed as `?rva0041F28C@ArmyMemberDefinition@@QAEPAMH@Z`). Its WorldBuilder twin 0x01332800 is reproduced instruction for instruction by a direct-return switch (`case 0: return &m_04; case 1: return &m_08; default: return &m_0C;`) built with `/Od /Ob1`; the ledger's current `p = ...; break; return p;` spelling builds the same retail bytes but a 69-byte debug body with an extra local, so it is not the original spelling.
2. WorldBuilder 0x01333240 (418 B, frame 0x48) is reproduced instruction for instruction (141 instructions, calls and absolute addresses masked) by `wb-faithful-source.cpp.txt` built with `/Od /Ob1`: an STLport `std::vector<ArmyMemberDefinition *>` at +4, `Real totals[3] = { 0.0f, 0.0f, 0.0f }` (three separate zero assignments give the same debug code), one `for (iterator it = begin(); it != end(); ++it)` per loop, `Real scale = 100.0f / totals[k]` per block and `*(*it)->rva0041F28C(k) *= scale`. The accessor is not inlined in WB, so it is an ordinary out-of-line member that retail's `/O1` (`/Ob2`) auto-inlines.
3. The in-place middle sum is an operand-order effect of the inlined accessor, not of statement order. Which of the three adds (and the three multiplies) has the accumulator as the left operand shifts with the function's symbol structure: iterator sharing, array or scalars, per-block or shared scale, raw pointers or vector, and the accessor's body spelling. A direct-return accessor with a vector, one iterator declared before the first loop and reused by all four loops, and the `totals[3]` array gives retail's pattern (middle add folded, all multiplies deref-first). Raw-pointer loops with per-loop iterators and assigned totals, or a vector with per-loop iterators and scalar totals, give the same 200-byte result.
4. The exact WB source (point 2) built with `/O1 /G7 /arch:SSE` gives 207 B with no folded add, the same wall as earlier banks. So the WB-proven source does not reproduce retail under the region flags, and every 200-byte variant deviates from WB in one declaration (the bank: one shared iterator instead of four).

## Ruled out in this run

- Compiler flags on the natural source: `/O2`, `/Ox`, `/G6`, `/arch:SSE2`, `/Op`, `/Oi`, `/GS`, `/Gy-`, `/GR`, `/Zi`, `/Ob1`, the spelled-out `/O1` set, and the pinned `vc71-sp1` and `vc71-ddk-4035` compilers: none folds the middle sum.
- `/Oy-` gives retail's XMM colouring (total0 xmm3, scale xmm2) with the folded middle add, but changes the integer allocation (198 B, 49 differing lines). The XMM colouring is therefore coupled to the integer allocation, not only to XMM use counts.
- Scale spellings (`Real scale = 100.0f; scale /= t`, `const Real`, declare-then-assign), `a = a + b` and `b + a` respellings, statement order in the first loop, explicit `inline` or in-class accessor definitions, `if`-chain or `case 2:` accessors, a `static const` or extern 100.0 datum, and unrelated functions earlier in the unit: no colouring change at 200 B.
- A diagnostic extra use of the block-1 scale (`g_sink = scale;`, not landable) flips the colouring with N = 1, so the gap is under one use, but it also changes the loop form.

## Next steps

- Find what moves `totals[0]` off xmm2 without touching the integer allocation. The `/Oy-` result points at the joint int/XMM allocation order rather than XMM weights alone.
- Before landing, reconcile with WB: the exact WB source must still be the one that lands, so the missing piece is more likely a build-environment difference (retail unit flags or STLport inline bodies) than a different declaration.
- Landing also needs the accessor body 0x0041F28C in the same unit (it is auto-inlined here, so its out-of-line copy is emitted beside the normalizer); its row currently lives in `Code/GameEngine/Source/Common/Rva0041F28CMethod.cpp`.
