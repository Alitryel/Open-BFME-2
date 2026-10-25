// cl: /O1 /MD
//
// ?clientOnly_getRenderObjInfo@Rva000B34D8@@QAE_NPAVVector3@@PAMPAURva000B34D8Out30@@@Z @0x000B34D8 151B:
// // guarded fetch via +0x44 RenderObjClass provider. Null yields false;
// // else Get_Position Vector3 to out0, out2 0x30B via slot20, float via
// // slot65 Ret+0xC to out1, true. Proven Get_Position; provider layout
// // (+0x18 float, +0x1C..+0x44 ints, slots 20/65) read from target
// // bytes; honest address-derived Out30/Ret65; boundary verified
// // (frame at 0xB34D8, ret 0xC abutting 0xB356F).

class Vector3 { public: float x; float y; float z; };
struct Rva000B34D8Out30 { float f00; int m04; int m08; int m0C; int m10; int m14; int m18; int m1C; int m20; int m24; int m28; int m2C; };
struct Rva000B34D8Ret65 { char m_pad00[0x0C]; float m_radius; };
class RenderObjClass { public:
	Vector3 Get_Position() const;
	virtual void vslot000();
	virtual void vslot001();
	virtual void vslot002();
	virtual void vslot003();
	virtual void vslot004();
	virtual void vslot005();
	virtual void vslot006();
	virtual void vslot007();
	virtual void vslot008();
	virtual void vslot009();
	virtual void vslot010();
	virtual void vslot011();
	virtual void vslot012();
	virtual void vslot013();
	virtual void vslot014();
	virtual void vslot015();
	virtual void vslot016();
	virtual void vslot017();
	virtual void vslot018();
	virtual void vslot019();
	virtual void vslot020();
	virtual void vslot021();
	virtual void vslot022();
	virtual void vslot023();
	virtual void vslot024();
	virtual void vslot025();
	virtual void vslot026();
	virtual void vslot027();
	virtual void vslot028();
	virtual void vslot029();
	virtual void vslot030();
	virtual void vslot031();
	virtual void vslot032();
	virtual void vslot033();
	virtual void vslot034();
	virtual void vslot035();
	virtual void vslot036();
	virtual void vslot037();
	virtual void vslot038();
	virtual void vslot039();
	virtual void vslot040();
	virtual void vslot041();
	virtual void vslot042();
	virtual void vslot043();
	virtual void vslot044();
	virtual void vslot045();
	virtual void vslot046();
	virtual void vslot047();
	virtual void vslot048();
	virtual void vslot049();
	virtual void vslot050();
	virtual void vslot051();
	virtual void vslot052();
	virtual void vslot053();
	virtual void vslot054();
	virtual void vslot055();
	virtual void vslot056();
	virtual void vslot057();
	virtual void vslot058();
	virtual void vslot059();
	virtual void vslot060();
	virtual void vslot061();
	virtual void vslot062();
	virtual void vslot063();
	virtual void vslot064();
	virtual Rva000B34D8Ret65 *vslot065();
public:
	char m_pad04[0x18 - 4];
	float f18; int m1C; int m20; int m24; int m28; int m2C; int m30; int m34; int m38; int m3C; int m40; int m44;
};
// A one-slot draw interface: W3DScriptedModelDraw's +0x0C base, whose vtable
// slot 0 is this function (also inherited unchanged by W3DTankDraw/W3DTruckDraw).
class Rva000B34D8 { public: virtual bool clientOnly_getRenderObjInfo(Vector3 *pos, float *boundingSphereRadius, Rva000B34D8Out30 *transform); private: char m_pad04[0x44 - 4]; RenderObjClass *m_44; };
bool Rva000B34D8::clientOnly_getRenderObjInfo(Vector3 *pos, float *boundingSphereRadius, Rva000B34D8Out30 *transform) {
	if (!m_44) return false;
	*pos = m_44->Get_Position();
	RenderObjClass *renderObj = m_44;
	renderObj->vslot020();
	transform->f00 = renderObj->f18;
	transform->m04 = renderObj->m1C;
	transform->m08 = renderObj->m20;
	transform->m0C = renderObj->m24;
	transform->m10 = renderObj->m28;
	transform->m14 = renderObj->m2C;
	transform->m18 = renderObj->m30;
	transform->m1C = renderObj->m34;
	transform->m20 = renderObj->m38;
	transform->m24 = renderObj->m3C;
	transform->m28 = renderObj->m40;
	transform->m2C = renderObj->m44;
	Rva000B34D8Ret65 *r = m_44->vslot065();
	*boundingSphereRadius = r->m_radius;
	return true;
}
