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

## Session 2 (2026-10-21, later): the three dependent anchors are solved in principle

Per-use attribution of every output-loop address (`build/s1c/cmap.py`, untracked:
which cursor serves each family offset) gives one rule for below, above and dest
in retail, the bank and the ddmin hit alike:

- An address `X + k` whose offset equals another family's cursor anchor is served
  as `thatCursor + (X - Y)` (zero displacement; the pixel at the source anchor
  also serves above at +1 and below through above: `[(Sc + (A-S)) + (B-A)]`).
- Each family's own cursor anchor is the **second distinct nonzero offset among the
  uses left to its own cursor** (the single-family call-probe rule):
  retail B own {1..7} -> 2, A own {3..7} -> 4, D own {1,3,5,6,7} -> 3;
  bank B own {0,2..7} -> 3, A own {0,4..7} -> 5, D' (dst-1) own {2,4,6,7,8} -> 4 = D+3,
  plain store own {0,2,4,6,7} -> 4.
- So below/above/dest follow the source anchor. The only independent residue is
  the **source anchor (bank +1, retail 0)**; the ddmin hit confirms: source 0 alone
  brings B2 A4 D3 with the plain row store.

Retail output-loop map (after the four pushes): above [0x1c], below [0x30],
cursors A [0x14] = above+4, B edi = below+2, S ecx = source, D [0x24] = dest+3;
differences A-S [0x20], B-A [0x64], D-S [0x54], A-B [0x5c], D-B [0x60], D-A [0x58];
weights esi = horizontal+1 (`lea [esp+0x6a]`, stride 0x12), eax = vertical+8
(`lea [esp+0x108]`, stride 0x10); counter [0x2c] = 8. Retail loads:
S0 S1 B0 S-1 A0 | S2 A1 B1 | S3 A2 B2 | S4 B3 A3 | ... | B6 A6 S7 S7 S8 B7 A7.
The bank has the same structure shifted one pixel late (pixel 1 takes retail's
pixel-0 addressing).

### ddmin of the one random anchor hit

`build/s1c/dd.py` minimised the rs_1 hit to: pixel 1 right and left through
`q = source + r * pitch + 1` (`q[1]`, `q[-1]`), pixel 2 left through
`source[idx + 1]` (`idx = r * pitch`), pixel 1 above through `above[idx + 1]`, and a
`destinationRow[c]` store. Anchors S0 B2 A4 D3 (all retail) at 2028 B, frame 0x17c,
but c2 makes `source + 1` and `above + 1` separate families (`lea ebx,[ecx+1]; sub
ebx,ecx` = difference 1), so S1 is loaded three times. A factorial over those
choices (f5.py) shows source 0 needs pixel-1 right and left through `q` and pixel-2
left through `idx`; best insn ratio 0.7423 (2019 B, bdiff 1505), not banked: it
keeps the redundant loads and scores below the bank on bytes.

### Disproven this session (do not repeat)

- Five pointer families (left/right through their own row pointers) x index forms.
- Types of pitch/r/c and output-loop variable scope: identical to the bank.
- 240 prologue orders and cap forms: no source move; declaring below before above
  swaps the below/above anchors (family order follows base-pointer declaration).
- above/below through source (thr), inline helpers for the pixel (inl, inl2),
  natural weight indexing (nat), a rolled pixel loop (1085 B, stays rolled).
- There is no WorldBuilder twin. BFME 1 has the same body only as a gen dump
  (`d_009b10e0`, 0x9B10E0..0x9B18CE), no C++.

Landing note: the sharpen table must be `extern "C" int g_vp6SharpenModifier[64];`
(as in `Code/Libraries/Source/VP6/DeringBlock.cpp`); the bank still says
`Vp6FilterEdgeTagTable`.

### Carry factorial and flags (session 2, end)

- Carried pixel locals (`build/s1c/carry.py`): row-scope `leftPixel, centerPixel,
  rightPixel[, belowPixel, abovePixel]`, per pixel `leftPixel = centerPixel;
  centerPixel = rightPixel;` (modes none / L / C / LC) x all LCR and LCRBA statement
  orders x weights first/last = 1008 variants. Statement order is inert; only the
  mode moves anchors: none and C = bank (S1 B3 A5 D3'), L = S1 B4 A2 D4,
  LC = S-1 B3 A1 D3. No variant reaches S0.
- Flags on the bank: /G5, /GB, /Ox, /Op, /Ob0, /Ob1, /Gr, /arch:SSE, /Og /Oi /Ot /Oy
  are byte-identical to /O2 /G6; /G7 and /arch:SSE2 change scheduling only
  (same anchors, worse); /Oa, /Ow, /Oy-, /O1, /Os much worse. /O2 /G6 stands.
- Per-pixel shifted source `q = source + r * pitch + k` for all pixels (pp8) with the
  plain row store reproduces retail's S family exactly, including the doubled S7
  load (`S 0:ecx ... 7:ecx+7 7:ecx+7 8:ecx+8`), but then A is served first with
  its cursor at A+1 (B1 = A cursor + (B-A)), B at +3, D at +4. Retail serves B
  before A (A2 = B cursor + (A-B)) with A1 = A0addr + 1. So the "second distinct
  nonzero own use" rule holds for retail and the bank but not for pp8 (A own
  {1..7} -> 1): the family processing order is itself spelling-dependent.

### Call-probe model fitted to all single-family data (untested predictions)

Zero offsets never count as singles. Let c be the use count of the most repeated
offset (an address CSE) and s the number of nonzero offsets used once. If c >= s
the repeated offset is the anchor; else the anchor is the second single in IL
order. This fits every data point above ([1,2,3,4,1]->3, [1,2,3,4,1,1]->1,
[3,0,0,6,1]->6, [0,0,5,6]->0, ...). Next session: test it with multi-CSE probes
([1,2,1,2], [0,1,0,1], the pp8 S list), then use it to pick per-pixel spellings
that leave A's own uses at {3..7} with B processed first.
