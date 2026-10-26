# BeaconClientUpdate receiver prerequisite, 2026-10-26, codex

Allocated TU: Code/GameEngine/Source/GameClient/Drawable/Update/BeaconClientUpdate.cpp, family A shard 0/2; runner --check-tu returns 0. The scoped planner records a WorldBuilder path pair and same-name ZH definitions as hints only, with no alternatives, plus internal-linkage and quoted-include review prerequisites. Current tu_skeleton routing approves nine parent rows. No merge or split was applied.

## Demonstrated compatibility

Before ordinary --merge TU --dry-run: no verified composition of two donors; the cached-name-key method is absent from the update body's private receiver. After: update and pool-key donors accepted, twelve existing rows / 937 retail bytes. The standalone update source owns ten rows / 858 bytes; the newly compatible pool-key donor adds two rows / 79 existing bytes. No new bytes, row moves, file reduction, identity/data retirement or downstream Luna landing is claimed.

BeaconClientUpdateView.h shares the existing accessed receiver prefix: data +4, drawable +8, particle ID +C, last pulse +10. It adds the existing cached-name-key method declaration alongside the update declaration. This is explicitly an incomplete virtual interface; these consumers emit no receiver constructor or vtable, and no complete inheritance or virtual-slot ordering is inferred. ParticleSystemID and NameKeyType retain their definitions. Both existing function bodies and compile flags are unchanged.

## Verification

- ./build.sh both donors before/after: 12/12 exact, three string and three float literals checked. Four funclet label changes verify through their parent's EH data. eh_verify --sources-from build/codex-beacon-sources.txt: four graphs EXACT, no missing object. find_declared_unmatched passes both; class_gate passes both plus the scoped header.
- Saved/current objects compared through allowed_symbols.Obj/_object_defs and census COMDAT readers: all nondebug sections (24 update, eight pool), payloads, relocations, flags, COMDAT policies, external code/data, undefined symbols and aliases are identical. External code counts remain ten plus one. allowed_symbols.scan: 52 facts before/after, no changes. data_check.object_facts reference/owner sets equal; converged check has two sources, ten addresses, zero second names or unjudged rows.
- Final ordinary composition build/tu_skeleton/a8b1b39e16588352.obj exactly preserves the standalone union: eleven external code definitions, six data definitions with payloads/relocations/selections, all COMDAT policies, aliases, data references/owners and unresolved symbols after internal resolution. No new/lost/changed definitions or guard normalization. This preserves the private Drawable-in-ESI helper ABI and EH providers in the composed unit as well as the individually rowed bytes.
- link_check --prepare-current accepts both explicit providers with strict receipts; --new-variants passes. Neither updates a census or proves whole-link closure. The planner refreshed after editing and --check passes.

Scratch evidence: build/codex-beacon-* (before sources/objects, builds, ordinary trials, object/section/reference/data/composition scripts and JSON, strict receipts). Compilation used build.sh and supported TU trials, never manual build.compile_source.

## Remaining work and debt

The opaque PointDefenseLaserUpdateCtor.cpp still lacks a compatible constructor declaration/hierarchy. BeaconClientUpdateXfer.cpp still lacks the shared xfer/base declaration. CleanupHazardUpdateCtor.cpp still disagrees with the accessed module-data member declarations. Their authored bodies and present-unmatched markers were untouched. Staged code identity reports twelve rows and zero new findings. Staged shadow data checking reports the same pre-existing pool guard/key wrong-name facts at 0x00A04338/0x00A04334; unchanged object facts above prove this repair adds neither finding, and the old baseline spelling is retained. Mixed constants and module-data parser rows stay behind their supported split lane. A future merge must transfer the pool guard's existing data-check key and two data-ledger records as printed; only the debt register's fresh retirement verdict may remove them. No protected ledger, baseline, hatch, TU map or canonical class was changed.

## Complete outgoing path compatibility audit

Audited pending commits 84d78f24f6 and 4e67734403 plus this staged change together, including origin/master..HEAD and the own log from dfc0c39c28. No source path moves/removals. New scoped headers are SquishCollideView.h and BeaconClientUpdateView.h, each with exactly two direct consumers verified together. Combined active tools, hooks, workflows, source includes, build input and registry searches find no required path repairs. Relative includes resolve to the shared headers; historical EA paths remain. Inverse differences for independent upstream commits are outside this batch. Header debt retirement from the prior commit remains one row; identity retirement and recovered bytes remain zero.

Keep the four Beacon file claims and prior Squish/SubObjects claims until confirmed publication, then release them and settle landed RVAs. No maintainer-only link cycle/nightly/smoke ran. Leave compatible donors for Luna.
