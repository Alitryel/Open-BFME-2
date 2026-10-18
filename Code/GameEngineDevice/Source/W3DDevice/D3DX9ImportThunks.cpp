// cl: /O2 /G7 /Oy /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// Typed C++ forwarding through genuine PE import-pointer symbols.
// VS2003 __identifier names the actual decorated __imp__ symbol; no alias,
// address pin, inline assembly, emitted bytes or replacement datum is used.
// Public API types and signatures: Microsoft D3DX9 SDK documentation.
#include <windows.h>
struct D3DXMATRIX;
struct D3DXVECTOR3;
struct D3DXMACRO;
struct D3DXIMAGE_INFO;
struct D3DXSEMANTIC;
struct ID3DXInclude;
struct ID3DXBuffer;
struct ID3DXEffect;
struct ID3DXEffectPool;
struct IDirect3DDevice9;
struct IDirect3DTexture9;
struct IDirect3DCubeTexture9;
struct IDirect3DVolumeTexture9;
struct IDirect3DBaseTexture9;
struct IDirect3DSurface9;
struct IDirect3DVolume9;
struct _D3DBOX;
typedef _D3DBOX D3DBOX;
enum _D3DFORMAT;
typedef _D3DFORMAT D3DFORMAT;
enum _D3DPOOL;
typedef _D3DPOOL D3DPOOL;
typedef DWORD D3DCOLOR;
typedef ID3DXInclude *LPD3DXINCLUDE;
typedef ID3DXBuffer *LPD3DXBUFFER;
typedef ID3DXEffect *LPD3DXEFFECT;
typedef ID3DXEffectPool *LPD3DXEFFECTPOOL;
typedef IDirect3DDevice9 *LPDIRECT3DDEVICE9;
typedef IDirect3DTexture9 *LPDIRECT3DTEXTURE9;
typedef IDirect3DCubeTexture9 *LPDIRECT3DCUBETEXTURE9;
typedef IDirect3DVolumeTexture9 *LPDIRECT3DVOLUMETEXTURE9;
typedef IDirect3DBaseTexture9 *LPDIRECT3DBASETEXTURE9;
typedef IDirect3DSurface9 *LPDIRECT3DSURFACE9;
typedef IDirect3DVolume9 *LPDIRECT3DVOLUME9;
typedef char D3DX9ForwardedWidths[(sizeof(D3DFORMAT)==4 && sizeof(D3DPOOL)==4 && sizeof(FLOAT)==4 && sizeof(DWORD)==4 && sizeof(HRESULT)==4 && sizeof(void*)==4) ? 1 : -1];
extern "C" {
// _D3DXMatrixMultiply@12
typedef D3DXMATRIX* (__stdcall *PFN_D3DXMatrixMultiply)(D3DXMATRIX *, const D3DXMATRIX *, const D3DXMATRIX *);
extern PFN_D3DXMatrixMultiply __identifier("_imp__D3DXMatrixMultiply@12");
D3DXMATRIX* __stdcall D3DXMatrixMultiply(D3DXMATRIX *pOut, const D3DXMATRIX *pM1, const D3DXMATRIX *pM2) {
 return __identifier("_imp__D3DXMatrixMultiply@12")(pOut, pM1, pM2);
}

// _D3DXMatrixScaling@16
typedef D3DXMATRIX* (__stdcall *PFN_D3DXMatrixScaling)(D3DXMATRIX *, FLOAT, FLOAT, FLOAT);
extern PFN_D3DXMatrixScaling __identifier("_imp__D3DXMatrixScaling@16");
D3DXMATRIX* __stdcall D3DXMatrixScaling(D3DXMATRIX *pOut, FLOAT sx, FLOAT sy, FLOAT sz) {
 return __identifier("_imp__D3DXMatrixScaling@16")(pOut, sx, sy, sz);
}
}
