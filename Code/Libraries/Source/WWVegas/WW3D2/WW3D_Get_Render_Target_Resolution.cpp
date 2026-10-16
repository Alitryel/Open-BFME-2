// cl: /DNDEBUG /MD /EHsc /G7
//
// ?Get_Render_Target_Resolution@DX8Wrapper@@KAXAAH00AA_N@Z, retail 0x00121860,
// 195 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2/WW3D_Get_Render_Target_Resolution.cpp):
// SEH frame with a scope guard around the device branch (lock in the
// constructor, release in the destructor). The device virtual at slot 0x30
// fills the mode struct at esp+4 (width at +0x18, height at +0x1C); both
// exits share the bit-depth and windowed globals. BFME2 globals and the
// DX8 lock pair replace the reference names; every global rides a DIR32
// relocation copied from retail.

typedef int Int;
typedef bool Bool;

#define NULL 0

void BFME_DX8_Thread_Lock(void); // retail 0x0011F520
bool BFME_DX8_Thread_Assert(void); // retail 0x00120F50

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

struct BfmeDisplayModeInfo
{
	char m_bfmeHead[0x18];
	Int m_bfmeWidth; // +0x18
	Int m_bfmeHeight; // +0x1C
};

class BfmeRenderDevice
{
public:
	virtual long __stdcall bfmeSlot00(void) = 0;
	virtual long __stdcall bfmeSlot04(void) = 0;
	virtual long __stdcall bfmeSlot08(void) = 0;
	virtual long __stdcall bfmeSlot0C(void) = 0;
	virtual long __stdcall bfmeSlot10(void) = 0;
	virtual long __stdcall bfmeSlot14(void) = 0;
	virtual long __stdcall bfmeSlot18(void) = 0;
	virtual long __stdcall bfmeSlot1C(void) = 0;
	virtual long __stdcall bfmeSlot20(void) = 0;
	virtual long __stdcall bfmeSlot24(void) = 0;
	virtual long __stdcall bfmeSlot28(void) = 0;
	virtual long __stdcall bfmeSlot2C(void) = 0;
	virtual long __stdcall bfmeGetModeInfo(BfmeDisplayModeInfo *info) = 0; // +0x30
};

// ?TheBfmeRenderDevice@@3PAVBfmeRenderDevice@@A: the global at this VA is ?CurrentRenderTarget@DX8Wrapper@@1PAUIDirect3DSurface8@@A; this name is an alias for it.
extern BfmeRenderDevice * TheBfmeRenderDevice;
#pragma comment(linker, "/alternatename:?TheBfmeRenderDevice@@3PAVBfmeRenderDevice@@A=?CurrentRenderTarget@DX8Wrapper@@1PAUIDirect3DSurface8@@A")

extern Int BfmeRenderWidth; // 0x00DB5FD4
extern Int BfmeRenderHeight; // 0x00DB5FD8
extern Int BfmeRenderBitDepth; // 0x00DB5FDC
// ?BfmeRenderBitDepth@@3HA: the global at this VA is ?BitDepth@DX8Wrapper@@1HA; this name is an alias for it.
extern int BfmeRenderBitDepth;
#pragma comment(linker, "/alternatename:?BfmeRenderBitDepth@@3HA=?BitDepth@DX8Wrapper@@1HA")
extern Bool BfmeRenderWindowed; // 0x00DEDA06

// the WW3D forwarder lives at 0x00116FF0 (5B thunk, already claimed);
// this TU recovers the DX8Wrapper body it jumps to (private static, hence
// the KAX mangling, matching the pre-existing pin).
class DX8Wrapper
{
	static void Get_Render_Target_Resolution(Int &width, Int &height, Int &bitDepth, Bool &windowed);
};

// ?Get_Render_Target_Resolution@DX8Wrapper@@KAXAAH00AA_N@Z
// ?DX8Wrapper::Get_Render_Target_Resolution present-unmatched
void DX8Wrapper::Get_Render_Target_Resolution(Int &width, Int &height, Int &bitDepth, Bool &windowed)
{
	if (TheBfmeRenderDevice != NULL)
	{
		BFMEDX8DeviceLock guard;
		BfmeDisplayModeInfo info;

		TheBfmeRenderDevice->bfmeGetModeInfo(&info);

		width = info.m_bfmeWidth;
		height = info.m_bfmeHeight;
		bitDepth = BfmeRenderBitDepth;
		windowed = BfmeRenderWindowed;
	}
	else
	{
		width = BfmeRenderWidth;
		height = BfmeRenderHeight;
		bitDepth = BfmeRenderBitDepth;
		windowed = BfmeRenderWindowed;
	}
}

// ?BfmeRenderWindowed@@3_NA: the global at this VA is ?IsWindowed@DX8Wrapper@@1_NA; this name is an alias for it.
extern bool BfmeRenderWindowed;
#pragma comment(linker, "/alternatename:?BfmeRenderWindowed@@3_NA=?IsWindowed@DX8Wrapper@@1_NA")
#pragma comment(linker, "/alternatename:?g_Va00DEDA06@@3EA=?IsWindowed@DX8Wrapper@@1_NA")
// ?BfmeRenderWindowed@@3_NA: the global at VA 0xdeda06 is ?IsWindowed@DX8Wrapper@@1_NA.
#pragma comment(linker, "/alternatename:?BfmeRenderWindowed@@3_NA=?IsWindowed@DX8Wrapper@@1_NA")
