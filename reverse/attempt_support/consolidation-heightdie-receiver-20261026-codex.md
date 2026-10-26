# HeightDieUpdate receiver prerequisite, 2026-10-26, codex

Allocated destination: `Code/GameEngine/Source/GameLogic/Object/Update/HeightDieUpdate.cpp`, family A shard 0/2. Runner allocation and `--check-tu` authorize this scope; the refreshed Update-directory name planner supplies original-path hints, not merge approval. Current `tu_skeleton.py --plan` approves seven parent rows across five donors and two mixed files. No merge or split was applied.

## Demonstrated unblock

The ordinary `--merge TU --dry-run` initially accepted only HeightDieUpdateUpdate.cpp (four rows, 633 retail bytes). Transfer, pool key, module-data constructor and constructor each failed declaration reconciliation. The final ordinary trial accepts HeightDieUpdateXfer.cpp, HeightDieUpdatePoolKey.cpp and HeightDieUpdateUpdate.cpp together: seven rows, 799 existing retail bytes. This adds two compatible donors / three rows (166 bytes) to the trial, without claiming recovered bytes or a downstream Luna landing.

HeightDieUpdateView.h shares the update donor's measured receiver fields and multiple-inheritance interface positions with transfer and pool key. Transfer's existing primary slot 3 and pool key's recorded slot 4 are declared without constructing a vtable. The primary base placeholder slots are incomplete structural declarations, not recovered names. Existing update interface position +0x10 and fields +0x20 through +0x30 are retained. The three-float transfer operand uses canonical Coord3DBase and an explicit reference cast from canonical Coord3D; an initial asBase call emitted an unnecessary helper and was removed before acceptance. No donor reference is claimed as a BFME 2 source path.

## Verification

- Before and after `./build.sh` on the three donors: 7/7 byte exact; one string exact. Both update funclets verified against parent EH data after compiler label renumbering.
- `find_declared_unmatched.py` on all three: no unrowed bodies. `class_gate.py` on the header and three consumers passes.
- Saved before objects versus fresh objects via upstream allowed_symbols.Obj/_object_defs and census COMDAT selection readers: every non-debug section, payload, relocation, selection policy, code/data definition, undefined symbol and alternatename is identical in each donor. External code definition counts are 1 transfer, 1 pool key and 11 update.
- `allowed_symbols.py --source` finds 19 references (14 owner, 3 alias, 2 EH), zero wrong bindings. Repeating its scan against the saved before objects gives identical 19 facts. `data_check.object_facts` likewise gives identical before/after reference and owner sets.
- Final trial composition object `build/tu_skeleton/d626e5e9189e238e.obj`: all 13 code definitions equal the standalone union, no conflicts, additions or losses; both external data definitions and their bytes/relocations are equal; COMDAT selection policies and alternatenames equal; undefined symbols equal after internal resolution. Per-source data references and aggregate owners equal with no guard normalization needed. This verifies composition providers/consumers, beyond matching body bytes.
- `link_check.py --prepare-current` explicitly prepared all three owned sources with strict reusable receipts. `link_check.py --new-variants --paths-from build/codex-heightdie-sources.txt` passes. These are predictive checks, not census LINKED progress.
- `eh_verify.py --sources-from build/codex-heightdie-sources.txt`: two EH rows EXACT, no missing object. Scoped name planner regenerated after editing and freshness check passes.

Scratch reports and comparison scripts use the `build/codex-heightdie` prefix. Baseline objects are preserved in `build/codex-heightdie-before-objects`. All comparisons use supported upstream object/identity readers; compilation was only through build.sh and tu_skeleton's trial verifier.

## Remaining prerequisites and debt

The ordinary trial still rejects HeightDieUpdateModuleDataCtor.cpp (its constructor is absent from the shared field-only declaration) and HeightDieUpdateCtor.cpp (its explicit-vtable model needs constructor/hierarchy reconciliation). They were not edited or repeatedly rebuilt as separate attempts. Two mixed owners remain behind the supported split lane: Common/Rva0024A797Derived.cpp and Update/ModuleDataBuildFieldParse.cpp. Scope-wide file/RVA claims are still required for any follow-up.

The three existing data identity findings remain unchanged: pool-key local static and guard at 0xA03980/0xA03984 and update's storage prototype at 0x9FEFA4. The baseline's historical guard spelling differs from the current emitted symbol; this pre-existing mismatch is retained, not retired by this declaration repair. No code identity, data, header/ms-header register, hatch baseline, ledger or TU map was changed. File reduction 0; identity debt retired 0; authored/recovered C++ bytes 0.

## Complete outgoing compatibility audit

Audited HEAD a338c81b13 plus these staged changes; there are no unpublished earlier commits and no moved, renamed or deleted source paths. Origin advanced in unrelated files while this work ran. Combined searches of tools, hooks, workflows, source/header includes and reverse registers found no active path consumer requiring repair. The new scoped header has exactly these three direct consumers, all built and compared together; build flags, registry paths and historical EA paths remain unchanged. No pending source move or merge is included. Normal hooks and the pre-push selected-provider/lost-byte report remain required; no maintainer-only link cycle, nightly or smoke run was started.

Retain the destination, three donor and new-header file claims until this prerequisite commit is confirmed published; then release them and settle landed RVAs. Compatible donors are left for Luna. The upstream merge will carry surviving data keys; a file merge alone is not identity retirement.
