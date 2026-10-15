// ?rva002197A6@CreateAHeroManager@@QAEPAVCreateAHeroData@@H@Z
// partial score=0.95 date=2026-10-15
// ?rva002197A6@CreateAHeroManager@@QAEPAVCreateAHeroData@@H@Z
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// --- 0x002197A6 (116B): CreateAHeroManager hero lookup by key. With a game
// info up, scan its 8 slots for the first occupied entry whose key matches;
// otherwise scan the global registry vector.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

class CreateAHeroData
{
public:
	int m_unk0;
	int m_id;
};

class GameSlot
{
public:
	char m_pad[0x60];
	unsigned char m_has;
	char m_pad61[3];
	CreateAHeroData m_obj;
};

class GameInfo
{
public:
	GameSlot *getSlot(int i);
};

class HeroVec
{
public:
	unsigned int size() const { return m_end - m_begin; }
	CreateAHeroData *operator[](unsigned int i) const { return m_begin[i]; }
	CreateAHeroData **m_begin;
	CreateAHeroData **m_end;
};
extern GameInfo *g_Rva00E02EEC;
extern CreateAHeroData **g_Rva009FE358;
extern CreateAHeroData **g_Rva009FE35C;

class CreateAHeroManager
{
public:
	CreateAHeroData *rva002197A6(int id);
};

CreateAHeroData *CreateAHeroManager::rva002197A6(int id)
{
	CreateAHeroData *result = 0;
	unsigned int i = 0;
	if (g_Rva00E02EEC != 0)
	{
		for (; result == 0 && i < 8; ++i)
		{
			GameSlot *slot = g_Rva00E02EEC->getSlot(i);
			if (slot == 0)
				continue;
			CreateAHeroData *obj = slot->m_has ? &slot->m_obj : (CreateAHeroData *)0;
			if (obj == 0)
				continue;
			if (obj->m_id == id)
				result = obj;
		}
		return result;
	}
	else
	{
		CreateAHeroData **end = g_Rva009FE35C;
		_ReadWriteBarrier();
		unsigned int count = (unsigned int)(end - (g_Rva009FE358));
		for (; result == 0 && i < count; ++i)
		{
			CreateAHeroData *obj = (g_Rva009FE358)[i];
			result = (id == obj->m_id) ? obj : result;
		}
		return result;
	}
}
