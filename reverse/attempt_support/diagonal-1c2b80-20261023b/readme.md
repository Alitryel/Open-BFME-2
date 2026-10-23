# DiagonalBlur 0x001C2B80 (916 B): c2 symbol-id alignment, 2026-10-23 (b)

Spec `reverse/vp6_cleanroom/specs/001c2b80.md` and retail only; no decoder
source read. Bank unchanged: `reverse/attempts/0x001c2b80.cpp` (nd 2, the two
SIB base/index swaps at +0xb2 and +0x135). Earlier handoffs:
`diagonal-1c2b80-20261022.md`, `diagonal-1c2b80-20261023/readme.md`.

## Result: the bank's structure is retail's; only id alignment differs

Compiling the bank under winedbg and consuming **28 extra kind-15 symbol ids**
(c2 "hash vars") early in DiagonalBlur's compile gives **exact retail bytes
(nd 0)**. `inject2.py.txt 1:28` does this; any injection point at kind-15
ordinal 1..1040 or 1056..1090 works (1050: nd 6; 1098/1100: nd 20; 1102: nd 2).
N sweep at ordinal 100: 28 -> 0, 24 -> 3, 32 -> 2, 4 -> 32, 8 -> 35, 56 -> 12,
60 -> 9, others worse. So the residue is only symbol numbering, and a matching
source is the bank plus an edit invisible in code that changes the kind-15
count before T (below) by -4 (mod 32) and leaves everything else alone.

## c2 id model (validated: replay of 4937 allocation events, 0 mismatches)

- Global id counter `[0x108a79d0]`; each kind's pool takes 32-id chunks from it.
- Kind 15 (hash vars): entry 0x1076045d, arena `[0x108a79b0]` (+4 cur, +8 end,
  symbol 0x60 B, id at +0x1c); refill 0x10763196 -> 0x107603db (0xc0c B, 32
  sequential ids).
- Kind 3: free list `[0x108a79a4]` at 0x1075a0db (recycled symbols keep ids),
  else arena `[0x108a79ac]` at 0x10760853 (new ids). Dispatch byte table
  0x1075a0b5[kind], jump table 0x1075a110.
- Per-function reset at 0x107765a6..0x10776609 (counter 0, four arenas
  preallocated with ids 0..127, kind-15 arena 0, free list 0): nothing crosses
  functions, so same-unit context cannot move it (DeringBlock/StrongC/WeakC
  before the body: nd 2).
- FactCanonSort keys (0x1075d388): leaf `(class != 0x380) << 16 | hash`,
  interior hash 0x1075d54e = sum of `(child.key & 0xffff) << (i & 7)` plus
  `op - 0x24a`; sort at 0x1075cd0c, comparator 0x1076a394. Interior keys hash
  ids too, so the tap-sum order and the SIB order both follow absolute ids.

**T** = the first global chunk taken by kind 3 after kind 15 started
(`c15t.py.txt`). Bank: 1050 kind-15 allocations before T, i.e. 6 free slots
left in the kind-15 chunk; retail needs 10 (count at T = 22 mod 32).
`count15.py.txt` writes the event list (kind-15 ids, -1 for new kind-3) and the
counter at each event; `callers15.py.txt` histograms the allocating c2 callers.
Bank: 1923 kind-15 in total, start id 960; allocating paths before T:
966e5->62180 (315), 51004->61819 (220), 6165d->636a2 (215), 52001 (60),
54bce (64), 61819 (79), 6b50f (42). The same profile repeats after T (second
optimisation round), so the pre-T count is roughly one round over the body.

## Measured edits (count at T, compensated nd = nd after injecting the missing ids)

- Named-sample patterns (`gen5.py.txt`, bit j = pixel j has nine named
  sample locals): every pattern with exactly two named pixels (bank p03, p05,
  p06, p09, p10, p12) has count 1050 and compensated nd **0**. Three named:
  1050, nd 12, compensated 9. **All four named (p15): count 1046, the retail
  alignment without injection, but nd 11** (eleven SIB swaps, base/index all
  one way); injection sweep 1..31 on p15 is no better (N=0 best).
- p03 + 64 inert locals reproduces p15's exact 11-swap pattern; p15 + 32 equals
  p03 + 128; p03 + 32 equals p03. Named samples and inert locals act through
  the same early kind-3 count, which moves T and the kind-3 ids together.
- Inert `int padN = N;` locals 0..23 on the bank: fully inert (nd 2, count
  1050, compensated 0). 24..31 still nd 2 uncompensated, but they began to move
  T (the scan was injecting N=22 there when it was stopped at wind-down; those
  counts were cut off, so measure 24..63 again). The effect seen at 64 (p15's
  pattern) starts somewhere in 32..63.
- Manually unrolled pass 2 (u010/u110/u111): count 1050, compensated 28;
  u100: total +18 kind-15, compensated 10..28. Not the source shape.

## Next steps

1. Look for an edit that only changes kind-15 by -4 (mod 32) before T.
   Hash vars are per-expression entries, so candidates are redundant spellings
   that CSE removes, e.g. a repeated subexpression or a recomputed offset in one
   pixel, a sample read twice, or a named offset local. Measure each with
   `evalv2.sh.txt` (prints count at T, needed N and compensated nd). Keep only
   edits with compensated nd 0, then combine them until the sum is -4 (mod 32).
2. Alternatively, find a kind-3 change that moves T by -4 kind-15 allocations
   (as p15 does) without p15's SIB swaps. Its eleven swaps come from the
   kind-3 ids of the extra named samples, so a different early kind-3 count
   (declaration placement or scope of the samples) might keep T but restore
   the ids.

Disproven this session, on top of the earlier handoffs: the total kind-15
count as a metric (naming patterns all have 1923, alignment differs at T);
kind-15 injection on p15; inert-local counts 0..23 on the bank; injection at
or after T.

Scripts: copy `*.txt` to `build/db/` (`wdbg.py.txt` to `build/c2tr/wdbg.py`).
They compile through `build.compiler_command` under winedbg into private
objects in `build/db/tr/`; about 32 s (inject) / 45 s (count) per run, 8 in
parallel.
