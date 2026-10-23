ShellMenuScheme node allocator, 2026-10-20
========================================

Baseline d89f9f8652; BFME1 verified inputs remain92f6bbe8e1dcdb46b5d27da0674313efc822b790.
The unit emitted an unused __node_alloc<true,0>::allocate copy differing from
the first kept copy. Declare the specialization out of line, as other units
already do, so this unit uses the shared implementation. No allocator
algorithm, type identity or target layout changes.

Paired same-index legacy prediction:0/1 ->1/1 units,0 ->289 nonpadding bytes.
Both phases have strict-current objects; all6 rows pass the byte gate and
strict receipts. Retained nondebug code, data, EH and symbolic relocations
are identical with no callee rebinding; proof.json records removed COMDATs.
EH2 graphs EXACT; class, declared-definition and converged data checks pass.
Closed-strict closure/gain is unmeasured. Remaining unreferenced list allocator
copies are diagnostics under retail-truth-2 and were left untouched.

Cause sweep: the published sole-allocate peers BridgeBehaviorParseFX,
BridgeBehaviorParseOCL, AnimateWindowManager and FloodUpdate are all held by
another worker (yasinschroeder-codex). Other current unclaimed units with this
copy have independent blockers; no zero-gain changes were kept.
