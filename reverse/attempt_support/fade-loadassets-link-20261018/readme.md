# FadeInTextRender duplicate asset-loader repair

At BFME 2 revision a70640ead2787d0c80611649215351f1256f2dba, the rendering
unit rva00596908Rva00596908Farm.cpp also emitted an undeclared second definition
of FadeInTextRender::LoadAssets. Its copy retained an unresolved g_009BA4E8,
while the ledger's real LoadAssets provider, Rva0059675AInitialize.cpp, already
used the canonical BfmeClientFramesPerSecond binding. The duplicate blocked both
units. Remove the second definition and its unused global declaration, keeping
the virtual declaration, class layout and rendering body unchanged.

Target evidence: ledger ownership places LoadAssets at 0x005967B3 (341 bytes)
and the renderer at 0x00596908 (481 bytes); both retail EH graphs verify EXACT.
The existing vftable evidence remains in the source. This repair asserts no new
identity, layout, source recovery, global alias or authored C++ coverage.

## Paired local evidence

The runner's index measures commit c2c5ac8c27, dated 2026-10-18 11:36;
its SHA-256 is recorded in object-proof.json. The index and link_status.csv were
not changed. Snapshots used the same original object basenames and index, with
both providers refreshed in memory together for each phase.

Before: 0/2 units link. The renderer has an unresolved global, duplicate loader
and losing loader copy; the provider also has a duplicate loader.
After: 2/2 units link with no local findings, projecting 0 -> 822 existing retail
bytes (481 renderer + 341 provider) under the bounded legacy index rules.
This is a local legacy prediction with self-strict byte receipts, not a
closed-strict measurement or a full link-cycle result. No broader gain claimed.

Object comparison: the provider is byte-for-byte unchanged. All 11 retained
renderer COMDAT copies retain their byte/relocation digest; no new copies,
strong definitions, undefined names or weak bindings appear. Removed copies are
the loader and its now-unused string/float/string-wrapper emissions. Both
objects have strict-current dependency receipts before and after the change.

## Checks

On both source paths, except where noted:

- `python3 tools/link_check.py --prepare-current SOURCE...`: before and after,
  five matched rows pass full bytes, one string and eleven floats verify.
- `./build.sh RENDERER`: renderer 1/1 exact after removal.
- `python3 tools/link_check.py SOURCE...`: paired before/after outputs included.
- `python3 tools/eh_verify.py SOURCE... --json PATH`: two EH graphs EXACT.
- `python3 tools/data_check.py --converged SOURCE...`: nine addresses, zero
  second names or unjudged addresses; normal shadow data check zero findings.
- `python3 tools/class_gate.py RENDERER`: passes.
- `python3 tools/find_declared_unmatched.py RENDERER`: all definitions matched.
- `python3 tools/place_bodies.py SOURCE...`: zero extra bodies or pins.
- `python3 tools/check_csv.py` and `git diff --check`: pass.

## Donor review and outstanding boundaries

Reused the prior BFME 1 linking survey in
reverse/attempt_support/link-inline-emitters-20261014/readme.md and reviewed
upstream d348fca17814122303884ebe194cbc877a2c0bb0's
 game/GameEngine/Source/Common/Rva007E8600Clear.cpp. Its duplicate-emitter
repair is a general lead only; the BFME 2 ownership, object and byte evidence
above independently establish this repair. No donor addresses or layouts copied.

BFME 1's checkout remains at verified pointer
64d369b90170b7e9ec917d646f020b11f13eb0d5. The freshness update is due and the
submodule is claimed by another worker; preserve its verified inputs and the
existing comparative-gate blocker. No freshness success stamp was written.
Full link cycles and closed-strict measurements remain for authorized runners.
