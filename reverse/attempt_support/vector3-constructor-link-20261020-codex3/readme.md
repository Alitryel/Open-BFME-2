# Vector3 dynamic-vector constructor selection

The published b73720bed9 index selects non-retail copies of the
DynamicVectorClass<Vector3>(unsigned, const Vector3 *) constructor from
dx8renderer.cpp, mesh.cpp and collect.cpp. The 39-byte native body at
0x000F1C7A is already rowed in FXShaderRendererSkin.cpp. Its base call goes
to the 12-byte-stride VectorClass<Vector3> constructor at 0x000F0D2F and its
vtable is 0x00BCEFDC; the row's native caller evidence identifies Vector3,
not the formerly claimed 16-byte Curve3D key type.

Declare that constructor specialization in the three competing units so
their calls use the existing verified provider. No flags, class layout,
implementation, pins, aliases or shared headers change. This sweeps every
wrong constructor copy in the index.

The five-file paired legacy prediction goes 0 -> 394 linked bytes, all in
Rva007ABEF3ArgCtorInits.cpp. Other scope members retain the independent
blockers shown in after.txt; FXShaderRendererSkin itself still loses Resize
and has unrowed rendering callees. No formal self-strict or closed-strict
link-cycle gain is claimed. Scoped byte gate: 143/143 across six sources
(the mesh.cpp filter includes a sibling); all touched files pass the frozen
source check. EH results are recorded alongside this handoff.

Target facts come from the rowed native constructor, consumers and full
byte checks; the existing WWLib source supplies template semantics. The
current BFME1 linking-donor review is in
script-cleanup-link-20261020-codex3/readme.md. No new donor input was used.
