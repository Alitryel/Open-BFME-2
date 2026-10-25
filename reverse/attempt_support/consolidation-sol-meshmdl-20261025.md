# Mesh-model consolidation prerequisite, 2026-10-25

Seat codexb, Libraries pool. The normal meshmdl.cpp dry run rejected every
clean donor: its fullest MeshModelClass view in MeshModelClassAssign.cpp
lacked the seed's Needs_Vertex_Normals declaration, Get_Flag and PRELIT_MASK.
The material-description view also lacked Do_Mappers_Need_Normals.

The assignment donor now declares those existing methods and exposes the
seed's target-proven flag byte at +0x19 inside MeshGeometryClass's padding.
The base remains 0x8C bytes and the material pointers retain their proven
offsets, including CurMatDesc at +0x94. This is reconciliation of existing
BFME 2 views; the external donor names and layouts are not additional target
evidence. The assignment body and all virtual declarations are unchanged.
No canonical class header is registered for MeshModelClass.

Acceptance: ./build.sh for assignment and seed preserves all four rows,
including the assignment's EH rows. eh_verify reports one EXACT parent,
zero missing objects. Declared-unmatched passes. Code identity scans four
rows with zero new findings, including selected definitions and the direct
provider bindings (unregister, gap-filler, mesh/material assignment, allocation,
copy and clone). Data identity reports zero findings. The scoped Microsoft
header refresh retains the assignment's existing four same-definition items
unchanged; there is no canonical-header queue entry or code/data identity
baseline key to retire or transfer. No source path or ledger owner changes.

The after dry run accepts seed plus assignment, four rows, and emits composed
C++. Leave that subset for Luna's ordinary merge and destination checks.
Make_Geometry_Unique still lacks its buffer fields in the selected view;
mixed and protected donors remain untouched. Local receipts:
build/sol-meshmdl-before.txt, build/sol-meshmdl-prereq-build.txt and
build/sol-meshmdl-after.txt.

The complete outgoing prerequisite batch still has no path moves. Active
tooling, hooks, workflows, includes, build inputs, registries and historical
paths need no repointing. Existing debt keys retain their source owners.
No recovered/linked bytes, file reduction or identity retirement is claimed.
Keep file claims for meshmdl.cpp, MeshModelClassAssign.cpp and this handoff,
plus RVAs 0x00171850 and 0x00171E60, until publication is confirmed.

## Font-library investigation boundary

The current normal W3DGameFont.cpp dry run accepts the seed, vector destructors
and unsigned Add (six rows). The font-cache donor still fails because the
selected FontCharsClass has a three-argument API while the target worker uses
four arguments. The library destructor still has private SimpleVec/SimpleDynVec
templates conflicting with the seed's headers. Existing re_attempts entries
also document incompatible FontLibrary/W3DFontLibrary virtual contracts.
No font source was edited or claimed, and no merge applied. Reconcile that
broader contract before repeating this unchanged trial. Receipt:
build/sol-gamefont-before.txt.
