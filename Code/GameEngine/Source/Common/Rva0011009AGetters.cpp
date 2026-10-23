// cl: /GX-
// ?Rva0011009AGet@@YAHXZ @ 0x0011009A (6B): global dword getter reading
// 0x00DB5FD4 (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp (same shape).
// First of an adjacent pair (0x11009A/A0, themselves preceded by an A0-form
// global byte getter); dedicated TU so no caller inlines the load
// (Rva007EB810Get precedent).

extern int BfmeRenderWidth;

int Rva0011009AGet(void)
{
	return BfmeRenderWidth;
}

// ?Rva001100A0Get@@YAHXZ @ 0x001100A0 (6B): same shape over 0x00DB5FD8.

extern int BfmeRenderHeight;

int Rva001100A0Get(void)
{
	return BfmeRenderHeight;
}
