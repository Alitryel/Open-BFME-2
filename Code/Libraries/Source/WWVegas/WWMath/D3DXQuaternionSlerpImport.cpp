// cl: /O2 /G7 /MD /arch:SSE2 /DNDEBUG
// Retail RVA 0x0075B4C6 is a 6B FF25 import thunk through IAT VA 0x00BBAA28.
// The PE independently names d3dx9_27.dll!D3DXQuaternionSlerp; the validated
// D3DX declaration supplies stdcall16 and the quaternion-pointer return ABI.
// Quaternion is the existing shared type, used opaquely here. The address-derived
// wrapper spelling is structural, not a claim about the original thunk name.
// Ordinary C++ tail forwarding emits the entire thunk without inline assembly.
class Quaternion;
extern "C" __declspec(dllimport) Quaternion * __stdcall D3DXQuaternionSlerp(Quaternion *, const Quaternion *, const Quaternion *, float);
extern "C" Quaternion * __stdcall rva0075B4C6D3DXQuaternionSlerp(Quaternion *res, const Quaternion *quaternion, const Quaternion *q, float alpha)
{
    return D3DXQuaternionSlerp(res, quaternion, q, alpha);
}
