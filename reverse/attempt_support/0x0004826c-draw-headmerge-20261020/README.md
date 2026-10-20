# 0x0004826C W3DDisplay::gatherDebugStats: draw's third packing reference (2026-10-20)

Not exact.

**Two bases:**
- Bank: 4101/4101, 13 bytes.
- True base: the bank without `releaseBuffer() throw()`, which is `build/agW/b0old.cpp`. It scores 44 bytes, nd 48.

**Why the 13-byte bank is misleading.** Its nothrow line removes font's conflicts with the EH objects, so font joins fpsString's colour. That reaches retail's name/perLine order by coincidence, while font and the loop counter themselves stay wrong.

## Mechanism (c2 3077)
**Element order.** AddStackElement keeps a weight-sorted list. Ties keep the order in which elements reached their weight, i.e. the IL order of each element's last reference.

**Colouring.** colorElemental (0x91426) puts each element in the newest compatible colour.

**Layout.** Applies only to frames over 0x80. It is a recursive quicksort at 0xAE0C4 with comparator 0xAE9C2:
- the middle element is the pivot and is swapped left;
- Lomuto partition;
- key is weight*1000/size, descending; equal keys compare as 0.

`build/agW/tools/sim.py` reproduces both banks' traced layouts exactly.

**What retail needs.** The throwing-releaseBuffer conflicts, plus `draw` with 3 packing references. `draw` must be visited in the weight-3 group before element 0x611. `sim2.py` found that only `draw`+1 fits.

**Weights are counted at StackPacking.** Afterwards, `dop2_FinalFlowOpts` deletes tuples through `TupRemoveRange` (0x9724C), via FgDoHeadMerge, FgTryTailMerge and FgTryCommonTailMerge. `rm.py` lists them; in our build, for example, unibuffer has 77 references in the IL but 75 in the code.

**Retail's third `draw` reference** is a spill store duplicated onto both out-edges of the first `if (draw)` branch, then head-merged above the `je`. The evidence: store at +0x90D/+0x90F/+0x912 between `cmp eax,ebx` and `je TERRAIN`, and only +0xC30 reaches the reload at +0xC44.

**Ours** stores right after the definition in block 69, because `draw`'s candidate covers blocks 69 and 70 (`obj = [draw+0xFC]`). The split comes from ColMakeSplitPoint (return address 0x1090E), not SpillOrDefer.

## Ruled out (throwing base, all still 44)
- WorldBuilder shape `Object *obj = 0; if (draw) obj = draw->m_object; if (obj)`.
- A `Drawable *&` alias.
- An inline `Drawable *const &` helper.
- A copy at the definition.
- `throw()` on findDrawableByID, getMousedOverDrawableID, getFirstSelectedDrawable and getSelectCount.

Code changes instead:
- goto: 4096 B.
- Copy after the block: 4107 B.
- Nested if with a duplicated TERRAIN arm: 48 B.

## Next
Find an honest form in which the obj load in the non-null arm does not use draw's register candidate, so draw's piece ends at the branch and c2 places the store on both out-edges. Check each candidate with:
1. `rm.py --focus gatherDebugStats`: look for a FgDoHeadMerge removal of a tuple whose def is `(2, e, '_draw')`.
2. `sct.py`, then `sim.py --verify`.
3. `score.py`.

Tools: `build/agW/tools/` (sim.py, sim2.py, rm.py, passes.py, splt.py, sod.py, sbs.py, wvf.py, var.py, plus agT copies).
Model: claude-opus-5-5, subagent.

## Second pass: mechanism proven, slot-correct near miss
**Best near miss:** `build/agW/v_d5.cpp`, size 4104/4101, nd 7.
- Every stack slot matches retail.
- Only the store placement differs: the store sits at +0x91D in the non-null arm and +0xA02 in TERRAIN, where retail has one store at +0x90F.
- Change, applied to the throwing base:
  ```
  Drawable *draw; Object *obj = 0; Drawable *mouseDraw = find...;
  if (mouseDraw) { draw = mouseDraw; obj = mouseDraw->m_object; }
  if (obj) {...} else { draw = mouseDraw; TERRAIN }
  ```
- Also slot-correct at 4104 B: `v_d2` (nd 9), `v_d3` (nd 9) and `v_d6` (nd 8).

**Established:**
1. **Spill stores follow definitions.** `CmdInsertExit` (0x8C9B3, from 0x8B79C inside ColProcessSplitGlobregs) puts one op-619 store after each definition of a split candidate. RewriteSplitGlobregs puts the reload (op 618) in a new edge block. So two stores need two definitions.
2. **Accounting.** Packing weight minus the references removed by merges (TupRemoveRange from FgDoHeadMerge/FgTryTailMerge/FgTryCommonTailMerge) equals the final reference count; read-modify-write counts twice. This holds for every 4-byte colour. Retail's -0x18 colour balances with `draw` at 3 and one merged-away reference.
3. **The merge is a head merge at the first `if (draw)` branch.**
   - Shape: `cmp eax,ebx; mov [ebp-0x18],eax; je`.
   - Not a tail merge: only +0xC30 reaches the +0xC44 reload.
4. **What blocks it.** Both successors need a single predecessor and must start with an identical `draw = eax` store.
   - A copy in the null arm is constant-folded to ebx (zero), so the two stores differ.
   - With TERRAIN shared, it has two predecessors, so no merge happens.
   - FgEarlyTailDup only duplicates blocks of at most 2 tuples (size × predecessors ≤ 8).

**Next:**
- Find the pass order of branch-condition constant folding against jump threading and tail duplication.
- Find a 2-tuple join block whose duplication puts the copy on both edges.
- Check whether the zero register can be something other than ebx.
- Verify any candidate with `rm.py`: look for a FgDoHeadMerge removal of the op-619 store of `_draw`.

Tools (in `build/agW/tools/`): `ilsnap.py`, `ins.py`, `exits.py`, `acct.py`, `rm.py`, `sim.py`, `sim2.py`, `splt.py`, `sod.py`, `passes.py`, `sbs.py`, `var.py`.
