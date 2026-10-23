// cl: /EHs-c-
//
// ??0Rva00563FE1@@QAE@I@Z, retail 0x00563FE1, 32 bytes.
//
// Single-argument __thiscall constructor: parks the incoming dword at +0x04,
// then writes the shared secondary vftable 0x00C1C780 at +0x08, the primary
// vftable 0x00C1D2C0 at +0x00, and the shared secondary again at +0x08.
//
// BFME1 near-miss donor is reference/open-bfme-1/.../T4VtableSetCtors.cpp,
// Rva005EE820 at 0x005EE820 (32 bytes, same store sequence through the BFME1
// tables 0x0110F978/0x01112B28/0x01112B24, but `ret 8`: its second parameter
// is never read). BFME2 dropped that unread parameter, so the callee pops
// four bytes instead of eight; the remaining stores are unchanged. Both
// +0x08 stores hold the same table here, spelled as two volatile stores so
// the compiler may neither merge nor drop them, exactly as the donor models
// the inlined-base-then-derived sequence.
//
// Tables use address-derived aliases, preserving uncertainty about the
// caller's class identity while resolving real linker definitions.
// 0x00C1C780 is independently witnessed as a shared secondary vftable: the
// Die-family intermediate base 0x45CEBD installs it alongside 0xC41E78 and
// 0xC4A650, and the FXParticleSystem velocity template row 0x3A73F8 lists it
// among its subobject vtables. No caller names this body, so the class keeps
// its address-derived name.

// Address-named alias: retail RVA 0x0081C780 is one __purecall slot.
// The emitted donor table is independently checked as four bytes with
// one __purecall relocation, whose matched body is at RVA 0x0003B810.
// This establishes table contents; it assigns no donor class to the caller.
extern "C" const void *const vtbl_00C1C780[];
#pragma comment(linker, "/alternatename:_vtbl_00C1C780=??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")

extern "C" const void *const vtbl_00C1D2C0[];  // ??_7Rva005EA430@@6BV3Vt01111D90@@@
#pragma comment(linker, "/alternatename:_vtbl_00C1D2C0=??_7Rva005EA430@@6BV3Vt01111D90@@@")

class Rva00563FE1
{
public:
	Rva00563FE1( unsigned int a );
private:
	unsigned char m_storage[ 0x0c ];
};

// Both table names alias the independently checked four-byte retail table.
// Keeping separate compiler names preserves the two immediate stores while
// the linker resolves them to the same address; no zero-filled anchor remains.
extern "C" const void *const vtbl_00C1C780_again[];
#pragma comment(linker, "/alternatename:_vtbl_00C1C780_again=??_7?$CategoryModuleInfo@$00@FXParticleSystem@@6B@")

Rva00563FE1::Rva00563FE1( unsigned int a )
{
	volatile unsigned int *slots = (unsigned int *)this;
	slots[ 1 ] = a;
	slots[ 2 ] = ((unsigned int)vtbl_00C1C780);
	slots[ 0 ] = ((unsigned int)vtbl_00C1D2C0);
	slots[ 2 ] = (unsigned int)vtbl_00C1C780_again;
}
