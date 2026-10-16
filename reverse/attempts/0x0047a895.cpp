// ?rva0047A895@HordeContain@@QAEXPAVObject@@PBUCoord3D@@M_N@Z
// partial score=0.6 date=2026-10-16
// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /ICode/Libraries/Include
//
// ?rva0047A895@HordeContain@@QAEXPAVObject@@PBUCoord3D@@M_N@Z, retail 0x0047A895 (1018 B, RET 0x10)
//
// W9-O2 first C++ draft (2026-10-16). Target facts: native 0x47A895..0x47AC8F and WB 0x0115F9B0
// (debug: Object.h clear/setModelConditionState at lines 862/873, BitFlags test/set/clear,
// HordeContain::updatePosition = 0x474842, HordeContain::_updatePosition = 0x471464,
// Locomotor::getMaxSpeed/getMaxTurnRate, Object::GetRelativeAngle, Coord3D GetLength/normalize,
// cos/sin, Thing::setTransformMatrix/setPosition, Object::setNextPosition inlined (+0x198/+0x1A6)).
// A HordeContain member update that, for kind 0xDA, defers to updatePosition; for an AI whose slot
// 0x1BC holds, clears one model condition; otherwise moves the member towards pos clamped by its
// locomotor speed (x1.25) and turn rate, picks the rank angle by the formation slot's key, toggles
// model conditions 29 / 0xB7 from the module data's flags and sets its transform.
// Residue (nd ~130, 1028 B): obj set-path bit test loads the word (retail test/or memory with the
// mask in EAX); frame 0x4C vs 0x48 (retail overlaps the slot int, the 0x0046A5B1 result temp and
// delta); member-wise position copy register order; the inlined Rotate_Z x87/SSE split.
#include <math.h>
#include "Lib/Coord3D.h"
#include "Lib/Coord2D.h"

class Vector3
{
public:
	float &operator[](int i) { return (&X)[i]; }
	const float &operator[](int i) const { return (&X)[i]; }
	float X;
	float Y;
	float Z;
};

class Vector4
{
public:
	__forceinline void Set(float x, float y, float z, float w) { X = x; Y = y; Z = z; W = w; }
	float &operator[](int i) { return (&X)[i]; }
	float X;
	float Y;
	float Z;
	float W;
};

class Matrix3D
{
public:
	__forceinline explicit Matrix3D(bool init) { if (init) Make_Identity(); }
	__forceinline void Make_Identity()
	{
		Row[0].Set(1.0f, 0.0f, 0.0f, 0.0f);
		Row[1].Set(0.0f, 1.0f, 0.0f, 0.0f);
		Row[2].Set(0.0f, 0.0f, 1.0f, 0.0f);
	}
	__forceinline void Set_Translation(const Vector3 &t) { Row[0][3] = t[0]; Row[1][3] = t[1]; Row[2][3] = t[2]; }
	__forceinline void Rotate_Z(float theta)
	{
		float tmp1, tmp2;
		float c, s;

		c = cosf(theta);
		s = sinf(theta);

		tmp1 = Row[0][0]; tmp2 = Row[0][1];
		Row[0][0] = (float)( c*tmp1 + s*tmp2);
		Row[0][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[1][0]; tmp2 = Row[1][1];
		Row[1][0] = (float)( c*tmp1 + s*tmp2);
		Row[1][1] = (float)(-s*tmp1 + c*tmp2);

		tmp1 = Row[2][0]; tmp2 = Row[2][1];
		Row[2][0] = (float)( c*tmp1 + s*tmp2);
		Row[2][1] = (float)(-s*tmp1 + c*tmp2);
	}
private:
	Vector4 Row[3];
};

enum KindOfType { KINDOF_RVA0047A895_DA = 0xDA };

class Object;
class Locomotor
{
public:
	float getMaxSpeed(Object *obj) const;		// 0x001E46E1
	float getMaxTurnRate(Object *obj) const;	// 0x001E3E9F
};
struct Rva0028AC4EEntry;

class PhysicsBehavior
{
public:
	void rva00390629(bool flag);			// 0x00390629
};

class Rva0047A895AI
{
public:
	virtual void v000();
	virtual void v001();
	virtual void v002();
	virtual void v003();
	virtual void v004();
	virtual void v005();
	virtual void v006();
	virtual void v007();
	virtual void v008();
	virtual void v009();
	virtual void v010();
	virtual void v011();
	virtual void v012();
	virtual void v013();
	virtual void v014();
	virtual void v015();
	virtual void v016();
	virtual void v017();
	virtual void v018();
	virtual void v019();
	virtual void v020();
	virtual void v021();
	virtual void v022();
	virtual void v023();
	virtual void v024();
	virtual void v025();
	virtual void v026();
	virtual void v027();
	virtual void v028();
	virtual void v029();
	virtual void v030();
	virtual void v031();
	virtual void v032();
	virtual void v033();
	virtual void v034();
	virtual void v035();
	virtual void v036();
	virtual void v037();
	virtual void v038();
	virtual void v039();
	virtual void v040();
	virtual void v041();
	virtual void v042();
	virtual void v043();
	virtual void v044();
	virtual void v045();
	virtual void v046();
	virtual void v047();
	virtual void v048();
	virtual void v049();
	virtual void v050();
	virtual void v051();
	virtual void v052();
	virtual void v053();
	virtual void v054();
	virtual void v055();
	virtual void v056();
	virtual void v057();
	virtual void v058();
	virtual void v059();
	virtual void v060();
	virtual void v061();
	virtual void v062();
	virtual void v063();
	virtual void v064();
	virtual void v065();
	virtual void v066();
	virtual void v067();
	virtual void v068();
	virtual void v069();
	virtual void v070();
	virtual void v071();
	virtual void v072();
	virtual void v073();
	virtual void v074();
	virtual void v075();
	virtual void v076();
	virtual void v077();
	virtual void v078();
	virtual void v079();
	virtual void v080();
	virtual void v081();
	virtual void v082();
	virtual void v083();
	virtual void v084();
	virtual void v085();
	virtual void v086();
	virtual void v087();
	virtual void v088();
	virtual void v089();
	virtual void v090();
	virtual void v091();
	virtual void v092();
	virtual void v093();
	virtual void v094();
	virtual void v095();
	virtual void v096();
	virtual void v097();
	virtual void v098();
	virtual void v099();
	virtual void v100();
	virtual void v101();
	virtual void v102();
	virtual void v103();
	virtual void v104();
	virtual void v105();
	virtual void v106();
	virtual void v107();
	virtual void v108();
	virtual void v109();
	virtual void v110();
	virtual bool rva0047A895Slot111();	// +0x1BC
};

class Thing
{
public:
	void setTransformMatrix(const Matrix3D *mtx);	// 0x0030A2B7
	void setPosition(const Coord3D *pos);		// 0x0030AA80
};

class Object : public Thing
{
public:
	bool isKindOf(KindOfType t) const;		// 0x0006F039
	const Rva0028AC4EEntry *rva0028AC4E() const;	// 0x0028AC4E
	void rva0028AE6D();				// 0x0028AE6D
	float GetRelativeAngle(const Coord3D *pos) const;	// 0x000B4542
	char m_pad000[0x38];
	Coord3D m_pos;				// +0x38
	float m_orientation;			// +0x44
	char m_pad048[0x74 - 0x48];
	int m_id;				// +0x74
	char m_pad078[0x110 - 0x78];
	unsigned int m_modelConditions[6];	// +0x110
	char m_pad128[0x198 - 0x128];
	Coord3D m_198;				// +0x198
	char m_pad1A4[0x1A6 - 0x1A4];
	bool m_1A6;				// +0x1A6
	char m_pad1A7[0x258 - 0x1A7];
	Rva0047A895AI *m_258;			// +0x258
	PhysicsBehavior *m_physics;		// +0x25C
};

struct Rva0047A895Slot				// 0x1C bytes at +0x188
{
	int m_00;
	float m_04;
	char m_pad08[0x1C - 0x08];
};

struct Rva0047A895Rank				// 0x18 bytes at +0x6FC
{
	float m_threshold;
	float m_angle;
	char m_pad08[0x18 - 0x08];
};

struct Rva0047A895Data
{
	char m_pad000[0x110];
	unsigned int m_110;			// +0x110 flags (bit 29)
	char m_pad114[0x124 - 0x114];
	unsigned int m_124;			// +0x124 flags (bit 23)
};

class Rva00474842
{
public:
	void rva00474842(Object *obj, const Coord3D *pos, float angle, bool flag);	// 0x00474842
};

class Rva0046ACF6
{
public:
	int rva0046ACF6(int id);			// 0x0046ACF6
};

class HordeContain
{
public:
	void rva0047A895(Object *obj, const Coord3D *pos, float angle, bool flag);
	void _updatePosition(Object *obj, const Coord3D *pos, float angle);	// 0x00471464
	Coord2D *rva0046A5B1(Coord2D *out, int slot);	// 0x0046A5B1
private:
	char m_pad000[0x08];
	const Rva0047A895Data *m_data;		// +0x08
	char m_pad00C[0x188 - 0x0C];
	Rva0047A895Slot *m_slots;		// +0x188
	char m_pad18C[0x2A0 - 0x18C];
	int m_2A0;				// +0x2A0
	char m_pad2A4[0x6FC - 0x2A4];
	Rva0047A895Rank m_ranks[(0x8DC - 0x6FC) / 0x18];	// +0x6FC
	int m_rankCount;			// +0x8DC
};

// Model-condition bits as BitFlags words: (word index, mask).
static inline bool flagTest(unsigned int w, int bit) { return (w & (1u << (bit & 31))) != 0; }
static inline bool mcTestFn(const unsigned int *w, int b) { return (w[b >> 5] & (1u << (b & 31))) != 0; }
static inline void mcSetFn(unsigned int *w, int b) { w[b >> 5] |= 1u << (b & 31); }
#define MC_WORD(b) ((b) >> 5)
#define MC_MASK(b) (1u << ((b) & 31))
#define mcTest(w, b) ((((const unsigned char *)(w))[(b) >> 3] & (1u << ((b) & 7))) != 0)
#define mcTestW(w, b) (((w)[MC_WORD(b)] & MC_MASK(b)) != 0)
#define mcSet(w, b) ((w)[MC_WORD(b)] |= MC_MASK(b))
#define mcClear(w, b) ((w)[MC_WORD(b)] &= ~MC_MASK(b))

void HordeContain::rva0047A895(Object *obj, const Coord3D *pos, float angle, bool flag)
{
	if (obj->isKindOf(KINDOF_RVA0047A895_DA)) {
		((Rva00474842 *)this)->rva00474842(obj, pos, angle, flag);
		if (mcTest(obj->m_modelConditions, 0xBA)) {
			mcClear(obj->m_modelConditions, 0xBA);
			obj->rva0028AE6D();
		}
		return;
	}
	Rva0047A895AI *ai = obj->m_258;
	if (ai && ai->rva0047A895Slot111()) {
		if (mcTest(obj->m_modelConditions, 0x1D)) {
			mcClear(obj->m_modelConditions, 0x1D);
			obj->rva0028AE6D();
		}
		return;
	}
	if (m_2A0 != 0) {
		_updatePosition(obj, pos, angle);
		return;
	}
	float maxMove;
	{
	int slot = ((Rva0046ACF6 *)this)->rva0046ACF6(obj->m_id);
	float key = m_slots[slot].m_04;
	int i;
	for (i = m_rankCount - 1; i > 0; --i) {
		if (m_ranks[i].m_threshold == key)
			break;
	}
	if (i < 0)
		i = 0;
	angle = m_ranks[i].m_angle;
	maxMove = 9999.0f;
	float maxTurn = 3.1415927f;
	Locomotor *loco = (Locomotor *)obj->rva0028AC4E();
	if (loco) {
		maxMove = loco->getMaxSpeed(obj) * 1.25f;
		maxTurn = loco->getMaxTurnRate(obj);
	}
	if (flagTest(m_data->m_110, 29)) {
		if (!mcTestFn(obj->m_modelConditions, 0x1D)) {
			mcSetFn(obj->m_modelConditions, 0x1D);
			obj->rva0028AE6D();
		}
	} else if (mcTest(obj->m_modelConditions, 0x1D)) {
		mcClear(obj->m_modelConditions, 0x1D);
		obj->rva0028AE6D();
	}
	if (flagTest(m_data->m_124, 23)) {
		if (!mcTestFn(obj->m_modelConditions, 0xB7)) {
			mcSetFn(obj->m_modelConditions, 0xB7);
			obj->rva0028AE6D();
		}
		Coord2D offset;
		rva0046A5B1(&offset, slot);
		float rel = obj->GetRelativeAngle(pos);
		if (rel > maxTurn)
			rel = maxTurn;
		else if (-maxTurn > rel)
			rel = -maxTurn;
		angle = obj->m_orientation + rel;
	} else if (mcTest(obj->m_modelConditions, 0xB7)) {
		mcClear(obj->m_modelConditions, 0xB7);
		obj->rva0028AE6D();
	}
	}
	Coord3D newPos;
	newPos.x = obj->m_pos.x;
	newPos.y = obj->m_pos.y;
	newPos.z = obj->m_pos.z;
	{
	Coord3D delta;
	delta.x = pos->x - newPos.x;
	delta.y = pos->y - newPos.y;
	delta.z = pos->z - newPos.z;
	if (delta.GetLength() > maxMove) {
		delta.normalize();
		newPos.x += delta.x * maxMove;
		newPos.y += delta.y * maxMove;
		newPos.z += delta.z * maxMove;
	} else {
		newPos = *pos;
	}
	}
	Matrix3D mtx(true);
	mtx.Set_Translation(*(const Vector3 *)&newPos);
	mtx.Rotate_Z(angle);
	obj->setTransformMatrix(&mtx);
	obj->setPosition(&newPos);
	obj->m_1A6 = true;
	obj->m_198 = newPos;
	if (obj->m_physics)
		obj->m_physics->rva00390629(false);
}
