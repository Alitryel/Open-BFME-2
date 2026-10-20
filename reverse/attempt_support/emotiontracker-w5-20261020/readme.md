# EmotionTrackerUpdate::update 0x4B1633 (2200 B), w5 session 2026-10-20

Continues `../emotiontracker-r48-20261020/readme.md`. The banked body
`reverse/attempts/0x004b1633.cpp` (score 0.99) now carries the ZH colour idiom
below; bytes are unchanged (2194 B, case-2 call order at +0x572 differs).

## Finding: two counters, not one

Harness: insert N unused `int dK=K;` locals (B meter) and sweep N (step 2).
Pattern letters: a = 2194 B (bank residue), X = exact 2200, b = 2206 B.

| body | pattern (N = 0, 2, 4, ...) | exact for N |
|---|---|---|
| old bank | `a x31 XXXX bbbb a x8 XXX` | 62..68, 94..100 |
| bank + GameMakeColor | `a x15 XXXX bbb a x9 XXXX bbbbbb ...` | 30..36, 62..68, 94.. |

* The exact windows have period 32 (phase counter). With the GameMakeColor
  variant the window N=-2..4 would already contain N=0, so the phase is right.
* A separate minimum (threshold counter) hides windows below it: >36 for the
  old bank, in (4, 30] with GameMakeColor.
* The meter's position does not matter (the loop anchor gives the same
  pattern): it is a whole-function count.

What moved the threshold, phase-swept:

| edit | effect |
|---|---|
| `inline Color GameMakeColor(r,g,b,a)` for the three debug circles (ZH idiom; `__forceinline` the same) | threshold -32, phase unchanged |
| only 1 or 2 of those calls | nothing |

Calibration on the GameMakeColor body (diagnostics only, NOT shippable padding):

| added at `Object *closest=0;` | first exact |
|---|---|
| unused `GameMakeColor(1,2,3,4);` statements | 7 |
| `unsigned long uK=GameMakeColor(1,2,3,4);` initialised locals | 3 (4 is also exact; 5+ gives 2206) |

So the original has about seven more inline calls with parameters (or about
three initialised locals fed by such calls) than this body.

## Tried here, all bytes-neutral but none closes on the GameMakeColor base

32-way factorial: `fa/` = {kind, dbg, ft, fset, nug}, all 2194:

* kind: forceinline `Object::isKindOf` -> `ThingTemplate::isKindOf` byte form
  (`m_kindOf[t>>3] & 1<<(t&7)`).
* dbg: `DbgPos pos(*obj->getPosition())` with an empty dtor. This is WB's
  EH state 0 around the pos copy. On the old bank it shifts the phase +2.
* ft: inline `ThingFactory::findTemplate` wrapper over findTemplateInternal
  (the WB callee).
* fset: `setFlag(i,b)` inline setter.
* nug: the two duplicated nugget-search loops as one forceinline
  `hasNugget(type,enemyCount,allyCount,other)`.
  - Plain `inline` is not inlined (2100 B).
  - `isFriend()` helper: regalloc drift.
  - On its own, nug raises the threshold back to 62.

Also changing codegen (rejected):

* Getters on `EmotionUpdateData` floats: regalloc drift, 2211 B.
* A switch on `active->getType()`: 2192 B.

## Next

Look for the natural source of about 7 multi-parameter inline calls. Candidates:

* An inline wrapper around the debug `circle` virtual (pos, radius, colour).
* Inline wrappers with converted args around the placeholder callees
  `Rva00739830::rva00739830(pos,1,mask)` (BfmePointFD cast) and
  `rva0028F326(other,range)` (unsigned cast).
* `Object::rva00263763(other)` as an inline distance helper.
* A real `testStatus(ObjectStatusTypes)` inline layer.

Measure each with the B-meter sweep from a copy of the bank. Scratch:
`build/w5/e4/phase.py`, `fact.py`, `gm/` (local, untracked).

## Late result: free inline wrappers do not move the threshold

Each of these keeps the bytes, and each body still needs exactly 7 dummy
GameMakeColor calls (g-meter):

* `isWithin(obj,other,range)` over rva0028F326, returning `unsigned char`;
  a `bool` with `!=0` drifts regalloc.
* `countInRange(pos,1,mask)` over rva00739830.
* `distSq(a,b)` over rva00263763.

A `drawDebugCircle(pos,r,colour)` wrapper changes codegen (2185 B).

So it is not the number of parameterised inline calls. GameMakeColor's
constant `(a<<24)|(r<<16)|(g<<8)|b` expression is the likely driver: look for
folded constant arithmetic in the original, such as `sqr()`/`LOGICFRAMES_PER_SECOND`
style expressions, FLT_MAX, or colour and mask construction.
