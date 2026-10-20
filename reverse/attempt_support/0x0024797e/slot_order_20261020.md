# 0x0024797E GameLogicSnapshot::DoXfer: frame slot order, second pass (2026-10-20)

The bank `reverse/attempts/0x0024797e.cpp` is unchanged at 0.9732 (49
instructions differ, all offset-only). Earlier disproven trials are in
`frame_priority_20261020.md`. Do not repeat them.

## Residue

Only stack offsets differ. The registers, schedule and size (2195 B) match.

    retail: id 0x1c, objectCount 0x20, group 0x24, mode 0x28, second 0x2c,
            tocID group 0x30, begin() temp 0x34 (8 B), guard 0x38, it 0x3c (8 B)
    bank:   it 0x1c (8 B), id 0x20, objectCount 0x24, group 0x28, mode 0x2c,
            second 0x30, tocID group 0x34, guard 0x38, begin() temp 0x3c

## Measured allocator facts (cl 7.1 /O1, small probes)

- Slots are assigned in a stable sort by reference count (descending, ties
  in declaration order), first fit. Function-scope variables conflict with
  every other variable, and sibling scopes share slots.
- The heaviest variables also reuse the parameter home `[ebp+8]` when the
  parameter is cached in a register (esi = xfer). The `[ebp+8]` users are
  identical in retail and the bank (26 references, same instructions,
  including the CreateMask by-value `mov [ebp+8],esp`). That rules out the +8
  lead.
- Probe (buildable store loop plus two function-scope ints `a`, `b`): `it`
  lands last (after a, b). Adding a sibling block `{int d0; x->xferInt(&d0);}`
  before `a` moves `it` ahead of a and b. Giving d0 five references sends it
  to +8, and `it` is last again. So the order depends on first-fit occupancy
  and not only on `it`'s own weight.

## Tried in this pass (all without an exact match)

- **Control flow.** Section bisection: deleting the snapshot+buildable block
  (B6) or the TOC store/load sections (C1234) flips `it` late; C12 is midway.
  Brace-wrapping each of the 14 top-level sections (wrap/): best wrap/toc
  0.9753, wrong structure.
- **Variable lifetime.** Moving the id, tocID and defaultTeam declarations and
  scopes (T1-T6), and splitting id per branch (idv i1-i8): best i1 0.9768, but
  the frame drifts to 0x6c and id moves to +8, so it is not retail's shape.
- **Symbol numbering.** Padding declarations e1-e13 so the `$NNNN` numbering
  shifts: inert.
- **Types and layout.** As the earlier handoff lists, plus the guard with an
  out-of-line ctor and inline dtor as retail calls it (retail 0x233).
- **Callee visibility.** Guard ctor and dtor visibility: no slot change.
- **Compiler settings.** `permute.py --flags`: inert. permute.py itself
  refuses ("only constants or offsets differ: a layout fact, not an order").
  It needs the zero-padded rva `0x0024797e`.

## Open lead

Retail's `it` sorts after guard and begin() temp, so in retail's source `it`
has fewer weighted references than id and objectCount, or a heavier
earlier-declared variable occupies 0x1c first. A function-scope variable that
the bank does not have, with 4 or more references and a lifetime overlapping
the TOC section, would push `it` back. Look for one in the ZH donor
(`GameLogic::xfer`, GameLogic.cpp:4690) that the bank folded away.

Scratch, untracked: `build/c24797e/` (`mini.py` scores, `probe/pr2.py`
prints slots including positive offsets).

Model: claude-opus-5.5.
