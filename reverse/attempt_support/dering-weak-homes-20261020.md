# 0x001C22C0 DeringBlockWeak_C: row-cursor spill-home trials (2026-10-20)

The bank `reverse/attempts/0x001c22c0.cpp` is unchanged at 0.973788 (byte ratio),
1526 B, exact size. Every trial below used approved clean-room specs 001c22c0 and
001c1ad0 plus retail disassembly. No decoder source was consulted. Earlier rounds:
`dering-weak-rowcounter-20261020.md` and `dering-weak-flat-20261020.md`.

## Residue

Only the output-loop prologue and the row-end cursor updates differ.

- **Prologue colouring.** Retail keeps `below` in esi and `source` in edi. Ours
  keeps them in ebx and esi. Retail reuses esi for the horizontal-weight cursor
  and edi for the vertical-weight cursor. Ours gives `below` its own register.
- **Spill homes.** These are in `above`/`below`'s dead slots plus `[esp+0x40]`:

  | Cursor        | Retail | Ours |
  |---------------|--------|------|
  | above         | 0x28   | 0x30 |
  | vertical      | 0x30   | 0x40 |
  | `source + 1`  | 0x40   | 0x28 |

- **Row-end update order.** Retail: below, dest, `source + 1`, above, vertical.
  Ours: dest, `source + 1`, above, vertical, below. That is the same cyclic order
  with below moved first, and in retail `source + 1` is packed last.

The `source + 1` cursor is the horizontal loop's hoisted `ebp`, carried over into
the output loop. Retail does this as well.

## Disproven this round (do not repeat)

- Biases of -2..2 on the six family bases (s, b, a, h, v, d), declared as
  locals: 243 variants. None is better.
- Inline `(base + b)[i - b]` spellings: inert.
- Per-row pointer increments (`p += pitch`) for every subset of the six
  families: 64 variants, all worse. Above alone scores 0.657, vertical alone 0.924.
- Index spelling forms: 768 variants, all byte-identical to the bank.
- Declaration order of the nine function-scope locals (quality, sharpen, above,
  below, cap, vertical, horizontal, c, r; cap kept after quality): 150 random
  orders. Six are identical to the bank, the rest worse.
- How the horizontal loop creates `source + 1`:
  - `hrow = source + 1` with indices -1/-2: 0.908.
  - `hrow = source - 1` with +1/0: 0.769, 1328 B.
  - No row pointer (`source[r * pitch + hc]`): 0.895, 1520 B.
  - A second `hprev = source - 1` row pointer: 0.782.

- The output loop as a `__forceinline` helper that keeps its parameters:
  - `above`/`below` passed in, with its own counters: 0.954;
  - `above`/`below` derived inside the helper: 0.860, 1520 B;
  - the shared `r`/`c` passed by reference: 0.965.

  None of these moves the spill homes or the prologue colouring.

## Untried

- Splitting the weight loops into helpers in the same way, to change the IV
  creation order without changing the inner-loop code.
- A gap measurement of the slot-packing order: throwaway uses of each row
  cursor's base before the output loop, counted the way the IL-count probes in
  `dering-weak-rowcounter-20261020.md` were.

Scratch, untracked: `build/c1c22c0/` (`gen.py`, `gen2.py`, `gen3.py`, `gend.py`,
`genh.py`, `genf.py`, `score.py`).
