# 0x24797E DoXfer: rename sweep (2026-10-21)

Tested the name-hash slot-order lever (memory/recipe from 0x560B11: locals
with equal weight are ordered by name) on the bank `reverse/attempts/0x0024797e.cpp`.

- Buildable-map iterator `it`: 40 replacement names. Every variant compiles
  to 2195 B, nd 87, bytediff 47, the same as the bank.
- `id`, `objectCount`, `guard`, `second`, `tocID`, `defaultTeam`: 10 names
  each (a, zq, k9, objId, tmp, b7, xx, m, w3, qq), renamed with the regex
  `(?<![\w>.])var\b` inside the DoXfer body only. All 60 variants are
  identical to the bank (2195 B, nd 87, bytediff 47).

Verdict: the residue is not a name tie-break. Slot order is decided by
weight or lifetime, so the open lead in `slot_order_20261020.md` (a missing
function-scope variable from the ZH `GameLogic::xfer` donor) still stands.

Model: claude-opus-5.5.
