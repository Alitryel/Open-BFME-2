# 0x0024797E DoXfer: the exact colouring requirement (2026-10-21)

The bank is unchanged (2195 B, bytediff 47, slot displacements only). This note
replaces the earlier priority/first-fit guesses with c2's actual stack-colouring
rules, traced on the bank (`build/agAE/sct.py --focus DoXfer`). It names the one
conflict-set difference retail has. Model claude-opus-5-5, about 60 minutes.

## c2 rules (3077, verified by replay)

* `colorElemental` (0x91426) takes elements in order: size ascending, then weight
  descending.
* Each element scans the existing colours from the **newest down to colour 1** and
  joins the first colour where all of these hold:
  * element size <= 2 x colour size;
  * the element is not in any member's conflict set;
  * its own conflict set contains no member.
* Otherwise the element opens a new colour.
* Conflict sets are asymmetric. The guard's own set is empty, but 23 later elements
  list the guard.
* A replay of exactly these rules (`build/dx/lay.py`, scratch) reproduces the
  traced colouring 1:1.

## Bank colouring vs retail

* Bank colouring:
  * `it` (8 B, element 30) conflicts with the guard (element 28, colour 10). It
    therefore falls through to colour 3 {value, defaultTeam, end}, at [ebp-0x1c].
  * The `begin()` temp (element 31) then joins the guard's colour 10, at [ebp-0x3c].
* Retail layout (it -0x3c over guard -0x38; begin temp -0x34 sharing the tocID
  dword) is exactly the replay with **one conflict removed: it–guard**. Then
  `it` joins colour 10 {guard, it}. The begin temp skips colour 10 because it
  conflicts with `it`, and joins colour 9 {slot, tocID, status, status, slot,
  begin temp}, an 8-byte colour.
* In this function, `it` and the guard are the only pair whose conflict decides
  the layout.

Supporting stack-weight probes (`build/dx/wt.py`, scratch copy of agAP's wtpatch):

* `it` weight -2 puts -0x1c..-0x2c at retail's offsets (bytediff 47 to 37).
* Adding begin temp -1 gives bytediff 33.
* Weights alone cannot finish it, because the remaining difference is a colour join.

## What does not remove the it–guard conflict

* `it` declared at the top of the function, before the guard, after the guard,
  or in the storing `if` block, with the loop as `for (it = ...)`. All four
  leave it's conflict set unchanged (11 entries, including the guard) and the
  score unchanged (`build/dx/gen.py`).

## Facts for the next seat

* Elements after the guard's ctor that do **not** conflict with the guard:
  * `defaultTeam`, which is never address-taken;
  * the `begin()` hidden-return temp, which is address-taken but has no call in
    its live range.
* Every other later element conflicts with it, including `end`, `status`, `slot`,
  `empty`, `it` and the hash temps.
* Retail calls the guard ctor out of line (`lea ecx,[ebp-0x38]; call 0x4224C`). Its
  dtor is inlined at the end (`dec [TheGameLogic+0x1b4]`), and its EH state 3 is
  active through the buildable loop. So retail's guard is the same object; the
  difference has to be in how `it`'s live range or escape is seen.
* Where the sets are written: c2 0x91db3 (`push conf[ebp]; eax=edi; call
  0x107afac0`, an SBV or). Each element receives its whole set in one call:
  * `it`: [0,6,8,10,11,13,14,22,28,30];
  * begin temp: [0,6,8,10,11,14,31].
  The set in `edi` is accumulated per element by the code that jumps to 0x91da3.
  The c2 code there is hot/cold split. Scratch hook:
  `build/dx/confwhy2.py SRC --focus DoXfer --idx 30,31`.
* (The other site, 0xa0779 in 0x909b1, fires once and is not the one.)
* Next: find who builds that `edi` set (a live-set union over the element's live
  points). Then test whether the guard enters it at the loop body's throwing calls
  (EH liveness). If it does, retail's `it` stack home must not be live across a
  throwing call, so look for a loop shape that only stores `it` right before the
  out-of-line `++`.
