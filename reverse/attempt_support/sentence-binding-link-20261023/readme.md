# Sentence destructor binding prerequisite

Inputs: BFME 2 dc623d4c10, BFME 1 96c88c73a5cd1a58fc2f8db691beea50acd996db,
MSVC 7.1, each source's committed `// cl:` flags. Published census b711de3634.

Current-source four-unit cohort (sentence destructor, render2dsentence,
PendingSurfaceStructResize, ATL/Rva00001E13Dtor) links only the last 8-byte unit.
The sentence destructor owns 356 nonpadding matched bytes. It is blocked by
undefined EnumParameterClass::ENUM_VALUE::~ENUM_VALUE and the first selected
non-retail VectorClass<PendingSurfaceStruct>::Resize from render2dsentence.cpp.
Other two large units have additional independent blockers.

Native 0x00157C70 has a proven 347-byte boundary. At 0x00157D1A it selects
array callback 0x00001E13 with stride 8; that rowed callback adds four to this
and tail-calls W3DRadarResetSurface::~W3DRadarResetSurface. The inherited enum
name and ILT 0x000470F5 comment do not identify this target record. The tracked
patch uses the rowed Rva00001E13 view only for native element teardown while
retaining the established vector spelling/vtable. All 5/5 rows (including
renumbered EH funclets), string/float/import checks and frozen-file check pass.
This is a verified prerequisite, not a claimed link gain or record identity.

Two bounded provider trials declared only the native pending-surface Resize:
explicit specialization and extern explicit member instantiation. Both fail
C2248 on the private PendingSurfaceStruct parameter. The unit's existing whole
class explicit instantiation can name that type, but does not solve selective
member suppression. No class access or shared header was changed. A proper
class-view reconciliation or explicit-instantiation strategy is prerequisite;
then reapply the patch and measure the complete provider cohort. Do not claim
the patch alone links the unit. Both source files restored.
