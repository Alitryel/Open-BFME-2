# DX8PolygonRenderer consolidation prerequisite, 2026-10-25

The prior normal trial rejected both constructor fragments with MSVC C1001
while combining their private class declarations with the seed's included
renderer header. The current reference header already declares the BFME
split-table fields used by these constructors. This is a declaration conflict,
not missing retail coverage.

## Primary constructor

DX8PolygonRendererCtor.cpp now includes the same renderer header and compiler
environment as dx8polygonrenderer.cpp. It drops its private renderer, mesh and
multilist declarations. The existing target evidence for MeshModel's polygon
list at +0x9C is kept as an explicit list view; no legacy donor mesh layout is
assumed. The real header's Add_Tail inlines to the existing Internal_Add_Tail
provider. No new global, pin, alias, pragma or helper is added.

`./build.sh DX8PolygonRendererCtor.cpp` preserves the entire 139-byte row at
0x00187DE0; literal, float, import and declared-unmatched checks pass. Normal
`tu_skeleton.py --merge .../dx8polygonrenderer.cpp --dry-run` now accepts the
seed and primary constructor, eight rows, versus no accepted pair before.
Receipts: build/sol-dx8polygon-ctor-header-build.txt and
build/sol-dx8polygon-ctor-header-after.txt. The untouched copy-constructor
fragment still encounters C1001. No merge is applied here; leave compatible
fragments for Luna's normal merge and destination checks.

## Ownership and publication audit

The outgoing range after b8e74688e5 contains the Bib allocation prerequisite
and this source edit. No source moves or disappears; no active tool, hook,
workflow, build input, include consumer or registry needs a path update.
The existing quoted renderer header resolves through the same include order
as the seed. Original EA paths and earlier evidence are retained as history.
No identity/data/header-register key names the constructor donor, and no
protected register or row owner is changed. Byte verification includes the
constructor reference and selected inline list provider. Debt retirement is
not claimed. Actual source files removed 0, recovered bytes 0, identity keys
retired 0. Keep the source/handoff claims until publication is confirmed.

## Copy constructor follow-up

DX8PolygonRendererCopyCtor.cpp now adopts the same header and compiler
include environment. Its field initializers stay unchanged, and its list
insertion uses the same retail-proven +0x9C list view as the primary ctor.
`./build.sh DX8PolygonRendererCopyCtor.cpp` preserves all 149 bytes at
0x00187E90, with literal/float/import and declared-unmatched checks passing.
The normal merge dry run now accepts the seed and both constructor fragments:
three files, nine rows, no rejected donors. Receipts:
build/sol-dx8polygon-copy-header-build.txt and
build/sol-dx8polygon-copy-header-after.txt. Luna can apply the ordinary merge;
this prerequisite commit itself removes no file or identity key.

The outgoing range from its merge base with origin/master plus this staged
change still contains only in-place source repairs, evidence and the attempt
log. There are no pending source moves, changed include targets or deleted
paths for active tools, hooks, workflows, build inputs or registries to follow.
The earlier publication audit therefore remains applicable to the full batch.
