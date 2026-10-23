# 0x001C1AD0 DeringBlockStrong_C: base/constant anchor levers (2026-10-20)

The bank `reverse/attempts/0x001c1ad0.cpp` moved from 0.832 to 0.840 (byte ratio).
Permute fitness moved from 0.7885 to 0.8020. The compiled size is still 2046 B,
against retail's 2030 B. This round builds on
`dering-strong-anchor-20261020.md` and `dering-strong-cursor-20261020.md`.
Everything here comes from clean-room specs 001c1ad0 and 001c22c0 plus retail
disassembly. No decoder source was consulted.

## Finding

MSVC 7.1 picks each strength-reduced cursor's constant from how the source
spells the base and the constant, not from the address alone. Writing a family
as `(base + b)[index - b]` moves its cursor even though the addresses do not
change. Two families now match retail:

- **Dest.** Declare `unsigned char *dst = destination - 1;` and store with
  `dst[r * pitch + c + 1]`. This gives retail's dest+3 cursor and the store
  pattern `[ecx+ebx]`, `[ebp-2]`, `[ebx+edi]`, `[ebp]`, `[ebx+ebp]`, `[ebp+2..4]`.
  The cost is one extra `dec edx` in the output-loop prologue.
- **Vertical weights.** Use `downWeights = vertical + 9` and
  `upWeights = vertical + 1`, both read at index `r * 8 + k - 1`. This gives
  retail's vertical+8 cursor: `[eax]` for down, `[eax-0x10]` for up.
  - A down base of +6, +7 or +10 scores the same.
  - The up base must be +1 or +2.
  - A down base of +8 with an up base of +1 gives nothing.

The horizontal family (+1) already matched.

## Still wrong

- **Source.** The cursor is ecx = source+1, carried over from the horizontal
  loop's ebp. Retail's is source+0, loaded fresh from `[esp+0x190]`. Trial H1
  (a horizontal loop over `destination`) still gets `[esp+0x190]; inc ecx`. So
  the +1 comes from the output loop itself.
- **Below and above.** Ours are +3 and +5; retail's are +2 and +4.
- **Retail's pixel 0.** It does not use the below/above cursors. It forms
  `ecx + (above - source)`, spills it to `[esp+0x28]`, and reads below as
  `[that + (below - above)]`. Pixels 1..7 use the cursors edi = below+2 and
  `[esp+0x14]` = above+4.
- **Frame and prologue.** The frame is 0x174 against 0x178. The prologue also has
  the extra `dec edx`.

## Disproven this round (do not repeat)

- An IL counter ahead of the loop (16 probes, inert).
- Carrying the centre pixel to the next pixel (0.720).
- Masks over per-pixel `p` / `pb = p + pitch` / `pa = p - pitch` (766
  variants). None was better, and the per-pixel forms give 2013 B.
- Horizontal-loop source probes. H1 keeps source+1; H3 and H4 are worse.
- Source-row bias from -2 to 2, and a biased `src` copy, each combined with
  below/above/dest biases (1250 variants). None beats the bank. Copy locals at
  bias 0 drop to 0.735.
- Biasing the above/below declarations themselves (e-series). The best,
  e4333, scored 0.819.

## Untried

- Spelling pixel 0 alone through a `p - pitch` / `+ 2 * pitch` pair, keeping
  the biased cursors for pixels 1..7. The earlier masks applied one spelling to
  all three families together.
- The left pixel through its own biased pointer, while centre and right go
  through `(source + 1)[k - 1]`.
- Running `tools/permute.py 0x1C1AD0` from this bank. Its residue is now mostly
  anchor constants and the frame.

Scratch tooling, untracked: `build/c1c1ad0/variants.py` (factories mk, mkbias,
mkc, mkd), `gen2.py`, `score.py`. The bank is `mkd(0,0,0,-1, wd=1, wu=1)`.

## Follow-up: the handoff's untried items (2026-10-20, later round)

All three are now disproven. The bank is unchanged.

- **Pixel 0 alone through `p`.** Seven forms, with every other pixel kept on
  the biased cursors:
  - `p[pitch]`/`p[-pitch]`, `(p + pitch)[0]`/`(p - pitch)[0]` and
    `(p - pitch)[2 * pitch]`: 0.669;
  - below only (`p[pitch]`): 0.813;
  - above only (`p[-pitch]`): 0.679;
  - `above[r * pitch + 2 * pitch]` for below: 0.831;
  - pixels 0 and 1 both: 0.626.
- **Left pixel through its own pointer.** Six forms: `pl = source - 1 + r * pitch`
  with centre and right on `p` (0.8394), on `q = source + 1 + r * pitch` (0.599,
  2002 B), or indexed on `source` (0.833). With `q` alone, any left spelling
  gives 0.599.
- **Permute from the bank.** 1226 trials. Fitness went from 0.802 to 0.825
  (bytes 0.850, frame 0x178), but every gain came from semantics-breaking
  mutations: an `unsigned` value or weights in pixels 1, 3 and 6, which make
  the clamp-to-0 dead and the shift logical, and `above[r * up * pitch + 2]`.
  With those reverted the best scores 0.834.

One structural observation for the next round. With hand-unrolled stores and
`destination` unbiased, ours addresses pixels 0, 2, 4, 6 and 7 through the dest
cursor (+4) and pixels 1, 3 and 5 relative to another family's cursor. Retail
has the same alternation shifted one pixel earlier: relative at 0, 2 and 4.
The below and above families shift the same way: retail's pixel 0 reads both
relative to the source cursor, while ours first does that at pixel 1. Retail's
extra frame dword is the pixel-0 spill at `[esp+0x28]`. So the +1 anchor
offset and the 0x174 frame are one symptom. Whatever moves the first relative
reference to pixel 0 should fix both.

The retail tail shows how a reference is chosen to go relative. Store k goes
through another family's cursor exactly when that cursor's constant is k:

- store 0 is `[ebx+ecx]`, using the source cursor at +0;
- store 2 is `[ebx+edi]`, using the below cursor at +2;
- store 4 is `[ebx+ebp]`, using the above cursor at +4;
- the other stores use the dest cursor at +3.

Ours does the same with constants 1, 3, 4 and 5. So only the four anchor
constants need to move, and they move together. That points at the shared
integer index temps (`r * pitch + k`, used by below, above and the unrolled
store loop) rather than at each pointer family separately.

