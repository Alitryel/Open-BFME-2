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
