# Consolidation verifier diagnostic cache prerequisite (2026-10-26, codex)

The allocated BridgeTowerBehavior destination exposed a shared tooling
prerequisite already recorded for FireSpreadUpdate and DebugIOCon. This is a
separate verifier repair after the BridgeTower source trial was restored and
its false reject recorded. No source trial or ledger change accompanies it.

`Verifier.matched` cached only the compiled object or failed result. On a
cache hit, its `errors` and `all_errors` still described the most recently
compiled candidate. The merge retry uses those redefinition errors to choose
which private declarations to drop. An A/B/cached-A sequence therefore followed
B's declaration edits for A; an otherwise accepted candidate could fail the
final recheck. The FireSpread reproduction is retained in
`build/codex-firespread-cache-repro.txt`; the fresh BridgeTower ordinary trial
reports this failure in `build/codex-bridgetower-after-trial.txt`.

Each cache entry now stores its own object result and diagnostics. Every lookup
restores that entry's errors; successful compiles and hits clear stale errors.
Compile failures remain failures and the same row-by-row retail byte comparison
still decides acceptance. No flags, routing, retry limits or gate exceptions
change.

Three regression cases drive the real Verifier.matched path with a deterministic
compiler fixture: failed A/B/cached-A diagnostics, success after failure on fresh
compile and cache hit, and byte mismatch after an unrelated compile failure.
All three fail against the original code. With the fix,
`python3 -m pytest -q tools/tests/test_tu_skeleton.py tools/tests/test_gate_exploits.py`
passes 92 tests; the existing open audit-escape fixture is intentionally skipped
by that suite. Existing closed exploit cases continue to reject their variants.
`python3 -m pytest -q tools/tests/test_tu_skeleton_carry.py tools/tests/test_tu_skeleton_split.py`
also passes 32 tests and two subtests, covering the other verifier consumers.
Before/after output is preserved as `build/codex-verifier-cache-{before,tests}.txt`.
`find_declared_unmatched.py` and `git diff --check` pass.

This repair changes no game source object, selected provider, COMDAT or data
binding; all recovered GameMemory object/composition evidence remains valid.
The complete outgoing range through the blocked BridgeTower receipt contains
no existing source path moves, plus the already verified GameMemoryGuardView.h
and its two consumers. Combined tools/hooks/workflows/includes/build/doxygen/
registry searches were repeated for that pending header and the interface path;
no active consumer needs repointing. Historical EA paths remain intact. No
baseline, whitelist, gate exception or protected register is staged.

BridgeTower's source claims were released after restoration. Reclaim and retry
its banked measured-access patch with ordinary `--merge TU --dry-run` after this
separate verifier commit. FireSpread's minimal shared declaration and DebugIOCon's
FreeConsole include trial are independent follow-ups under their current owners
and allocations. No downstream merge is claimed until its own ordinary trial
and provider/consumer comparison succeed. Recovered C++ bytes, source-file
reduction and identity debt retired are zero.

Keep the tool/test/handoff file claims, the blocked BridgeTower handoff claim,
and inherited GameMemory/register claims until the batch is confirmed published.
