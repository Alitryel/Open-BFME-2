// ?rva0039321C@BuildAssistant@@QAE_NPAX000H@Z
// partial score=0.367 date=2026-10-17
// ?rva0039321C@BuildAssistant@@QAE_NPAX000H@Z
// partial score=0.6 date=2026-10-14
// ?rva0039321C@BuildAssistant@@QAE_NPAX000H@Z
// partial score=0.55 date=2026-10-14
// ?rva0039321C@BuildAssistant@@QAE_NPAX000H@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "Code/Libraries/Include/Lib/Coord2D.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include "ascii_string.h"

float normalizeAngle(float angle);

class GlobalData
{
public:
	char m_pad[0xA94];
	unsigned int m_count;
};
extern GlobalData *TheWritableGlobalData;

class TerrainLogic
{
public:
	virtual void t0(); virtual void t1(); virtual void t2(); virtual void t3();
	virtual void t4(); virtual void t5();
	virtual float getHeightAtPoint(float x, float y, float z);
};
extern TerrainLogic *TheTerrainLogic;

class Player
{
public:
	char m_pad94[0x94];
	int m_field94;
};

class ThingTemplate;

class Rva00293330Result
{
public:
	virtual void v00();
	virtual ThingTemplate *getEntry(unsigned int index);	// +0x04
	virtual void v02();
	virtual ThingTemplate *getDefault();			// +0x0C
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual void v07(); virtual void v08(); virtual void v09(); virtual void v10();
	virtual float getRange();				// +0x2C
};

class Rva00293330
{
public:
	void *rva00293330(unsigned int key);
};

class Object : public Rva00293330
{
public:
	int rva0028BD17() const;
	Player *getControllingPlayer() const;
	char m_pad38[0x38];
	float m_x, m_y, m_z;	// +0x38
	char m_pad44[0x7C - 0x44];
	int m_priority;		// +0x7C
};

class ThingTemplate
{
public:
	bool isEquivalentTo(const ThingTemplate *other) const;
	int rva0033A69A(const Player *player, int builderAddress, int price) const;
	char m_pad64[0x64];
	AsciiString m_name;
	char m_padC8[0xC8 - 0x64 - 8];
	float m_fieldC8;
};

class Rva003920F7
{
public:
	void rva003920F7(unsigned int index, const Coord3D *src);
};

class Rva0039205C
{
public:
	void rva00392CAC();
	void rva00392129(unsigned int index, float value);
	void rva0039215F(unsigned int index, const AsciiString &value);
	void rva00392196(unsigned int index, int value);
	int m_count;		// +0x00
	int m_unk04;		// +0x04
	char m_pad08[0x0C - 0x08];
	unsigned char m_b0C;	// +0x0C
	unsigned char m_b0D;	// +0x0D
	char m_pad0E[0x02];
	int m_cached10;		// +0x10
	void *m_unk14;		// +0x14
};

class PartitionManager
{
public:
	Object *rva00625340(const Coord3D *pos, float radius, int distType);
};
extern PartitionManager *ThePartitionManager;

class BuildAssistant
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20();
	virtual bool place(Rva0039205C *out, Object *b, Object *a, unsigned int key, int flag);
	bool rva0039321C(void *a0, void *a1, void *a2, void *a3, int a4);
};

bool BuildAssistant::rva0039321C(void *a0, void *a1, void *a2, void *a3, int a4)
{
	if (a1 == 0 || a2 == 0)
		return false;

	Object *p1 = (Object *)a2;
	Object *p2 = (Object *)a1;
	if ((p1->m_priority > p2->m_priority && !(unsigned char)a4) ? true : true)
	{
		Object *t = p1;
		p1 = p2;
		p2 = t;
	}

	if (!p2->rva0028BD17())
		return false;

	Rva00293330Result *found = (Rva00293330Result *)((Rva00293330 *)p1)->rva00293330((unsigned int)(unsigned)a3);
	if (found == 0)
		return false;

	ThingTemplate *def = found->getDefault();
	if (def == 0)
		return false;

	float p1z = p1->m_z;
	float p1x = p1->m_x;
	float p1y = p1->m_y;
	float p2x = p2->m_x;
	float p2y = p2->m_y;
	float dx = p2x - p1x;
	float dy = p2y - p1y;
	*(volatile float*)&p1z;

	Coord2D angle2d;
	angle2d.x = dx;
	angle2d.y = dy;
	float angle = normalizeAngle(angle2d.toAngle() + 1.5707964f);

	Coord3D dir;
	dir.x = dx;
	dir.y = dy;
	dir.z = 0.0f;

	Coord3D pos;
	pos.x = p1->m_x;
	pos.y = p1->m_y;
	pos.z = p1->m_z;

	dir.normalize();
	float reach = found->getRange();
	*(volatile float*)&reach;
	pos.x += dir.x * reach;
	pos.y += dir.y * reach;

	Player *player = p1->getControllingPlayer();
	int limit = player->m_field94;
	float accum = 0.0f;
	int i = 0;
	float dist = dir.length();
	for (;;)
	{
		if (!(!(reach <= dist)))
			return true;
		if (i >= (int)TheWritableGlobalData->m_count - 1)
			return true;

		ThingTemplate *entry = found->getEntry((unsigned int)i);
		if (entry == 0)
			entry = *(ThingTemplate **)((char *)p1 + 4);

		float radius = entry->m_fieldC8 - 1.0f;

		Coord3D sample;
		sample.x = pos.x + dir.x * radius;
		_ReadWriteBarrier();
		sample.y = pos.y + dir.y * radius;
		sample.z = TheTerrainLogic->getHeightAtPoint(sample.x, sample.y, 0.0f);

		Object *blocker = ThePartitionManager->rva00625340(&sample, radius * 0.25f, 1);
		bool valid = false;
		if (blocker != 0)
		{
			if ((*(unsigned char *)((char *)blocker + 0x438) & 1) != 0)
			{
				if ((*(ThingTemplate **)((char *)blocker + 4))->isEquivalentTo(entry))
					valid = true;
			}
			else
			{
				Coord3D delta;
				delta.x = blocker->m_x - sample.x;
				delta.y = blocker->m_y - sample.y;
				delta.z = blocker->m_z - sample.z;
				float d = delta.length();
				float blockerRadius = *(float *)((char *)blocker + 0xD0);
				if (!(d <= 1.1f))
				{
					if (radius * 1.1f < blockerRadius)
						goto advance;
					if ((*(ThingTemplate **)((char *)blocker + 4))->isEquivalentTo(entry))
					{
						if (a4 == 0)
						{
							((Rva0039205C *)a0)->rva00392CAC();
							return place((Rva0039205C *)a0, p2, p1, (unsigned int)(unsigned)a3, 1);
						}
						return false;
					}
				}
			}
		}

		((Rva003920F7 *)a0)->rva003920F7((unsigned int)i, &sample);
		((Rva0039205C *)a0)->rva00392129((unsigned int)i, angle);
		((Rva0039205C *)a0)->rva0039215F((unsigned int)i, def->m_name);
		((Rva0039205C *)a0)->rva00392196((unsigned int)i, 0);
		((Rva0039205C *)a0)->m_count = i + 1;
		((Rva0039205C *)a0)->m_b0D = 0;
		((Rva0039205C *)a0)->m_b0C = 0;
		((Rva0039205C *)a0)->m_cached10 = 10;
		if (valid)
			((Rva0039205C *)a0)->rva00392196((unsigned int)i, 10);

	advance:
		pos.x += dir.x * radius;
		pos.y += dir.y * radius;
		((Rva0039205C *)a0)->m_unk04 += entry->rva0033A69A(player, (int)p1, -1);
		if (((Rva0039205C *)a0)->m_unk04 > limit)
			((Rva0039205C *)a0)->rva00392196((unsigned int)i, 7);
		i++;
		accum += radius * 1.0f;
		if (i >= (int)TheWritableGlobalData->m_count)
			return true;
		if (!(dist > accum))
			return true;
	}
}
