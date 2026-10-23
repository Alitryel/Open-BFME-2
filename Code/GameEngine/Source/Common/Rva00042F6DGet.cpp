// cl: /GX-
// ?Rva00042F6DGet@@YAHXZ @ 0x00042F6D (6B): global dword getter reading
// 0x00DEDA7C (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp (same shape; the
// load address is a .data global). Dedicated TU so no caller inlines the
// load (Rva007EB810Get precedent).

// dx8wrapper.cpp's protected ?CurrentCaps@DX8Wrapper@@1PAVDX8Caps@@A, read through a
// TU-scoped friend view (real decoration, no alias).
class DX8Caps;
class DX8Wrapper
{
	friend int Rva00042F6DGet(void);
protected:
	static DX8Caps *CurrentCaps;
};

int Rva00042F6DGet(void)
{
	return (int)DX8Wrapper::CurrentCaps;
}
