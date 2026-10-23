// cl: /MD /EHsc /DNDEBUG
// W3DBridge index copier; the 0x000DF11E caller passes this in ECX.
// Mesh offsets follow retail Peek_Model and polygon-array accesses.
struct De5d2Inner
{
	int _pad[3];
	unsigned short *m_buf;
};
struct De5d2Mid
{
	char _pad0[0x24];
	int m_count;
	char _pad1[4];
	De5d2Inner *m_inner;
};
class MeshClass
{
public:
	char _pad[0xC4];
	De5d2Mid *m_mid;
};
struct TriIndex { unsigned short I, J, K; };

class W3DBridge
{
protected:
	int getModelIndices(unsigned short *, int, int, MeshClass *);
};

int W3DBridge::getModelIndices(unsigned short *destination_ib, int curIndex, int vertexOffset, MeshClass *pMesh)
{
	if (pMesh == 0)
		return 0;
	De5d2Mid *model = pMesh->m_mid;
	int numPoly = model->m_count;
	De5d2Inner *inner = model->m_inner;
	const TriIndex *pPoly = (const TriIndex *)inner->m_buf;
	const int maxBridgeIndex = 16000;
	if (curIndex + 3 * numPoly + 6 >= maxBridgeIndex)
		return 0;
	unsigned short *curIb = destination_ib + curIndex;
	for (int i = 0; i < numPoly; i++)
	{
		*curIb++ = vertexOffset + pPoly[i].I;
		*curIb++ = vertexOffset + pPoly[i].J;
		*curIb++ = vertexOffset + pPoly[i].K;
	}
	return numPoly * 3;
}
