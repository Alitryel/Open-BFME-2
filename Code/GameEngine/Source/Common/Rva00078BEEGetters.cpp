// cl: /GX-
// ?Rva00078BEEGet@@YAHXZ @ 0x00078BEE (6B): global dword getter reading
// 0x001FDEB4 (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp (same shape).
// First of an adjacent pair (0x78BEE/F4); dedicated TU so no caller
// inlines the load (Rva007EB810Get precedent).

extern int TheW3DHordeModelDrawCount;

int Rva00078BEEGet(void)
{
	return TheW3DHordeModelDrawCount;
}

// ?Rva00078BF4Get@@YAHXZ @ 0x00078BF4 (6B): same shape over 0x001FDEB0.

extern int g_Va001FDEB0;
// g_Va001FDEB0: matched references place it at VA 0xde1fb0 (zero-filled .bss).
int g_Va001FDEB0;

int Rva00078BF4Get(void)
{
	return g_Va001FDEB0;
}
