// ?doDrawModule@W3DModelDraw@@UAEXPBVMatrix3D@@@Z
// partial score=0.98 date=2026-10-13
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /DWIN32 /D_WINDOWS /Ireference/shims/bfme2_ascii /ICode/Libraries/Include/Lib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/WWVegas
// W3DModelDraw::doDrawModule @0x000C7BC4 1563B.
// Target facts: thiscall RET 4, the slot the W3DTruckDraw and W3DTankDraw
// doDrawModule bodies chain to; the transform argument (not the drawable's
// own matrix) feeds both the particle position and the render transform.
// Module data +0x04 gates on +0x15D (multiplayer only, global +0xD45 off) and
// +0x15F; a client particle system handle at +0x1C follows the transform while
// module data +0x14 names a template and bit 15 of +0x198 is set, else it is
// destroyed. Render object +0x50 takes the transform: rotated by the tactical
// view angle when the template byte +0x122 bit 0 is set, else the
// reactToTransformChange +0x69/+0x6A shape, then adjustTransformMtx (0x000B710D)
// and Set_Transform. +0x270..+0x288 ramp the render object emissive colour by
// elapsed client frames. Drawables whose ids sit in the set at +0xA8 copy the
// owner's +0x68 state and draw. Shroud bytes +0x4A/+0x4B track the object's
// +0x274 owner and +0x438 bit 0.
// Donor facts: Zero Hour W3DModelDraw::doDrawModule supplies the spine
// (Set_Transform, handleClientTurretPositioning, the bone particle refresh
// 0x000C6E1A, handleClientRecoil); everything else is BFME 2 only.
#include <math.h>
#include "ascii_string.h"
#include "Coord3D.h"
#include "matrix3d.h"

#define SLOT(n) virtual void slot##n();

typedef float Real;
typedef unsigned int UnsignedInt;

class ThingTemplate
{
public:
	char m_pad00[0x122];
	unsigned char m_flags122;
};

class Rva000C8144Owner
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10)
	virtual bool rvaSlot11();
};

struct Rva000C8131Link
{
	char m_pad00[0x250];
	Rva000C8144Owner *m_owner;
};

class Object
{
public:
	Real getOrientation() const { return m_orientation; }
	char m_pad00[0x1C0];
	Real m_orientation;
	char m_pad1C4[0x274 - 0x1C4];
	Rva000C8131Link *m_link;
	char m_pad278[0x438 - 0x278];
	unsigned char m_flags438;
};

class Gen_0075EF90
{
public:
	Gen_0075EF90 &bfmeAssign(const Gen_0075EF90 &that);
};

class View;

class Drawable
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	Object *getObject() const { return m_object; }
	void draw(View *view);
	char m_pad00[0x04];
	const ThingTemplate *m_template;
	char m_pad08[0x68 - 0x08];
	Gen_0075EF90 *m_state68;
	char m_pad6C[0xFC - 0x6C];
	Object *m_object;
};

class Rva002716Holder
{
public:
	void Rva002716ACBroadcast();
};

class InGameUI
{
public:
	Real rva0029B3C1(const Object *obj) const;
};
extern InGameUI *TheInGameUI;

class View
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61) SLOT(62) SLOT(63)
	virtual Real getAngle();
};
extern View *TheTacticalView;

class GameClient
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	virtual Drawable *findDrawableByID(UnsignedInt id);
	SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30)
	virtual UnsignedInt getFrame();
};
extern GameClient *TheGameClient;

class GameLogic
{
public:
	bool isInMultiplayerGame();
};
extern GameLogic *TheGameLogic;

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct GlobalDataView
{
	char m_pad00[0xD45];
	bool m_flagD45;
};

class TerrainLogic
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18)
	virtual void rvaSlot19(Real x, Real y, Real *z, void *normal, int flags);
};
extern TerrainLogic *TheTerrainLogic;

class RvaSmartPtr12 { public: RvaSmartPtr12 &operator=(const RvaSmartPtr12 &) throw(); void rva0004CBC0() throw(); };
struct Rva001F3899Arg;
class Rva001F3899Slot { public: void set(const Rva001F3899Arg &arg); };
class Rva001F384AByteZeroSetter { public: void disable(); };
class ParticleSystem
{
public:
	void destroy();
};
ParticleSystem *Make001FCBD7();
class BfmeParticleSystemHandle
{
public:
	__forceinline ~BfmeParticleSystemHandle() { if (m_system) ((RvaSmartPtr12 *)this)->rva0004CBC0(); }
	__forceinline BfmeParticleSystemHandle &operator=(const BfmeParticleSystemHandle &that) { ((RvaSmartPtr12 *)this)->operator=(*(const RvaSmartPtr12 *)&that); return *this; }
	ParticleSystem *get() const
	{
		ParticleSystem *p = m_system;
		if (!p) return Make001FCBD7(); return p;
	}
	ParticleSystem *volatile m_system;
	void *m_prev;
	void *m_next;
};
class ParticleSystemTemplate;
class ParticleSystemManager
{
public:
	ParticleSystemTemplate *findTemplate(const AsciiString &name) const;
	BfmeParticleSystemHandle createParticleSystem(const ParticleSystemTemplate *tmpl, bool createSlaves);
};
extern ParticleSystemManager *TheParticleSystemManager;

class RenderObjClass
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20)
	virtual void Set_Transform(const Matrix3D &m);
};
bool Rva0010E676_SetEmissive(RenderObjClass *robj, float r, float g, float b);

class RadiusDecal { public: void update(); };

class W3DScriptedModelDraw { public: void rva000B710D(Matrix3D &mtx); void rva000BD6C2(); };
class Rva000BFDFE { public: void rva000C0386(); };
class Rva000B3B2BArg;
class Rva000B3B2B { public: void rva000B3B2B(Rva000B3B2BArg *robj); };

namespace _STL {
struct _Rb_tree_node_base
{
	int _M_color;
	_Rb_tree_node_base *_M_parent;
	_Rb_tree_node_base *_M_left;
	_Rb_tree_node_base *_M_right;
};
template <class _Dummy> struct _Rb_global
{
	static _Rb_tree_node_base *_M_increment(_Rb_tree_node_base *node);
};
}

struct DrawableIDNode : public _STL::_Rb_tree_node_base
{
	UnsignedInt m_id;
};

struct Rva000C7C35Flags
{
	bool test(int bit) const { return (m_bits >> bit) & 1; }
	UnsignedInt m_bits;
};

struct Rva000C8174Shroud
{
	char m_pad00[0x04];
	bool m_flag04;
	char m_pad05[0x34 - 0x05];
	int m_mode;
};

struct W3DModelDrawModuleData
{
	char m_pad00[0x14];
	AsciiString m_particleSysName;
	char m_pad18[0x69 - 0x18];
	bool m_bfmeFlag69;
	bool m_bfmeFlag6A;
	char m_pad6B[0x108 - 0x6B];
	bool m_flag108;
	char m_pad109[0x136 - 0x109];
	bool m_flag136;
	char m_pad137[0x15D - 0x137];
	bool m_multiplayerOnly;
	bool m_flag15E;
	bool m_flag15F;
};

class DrawModuleView
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26) SLOT(27) SLOT(28) SLOT(29) SLOT(30) SLOT(31)
	SLOT(32) SLOT(33) SLOT(34) SLOT(35) SLOT(36) SLOT(37) SLOT(38) SLOT(39)
	SLOT(40) SLOT(41) SLOT(42) SLOT(43) SLOT(44) SLOT(45) SLOT(46) SLOT(47)
	SLOT(48) SLOT(49) SLOT(50) SLOT(51) SLOT(52) SLOT(53) SLOT(54) SLOT(55)
	SLOT(56) SLOT(57) SLOT(58) SLOT(59) SLOT(60) SLOT(61)
	virtual void rvaSlot62();
protected:
	const W3DModelDrawModuleData *m_moduleData;	// 0x04
	Drawable *m_drawable;				// 0x08
};

class ObjectDrawInterfaceView
{
public:
	SLOT(00) SLOT(01) SLOT(02) SLOT(03) SLOT(04) SLOT(05) SLOT(06) SLOT(07)
	SLOT(08) SLOT(09) SLOT(10) SLOT(11) SLOT(12) SLOT(13) SLOT(14) SLOT(15)
	SLOT(16) SLOT(17) SLOT(18) SLOT(19) SLOT(20) SLOT(21) SLOT(22) SLOT(23)
	SLOT(24) SLOT(25) SLOT(26)
	virtual void rvaSlot27(bool enable);
	SLOT(28)
	virtual void rvaSlot29();
private:
	char m_pad04[0x10 - 0x04];
};

class W3DModelDraw : public DrawModuleView, public ObjectDrawInterfaceView
{
public:
	virtual void doDrawModule(const Matrix3D *transformMtx);
protected:
	const W3DModelDrawModuleData *getW3DModelDrawModuleData() const { return m_moduleData; }
	Drawable *getDrawable() const { return m_drawable; }
	void adjustTransformMtx(Matrix3D &mtx) { ((W3DScriptedModelDraw *)this)->rva000B710D(mtx); }
	void handleClientTurretPositioning();
	void handleClientRecoil();
	void rva000C6E1A();
	void rva000BD6C2() { ((W3DScriptedModelDraw *)this)->rva000BD6C2(); }
private:
	BfmeParticleSystemHandle m_particleSystem;	// 0x1C
	char m_pad28[0x4A - 0x28];
	bool m_flag4A;					// 0x4A
	bool m_hiddenByShroud;				// 0x4B
	char m_pad4C[0x50 - 0x4C];
	RenderObjClass *m_renderObject;			// 0x50
	char m_pad54[0x58 - 0x54];
	Rva000C8174Shroud *m_shroud;			// 0x58
	char m_pad5C[0x68 - 0x5C];
	int m_value68;					// 0x68
	int m_value6C;					// 0x6C
	char m_pad70[0x74 - 0x70];
	int m_value74;					// 0x74
	int m_value78;					// 0x78
	char m_pad7C[0xA0 - 0x7C];
	bool m_dirty;					// 0xA0
	char m_padA1[0xA4 - 0xA1];
	int m_valueA4;					// 0xA4
	DrawableIDNode *m_idHeader;			// 0xA8
	UnsignedInt m_idCount;				// 0xAC
	char m_padB0[0xBC - 0xB0];
	int m_valueBC;					// 0xBC
	char m_padC0[0x198 - 0xC0];
	Rva000C7C35Flags m_flags198;			// 0x198
	char m_pad19C[0x1C8 - 0x19C];
	bool m_flag1C8;					// 0x1C8
	bool m_flag1C9;					// 0x1C9
	char m_pad1CA[0x1D0 - 0x1CA];
	RadiusDecal m_decal;				// 0x1D0
	char m_pad1D1[0x270 - 0x1D1];
	bool m_emissiveFading;				// 0x270
	char m_pad271[0x274 - 0x271];
	UnsignedInt m_emissiveDuration;			// 0x274
	UnsignedInt m_emissiveElapsed;			// 0x278
	UnsignedInt m_emissiveLastFrame;		// 0x27C
	Real m_emissiveR;				// 0x280
	Real m_emissiveG;				// 0x284
	Real m_emissiveB;				// 0x288
};

template <class T> inline const T &minOf(const T &a, const T &b) { return b < a ? b : a; }

void W3DModelDraw::doDrawModule(const Matrix3D *transformMtx)
{
	if (!m_dirty && m_valueA4)
		return;

	const W3DModelDrawModuleData *d = getW3DModelDrawModuleData();
	if (d->m_multiplayerOnly)
	{
		if (!TheGameLogic->isInMultiplayerGame())
			return;
		if (((GlobalDataView *)TheWritableGlobalData)->m_flagD45)
			return;
	}
	if (d->m_flag15F && m_valueBC)
		return;

	m_dirty = false;

	const Rva000C7C35Flags *flags = &m_flags198;
	if (flags->test(15) && !((const StringBase<char> *)&d->m_particleSysName)->isEmpty())
	{
		Vector3 trans = transformMtx->Get_Translation();
		Coord3D pos = *(Coord3D *)&trans;
		TheTerrainLogic->rvaSlot19(pos.x, pos.y, &pos.z, 0, 0);
		if (m_particleSystem.m_system)
		{
			((Rva001F3899Slot *)m_particleSystem.get())->set(*(const Rva001F3899Arg *)&pos);
		}
		else
		{
			const ParticleSystemTemplate *tmpl = TheParticleSystemManager->findTemplate(d->m_particleSysName);
			if (tmpl)
			{
				m_particleSystem = TheParticleSystemManager->createParticleSystem(tmpl, true);
				if (m_particleSystem.m_system)
				{
					((Rva001F3899Slot *)m_particleSystem.get())->set(*(const Rva001F3899Arg *)&pos);
					((Rva001F384AByteZeroSetter *)m_particleSystem.get())->disable();
				}
			}
		}
	}
	else if (m_particleSystem.m_system)
	{
		m_particleSystem.get()->destroy();
		if (m_particleSystem.m_system)
		{
			((RvaSmartPtr12 *)&m_particleSystem)->rva0004CBC0();
			*(ParticleSystem **)&m_particleSystem = 0;
		}
	}

	((Rva000BFDFE *)this)->rva000C0386();

	if (m_renderObject)
	{
		Matrix3D mtx(true);
		if (getDrawable()->getTemplate()->m_flags122 & 1)
		{
			mtx.Set_Translation(transformMtx->Get_Translation());
			mtx.Rotate_Z(TheTacticalView->getAngle());
		}
		else if (!d->m_bfmeFlag69 && !d->m_bfmeFlag6A)
		{
			mtx = *transformMtx;
		}
		else
		{
			mtx.Set_Translation(transformMtx->Get_Translation());
			if (d->m_bfmeFlag6A)
			{
				Object *obj = getDrawable()->getObject();
				Real angle;
				if (TheInGameUI)
					angle = TheInGameUI->rva0029B3C1(obj);
				else
					angle = obj->getOrientation();
				mtx.Rotate_Z(angle);
			}
		}
		adjustTransformMtx(mtx);
		m_renderObject->Set_Transform(mtx);

		if (m_emissiveFading)
		{
			UnsignedInt now = TheGameClient->getFrame();
			UnsignedInt delta = now - m_emissiveLastFrame;
			m_emissiveLastFrame = now;
			UnsignedInt elapsed = m_emissiveElapsed + delta;
			m_emissiveElapsed = minOf(m_emissiveDuration, elapsed);
			Real ratio = (Real)m_emissiveElapsed / (Real)m_emissiveDuration;
			Rva0010E676_SetEmissive(m_renderObject, ratio * m_emissiveR, ratio * m_emissiveG, ratio * m_emissiveB);
			if (m_emissiveElapsed >= m_emissiveDuration)
				m_emissiveFading = false;
		}
	}

	handleClientTurretPositioning();
	rva000C6E1A();

	if (d->m_flag108)
		rvaSlot27(false);

	if (m_idCount)
	{
		for (_STL::_Rb_tree_node_base *node = m_idHeader->_M_left; node != m_idHeader;
			node = _STL::_Rb_global<bool>::_M_increment(node))
		{
			Drawable *other = TheGameClient->findDrawableByID(((DrawableIDNode *)node)->m_id);
			if (other)
			{
				if (getDrawable()->m_state68 && other->m_state68)
					other->m_state68->bfmeAssign(*getDrawable()->m_state68);
				((Rva002716Holder *)other)->Rva002716ACBroadcast();
				other->draw(0);
			}
		}
	}

	rvaSlot62();
	rva000BD6C2();

	Object *obj = getDrawable()->getObject();
	Rva000C8131Link *link;
	if (obj && (link = obj->m_link) != 0 && !d->m_flag136 && !link->m_owner->rvaSlot11())
	{
		if (!m_hiddenByShroud)
			m_hiddenByShroud = true;
	}
	else if (m_flag4A && m_hiddenByShroud)
	{
		m_hiddenByShroud = false;
	}
	if (obj && m_shroud && m_shroud->m_mode == 1 && (obj->m_flags438 & 1))
	{
		m_hiddenByShroud = true;
		m_shroud->m_flag04 = false;
	}

	if ((m_value74 != m_value78 && m_flag1C9) || (m_value68 != m_value6C && m_flag1C8))
		rvaSlot29();

	((Rva000B3B2B *)this)->rva000B3B2B((Rva000B3B2BArg *)m_renderObject);
	m_decal.update();
	handleClientRecoil();
}
