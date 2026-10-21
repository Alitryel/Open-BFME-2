# _DeringBlockStrong_C 0x1C1AD0: c2 strength-reduction anchor probes (2026-10-21)

Bank: `reverse/attempts/0x001c1ad0.cpp` (0.84, 2046 B vs 2030). Residue unchanged:
every output-loop address family sits one offset above retail (source +1 vs 0,
below +3 vs +2, above +5 vs +4, natural dest +4 vs +3), frame 0x174 vs 0x178.
Earlier lists: `dering-strong-anchor-20261020.md`, `dering-strong-bias-20261020.md`,
`dering-strong-cursor-20261020.md`.

Compiler: cl 13.10.3077 `/O2 /G6 /DNDEBUG /MD`. Scratch probes lived in
`build/s1c/` (untracked): `cp.py`/`cpa.py` single-family call probe,
`mp.py` multi-family call probe, `gp2.py` 8-pixel output-loop probe with per-pixel
source forms, `anc.py` anchor extractor (source anchor from the first load
displacement, dest anchor from the first one-register store, relative stores).

## Established (do not repeat)

- Pixel-sum term order and centre/right hoisting: all 120 term orders x 2 hoist
  forms compile to identical bytes. c2 canonicalises the sum; no anchor effect.
- Source anchor is intrinsic to the source family: dropping below, above or dest
  from the probe leaves the source cursor at +1 in row form. Dropping dest does
  not move the others.
- below/above as `arr[r*pitch+k]` and per-pixel `pb = below + r*pitch` forms are
  equivalent; `p + pitch` / `p - pitch` forms are much worse.
- Per-pixel source form mixing, all 256 combinations of row form
  (`source[r*pitch+k]`) and per-pixel pointer (`p = source + r*pitch; p[k]`),
  store `destination[r*pitch+c]`, anchor tuples (s, d, relative store k):
  126x (0,4,(0,1,3)) e.g. pppppppp; 64x (1,5,(1,2,4)); 32x (2,5,(1,2,4));
  14x (3,5,(1,3,4)); 12x (1,4,(1,3,5)) incl. rrrrrrrr (bank shape);
  6x (4,5,(1,3,4)); 2x (5,4,(1,3,5)). Retail in this store form would be
  (0,3,(0,2,4)): not reached by any mix.

## Single-family anchor rule (call probe, `f(source[r*pitch+k])` per k)

With distinct offsets the cursor anchor is the second distinct nonzero offset in
IL order (zero offsets ignored; one nonzero offset -> that offset when no zero,
two or more zeros dominate -> 0): all 24 orders of {0,1,2,3} fit, [1,2]->2,
[2,1]->1, [5,3,7,1,2]->3, [2,7,5,3]->7, [3,0,0,6,1]->6, [0,5,6]->6, [5,0,6]->6,
[0,0,5,6]->0, [5,6,0,0]->0, [5,6,7,0,0,0]->0. Repeated offsets perturb it in a
use-count way not yet modelled: [1,2,1]->1, [1,2,2]->2, [1,2,3,4,1]->3,
[1,2,3,4,1,1]->1, [1,2,3,4,3]->2, [4,1,2,2]->2, [1,-1,-1]->-1.
Counts matter but are not simply "most used": [1,2,3,4,1]->3 although 1 is
used twice. The real row-form source sequence (0,1,-1,1,2,0,2,3,1,...) gives 1.
The pp form (p[k] through a shifted base) gives source 0 but moves the other
families (rel 0,1,3; dest 4).

## Next leads

- Spell the source so that offset 0 dominates the use count while keeping the
  row form for below/above/dest (e.g. a pointer advanced per pixel only for the
  centre load, or left/right read through separate row pointers).
- Combine pp source with below/above/dest spellings whose own counts favour
  +2/+4/+3.
