// cl: /GX-
// DX8Wrapper device-query leaves:
// ?Rva00116F50@@YA_NXZ @ 0x00116F50 (11B): normalizes
// DX8Wrapper::Set_Next_Render_Device to bool (call + test + setne).
// ?Rva00116F60Get@@YAHXZ @ 0x00116F60 (6B): global dword getter over
// the window handle at 0x00DEC408 (mov eax,[mem]; ret).
// ?Rva00116F00@@YA_NXZ @ 0x00116F00 (11B): normalizes
// DX8Wrapper::Set_Any_Render_Device to bool (same uchar-temp idiom).
// Dedicated TU so no caller inlines any body (Rva007EB810Get precedent).

class DX8Wrapper
{
protected:
	static bool Set_Next_Render_Device();
	static bool Set_Any_Render_Device();
	friend bool Rva00116F50();
	friend bool Rva00116F00();
};

// 0x00DEC408 is the render window handle (defined in WW3D_Init_Bfme.cpp).
extern void *g_WW3D_Hwnd;

// ?Rva00116F50@@YA_NXZ
bool Rva00116F50(void)
{
	unsigned char ok = DX8Wrapper::Set_Next_Render_Device();
	return ok;
}

// ?Rva00116F60Get@@YAHXZ
int Rva00116F60Get(void)
{
	return (int)g_WW3D_Hwnd;
}

// ?Rva00116F00@@YA_NXZ
bool Rva00116F00(void)
{
	unsigned char ok = DX8Wrapper::Set_Any_Render_Device();
	return ok;
}
