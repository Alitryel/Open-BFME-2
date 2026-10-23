// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Target 0x0006B895..0x0006BBD9, RET 4 (836 bytes), and 0x0006BBD9..0x0006BE05,
// RET 8 (556 bytes). BaseHeightMapRenderObjClass
// draw step for the two vegetation buffers: the tree buffer at +0x3850 under a
// "Frame"/"RenderTrees" render-event scope and the shrub buffer at +0x3854
// under "RenderShrubs", each after loading the object's own transform (+0x18)
// as the DX8 world matrix. Receiver evidence: +0x3850/+0x3854 are the buffers
// whose per-frame updates 0x000EC9C6 / 0x000E89BD are rowed, and the
// neighbouring 0x0006B804 uses the same receiver. WB's unnamed twin is
// 12 KB because it keeps DX8Wrapper::Set_Transform and Set_DX8_Render_State
// out of line; the retail copy has them inlined, as the world-matrix store
// at 0x00DEE7C4 and the render-state check at 0x00DED5F8 + 4 * state show.
// The second step ("RenderBuffs") loads the same transform through ZH's
// inline DX8Wrapper::Set_Transform(D3DTS_WORLD, Matrix3D) (Matrix4x4 staging
// copy, transposed into render_state.world), installs the vertex material at
// +0x3818 through the inlined Set_Material and hands both arguments to the
// buff buffer at +0x3874: its draw body 0x000D28FA follows the rowed
// W3DBuffBuffer fill 0x000D2301 and calls it at 0x000D3744.
// The target identity of the receiver method names is unknown.

typedef int Int;
typedef float Real;
typedef bool Bool;

class StringClass {
 char *m_Buffer; static char *m_EmptyString; static char m_NullChar;
 void Free_String();
public:
 StringClass(int n=0,bool temporary=false);
 __forceinline ~StringClass() { Free_String(); }
};

class BFME2ScopedRenderEvent
{
	char Label[256];
	char Group[64];
public:
	BFME2ScopedRenderEvent(const char *label, const char *group, unsigned color);
	~BFME2ScopedRenderEvent();
};

class VertexMaterialClass
{
public:
	virtual void Delete_This();
	int refs;
	void Release_Ref()
	{
		if (!--refs)
			Delete_This();
	}
};
extern VertexMaterialClass *ScreenMaterial;

struct IDirect3DDevice8;
struct DeviceVtable
{
	char pad[0xb0];
	int (__stdcall *SetTransform)(IDirect3DDevice8 *, int, const void *);
	char pad_b4[0xe4 - 0xb4];
	int (__stdcall *SetRenderState)(IDirect3DDevice8 *, unsigned long, unsigned);
};
struct IDirect3DDevice8
{
	DeviceVtable *v;
};
extern unsigned number_of_DX8_calls;
class Matrix4 { public: float Row[16]; };
struct Rva00726290Matrix4;
__forceinline void Rva0006BBD9SetWorld(const Rva00726290Matrix4 &);
struct RenderStateStruct { unsigned shader; char m_pad04[0x1E8]; Matrix4 world; };
class WW3D { friend class BaseHeightMapRenderObjClass; static bool SnapshotActivated; };
struct Rva00726290Matrix3D;
__forceinline void Rva00726290SetWorld(const Rva00726290Matrix3D &);

class DX8Wrapper
{
 friend class BaseHeightMapRenderObjClass;
 friend void Rva00726290SetWorld(const Rva00726290Matrix3D &);
 friend void Rva0006BBD9SetWorld(const Rva00726290Matrix4 &);
 friend void BfmeSetTransform(int, const class BfmeMatrix3D &);
protected:
 static unsigned render_state_changed, RenderStates[256], render_state_changes, matrix_changes;
 static RenderStateStruct render_state;
 static IDirect3DDevice8 *D3DDevice;
public:
	static void Get_DX8_Render_State_Value_Name(StringClass &, unsigned long, unsigned int);
};

struct Rva00726290Matrix3D
{
	Real row[12];
};

__forceinline void Rva00726290SetWorld(const Rva00726290Matrix3D &m)
{
	DX8Wrapper::render_state.world.Row[0] = m.row[0];
	DX8Wrapper::render_state.world.Row[1] = m.row[4];
	DX8Wrapper::render_state.world.Row[2] = m.row[8];
	DX8Wrapper::render_state.world.Row[3] = 0.0f;
	DX8Wrapper::render_state.world.Row[4] = m.row[1];
	DX8Wrapper::render_state.world.Row[5] = m.row[5];
	DX8Wrapper::render_state.world.Row[6] = m.row[9];
	DX8Wrapper::render_state.world.Row[7] = 0.0f;
	DX8Wrapper::render_state.world.Row[8] = m.row[2];
	DX8Wrapper::render_state.world.Row[9] = m.row[6];
	DX8Wrapper::render_state.world.Row[10] = m.row[10];
	DX8Wrapper::render_state.world.Row[11] = 0.0f;
	DX8Wrapper::render_state.world.Row[12] = m.row[3];
	DX8Wrapper::render_state.world.Row[13] = m.row[7];
	DX8Wrapper::render_state.world.Row[14] = m.row[11];
	DX8Wrapper::render_state.world.Row[15] = 1.0f;
	DX8Wrapper::render_state_changed = (DX8Wrapper::render_state_changed & 0xfffbffff) | 1;
}

struct Rva00726290Matrix4
{
	Real row[16];
};

__forceinline void Rva0006BBD9SetWorld(const Rva00726290Matrix4 &m)
{
	DX8Wrapper::render_state.world.Row[0] = m.row[0];
	DX8Wrapper::render_state.world.Row[1] = m.row[4];
	DX8Wrapper::render_state.world.Row[2] = m.row[8];
	DX8Wrapper::render_state.world.Row[3] = m.row[12];
	DX8Wrapper::render_state.world.Row[4] = m.row[1];
	DX8Wrapper::render_state.world.Row[5] = m.row[5];
	DX8Wrapper::render_state.world.Row[6] = m.row[9];
	DX8Wrapper::render_state.world.Row[7] = m.row[13];
	DX8Wrapper::render_state.world.Row[8] = m.row[2];
	DX8Wrapper::render_state.world.Row[9] = m.row[6];
	DX8Wrapper::render_state.world.Row[10] = m.row[10];
	DX8Wrapper::render_state.world.Row[11] = m.row[14];
	DX8Wrapper::render_state.world.Row[12] = m.row[3];
	DX8Wrapper::render_state.world.Row[13] = m.row[7];
	DX8Wrapper::render_state.world.Row[14] = m.row[11];
	DX8Wrapper::render_state.world.Row[15] = m.row[15];
	DX8Wrapper::render_state_changed = (DX8Wrapper::render_state_changed & 0xfffbffff) | 1;
}

#define BFME_SET_RS(state_, value_) do { \
	if (DX8Wrapper::RenderStates[(state_)] != (unsigned)(value_)) { \
		if (WW3D::SnapshotActivated) { \
			StringClass valueName(0, true); \
			DX8Wrapper::Get_DX8_Render_State_Value_Name(valueName, (state_), (value_)); \
		} \
		DX8Wrapper::RenderStates[(state_)] = (value_); \
		DX8Wrapper::D3DDevice->v->SetRenderState(DX8Wrapper::D3DDevice, (state_), (value_)); \
		++number_of_DX8_calls; \
		++DX8Wrapper::render_state_changes; \
	} \
} while (0)

class GlobalData;
extern GlobalData *TheWritableGlobalData;

class RenderInfoClass;
class Rva000EC9C6 { public: void rva000EC9C6(int); };
class W3DShrubBuffer { public: void drawShrubs(int); };
class W3DBuffBuffer { public: void rva000D28FA(RenderInfoClass &rinfo, bool flag); };

class BaseHeightMapRenderObjClass
{
public:
	void rva0006B895(RenderInfoClass &rinfo);
	void rva0006BBD9(int a, int b);
	void rva000687EF();

private:
	char m_pad00[0x18];
	Rva00726290Matrix3D m_transform;	// +0x18
	char m_pad48[0x78 - 0x48];
	int m_78;
	char m_pad7C[0x37C0 - 0x7C];
	int m_37C0;
	char m_pad37C4[0x3818 - 0x37C4];
	VertexMaterialClass *m_material;	// +0x3818
	char m_pad381C[0x3850 - 0x381C];
	Rva000EC9C6 *m_treeBuffer;
	W3DShrubBuffer *m_shrubBuffer;
	char m_pad3858[0x3874 - 0x3858];
	W3DBuffBuffer *m_buffBuffer;	// +0x3874
};

class BfmeVector4
{
public:
	Real X, Y, Z, W;
	__forceinline BfmeVector4() {}
	__forceinline BfmeVector4(const BfmeVector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; }
	__forceinline BfmeVector4 &operator=(const BfmeVector4 &v) { X = v.X; Y = v.Y; Z = v.Z; W = v.W; return *this; }
	__forceinline BfmeVector4(Real x, Real y, Real z, Real w) { X = x; Y = y; Z = z; W = w; }
	__forceinline Real &operator[](int i) { return (&X)[i]; }
	__forceinline const Real &operator[](int i) const { return (&X)[i]; }
};

class BfmeMatrix3D
{
public:
	BfmeVector4 Row[3];
	__forceinline BfmeMatrix3D(const BfmeMatrix3D &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; }
	__forceinline const BfmeVector4 &operator[](int i) const { return Row[i]; }
};

class BfmeMatrix4x4
{
public:
	BfmeVector4 Row[4];
	__forceinline BfmeMatrix4x4(const BfmeMatrix4x4 &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3]; }
	__forceinline BfmeMatrix4x4 &operator=(const BfmeMatrix4x4 &m) { Row[0] = m.Row[0]; Row[1] = m.Row[1]; Row[2] = m.Row[2]; Row[3] = m.Row[3]; return *this; }
	__forceinline explicit BfmeMatrix4x4(const BfmeMatrix3D &m) { Init(m); }
	__forceinline BfmeMatrix4x4(const BfmeVector4 &r0, const BfmeVector4 &r1, const BfmeVector4 &r2, const BfmeVector4 &r3) { Init(r0, r1, r2, r3); }
	__forceinline void Init(const BfmeMatrix3D &m) { Row[0] = m[0]; Row[1] = m[1]; Row[2] = m[2]; Row[3] = BfmeVector4(0.0f, 0.0f, 0.0f, 1.0f); }
	__forceinline void Init(const BfmeVector4 &r0, const BfmeVector4 &r1, const BfmeVector4 &r2, const BfmeVector4 &r3) { Row[0] = r0; Row[1] = r1; Row[2] = r2; Row[3] = r3; }
	__forceinline BfmeMatrix4x4 Transpose() const
	{
		return BfmeMatrix4x4(
			BfmeVector4(Row[0][0], Row[1][0], Row[2][0], Row[3][0]),
			BfmeVector4(Row[0][1], Row[1][1], Row[2][1], Row[3][1]),
			BfmeVector4(Row[0][2], Row[1][2], Row[2][2], Row[3][2]),
			BfmeVector4(Row[0][3], Row[1][3], Row[2][3], Row[3][3]));
	}
};

// DX8Wrapper::Set_Transform(D3DTRANSFORMSTATETYPE, const Matrix3D &), the
// inline ZH overload: the Matrix4x4 staging copy has its address taken by the
// generic case, which is why retail keeps all sixteen of its stores.
__forceinline void BfmeSetTransform(int transform, const BfmeMatrix3D &m)
{
	BfmeMatrix4x4 m2(m);
	switch (transform) {
	case 256:
		*(BfmeMatrix4x4 *)&DX8Wrapper::render_state.world = m2.Transpose();
		DX8Wrapper::render_state_changed |= 1u;
		DX8Wrapper::render_state_changed &= ~0x40000u;
		break;
	default:
		DX8Wrapper::matrix_changes++;
		m2 = m2.Transpose();
		DX8Wrapper::D3DDevice->v->SetTransform(DX8Wrapper::D3DDevice, transform, &m2);
		number_of_DX8_calls++;
		break;
	}
}

class RtsTreeBufferView { public: char pad[0x45c5c]; unsigned char m_45C5C; };

void BaseHeightMapRenderObjClass::rva0006B895(RenderInfoClass &rinfo)
{
	if (m_37C0 == 0 || m_78 == 0 || ((const unsigned char *)TheWritableGlobalData)[0x3f] == 0)
		return;

	if (m_treeBuffer != 0) {
		BFME2ScopedRenderEvent event("RenderTrees", "Frame", 0);
		Rva00726290Matrix3D world;
		world.row[0] = m_transform.row[0];
		world.row[1] = m_transform.row[1];
		world.row[2] = m_transform.row[2];
		world.row[3] = m_transform.row[3];
		world.row[4] = m_transform.row[4];
		world.row[5] = m_transform.row[5];
		world.row[6] = m_transform.row[6];
		world.row[7] = m_transform.row[7];
		world.row[8] = m_transform.row[8];
		world.row[9] = m_transform.row[9];
		world.row[10] = m_transform.row[10];
		world.row[11] = m_transform.row[11];
		Rva00726290SetWorld(world);
		m_treeBuffer->rva000EC9C6((Int)&rinfo);
		if (((RtsTreeBufferView *)m_treeBuffer)->m_45C5C != 0)
			rva000687EF();
	}

	if (m_shrubBuffer != 0) {
		BFME2ScopedRenderEvent event("RenderShrubs", "Frame", 0);
		Rva00726290Matrix3D world;
		world.row[0] = m_transform.row[0];
		world.row[1] = m_transform.row[1];
		world.row[2] = m_transform.row[2];
		world.row[3] = m_transform.row[3];
		world.row[4] = m_transform.row[4];
		world.row[5] = m_transform.row[5];
		world.row[6] = m_transform.row[6];
		world.row[7] = m_transform.row[7];
		world.row[8] = m_transform.row[8];
		world.row[9] = m_transform.row[9];
		world.row[10] = m_transform.row[10];
		world.row[11] = m_transform.row[11];
		Rva00726290SetWorld(world);
		BFME_SET_RS(0x34, 0);
		m_shrubBuffer->drawShrubs((Int)&rinfo);
	}
}

void BaseHeightMapRenderObjClass::rva0006BBD9(int a, int b)
{
	if (m_37C0 == 0 || m_78 == 0 || m_buffBuffer == 0)
		return;

	BFME2ScopedRenderEvent event("RenderBuffs", "Frame", 0);
	BfmeMatrix3D tm(*(const BfmeMatrix3D *)&m_transform);
	BfmeSetTransform(256, tm);

	VertexMaterialClass *material = m_material;
	if (material)
		++material->refs;
	if (ScreenMaterial)
		ScreenMaterial->Release_Ref();
	ScreenMaterial = material;
	DX8Wrapper::render_state_changed |= 0x4000;
	m_buffBuffer->rva000D28FA(*(RenderInfoClass *)a, *(bool *)&b);
}
