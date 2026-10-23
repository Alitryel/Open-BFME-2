# 0x002E3AA8 PolygonTrigger::adjustCameraMovement — 8-byte selection wall

Date: 2026-10-22. Target 723 B; bank 715 B (score 0.9566).

## Residue (re-measured this session)

The bank and retail are instruction-for-instruction identical for 202 of 204
instructions. The only real diff block is the slide tail; the other four
`!=` blocks are cascaded jump displacements caused by the 8-byte size
difference. First diff `+0x56` at RVA `0x002E3AFE` is the `jmp` to the
success epilogue (`6c` vs `64` displacement).

Retail tail (0x2E3D14..0x2E3D54):

```
movss xmm2,[ebp+0x14]      ; remaining
mulss xmm2,[ebp-0x14]      ; prod.x
movss xmm1,[ebp-0x4c]      ; candidate.x   <-- 4-byte load
movss xmm3,[ebp+0x14]
mulss xmm3,[ebp-0x10]      ; prod.y
movss xmm0,[ebp-0xc]       ; along.z
mulss xmm0,[ebp+0x14]      ; prod.z (candidate.z == 0 propagated, no add)
addss xmm1,xmm2            ; candidate.x + prod.x (reg,reg)
movss [ebp-0x28],xmm1      ; next.x
movss xmm1,[ebp-0x48]      ; candidate.y   <-- 4-byte load
addss xmm1,xmm3
movss [ebp-0x24],xmm1      ; next.y
movss [ebp-0x20],xmm0      ; next.z
```

Bank tail (same slot map):

```
movss xmm0,[ebp+0x14]
movss xmm1,[ebp+0x14]
mulss xmm0,[ebp-0x14]
mulss xmm1,[ebp-0x10]
movss xmm2,[ebp-0xc]
mulss xmm2,[ebp+0x14]
addss xmm0,[ebp-0x4c]      ; folded memory operand
addss xmm1,[ebp-0x48]      ; folded memory operand
movss [ebp-0x28],xmm0
```

The deficit is exactly the two 4-byte `movss` loads of `candidate.x`/`candidate.y`,
which the bank's build folds into `addss` as a memory operand.

Slot map is confirmed by the epilogue: `[0x28]` is `next` (poly argument, then
`movsd`-copied to `[0x4c]` on success), `[0x4c]` is `candidate` (also copied to
`*out`), `[0x14]/[0x10]/[0xc]` is `along`, and `remaining` reuses the `slide`
argument slot `[ebp+0x14]`. Frame `sub esp,0x4c` matches.

## Why this is not a spelling problem

`docs/matching.md` says (`m.X += t`): "`t` = a product written in the same
statement folds; `t` = an element of a scalar-replaced local (`last *= u;
m += last`) loads, unless the allocator coalesces." The retail shape is the
*latter* (load destination, add a register product), but every benign way to
express the `last *= u; m += last` form is coalesced back into the product and
folded.

Measured this session (all compile to 715 B, same instruction stream):

- three-arg ctor both operand orders; per-component `=`; per-component `+=`;
  reversed operands; `next.add(along)` by value; `next.add(&along)` by pointer
- named locals `px/py/pz`, `nx/ny/nz`, `dx/dy/dz`, `cx/cy/cz`; assignment after
  declaration; `+=` after explicit member copy
- a separate `Coord3D scaled(...)` / `Coord3D scaled(along); scaled.scale(r)` /
  explicit member-wise `scaled.x=...` then `next.add(&scaled)` (the documented
  scalar-replacement form)
- `along.scale(remaining)` removed and the multiply written inline per component
- `scaleInlined`; `const Coord3D&`; reference-to-member; explicit
  `Coord3D(candidate.x,candidate.y,candidate.z)` (not the copy ctor)
- `permute.py 0x002e3aa8 --minutes 12 --jobs 4`: 1301 trials, best 0.9566
  (no gain).

## Diagnostics

- `const volatile float *cp=&candidate.x` then `next.x=cp[0]+along.x; ...`
  yields 732 B and **does** produce the retail `movss r,[m]; addss r,reg`
  shape. So the instruction sequence is reachable; the volatile access changes
  the slot assignment (along/candidate slots swap) and adds an extra store, so
  it is not the answer.
- Declaring `Coord3D next(candidate);` before the `if` instead of inside it
  (so the copy is materialized) gives 743 B with a different tail; declaring
  `next` and assigning inside gives 745 B. Placement changes the schedule but
  overshoots.

## Context that constrains any retry

Retail folds the memory operands elsewhere in the *same* function
(`0x2E3C02 addss xmm1,[ebp-0x40]`, `0x2E3C0B addss xmm0,[ebp-0x3c]`, both
`normal.x*0.1 + intersection.x`), and the bank reproduces those exactly. So the
fold rule is not a global switch: the tail differs only because the destination
of the accumulating add (`next.x`, forwarded from `candidate.x`) is loaded and
added as a register, while the earlier products are added into a folded memory
constant.

Retail's schedule interleaves (prod.x, load cand.x, prod.y, prod.z, add.x,
store, load cand.y, add.y, store, store z); the bank batches all three products
then the two adds. A retry should aim at the scheduler as much as the
expression: the load in retail is hoisted away from its add, which is the
condition under which the fold cannot happen.

## Best candidate

`reverse/attempts/0x002e3aa8.cpp` (715 B, score 0.9566), unchanged this
session. Reproduce with:

```
python3 tools/explain_mismatch.py \
  '?adjustCameraMovement@PolygonTrigger@@QAE_NPBUCoord3D@@0PAU2@_N@Z' \
  --rva 0x002E3AA8 --size 723 --source reverse/attempts/0x002e3aa8.cpp
```

Scratch variants: `build/cam/try*.cpp`, `build/cam/diff*.txt`,
`build/cam/retail.asm`, `build/cam/wb_0xaba7d0.c` (WorldBuilder decomp of the
same function, confirming `Coord3D next(candidate); next.Add(&along);`
semantics).
