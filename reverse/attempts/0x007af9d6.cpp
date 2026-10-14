// ?rva007AF9D6@Rva007AF9D6SplineEffectTable@@SAXXZ
// partial score=0.7 date=2026-10-14
// cl: /O2 /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD
// ?rva007AF9D6@Rva007AF9D6SplineEffectTable@@SAXXZ, retail 0x007AF9D6 (571B):
// a static initializer that fills the ten 16-byte FieldParse entries at
// VA 0x00DC1518 (nine and the null terminator). Each entry names one of the
// file-scope effect-name AsciiStrings and parses it with the rowed
// SplineEffectParseINIBlock (0x004E3F48), passing the same name text as the
// user data: { name.str(), SplineEffectParseINIBlock, name.str(), 0 }. The
// names, in table order, are the strings at E02E70 ("ConqueredEffectEvenglow"),
// E02E74 ("ConqueredEffectFlareup"), E02E68, E02E6C, E02E64, E02E78, E02E7C,
// E02E80 and E02E84. Retail tests each string pointer twice, once per str().
// The table's own name is not recovered; the function is written as an
// explicit address-named initializer, like the other static-init strips.
#include "ascii_string.h"

class INI;
void SplineEffectParseINIBlock(INI *ini, void *instance, void *store, const char *name);

struct Rva007AF9D6FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const char *name);
	const void *userData;
	int offset;
};

extern Rva007AF9D6FieldParse g_rva007AF9D6Table[10];
extern unsigned g_Va00E02E70;
extern unsigned g_Va00E02E74;
extern AsciiString g_Rva00E02E68;
extern AsciiString g_Rva00E02E6C;
extern AsciiString g_Rva00E02E64;
extern AsciiString g_Rva00E02E78;
extern AsciiString g_Rva00E02E7C;
extern AsciiString g_Rva00E02E80;
extern AsciiString g_Rva00E02E84;

struct Rva007AF9D6SplineEffectTable
{
	static void rva007AF9D6();
};

static __forceinline void setEntry(Rva007AF9D6FieldParse &entry, const AsciiString &name)
{
	entry.token = name.str();
	entry.parse = SplineEffectParseINIBlock;
	entry.userData = name.str();
	entry.offset = 0;
}

void Rva007AF9D6SplineEffectTable::rva007AF9D6()
{
	setEntry(g_rva007AF9D6Table[0], *(const AsciiString *)&g_Va00E02E70);
	setEntry(g_rva007AF9D6Table[1], *(const AsciiString *)&g_Va00E02E74);
	setEntry(g_rva007AF9D6Table[2], g_Rva00E02E68);
	setEntry(g_rva007AF9D6Table[3], g_Rva00E02E6C);
	setEntry(g_rva007AF9D6Table[4], g_Rva00E02E64);
	setEntry(g_rva007AF9D6Table[5], g_Rva00E02E78);
	setEntry(g_rva007AF9D6Table[6], g_Rva00E02E7C);
	setEntry(g_rva007AF9D6Table[7], g_Rva00E02E80);
	setEntry(g_rva007AF9D6Table[8], g_Rva00E02E84);
	g_rva007AF9D6Table[9].token = 0;
	g_rva007AF9D6Table[9].parse = 0;
	g_rva007AF9D6Table[9].userData = 0;
	g_rva007AF9D6Table[9].offset = 0;
}
