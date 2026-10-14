// ?Rva005D88AA@Rva005D8883@@UAE_NPAVObject@@@Z
// partial score=0.9515410574 date=2026-10-14
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?Rva005D88AA@Rva005D8883@@UAE_NPAVObject@@@Z
// partial score=0.91 date=2026-09-26
// ?Rva005D88AA@Rva005D8883@@UAE_NPAVObject@@@Z
// partial score=0.91 date=2026-09-26
// cl: /ICode/Libraries/Include /O1 /MD /arch:SSE
class Object;
class ThingTemplate
{
public:
	unsigned char m_pad[0x108];
	unsigned char m_kindByte108;
};
class AIUpdateInterface
{
public:
	Object* getCurrentVictim() const;
};
#include "Lib/Coord3D.h"
class Object
{
public:
	char m_pad0[4];
	ThingTemplate* m_template;
	char m_pad8[0x38 - 8];
	Coord3D m_position;
	char m_pad44[0x258 - 0x38 - sizeof(Coord3D)];
	AIUpdateInterface* m_ai;
};
class Rva005D8883
{
public:
	virtual ~Rva005D8883();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual bool Rva005D88AA(Object* obj);
};
// ?Rva005D88AA@Rva005D8883@@UAE_NPAVObject@@@Z present-unmatched
bool Rva005D8883::Rva005D88AA(Object* obj)
{
	Object* victim = obj->m_ai->getCurrentVictim();
	if (victim == 0 || (victim->m_template->m_kindByte108 & 0x80) != 0)
		return false;
	const Coord3D* a = &obj->m_position;
	const Coord3D* b = &victim->m_position;
	float ax = a->x;
float ay = a->y;
float az = a->z;
float bx = b->x;
float by = b->y;
float bz = b->z;
_ReadWriteBarrier();
float dx = bx - ax;
	float dy = by - ay;
	float dz = bz - az;
	float distSq = dz * dz + dy * dy + dx * dx;
	return distSq <= 22500.0f;
}
