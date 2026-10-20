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
// ?rva000EB6BB@Rva000EC9C6@@QAEXXZ, retail 0x000EB6BB (2326 bytes), is ZH
// loadTreesInVertexAndIndexBuffers with the locals of its WorldBuilder twin (WB 0x0089B530).
// BF1 575ba2b04 W3DTreeBufferRva00734270.cpp and ZH give the buffer-load semantics; the
// target body supplies E8 tree records, 5C type records, 44B vertices and lock/capacity checks.
// WB 0x0089B530 re-tests type<0 at the mesh check, stores firstIndex before bufferNdx, uses
// one i for both inner loops, Get_Vertex_Array(bool) and the WWMath header Translate and
// Transform_Vector.
#include "vector3.h"
#include "vector2.h"
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

class RefCountClass
{
public:
	RefCountClass() : m_refs(1) {}
	RefCountClass(const RefCountClass &) : m_refs(1) {}
	virtual void Delete_This();

protected:
	virtual ~RefCountClass() {}

private:
	int m_refs;
};

template <class T>
class ShareBufferClass : public RefCountClass
{
public:
	ShareBufferClass(int count, const char *msg, int alignment = 0);
	T *Get_Array() { return m_array; }

protected:
	T *m_rawBuffer;
	T *m_array;
	int m_count;
	int m_alignment;
};

class UVBufferClass : public ShareBufferClass<Vector2>
{
public:
	UVBufferClass(int count, const char *msg);

private:
	unsigned int m_crc;
};

class MeshMatDescClass
{
public:
	// Header-inline body of rowed 0x000D1F1A; cl keeps it out of line, and seeing that it
	// stores nothing lets the model pointer stay live across the call.
	Vector2 *Get_UV_Array(int pass, int stage)
	{
		if (m_uvSource[pass][stage] == -1)
			return 0;
		if (m_uv[m_uvSource[pass][stage]])
			return m_uv[m_uvSource[pass][stage]]->Get_Array();
		return 0;
	}
	inline Vector2 *Get_UV_Array_By_Index(int index, bool create)
	{
		if (create && !m_uv[index])
			m_uv[index] = new UVBufferClass(m_vertexCount, "MeshMatDescClass::UV");
		if (!create && m_unknown0C != 0 && index < 2)
			return Get_UV_Array(0, index);
		if (m_uv[index])
			return m_uv[index]->Get_Array();
		return 0;
	}
	inline unsigned *Get_Color_Array(int index, bool create)
	{
		if (create && !m_colorArray[index])
			m_colorArray[index] = new ShareBufferClass<unsigned>(m_vertexCount, "MeshMatDescClass::ColorArray");
		if (m_colorArray[index])
			return m_colorArray[index]->Get_Array();
		return 0;
	}
private:
	int m_passCount;
	int m_vertexCount;
	int m_polyCount;
	int m_unknown0C;
	UVBufferClass *m_uv[8];
	int m_uvSource[4][2];
	ShareBufferClass<unsigned> *m_colorArray[2];
};

class MeshGeometryClass
{
public:
	const Vector3 *Get_Vertex_Normal_Array(bool);
};

template <class T> struct Rva000EBFD1ShareBuffer
{
	unsigned char m_head[0x0c];
	T *m_array;
	T *Get_Array(void) { return m_array; }
};

// The tree mesh's model.
class Rva000EBFD1Model : public MeshGeometryClass
{
public:
	int Get_Vertex_Count(void) const { return m_vertexCount; }
	Vector3 *Get_Vertex_Array(bool secondary = false) const
	{
		if (secondary)
			return m_vertexArray[1]->Get_Array();
		return m_vertexArray[0]->Get_Array();
	}
	int Get_Polygon_Count(void) const { return m_polyCount; }
	TriIndex *Get_Polygon_Array(void) const { return m_polyArray->Get_Array(); }
	Vector2 *Get_UV_Array_By_Index(int index, bool create) { return m_matDesc->Get_UV_Array_By_Index(index, create); }
	unsigned *Get_Color_Array(int index, bool create) { return m_matDesc->Get_Color_Array(index, create); }
private:
	unsigned char m_head[0x24];
	int m_polyCount;
	int m_vertexCount;
	Rva000EBFD1ShareBuffer<TriIndex> *m_polyArray;
	Rva000EBFD1ShareBuffer<Vector3> *m_vertexArray[2];
	unsigned char m_pad38[0x94 - 0x38];
	MeshMatDescClass *m_matDesc;
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
	void rva000EB6BB(void);
	void rva000EBFD1(void);

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

// Rebuilds every buffer from the visible trees; the sway type rides in u2 unless the type never sways.
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
		// Add to the index buffer & vertex buffer.
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
			// m_offset is ZH TTreeType's Vector3 offset; the type contract stores it as float[3].
			transform.Translate(*(const Vector3 *)m_treeTypes[type].m_offset);

			int startVertex = m_curNumTreeVertices[bNdx];
			m_trees[curTree].firstIndex = startVertex;
			m_trees[curTree].bufferNdx = bNdx;
			int i;
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
			for (i = 0; i < numVertex; i++) {
				Matrix3D::Transform_Vector(transform, pVert[i], (Vector3 *)curVb);
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
				curVb->u2 = m_treeTypes[m_trees[curTree].treeType].m_data->m_noSway ? 0 : m_trees[curTree].swayType;
				curVb->v2 = loc.Z;
				curVb++;
			}
			m_curNumTreeVertices[bNdx] += numVertex;
			for (i = 0; i < numIndex; i++) {
				*curIb++ = startVertex + pPoly[i].I;
				*curIb++ = startVertex + pPoly[i].J;
				*curIb++ = startVertex + pPoly[i].K;
			}
			m_curNumTreeIndices[bNdx] += 3 * numIndex;
		}
	}
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
