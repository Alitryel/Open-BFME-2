// cl: /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /GX
// ??1VictorySystem@@UAE@XZ @0x004053C2 79B dtor stores C388D4 plus C388C4 calls rowed 0x00405350 restores BBB554 calls rowed base 0x001B4E74 caller deleting dtor 0x0040559F
struct Rva00405350 { ~Rva00405350(); };
// Retail base vtable BD77A0 and destructor 1B4E74 prove the canonical 12-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"
#define BFME_SNAPSHOT_NAME_SLOT
#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
class Xfer;
// VictorySystem (ctor 0x004054E1 in VictorySystemCtor.cpp stores the same
// two vftables): the virtual list must equal that unit's so both emit one
// ??_7VictorySystem@@6BSubsystemInterface@@@ / 6BSnapshot@@@ copy.
class VictorySystem : public SubsystemInterface, public Snapshot {
public:
	VictorySystem();
	virtual ~VictorySystem();
	virtual void init();
	virtual void reset();
	virtual void update();
	virtual void LoadPostProcess() {}
	// Retail 0x00405411, between this destructor and the ??_E thunk 0x00405417.
	virtual const char *GetSnapshotName() const { return "VictorySystem"; }
	virtual void DoXfer(Xfer *);
	virtual void newMap();
private:
	char m_pad10[272];
	Rva00405350 m_vec120;
};
VictorySystem::~VictorySystem() {}
