// ?update@AIUpdateInterface@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.2 date=2026-10-17
// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /O1 /arch:SSE /G7
// stlport
// ??1TransportAIUpdateModuleData@@UAE@XZ @0x0026E1FC 107B.
// Identity: the packet pins this address as the TransportAIUpdateModuleData
// destructor; the BFME1 destructor thunk supplies the member teardown shape.
#include "ascii_string.h"

class Rva0026E1A6
{
	void *m_header;
	unsigned int m_count;
	unsigned int m_reserved;
public:
	~Rva0026E1A6();
};

#include <vector>

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
}

class ModuleData
{
public:
	virtual ~ModuleData() {}
	unsigned int m_moduleTagNameKey;
};

class TransportAIUpdateModuleData : public ModuleData
{
public:
	virtual ~TransportAIUpdateModuleData();

private:
	Rva0026E1A6 m_tree;
	int *m_p14;
	int m_f1c, m_f20, m_f24, m_f28, m_f2c;
	AsciiString m_s30;
	int m_f34, m_f38, m_f3c, m_f40, m_f44;
	AsciiString m_s44;
	int m_f48, m_f4c, m_f50, m_f54;
	std::vector<AsciiString> m_vec;
};

// ---------------------------------------------------------------------------
// Minimal declarations for the retail body of AIUpdateInterface::update.
// ---------------------------------------------------------------------------

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 0 };

enum AICommandType { AICMD_UNKNOWN = 0 };
enum CommandSourceType { CMD_FROM_UNKNOWN = 0 };

enum ObjectStatusTypes
{
	OBJECT_STATUS_UNSELECTABLE = 0x4a,
	OBJECT_STATUS_UNDER_CONSTRUCTION = 0x26
};

enum KindOfType
{
	KINDOF_25 = 0x25,
	KINDOF_3D = 0x3d,
	KINDOF_1BA = 0x1ba
};

class Object;
class Team;
class AIUpdateInterface;

class Coord3D
{
public:
	float x, y, z;
	float GetLengthEstimate2D() const;
};

class GeometryInfo
{
public:
	GeometryInfo(const GeometryInfo &);
	~GeometryInfo();
	unsigned char m_pad[0x60];
	float m_radius; // +0x5c
};

class AICommandParms
{
public:
	AICommandParms(AICommandType, CommandSourceType);
	~AICommandParms();
	unsigned char m_data[0xDC];
};

class Object
{
public:
	bool testStatus(ObjectStatusTypes) const;
	bool isKindOf(KindOfType) const;
	void setStatus(ObjectStatusTypes, bool);
	void *getTemplate() const;
	float getDistanceTo(const void *) const;
	bool isWithinDistanceOf(const Object *, int) const;
	void *getAIUpdateInterface() const;
	void *getTeam() const;
};

class AIUpdateInterface
{
public:
	virtual UpdateSleepTime update();
	int quickHordeUpdate();
	int handleEngagedFlag();
	int getCurrentVictim();
	void rva00265173();
	void rva0028AE6D();
	void rva00298C76(Team *, unsigned int);
};

// AIUpdateInterface is a sub-object embedded at offset 0x10 inside the
// concrete update module; the module's own header sits at -0x10.
struct AIUpdateInterfaceFull : public AIUpdateInterface
{
	unsigned char m_pad0[0x20 - 0x4];
	Object *m_object;              // +0x20
	unsigned char m_pad1[0x1ec - 0x24];
	int m_state;                   // +0x1ec
	unsigned char m_pad2[0x230 - 0x1f0];
	unsigned int m_teamID;         // +0x230
	unsigned char m_pad3[0x2dc - 0x234];
	int m_command;                 // +0x2dc
	unsigned char m_pad4[0x3be - 0x2e0];
	unsigned char m_flag3be;       // +0x3be
	unsigned char m_pad5[0x3c0 - 0x3bf];
	unsigned char m_scriptTracker[0x40]; // +0x3c0
};

// The update module header (Object *this is the AIUpdateInterface sub-object).
struct AIUpdateModuleHeader
{
	unsigned char m_pad0[0x74];
	int m_ordersID;                // +0x74
};

extern "C" void __EH_prolog();

// ---------------------------------------------------------------------------

UpdateSleepTime AIUpdateInterface::update()
{
	AIUpdateInterfaceFull *self = (AIUpdateInterfaceFull *)this;
	Object *object = *(Object **)((char *)self - 8);
	UpdateSleepTime ret = UPDATE_SLEEP_NONE;
	int distanceEstimate = *(volatile int *)0xe01e18;
	AIUpdateModuleHeader *hdr0 = (AIUpdateModuleHeader *)((char *)self - 0x10);
	int orders0 = hdr0->m_ordersID;
	(void)orders0;
	self->rva00265173();
	if (object->testStatus((ObjectStatusTypes)0x48)) {}
	if (orders0) (void)orders0;

	int engagedProbe = *(volatile int *)((char *)self + 0x130);
	int stateProbe = self->m_state;
	if (engagedProbe) (void)stateProbe;
	if ((1 ? *(volatile int *)&self->m_command : *(volatile int *)&self->m_command) != -1)
	{
		if (object->isKindOf((KindOfType)KINDOF_3D))
		{
			if (!object->isKindOf((KindOfType)KINDOF_1BA))
			{
				self->m_flag3be = 1;
			}
		}
	}
	if (*(int *)((char *)self + 0x2dc) != -1)
	{
		AICommandParms parms((AICommandType)-1, (CommandSourceType)2);
		void *iface = *(void **)((char *)self + 0x10);
		*(volatile int *)&self->m_command = -1;
		(*(void (__stdcall **)(AICommandParms *)) * (void **)iface)(&parms);
		distanceEstimate = 0;
		if (0) throw 1;
	}
	if (*(volatile unsigned int *)&self->m_teamID != 0)
	{
		self->m_teamID = 0;
	}

	if (*(volatile unsigned int *)&self->m_teamID != 0)
	{
		self->m_teamID = 0;
	}

	if (self->m_state == 2 || self->m_state == 3 || self->m_state == 4)
	{
		if (object->isKindOf((KindOfType)KINDOF_25))
		{
			distanceEstimate = self->quickHordeUpdate();
		}
	}
	if (object->isKindOf((KindOfType)KINDOF_3D))
	{
		if (!object->isKindOf((KindOfType)KINDOF_1BA))
		{
			self->m_flag3be = 1;
		}
	}
	if (self->handleEngagedFlag())
	{
		distanceEstimate = self->getCurrentVictim();
	}

	if (!object->testStatus(OBJECT_STATUS_UNDER_CONSTRUCTION))
	{
		GeometryInfo info(*(GeometryInfo *)0);
		(void)info.m_radius;
	}
	{
		void *p = *(void **)0xe01e18;
		(void)p;
	}

	if (*(volatile unsigned int *)&self->m_teamID != 0)
	{
		self->m_teamID = 0;
	}

	if (*(volatile unsigned int *)&self->m_teamID == 0)
	{
		AIUpdateModuleHeader *hdr = (AIUpdateModuleHeader *)((char *)self - 0x10);
		int orders = hdr->m_ordersID;
		(void)orders;
		self->rva00265173();
	}
	(void)distanceEstimate;
	return ret;
}
