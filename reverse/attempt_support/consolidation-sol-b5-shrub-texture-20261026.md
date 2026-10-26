# Shrub texture composition prerequisite, 2026-10-26

Seat codexb5, allocated family B shard 1/2. This extends the verified movement
prerequisite for Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DShrubBuffer.cpp;
the allocated destination check exited 0. Scoped planner refreshed under that
GameClient directory after the final edit; current routing remains authoritative.

## Demonstrated unblock

The texture donor previously used private texture/packer fields absent from the
seed's opaque base. Give the existing base storage protected access, retaining
its extent, and express the donor's existing offsets through typed views of that
storage. Align the donor's type-array origin with the seed at +0x4FB70; its
texture-specific view starts at +0x20 within each 0x5C record. The existing count
remains at +0x51270. No new canonical layout or donor name is claimed.

Normal `tu_skeleton.merge(..., dry_run=True)` now accepts the seed plus
W3DShrubBufferRva000E72B3.cpp, W3DShrubBufferUnitMoved.cpp and
W3DShrubBufferUpdateTexture.cpp together: 21 rows, up from 13 before this repair.
The additional eight existing rows include the 692-byte updateTexture body and
its unwind funclets. No merge was applied. This is a demonstrated prerequisite
for Luna, with no subsequent Luna landing claimed.

## Verification

- `./build.sh` on all four affected files: 21/21 exact; two string literals,
  four empty-string references, 12 float literals and four imports verified.
  `find_declared_unmatched.py` passes all four files.
- Before/after supported `allowed_symbols.load/scan`, object definition,
  `link_census._comdat_selections` and `data_check.object_facts` receipts are
  identical after normalizing local EH labels. All 59 bindings remain unchanged
  (45 owner, nine alias, three fold, two EH), as do external definitions,
  undefined names, COMDAT selections/flags and data facts.
- Capture the object produced by the normal merge verifier; all 21 rows reverify.
  The composition preserves all 59 bindings, drops no external definition and
  adds no undefined symbol. It emits the same empty Coord3D constructor already
  verified against its retail owner in the preceding movement prerequisite.
  Global lowest-RVA provider selection over all 43 composed names changes zero
  selected definitions; data binding and definition sets are equal.
- `eh_verify.py` on standalone sources and on the captured composed object:
  two exact EH rows each, no failures. `class_gate.py`, shadow and converged
  `data_check.py`, `ms_header_audit.py check` and `git diff --check` pass.
- The adjacent JSON preserves before/after facts, composition, consumer-binding,
  selected-provider, EH and source-hash receipts. Scratch scripts in build/
  call supported evidence APIs and never `build.compile_source`.

## Remaining prerequisites and outgoing audit

The full shrub TU still rejects other private class declarations, mixed donors
and STL/include collisions. Existing header and identity debt stays accounted
for at its original paths. No ledger, TU map, register, baseline or escape hatch
changed. Recovered bytes, source-file reduction and identity-debt retirement
are each zero.

Audited outgoing merge-base range through 2942b64f40 plus this prerequisite:
no existing source path moves. The only new source header is the preceding
waypoint prerequisite's TU-local render view; its two direct consumers and the
hook's dependent-source scope were verified. No active tool, hook, workflow,
include, build input or registry requires repointing. Historical EA paths are
retained. No maintainer-only link cycle, smoke or nightly run was started.

Read-only allocated LadderDefs reassessment (`--plan` and normal `--merge
--dry-run`) now fails final verification with C2950 at
reference/shims/bfmealloc/stl/_alloc.h:446: allocator<char> explicitly instantiates
an explicit specialization. No donors accepted and no source changed. Its
existing helper-provider prerequisite is not sufficient to clear this final
compile obstacle; do not repeat the unchanged trial. Mixed donors remain too.

Keep the four shrub source scopes and associated evidence claims until confirmed
publication; then release file scopes and settle landed RVAs. Earlier index,
composed-provider and waypoint claims remain attached to the same pending batch.
