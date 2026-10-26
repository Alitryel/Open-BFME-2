# ResourceGatheringManager STL receiver prerequisite, 2026-10-26, codex

Allocated destination: `Code/GameEngine/Source/Common/RTS/ResourceGatheringManager.cpp`, family A shard 0/2. The runner queue/check-tu authorizes this destination; the current RTS name planner supplies original-path evidence, not merge approval. Current upstream routing approves twelve parent rows; ModuleNameGetters.cpp and ResourceGatheringManager_findBestSupplyWarehouse.cpp are mixed and untouched. No merge or split was applied.

## Demonstrated unblock

The initial ordinary `tu_skeleton.py --merge TU --dry-run` accepts no multi-file merge: the transfer donor's private STL allocator/list declarations conflict with the seed's real STLport types. The repaired ordinary trial accepts the seed plus ResourceGatheringManagerXfer.cpp: five rows, 236 existing retail bytes (182 seed, 54 transfer). This makes one additional donor / one row compatible; no recovered bytes, file reduction or downstream Luna landing is claimed.

ResourceGatheringManagerView.h shares the measured prefix: primary vptr +0, warehouse list +4, center list +8. The real `_STL::list<int>` replaces transfer's private allocator/list replica. Its existing primary slot 3 is declared without emitting a constructor/vtable. Other lifecycle declarations and the full hierarchy remain unrecovered. The unused private Coord3DBase definition was removed; its forward declaration uses the canonical struct tag. Transfer now uses the seed's real STLport/shim compile environment. No function body changed.

The first composition matched every row but changed three emitted STL helpers (list erase and the two allocator deallocation helpers) from `_free` to `__imp__free`: tu_skeleton's donor-majority flags omitted the seed's existing /D_CRTIMP=. This was rejected as sufficient evidence. The seed now spells that same empty CRT import macro before its STL includes when it is otherwise undefined, retaining the established provider bindings under normal donor-majority composition. No tool/gate or protected override was changed.

## Verification and provider/consumer evidence

- Before/after `./build.sh TU ResourceGatheringManagerXfer.cpp`: 5/5 byte exact; no literals/imports. `find_declared_unmatched.py` finds no unrowed bodies. `class_gate.py` passes for both consumers and the scoped header.
- Saved standalone objects versus fresh objects, using upstream allowed_symbols.Obj/_object_defs and COMDAT readers: all 19 seed and one transfer external code definitions, relocations, undefined symbols, aliases and external data definitions remain identical. Every seed non-debug section is identical. Transfer's only section change is .drectve adding STLport's normal default libraries already requested by the seed; code remains identical. The before/after union and final composition request exactly stlport_vc7_static.lib, msvcprt, MSVCRT and OLDNAMES.
- `allowed_symbols.py --source` on each source: four seed and three transfer references, all owners, zero wrong bindings. Saved-object comparisons give the same seven references before and after. `data_check.object_facts` reference/owner sets are identical. `data_check.py --converged --source` passes for each source (no second names or unjudged rows).
- Final ordinary composition object `build/tu_skeleton/44c3bff567b1892e.obj`: all 20 external code definitions equal the standalone union; zero definition conflicts, additions, losses or changed bodies. COMDAT selection policies, aliases and unresolved symbols after internal resolution are identical. No external data definitions; per-source data facts and owner union identical, without guard normalization. This includes the three STL providers that the initial otherwise matching composition changed.
- `link_check.py --prepare-current` explicitly prepared both sources: strict reusable receipts, 5/5 exact. `--new-variants --paths-from build/codex-resource-sources.txt` passes. These are predictive checks, not census LINKED progress.
- `name_lane.py consolidate --under Code/GameEngine/Source/Common/RTS/ --out build/consolidation/codex-resource` was refreshed after the final edit; its freshness check passes. Trial/planner were run sequentially to avoid inventorying temporary trial sources.

Scratch evidence uses build/codex-resource, including before objects, source backups, ordinary before/after trials, code/data/reference comparison scripts and composition proof JSON. Compilation was only through build.sh and the upstream TU trial verifier.

## Remaining prerequisites and debt

ResourceGatheringManagerDestructor.cpp still needs constructor/lifecycle declaration reconciliation; ResourceGatheringManagerDeleter.cpp still needs its EmitVtableTag constructor model reconciled. Neither donor was edited. The two mixed files remain behind the supported split lane. The separate findBestSupplyWarehouse mixed owner's existing GameLogic header-queue conflict remains untouched. There are no existing scoped seed/transfer keys in code/data identity, hatch or flag-override registers to retire. No ledger, baseline, TU map or header queue was changed. Identity debt retired 0; file reduction 0; authored/recovered C++ bytes 0.

This commit also corrects the StealthDetector handoff's total from 1808 to 1841 existing bytes; its accepted fifteen rows and three newly compatible rows (147 bytes) are unchanged.

## Complete outgoing compatibility audit

Before this publish attempt, fetched origin and inspected git diff --name-status --find-renames origin/master..HEAD plus git log --name-status origin/master..HEAD, covering pending commits 7329f8736f, 45eb12416e, 0e5ad8a973 and 87ed3c05a4 together with this staged repair. No source path was moved, renamed or removed in the outgoing batch. Combined searches of active tools, hooks, workflows, source/header includes, build inputs and reverse registers found no path consumer requiring repair. The three new scoped headers have exactly their eight direct consumers (HeightDie three, StealthDetector three, ResourceGathering two), all verified in their respective prerequisite batches. Historical EA paths and protected-register ownership remain unchanged. Existing data/code findings are retained separately from compatibility progress.

Normal pre-push selected-provider, lost-byte and freshness audit remains required and its shadow/inconclusive findings need review. No maintainer-only link cycle, nightly or smoke command was run. Retain this destination, transfer, header and handoff file claims until publication is confirmed; release afterward and settle landed RVAs. Compatible donors are left for Luna.
