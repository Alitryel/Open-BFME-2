// ?rva00272FB6@Rva00272FB6@@QAEXXZ
// partial score=0.11 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /Ireference/shims/bfme2_vector3 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// Link view first: Vector3::Length stays inline without emitting a copy that competes with retail's owner (0x000692B3).
#include "../../../../reference/shims/bfme_vector3_lenfull_link/vector3_lenfull_link.h"
//
// ?rva00272FB6@Rva00272FB6@@QAEXXZ, retail 0x00272FB6..0x00273645 (1682 bytes):
// Drawable local-transform update. Lazily creates the DrawableLocoInfo at +0x13C,
// then blends the loco info's matrices with the object's direction vectors,
// applies the pitch/roll clamp, the chase-field damping and the terrain
// following, and finally writes the resulting position/orientation out to the
// caller's Coord3D.

#include "../../../Libraries/Include/Lib/Coord3D.h"
#include "vector3.h"

class Matrix3D;
class Drawable;
class Object;
class Thing;
class DrawableLocoInfo;

// Minimal views of the engine types the body touches, laid out at the offsets
// the disassembly uses.
class GeometryInfo {
public:
	float getMaxHeightAbovePosition() const;
private:
	char m_pad[0xCC];
public:
	int m_minX;      // +0xCC
	int m_minY;      // +0xD0
};

class Object {
public:
	char m_pad[0x114];
	float m_something114;   // +0x114
	float m_something118;   // +0x118
	float m_something11C;   // +0x11C
	float m_something120;   // +0x120
};

class Thing {
public:
	const Coord3D *getUnitDirectionVector2D() const;
};

class DrawableLocoInfo {
public:
	DrawableLocoInfo();
	char m_pad[0x34];
	float m_pitchRate;      // +0x34
	float m_rollRate;       // +0x38
	char m_tail[0x58-0x3C];
};

class Rva002627E8 {
public:
	float rva002627E8() const;
};

class Rva001E3F27FloatChaseField {
public:
	float get() const;
};

class Rva001E46E1 {
public:
	float rva001E4845(Object *obj);
};

class Drawable {
public:
	char m_pad[0x13C];
	DrawableLocoInfo *m_locoInfo;   // +0x13C
	const Coord3D *getUnitDirectionVector2D() const;
};

// The class the function is a member of; only the fields it touches.
class Rva00272FB6 {
public:
	void rva00272FB6();

	char m_pad[0x13C];
	DrawableLocoInfo *m_locoInfo;   // +0x13C
	unsigned int m_flags268;        // +0x268
};

float Sin(float angle);

int GetGameClientRandomValue(int lo, int hi, char *file, int line);

extern float g_dba4e4;
extern float g_dba4e8;
extern float g_bbb8d8;
extern float g_bbb8d4;
extern float g_bfad90;
extern float g_bc2924;
extern float g_bc5cd8;
extern float g_bc8180;
extern float g_bc26f0;

void Rva00272FB6::rva00272FB6()
{
	struct { float v; unsigned char pad[12]; } padA;
	struct { float v; unsigned char pad[12]; } padB;
	struct { float v; unsigned char pad[12]; } padC;
	struct { float v; unsigned char pad[12]; } padD;
	(void)padA; (void)padB; (void)padC; (void)padD;
	Object *obj = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 4);

	DrawableLocoInfo *fresh;
	{ int z = 0; *(volatile int *)&z = z; fresh = (DrawableLocoInfo *)(z ? 0 : m_locoInfo); }
	if (fresh == (DrawableLocoInfo *)0) {
		fresh = (1 ? new DrawableLocoInfo() : new DrawableLocoInfo());
		m_locoInfo = fresh;
	}

	Drawable *drawable = *reinterpret_cast<Drawable **>(reinterpret_cast<char *>(this) + 0xFC);
	Object *o2 = *reinterpret_cast<Object **>(reinterpret_cast<char *>(this) + 4);
	float local38 = *(volatile float *)(reinterpret_cast<char *>(o2) + 0x88);
	*(volatile float *)&local38 = local38;
	float local20 = *(volatile float *)(reinterpret_cast<char *>(o2) + 0x90);
	*(volatile float *)&local20 = local20;
	float local24 = *(volatile float *)(reinterpret_cast<char *>(o2) + 0x94);
	*(volatile float *)&local24 = local24;
	float local14 = *(volatile float *)(reinterpret_cast<char *>(o2) + 0x98);
	*(volatile float *)&local14 = local14;
	float local18 = *(volatile float *)(reinterpret_cast<char *>(o2) + 0x9C);
	*(volatile float *)&local18 = local18;
	float local2c = *(volatile float *)(reinterpret_cast<char *>(o2) + 0xA8);
	*(volatile float *)&local2c = local2c;
	float local30 = *(volatile float *)(reinterpret_cast<char *>(o2) + 0xB0);
	*(volatile float *)&local30 = local30;
	float local34 = *(volatile float *)(reinterpret_cast<char *>(o2) + 0xB4);
	*(volatile float *)&local34 = local34;
	float local1c = *(volatile float *)(reinterpret_cast<char *>(o2) + 0xB8);
	*(volatile float *)&local1c = local1c;
	float local40 = *(volatile float *)(reinterpret_cast<char *>(o2) + 0x8C);
	*(volatile float *)&local40 = local40;
	obj = o2;
	*(volatile float *)&local38 = local38;
	if (drawable == 0)
		return;

	DrawableLocoInfo *loco = *reinterpret_cast<DrawableLocoInfo **>(reinterpret_cast<char *>(drawable) + 0x258);
	if (loco == 0)
		return;

	if (*reinterpret_cast<void **>(reinterpret_cast<char *>(drawable) + 0x25C) == 0)
		return;

	const Coord3D *dir = reinterpret_cast<Thing *>(this)->getUnitDirectionVector2D();

	float v58, v54, v50;
	{
		float dx = *(float *)((char *)this + 0x424) - *(float *)((char *)this + 0x418);
		float dy = *(float *)((char *)this + 0x428) - *(float *)((char *)this + 0x41C);
		float dz = *(float *)((char *)this + 0x42C) - *(float *)((char *)this + 0x420);
		v58 = dx;
		v54 = dy;
		v50 = dz;
	}

	float v4c = 0.0f;
	float v48 = 0.0f;

	if (drawable->getUnitDirectionVector2D() != 0) {
		// placeholder for the isKindOf branch structure
	}

	// direction-vector blend
	{
		float dx = v58;
		float dy = v54;
		float dz = v50;

		Coord3D tmp;
		tmp.x = dx;
		tmp.y = dy;
		tmp.z = dz;
		tmp.normalize();

		float scale = reinterpret_cast<Rva001E46E1 *>(*reinterpret_cast<void **>(reinterpret_cast<char *>(this) + 8))->rva001E4845(reinterpret_cast<Object *>(drawable));
		(void)scale;
	}

	float ratio = g_dba4e4 / g_dba4e8;
	v50 *= ratio;
	v4c *= ratio;
	v48 *= ratio;

	float f1 = g_bbb8d8 - local14;
	float f2 = g_bbb8d8 - local18;

	DrawableLocoInfo *li = m_locoInfo;

	float m5 = li->m_pad[4];
	m5 *= (g_bbb8d8 - local14);
	m5 *= local20;

	float m6 = 0.0f - m5;
	float m7 = 0.0f - (li->m_pad[8] * local14);
	m6 += m7;
	m6 += li->m_pad[8];
	li->m_pad[8] = m6;

	li = m_locoInfo;
	float m9 = li->m_pad[12];
	m9 *= f2;
	m9 *= local24;
	float m10 = 0.0f - m9;
	float m11 = 0.0f - (li->m_pad[16] * local18);
	m10 += m11;
	m10 += li->m_pad[16];
	li->m_pad[16] = m10;

	li = m_locoInfo;
	li->m_pad[4] += li->m_pad[8] * local1c;

	li = m_locoInfo;
	li->m_pad[12] += li->m_pad[16] * local1c;

	li = m_locoInfo;
	float m12 = li->m_pad[24];
	m12 *= f1;
	m12 *= local20;
	float m13 = 0.0f - m12;
	float m14 = 0.0f - (li->m_pad[28] * local14);
	m13 += m14;
	m13 += li->m_pad[28];
	li->m_pad[28] = m13;

	li = m_locoInfo;
	li->m_pad[24] += li->m_pad[28];

	li = m_locoInfo;
	float m15 = li->m_pad[32];
	m15 *= f2;
	m15 *= local24;
	float m16 = 0.0f - m15;
	float m17 = 0.0f - (li->m_pad[36] * local18);
	m16 += m17;
	m16 += li->m_pad[36];
	li->m_pad[36] = m16;

	li = m_locoInfo;
	li->m_pad[32] += li->m_pad[36];

	li = m_locoInfo;
	float px = li->m_pad[28] + li->m_pad[8];
	float py = li->m_pad[24] + li->m_pad[4];
	*(float *)((char *)this + 0x20) = px;

	Rva002627E8 *out = reinterpret_cast<Rva002627E8 *>(reinterpret_cast<char *>(this) + 0x10);
	(void)out;

	float outX = li->m_pad[36] + li->m_pad[16];
	float outY = li->m_pad[32] + li->m_pad[12];
	(void)outX;
	(void)outY;
}
