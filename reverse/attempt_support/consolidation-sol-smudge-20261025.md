# W3DSmudge consolidation prerequisites, 2026-10-25

## Constructor header adoption

The device Luna handoff reports C2065 for `m_probeColor` when the constructor
fragment is composed with the seed's legacy W3DSmudge header. This is an
existing matched body at 0x000A60F0, not a missing retail row.

The retail 48-byte constructor calls SmudgeManager, zeroes seven dwords at
+0x24 through +0x3C, installs its vtable and stores 0x00FFEEDD at +0x40.
The seed header provides the seven ordinary members but stops before the
BFME probe-color tail. The constructor now uses that same header and include
environment, retaining an explicit target-proven +0x40 access for the tail.
No external donor layout is treated as evidence for that added dword.

`./build.sh W3DSmudgeManagerConstructor.cpp` preserves the entire 48-byte row;
literal, float, import and declared-unmatched checks pass. Receipt:
build/sol-smudge-ctor-header-build.txt. The normal merge trial and remaining
prerequisites are recorded below after its completion.

No source path moves or disappears. No protected register names the ctor
fragment; no header, data or identity retirement is claimed. The outgoing
batch's source edits are all in place, so there are no changed paths for active
tools, hooks, workflows, include consumers, build inputs or registries to
follow. Original EA paths and earlier blocker evidence remain unchanged.

The normal `--merge W3DSmudge.cpp --dry-run` now accepts the seed and ctor,
eight rows, versus no accepted donor in the earlier Luna trial. Receipt:
build/sol-smudge-ctor-header-after.txt. Remaining whole-file blockers are
ReleaseResources C2440 (`DX8IndexBufferClass *` to `IndexBufferRef *`),
ReAcquireResources byte mismatch, and copyRect C1001. Mixed render/probe/math
files still need the supported split lane. No merge is applied in this commit.

## Release-resources slot view

The fresh ctor trial reproduces C2440 in ReleaseResources when the native
IndexBufferRef pointer is initialized from the seed header's DX8IndexBufferClass
slot. Keep that slot's real class name in the donor too, and cast only the local
view used for its native refcount-prefix operations. Retail proves the slot at
+0x34, count at pointee +4 and zero-count call through vtable slot zero.
The native body at 0x000A6135 and its EH handler remain byte exact (2/2 rows,
65-byte body plus 10-byte handler); literals, floats, imports and the frozen-file
check pass. Receipt: build/sol-smudge-release-build.txt. The old leading
comment's other-image address/size and unrelated GameFont path were corrected.
No row, protected register, path consumer or escape-hatch count changes.

Normal `--merge W3DSmudge.cpp --dry-run` now accepts all three files (seed,
constructor and release resources), preserving ten rows; the only rejected
whole-file donors are still ReAcquireResources (`bytes`) and copyRect (C1001).
Receipt: build/sol-smudge-release-after.txt. The original comment about a
reloaded count was also corrected to the retail decrement/branch sequence.
This leaves the compatible three-file subset ready for Luna, without changing
identity ownership or claiming a full subsystem merge.
