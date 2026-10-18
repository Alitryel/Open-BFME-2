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

// _D3DXMatrixTranslation@16
typedef D3DXMATRIX* (__stdcall *PFN_D3DXMatrixTranslation)(D3DXMATRIX *, FLOAT, FLOAT, FLOAT);
extern PFN_D3DXMatrixTranslation __identifier("_imp__D3DXMatrixTranslation@16");
D3DXMATRIX* __stdcall D3DXMatrixTranslation(D3DXMATRIX *pOut, FLOAT x, FLOAT y, FLOAT z) {
 return __identifier("_imp__D3DXMatrixTranslation@16")(pOut, x, y, z);
}

// _D3DXAssembleShader@28
typedef HRESULT (__stdcall *PFN_D3DXAssembleShader)(LPCSTR, UINT, const D3DXMACRO *, LPD3DXINCLUDE, DWORD, LPD3DXBUFFER *, LPD3DXBUFFER *);
extern PFN_D3DXAssembleShader __identifier("_imp__D3DXAssembleShader@28");
HRESULT __stdcall D3DXAssembleShader(LPCSTR pSrcData, UINT SrcDataLen, const D3DXMACRO *pDefines, LPD3DXINCLUDE pInclude, DWORD Flags, LPD3DXBUFFER *ppShader, LPD3DXBUFFER *ppErrorMsgs) {
 return __identifier("_imp__D3DXAssembleShader@28")(pSrcData, SrcDataLen, pDefines, pInclude, Flags, ppShader, ppErrorMsgs);
}

// _D3DXMatrixTranspose@8
typedef D3DXMATRIX* (__stdcall *PFN_D3DXMatrixTranspose)(D3DXMATRIX *, const D3DXMATRIX *);
extern PFN_D3DXMatrixTranspose __identifier("_imp__D3DXMatrixTranspose@8");
D3DXMATRIX* __stdcall D3DXMatrixTranspose(D3DXMATRIX *pOut, const D3DXMATRIX *pM) {
 return __identifier("_imp__D3DXMatrixTranspose@8")(pOut, pM);
}

// _D3DXMatrixRotationZ@8
typedef D3DXMATRIX* (__stdcall *PFN_D3DXMatrixRotationZ)(D3DXMATRIX *, FLOAT);
extern PFN_D3DXMatrixRotationZ __identifier("_imp__D3DXMatrixRotationZ@8");
D3DXMATRIX* __stdcall D3DXMatrixRotationZ(D3DXMATRIX *pOut, FLOAT Angle) {
 return __identifier("_imp__D3DXMatrixRotationZ@8")(pOut, Angle);
}

// _D3DXFilterTexture@16
typedef HRESULT (__stdcall *PFN_D3DXFilterTexture)(LPDIRECT3DBASETEXTURE9, const PALETTEENTRY *, UINT, DWORD);
extern PFN_D3DXFilterTexture __identifier("_imp__D3DXFilterTexture@16");
HRESULT __stdcall D3DXFilterTexture(LPDIRECT3DBASETEXTURE9 pBaseTexture, const PALETTEENTRY *pPalette, UINT SrcLevel, DWORD MipFilter) {
 return __identifier("_imp__D3DXFilterTexture@16")(pBaseTexture, pPalette, SrcLevel, MipFilter);
}

// _D3DXLoadSurfaceFromMemory@40
typedef HRESULT (__stdcall *PFN_D3DXLoadSurfaceFromMemory)(LPDIRECT3DSURFACE9, const PALETTEENTRY *, const RECT *, LPCVOID, D3DFORMAT, UINT, const PALETTEENTRY *, const RECT *, DWORD, D3DCOLOR);
extern PFN_D3DXLoadSurfaceFromMemory __identifier("_imp__D3DXLoadSurfaceFromMemory@40");
HRESULT __stdcall D3DXLoadSurfaceFromMemory(LPDIRECT3DSURFACE9 pDestSurface, const PALETTEENTRY *pDestPalette, const RECT *pDestRect, LPCVOID pSrcMemory, D3DFORMAT SrcFormat, UINT SrcPitch, const PALETTEENTRY *pSrcPalette, const RECT *pSrcRect, DWORD Filter, D3DCOLOR ColorKey) {
 return __identifier("_imp__D3DXLoadSurfaceFromMemory@40")(pDestSurface, pDestPalette, pDestRect, pSrcMemory, SrcFormat, SrcPitch, pSrcPalette, pSrcRect, Filter, ColorKey);
}

// _D3DXVec3TransformCoordArray@24
typedef D3DXVECTOR3* (__stdcall *PFN_D3DXVec3TransformCoordArray)(D3DXVECTOR3 *, UINT, const D3DXVECTOR3 *, UINT, const D3DXMATRIX *, UINT);
extern PFN_D3DXVec3TransformCoordArray __identifier("_imp__D3DXVec3TransformCoordArray@24");
D3DXVECTOR3* __stdcall D3DXVec3TransformCoordArray(D3DXVECTOR3 *pOut, UINT OutStride, const D3DXVECTOR3 *pV, UINT VStride, const D3DXMATRIX *pM, UINT n) {
 return __identifier("_imp__D3DXVec3TransformCoordArray@24")(pOut, OutStride, pV, VStride, pM, n);
}

// _D3DXCreateTexture@32
typedef HRESULT (__stdcall *PFN_D3DXCreateTexture)(LPDIRECT3DDEVICE9, UINT, UINT, UINT, DWORD, D3DFORMAT, D3DPOOL, LPDIRECT3DTEXTURE9 *);
extern PFN_D3DXCreateTexture __identifier("_imp__D3DXCreateTexture@32");
HRESULT __stdcall D3DXCreateTexture(LPDIRECT3DDEVICE9 pDevice, UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DTEXTURE9 *ppTexture) {
 return __identifier("_imp__D3DXCreateTexture@32")(pDevice, Width, Height, MipLevels, Usage, Format, Pool, ppTexture);
}

// _D3DXCreateTextureFromFileInMemoryEx@60
typedef HRESULT (__stdcall *PFN_D3DXCreateTextureFromFileInMemoryEx)(LPDIRECT3DDEVICE9, LPCVOID, UINT, UINT, UINT, UINT, DWORD, D3DFORMAT, D3DPOOL, DWORD, DWORD, D3DCOLOR, D3DXIMAGE_INFO *, PALETTEENTRY *, LPDIRECT3DTEXTURE9 *);
extern PFN_D3DXCreateTextureFromFileInMemoryEx __identifier("_imp__D3DXCreateTextureFromFileInMemoryEx@60");
HRESULT __stdcall D3DXCreateTextureFromFileInMemoryEx(LPDIRECT3DDEVICE9 pDevice, LPCVOID pSrcData, UINT SrcDataSize, UINT Width, UINT Height, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, LPDIRECT3DTEXTURE9 *ppTexture) {
 return __identifier("_imp__D3DXCreateTextureFromFileInMemoryEx@60")(pDevice, pSrcData, SrcDataSize, Width, Height, MipLevels, Usage, Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, ppTexture);
}

// _D3DXLoadSurfaceFromFileInMemory@36
typedef HRESULT (__stdcall *PFN_D3DXLoadSurfaceFromFileInMemory)(LPDIRECT3DSURFACE9, const PALETTEENTRY *, const RECT *, LPCVOID, UINT, const RECT *, DWORD, D3DCOLOR, D3DXIMAGE_INFO *);
extern PFN_D3DXLoadSurfaceFromFileInMemory __identifier("_imp__D3DXLoadSurfaceFromFileInMemory@36");
HRESULT __stdcall D3DXLoadSurfaceFromFileInMemory(LPDIRECT3DSURFACE9 pDestSurface, const PALETTEENTRY *pDestPalette, const RECT *pDestRect, LPCVOID pSrcData, UINT SrcData, const RECT *pSrcRect, DWORD Filter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo) {
 return __identifier("_imp__D3DXLoadSurfaceFromFileInMemory@36")(pDestSurface, pDestPalette, pDestRect, pSrcData, SrcData, pSrcRect, Filter, ColorKey, pSrcInfo);
}

// _D3DXCheckTextureRequirements@28
typedef HRESULT (__stdcall *PFN_D3DXCheckTextureRequirements)(LPDIRECT3DDEVICE9, UINT *, UINT *, UINT *, DWORD, D3DFORMAT *, D3DPOOL);
extern PFN_D3DXCheckTextureRequirements __identifier("_imp__D3DXCheckTextureRequirements@28");
HRESULT __stdcall D3DXCheckTextureRequirements(LPDIRECT3DDEVICE9 pDevice, UINT *pWidth, UINT *pHeight, UINT *pNumMipLevels, DWORD Usage, D3DFORMAT *pFormat, D3DPOOL Pool) {
 return __identifier("_imp__D3DXCheckTextureRequirements@28")(pDevice, pWidth, pHeight, pNumMipLevels, Usage, pFormat, Pool);
}

// _D3DXLoadVolumeFromFileInMemory@36
typedef HRESULT (__stdcall *PFN_D3DXLoadVolumeFromFileInMemory)(LPDIRECT3DVOLUME9, const PALETTEENTRY *, const D3DBOX *, LPCVOID, UINT, const D3DBOX *, DWORD, D3DCOLOR, D3DXIMAGE_INFO *);
extern PFN_D3DXLoadVolumeFromFileInMemory __identifier("_imp__D3DXLoadVolumeFromFileInMemory@36");
HRESULT __stdcall D3DXLoadVolumeFromFileInMemory(LPDIRECT3DVOLUME9 pDestVolume, const PALETTEENTRY *pDestPalette, const D3DBOX *pDestBox, LPCVOID pSrcData, UINT SrcDataSize, const D3DBOX *pSrcBox, DWORD Filter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo) {
 return __identifier("_imp__D3DXLoadVolumeFromFileInMemory@36")(pDestVolume, pDestPalette, pDestBox, pSrcData, SrcDataSize, pSrcBox, Filter, ColorKey, pSrcInfo);
}

// _D3DXCreateVolumeTexture@36
typedef HRESULT (__stdcall *PFN_D3DXCreateVolumeTexture)(LPDIRECT3DDEVICE9, UINT, UINT, UINT, UINT, DWORD, D3DFORMAT, D3DPOOL, LPDIRECT3DVOLUMETEXTURE9 *);
extern PFN_D3DXCreateVolumeTexture __identifier("_imp__D3DXCreateVolumeTexture@36");
HRESULT __stdcall D3DXCreateVolumeTexture(LPDIRECT3DDEVICE9 pDevice, UINT Width, UINT Height, UINT Depth, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, LPDIRECT3DVOLUMETEXTURE9 *ppVolumeTexture) {
 return __identifier("_imp__D3DXCreateVolumeTexture@36")(pDevice, Width, Height, Depth, MipLevels, Usage, Format, Pool, ppVolumeTexture);
}

// _D3DXCreateVolumeTextureFromFileInMemoryEx@64
typedef HRESULT (__stdcall *PFN_D3DXCreateVolumeTextureFromFileInMemoryEx)(LPDIRECT3DDEVICE9, LPCVOID, UINT, UINT, UINT, UINT, UINT, DWORD, D3DFORMAT, D3DPOOL, DWORD, DWORD, D3DCOLOR, D3DXIMAGE_INFO *, PALETTEENTRY *, LPDIRECT3DVOLUMETEXTURE9 *);
extern PFN_D3DXCreateVolumeTextureFromFileInMemoryEx __identifier("_imp__D3DXCreateVolumeTextureFromFileInMemoryEx@64");
HRESULT __stdcall D3DXCreateVolumeTextureFromFileInMemoryEx(LPDIRECT3DDEVICE9 pDevice, LPCVOID pSrcData, UINT SrcDataSize, UINT Width, UINT Height, UINT Depth, UINT MipLevels, DWORD Usage, D3DFORMAT Format, D3DPOOL Pool, DWORD Filter, DWORD MipFilter, D3DCOLOR ColorKey, D3DXIMAGE_INFO *pSrcInfo, PALETTEENTRY *pPalette, LPDIRECT3DVOLUMETEXTURE9 *ppVolumeTexture) {
 return __identifier("_imp__D3DXCreateVolumeTextureFromFileInMemoryEx@64")(pDevice, pSrcData, SrcDataSize, Width, Height, Depth, MipLevels, Usage, Format, Pool, Filter, MipFilter, ColorKey, pSrcInfo, pPalette, ppVolumeTexture);
}
}
