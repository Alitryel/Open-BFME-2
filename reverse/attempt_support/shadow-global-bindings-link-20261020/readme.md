Shadow renderer global bindings, 2026-10-20

RenderDynamicMeshVolume newly links +2,730 B in paired legacy previews against
census 2026-10-20 18:36 at e7a7769fe5. The four checked neighbouring/provider
units stay linked: 4,802 -> 7,532 B total. This is a legacy prediction, not a
closed-strict gain, census update or full executable link.

Bind the renderer's three unresolved global declarations to existing providers:
- g_Va00DEBE0C -> g_00DEBE0C, the typed TCB vector defined by Rva000F1A32Ctor;
- g_Va00DEBD00 -> shadowCameraFrustum, defined by RenderShadows;
- Rva00DDD9D0Identity -> Matrix3D::Identity, defined by matrix3d.cpp.
No new data definition, pin, alternate name or shared header is introduced.

The first two bindings are supported by the existing target relocation
addresses, provider definitions and the adjacent matched shadow consumers.
The identity name has more than a single value/shape match: matrix3d.cpp's
entire ten-matrix 480-byte region, starting with Identity, equals the retail
region at RVA 0x009DD9D0 without any relocations (identity.txt). RenderVolume
already uses that real name at the same target. No new complete class-layout
claim is made; existing private views and their verified field access remain.
name_globals.py --dry-run found no literal-address rewrite in this unit.

Before and after self-strict preparation: all 12 renderer rows exact; strings,
floats and imports pass, parent EH graph EXACT despite label renumbering.
The three providers are separately byte-verified. Frozen-source, class gate,
converged data and diff checks pass. No compiled function bytes are added.

BFME1 donor remains at verified 4483e88da; relevant current linking commits
reviewed earlier in the session contained no same-name repair. The target's
own providers, adjacent renderer and full constant region establish this fix.
