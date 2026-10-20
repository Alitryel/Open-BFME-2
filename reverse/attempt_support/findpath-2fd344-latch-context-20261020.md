# FindPath 0x002FD344: the latch reload order is set by the whole function

Result: blocked. The bank `reverse/attempts/0x002fd344.cpp` stays unchanged and is still the best body. Model: claude-opus-5-5. Input revision d94c5bde83 (current `pathfinder.cpp`, bank replayed into the whole owner exactly as `findpath-ordered-latch-20261019/replay.py.txt` does).

## Remaining mismatch (unchanged)

The replay measures 781 B against retail's 781 B with 0 structural regions, 11 memory lines and 0 register lines under `tools/align_diff.py`. Nine of the memory lines are relocations. The other two are the loop-latch reloads at +0x1C1/+0x1C6 (retail 0x002FD505/0x002FD50A): retail reloads y (xmm2, [ebp-0x20]) before x (xmm1, [ebp-0x24]); the replay reloads x before y. That is 4 operand bytes.

## Hypothesis tested this round (callee visibility)

The handle destructor `rva002EAD62` (rowed in `Code/Libraries/Source/WWVegas/WWLib/stlport_auto_ptr_rva0053476A.cpp`, an auto_ptr-style `delete m_ptr`) is opaque in the bank, so the handle local escapes. Hypothesis: a visible select-any copy changes the allocator state that orders the latch. Refuting observation, registered beforehand: the latch stays x,y,z. Outcome: refuted.

| Trial | Size | Structural | Latch |
|---|---:|---:|---|
| Visible copy, `~Rva0053476A() throw()` | 777 B | 1 (drops retail's `or [ebp-4],-1` before the destructor call) | x,y,z |
| Visible copy, destructor without `throw()` | 781 B | 0 | x,y,z |

Making QuickDoesPathExist, FindClosestHierarchicalPath or InternalFindPath opaque at their FindPath call sites (diagnostic) also leaves x,y,z.

## New finding: the order is not a property of the delta, scale or loop statements

- The matched sibling FindClosestPath (0x002FA3F1, same unit, the same backoff loop) reloads z,y,x in retail and in our compile. Its exact delta, steps, scale and `++i` loop spelling transplanted into FindPath gives x,y,z with otherwise identical bytes.
- Truncating FindClosestPath after its loop with a diagnostic `return 0` changes its own latch. Code before the loop does not matter (removing the pre-loop block keeps z,y,x).

| FindClosestPath truncated before | Latch |
|---|---|
| `clippedFrom`, `startIndex`, `parent`, and every point up to `readMoverInfo` | x,y,z |
| `Bool gotHierarchical` (adds `if(!checkForMovement(obj,info)) m_isTunneling=true;`) | y,x,z (retail FindPath's order) |
| the same, with `checkForMovement` replaced by an opaque function | y,x,z |
| `destinationLayer` | y,x,z |
| `startedStuck` and later, or the full body | z,y,x |

The one flipping pair compared in full (truncated before and after the `checkForMovement` statement) also differs in general-purpose register assignment across the whole function, which points at whole-function register allocation rather than at the statements that compute delta.

## What does and does not move the order inside FindPath

- Byte-identical spellings (781 B, only the two latch lines differ), all still x,y,z: field-wise or `copyCoord3D` copies of adjusted, delta and destination; the three steps forms (`/30-1`, `-1-(Int)(len*-1/30)`, a float `dist` local); helpers or explicit fields for scale and the loop subtraction; `i++` or `++i`; `clear()` instead of the erase view; the `pathfinderLog` helpers for both log sites; `*destinationAdjusted = true` after the delta copy; `i` declared outside the loop; nested or split `else if` forms of the hierarchical-result branch; `(double)` log arguments. A 12-variant random combination of these knobs gave the same bytes every time.
- Spellings that change other bytes and keep x,y,z: copying destination before the mineshaft stores, swapping the mineshaft stores, moving `Bool human` or `*destinationAdjusted = true`, declaring destination before the loop, and testing `hierarchical.path` positively.
- Diagnostic probes that keep x,y,z: extra branches, calls, integer locals or escaping aggregates after the loop; extra reads of destination fields; one extra use of any long-lived integer variable (`this`, `from`, `obj`, `locos`, `steps`, `i`), even where it reassigns registers; an extra use of scaled y, x or z before the loop (which changes the registers but not the reload order); unrelated functions added elsewhere in the unit.
- Only float values passed by value to calls flipped it: one float passed twice after the loop gave z,y,x, three floats gave z,x,y, and one float before the loop gave z,x,y. Retail's FindPath passes no float by value, so this is a diagnostic handle, not a candidate.

## Ruled out, with prior rounds

Statement-level spellings of delta, scale and the loop (earlier rounds and this one), callee visibility of every callee that receives a local's address, compiler flags (/G5, /G6, no /G, /Op), struct-copy initialisation (`Coord3D delta = adjusted;` gives 777 B with 25 structural regions; `adjusted = *rawTo` gives 746 B with a `movsd` block copy retail does not have; `destination = adjusted` gives 758 B).

## Next lever

Retail's FindPath must carry an IL difference that changes the XMM allocation order but no emitted byte. Two directions remain. First, find more matched bodies with a multi-value loop-latch reload and correlate their orders with the live-range set, to learn which allocator input decides the order. Second, compare FindPath's post-loop structure with FindClosestPath's flipping region (`checkForMovement` with a by-reference aggregate and a conditional member store), because that region alone produced retail's y,x,z.

Raw evidence is in the untracked seat folder `build/w1_fp/`: `prepare.py` regenerates the whole-owner replay, `set*.py` hold each probe family, `*.align.log` hold the measurements, `latch.py` prints a compiled body's latch, `retail_findpath.txt` and `retail_fcp.txt` hold retail disassembly, and `wb_findpath.txt` holds the WorldBuilder body.
