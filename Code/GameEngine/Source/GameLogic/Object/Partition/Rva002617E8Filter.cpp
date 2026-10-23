// cl: /ICode/Libraries/Include /O1 /arch:SSE /DNDEBUG /MD
// ?allow@Rva002617E8Filter@@QAE_NPAVObject@@@Z 0x002617E8 115B
// Radius test keeps the x87 NaN path (fst / fldz / fcompi / jae). The
// squared compare is written distance < range so the squares stay in
// xmm3/xmm1, and the range sum is a named (m_range + radius) plus the
// object's +0xB8 so the adds are m_14, radius, then +0xB8.
#include "Lib/Coord3D.h"
class Object
{
public:
	float getShroudClearingRange() const;
	const Coord3D *getPosition() const { return &m_pos; }
	float getB8() const { return m_b8; }
private:
	unsigned char m_pad00[0x38];
	Coord3D m_pos;
	unsigned char m_pad44[0xB8 - 0x44];
	float m_b8;
};
class Rva002617E8Filter
{
public:
	bool allow(Object *obj);
private:
	void *m_vptr;
	void *m_next;
	Coord3D m_pos;
	float m_range;
	bool m_inside;
};
bool Rva002617E8Filter::allow(Object *obj)
{
	float radius = obj->getShroudClearingRange();
	if (radius <= 0.0f)
		return !m_inside;
	float dx = obj->getPosition()->x - m_pos.x;
	float dy = obj->getPosition()->y - m_pos.y;
	float inner = m_range + radius;
	float range = inner + obj->getB8();
	if (dx * dx + dy * dy < range * range)
		return m_inside;
	return !m_inside;
}
