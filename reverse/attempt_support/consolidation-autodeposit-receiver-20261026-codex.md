# AutoDepositUpdate receiver prerequisite, 2026-10-26, codex

Allocated destination: Code/GameEngine/Source/GameLogic/Object/Update/AutoDepositUpdate.cpp, family A shard 0/2. The runner allocation grants this destination; the refreshed Update-directory planner supplies placement hints, not merge approval. Current --plan approves five parent rows across three clean donors plus mixed Common/Rva0024A797Derived.cpp. No merge or split was applied.

## Demonstrated unblock

Before the ordinary --merge TU --dry-run accepts only AutoDepositUpdateUpdate.cpp (six rows, 1015 existing bytes). The pool key fails because its method is absent from the update donor's private class. After the shared receiver repair, the same ordinary trial accepts update plus pool key: eight rows, 1094 existing retail bytes. One additional donor / two rows / 79 existing bytes become compatible. No downstream Luna landing, recovered bytes or linking census gain is claimed.

AutoDepositUpdateView.h shares the update donor's measured receiver: primary data +4, object +8, other interface +C, update interface +10, deposit state +20, flags +24/+25. Its update interface and existing inline accessors are preserved. The primary prefix's slots 0..3 remain explicitly incomplete structural declarations; the cached name key is the existing slot 4, proven in re_attempts.log at 0x0049A1CA. No constructor or primary vtable is emitted. The partial receiver makes no full-hierarchy claim. No function body, compile flag, canonical header, name or ledger changed.

## Verification

- Before/after ./build.sh on both donors: 8/8 byte exact, three string literals and five compiler float literals verified. Both unwind rows remain verified against parent EH data despite compiler-label renumbering. eh_verify.py --sources-from build/codex-autodeposit-sources.txt: three EH graphs EXACT, no missing object.
- find_declared_unmatched.py passes both donors; class_gate.py passes the scoped header and both consumers.
- Saved before objects versus current objects through upstream allowed_symbols.Obj/_object_defs and census COMDAT readers: every non-debug section (26 update, eight pool), payload, relocation, flag, COMDAT selection policy, external code/data definition, undefined symbol and alternatename identical. External code definitions remain fifteen update and one pool.
- Paired allowed_symbols.scan with scratch row views using build.located_funclet's verified parent-EH placements: 38 before and after reference facts, no additions/removals. No ledger/object-symbol hatch was edited. data_check.object_facts reference and owner sets identical. Converged data checks pass both sources: no second names or unjudged rows.
- Final ordinary composition object build/tu_skeleton/5aee882333f8fd36.obj: all sixteen external code definitions equal the standalone union, no conflicts/losses/additions/changed bodies. Six external data definitions and their payloads/relocations are identical. COMDAT policies, aliases and unresolved symbols after internal resolution are equal. Per-source data references and aggregate owners equal without guard normalization. This checks provider/consumer composition beyond matching ledger rows.
- link_check.py --prepare-current --paths-from build/codex-autodeposit-sources.txt: both explicit providers byte-verified with strict reusable receipts. --new-variants passes. These are predictive checks, not a census update.
- name_lane.py consolidate --under Code/GameEngine/Source/GameLogic/Object/Update/ --out build/consolidation/codex-autodeposit refreshed after editing; --check passes. Original-path alternatives point here as hints; current routing is rebuilt in memory by the TU tool.

Scratch evidence uses build/codex-autodeposit (before sources/objects, ordinary before/after trials, object/reference/data/composition scripts and JSON). Compilation used only build.sh and the supported trial verifier.

## Remaining prerequisites and debt

AutoDepositUpdateCtor.cpp still fails constructor declaration/hierarchy reconciliation and was not edited; its constructor emits primary vtables. The mixed deleting-destructor owner stays behind the supported split lane. The existing pool guard wrong-name key at A03B14 remains in data_check_baseline.txt; its historical pre-rename spelling is not silently retired. A future merge must transfer its key and two data-ledger records as the tool prints, then retire only findings the register's own fresh verdict proves fixed. No baseline, identity/data/header debt, TU map, hatch or ledger was changed. File reduction 0; debt retired 0; authored/recovered C++ bytes 0.

## Complete outgoing compatibility audit

Fetched origin before this commit and audited git diff --name-status --find-renames origin/master..HEAD plus git log --name-status origin/master..HEAD, covering pending 7329f8736f, 45eb12416e, 0e5ad8a973, 87ed3c05a4, 947bdbc6d7 and this staged repair. No source path was moved, renamed or removed. Combined active tools/hooks/workflows/source includes/build inputs/register searches require no path consumer repair. Four new scoped headers have exactly ten direct consumers (HeightDie three, StealthDetector three, ResourceGathering two, AutoDeposit two), all verified together in their respective repairs. Historical EA paths and protected-register ownership remain intact. Existing code/data findings are separate from compatibility progress.

Review normal pre-push selected-provider/lost-byte/freshness output when publication runs. No maintainer-only link cycle/nightly/smoke command ran. Keep destination, two donor, header and handoff claims until confirmed publication, then release and settle landed RVAs. Leave the compatible merge to Luna.
