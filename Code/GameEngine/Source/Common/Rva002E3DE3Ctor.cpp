// cl: /MD /EHsc
//
// ??0Rva002E3DE3@@QAE@HH@Z retail 0x002E3DE3 71B.
// Evidence: forwards the list head at 0x00DFF0B8 (the global the rowed
// Rva002E3714Unlink walks) and both stack arguments to the base ctor at
// 0x002E3D7B, enters unwind state 0, installs vtable 0x00C04C04, stores the
// same head at +0x10 and calls the rowed no-argument Rva002E373CClear at
// 0x002E373C, returning with ret 8.
//
// U-twin: the base at 0x002E3D7B is the rowed TriggerAreas parser binding
// ??0Rva002E3D7B@@QAE@PAXPAVBfmeParserRegistryVE@@PBVAsciiString@@@Z, defined
// in Rva000AEFAA.cpp; the caller must call it by the ledger name, so the base
// ctor and its dtor (whose call the ctor's unwind funclet emits) are declared
// with the ledger signature. The derived dtor is left implicit.

class AsciiString;
class BfmeParserRegistryVE;
struct Rva002E36D5Node;
extern Rva002E36D5Node *g_00DFF0B8;

void Rva002E373CClear();

class Rva002E3D7B
{
public:
	Rva002E3D7B(void *owner, BfmeParserRegistryVE *registry, const AsciiString *parentLabel);
	virtual ~Rva002E3D7B();
private:
	char m_pad04[0xC];
};

class Rva002E3DE3 : public Rva002E3D7B
{
public:
	Rva002E3DE3(int first, int second);
private:
	Rva002E36D5Node **m_head10;
};

Rva002E3DE3::Rva002E3DE3(int first, int second)
	: Rva002E3D7B((void *)&g_00DFF0B8, (BfmeParserRegistryVE *)first, (const AsciiString *)second),
	m_head10(&g_00DFF0B8)
{
	Rva002E373CClear();
}
