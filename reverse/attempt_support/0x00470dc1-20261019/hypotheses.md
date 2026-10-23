# Target 0x00470DC1

Start: 2026-10-19 02:23:14 UTC. Model: gpt-6.1-sol. Base commit: 0d8d778ff93a2a6a95bceba097f36d17be78eb6b.

Read all four verdicts in reverse/re_attempts.log and all bank comments before experiments. The sole explicit prior evidence path, build/wb_470dc1_full.txt, is absent in this checkout. The cached parent audit under reverse/attempt_support/crack-g-parents-20261014/parent-audit.tsv agrees with the identity caution. No earlier experiment sources or diagnostics for this target were found under reverse/attempt_support.

Retail evidence is captured verbatim in retail.txt. Ghidra records the 1699-byte boundary; retail ends in ordinary ret immediately before the next prologue at 0x00471464. Primary vtable slot 35 contains this address. The caller uses primary this, and calls through secondary +0x11C and primary +0x90, with no stack parameters to this function. Callees are checked against current rows. This supports the address-derived virtual member name and existing target view, without identifying its original method name. The record descriptions in the prior bank remain structural inferences.

Baseline experiment: reconstruct the fragment in a scratch copy of the current home unit, with its exact build flags and all existing definitions. First run explain_mismatch, then align_diff against the resulting fresh object. Refutation: a compile failure or changed call resolution would show that the old bank cannot be reproduced with current dependencies.

H1 (before first shape experiment): replace the loop-scoped named ID with the full-expression getID() temporary in m_170.find. Retail stores the ID and later attacker pointer in the same [ebp-0x18] slot. The bank keeps an int ID at loop scope and a separately declared attacker pointer. A temporary with a shorter C++ lifetime may let MSVC reuse that slot, restoring the four-byte frame allocation and reducing memory differences. Refuted if the frame and slot offsets stay unchanged or alignment metrics regress.

H2 (independent, before its experiment): cache TheGameLogic in a local immediately before the two attack-pair lookups. Retail explicitly loads it once into ESI at +0x19A, then uses the same ESI for both calls. The bank rereads the external pointer for each call, because the declaration alone cannot prove it unchanged. Refuted if the local produces another allocation or adds structural, memory or register differences.

Baseline reproduces 1700 bytes, 36 structural regions, 75 memory and 31 register differences, with 1381 positional differing bytes after the normal relocation patch. This positional count is not the previous author's undefined nd179 metric. H1 is byte-identical to baseline. H2 and H12 regress to 37 regions, 79 memory and 34 register differences (1696 bytes, 1389 positional differences); the cached GameLogic changes XMM allocation elsewhere.

H3: correct the held-position branch from target evidence. Retail keeps ESI pointing at obj+0x38 at +0x577 through the +0x638 release-range test; +0x646 jumps into the copy at +0x652 without forming the held-record pointer. Thus the intermediate release band copies obj->m_position, not slot->m_position. Only +0x648 forms the held-record pointer in the no-leader/no-range path. Move that pointer construction into its actual else arm, and model the count as unsigned because +0x650 branches with JA. Refutation: correcting these accesses still leaves the early pointer spill and the signed count test in generated instructions.

H4: initialize offset and toClosest directly from component differences, instead of POD copy followed by subtraction. Retail has scalar subtracts at +0x577 and +0x42D, without movsd copies. The existing bank emits those copies, which demonstrates that the compiler does not remove the POD materialization. Refutation: direct initialization keeps the redundant movsd or worsens alignment. Test offset and toClosest independently before combining.

H3/H4 observations: H3 has 38/96/50 regions/memory/register. Direct offset or closest differences reduce regions to 23 or 22, but worsen memory/register versus baseline (94/47 and 92/45); neither qualifies for replacing the bank. The H3 correction also flips this/object between EDI/EBX. Retail uses a member-position pointer in ESI through the release-band copy.

H5: use a local member-position pointer throughout the held-slot calculation, matching retail's ESI at +0x577. This reduces repeated references to obj in that arm and lets the object pointer die there. Separately, use a TU-local derived Coord3D with a member-wise copy constructor for offset/toClosest, as the existing HordeDelta2D sibling does. Coord3DCtorView.h establishes retail's user copy constructor at 0x004216D3; the constructor should scalarize the copies without changing the shared header or the POD assignment copies that retail still emits. Refutation: register allocation remains flipped or redundant movsd survives. Compare each independently and combine only supported effects.

H5ctor qualifies as closer: 27 regions, 56 memory, 28 register versus baseline 36/75/31. Copies scalarize and callee-saved allocation returns to EBX=this, EDI=obj. The pointer-local variant regresses. Preserve H5ctor while investigating remaining independent regions.

H6: retry the explicit GameLogic cache on H5ctor, because changed live ranges removed the H3 allocation regression. Separately express the final side and held-position updates as scale-then-add operations: retail loads all three values before multiplying and interleaves multiplication with adding the destination, unlike the bank's independent component assignments. The matching notes document precisely this scalar-replacement distinction. Refutation: extra structural regions or any operand category regression. Retain trials separately even when not bankable.

H6 observations: logic cache again adds a region; scale-then-add does not reproduce the fused held stores. H6closest trades memory improvements for a register regression against H5ctor and is not adopted. H5ctor remains the best candidate that improves every class over the old bank.

H7: use Coord3D's void inline scale/sub/add APIs in place of reference-returning operators. These are the established donor APIs and retain the same arithmetic; retail's grouped preloads at +0x369 and +0x5E7 differ from the operator form. Test scale separately from sub/add to identify which inline boundary changes scalar replacement. Refutation: identical output or category regression.

H8: construct a local copy of self's position before subtracting it from pos in the facing branch. Retail explicitly loads self.x and self.y to registers before their subtracts; H5ctor instead folds each memory operand and performs y first. A member-wise user constructor can preserve those independent inputs as scalar locals. Refutation: no preload/order correction or added copies. This uses the same verified constructor view as H5, without changing a shared header.

H8 improves to 27/55/27, 1690 bytes and 1190 positional differences. H7 is identical to H5ctor. H8 matches the facing branch's instruction count and x-first preloads; the zero-XMM initialization and final two stores remain reordered.

H9: invert the held-count guard so the zero-count copy is the first arm, matching retail's JA to the decrement block. Separately factor the two held-position copies through one local source pointer and explicit shared copy label; retail proves their shared copy tail at +0x652, with ESI either obj+0x38 or node+0x14. This is the same control flow and target arithmetic, without synthetic accesses or compiler barriers. Refutation: no shared tail or additional operand differences.

H9invert reaches 25/56/27 and H9merge reaches 32/51/28. Both trade categories against H8 and are retained as diagnostics, not replacements for H8.

H10: copy the address-escaped pos or side into a member-wise constructed local before scaling. The Normalize calls make those source objects address-escaped; plain scalar operations on their memory retain sequenced stores, while a fresh local can be scalar-replaced. Retail's +0x369, +0x472 and +0x5E7 preloads are evidence for this distinction. Test pair, side and held arms independently. Refutation: the fresh copy emits movsd, extra stores or category regressions. Unlike H6's direct scale-then-add, this gives the scaled value its own unescaped lifetime.

H10side improves H8 to 26/51/27 without changing emitted length or positional byte count. H10pair and H10held compile identically to H8. Retain the side-only form.

H11: represent dx/dy/dz as a member-wise constructed Coord3D difference before computing the perpendicular. Retail consumes these components as one scalarized triple at +0x3EA, whereas the bank declares three independent floats. H5 established that local construction affects scalar identity and load grouping. Refutation: identical output or a category regression.

H12: zero dir.z before writing its x/y differences. Retail initializes zero XMM2 at +0xEB, before the first subtract, and stores z before x at +0x119. The source currently zeros z after those assignments; statement order is a documented scheduling lever. Refutation: the zero initialization stays late or another category worsens.

H11/H12 combined improve to 21/48/24, 1686 bytes. The facing branch now matches its complete local operation order; its remaining offset comes from the frame. The perpendicular construction also loses several structural differences. Positional differences rise relative to H8 because later instructions shift, but remain below baseline; the alignment metrics determine selection.

H13: test non-POD construction for the returned position itself. The original Coord3D copy constructor is independently established, while the bank's slot7 result is POD. First construct the existing local derived view from the returned Coord3D. The view needs a base assignment preserving the POD copy operations that retail proves. Refutation: an extra hidden-return temporary or new copies instead of improved scalar replacement. This is a scratch test of the known constructor contract, not a new identity claim.

H13 regresses to 21/125/35 and introduces the predicted extra returned-value temporary. Keep the POD return local.

H14: place length's assignment inside the first comparison. Retail stores the float with FST but immediately compares its still-live x87 return value with the double product at +0x5AE. The current source's separate declaration instead emits FSTP followed by FLD/FXCH. An assignment expression explicitly consumes the producer value while preserving the float for the later comparison, and might also alter the conflicting spill slot. Refutation: FSTP/FLD/FXCH remain or any alignment class regresses.

H14 is identical to H11both. The remaining compiler differences do not yet have another supported repair. H11both is the selected best candidate; no mismatching source was written under Code. Keep all rejected trials and raw probe logs in build/worker_470dc1.
