// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// ??4MeshModelClass@@QAEAAV0@ABV0@@Z at retail 0x00171E60 (265 bytes).
//
// MeshModelClass::operator=, guided by Zero Hour's WW3D2 meshmdl.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference)
// and the BFME1 donor reference/open-bfme-1/game/Libraries/Source/WWVegas/
// WW3D2/meshmdl.cpp. Placement: directly before the matched
// MeshModelClass::Reset (0x00171F70), as in meshmdl.cpp.
//
// Target evidence: the self-assignment guard, then the same unregister head
// the matched destructor (MeshModelClassDtor.cpp, 0x00172AB0) and the
// standalone 0x001716E0 use in place of ZH's TheDX8MeshRenderer call (the two
// guarded global pointers, then the CurMatDesc UV[0] guard around 0x00199FA5);
// then the matched MeshGeometryClass::operator= (0x00168FE0),
// MeshMatDescClass::operator= (0x0015D800) on DefMatDesc, CurMatDesc alias,
// AlternateMatDesc delete (non-virtual ~MeshMatDescClass 0x0015DC40 plus
// operator delete) and 0x118-byte copy (0x0015DD10), and the matched
// clone_materials tail (0x001881C0). BFME 2 has no GapFiller copy here: its
// GapFiller is released by the context helper in the head.

#include <new>
#include <stddef.h>

class W3DMPO
{
};

class RefCountClass
{
public:
	virtual void Delete_This();
	virtual ~RefCountClass();

private:
	int NumRefs;
};

class MultiListObjectClass
{
public:
	virtual ~MultiListObjectClass();

private:
	void *ListNode;
};

struct UVBufferClass;

class MeshMatDescClass
{
public:
	MeshMatDescClass(const MeshMatDescClass &that);
	~MeshMatDescClass();
	MeshMatDescClass &operator=(const MeshMatDescClass &that);
	bool Do_Mappers_Need_Normals();

	int PassCount;
	int VertexCount;
	int PolyCount;
	UVBufferClass *UV[8];
	char m_pad[0x118 - 0x2C];
};

// Stands in for MeshGeometryClass: W3DMPO (empty) + RefCountClass (vptr +0)
// + MultiListObjectClass (vptr +8); total 0x8C per the proven sizeof.
class MeshGeometryClass : public W3DMPO, public RefCountClass, public MultiListObjectClass
{
public:
	virtual ~MeshGeometryClass();
	MeshGeometryClass &operator=(const MeshGeometryClass &that);

protected:
	// Needs_Vertex_Normals (0x00171850) proves the packed flag byte at +0x19.
	char m_pad10[0x19 - sizeof(RefCountClass) - sizeof(MultiListObjectClass)];
	unsigned char m_flagByte;
	char m_pad1A[0x8C - 0x1A];
};

class MeshModelClass;

class DX8MeshRendererClass
{
public:
	void Unregister_Mesh_Type(MeshModelClass *mmc);
};

extern DX8MeshRendererClass *TheDX8MeshRenderer;

class Rva00DF6F94GapFillerContext
{
public:
	void DeleteModelGapFiller(MeshModelClass *mmc);
};

extern Rva00DF6F94GapFillerContext *TheMeshGapFillerContext;

class Rva00199FA5Rec;
bool __cdecl rva00199FA5(Rva00199FA5Rec *p);

class MeshModelClass : public MeshGeometryClass
{
public:
	virtual ~MeshModelClass();
	MeshModelClass &operator=(const MeshModelClass &that);
	bool Needs_Vertex_Normals();
	int Get_Flag(int mask) const { return m_flagByte & mask; }

	enum { PRELIT_MASK = 0xE0 };

protected:
	void clone_materials(const MeshModelClass &srcmesh);

private:
	MeshMatDescClass *DefMatDesc;
	MeshMatDescClass *AlternateMatDesc;
	MeshMatDescClass *CurMatDesc;
	void *MatInfo;
};

// ??4MeshModelClass@@QAEAAV0@ABV0@@Z
MeshModelClass &MeshModelClass::operator=(const MeshModelClass &that)
{
	if (this != &that) {
		// Remove all polygon renderers, this will remove the mesh from the rendering system.
		// The mesh will be initialized to rendering system the next time it is rendered.
		if (TheDX8MeshRenderer != NULL) {
			TheDX8MeshRenderer->Unregister_Mesh_Type(this);
		}
		if (TheMeshGapFillerContext != NULL) {
			TheMeshGapFillerContext->DeleteModelGapFiller(this);
		}
		if (CurMatDesc->UV[0] != NULL) {
			rva00199FA5((Rva00199FA5Rec *)CurMatDesc);
		}

		MeshGeometryClass::operator=(that);

		*DefMatDesc = *(that.DefMatDesc);
		CurMatDesc = DefMatDesc;

		if (AlternateMatDesc != NULL) {
			delete AlternateMatDesc;
			AlternateMatDesc = NULL;
		}

		if (that.AlternateMatDesc != NULL) {
			AlternateMatDesc = new MeshMatDescClass(*(that.AlternateMatDesc));
		}

		clone_materials(that);
	}
	return *this;
}
