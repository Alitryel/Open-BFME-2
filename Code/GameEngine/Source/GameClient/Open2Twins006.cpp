// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/moduledata
// stlport
// BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/GameClient/Open2Twins006.cpp
// The owned implementation at +0x10 uses its retail destructor provider.
// SubsystemInterface occupies 12 bytes, placing Snapshot at +0xC.

#include "Common/Snapshot.h"

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/Common/SubsystemInterface.h
#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

// Snapshot is the canonical BFME2 base from reference/shims/moduledata/Common/Snapshot.h
// (virtual dtor then crc/xfer/loadPostProcess, vtable 0x00BBB554).

class PartitionManagerImpl
{
public:
	virtual ~PartitionManagerImpl();
};

struct Rva009F5970StateInit
{
	float value[6];
};

class T_009f4fb0
{
public:
	void m(Rva009F5970StateInit *value);
};

class Open2Store880FC0 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Open2Store880FC0();
	virtual void init();

private:
	PartitionManagerImpl *m_map;
};

// @??1Open2Store880FC0@@UAE@XZ 0x00880FC0
Open2Store880FC0::~Open2Store880FC0()
{
	PartitionManagerImpl *impl = m_map;
	if (impl) {
		impl->PartitionManagerImpl::~PartitionManagerImpl();
		::operator delete(impl);
	}
}

// ?init@Open2Store880FC0@@UAEXXZ 0x00625560 67B slot1 of 0x0087C6B0 calls T_009f4fb0::m at 0x006276E0 with zeroed state
void Open2Store880FC0::init()
{
	Rva009F5970StateInit state;
	state.value[0] = 0.0f;
	state.value[1] = 0.0f;
	state.value[2] = 0.0f;
	state.value[3] = 0.0f;
	state.value[4] = 0.0f;
	state.value[5] = 0.0f;
	((T_009f4fb0 *)m_map)->m(&state);
}

struct BfmeFlagPair
{
	bool m_bfmeFirst;
	bool m_bfmeSecond;
};

class BfmeFlagTarget
{
public:
	virtual ~BfmeFlagTarget();
	virtual void pad1();
	virtual void pad2();
	virtual void pad3();
	virtual void pad4();
	virtual void pad5();
	virtual void pad6();
	virtual void pad7();
	virtual void pad8();
	virtual void pad9();
	virtual void bfmeDescribe(BfmeFlagPair *flags);
};

class BfmeSinkA
{
public:
	void bfmeAccept(BfmeFlagTarget *target);
};

class Gen_00881040
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	BfmeSinkA *m_bfmeSink;
};

void Gen_00881040::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->bfmeAccept(target);
}

class Xfer;
class ShroudManagerImpl
{
public:
	ShroudManagerImpl();
	~ShroudManagerImpl();
	void rva0073D8B0(Xfer *xfer);
private:
	unsigned char storage[0x70];
};

class Open2Store8F75D0 : public SubsystemInterface, public Snapshot
{
public:
	Open2Store8F75D0();
	virtual ~Open2Store8F75D0();

private:
	ShroudManagerImpl *m_map;
};

// @??1Open2Store8F75D0@@UAE@XZ 0x00739980
Open2Store8F75D0::~Open2Store8F75D0()
{
	delete m_map;
}

// BFME1 donor: Rva008F7510ShroudManagerCtor.cpp at 6583b3c1ff21db4a561285717028fdafc780b7db.
// Retail allocates 0x70 bytes and constructs the owned ShroudManagerImpl at 0x0073E310.
Open2Store8F75D0::Open2Store8F75D0()
{
 m_map = new ShroudManagerImpl;
}

class Gen_008F7650
{
public:
	void bfmeDescribe(BfmeFlagTarget *target);

private:
	char m_bfmeHead[4];
	ShroudManagerImpl *m_bfmeSink;	// retail calls the rowed ShroudManagerImpl Xfer body 0x0073D8B0
};

void Gen_008F7650::bfmeDescribe(BfmeFlagTarget *target)
{
	BfmeFlagPair flags;

	flags.m_bfmeFirst = true;
	flags.m_bfmeSecond = true;

	target->bfmeDescribe(&flags);

	m_bfmeSink->rva0073D8B0(reinterpret_cast<Xfer *>(target));
}

class Rva009A4620CollisionData
{
public:
	~Rva009A4620CollisionData();
};

class Open2Store9A2680 : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Open2Store9A2680();

private:
	Rva009A4620CollisionData *m_map;
};

// @??1Open2Store9A2680@@UAE@XZ 0x00758310
Open2Store9A2680::~Open2Store9A2680()
{
	delete m_map;
}


