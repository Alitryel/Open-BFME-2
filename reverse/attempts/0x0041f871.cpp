// ?parseArmyDefinition@ArmyDefinitionManager@@SAXPAVINI@@@Z
// partial score=0.96 date=2026-10-17
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#include <vector>
namespace _STL {
}
class AsciiString
{
public:
	char _d[4];
};
class INI
{
public:
	void initFromINI(void* p, struct FieldParse const* f);
};
struct FieldParse {};
class NameKeyGenerator
{
public:
	int nameToKey(AsciiString const& s);
};
class ArmyDefinition
{
public:
	ArmyDefinition();
	~ArmyDefinition();
	void postParse();
	AsciiString m_name;
	char _pad[0xE0 - 4];
};
class ObjectLookupMap
{
public:
	void** findSlot(int* k);
};
namespace _STL {
template<class _K, class _V> struct _MapStub
{
	struct _Ht { void* _M_find(int const& k); };
	_Ht _m;
};
}

class ArmyDefinitionManager
{
public:
	static void __cdecl parseArmyDefinition(INI* ini);
};

void __cdecl ArmyDefinitionManager::parseArmyDefinition(INI* ini)
{
	ArmyDefinition* def = 0;
	ArmyDefinition* tmp;
	{
		void* mem = operator new(0xE0);
		tmp = (ArmyDefinition*)mem;
		if (tmp) {
			def = tmp;
			def->ArmyDefinition::ArmyDefinition();
		} else {
			def = tmp;
		}
	}
	ini->initFromINI(def, (FieldParse const*)0xC3B5E8);
	NameKeyGenerator* gen = *(NameKeyGenerator* volatile*)0xDF36A4;
	int key = gen->nameToKey(def->m_name);
	ObjectLookupMap* map = *(ObjectLookupMap* volatile*)0x00E0312C;
	map = (ObjectLookupMap*)((char*)map + 12);
	_STL::_MapStub<int,int>::_Ht* ht = (_STL::_MapStub<int,int>::_Ht*)map;
	int kcopy = key;
	int* kptr = &kcopy;
	void* found;
	{
		found = ht->_M_find(kcopy);
	}
	if (!found) {
		void** slot = map->findSlot(kptr);
		*slot = def;
		def->postParse();
	} else {
		if (def) {
			def->~ArmyDefinition();
			operator delete(def);
		}
	}
}
