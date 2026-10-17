// ?Rva00173C04Skin@@YGXPAX0@Z
// partial score=0.359 date=2026-10-17
// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport's sort over 32-byte BfmeAssignRecord32 records with a comparator
// function pointer: sort (0x00174870, 67B) and its family 0x00173878 ..
// 0x001746C3. Target evidence: the median it calls is the function-pointer
// median folded at 0x004C6F77 (rowed by hand as Rva004C6F77Median), and every
// body copies, assigns and destroys records through the rowed out-of-line
// copy constructor (0x00173731), assignment (0x00173499) and destructor
// (0x0017330A). The inserts, heap adjust and insertion-sort pieces rowed
// in the stlport_bfmeassignrecord32_*.cpp units are this instantiation's
// bodies too.
//
// The record is declared as stlport_bfmeassignrecord32_insertion_sort.cpp
// declares it, with those three members out of line. The introsort loop's
// range test needs /G7.

struct Vector3 { float X, Y, Z; };
struct Vector2 { float U, V; };
class AsciiString;

// DynamicVectorClass<T> instance layout: vtable, then m_Array (0x4),
// m_ActiveCount (0x8), m_Length (0xc).
template <class T>
class DynamicVectorClass
{
public:
	void *m_VTable;
	T *m_Array;
	int m_ActiveCount;
	int m_Length;
	void Resize(int, T const *);
	T &operator[](int);
};

// Mesh geometry / material descriptor shape used by the skinning loop.
class MeshMatDescClass
{
public:
	virtual void *_vf0();
	virtual void *_vf1();
	virtual Vector2 *Get_UV_Array(int, int);
	void *m_VertexMaterialClass;   // 0x0
	int m_PassCount;               // 0x4
	int m_UV1Count;                // 0xc
	void *m_UV1Array;              // 0x10
	void *m_UV2Array;              // 0x14
	char _pad[0x50 - 0x18];
	void *m_ColorArray;            // 0x50
};

class MeshGeometryClass
{
public:
	virtual const char *Get_Name();
	void *m_pMaterialDesc;         // 0x94
};

class MeshClass
{
public:
	MeshGeometryClass *Peek_Geometry();   // vtable +0x28
	void Get_Deformed_Vertices(Vector3 *, Vector3 *);
	void *m_pGeometry;                    // 0xc4
};

class Debug_Statistics
{
public:
	static void Record_DX8_Skin_Polys_And_Vertices(int, int);
};

struct SkinVertex
{
	Vector3 Position;   // 0x00
	Vector3 Normal;     // 0x0c
	int BoneIndex;      // 0x18
	Vector2 UV1;        // 0x1c
	Vector2 UV2;        // 0x24
};

class AsciiString
{
public:
	AsciiString(const char *);
	~AsciiString();
	char *_p;
};
extern DynamicVectorClass<Vector3> _SkinNormals;
extern DynamicVectorClass<Vector3> _SkinVertices;

// 0x00173C04
void __stdcall Rva00173C04Skin(void *mesh, void *verts)
{
	MeshClass *m = (MeshClass *)mesh;
	SkinVertex *out = (SkinVertex *)verts;

	static AsciiString s1("skin1");
	static AsciiString s2("skin2");
	MeshGeometryClass *geo = (MeshGeometryClass *)*(void **)((char *)m + 0xc4);
	int count = *(int *)((char *)m + 0xc4);
	(void)count;
	int _padframe[3];
	*(volatile int *)&_padframe[0] = 0;
	*(volatile int *)&_padframe[1] = 0;

	int vertCount = *(int *)((char *)geo + 0x28);
	Debug_Statistics::Record_DX8_Skin_Polys_And_Vertices((int)geo, (vertCount ? vertCount : vertCount));

	if (_SkinVertices.m_ActiveCount < vertCount)
		_SkinVertices.Resize(vertCount, 0);
	if (_SkinNormals.m_ActiveCount < vertCount)
		_SkinNormals.Resize(vertCount, 0);

	MeshMatDescClass *desc = (MeshMatDescClass *)geo->m_pMaterialDesc;

	Vector2 *uv1 = 0;
	if ((desc->m_UV1Count ? desc->m_UV1Count : 0) != 0)
		uv1 = desc->Get_UV_Array(0, 0);
	else if (desc->m_UV1Array != 0)
		uv1 = (Vector2 *)*((void **)((char *)desc->m_UV1Array + 0xc));

	Vector2 *uv2 = 0;
	if ((desc->m_UV1Count ? desc->m_UV1Count : 0) != 0)
		uv2 = desc->Get_UV_Array(0, 1);
	else if (desc->m_UV2Array != 0)
		uv2 = (Vector2 *)*((void **)((char *)desc->m_UV2Array + 0xc));

	int *boneIdx = 0;
	if ((desc->m_ColorArray ? 1 : 1) != 0 && desc->m_ColorArray != 0)
		boneIdx = (int *)*((void **)((char *)desc->m_ColorArray + 0xc));

	m->Get_Deformed_Vertices(_SkinVertices.m_Array, _SkinNormals.m_Array);

	Vector3 *vp = _SkinVertices.m_Array;
	Vector3 *np = _SkinNormals.m_Array;

	for (int i = 0; i < vertCount; i++)
	{
		out->Position = *vp;
		out->Normal = *np;

		if (boneIdx)
		{
			out->BoneIndex = *boneIdx;
			boneIdx++;
		}
		else
		{
			out->BoneIndex = -1;
		}

		if (uv1)
		{
			out->UV1 = *uv1;
			uv1++;
		}
		else
		{
			out->UV1.U = 0.0f;
			out->UV1.V = 0.0f;
		}

		if (uv2)
		{
			out->UV2 = *uv2;
			uv2++;
		}
		else
		{
			out->UV2.U = 0.0f;
			out->UV2.V = 0.0f;
		}

		vp++;
		np++;
		out++;
	}
}
