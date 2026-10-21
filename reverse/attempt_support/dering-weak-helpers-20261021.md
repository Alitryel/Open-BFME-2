# Weak deringing: names, C mode, weight helpers, sink probes (2026-10-21)

Native `_DeringBlockWeak_C` is 0x1C22C0..0x1C28B6, 1526 bytes. Inputs: clean-room
specs 001c22c0 and 001c1ad0, retail bytes and the committed bank only.

The bank `reverse/attempts/0x001c22c0.cpp` is unchanged at 0.973788, with 56
differing bytes from +0x2E3. The residue is still the output-loop row-cursor
spill homes and the colouring of the prologue registers.

Row-end slot traffic, from the last `jb` before `pop edi`:

| Source | Slot traffic |
|---|---|
| retail | `L180 L1c L24 L40 L28 L2c S1c L30 S24 S40 S28 S30 S2c` |
| bank | `L180 L24 L28 L30 L40 S24 L1c L2c S40 S28 S30 S1c S2c` |

## Ruled out in this run (do not repeat)

- Names: 160 random renames of the 18 identifiers. All are byte-identical to the bank.
- Compiler settings:
  - The body compiled as C (`.c`): identical.
  - `tools/permute.py --flags`: no closure.
- Lifetime and declarations:
  - Without the `below` local, without the `above` local, or with row pointers: much worse.
  - `above`/`below` declared late: much worse.
  - `below` read first, or non-const pointers: identical.
- Control flow, the handoff item untried in `dering-weak-homes-20261020.md`. Each weight loop was split into a `__forceinline` helper:
  - Vertical only: 70 differing bytes.
  - Horizontal only: 100 differing bytes.
  - Both: 1542 B.

  In every case the slot traffic is the same as the bank's.
- Gap probes, a diagnostic global sink after the output loop:
  - `above` or `below`: 1551 B.
  - `source`: 1554 B.
  - `above + 1`: 1536 B.

  None of these produces retail's slot traffic, so no single extra use of a base pointer reproduces the allocation.

Callee visibility does not apply, because the body has no calls. The next
hypothesis needs a source change that makes retail's first-loaded slot
(`0x1c`) a cursor updated before `below + 3`. Scratch, untracked:
`build/claude3/dw/`.
