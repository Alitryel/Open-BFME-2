// cl: -DNDEBUG -MD -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/AI
//
// Retail 0x003E6E90: six-argument thiscall wrapper around 0x003DF580.  Forwards
// the six arguments plus &arg6 and a trailing 0, then returns whether arg6 is
// null when the inner call succeeded.

typedef unsigned char Bool;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/AIPathfind.h
enum PathfindLayerEnum { LAYER_INVALID = 0 };
class Object;
class Pathfinder
{
public:
	bool CheckDestination(class Object *obj, int cellX, int cellY, enum PathfindLayerEnum layer, int radius, bool centerInCell, int *result, bool flag);
	Bool bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
		void *a6);
};

// ?bfmeWrapE6E90@Pathfinder@@QAEEPAX00000@Z
Bool Pathfinder::bfmeWrapE6E90(void *a1, void *a2, void *a3, void *a4, void *a5,
	void *a6)
{
	if (!CheckDestination((class Object *)a1, (int)a2, (int)a3, (enum PathfindLayerEnum)(int)a4, (int)a5, *(bool *)&a6, (int *)&a6, false))
		return 0;
	int result = 0;
	void *p = a6;
	return (Bool)(result + (p == 0));
}
