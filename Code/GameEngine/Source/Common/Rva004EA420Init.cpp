// cl: /ICode/GameEngine/Source /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /O1 /G7 /arch:SSE /DNDEBUG /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Native 0x004EA420..0x004EA4E4 (197B). If the global pointer vector at
// 0x00E04494 is empty and Rva004EA2C5Get()>0, reserves it, walks GameLogic
// objects (getFirstObject 0x0023CAD2) and for each whose +4 record has an
// AsciiString at +0x64 equal to the global AsciiString 0x00E04490
// (StringBase compare 0x000069D6) creates an Rva00596F18 (rowed ctor
// 0x00596EEF), sets its Coord3D from object+0x38 (rowed 0x00573A00), copies
// object+0x44 to item+0x3C and push_backs it (rowed 0x004DFCB0); next at
// object+0x8C.
//
// Codegen: the new item is held in a pointer-to-const-ModuleData variable (the
// address passed to push_back takes it by const reference); its home is
// written right after the allocation, before the Coord3D call, like retail.
// A plain 'Rva00596F18 *item' local gets its home store sunk to the push_back.
#include <vector>
#include "ascii_string.h"
#include "Coord3D.h"

#include "Common/GameLogicObjectLookupView.h"
// Suppress this TU's non-retail copy of ?_M_clear@?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@IAEXXZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class ModuleData;
namespace _STL { template <> void vector<const ModuleData *, allocator<const ModuleData *> >::_M_clear(); }
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}
extern GameLogic *TheGameLogic;

int Rva004EA2C5Get();

class ModuleData;

class Rva00573A00
{
public:
	void rva00573A00(const Coord3D *pos);
};

class Rva00596F18 : public Rva00573A00
{
public:
	Rva00596F18(void *arg);
private:
	char m_pad[0x74];
};

extern _STL::vector<const ModuleData *> g_00E04494;
extern AsciiString g_00E04490;

class Rva004EA3B8
{
public:
	void rva004EA420();
};

void Rva004EA3B8::rva004EA420()
{
	if (!g_00E04494.empty())
		return;
	int count = Rva004EA2C5Get();
	if (count <= 0)
		return;
	g_00E04494.reserve(count);
	int index = 0;
	Object *obj = TheGameLogic->getFirstObject();
	if (!obj)
		return;
	do
	{
		char *record = *(char **)((char *)obj + 4);
		if (((const StringBase<char> *)(record + 0x64))->compare(*(const StringBase<char> *)&g_00E04490) == 0)
		{
			const ModuleData *entry = (const ModuleData *)new Rva00596F18((void *)index++);
			((Rva00596F18 *)entry)->rva00573A00((const Coord3D *)((char *)obj + 0x38));
			*(int *)((char *)entry + 0x3C) = *(int *)((char *)obj + 0x44);
			g_00E04494.push_back(entry);
		}
		obj = *(Object **)((char *)obj + 0x8C);
	} while (obj);
}
