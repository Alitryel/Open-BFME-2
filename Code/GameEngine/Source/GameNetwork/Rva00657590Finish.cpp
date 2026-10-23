// cl: /O2
//
// ?m@T_007ea5e0@@QAEXXZ @0x00657590 (87B): FESL servicehub eight-slot notify.
//
// Gets the service singleton via 0x00656B60, calls virtual slots +0xC then +0x8
// (keeping the +0x8 result as the notify value), notifies every non-null owner
// in the eight slots at +0x10 through the slot's virtual slot 0, calls +0x10,
// then tail-jumps to 0x00665310 when the +0x8 status word lacks bit 2.
//
// The slot array is typed `SlotObj *` rather than `void *`: that is what makes
// the object pointer land in ebp and the notify value in ebx and emits retail's
// extra mov ecx,eax in the loop (evidenced by the exact 87B body). Evidence:
// caller 0x006669F3 names the callee, and the same eight-slot owner table is
// spelled by the matched Rva007EAServiceList add/remove at 0x00657500/0x00657540.
int __cdecl Rva00656B60Get();
void __cdecl Rva007F8C90();

struct GetObj
{
	virtual void v0();
	virtual void v1();
	virtual int v2();
	virtual void v3();
	virtual void v4();
};

struct SlotObj
{
	virtual void f(int v);
};

class T_007ea5e0
{
public:
	void m();

private:
	char m_pad[8];
	unsigned char m_08;
	char m_pad09[7];
	SlotObj *m_slots[8];
};

void T_007ea5e0::m()
{
	((GetObj *)Rva00656B60Get())->v3();
	int v = ((GetObj *)Rva00656B60Get())->v2();
	for (int i = 0; i < 8; ++i) {
		if (m_slots[i] != 0)
			m_slots[i]->f(v);
	}
	((GetObj *)Rva00656B60Get())->v4();
	if ((m_08 & 2) != 0)
		return;
	Rva007F8C90();
}
