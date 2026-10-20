// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ
// partial score=0.97 date=2026-10-20
// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ
// partial score=0.76 date=2026-10-20
// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ
// partial score=0.64 date=2026-10-20
// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ
// partial score=0.55 date=2026-10-17
// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ
// partial score=0.9 date=2026-10-12
// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ
// partial score=0.8116742830418466 date=2026-10-10
// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ
// Notes kept from the earlier banks of this body:
// Get_UV_Array is the header-inline body of rowed 0x000D1F1A; cl keeps it out of line, and
// seeing that it stores nothing lets the model pointer stay live across the call.
// Matrix3D::postMul (a = a * b); row 1's W sum keeps retail's association (t0+t2)+t1.
// Matrix-bank continuation: local postMul copies BF1 575ba2b04 matrix3d.h arithmetic.
// Same-valued coefficient PHIs and scoped initialized coefficient volatile reads
// change compiler scheduling; full emitted extent remains part of the score.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// BF1 575ba2b04 W3DTreeBufferRva00734270.cpp and ZH loadTreesInVertexAndIndexBuffers
// provide the buffer-update/locked-buffer semantics. This native EB6BB..EBFD1
// body independently supplies E8 tree records, 5C type records, 44B vertices,
// scale/postMul/offset composition and lock/capacity checks. The sibling updater
// EBFD1..EC67F is separate evidence; its alpha/fade behavior is not claimed here.
// WB 89B530 re-tests type<0 at the mesh check and stores firstVertex before buffer.
// WB 89B530 locals (one curTree for both loops, vb/ib/curIb/curVb, type, scale, loc, mtx pointer), canonical
// record/type views, header Scale/postMul, TU Translate/Transform_Vector with row 2 grouped, nested model
// accessors, per-loop i and the (index, create) UV/colour accessors give retail's 2326 B with 0 regions.
// The sway int at record +0x60 is read through m_pad5C; the create branch allocates a stand-in buffer.
#include "vector3.h"
#include "vector2.h"
#include "matrix3d.h"
#include "../../Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeRecord.h"
#include "../../Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTreeTypeRecord.h"

class VertexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(VertexBufferClass *vertexBuffer, int flags);
		~WriteLockClass();
		void *Get_Vertex_Array(void) { return m_vertices; }
	private:
		VertexBufferClass *m_vertexBuffer;
		void *m_vertices;
		int m_flags;
	};
};

class IndexBufferClass
{
public:
	class WriteLockClass
	{
	public:
		WriteLockClass(IndexBufferClass *indexBuffer, int flags);
		~WriteLockClass();
		unsigned short *Get_Index_Array(void) { return m_indices; }
	private:
		IndexBufferClass *m_indexBuffer;
		unsigned short *m_indices;
		int m_flags;
	};
};

struct VertexFormatXYZNDUV1
{
	float x, y, z;
	float nx, ny, nz;
	unsigned int diffuse;
	float u1, v1;
	float u2, v2;
};

struct TriIndex
{
	unsigned short I, J, K;
};

template <class T> struct ShareBufferView
{
	unsigned char m_head[0x0c];
	T *m_array;
	T *Get_Array(void) { return m_array; }
};

class MeshMatDescClass
{
public:
	Vector2 *Get_UV_Array(int pass, int stage)
	{
		if (m_uvSource[pass][stage] == -1)
			return 0;
		if (m_uv[m_uvSource[pass][stage]])
			return m_uv[m_uvSource[pass][stage]]->Get_Array();
		return 0;
	}
	__forceinline Vector2 *Get_UV_Array_By_Index(int index, bool create)
	{
		if (create && !m_uv[index])
			m_uv[index] = new ShareBufferView<Vector2>;
		if (!create && m_unknown0C != 0 && index < 2)
			return Get_UV_Array(0, index);
		if (m_uv[index])
			return m_uv[index]->Get_Array();
		return 0;
	}
	__forceinline unsigned *Get_Color_Array(int index, bool create)
	{
		if (create && !m_colorArray[index])
			m_colorArray[index] = new ShareBufferView<unsigned>;
		if (m_colorArray[index])
			return m_colorArray[index]->Get_Array();
		return 0;
	}
private:
	unsigned char m_head[0x0c];
	int m_unknown0C;
	ShareBufferView<Vector2> *m_uv[8];
	int m_uvSource[4][2];
	ShareBufferView<unsigned> *m_colorArray[2];
};

class MeshGeometryClass
{
public:
	const Vector3 *Get_Vertex_Normal_Array(bool);
};

class Rva000EB6BBModel : public MeshGeometryClass
{
public:
	int Get_Vertex_Count(void) const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array(void) const { return m_vertexArray->Get_Array(); }
	int Get_Polygon_Count(void) const { return m_polyCount; }
	TriIndex *Get_Polygon_Array(void) const { return m_polyArray->Get_Array(); }
	__forceinline Vector2 *Get_UV_Array_By_Index(int index, bool create) { return m_matDesc->Get_UV_Array_By_Index(index, create); }
	__forceinline unsigned *Get_Color_Array(int index, bool create) { return m_matDesc->Get_Color_Array(index, create); }
private:
	unsigned char m_head[0x24];
	int m_polyCount;
	int m_vertexCount;
	ShareBufferView<TriIndex> *m_polyArray;
	ShareBufferView<Vector3> *m_vertexArray;
	unsigned char m_pad34[0x94 - 0x34];
	MeshMatDescClass *m_matDesc;
};

// The tree type's mesh.
class Rva000EDA94Ref
{
public:
	Rva000EB6BBModel *Peek_Model(void) const { return m_model; }
private:
	unsigned char m_head[0xc4];
	Rva000EB6BBModel *m_model;
};

struct W3DTreeDrawModuleData
{
	unsigned char m_pad00[0x54];
	bool m_noSway;
	unsigned char m_pad55[3];
	int m_field58;
};

template <class T> struct PtrVector
{
	T *m_start, *m_finish, *m_endOfStorage;
	T *begin(void) { return m_start; }
	T &operator[](unsigned int n) { return *(begin() + n); }
	unsigned int size(void) const { return unsigned(m_finish - m_start); }
};

class Rva000EC9C6
{
public:
	void rva000EB6BB(void);

private:
	void *m_vtable;
	PtrVector<VertexBufferClass *> m_vertexTree;
	PtrVector<int> m_curNumTreeVertices;
	PtrVector<IndexBufferClass *> m_indexTree;
	PtrVector<int> m_curNumTreeIndices;
	unsigned char m_pad34[0x5c0 - 0x34];
	Rva000EDA94Record m_trees[1200];
	int m_numTrees;
	bool m_anythingChanged;
	unsigned char m_pad44545[0x44554 - 0x44545];
	bool m_initialized;
	unsigned char m_pad44555[0x44558 - 0x44555];
	Rva000EC67F m_treeTypes[64];
	unsigned char m_pad45c58[0x45c60 - 0x45c58];
	int m_treeIndexStep;
};

// Matrix3D::Translate(x,y,z) applied to the offset, row 2 grouped as retail.
static inline void TranslateOffset(Matrix3D &m, const float *t)
{
	m[0][3] += (float)(m[0][0] * t[0] + m[0][1] * t[1] + m[0][2] * t[2]);
	m[1][3] += (float)(m[1][0] * t[0] + m[1][1] * t[1] + m[1][2] * t[2]);
	m[2][3] += ((m[2][0] * t[0] + m[2][1] * t[1]) + m[2][2] * t[2]);
}

// Matrix3D::Transform_Vector, row 2 grouped as retail.
static inline void TreeTransform(const Matrix3D &A, const Vector3 &in, Vector3 *out)
{
	Vector3 tmp;
	Vector3 *v;
	if (out == &in) {
		tmp = in;
		v = &tmp;
	} else {
		v = (Vector3 *)&in;
	}
	out->X = (A[0][0] * v->X + A[0][1] * v->Y + A[0][2] * v->Z + A[0][3]);
	out->Y = (A[1][0] * v->X + A[1][1] * v->Y + A[1][2] * v->Z + A[1][3]);
	out->Z = ((A[2][0] * v->X + A[2][1] * v->Y) + A[2][2] * v->Z + A[2][3]);
}

// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ
void Rva000EC9C6::rva000EB6BB(void)
{
	if (!m_initialized || !m_indexTree[0] || !m_vertexTree[0])
		return;
	if (!m_anythingChanged)
		return;
	int curTree;
	for (curTree = 0; curTree < m_numTrees; curTree++)
		m_trees[curTree].bufferNdx = -1;
	curTree = 0;
	for (unsigned int bNdx = 0; bNdx < m_vertexTree.size(); bNdx++) {
		m_curNumTreeVertices[bNdx] = 0;
		m_curNumTreeIndices[bNdx] = 0;
		if (curTree >= m_numTrees)
			break;
		VertexFormatXYZNDUV1 *vb;
		unsigned short *ib;
		// Lock the buffers.
		IndexBufferClass::WriteLockClass lockIdxBuffer(m_indexTree[bNdx], 0x2000);
		VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTree[bNdx], 0x2000);
		vb = (VertexFormatXYZNDUV1 *)lockVtxBuffer.Get_Vertex_Array();
		ib = lockIdxBuffer.Get_Index_Array();
		unsigned short *curIb = ib;
		VertexFormatXYZNDUV1 *curVb = vb;

		for (; curTree < m_numTrees; curTree += m_treeIndexStep) {
			int type = m_trees[curTree].treeType;
			if (type < 0)
				continue; // Deleted tree. [6/9/2003]
			if (!m_trees[curTree].visible)
				continue;
			if (m_trees[curTree].m_fieldC8)
				continue;
			float scale = m_trees[curTree].scale;
			Vector3 loc = m_trees[curTree].location;
			const Matrix3D *mtx = &m_trees[curTree].transform;
			if (type < 0 || m_treeTypes[type].m_ref == 0)
				continue;

			Matrix3D transform;
			if (m_trees[curTree].m_toppleState || m_trees[curTree].m_flagC4)
				transform = m_trees[curTree].m_mtx;
			else
				transform.Set(loc);
			transform.Scale(scale);
			transform.postMul(*mtx);
			TranslateOffset(transform, m_treeTypes[type].m_offset);

			int startVertex = m_curNumTreeVertices[bNdx];
			m_trees[curTree].firstIndex = startVertex;
			m_trees[curTree].bufferNdx = bNdx;
			int numVertex = m_treeTypes[type].m_ref->Peek_Model()->Get_Vertex_Count();
			Vector3 *pVert = m_treeTypes[type].m_ref->Peek_Model()->Get_Vertex_Array();
			// If we happen to have too many trees, stop.
			if (m_curNumTreeVertices[bNdx] + numVertex >= 30000)
				break;
			int numIndex = m_treeTypes[type].m_ref->Peek_Model()->Get_Polygon_Count();
			const TriIndex *pPoly = m_treeTypes[type].m_ref->Peek_Model()->Get_Polygon_Array();
			if (m_curNumTreeIndices[bNdx] + 3 * numIndex >= 60000)
				break;
			const Vector2 *uvs = m_treeTypes[type].m_ref->Peek_Model()->Get_UV_Array_By_Index(0, false);
			const Vector3 *normals = m_treeTypes[type].m_ref->Peek_Model()->Get_Vertex_Normal_Array(false);
			const unsigned *vecDiffuse = m_treeTypes[type].m_ref->Peek_Model()->Get_Color_Array(0, false);
			float Uscale = m_treeTypes[type].m_coords24[0].x;
			float Vscale = m_treeTypes[type].m_coords24[0].y;
			float UOffset = m_treeTypes[type].m_coords34[0].x;
			float VOffset = m_treeTypes[type].m_coords34[0].y;
			for (int i = 0; i < numVertex; i++) {
				TreeTransform(transform, pVert[i], (Vector3 *)curVb);
				if (normals) {
					*(Vector3 *)&curVb->nx = normals[i];
				} else {
					curVb->nx = 0.0f;
					curVb->ny = 0.0f;
					curVb->nz = 1.0f;
				}
				if (vecDiffuse)
					curVb->diffuse = (vecDiffuse[i] & 0x00FFFFFF) | (m_trees[curTree].m_fieldE0 << 24);
				else
					curVb->diffuse = 0x00FFFFFF | (m_trees[curTree].m_fieldE0 << 24);
				// Update the uv values.  The W3D models each have their own texture, and
				// we use one texture with all images in one, so we have to change the uvs to
				// match.
				float U = uvs[i].U;
				float V = uvs[i].V;
				if (U > 1.0f) U = 1.0f;
				if (U < 0.0f) U = 0.0f;
				if (V > 1.0f) V = 1.0f;
				if (V < 0.0f) V = 0.0f;
				curVb->u1 = U * Uscale + UOffset;
				curVb->v1 = V * Vscale + VOffset;
				curVb->u2 = m_treeTypes[m_trees[curTree].treeType].m_data->m_noSway ? 0 : *(int *)&m_trees[curTree].m_pad5C[4];
				curVb->v2 = loc.Z;
				curVb++;
			}
			m_curNumTreeVertices[bNdx] += numVertex;
			for (int i = 0; i < numIndex; i++) {
				*curIb++ = startVertex + pPoly[i].I;
				*curIb++ = startVertex + pPoly[i].J;
				*curIb++ = startVertex + pPoly[i].K;
			}
			m_curNumTreeIndices[bNdx] += 3 * numIndex;
		}
	}
}
