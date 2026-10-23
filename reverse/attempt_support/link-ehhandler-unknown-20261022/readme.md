# Link census: EH-framed COMDAT copies are never proven retail (false reject)

Date: 2026-10-22. BFME 2 HEAD 7319984d1f; BFME 1 pointer 37c3022de1. Model:
claude-opus-5-5.

## Finding (target evidence)

`RetailTruth._judge` (tools/link_census.py) resolves a relocation only when its
referent is external, a label in the copy's own section, or a content-named
constant. A function with a C++ EH frame pushes its handler stub
(`push offset __ehhandler$<parent>`, DIR32 at +3). That stub is a TU-static in
`.text$x`, so the judge gives it no expected address and the copy stays
`unknown`, even when every byte and every other relocation is retail's. The
ledger rows these stubs (`__ehhandler$<parent>` rows, byte- and EH-verified),
and the name is derived from the parent's mangled name, so the row is retail's
stub for that parent.

Consequence under retail-truth-3: when the only copies matching retail are
EH-framed, no copy is proven `retail`, so `retail_kept` never exempts the other
units' differing copies and each of them counts as a COMDAT loser.

Example: `??1?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAE@XZ`
(row 0x0000B3C0, 63 B, owner `stlport_narrow_string_base_dtor.cpp`). The owner's
copy equals retail's bytes; relocations `__except_list` (absolute), `_free`
(0x30830, lands) and `__ehhandler$...` (row 0x0075B7CB, lands when resolved).
Judged `unknown`; 31 other units' copies are `wrong` and lose.

## Measurement (index brought to HEAD with --update-index, then every object
re-judged under the current ledger)

- Cause of `unknown` verdicts across all ledger objects: the `__ehhandler$`
  static alone is the only unresolved referent for 5,479 judged copies, by far
  the largest single cause (next: data globals with no address, e.g.
  `?g_freelistPool@@3VFreelistPool@@A` 1,439, `TheWritableGlobalData` 174).
- With `retailtruth-ehhandler.patch` applied: 3,260 COMDAT copies (2,950 names)
  go `unknown` -> `retail`, 2 go `unknown` -> `wrong`, none change otherwise.
- link_check over the 1,783 census files that did not link: 122 -> 125 link,
  LINKED 153,911 -> 163,510 bytes (+9,599). Most affected files hold other
  blockers too, so the effect grows as those are fixed.

## Why not landed here

The verdict change moves census figures, so it is a rule change
(retail-truth-4 after retail-truth-3), which needs the census to measure the
previous rule in the same judgment (a second RetailTruth without the
resolution, feeding previous losers and previous wrong_selected) and
`census_rebaseline.py` to record it. BFME 1's link_census.py has the same
limitation (its `_judge` also leaves statics unresolved), and the two projects
measure LINKING the same way, so the change should be decided for both.

## Proposed patch

`retailtruth-ehhandler.patch`: resolve a static `__ehhandler$` referent through
`self.ledger` (rows only, never pins). Needs, for a landing: RULES bump with
in-process previous-rule measurement, a test that an EH-framed copy whose stub
lands on the row is `retail` and one whose stub lands elsewhere is `wrong`, and
`tools/tests/test_gate_exploits.py` still refusing every case.

## Resolved upstream

Burachi-3D landed the same resolution independently as 893116198
("link_census: judge __ehhandler$ referents by their ledger row") with the
retail-truth-4 rules (99874b268, ae3b3e68e) the same morning. The proposed
patch here is superseded; keep this file only as the measurement record.
