# findBestTarget 0x005735C6: best-scope allocation flip (seat7, 2026-10-19)

Target `0x005735C6..0x0057377E`, 440 bytes, bank `reverse/attempts/0x005735c6.cpp`
(unchanged, 440 B, 6 differing rows). Native: the unit-null branch jumps straight
to the outer increment and `best = 0` is stored after the null test, so `best`
belongs inside the unit branch (WB 0x01504010 uses `if (!unit) continue;` and
declares best after it).

Every spelling with `best` defined only on the unit path compiles to 424 B with
118 differing rows: cl then gives EBX to the outer iterator and EDI to the inner
iterator and leaves `obj` and `structures` in memory, where native keeps the outer
iterator in EDI, `structures` in EBX outside the inner loop (reloaded from
[ebp-0x18] at the back edge) and `obj` in EBX inside it, with the inner iterator in
the dead `defender` slot.

Tried this session, all 424 B / 118 rows (scripts beside this file, run through
`tools/explain_mismatch.py` from `build/`):

- 81 declaration positions of `s`, `obj`, `unit`, `best` (function top, outer-loop
  top, first use), continue form;
- `continue` / split `continue` / `if` inner forms x `int` / `ObjectID` key x
  inline `getPosition()`/`getID()` accessors x best/bestDistance order, with
  `isValidTarget` returning `bool`;
- WB record temporaries (`myStats->units` then `get()`): 428 B, worse.

The inline-accessor lever that closed the sibling 0x005A9F70 (same owner-read
shape) does not move this allocation. The dtor residue (0x21B775 vs 0x286852,
map<int,int> vs the map<int,void*> family) is independent and still a pin question.
