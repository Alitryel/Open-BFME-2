// cl: /O2 /G7 /MD /Ireference/shims/sweep
// Target PE: FF25 at RVA62AFC8 through IAT BBA9DC is
// d3dx9_27.dll!D3DXVec3CatmullRom. The SDK declaration establishes five
// vector pointers plus float, stdcall24 and pointer result. Original thunk
// name is unknown. Ordinary C++ forwarding reproduces all six bytes.
#include "d3dx8math.h"
extern "C" __declspec(dllimport) D3DXVECTOR3 * __stdcall D3DXVec3CatmullRom(
    D3DXVECTOR3 *, const D3DXVECTOR3 *, const D3DXVECTOR3 *,
    const D3DXVECTOR3 *, const D3DXVECTOR3 *, float);
extern "C" D3DXVECTOR3 * __stdcall rva0062AFC8D3DXVec3CatmullRom(
    D3DXVECTOR3 *out, const D3DXVECTOR3 *d3DXVECTOR3, const D3DXVECTOR3 *p1,
    const D3DXVECTOR3 *p2, const D3DXVECTOR3 *p3, float t)
{
    return D3DXVec3CatmullRom(out, d3DXVECTOR3, p1, p2, p3, t);
}
