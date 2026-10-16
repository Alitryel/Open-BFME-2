// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX
//
// Ported from Open-BFME-1 GameEngine/Source/Common/Rva00372BA0ConditionalDispatcher.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?Rva00372BA0ConditionalDispatcher@@YAXPAX0_N@Z 0x00397CEB (31B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

class Object;

// 0x00396C43 and 0x00396E4A are the rowed enter/remove pair of one owner.
class Rva00396E4A
{
public:
	void rva00396C43(Object *obj);
	void rva00396E4A(Object *obj);
};

void Rva00372BA0ConditionalDispatcher(void *first, void *second, bool enabled)
{
	void *firstValue = first;
	Rva00396E4A *secondValue = (Rva00396E4A *)second;
	if (secondValue)
	{
		if (enabled)
		{
			secondValue->rva00396C43((Object *)firstValue);
			return;
		}
		secondValue->rva00396E4A((Object *)firstValue);
	}
}
