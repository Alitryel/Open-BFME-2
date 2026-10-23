// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /MD /EHsc
// ??0TerrainRoadCollection@@QAE@XZ @0x002DAC34 36B: ctor via rowed baseConstruct 0x001B4E63 plus lists at +0xC/+0x10 plus the shared TerrainRoadCollection ID counter.
// Evidence: vtable 0x00803D64 store; callees baseConstruct 0x001B4E63; ID counter 0x009FF088; caller 0x0022E874; neighbour dtor 0x002DAC58.
// The constructor initializes the same ID counter that newRoad and newBridge
// increment. The static member spelling follows ZH TerrainRoadCollection.

// BFME2 SubsystemInterface (12-byte base, 14-slot vtable 0x00BD77A0; ctor
// 0x001B4E63 / dtor 0x001B4E74 rowed as ??0/??1SubsystemInterface) from the
// subsystem shim, so this unit emits the retail 14-slot vtable 0x00C03D64.
typedef bool Bool;
#include "subsystem_interface.h"

struct Rva002DAC58Node;

class TerrainRoadCollection : public SubsystemInterface
{
public:
	TerrainRoadCollection();
	virtual ~TerrainRoadCollection();
	// Retail vtable 0x00C03D64 slots 1/9/10 (init/reset/update) are the folded
	// empty body at 0x000B3FD0.
	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}
private:
	static unsigned int m_idCounter;
	Rva002DAC58Node *m_list0C;
	Rva002DAC58Node *m_list10;
};

TerrainRoadCollection::TerrainRoadCollection()
	: m_list0C(0)
	, m_list10(0)
{
	TerrainRoadCollection::m_idCounter = 1;
}
