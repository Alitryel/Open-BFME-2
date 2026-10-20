# 0x00155B00 Render2DSentenceClass::Draw_Sentence (2187 B): handoff

Bank: `reverse/attempts/0x00155b00.cpp`. The previous bank (gpt, score 0.9026) measured 2249 B,
21 regions and 93 diffs (align T514/C510). This bank measures 2201 B, 25 regions and 73 diffs. The
frame is unchanged: flags `/arch:SSE /G7 /EHsc /MD`, ZH `rect.h`.

## Levers that helped (each verified against retail)
1. **Copy into a local whose address is never taken.** `RectClass rect = data.ScreenRect;
   RectClass uv_rect = data.UVRect;`, then build `screen_rect(left, top, w*sx+left, h*sy+top)`
   from it, `+= Location`, and floor each field. Retail loads the copy through registers. The old
   copy into address-taken `screen_rect` left dead copy stores.
2. **Store hoisting in the clip block.** Retail's shape is: store the screen value, `comiss
   screen,clip`, `ja`, store the clip value. That shape needs `clipped_rect` to stay in memory, so
   each field needs two definitions:
   `clipped.L = screen.L; if (!(screen.L > ClipRect.L)) clipped.L = ClipRect.L;` (R `<`, T `>`, B `<`).
3. **Preloaded clip value.** Writing `{ float c = ClipRect.X; ... }` per field preloads the clip
   value into a register as retail does (variant v25: 2193 B, 26 regions, 74 diffs). This fixes the
   instruction shape, but the xmm numbering is still wrong.

## Ruled out (measured by size / regions / diffs)
- Inline max/min, always.h by-value form, as in the ZH donor: 2169 B, 39 regions, 112 diffs.
  `clipped_rect` gets enregistered (slots move to 0x4c-0x58, movaps/jbe). Adding the `add_quad` bool,
  declaring clipped at loop or function scope, or initializing clipped (`= screen_rect`,
  `(0,0,0,0)`) changes nothing.
- const-ref max: 75 regions. Ternary with a local c: 44 regions, 139 diffs. if/else: 93 diffs.
  `ClipRect >= screen` form: 83 diffs.
- No rect copy, field assigns: 112 diffs. No copy, ctor from data: 103 diffs. Location in the ctor
  args: 98 diffs. floor in the ctor args: 213 diffs. Separate width/height floats: 89 diffs.
  uv copy before the rect copy: 82 diffs.
- Float-floor helper variants (gpt, log line ~62520): worse.

## Remaining residue (v18/v25)
- xmm assignment in the clip and percent blocks. Retail: clip temp xmm1, scr.R xmm0, B xmm4, T xmm6,
  L xmm7, uv.L xmm5. Ours: clip xmm0, R xmm3, B xmm6, T xmm5, uv.L xmm4.
- Operand and scheduling order in the percent (uv interpolation) block.
- Extra `movss [esp+0x14],xmm0`: screen.Left+Location.X is stored before floor, and retail
  omits the store.
- `add ecx,eax`/`push` register swap at 155ecf; prepass load order; the tail.
This body is the only link blocker of 2 units that hold 604 B (log line ~65084).
