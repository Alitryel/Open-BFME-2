# SquishCollide receiver prerequisite, 2026-10-26, codex

Allocated family A, shard 0/2 destination:
`Code/GameEngine/Source/GameLogic/Object/Collide/SquishCollide.cpp`.
The runner queue lists it unheld. Scoped Collide planner and current `--plan`
were reviewed; original-path alternatives remain hints, and current routing is
rebuilt in memory by tu_skeleton. No merge or split is applied.

The ordinary baseline dry run accepts only SquishCollideOnCollide.cpp. Adding
SquishCollidePoolKey.cpp fails C2143/C2501 on TheNameKeyGenerator. The repair
shares the collision body's existing Module/ObjectModule/BehaviorModule and
CollideModule receiver with the pool body through SquishCollideView.h, including
the already named pool-key method and NameKeyGenerator declarations. Both
matched bodies, their compiler flags, names and ledger ownership are retained.
No complete class recovery or constructor ABI is inferred.

The ordinary final `tu_skeleton.py --merge TU --dry-run` accepts both sources:
five existing rows / 1244 bytes, including verified EH rows. This adds one
compatible donor / two rows / 79 existing bytes. It demonstrates an unblock for
Luna; no downstream merge landing is claimed. The constructor remains rejected
(C2511, missing constructor declaration with its opaque base/vtable model).
Rva004BB68EDerived.cpp remains mixed. Its foreign rows were not edited.

## Acceptance and provider evidence

- `./build.sh` on both sources passes 5/5 matched rows, two literals, five float
  literals and imports. `eh_verify.py` reports two EXACT EH graphs. The generated
  unwind label is placed by verified parent EH data, without ledger changes.
- `find_declared_unmatched.py` and scoped `class_gate.py` pass for both consumers
  and the header. `check_csv.py` passes. Converged data enforcement passes both
  sources, ten addresses, no second names or unjudged rows.
- Saved verified baseline objects versus current objects through upstream
  allowed_symbols and COFF readers preserve all eleven external code definitions,
  undefined symbols, aliases and external data. OnCollide's sections reorder;
  owner-normalized non-debug section multisets (22 collision, eight pool) are
  identical including flags, bytes, relocations and COMDAT selections.
- Paired upstream allowed_symbols scans retain exactly forty reference facts,
  with zero additions/removals. Paired data_check.object_facts are identical.
- Final ordinary composition object `build/tu_skeleton/78b2e754d995a59a.obj`
  preserves all eleven external code definitions, all six external data
  definitions and their payloads/relocations, COMDAT policies, aliases and
  unresolved symbols after internal resolution. Per-source data references and
  aggregate owners agree after one verified composition-local guard renumbering:
  onCollide's STATIC guard S1 becomes S2 at the same retail address 0x00A04018,
  with identical four-byte uninitialized storage, flags and relocation count.
  Its unique parent/address and storage were checked explicitly, not ignored.
- `link_check.py --prepare-current` verifies strict reusable receipts for the
  two explicit providers; `--new-variants --paths-from` reports no new variants.
  No maintainer-only link cycle, smoke or nightly measurement was run.

Scratch evidence is `build/codex-squish-*`: before/after source and object
snapshots, byte builds, ordinary trials, normalized sections, code/data/reference
comparisons, composition proof, EH, receipts and variants. Existing pool guard
wrong-name debt remains recorded at its original source. No identity/data debt
is retired; a later merge must transfer its protected keys through the tool.
The header queues and owner/source registers remain unchanged. Staged shadow
checks still report the existing divergent Coord3D copy-constructor definition
and three existing wrong-name data facts (collision guard, pool guard/key).
The paired before/after object and reference comparisons above prove these
findings are retained, not introduced by the receiver change. No baseline is
expanded and no key is retired. Staged TU ownership passes.

## Publication compatibility audit

The inherited six-repair batch is upstream at dfc0c39c28, and its thirty scope
claims were released after confirming that publication. This new prerequisite
has no source path moves, renames or deleted donors. The sole source addition
is SquishCollideView.h, with exactly the two rebuilt consumers. Combined searches
of active tools, hooks, workflows, Code includes, build inputs and reverse
registries find no path consumer requiring repointing. Historical original EA
and donor paths remain intact. The fetched origin/master..HEAD view contains
inverse unrelated upstream changes; this batch's own outgoing range begins at
dfc0c39c28 and consists of this staged repair/handoff only. No protected register,
TU map, baseline, fold proof, source registry or source list is edited.

File reduction 0; recovered/authored C++ bytes 0; debt retired 0. Keep the five
file claims (destination, two sources, header, handoff) until publication is
confirmed. Luna may compose the now-compatible donors after normal claims,
protected-register transfers and its complete provider/consumer checks.
