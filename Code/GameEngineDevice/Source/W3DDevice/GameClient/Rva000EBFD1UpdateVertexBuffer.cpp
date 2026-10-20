// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// ?rva000EBFD1@Rva000EC9C6@@QAEXXZ, retail 0x000EBFD1 (1710 bytes), called by
// the rowed dispatcher Rva000EC9C6::rva000EC9C6 (0x000EC9C6).
// BF1 575ba2b04 W3DTreeBufferRva00734270.cpp and ZH updateVertexBuffer
// provide the update/alpha/locked-buffer semantics. Target EBFD1..EC67F
// independently supplies vector prefixes, E8 record stride, 2C output stride,
// composed scale/postMul/offset transform, extra C4 flag and fade flag40.
// The locals are the named slots of the WorldBuilder twin (WB 0x0089CA90).
// Identity arm first via Set(location); scale and product use the WWMath header
// Scale and postMul. The offset translation and the vertex transform are TU copies
// of the header helpers whose row 2 keeps retail's (X+Y)+Z grouping; cl 7.1 does
// not re-associate across parentheses.
#include "vector3.h"
#include "matrix3d.h"
#include "W3DTreeRecord.h"
#include "W3DTreeTypeRecord.h"

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

struct VertexFormatXYZNDUV1
{
	float x, y, z;
	float nx, ny, nz;
	unsigned int diffuse;
	float u1, v1;
	float u2, v2;
};

struct Rva000EBFD1VertexBuffer
{
	unsigned char m_head[0x0c];
	Vector3 *m_array;
	Vector3 *Get_Array(void) { return m_array; }
};

struct Rva000EBFD1Model
{
	unsigned char m_head[0x28];
	int m_vertexCount;
	unsigned char m_gap2c[4];
	Rva000EBFD1VertexBuffer *m_vertexArray;
	int Get_Vertex_Count(void) const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array(void) const { return m_vertexArray->Get_Array(); }
};

// The tree type's mesh.
class Rva000EDA94Ref
{
public:
	Rva000EBFD1Model *Peek_Model(void) const { return m_model; }
private:
	unsigned char m_head[0xc4];
	Rva000EBFD1Model *m_model;
};

struct W3DTreeDrawModuleData
{
	unsigned char m_pad00[0x58];
	int m_field58;
};

template <class T> struct PtrVector
{
	T *m_start, *m_finish, *m_endOfStorage;
	T *begin(void) { return m_start; }
	T &operator[](unsigned int n) { return *(begin() + n); }
	unsigned int size(void) const { return unsigned(m_finish - m_start); }
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
struct Rva000EBFD1GlobalFade
{
	unsigned char m_pad00[0x40];
	bool m_enabled;
};

class Rva000EC9C6
{
public:
	void rva000EBFD1(void);

private:
	void *m_vtable;
	PtrVector<VertexBufferClass *> m_vertexTree;
	unsigned char m_pad10[0x1c - 0x10];
	PtrVector<void *> m_indexTree;
	PtrVector<int> m_curNumTreeIndices;
	unsigned char m_pad34[0x5c0 - 0x34];
	Rva000EDA94Record m_trees[1200];
	int m_numTrees;
	unsigned char m_pad44544[0x44554 - 0x44544];
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

// ?rva000EBFD1@Rva000EC9C6@@QAEXXZ
void Rva000EC9C6::rva000EBFD1(void)
{
	if (!m_initialized || !m_indexTree[0] || !m_vertexTree[0])
		return;
	for (unsigned int bNdx = 0; bNdx < m_vertexTree.size(); bNdx++) {
		if (m_curNumTreeIndices[bNdx] == 0)
			break;
		VertexFormatXYZNDUV1 *vb;
		// Lock the buffers.
		VertexBufferClass::WriteLockClass lockVtxBuffer(m_vertexTree[bNdx], 0);
		vb = (VertexFormatXYZNDUV1 *)lockVtxBuffer.Get_Vertex_Array();

		VertexFormatXYZNDUV1 *curVb;

		for (int curTree = 0; curTree < m_numTrees; curTree += m_treeIndexStep) {
			if (m_trees[curTree].bufferNdx != (int)bNdx)
				continue;
			int type = m_trees[curTree].treeType;
			if (type < 0)
				continue; // Deleted tree. [6/9/2003]
			int alpha = m_trees[curTree].m_fieldE0;
			if (m_trees[curTree].m_toppleState == 0 && alpha == m_trees[curTree].m_fieldE4 && !m_trees[curTree].m_flagC4)
				continue;
			// Step the alpha toward its target by the type's fade step.
			if (((Rva000EBFD1GlobalFade *)TheWritableGlobalData)->m_enabled && alpha != m_trees[curTree].m_fieldE4) {
				if (alpha > m_trees[curTree].m_fieldE4) {
					alpha -= m_treeTypes[type].m_data->m_field58;
					if (alpha < m_trees[curTree].m_fieldE4)
						alpha = m_trees[curTree].m_fieldE4;
				} else {
					alpha += m_treeTypes[type].m_data->m_field58;
					if (alpha > m_trees[curTree].m_fieldE4)
						alpha = m_trees[curTree].m_fieldE4;
				}
				m_trees[curTree].m_fieldE0 = alpha;
			}
			if (!m_trees[curTree].visible)
				continue;
			if (m_trees[curTree].m_fieldC8)
				continue;
			float scale = m_trees[curTree].scale;
			Vector3 loc = m_trees[curTree].location;
			const Matrix3D *mtx = &m_trees[curTree].transform;
			if (!m_treeTypes[type].m_ref)
				type = 0;

			Matrix3D transform;
			if (!m_trees[curTree].m_toppleState && !m_trees[curTree].m_flagC4)
				transform.Set(loc);
			else
				transform = m_trees[curTree].m_mtx;
			transform.Scale(scale);
			transform.postMul(*mtx);
			TranslateOffset(transform, m_treeTypes[type].m_offset);

			int startVertex = m_trees[curTree].firstIndex;
			curVb = vb + startVertex;
			int i;
			int numVertex = m_treeTypes[type].m_ref->Peek_Model()->Get_Vertex_Count();
			Vector3 *pVert = m_treeTypes[type].m_ref->Peek_Model()->Get_Vertex_Array();

			for (i = 0; i < numVertex; i++) {
				TreeTransform(transform, pVert[i], (Vector3 *)curVb);
				curVb->diffuse = (curVb->diffuse & 0x00FFFFFF) | (alpha << 24);
				curVb++;
			}
		}
	}
}
