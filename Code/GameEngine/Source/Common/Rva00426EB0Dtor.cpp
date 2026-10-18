// cl: /O1 /EHs /DNDEBUG /MD
//
// ??1Rva00426EB0@@UAE@XZ, retail 0x00426EB0, 48 bytes.
// ModuleData-style dtor: EH_prolog with state 0, calls rowed member dtor
// ??1Rva00426B73@@QAE@XZ at +4, then restores Snapshot vtable g_00BBB554.
// Evidence: vtable store 0xBBB554 at [this] via g_00BBB554; call to rowed
// 0x00426B73; EH_prolog via 0x00629188; caller 0x00426E94 deleting dtor;
// shape follows Rva0026AF86Dtor plus PillageModuleDataDtor TU-local Snapshot.
// The rowed Snapshot destructor and its table share the canonical symbol.
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

struct Rva00426B73
{
	~Rva00426B73();
};

class __declspec(novtable) Rva00426EB0 : public Snapshot
{
public:
	virtual ~Rva00426EB0();
private:
	Rva00426B73 m_04;
};

Rva00426EB0::~Rva00426EB0()
{
}
