# 0x000909B7 Vp6Stream YUV→ARGB texture upload (1467 B)

**Landed exact (2026-10-20)** in `Code/GameEngine/Source/Common/Rva007E3C20Vp6StreamDtor.cpp`.
What closed it, after the 0.7797 stage below:

1. `/G7` on the unit (found by `permute.py --flags`; both earlier bodies stay
   exact): 0.8469.
2. The plane dimensions assigned inside the two forceinline converters rather
   than in the upload: 0.9072.
3. The converter takes the lock result as `void *bits` and declares
   `unsigned int *dest = (unsigned int *)bits;` late, next to `next`: 0.929.
4. A random search over the source order of the eight alpha-path dimension
   stores (`docs/recipes.md`, Frames, stores and locals): 0.9977, then a
   single move gave exact. Retail's scheduled store order, its reverse,
   twin-field copies and `uv = y >> 1` from a field were all worse.

The rest of this file is the history at the 0.7797 stage.

Bank: `reverse/attempts/0x000909b7.cpp`, fit 0.7797, 1464 B (retail 1467 B).
It is the whole `Rva007E3C20Vp6StreamDtor.cpp` TU with the body appended. The
flags are the file's own: `/O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc`.

## Evidence

Target facts:

- Retail vftable 0x00BC7F20 slot 3.
- `__EH_prolog` frame, `_chkstk` 0x109C.
- The device lock guard: Lock 0x0011F520 in its ctor, Assert 0x00120F50 in its dtor.
- `VP6_GetYUVConfig` 0x001B5C60, called once on the opaque path and twice on
  the alpha path (format 5 and `m_at38` set).
- The YUV tables at 0x00DE2098..0x00DE3498 (alpha, vRed, vGreen, uGreen, uBlue,
  clip[0x400]).
- The `row[1024]` staging buffer at ebp-0x10A4, copied to the next row with
  `memcpy`.

Donor (structure, not target proof): Open-BFME-1's own banked reconstruction
`targets/game/reverse/attempts/0x007e3e60.cpp` (BFME 1 at 92f6bbe8e). This
is game-side stream code, not the VP6 decoder, and no decoder source was read.

## Where the bank stands

The two inner pixel loops matched instruction for instruction in `fbb`. `fbb`
is the bank minus the `temp` change below, and scored 0.7699.

The bank declares `temp = row` at the top of the outer loop body instead of
resetting it after the memcpy, which raises the fit to 0.7797. But it reorders
the first inner loop's table loads, so `fbb`'s placement of `temp` is the
structurally safer base when testing slot hypotheses.

What is left is register and stack-slot allocation in the two setup blocks:

- Retail stores `frame.yHeight` early and reloads it; ours keeps it in `edi`.
- The slot packing differs (retail vs ours).

Retail slots on the alpha path:

| Variable | Slot |
|---|---|
| a1 | -0x10 |
| dest | -0x14 |
| temp | -0x18 |
| v | -0x1C |
| pitch, reused for blue | -0x20 |
| u | -0x24 |
| y1 | -0x28 |
| lock result, reused for the outer count | -0x2C |
| uvstep | -0x30 |
| j, reused for the inner count | -0x38 |
| red | -0x40 |
| dststep | -0x44 |
| 2*pitch | -0x48 |
| astep | -0x4C |
| ystep | -0x7C |
| frame cfg | -0x74 |
| alpha cfg | -0xA4 |

Retail's alpha dimension stores run in this order: `alpha.uvHeight`,
`alpha.yHeight`, `frame.yHeight`, `frame.uvWidth`, `alpha.uvWidth`,
`frame.uvHeight`, `frame.yWidth`, `alpha.yWidth`.

## Trials (none disproven twice)

Better:

- Form B (from BFME 1): u/v from `(uvHeight-1)*uvStride`, with `j` only a
  counter. It reproduces retail's `lea` for `j`. 0.7597 → 0.7692.
- Configs scoped to their if/else blocks: 0.7699.
- `temp` inside the outer loop: 0.7797.

Neutral or worse:

- control flow: alpha-first dimension stores, chained assignments, `y0` from
  `m_at34`
- lifetime: `j` declared first; config declaration order; one shared config;
  `row` declared in the caller and passed in; inert locals k=1..30 at the top
  and in the alpha helper
- types and layout: `next` as `unsigned int *`; `dest += dststep/4` (worse,
  0.674); the helper parameter order swapped
- callee visibility: both helpers are `__forceinline` members, which retail's
  single body requires

Compiler settings were left to `permute.py --flags`, which runs against this
bank.
