// cl: /GX-
// ?rva001100A6@Rva001100A6@@QAIXPAX@Z @0x001100A6 31B via virtual-slot12 clearer
// Cursor ABI: retail render 0xA9F98 passes renderer in ECX and cursor in EDX
// at +0x16F (line), +0x2EE and +0x58B (triangle). The body ignores the cursor;
// keep it in the signature so callers reproduce that argument setup.
// evidence: retail tests [this+D0] then calls [[ptr+1C]+30] then clears [this+DC]; callers 0x000A9F98 x3
class Slot12
{
public:
	virtual void __stdcall v00();
	virtual void __stdcall v01();
	virtual void __stdcall v02();
	virtual void __stdcall v03();
	virtual void __stdcall v04();
	virtual void __stdcall v05();
	virtual void __stdcall v06();
	virtual void __stdcall v07();
	virtual void __stdcall v08();
	virtual void __stdcall v09();
	virtual void __stdcall v10();
	virtual void __stdcall v11();
	virtual void __stdcall v12();
};
struct Mid
{
	char pad[0x1C];
	Slot12 *v;
};
class Rva001100A6
{
public:
	void __fastcall rva001100A6(void *vertices);
private:
	char m_pad[0xD0];
	Mid *m_mid;
	char m_pad2[8];
	int m_cleared;
};
void __fastcall Rva001100A6::rva001100A6(void *vertices)
{
	if (m_mid != 0)
	{
		m_mid->v->v12();
		m_cleared = 0;
	}
}

class Rva001100C5
{
public:
	void __fastcall rva001100C5(void *lines);
};

void __fastcall Rva001100C5::rva001100C5(void *lines)
{
	((Rva001100A6 *)this)->rva001100A6(lines);
}

