// ?quickHordeUpdate@AIUpdateInterface@@QAEXXZ
// partial score=0.094 date=2026-10-17
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /GX /I.
//
// ?quickHordeUpdate@AIUpdateInterface@@QAEXXZ, retail 0x0026C4EB, 2598 bytes.
// Reconstructed from the retail disassembly plus the WorldBuilder debug twin
// (game.dat rva 0x0026C4EB / WB va 0xe3b6d0).  The body clears five model
// condition bits on the controlled object, then drives the horde locomotion
// state machine (idle / tighten-to-position / path following).

typedef int Int;
typedef float Real;
typedef unsigned int UnsignedInt;

#include "Code/Libraries/Include/Lib/Coord3D.h"

class Object;
class Thing;
class Matrix3D;
class Path;
class Locomotor;
class Pathfinder;
class TerrainLogic;
class TurretStateMachine;
class AICommandInterface;
class AIUpdateInterface;

enum ModelConditionFlagType
{
	MODELCONDITION_NONE = 0
};

enum KindOfType
{
	KINDOF_9C = 0x9C
};

enum PathfindLayerEnum
{
	PATHFIND_LAYER_INVALID = 0
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

enum AICommandType
{
	AICMD_IDLE = 5
};

// ---------------------------------------------------------------------------
// The bit-flag word block at Object+0x110 (591 bits, 0x114..0x11F).
// ---------------------------------------------------------------------------
template <int NUMBITS>
class BitFlags
{
public:
	bool test(Int bit) const
	{
		return (m_bits[bit >> 5] & (1u << (bit & 0x1F))) != 0;
	}

	void ClearBit(Int bit)
	{
		m_bits[bit >> 5] &= ~(1u << (bit & 0x1F));
	}

	void SetBit(Int bit)
	{
		m_bits[bit >> 5] |= (1u << (bit & 0x1F));
	}

	UnsignedInt m_bits[NUMBITS / 32 + 1];
};

// ---------------------------------------------------------------------------
// Object: only the members this function touches, at the retail offsets.
// ---------------------------------------------------------------------------
class Object
{
public:
	void clearModelConditionState(ModelConditionFlagType flag);
	void setModelConditionState(ModelConditionFlagType flag);
	int getLayer() const;
	bool isKindOf(KindOfType kind) const;

	Real getOrientation() const { return m_orientation; }
	void setOrientation(Real angle) { m_orientation = angle; }
	void setPositionZ(Real z) { m_position.z = z; }
	void setTransformMatrix(const Matrix3D *m);
	Real getRelativeAngle(const Coord3D *pos) const;
	Object *getGoalObject() const;

	unsigned char m_pad00b[0x38]; // +0x00 .. +0x37
	Coord3D m_position; // +0x38
	Real m_orientation; // +0x44
	unsigned char m_pad44[0x110 - 0x48]; // +0x48 .. +0x10F
	// +0x110: model condition flags
	BitFlags<591> m_modelCondition; // +0x110
	unsigned char m_pad15C[0x274 - 0x15C]; // +0x15C .. +0x273
	// +0x274: AIUpdateInterface *
	AIUpdateInterface *m_ai; // +0x274
	unsigned char m_pad278[0x438 - 0x278]; // +0x278 .. +0x437
	// +0x438: status bits
	UnsignedInt m_status; // +0x438
};

// ---------------------------------------------------------------------------
// Thing: base of Object with the transform helpers.
// ---------------------------------------------------------------------------
class Thing
{
public:
	void setPositionZ(Real z);
	void setOrientation(Real angle);
	void setTransformMatrix(const Matrix3D *m);
};

// ---------------------------------------------------------------------------
// Path / Locomotor / Pathfinder / TerrainLogic stubs.
// ---------------------------------------------------------------------------
class Path
{
public:
	~Path();
	bool rva001E3591();
	bool rva00364521(const void *field, Coord3D *out);
	double rva00363D20();
};

class Locomotor
{
public:
	Real getMaxTurnRate(Object *obj) const;
	Real rva001E3E6D(Object *obj) const;
	Real rva001E46E1(Object *obj) const;
	void rva001E9083(Object *obj, const Coord3D *pos, Real a, Real b);
	void rva001E53D8(Real a, Object *obj);
};

class Pathfinder
{
public:
	bool IsValidMovementPositionForObject(const Coord3D *pos, int layer, int a, const Object *obj);
	bool IsValidHordeMemberRegularMovement(Object *obj, const Coord3D *from, const Coord3D *to, const Coord3D *to2);
	void rva002EF2A6(Object *obj);
	Path *GetHordeUnitPath(Object *obj, const Coord3D *pos);
};

class TerrainLogic
{
public:
	PathfindLayerEnum getLayerForDestination(Object *obj, const Coord3D *pos);
};

class TurretStateMachine
{
public:
	Object *getGoalObject();
};

// ---------------------------------------------------------------------------
// AIUpdateInterface: the class we are defining.
// ---------------------------------------------------------------------------
class AIUpdateInterface
{
public:
	void quickHordeUpdate();

	// vtable slots touched by the retail body.
	virtual void v00() = 0;
	virtual void v01() = 0;
	virtual void v02() = 0;
	virtual void v03() = 0;
	virtual void v04() = 0;
	virtual void v05() = 0;
	virtual void v06() = 0;
	virtual void v07() = 0;
	virtual void v08() = 0;
	virtual void v09() = 0;
	virtual void v10() = 0;
	virtual void v11() = 0;
	virtual void v12() = 0;
	virtual void v13() = 0;
	virtual void v14() = 0;
	virtual void v15() = 0;
	virtual void v16() = 0;
	virtual void v17() = 0;
	virtual void v18() = 0;
	virtual void v19() = 0;
	virtual void v20() = 0;
	virtual void v21() = 0;
	virtual void v22() = 0;
	virtual void v23() = 0;
	virtual void v24() = 0;
	virtual void v25() = 0;
	virtual void v26() = 0;
	virtual void v27() = 0;
	virtual void v28() = 0;
	virtual void v29() = 0;
	virtual void v30() = 0;
	virtual void v31() = 0;
	virtual void v32() = 0;
	virtual void v33() = 0;
	virtual void v34() = 0;
	virtual void v35() = 0;
	virtual void v36() = 0;
	virtual void v37() = 0;
	virtual void v38() = 0;
	virtual void v39() = 0;
	virtual void v40() = 0;
	virtual void v41() = 0;
	virtual void v42() = 0;
	virtual void v43() = 0;
	virtual void v44() = 0;
	virtual void v45() = 0;
	virtual void v46() = 0;
	virtual void v47() = 0;
	virtual void v48() = 0;
	virtual void v49() = 0;
	virtual void v50() = 0;
	virtual void v51() = 0;
	virtual void v52() = 0;
	virtual void v53() = 0;
	virtual void v54() = 0;
	virtual void v55() = 0;
	virtual void v56() = 0;
	virtual void v57() = 0;
	virtual void v58() = 0;
	virtual void v59() = 0;
	virtual void v60() = 0;
	virtual void v61() = 0;
	virtual void v62() = 0;
	virtual void v63() = 0;
	virtual void v64() = 0;
	virtual void v65() = 0;
	virtual void v66() = 0;
	virtual void v67() = 0;
	virtual void v68() = 0;
	virtual void v69() = 0;
	virtual void v70() = 0;
	virtual void v71() = 0;
	virtual void v72() = 0;
	virtual void v73() = 0;
	virtual void v74() = 0;
	virtual void v75() = 0;
	virtual void v76() = 0;
	virtual void v77() = 0;
	virtual void v78() = 0;
	virtual void v79() = 0;
	virtual void v80() = 0;
	virtual void v81() = 0;
	virtual void v82() = 0;
	virtual void v83() = 0;
	virtual void v84() = 0;
	virtual void v85() = 0;
	virtual void v86() = 0;
	virtual void v87() = 0;
	virtual void v88() = 0;
	virtual void v89() = 0;
	virtual void v90() = 0;
	virtual void v91() = 0;
	virtual void v92() = 0;
	virtual void v93() = 0;
	virtual void v94() = 0;
	virtual void v95() = 0;
	virtual void v96() = 0;
	virtual void v97() = 0;
	virtual void v98() = 0;
	virtual void v99() = 0;
	virtual void v100() = 0;
	virtual void v101() = 0;
	virtual void v102() = 0;
	virtual void v103() = 0;
	virtual void v104() = 0;
	virtual void v105() = 0;
	virtual void v106() = 0;
	virtual void v107() = 0;
	virtual void v108() = 0;
	virtual void v109() = 0;
	virtual void v110() = 0;
	virtual bool isIdle() = 0; // +0x1BC
	virtual bool rva001E3601() = 0; // +0x1C0
	virtual bool rva001E3591() = 0; // +0x1C4
	virtual void rva001E3E6D() = 0; // +0x254

	unsigned char m_pad04[0x20 - 0x04]; // +0x04 .. +0x1F
	// +0x20: AICommandInterface base
	AICommandInterface *m_commandInterface; // +0x20
	unsigned char m_pad24[0x30 - 0x24];
	// +0x30: locomotor
	Locomotor *m_locomotor; // +0x30
	// +0x34
	Int m_moveState; // +0x34
	unsigned char m_pad38[0x140 - 0x38];
	// +0x140: Path *
	Path *m_path; // +0x140
	unsigned char m_pad144[0x168 - 0x144];
	// +0x168
	Real m_float168; // +0x168
	unsigned char m_pad16C[0x1DC - 0x16C];
	// +0x1DC
	Int m_int1DC; // +0x1DC
	unsigned char m_pad1E0[0x1F0 - 0x1E0];
	// +0x1F0: locomotor
	Locomotor *m_locomotor2; // +0x1F0
	// +0x1FC
	Int m_state; // +0x1FC
	// +0x200: destination
	Coord3D m_dest; // +0x200
	unsigned char m_pad20C[0x3E0 - 0x20C];
	// +0x3E0
	bool m_flag3E0; // +0x3E0
};

// ---------------------------------------------------------------------------
// AICommandInterface.
// ---------------------------------------------------------------------------
class AICommandInterface
{
public:
	virtual void aiDoCommand(const void *parms) = 0;

	void aiIdle(CommandSourceType cmdSource);
};

// ---------------------------------------------------------------------------
// Globals.
// ---------------------------------------------------------------------------
extern Object *TheGameLogic;
extern TerrainLogic *TheTerrainLogic;
extern Pathfinder *ThePathfinder;

// ---------------------------------------------------------------------------
// Body.
// ---------------------------------------------------------------------------
void AIUpdateInterface::quickHordeUpdate()
{
	Object *obj = *(Object **)((char *)this + 8);
	Coord3D padA;
	Coord3D padB;
	Coord3D padC;
	Coord3D padD;

	// Clear five model condition bits.
	if (*(volatile unsigned char*)&((unsigned char *)obj)[0x118] & 0x80)
	{
		obj->clearModelConditionState(MODELCONDITION_NONE);
		((unsigned char *)obj)[0x118] &= 0x7f;
	}
	if (*(volatile unsigned int *)&obj->m_modelCondition.m_bits[3] & 0x20)
	{
		((unsigned int *)obj)[0x47] &= 0xffffffdf;
		obj->clearModelConditionState(MODELCONDITION_NONE);
	}
	if (*(volatile unsigned int *)&obj->m_modelCondition.m_bits[3] & 0x40)
	{
		((unsigned int *)obj)[0x47] &= 0xffffffbf;
		obj->clearModelConditionState(MODELCONDITION_NONE);
	}
	if (*(volatile unsigned int *)&obj->m_modelCondition.m_bits[3] & 0x200)
	{
		((unsigned char *)obj)[0x11d] &= 0xfd;
		obj->clearModelConditionState(MODELCONDITION_NONE);
	}
	if (*(volatile unsigned int *)&obj->m_modelCondition.m_bits[3] & 0x400)
	{
		((unsigned char *)obj)[0x11d] &= 0xfb;
		obj->clearModelConditionState(MODELCONDITION_NONE);
	}
	bool idle = this->rva001E3591();

	// If the object is idle and has no path, just idle the command interface.
	if (idle)
	{
		if (obj->m_ai == 0)
		{
			if (obj->getGoalObject() == 0)
			{
				((AICommandInterface *)((char *)this + 0x20))->aiIdle(CMD_FROM_AI);
				return;
			}
		}
	}

	// Path / locomotion update.
	Coord3D dest = m_dest;
	Coord3D cur;
	*(volatile Real*)&cur.x = obj->m_position.x;
	*(volatile Real*)&cur.y = obj->m_position.y;
	*(volatile Real*)&cur.z = obj->m_position.z;
	Real z = cur.z;
	Coord3D saveA = cur;
	Coord3D saveB = dest;
	if (m_state == 0) {
		if (obj->m_status & 1) {
			if (*(volatile unsigned char *)&((unsigned char *)obj)[0x11f] & 0x10) {
				((unsigned char *)obj)[0x11e] &= 0xef;
				obj->clearModelConditionState(MODELCONDITION_NONE);
			}
			Coord3D tmp = cur;
			PathfindLayerEnum layer = TheTerrainLogic->getLayerForDestination(obj, &tmp);
			Real zz = tmp.z;
			if (zz < cur.z) {
				obj->setPositionZ(zz);
				return;
			}
		}
		if (isIdle()) {
			bool b = (m_moveState != 0);
			m_flag3E0 = b;
			Locomotor* loc = m_locomotor;
			(void)loc;
		}
		if (m_state == 2 || m_state == 4 || m_state == 3) {
			Real ang = obj->getOrientation() - m_dest.x;
			(void)ang;
			m_state = 0;
		}
	}
	if (m_path) {
		delete m_path;
		m_path = 0;
	}
	Path* p = ThePathfinder->GetHordeUnitPath(obj, &m_dest);
	if (p) {
		m_path = p;
	}
	{
		Coord3D tailA;
		Coord3D tailB;
		Coord3D tailC;
		Coord3D tailD;
		dest = m_dest;
		tailA = cur;
		tailB = cur;
		tailC = dest;
		tailD = dest;
		(void)tailA; (void)tailB; (void)tailC; (void)tailD;
		(void)z;
		if (m_path != 0) {
			m_state = 1;
		}
	}
}
