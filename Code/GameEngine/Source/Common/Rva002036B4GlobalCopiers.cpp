// Global-to-member dword copiers: twelve-byte __thiscall members with one shape:
//
//     mov eax,[VA 0x00DFE18C] / mov dword ptr [ecx+<DISP>],eax / ret
//
// One dword is copied from the .data global at VA 0x00DFE18C (RVA 0x005FE18C)
// into a fixed displacement from `this`. Only these two bodies reference that
// global. Identity unrecoverable from 12 bytes, so globals and classes are
// address-derived (g_Va<VA> / Rva<RVA>GlobalCopier, honest names).
// No // cl: line (defaults match the frameless twelve-byte shape).
// ?apply@Rva002036B4GlobalCopier@@QAEXXZ @0x002036B4 12B.
// Copies g_Va00DFE18C to +0x1A104. Callers: calls at 0x002402D8, 0x003BE7D1,
// 0x003C3B6D. No donor; retail-shaped.
// ?apply@Rva002036C0GlobalCopier@@QAEXXZ @0x002036C0 12B.
// Copies g_Va00DFE18C to +0x1A108. Caller: call at 0x003BE8CB. No donor;
// retail-shaped.
extern int g_Va00DFE18C;
// g_Va00DFE18C: matched references place it at VA 0xdfe18c (zero-filled .bss).
int g_Va00DFE18C;

class Rva002036B4GlobalCopier
{
public:
	void apply();
	char m_lead[0x1A104];
	int m_value;
};

void Rva002036B4GlobalCopier::apply()
{
	m_value = g_Va00DFE18C;
}

class Rva002036C0GlobalCopier
{
public:
	void apply();
	char m_lead[0x1A108];
	int m_value;
};

void Rva002036C0GlobalCopier::apply()
{
	m_value = g_Va00DFE18C;
}
