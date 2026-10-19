// ?rva00173C04@FXShaderRenderer@@QAEXPAVRva0017368AMesh@@PAX@Z
// partial score=0.7 date=2026-10-19
// cl: /O1 /arch:SSE /G7 /EHsc /MD
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
// DynamicVectorClass<T> instance layout: vtable, then m_Array (0x4),
// m_ActiveCount (0x8), m_Length (0xc).
// Mesh geometry / material descriptor shape used by the skinning loop.
// 0x0
// 0x4
// 0xc
// 0x10
// 0x14
// 0x50
// 0x94
// vtable +0x28
// 0xc4
// 0x00
// 0x0c
// 0x18
// 0x1c
// 0x24
// 0x00173C04

// The inherited farm comments describe its earlier, unverified declarations.
// Target evidence and the corrected declarations below supersede those layouts.
// Evidence: reverse/attempt_support/00173c04-20261019.md.
// The method name is address-derived; the cache element type is donor-guided.
class Vector3 { public: float X, Y, Z; };
class Vector2 { public: float U, V; };
template<class T> class VectorClass
{
public:
    virtual ~VectorClass();
    virtual bool operator==(const VectorClass &) const;
    virtual bool Resize(int,const T *);
    virtual void Clear();
    virtual int ID(const T *);
    virtual int ID(const T &);
    T &operator[](int index) { return array[index]; }
    int Length() const { return length; }
protected:
    T *array;
    int length;
    bool valid,allocated,pad[2];
};
template<class T> class DynamicVectorClass : public VectorClass<T>
{
public:
    DynamicVectorClass(unsigned size=0,const T *array=0);
    virtual ~DynamicVectorClass();
    virtual bool Resize(int size,const T *array=0);
    int count,growth;
};
struct Rva00173C04Buffer { char unknown[12]; void *data; };
class MeshMatDescClass
{
public:
    Vector2 *Get_UV_Array(int pass, int stage);
    int unknown00[3];
    int legacyUV;
    Rva00173C04Buffer *uv[8];
    char unknown30[0x20];
    Rva00173C04Buffer *color;
};
struct Rva00173C04Model
{
    char unknown00[0x28];
    int vertexCount;
    char unknown2c[0x94-0x2c];
    MeshMatDescClass *desc;
};
class Rva0017368AMesh
{
public:
    virtual void vf00(); virtual void vf04(); virtual void vf08();
    virtual void vf0c(); virtual void vf10(); virtual void vf14();
    virtual void vf18(); virtual void vf1c(); virtual void vf20();
    virtual void vf24(); virtual int Polys();
    char unknown04[0xc4-4];
    Rva00173C04Model *model;
};
class MeshClass { public: void Get_Deformed_Vertices(Vector3 *,Vector3 *); };
namespace Debug_Statistics { void Record_DX8_Skin_Polys_And_Vertices(int,int); }
struct Rva00173C04Vertex { float x,y,z,nx,ny,nz; unsigned diffuse; float u1,v1,u2,v2; };
class FXShaderRenderer { public: void rva00173C04(Rva0017368AMesh *,void *); };
typedef char Rva00173C04Vector3Size[(sizeof(Vector3)==12)?1:-1];
typedef char Rva00173C04Vector2Size[(sizeof(Vector2)==8)?1:-1];
typedef char Rva00173C04CacheSize[(sizeof(DynamicVectorClass<Vector3>)==24)?1:-1];
typedef char Rva00173C04VertexSize[(sizeof(Rva00173C04Vertex)==44)?1:-1];
typedef char Rva00173C04MeshPrefixSize[(sizeof(Rva0017368AMesh)==200)?1:-1];
void FXShaderRenderer::rva00173C04(Rva0017368AMesh *mesh,void *vertices)
{
    static DynamicVectorClass<Vector3> positions;
    static DynamicVectorClass<Vector3> normals;
    Rva00173C04Model *model=mesh->model;
    int vertexCount=model->vertexCount;
    Debug_Statistics::Record_DX8_Skin_Polys_And_Vertices(mesh->Polys(),vertexCount);
    if (positions.Length() < vertexCount) positions.Resize(vertexCount);
    if (normals.Length() < vertexCount) normals.Resize(vertexCount);
    MeshMatDescClass *desc=model->desc;
    Vector3 *loc=&positions[0];
    Vector3 *norm=&normals[0];
    const Vector2 *uv0=0;
    if (desc->legacyUV) uv0=desc->Get_UV_Array(0,0);
    else if (desc->uv[0]) uv0=(Vector2 *)desc->uv[0]->data;
    const Vector2 *uv1=0;
    if (desc->legacyUV) uv1=desc->Get_UV_Array(0,1);
    else if (desc->uv[1]) uv1=(Vector2 *)desc->uv[1]->data;
    const unsigned *diffuse=desc->color ? (const unsigned *)desc->color->data : 0;
    Rva00173C04Vertex *verts=(Rva00173C04Vertex *)vertices;
    ((MeshClass *)mesh)->Get_Deformed_Vertices(loc,norm);
    for (int v=0;v<vertexCount;++v) {
        verts[v].x=loc->X; verts[v].y=loc->Y; verts[v].z=loc->Z;
        verts[v].nx=norm->X; verts[v].ny=norm->Y; verts[v].nz=norm->Z;
        if (diffuse) verts[v].diffuse=*diffuse++;
        else verts[v].diffuse=~0u;
        if (uv0) { verts[v].u1=uv0->U; verts[v].v1=uv0->V; ++uv0; }
        else { verts[v].u1=0.0f; verts[v].v1=0.0f; }
        if (uv1) { verts[v].u2=uv1->U; verts[v].v2=uv1->V; ++uv1; }
        else { verts[v].u2=0.0f; verts[v].v2=0.0f; }
        ++loc; ++norm;
    }
}
