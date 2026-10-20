NewMap provider reconciliation, 2026-10-20

Trial replaced the old Rva002E713F460::rva00533BEC(void*,void*,void*) call
with the rowed PathfindZoneManager::Update(PathfindCell**,PathfindLayer*,
const IRegion2D&) at 0x00533BEC. All 3/3 NewMap rows and 37/37 across the
callee units passed strict byte/string/float/import checks. Only the callee
relocation changed; there is only one caller of the old placeholder.

No repair landed: legacy preview on 5366c4f808 still has an unresolved bool
Pathfinder::rva00530212 because its newly landed unit is absent from that
census. Refreshing that object cannot insert a new provider into the measured
universe. Supported --refresh --current-ledger refused 26 missing objects
(including W3DDisplayDraw, Render2DClassRender, W3DTerrainBackgroundDoPartialUpdate,
DX8RendererAddMesh and MeshGeometryGetEdges). Do not fabricate provider order
or rebuild a census in a model seat. Restore source; retry the trivial typed
call replacement after the next published census includes the classifier or
current-ledger evidence is fully available. No legacy/closed-strict gain claimed.
