// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
// Reconstruction of the 78B frameless dispatcher at 0x00318ABB: sync the
// Sunbeam field-parse globals, run the SunbeamObject FieldParse into the
// second global through the rowed INI::initFromINI, mirror the globals
// back unless the INI's +0x08 kind is 2 or 4, then tail-jump the
// 0x00A01CEC global's slot 14 when present. All names but INI,
// initFromINI and AsciiString are address-derived; the addresses, the
// literal and the call shapes are target facts.
#include "ascii_string.h"

class INI;
struct FieldParse
{
    const char *token;
    void (*parse)(INI *, void *, void *, const void *);
    const void *userData;
    int offset;
};

class INI
{
public:
	void initFromINI(void *chunk, const FieldParse *parse);
	static void parseAsciiString(INI *, void *, void *, const void *);
	unsigned char m_pad[8];
	int m_08;
};

// Bind to the existing data-ledger owner; keep the retail access view local.
extern unsigned int g_Va00E01CF0;
// Bind to the existing data-ledger owner; keep the retail access view local.
extern unsigned int g_Va00E01CF4;
// Complete native table C0C78C..C0C7AC: the named string field and terminator.
// The dispatcher and table establish this shared string role; no object layout
// beyond the parsed offset zero is inferred from its address-derived name.
extern const FieldParse TheRva00318ABBSunbeam[] =
{
    {"SunbeamObject", INI::parseAsciiString, 0, 0},
    {0, 0, 0, 0}
};

class Rva00318ABBTarget
{
public:
	virtual void t00() = 0; virtual void t01() = 0;
	virtual void t02() = 0; virtual void t03() = 0;
	virtual void t04() = 0; virtual void t05() = 0;
	virtual void t06() = 0; virtual void t07() = 0;
	virtual void t08() = 0; virtual void t09() = 0;
	virtual void t10() = 0; virtual void t11() = 0;
	virtual void t12() = 0; virtual void t13() = 0;
	virtual void t14() = 0;
};

class CloudBreakEffectManager;
extern CloudBreakEffectManager *TheCloudBreakEffectManager;

void rva00318ABB(INI *ini)
{
	(*(AsciiString *)&g_Va00E01CF4) = (*(AsciiString *)&g_Va00E01CF0);
	ini->initFromINI(&(*(AsciiString *)&g_Va00E01CF4), TheRva00318ABBSunbeam);
	if (ini->m_08 != 2 && ini->m_08 != 4)
		(*(AsciiString *)&g_Va00E01CF0) = (*(AsciiString *)&g_Va00E01CF4);
	if (TheCloudBreakEffectManager != 0)
		return ((Rva00318ABBTarget *)TheCloudBreakEffectManager)->t14();
}

class Rva00318A87
{
public:
	void rva00318A87();
private:
	char m_pad[0x0C];
	AsciiString m_0C;
};

void Rva00318A87::rva00318A87()
{
	m_0C = *(AsciiString *)&g_Va00E01CF4;
}


// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?TheRva00318ABBSunbeam@@3UFieldParse@@B=?TheRva00318ABBSunbeam@@3QBUFieldParse@@B")
