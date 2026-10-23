// cl: /MD
// ?rva0027D3CB@Rva0027D3CB@@QAE_NH@Z, retail 0x0027D3CB, 14 bytes.
// WB 0x00C483B0 is a one-argument member forwarding through TheTerrainVisual.
// Native caller 0x005450D3 passes ECX, pushes one word, and tests AL.
// W3DTerrainVisual primary vtable VA 0x00BC80A0 slot 32 contains 0x00091F95:
// that verified provider returns false or forwards the word, and ends RET 4.
// The old void/four-argument declaration confused this with TerrainLogic's
// unrelated water-height slot. The receiver is unused in this forwarding body.
extern class G00DFF080Obj *TheTerrainVisual;

class Rva009FF080Manager0027D3CB
{
public:
	virtual void _slot00();
	virtual void _slot01();
	virtual void _slot02();
	virtual void _slot03();
	virtual void _slot04();
	virtual void _slot05();
	virtual void _slot06();
	virtual void _slot07();
	virtual void _slot08();
	virtual void _slot09();
	virtual void _slot10();
	virtual void _slot11();
	virtual void _slot12();
	virtual void _slot13();
	virtual void _slot14();
	virtual void _slot15();
	virtual void _slot16();
	virtual void _slot17();
	virtual void _slot18();
	virtual void _slot19();
	virtual void _slot20();
	virtual void _slot21();
	virtual void _slot22();
	virtual void _slot23();
	virtual void _slot24();
	virtual void _slot25();
	virtual void _slot26();
	virtual void _slot27();
	virtual void _slot28();
	virtual void _slot29(int a, int b);
	virtual void _slot30();
	virtual void _slot31();
	virtual bool _slot32(int handle);
};

#define TheRva009FF080Manager0027D3CB (*(Rva009FF080Manager0027D3CB **)&TheTerrainVisual)

class Rva0027D3CB
{
public:
	bool rva0027D3CB(int handle);
};

bool Rva0027D3CB::rva0027D3CB(int handle)
{
	return TheRva009FF080Manager0027D3CB->_slot32(handle);
}

//
// ?rva0027D347@Rva0027D347@@QAEXPAURva0027D347Arg@@H@Z retail 0x0027D347 24 bytes.
// Thiscall with (Arg*,int-dummy-ret8) via same global to slot29 (0x74)
// with (Arg+0xc, this+0). Caller 0x27E768. Same TU/flags as thunk above.
struct Rva0027D347Arg
{
	char m_pad00[0xc];
	int m_field0C;
};

class Rva0027D347
{
public:
	void rva0027D347(Rva0027D347Arg *a, int dummy);
private:
	int m_00;
};

void Rva0027D347::rva0027D347(Rva0027D347Arg *a, int dummy)
{
	TheRva009FF080Manager0027D3CB->_slot29(a->m_field0C, m_00);
}
