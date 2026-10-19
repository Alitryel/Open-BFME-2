// cl: /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1InstantDeathBehaviorModuleData@@UAE@XZ @0x0045D28D 105B via 3 inline vector frees plus rowed vector dtor, novtable restores g_00BBB554
#include <vector>

// Retail's own table symbol: an address-named alias (g_00BBB554) emits identical
// bytes but relocates to a different name, so the census kept this unit's copy
// as a loser against the row owner's.
extern "C" const void *const __identifier("??_7Snapshot@@6B@")[];

class Rva0045D28DBase
{
public:
	virtual ~Rva0045D28DBase() { *(const void *const **)this = __identifier("??_7Snapshot@@6B@"); }
	virtual void DestroyDieModuleData_virt00();
private:
	unsigned char m_pad[0x38 - 4];
};

struct Rva0045D137
{
	void *m_start;
	void *m_finish;
	void *m_endOfStorage;
	~Rva0045D137();
};

class __declspec(novtable) InstantDeathBehaviorModuleData : public Rva0045D28DBase
{
public:
	virtual ~InstantDeathBehaviorModuleData();
private:
	_STL::vector<int> m_v38;
	_STL::vector<int> m_v44;
	_STL::vector<int> m_v50;
	Rva0045D137 m_v5C;
};

InstantDeathBehaviorModuleData::~InstantDeathBehaviorModuleData()
{
}
