# New hypotheses before experiment 1

The current farm bank is semantically wrong: native argument 1 in EBP is x and argument 2 in EBX is y (73BFE4..73BFED; min comparison 73C092..73C0AF), whereas the bank names argument 1 ys and minimizes it. Native right-edge initial x is loaded from the updated first index at 73C164 after horizontal traversal 73C122..73C141, whereas the bank retains the original firstx. Both target updater calls use the same incoming object at entry ESP+16 (73C1A8 and 73C325), whereas the bank copies it for the first call. Correcting these three points, and removing the artificial volatile local, should produce a semantically faithful polygon raster. Refutation: a direct comparison with native coordinate, horizontal-edge or updater dataflow disagrees, or a deterministic trace differs from the target-derived algorithm.

Native entry follows five INT3 bytes at 73BFDB..73BFDF. Shared success epilogue 73C340..73C349 is reached by 73C06E, 73C26B and 73C2EF, so the complete boundary is 874 bytes, not the queued 865. Calls are thiscall 73BAA0 with three integer arguments and a 12-byte updater passed to the cdecl raster by value. Current provider/caller use Rva0073BAA0Base; the bank predates that reconciliation. No original source identity is asserted. Repair_queue dest reports a contradictory stlport_deque_int.cpp neighbour heuristic, not authoritative source evidence; shroud callers and recovered sibling rasters provide the subsystem relationship.

Measurements: copy the unmodified bank to a unique before.cpp; measure it and each trial with align_diff.py at size hint 865 (the tool discovers the complete 874-byte boundary). Each trial uses a unique path with no prior object and BFME_OBJSTORE=off. Keep raw output. A semantic repair may replace the wrong bank at comparable alignment under the assignment exception.

Prior evidence: all seven exact-symbol verdicts in reverse/re_attempts.log were read. Their only explicit evidence path is reverse/attempts/0x0073bfe0.cpp, read in full. Also read current updater/circle/parent sources and all four shroud-lightenv-math-link-20261013 support files mentioning this raster. Current BF1 revision a18d9ed50607e9175de4d6568798d7d73119de09 contains no taintmanager_impl.cpp. No donor source was ported.


## Experiment 2: repeated wrap expressions

WB 17E3E10 repeats prev(first,n) twice in left-edge initialization and again to assign the current index; it similarly repeats next(first,n) around the horizontal skip, right-edge initialization and each later edge transition. Native 73C114..73C11E and 73C143..73C1AD retain repeated wrap computations, but the bank caches each result before initialization. Reconstruct those expressions directly rather than caching. Prediction: structural regions fall because repeated wrap computations reappear, without extra memory/register defects. Refutation: the fresh align_diff output fails that comparison or retained wrap logic differs from retail.


## Experiment 3: direct minimum loads and shared loop variable

Retail has one unpeeled minimum-search loop at 73C092, comparing ys[i] with ys[first] directly. The bank's cached yi yields a different strength-reduced loop. WB local_10 is shared by the duplicate-removal and minimum loops. Restore that source lifetime and write the target's direct repeated array accesses, avoiding yi and the unused local pointer copies. Prediction: the minimum loop and allocation become closer. Refutation: fresh measurements show no reduction, or improvement in one class trades defects into another.


## Experiment 4: scalar edge state and top-tested updater loop

Repeated expression and shared-index trials did not improve the complete tuple. Retail stores independent edge fields at stack +1C/+20/+24 and +2C/+30/+34, retains the left index at +28 and the right index in EDI. WB has six independent scalar fields and one top-tested updater loop, while the bank uses RasterEdge constructor/set calls and two explicit updater sites. Reconstruct the same target-derived scalar dataflow and the top-tested loop; this permits cl to rotate the loop itself. Prediction: native repeated-wrap scheduling and frame lifetime become closer. Refutation: measured structural/memory/register tuple fails to improve, or scalar arithmetic changes an edge trace.


## Experiment 5: wrap helpers matching WB arithmetic

WB initializes prev as (i ? i : n) then subtracts one, rather than subtracting independently in both arms. It represents next as (i+1==n ? 0 : i+1), without mutating an argument. Native first prev uses TEST/LEA/JNE/LEA, and repeated prev assignment should avoid a conditional spill. Replace helper expressions with those source forms in the shared-index class-state trial. Prediction: wrap-related structural regions shrink. Refutation: a fresh full-tuple comparison shows no Pareto improvement.


## Experiment 6: isolate the minimum-search repair

The shared-index trial eliminated the initial peeled minimum-search regions, while its repeated edge expressions added regions elsewhere. Apply only the direct minimum array accesses and shared loop variable to the semantically corrected cached-edge candidate. Prediction: eliminate the initial minimum-search structural regions without importing repeated-wrap regressions. Refutation: the whole structural/memory/register tuple fails to improve against before.


## Isolated experiment directmin

Isolate direct minimum reads without sharing the duplicate-loop index. The shared index and direct reads were changed together in experiment 6; its first minimum loop improved but allocation regressed. Prediction: the direct reads alone remove peeled regions with less allocation disturbance. Refutation: the new structural/memory/register tuple fails to improve without a cross-class trade.


## Isolated experiment firstx

Remove the early firstx cache, passing xs[first] directly to the left initializer. Native 73C0E8 loads xs[first] after computing the height, whereas the bank caches it before prev. Prediction: the left initializer scheduling approaches native without changing edge arithmetic. Refutation: the new structural/memory/register tuple fails to improve without a cross-class trade.


## Isolated experiment hskip

Reconstruct only the native horizontal skip and right-edge initialization with repeated next expressions. The earlier all-site repeated trial mixed this with left and later edge transitions; isolate this contiguous native 73C122..73C1AD region. Prediction: fewer structural defects in that region without later-loop regressions. Refutation: the new structural/memory/register tuple fails to improve without a cross-class trade.


## Native differential trace probe

Link the already compiled bank and semantic candidate separately with one callback recorder. Execute the complete native 874-byte body in a local 32-bit process, patching only its two external calls to that recorder. Compare mutated coordinate arrays, char result, all scanline arguments, updater grid/mask contents and consistent updater identity across calls. Exercise duplicate vertices, horizontal edges, asymmetric coordinates, reverse winding, cyclic rotations and early callback failures. Prediction: the bank diverges and the corrected candidate agrees. Refutation: any corrected trace differs; no whole-program or general polygon correctness claim follows from passing these vectors.


## Experiment 10: repair cached horizontal traversal

The first native trace probe timed out. Source reinspection exposes an additional definite bank error: first=right=next(first,n) makes first and right equal after the first horizontal step, so ys[first]==ys[right] remains true forever. Native recomputes next(first,n) on each comparison. In the cached form, assign first=right and then recompute right=next(first,n). Prediction: the traversal terminates on the first nonhorizontal edge and matches the repeated native form; the original rectangle counterexample diverges. Refutation: any fresh trace differs from the native body on the defined convex input set. Keep the already-correct repeated hskip version as an independent candidate.


## Native differential trace probe

Link the already compiled bank and semantic candidate separately with one callback recorder. Execute the complete native 874-byte body in a local 32-bit process, patching only its two external calls to that recorder. Compare mutated coordinate arrays, char result, all scanline arguments, updater grid/mask contents and consistent updater identity across calls. Exercise duplicate vertices, horizontal edges, asymmetric coordinates, reverse winding, cyclic rotations and early callback failures. Prediction: the bank diverges and the corrected candidate agrees. Refutation: any corrected trace differs; no whole-program or general polygon correctness claim follows from passing these vectors.

Native trace domain correction: reverse winding with a horizontal predecessor at the minimum leaves the native left edge uninitialized (73C0F0 JLE skips both value and step writes). Such vectors cannot establish deterministic semantic differences. Exclude them explicitly; add diamonds with a unique minimum to retain defined reverse-winding coverage. Preserve the original failed raw logs as trace-*-unfiltered.log before rerunning.


## Native differential trace probe

Link the already compiled bank and semantic candidate separately with one callback recorder. Execute the complete native 874-byte body in a local 32-bit process, patching only its two external calls to that recorder. Compare mutated coordinate arrays, char result, all scanline arguments, updater grid/mask contents and consistent updater identity across calls. Exercise duplicate vertices, horizontal edges, asymmetric coordinates, reverse winding, cyclic rotations and early callback failures. Prediction: the bank diverges and the corrected candidate agrees. Refutation: any corrected trace differs; no whole-program or general polygon correctness claim follows from passing these vectors.


## Experiment hskip-direct

Combine the verified horizontal traversal with direct minimum loads. The isolated directmin trial and the repeated shared trial show that minimum caching changes peeling, but they used different edge forms. Prediction: eliminate minimum-search regions while retaining the valid hskip region. Refutation: fresh structural/memory/register counts fail to improve without a cross-class trade, or native traces differ.


## Experiment hskip-shared

Use the same duplicate/minimum loop index as WB together with the verified hskip traversal, isolating its allocation effect from repeated later-edge transitions. Refutation: fresh structural/memory/register counts fail to improve without a cross-class trade, or native traces differ.


## Experiment positive-step

WB tests remaining<1 and then loops while remaining==0. The current helper returns remaining!=0 and callers use a do loop. Reconstruct the positive-step helper and zero-tested inner while loops, which should allow the native DEC/TEST/JNE schedule. Native defined edge lengths remain positive until they reach zero, and negative newly constructed edges return before the next step. Refutation: fresh structural/memory/register counts fail to improve without a cross-class trade, or native traces differ.


## Experiment shared-positive

The positive-step form brought TEST back into the stepped loop and reduced register differences from 79 to 58 in the cached-minimum hskip trial. Apply it to the shared-index, direct-minimum form, which independently cut structural regions to 28. Prediction: reduce the corresponding structural and register residues. Refutation: fresh tuple trades defects between classes, or native traces fail.


## Experiment shared-transitions

The shared-index hskip form still caches each later transition index. Native 73C258 and 73C2DD recompute the next index after edge arithmetic; apply repeated expressions only to those later transitions, preserving the improved minimum and horizontal region. Prediction: reduce the corresponding structural and register residues. Refutation: fresh tuple trades defects between classes, or native traces fail.


## Final semantic candidate preparation

The shared-transitions trial has comparable alignment to the original wrong bank: 33/66/46 structural/memory/register versus 34/62/51. This is not a strict alignment improvement because memory differences increase. Under the assignment semantic-repair exception, retain it only if complete native traces agree. Remove the constant-true duplicated conditional and unreachable barrier machinery, retaining all existing bank comment lines; reconcile the updater class spelling with its existing matched provider Rva0073BAA0Base. Prediction: normalized body bytes and relocation offsets remain unchanged, only the actual external class name changes. Refutation: emitted code changes or the native trace probe fails. Do not publish a Code reconstruction.


## Native differential trace probe

Link the already compiled bank and semantic candidate separately with one callback recorder. Execute the complete native 874-byte body in a local 32-bit process, patching only its two external calls to that recorder. Compare mutated coordinate arrays, char result, all scanline arguments, updater grid/mask contents and consistent updater identity across calls. Exercise duplicate vertices, horizontal edges, asymmetric coordinates, reverse winding, cyclic rotations and early callback failures. Prediction: the bank diverges and the corrected candidate agrees. Refutation: any corrected trace differs; no whole-program or general polygon correctness claim follows from passing these vectors.


## Cleanup isolation canonical

The combined cleanup unexpectedly changed emitted code. Isolate the canonical updater name and unreachable barrier removal before choosing the bank. The constant-true duplicated conditional is semantically equivalent for ordinary integer-array reads and is inherited farm evidence; no volatile accesses remain. Prediction: name-only and unreachable-code changes leave instruction bytes and relocation offsets unchanged. Refutation: fresh raw object comparison differs.


## Cleanup isolation no-barrier

The combined cleanup unexpectedly changed emitted code. Isolate the canonical updater name and unreachable barrier removal before choosing the bank. The constant-true duplicated conditional is semantically equivalent for ordinary integer-array reads and is inherited farm evidence; no volatile accesses remain. Prediction: name-only and unreachable-code changes leave instruction bytes and relocation offsets unchanged. Refutation: fresh raw object comparison differs.


## Experiment: immutable pointer parameters

The canonical candidate reuses incoming pointer-argument stack slots for spills, while native retains those slots and has a 16-byte larger local frame. A top-level const qualification could prevent argument-slot reuse without changing the ABI or writable-array semantics. This is a compiler-shape inference, not a proven original declaration. Prediction: qualifying the two pointer parameters moves spills into native-like local slots. Refutation: emitted body is unchanged or the complete alignment tuple regresses.
The top-level const probe emits MSVC QAH rather than PAH, so its first align command did not select the emitted symbol. Measure a fresh identical file under its actual QAH symbol to complete the diagnostic; this does not justify changing the existing caller declaration or pin.


## Native differential trace probe

Link the already compiled bank and semantic candidate separately with one callback recorder. Execute the complete native 874-byte body in a local 32-bit process, patching only its two external calls to that recorder. Compare mutated coordinate arrays, char result, all scanline arguments, updater grid/mask contents and consistent updater identity across calls. Exercise duplicate vertices, horizontal edges, asymmetric coordinates, reverse winding, cyclic rotations and early callback failures. Prediction: the bank diverges and the corrected candidate agrees. Refutation: any corrected trace differs; no whole-program or general polygon correctness claim follows from passing these vectors.
