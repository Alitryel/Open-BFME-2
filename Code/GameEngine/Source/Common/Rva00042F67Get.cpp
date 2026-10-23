// cl: /GX-
// ?Rva00042F67Get@@YAHXZ @ 0x00042F67 (6B): global dword getter reading
// 0x00DEDA34 (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp (same shape; the
// load address is a .data global). Dedicated TU so no caller inlines the
// load (Rva007EB810Get precedent).

// dx8wrapper.cpp's protected ?D3DDevice@DX8Wrapper@@1PAUIDirect3DDevice8@@A, read through a
// TU-scoped friend view (real decoration, no alias).
struct IDirect3DDevice8;
class DX8Wrapper
{
	friend int Rva00042F67Get(void);
protected:
	static IDirect3DDevice8 *D3DDevice;
};

int Rva00042F67Get(void)
{
	return (int)DX8Wrapper::D3DDevice;
}
