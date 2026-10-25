# Mesh geometry-copy prerequisite, 2026-10-25

Seat codexb, Libraries pool. The prior ordinary meshmdl dry run accepted only
seed plus assignment (four rows). Make_Geometry_Unique collided with <new>
through the legacy always.h array-placement allocation definitions; its private
MeshModelClass buffer fields also could not compose with the assignment view.

The donor now uses <new>/<stddef.h>, forward-declares its unused element types,
and retains the existing count-at-4, Delete_This slot-0 refcount operations as
plain C++. Its existing target buffer offsets stay in a body-specific view;
seed and assignment views declare the existing method. No new layout, donor
identity or field-offset claim is inferred from the external reference.

Acceptance:
- ./build.sh meshmdl.cpp MeshModelClassAssign.cpp
  MeshModelClassMakeGeometryUnique.cpp: 11/11 rows exact, including the
  505-byte body, five unwind bodies and handler. EH verify: two EXACT parents,
  zero missing objects. Declared-unmatched passes for all three sources.
- The ordinary --merge meshmdl.cpp --dry-run accepts all three files and all
  11 rows with composed C++. This adds seven compatible rows to the existing
  four-row subset; the merge itself is left for Luna.
- Code identity: 11 rows, zero new findings in shadow. Data identity: zero
  findings. Microsoft-header scan: three files, zero local definitions; scoped
  refresh leaves the queue unchanged. No canonical class/header queue or
  identity/data baseline key is owned by these three files.

Receipts: build/sol-mesh-unique-{plan,build,after,identity,data,eh,headers}.txt.
The current source paths and row ownership stay unchanged; protected and mixed
satellites are retained. No identity key is retired, file removed or C++ byte
recovered by this prerequisite. The complete outgoing range has no path moves;
active tools, hooks, workflows, includes, build inputs and registries need no
repointing, and historical EA paths are preserved.

Keep the three source file claims, this handoff and RVA 0x00172070 until the
commit is confirmed published. Then release them; Luna can perform the normal
claimed merge and its destination acceptance checks.
