// cl: /DNDEBUG /MD /EHsc
// ?AddObjectToPathfindMap@Pathfinder@@QAEXPAVObject@@@Z @0x002E7178
// ?RemoveObjectFromPathfindMap@Pathfinder@@QAEXPAVObject@@@Z @0x002E718A 17B: adjacent sibling
// Shard TU: friend_notifyOfNewMapBoundary lives in
// Object_friendNotifyOfNewMapBoundary.cpp under /Oy- frames; this frameless
// leaf needs no frame so it lives here. Second body abuts first and forwards
// to same helper with 0 0 0 vs 1 0 0; same class proven by adjacency and shape.

class Object;

class Rva0036666B
{
public:
	bool rva0036666B();
};

class Rva00366561
{
public:
	bool rva00366561(int a, int b);
};

class Pathfinder
{
public:
	void AddObjectToPathfindMap(Object *object);
	void RemoveObjectFromPathfindMap(Object *object);
	void RemoveObjectGoalFromPathfindMap(Object *object);
	void RemoveObjectFromPathfindMapKeepingGateFlags(Object *object);
	int AddBridge(int arg);
	void rva00530212(Object *object, bool insert, bool keepGate, bool goal);	// 0x00530212 footprint classifier
private:
	char m_pad00[0x60];
	struct Slot { char bytes[0x40]; };
	Slot m_slots[16];
};

// ?AddObjectToPathfindMap@Pathfinder@@QAEXPAVObject@@@Z
void Pathfinder::AddObjectToPathfindMap(Object *object)
{
	rva00530212(object, true, false, false);
}

void Pathfinder::RemoveObjectFromPathfindMap(Object *object)
{
	rva00530212(object, false, false, false);
}

void Pathfinder::RemoveObjectGoalFromPathfindMap(Object *object)
{
	rva00530212(object, false, false, true);
}

void Pathfinder::RemoveObjectFromPathfindMapKeepingGateFlags(Object *object)
{
	rva00530212(object, false, true, false);
}

// ?AddBridge@Pathfinder@@QAEHH@Z @0x002E71BF 70B
// Evidence: unlock lane; callees rowed 0x0036666B 0x00366561; callers 0x002802E3 0x002812A4; array +0x60 stride 0x40 indices 2..15.
int Pathfinder::AddBridge(int arg)
{
	int i = 2;
	Slot *p = &m_slots[2];
	for (; i <= 0xf; ++i, ++p) {
		if (!((Rva0036666B *)p)->rva0036666B())
			goto second;
	}
	return 1;
second:
	if (!((Rva00366561 *)&m_slots[i])->rva00366561(arg, i))
		return 1;
	return i;
}

// ??0Rva002E7243@@QAE@HH@Z @0x002E7243 30B, RET8, no callers in retail: a
// five-word record built from two words with the remaining three set to -1.
// Retail stores +8 between loading and storing the first argument and the
// last two words after the second: the trailing pair is a member object
// whose own constructor sets both to -1 (cl hoists a constructor's own
// constant stores above its argument stores, but not into a member's
// constructor). Owner and field names are unrecovered (address-derived).
struct Rva002E7243Pair
{
	Rva002E7243Pair() : m_first(-1), m_second(-1) {}
	int m_first;
	int m_second;
};
class Rva002E7243
{
public:
	Rva002E7243(int first, int second);
private:
	int m_00;
	int m_04;
	int m_08;
	Rva002E7243Pair m_pair;
};
Rva002E7243::Rva002E7243(int first, int second) : m_00(first), m_04(second), m_08(-1) {}
