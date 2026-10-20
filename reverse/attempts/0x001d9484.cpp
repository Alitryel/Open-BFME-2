// ?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z
// partial score=0.99 date=2026-10-20
// cl: /Ireference/shims/bfmealloc /I. /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// ?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z
// partial score=0.921 date=2026-10-17
// ?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z
// partial score=0.9402902722801967 date=2026-10-13
// ?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z
// partial score=0.9402902722801967 date=2026-10-13
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC
// stlport
// WB ABCAB0 names ArmorStore::parseArmorDefinition; native1D9484..1D9611
// supplies override/new/template layout and the exact four-entry field table.
// ZH and BFME1 ba7ddda7 Armor.cpp support INI/Armor identity; BF1 donor place0.
// The inline volatile load-type getter restores the native single load/test,
// complete 397-byte extent and 126-instruction stream. Remaining homes differ:
// key -20 versus -10; conversion bitmap -14 versus -18; heap temps -18/-10
// versus -14/-1C. Actual pointer-container operator[]63 and push_back49 still
// need complete byte-and-relocation fold proof. No trial bindings are pins.
// claude-opus-5-5 2026-10-20: rts::hash defined inline and no iterator padding or volatile
// getter; only the operator[] call (fold pin to 0x0041F4E5) is unresolved. See
// reverse/attempt_support/0x001d9484_20261020_visible_hash.md.
// ArmorStore::parseArmorDefinition (retail 0x001D9484, 397 bytes), right after the store's
// slot-5 reload 0x001D93CE; WB ABCAB0 names it. The map at +0x0C and the pending vector at
// +0x2C are the containers ArmorStoreReload.cpp drains.

#include <hash_map>
#include <vector>
#include "ascii_string.h"

#define NULL 0

enum NameKeyType
{
	NAMEKEY_INVALID = 0,
	NAMEKEY_MAX = 1 << 23,
	FORCE_NAMEKEYTYPE_LONG = 0x7fffffff
};

namespace rts
{
// Inline: retail's _M_find 0x002888D4 reads the key straight into the bucket divide.
template <class T> struct hash
{
	size_t operator()(const T &value) const { return (size_t)value; }
};
}

class INI;

struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	int getLoadType() const { return m_loadType; }

private:
	char m_pad00[8];
	int m_loadType; // +0x08
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class ModuleData;

// BFME2 layout as ArmorTemplateParse.cpp measures it (0x7C bytes).
class ArmorTemplate
{
public:
	ArmorTemplate(const AsciiString &name);
	~ArmorTemplate() {}
	static void parseDamageScalar(INI *ini, void *instance, void *store, const void *userData);
	static void parseArmorCoefficients(INI *ini, void *instance, void *store, const void *userData);

	float m_head; // +0x00
	float m_damageCoefficient[27]; // +0x04
	float m_damageScalar; // +0x70
	int m_flag; // +0x74
	AsciiString m_name; // +0x78
};

typedef _STL::hash_map<NameKeyType, ArmorTemplate *, rts::hash<NameKeyType>, _STL::equal_to<NameKeyType> > ArmorTemplateMap;

class ArmorStore
{
public:
	static void parseArmorDefinition(INI *ini);

private:
	char m_pad00[0x0C];
	ArmorTemplateMap m_armorTemplates; // +0x0C
	_STL::vector<ArmorTemplate *> m_retired; // +0x20
	_STL::vector<ArmorTemplate *> m_pending; // +0x2C
};
extern ArmorStore *TheArmorStore;

// ?parseArmorDefinition@ArmorStore@@SAXPAVINI@@@Z
// Load type 5 replaces a known armor with a new pending template; any other
// repeat parses into a discarded local.
/*static*/ void ArmorStore::parseArmorDefinition(INI *ini)
{
	static const FieldParse myFieldParse[] =
	{
		{ "DamageScalar", ArmorTemplate::parseDamageScalar, NULL, 0 },
		{ "FlankedPenalty", INI::parsePercentToReal, NULL, 0 },
		{ "Armor", ArmorTemplate::parseArmorCoefficients, NULL, 0 },
		{ NULL, NULL, NULL, 0 }
	};

	const char *c = ini->getNextToken(NULL);
	NameKeyType key = TheNameKeyGenerator->nameToKey(c);
	ArmorTemplate *armorTmpl;
	ArmorTemplateMap::const_iterator it = TheArmorStore->m_armorTemplates.find(key);
	if (it != TheArmorStore->m_armorTemplates.end())
	{
		armorTmpl = it->second;
		if (ini->getLoadType() == 5)
		{
			armorTmpl->m_flag = 1;
			armorTmpl = new ArmorTemplate(c);
			armorTmpl->m_flag = 0;
			// Pointer-vector push_back through the rowed four-byte provider 0x004DFCB0.
			reinterpret_cast<_STL::vector<const ModuleData *> &>(TheArmorStore->m_pending).push_back(reinterpret_cast<const ModuleData * const &>(armorTmpl));
		}
		else
		{
			ArmorTemplate temp(c);
			ini->initFromINI(&temp, myFieldParse);
			return;
		}
	}
	else
	{
		armorTmpl = new ArmorTemplate(c);
		TheArmorStore->m_armorTemplates[key] = armorTmpl;
	}
	ini->initFromINI(armorTmpl, myFieldParse);
}
