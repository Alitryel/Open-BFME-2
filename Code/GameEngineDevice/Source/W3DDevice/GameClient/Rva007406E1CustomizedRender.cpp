// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Address-derived scene CustomizedRender, retail 0x007406E1..0x00740A45
// (868 bytes, EH, ret 4, WB 0x017EEF90 names View3D::CustomizedRender).
// Scene layout: ambient Vector3 +0x08, render/update multi-list +0x60,
// light multi-list +0x90; render-info light environment +0x28 and camera
// transform +0x18 agree with the landed 0x0009C9DE body.
// Body: clear the frame, per-frame-update the +0x60 list, clear lights 0-3,
// lazily build the function-local static light environment from the ambient
// and the +0x90 light list, apply render-state changes, set ZFUNC ALWAYS /
// ZWRITE off / ZENABLE off, render the +0x60 list, flush 0x001173F0, then
// restore ZWRITE on / ZFUNC ALWAYS. Callees are the rowed DX8Wrapper and
// LightEnvironmentClass providers; no new pins.
typedef unsigned long DWORD;
typedef long HRESULT;
typedef DWORD D3DRENDERSTATETYPE;
typedef int Int;

struct IDirect3DDevice8
{
#define G(n) virtual void __stdcall s##n() = 0;
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09)
	G(10) G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19)
	G(20) G(21) G(22) G(23) G(24) G(25) G(26) G(27) G(28) G(29)
	G(30) G(31) G(32) G(33) G(34) G(35) G(36) G(37) G(38) G(39)
	G(40) G(41) G(42) G(43) G(44) G(45) G(46) G(47) G(48) G(49)
	G(50) G(51) G(52) G(53) G(54) G(55) G(56)
#undef G
	virtual HRESULT __stdcall SetRenderState(D3DRENDERSTATETYPE state, DWORD value) = 0; // 57
};

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	~StringClass() { Free_String(); }
private:
	char *m_Buffer;
	void Free_String();
};

struct _D3DLIGHT8;
class Vector3;

extern unsigned number_of_DX8_calls;

class WW3D
{
public:
	static bool Is_Snapshot_Activated(void) { return SnapshotActivated; }
	static void Flush(class RenderInfoClass &rinfo);
private:
	static bool SnapshotActivated;
};

class DX8Wrapper
{
public:
	static void Set_Light(unsigned index, const _D3DLIGHT8 *light);
	static void Clear(bool clear_color, bool clear_z_stencil, bool clear_stencil, const Vector3 &color, float dest_alpha, float z, unsigned stencil);
	static void Apply_Render_State_Changes(void);
	static void Get_DX8_Render_State_Value_Name(StringClass &name, D3DRENDERSTATETYPE state, unsigned value);

	static __forceinline void Set_DX8_Render_State(D3DRENDERSTATETYPE state, unsigned value)
	{
		if (RenderStates[state] == value) return;
		if (WW3D::Is_Snapshot_Activated()) {
			StringClass value_name(0, true);
			Get_DX8_Render_State_Value_Name(value_name, state, value);
		}
		RenderStates[state] = value;
		D3DDevice->SetRenderState(state, value);
		number_of_DX8_calls++;
		render_state_changes++;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned RenderStates[256];
	static unsigned render_state_changes;
};

class Vector3
{
public:
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	float X, Y, Z;
};

class Matrix3D
{
public:
	float Row[3][4];
};

class CameraClass
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09)
	G(10) G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19)
#undef G
	virtual void Validate_Transform(void) const; // 20
	const Matrix3D &Get_Transform(void) const { Validate_Transform(); return Transform; }
private:
	char m_pad04[0x18 - 0x04];
	Matrix3D Transform; // +0x18
};

class LightEnvironmentClass;

class RenderInfoClass
{
public:
	CameraClass &Camera;
	char m_pad04[0x28 - 0x04];
	LightEnvironmentClass *light_environment; // +0x28
};

class RefCountClassView
{
public:
	virtual void rc00();
	int NumRefs;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();
	void *ListNode;
};

struct MultiListNodeClass
{
	MultiListNodeClass *Prev;
	MultiListNodeClass *Next;
	MultiListNodeClass *NextList;
	MultiListObjectClass *Object;
};

class GenericMultiListClass
{
public:
	virtual ~GenericMultiListClass();
	MultiListNodeClass Head;
	int m_extra;
};

class GenericMultiListIterator
{
public:
	GenericMultiListIterator(GenericMultiListClass *list) { First(list); }
	void First(GenericMultiListClass *list) { List = list; CurNode = List->Head.Next; }
	void First(void) { CurNode = List->Head.Next; }
	__declspec(dllimport) __forceinline void Next(void) { CurNode = CurNode->Next; }
	bool Is_Done(void) { return (CurNode == &(List->Head)); }
protected:
	MultiListObjectClass *Current_Object(void) { return CurNode->Object; }
	GenericMultiListClass *List;
	MultiListNodeClass *CurNode;
};

class RenderObjClass : public RefCountClassView, public MultiListObjectClass
{
public:
#define G(n) virtual void v##n();
	G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10) G(11)
#undef G
	virtual void Render(RenderInfoClass &rinfo); // 12
	virtual void On_Frame_Update(void); // 13
#define G(n) virtual void v##n();
	G(14) G(15) G(16) G(17) G(18) G(19) G(20) G(21) G(22) G(23) G(24)
	G(25) G(26) G(27) G(28) G(29) G(30) G(31) G(32) G(33) G(34) G(35)
	G(36) G(37) G(38) G(39) G(40) G(41) G(42) G(43) G(44) G(45) G(46)
	G(47) G(48) G(49) G(50) G(51) G(52) G(53) G(54) G(55) G(56) G(57)
	G(58) G(59) G(60) G(61) G(62) G(63) G(64) G(65) G(66) G(67) G(68)
	G(69) G(70) G(71) G(72) G(73) G(74) G(75) G(76) G(77) G(78) G(79)
	G(80) G(81) G(82) G(83) G(84) G(85) G(86) G(87) G(88) G(89) G(90)
	G(91) G(92) G(93) G(94) G(95)
#undef G
	virtual int Is_Really_Visible(void); // 96
};

class LightClass : public RenderObjClass
{
};

class RefRenderObjListIterator : public GenericMultiListIterator
{
public:
	__declspec(dllimport) __forceinline RefRenderObjListIterator(GenericMultiListClass *list) : GenericMultiListIterator(list) {}
	RenderObjClass *Peek_Obj(void) { return ((RenderObjClass *)Current_Object()); }
};


class BfmeVecHF;
class Gen_0094AC70
{
public:
	void bfmeSetPair(const BfmeVecHF *center, const BfmeVecHF *ambient);
};

class LightEnvironmentClass
{
public:
	LightEnvironmentClass();
	__forceinline void Reset(const Vector3 &object_center, const Vector3 &scene_ambient)
	{
		reinterpret_cast<Gen_0094AC70 *>(this)->bfmeSetPair(
			reinterpret_cast<const BfmeVecHF *>(&object_center),
			reinterpret_cast<const BfmeVecHF *>(&scene_ambient));
	}
	~LightEnvironmentClass();
	void Add_Light(const LightClass &light);
	void Pre_Render_Update(const Matrix3D &camera_tm);
private:
	char m_data[0x228];
};

class W3DShadowManager
{
public:
	void queueShadows(bool state) { m_isShadowScene = state; }
private:
	bool m_isShadowScene;
};
extern W3DShadowManager *TheW3DShadowManager;

class Rva0009A361
{
public:
	void rva0009A361(Int rinfo);
};

class Rva0009C983
{
public:
	void rva0009C983(Int rinfo);
};

class DisplayPass
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10)
	G(11) G(12) G(13) G(14) G(15) G(16) G(17) G(18) G(19) G(20) G(21)
#undef G
	virtual void begin(CameraClass *camera); // 22
	virtual void end(void); // 23
};

class Display
{
public:
	char m_pad00[0x2C];
	DisplayPass *m_2C; // +0x2C
};
extern Display *TheDisplay;

class ParticleSystemManager
{
public:
#define G(n) virtual void v##n();
	G(00) G(01) G(02) G(03) G(04) G(05) G(06) G(07) G(08) G(09) G(10)
	G(11) G(12) G(13) G(14) G(15)
#undef G
	virtual void doParticles(RenderInfoClass &rinfo); // 16
	virtual void v17();
	virtual void queueParticleRender(void); // 18
};
extern ParticleSystemManager *TheParticleSystemManager;

void rva001173f0(unsigned rinfo);


class Rva007406E1
{
public:
	void rva007406E1(RenderInfoClass &rinfo);

private:
	char m_00[8];
	Vector3 m_ambientLight;										// +0x08
	char m_14[0x5C - 0x14];
	GenericMultiListClass m_renderList;							// +0x5C (multi-list head +0x60)
	char m_renderPad[0x8C - (0x5C + sizeof(GenericMultiListClass))];
	GenericMultiListClass m_lightList;							// +0x8C (multi-list head +0x90)
};

void Rva007406E1::rva007406E1(RenderInfoClass &rinfo)
{
	DX8Wrapper::Clear(false, true, true, Vector3(0, 0, 0), 0.0f, 1.0f, 0);

	RefRenderObjListIterator it(&m_renderList);
	for (it.First(); !it.Is_Done(); it.Next())
		it.Peek_Obj()->On_Frame_Update();

	DX8Wrapper::Set_Light(0, 0);
	DX8Wrapper::Set_Light(1, 0);
	DX8Wrapper::Set_Light(2, 0);
	DX8Wrapper::Set_Light(3, 0);

	if (!rinfo.light_environment) {
		static LightEnvironmentClass lenv;
		Vector3 zero(0, 0, 0);
		lenv.Reset(zero, m_ambientLight);
		for (it.First(&m_lightList); !it.Is_Done(); it.Next())
			lenv.Add_Light(*(LightClass *)it.Peek_Obj());
		lenv.Pre_Render_Update(rinfo.Camera.Get_Transform());
		rinfo.light_environment = &lenv;
	}

	DX8Wrapper::Apply_Render_State_Changes();
	DX8Wrapper::Set_DX8_Render_State(0x17, 8);
	DX8Wrapper::Set_DX8_Render_State(0xe, 0);
	DX8Wrapper::Set_DX8_Render_State(7, 0);

	for (it.First(&m_renderList); !it.Is_Done(); it.Next())
		it.Peek_Obj()->Render(rinfo);

	rva001173f0((unsigned)&rinfo);
	DX8Wrapper::Set_DX8_Render_State(0xe, 1);
	DX8Wrapper::Set_DX8_Render_State(0x17, 8);
}
