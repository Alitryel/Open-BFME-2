# 0x0014C470 MeshClass::RecolorHouseColor: slot membership trials (opus seat, 2026-10-20)

Starting point: `reverse/attempts/0x0014c470.cpp` (2291 B, structurally exact, 71 differing
instructions, every one a `[esp+N]` displacement). Slot table and earlier ruled-out list:
`0x0014c470_20261020_w2_wb_accessors.md` and `0x0014c470_20261020_jacob_type_controls.md`.

## Target of the remaining work

Retail packs `textureIndex` (n) and the `AsciiString(source.name)` key temporary into the slot of
the *second* effect handle (the `rva0007B9EE()` temporary in the `->rva0015148D()` operand of the
FX condition, WB `local_134`, conditional-temporary flag bit 2). Ours puts both into the EH
conditional-temporary flags slot; that slot then outranks the model holder, which swaps holder/flags
(0x08/0x0C) and shifts the effect-handle slots (second 0x10 vs ours 0x1C, first 0x14 vs 0x10,
setup spill 0x18 vs 0x14).

## Ruled out this round (scratch compiles, all inert: same 71 instructions, 2291 B)

- `permute.py --flags 0x14C470` (flag sweep on a depth-adjusted copy): inert or worse.
- `permute.py` body permutation: refuses the residue ("offset-only diff is a layout fact").
- TU temporary-counter bump (dummy functions with N temporaries ahead of the body): inert.
- Local rename sweep (24 names, 2 passes; slot order by name hash): inert.
- WorldBuilder's named condition bool (`bool usable = setup && X().p && X()->rva0015148D();
  if (usable) {...}`), both initialised and assigned forms: inert.
- docs/recipes.md "Block-scope address-taken locals" lever: n and the key temp are already in
  closed blocks; earlier seats also widened/narrowed them (key in its own block, textureIndex earlier).

Next untried angle: give the FX condition temporaries a different lifetime class (e.g. spell the
`.p` test through an inline accessor that takes the handle by value, so the first two handles are
no longer conditional temporaries) and watch whether the flags slot stops absorbing n.
