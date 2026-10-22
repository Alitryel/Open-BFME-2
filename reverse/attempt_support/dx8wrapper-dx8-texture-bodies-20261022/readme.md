# dx8wrapper.cpp: unmatched DX8-typed bodies removed (2026-10-22)

`removed_bodies.cpp.txt` holds the Zero Hour-ported definitions taken out of
`Code/Libraries/Source/WWVegas/WW3D2/dx8wrapper.cpp` so the unit's 203 matched
rows (27,106 bytes) link:

- `Non_Fatal_Log_DX8_ErrorCode`, `DX8Wrapper::Begin_Scene`,
  `getBackBufferFormat`, `_Get_DX8_Back_Buffer`,
  `Create_Render_Target(int, int, WW3DFormat)`;
- the three `_Create_DX8_Texture` overloads, `_Create_DX8_ZTexture`,
  `_Create_DX8_Cube_Texture`, `_Create_DX8_Volume_Texture`.

None had a ledger row (each was `present-unmatched` or unmarked), nothing else
in the unit called them, and they were the unit's only references to ten
undefined names (`D3DX*`, the DX8-typed format converters,
`SurfaceClass(IDirect3DSurface8*)`, `DX8WebBrowser::Update`,
`MissingTexture::_Get_Missing_Texture`). They are Zero Hour's DX8 signatures;
BFME 2 is a Direct3D 9 build, so their mangled names are not retail's either.

texture.cpp, ww3d.cpp and HeightMap.cpp reference some of these DX8 names. All
three already failed to link on other DX8-typed names before this change; they
now list the removed names among their unresolved ones.

Recover a body from this file only with a D3D9 signature that byte-matches
retail, and add it with a row.
