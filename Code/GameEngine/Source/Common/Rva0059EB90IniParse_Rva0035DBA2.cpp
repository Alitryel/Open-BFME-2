// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common

struct FieldParse;

void *__cdecl operator new(unsigned int);
void __cdecl operator delete(void *);

class Rva0035DA01
{
public:
	Rva0035DA01();

private:
	unsigned char m_pad[0x40];
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *fieldParse);
};

struct Gen_00489270
{
	void m(int value);
};

// The rowed 35DB3F constructor initializes this same 0x40-byte allocation.
// Native parser and buildFieldParse4BB0BB both pass the empty C6BB18 table.
extern const int g_emptyFieldParseTable[4];

// ?rva0059EB90@@YAXPAVINI@@PAUGen_00489270@@@Z
void rva0059EB90(INI *ini, Gen_00489270 *store)
{
	Rva0035DA01 *item = new Rva0035DA01;
	ini->initFromINI(item, reinterpret_cast<const FieldParse *>(g_emptyFieldParseTable));
	store->m((int)item);
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:??0BfmeC1137@@QAE@XZ=??0Rva0035DA01@@QAE@XZ")
#pragma comment(linker, "/alternatename:?TheRva0059EB90FieldParse@@3QBUFieldParse@@B=?g_emptyFieldParseTable@@3QBHB")
