# FindPath 0x002FD344: a single inline expansion of exactly k parameters closes the latch

Result: blocked (no natural form found). The bank `reverse/attempts/0x002fd344.cpp` is unchanged and still the best natural body. Model: claude-opus-5-5. Inputs: master 5769adaac3, bank replayed into the whole `pathfinder.cpp` owner (same replay as `findpath-ordered-latch-20261019/replay.py.txt`). Scorer: `tools/align_diff.py`. Exact means 781 B, 0 structural regions and 9 memory lines, all of them relocations.

## Baseline

The baseline is 781 B, 0 structural, 11 memory lines and 0 register lines. The two extra lines are the loop-latch reloads at +0x1C1/+0x1C6. Retail reloads y (xmm2, [ebp-0x20]), then x (xmm1), then z. The replay reloads x, then y, then z.

## Proof that the residue is a c2 numbering effect

I inserted `static __forceinline void kdum(int d0, ..., int d{k-1}) {}` before the helpers. One `kdum(0, 1, ...);` statement then went at each position below.

Each position has its own window. Below the window the result is 11 memory lines (baseline order). Above it the result is 12 (another wrong order). At exactly one k the result is 9, which is byte-exact.

| Position (inserted before) | Exact at k | Notes |
|---|---:|---|
| top: `if (g_00E03745)` log block | 18 | 4..17 give 11; 19..64 give 12 |
| adj: `Coord3D adjusted; copyCoord3D(...)` | 17 | |
| dlt: `Coord3D delta; copyCoord3D(...)` | none | 13..18 give 11; 19 and 20 give 12 |
| lp: `for (Int i ...)` (after the scale) | 16 | 4..15 give 11; 17..64 give 12 |
| inl: the loop's `subCoord3D(&adjusted, &delta)` | 16 | |
| aft: the hops erase block | none | 17 gives 11; 18 gives 12 |
| dst: `Coord3D destination; ...` | 14 | |

What counts at lp:
- The parameter type does not matter. int, float, `const Coord3D *` and variable (not constant) arguments all give exactly 16.
- One expansion tree counts as a whole. An outer `kdum(8)` whose body calls `kdumB(8)` closes it at 8 + 8 = 16.
- Separate statements do not add up. Two statements of 8 parameters each (the same function or two different ones) give 11 for every k from 1 to 32. So does the same 16-parameter call twice.
- A smaller expansion after the 16-parameter call keeps it exact (1 to 3 parameters tested). Two or more parameters before it break it (11).
- Extra parameters on the existing helpers behave differently:
  - On `subCoord3D` they are inert for every k up to 32 (11).
  - On `scaleCoord3D` they jump from 11 straight to 12 between 15 and 16 extra parameters. There is no exact window.

Inert (11 everywhere):
- unused locals (int, float or Coord3D) in the body;
- locals inside an inline helper (`int aN = N;` with up to 18 of them);
- empty inline calls repeated up to 18 times;
- 10 to 300 dummy class declarations before the function or at the top of the TU;
- a 4-, 16- or 40-parameter non-inline function before FindPath;
- moving the FindPath block to the end of the TU.

So the effect is local to the function. It depends on the parameter count of one inline expansion tree in one statement, not on total symbols.

## Natural forms tried this round (none reach a window)

| Variant | Result |
|---|---|
| Log names through `((const AsciiString *)...)->str()` (file precedent at the 0x2FBBEB log) | 783 B, 1 region, 12 |
| `steps = (Int)(...); steps--;` and `steps -= 1;` (WB stores `local_34` twice) | 11 |
| `Coord3D &d = *dst` alias inside `subCoord3D` | 11 |
| Derived `FPCoord : Coord3D` for adjusted/delta/destination, with an empty inline ctor, an empty dtor, or both | 11 |
| The same view with an inline copy ctor (with or without a dtor) | 761 B, 21 regions |

## Next angle for a closer

The dummy call must not land. To land, a closer needs a real inline expansion tree in one statement with the right parameter total at a position that has a window: 16 between the scale and the loop or at the loop's first sub, 14 at destination, 17 at adjusted, 18 at the top.

WB D48230 shows only member operators there:
- `Coord3D::operator-=`, `operator*=`, `length` and `Normalize`;
- a `Coord3D` with a destructor (EH states on adjusted, delta and destination);
- `Coord3DBase` parameters for `from`.

None of these alone has that arity. One candidate is a real inline header chain where one member calls nested setters, so the whole tree counts as one expansion. Check it with the nest probe first: an outer helper of a parameters calling an inner helper of b parameters, a + b = 16 at lp.

The probe scripts (scratch, untracked) were `build/s2fd/rk2.py` (positions), `rk3.py` (kinds: split, two, dup, nest, p16a, p16b, ptr, flt, var, loc, rep0) and `dcl.py` (class declarations).
