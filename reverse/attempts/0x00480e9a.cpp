// ?rva00480E9A@Rva00480E9A@@QAEXPAVObject@@@Z
// partial score=0.7212 date=2026-10-14
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva00480E9A@Rva00480E9A@@QAEXPAVObject@@@Z
// partial score=0.588 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva00480E9A@Rva00480E9A@@QAEXPAVObject@@@Z @0x00480E9A 328B, retail-guided
// (the WB 0x11B6E00 is a different build). AI idle + orders, bitset guard,
// partition query that destroys the closest object, upgrade loop, trailing FX,
// then record the object id.
class Object;
class Player;
class UpgradeTemplate;
class FXList;
struct UpgradeTemplateView { void *m_4; };

class GameLogic { public: void destroyObject(Object *obj); };
extern GameLogic *TheGameLogic;

class PartitionManager;
extern PartitionManager *ThePartitionManager;
class UpgradeCenter;
extern UpgradeCenter *TheUpgradeCenter;

class AIUpdateInterface
{
public:
#define BFME_V8(a,b,c,d,e,f,g,h) virtual void v##a(); virtual void v##b(); virtual void v##c(); virtual void v##d(); virtual void v##e(); virtual void v##f(); virtual void v##g(); virtual void v##h();
	BFME_V8(000,001,002,003,004,005,006,007) BFME_V8(008,009,010,011,012,013,014,015)
	BFME_V8(016,017,018,019,020,021,022,023) BFME_V8(024,025,026,027,028,029,030,031)
	BFME_V8(032,033,034,035,036,037,038,039) BFME_V8(040,041,042,043,044,045,046,047)
	BFME_V8(048,049,050,051,052,053,054,055) BFME_V8(056,057,058,059,060,061,062,063)
	BFME_V8(064,065,066,067,068,069,070,071) BFME_V8(072,073,074,075,076,077,078,079)
	BFME_V8(080,081,082,083,084,085,086,087) BFME_V8(088,089,090,091,092,093,094,095)
	BFME_V8(096,097,098,099,100,101,102,103) BFME_V8(104,105,106,107,108,109,110,111)
	BFME_V8(112,113,114,115,116,117,118,119) BFME_V8(120,121,122,123,124,125,126,127)
	BFME_V8(128,129,130,131,132,133,134,135) BFME_V8(136,137,138,139,140,141,142)
	virtual int v143();
#undef BFME_V8
};

class Player
{
public:
	void rva002AE329(const UpgradeTemplate *up, int a, int b);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva0028CDEB(const void *bits, int flag);
	void rva00293077(const void *up);
	void *m_258; // +0x258 AI
	int m_74;    // +0x74
};

class Rva00480E9A
{
public:
	void rva00480E9A(Object *obj);
private:
	void *m_4;   // +0x04
	void *m_8;   // +0x08
	char m_pad0C[0x9EC - 0x0C];
	int m_9EC;   // +0x9EC
};

struct Rva00480E9AQuery
{
	int m_00;
	void *m_04;
	void *m_08;
	Player *m_0C;
	unsigned char m_10;
};

int rva001E8A38(AIUpdateInterface *ai, int value);
void rva003551D3(void *manager, int id);
bool rva004454BA(void *bits);
Object *rva00625360(PartitionManager *pm, void *pos, float radius, int mode, Rva00480E9AQuery *query);
UpgradeTemplate *rva0026F26D(UpgradeCenter *uc, int id);
void rva000B2235(FXList *fx, Object *obj, int flag);

extern float g_00DC9EB4;

void Rva00480E9A::rva00480E9A(Object *obj)
{
	void *m8 = (obj ? m_8 : m_8);
	AIUpdateInterface *ai = (AIUpdateInterface *)obj->m_258;
	int v = ai->v143();
	rva001E8A38(ai, v);
	rva003551D3((void *)0x00E01E18, obj->m_74);

	void *m4 = m_4;
	void *bits = (char *)m4 + 0xEC;
	if (rva004454BA(bits))
		obj->rva0028CDEB(bits, 0);

	Player *p = obj->getControllingPlayer();
	Rva00480E9AQuery query;
	query.m_00 = 0;
	query.m_04 = (void *)0x00BCECF0;
	query.m_08 = (char *)m4 + 0xFC;
	query.m_0C = p;
	query.m_10 = 1;
	_ReadWriteBarrier();
	float radius = g_00DC9EB4;
	Object *closest = rva00625360(ThePartitionManager, (char *)m8 + 0x38, radius, 3, &query);
	if (closest)
		TheGameLogic->destroyObject(closest);

	for (int *it = *(int **)((char *)m4 + 0x100); it != *(int **)((char *)m4 + 0x104); ++it)
	{
		UpgradeTemplate *up = rva0026F26D(TheUpgradeCenter, *it);
		if (((UpgradeTemplateView *)up)->m_4 == 0)
		{

			(obj->getControllingPlayer())->rva002AE329(up, 2, 0);
		}
		else
		{
			obj->rva00293077(up);
		}
	}

	FXList *fx = *(FXList **)((char *)m4 + 0x10C);
	if (fx)
		rva000B2235(fx, obj, 0);

	m_9EC = obj->m_74;
}
