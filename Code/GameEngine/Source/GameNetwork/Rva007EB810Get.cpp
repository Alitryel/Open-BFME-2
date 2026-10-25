// cl: /GX-
// ?Rva007EB810Get@@YAPAURva007EB810Diag@@XZ @ 0x006587A0 (6B): getter reading
// 0x00E09FBC (mov eax,[mem]; ret). Ported from Open-BFME-1
// Code/GameEngine/Source/Common/GlobalDwordGetters.cpp
// (?Rva007EB810Get@@YAHXZ at 0x7EB810, same shape). The diagnostic reporter
// pointer the FESL join fail paths call through (returned as the Diag
// pointer every caller declares, not as the int of the BFME1 port); kept in its own TU so the
// Join callers keep their call-through-edx shape (same-TU definition lets
// MSVC inline the load and breaks them).

struct Rva007EB810Diag;

extern int g_FeslDiagReporter;

Rva007EB810Diag *Rva007EB810Get(void)
{
	return (Rva007EB810Diag *)g_FeslDiagReporter;
}
// ?g_FeslDiagReporter@@3HA: the global at VA 0xe09fbc is ?g_Va0130A5A0@@3PAURva007EB810Diag@@A.
#pragma comment(linker, "/alternatename:?g_FeslDiagReporter@@3HA=?g_Va0130A5A0@@3PAURva007EB810Diag@@A")
