// Native1E685F..1E68D7 RET12; WB ADF040 and owned1E702E forwarder
// establish the same receiver and matrix-copy/turn/pivot sequence. The source
// matrix begins at object+08 and three16-byte rows populate receiver+68.
// Row setters copy four words each; whole-matrix assignment emits REP MOVS.
// The existing address-derived three-word signature is retained: objectWord
// is the first caller pointer and the other words are passed as pointer bits
// to the now-owned turn/pivot worker. Original API type spelling is unproven.
// Row storage/layout and complete calls are target evidence; no donor layout
// or class extent is claimed.
// cl: /O1 /DNDEBUG /MD /I.

// Native 0x001E68D7..0x001E6B8B is a four-argument Locomotor movement step.
// Its offsets, speed clamp, reverse flag and turn scaling come from retail.
// The writable scale name describes its use; its original EA name is unknown.
typedef float Real;
typedef bool Bool;

#include "Code/Libraries/Include/Lib/Coord3D.h"
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)

struct SteeringCoord : Coord3D
{
    SteeringCoord() {}
    void copy(const Coord3D &r) { x = r.x; y = r.y; z = r.z; }
    SteeringCoord(const Coord3D &r) { copy(r); }
    void subtract(const Coord3D &r) { x -= r.x; y -= r.y; z -= r.z; }
};
#include <math.h>
float __cdecl atan2(float y, float x);	// math.h's float overload, retail 0x000422CD
Real normalizeAngle(Real angle);
Real Cos(Real angle);
Real Sin(Real angle);

class Object
{
public:
	void rva0028AE6D();
    bool modelTest(int bit) const { return (m_modelConditions & (1 << bit)) != 0; }

	char m_pad000[0x38];
	Coord3D m_pos; // +0x38
	Real m_orientation; // +0x44
	char m_pad048[0x11c - 0x48];
	unsigned int m_modelConditions; // observed word at Object +0x11C
};

class Rva001E46E1
{
public:
	Real rva001E4845(Object *obj);
    void rva001E56DC(Object *, const Coord3D *, float, float *);
};

struct MatrixRow{unsigned int a,b,c,d;__forceinline void set(const MatrixRow&r){a=r.a;b=r.b;c=r.c;d=r.d;}};
class Thing {public:char prefix[8];MatrixRow matrix[3];};
class Rva001E685F {public:void rva001E685F(int,int,int);char prefix[0x68];MatrixRow matrix[3];};

class Rva001E6007
{
public:
	void rva001e6007(unsigned int obj, unsigned int goalPos, Real onPathDistToGoal, Real desiredSpeed);
};

struct LocomotorReverseData
{
	char m_pad000[0xd8];
	int m_canReverse; // +0xD8
	char m_pad0DC[0x13c - 0xdc];
	Bool m_13C; // +0x13C
	char m_pad13D[3];
	Real m_reverseDistance; // +0x140
	Real m_reversePathDistance; // +0x144
	Real m_reverseAngle; // +0x148
};

class Locomotor
{
public:
	Real getMaxSpeed(Object *obj) const;
    Real getMaxTurnRate(Object *obj) const;
    void rva001E68D7(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal, Real desiredSpeed);

private:
	void *m_vtbl;
	LocomotorReverseData *m_template; // +0x04
	char m_pad08[0x14 - 8];
	Coord3D m_point; // +0x14
	char m_pad20[0x40 - 0x20];
	Real m_turnRate; // +0x40
	unsigned int m_flags; // +0x44
    bool reversing() const { return (m_flags & (1 << 7)) != 0; }
};

float g_locomotorReverseTurnScale = 3.5f;

void Locomotor::rva001E68D7(Object *obj, const Coord3D *goalPos, Real onPathDistToGoal, Real desiredSpeed)
{
	// sanity, we cannot use desired speed that is greater than our max speed we are capable of moving at
	Real maxSpeed = getMaxSpeed(obj);
	if (desiredSpeed > maxSpeed)
		desiredSpeed = maxSpeed;

	// Orient toward goal position
	Real angle = obj->m_orientation;
	SteeringCoord target;
	Real desiredAngle = atan2(goalPos->y - obj->m_pos.y, goalPos->x - obj->m_pos.x);
	Real relAngle = normalizeAngle(desiredAngle - angle);

	Bool reverse = m_template->m_canReverse != 0;
	if (reverse)
	{
		target.copy(m_point);
		target.subtract(obj->m_pos);
		Real distance = target.GetLengthEstimate2D();
		if (distance > m_template->m_reverseDistance && onPathDistToGoal > m_template->m_reversePathDistance)
			reverse = false;
	}

	Real turnRate = m_turnRate;
	if (reverse && (_ReadWriteBarrier(), fabs(relAngle)) > m_template->m_reverseAngle * 3.1415927f)
	{
		if (!(obj->m_modelConditions & 0x10000000))
		{
			// Preserve retail's separate test and memory update.
			_ReadWriteBarrier();
			obj->m_modelConditions |= 0x10000000;
			obj->rva0028AE6D();
		}
		m_flags |= 0x80;
	}
	else
	{
		if (obj->m_modelConditions & 0x10000000)
		{
			_ReadWriteBarrier();
			obj->m_modelConditions &= ~0x10000000;
			obj->rva0028AE6D();
		}
		m_flags &= ~0x80;
	}

	if (reversing())
		desiredAngle = normalizeAngle(desiredAngle - 3.1415927f);

	target.copy(obj->m_pos);
	target.x += Cos(desiredAngle) * 1000.0f;
	target.y += Sin(desiredAngle) * 1000.0f;
	reinterpret_cast<Rva001E685F *>(this)->rva001E685F((int)obj, (int)&target, 0);

	if (reinterpret_cast<Rva001E46E1 *>(this)->rva001E4845(obj) >= turnRate)
		relAngle *= 2.0f;

	if (maxSpeed > 0.0f)
	{
		// Modulate speed according to turning. The more we have to turn, the slower we go
		Real maxTurnRate = getMaxTurnRate(obj);
        Real angleCoeff = (Real)fabs(relAngle) / (g_locomotorReverseTurnScale * maxTurnRate);
		if (angleCoeff > 0.9f)
			angleCoeff = 0.9f;
        desiredSpeed = (1.0f - angleCoeff) * desiredSpeed;
        if (m_template->m_13C && reversing())
        {
            if (obj->modelTest(5) || obj->modelTest(6))
                desiredSpeed = 0.0f;
        }
		reinterpret_cast<Rva001E6007 *>(this)->rva001e6007((unsigned int)obj, (unsigned int)goalPos, onPathDistToGoal, desiredSpeed);
	}
}

void Rva001E685F::rva001E685F(int objectWord,int a,int b){
Thing*obj=(Thing*)objectWord;
matrix[0].set(obj->matrix[0]);
matrix[1].set(obj->matrix[1]);
matrix[2].set(obj->matrix[2]);
float turn=((const Locomotor*)this)->getMaxTurnRate((Object*)obj);((Rva001E46E1*)this)->rva001E56DC((Object*)obj,(const Coord3D*)a,turn,(float*)b);}
