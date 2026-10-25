# W3DBibBuffer allocation prerequisite, 2026-10-25

Scope: the normal W3DBibBuffer.cpp consolidation trial previously rejected the
allocation donor because its private vertex-buffer slot was typed as
BfmeDynamicNativeVB*, whereas the seed exposes the slot as DX8VertexBufferClass*
for its lock API. The allocation still constructs the target-proven native
buffer; this change casts that pointer into the slot's existing seed view.
It does not infer inheritance or change allocation size, constructor arguments,
field placement, flags, or a ledger row.

## Verification

- `./build.sh Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBibBuffer_allocateBibBuffers.cpp`:
  4/4 existing rows exact, including both EH funclets; no string, float or
  import references. Receipt: build/sol-bib-allocate-build.txt.
- `find_declared_unmatched.py` passes for the donor; `git diff --check` passes.
- Normal `tu_skeleton.py --merge Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DBibBuffer.cpp --dry-run`
  now accepts the seed plus allocation donor, 15 rows. Before this repair the
  trial accepted neither. Receipt: build/sol-bib-allocate-after.txt.
- Remaining independent donors: W3DBibBufferDtor.cpp fails byte verification;
  W3DBibBufferConstructor.cpp produces MSVC C1001 in composition. Neither is
  changed or claimed here. A full four-file merge remains blocked. Luna may
  merge the accepted allocation pair through the normal tool.

## Batch and ownership audit

At b8e74688e5 the preceding batch is published. This prerequisite changes one
source in place and adds this handoff: no source paths move or disappear, and
there are no new include consumers. The active tools/hooks/workflows/build
inputs and path-keyed ledgers need no repointing. Existing identity, data and
header registers contain no key for the allocation donor; no register is
edited or debt retirement claimed. Retail names, existing pins, EH parent
ownership and constructor references are preserved. No merge or split is
applied: source files removed 0, recovered C++ bytes 0, identity keys retired 0.
