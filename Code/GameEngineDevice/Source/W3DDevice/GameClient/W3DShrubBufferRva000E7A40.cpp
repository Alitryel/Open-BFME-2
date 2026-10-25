// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// W3DShrubBuffer indexed toppling update, retail 0x000E7A40 (196 bytes, ret 4). Open-BFME-1 twin:
// W3DShrubBuffer_updateTopplingTree.cpp (0x0071D9F0). The sink counter runs down; the topple and push-aside
// models fade by the remaining fraction (SetOpacity 0x0010E87A) and the record is removed when it reaches zero
// (0x000E75F5). BFME2 layout: 2000 records of 0xA0 at +0x1958 (sink frames +0x90, topple model +0x94, push-aside
// model +0x98), count +0x4FB58, types of 0x5C at +0x4FB70 with the type data at +0x20 (topple frames +0x4C).
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class RenderObjClass;
bool Rva0010E87A_SetOpacity(RenderObjClass *object, float value);

struct Rva000E7A40TypeData
{
	char m_pad00[0x4c];
	UnsignedInt m_toppleFrames;
};

struct Rva000E7A40Tree
{
	char m_pad00[0x40];
	Int m_treeType;
	char m_pad44[0x90 - 0x44];
	UnsignedInt m_sinkFrames;
	RenderObjClass *m_topple;
	RenderObjClass *m_pushAside;
	char m_pad9c[4];
};

struct Rva000E7A40Type
{
	char m_pad00[0x20];
	Rva000E7A40TypeData *m_data;
	char m_pad24[0x5c - 0x24];
};

// The record and type arrays are spelled as W3DShrubBuffer.cpp's own view spells them (opaque element storage);
// this body reads them through its local element views above.
class Rva000E9C1DRecord
{
public:
	Rva000E9C1DRecord();
private:
	unsigned char m_storage[0xA0];
};

class Rva000E9C1DType
{
public:
	Rva000E9C1DType();
	~Rva000E9C1DType();
private:
	unsigned char m_storage[0x5C];
};

class W3DShrubBuffer
{
public:
	void rva000E7A40(Int treeIndex);
	void rva000E75F5(Int index);

private:
	char m_pad00[0x1958];
	Rva000E9C1DRecord m_records[2000];
	Int m_count;
	char m_pad4fb5c[0x4fb70 - 0x4fb5c];
	Rva000E9C1DType m_types[64];
};

void W3DShrubBuffer::rva000E7A40(Int treeIndex)
{
	Rva000E7A40Tree *trees = reinterpret_cast<Rva000E7A40Tree *>(m_records);
	Rva000E7A40Type *treeTypes = reinterpret_cast<Rva000E7A40Type *>(m_types);
	char *treeBytes = reinterpret_cast<char *>(this) + treeIndex * 0xa0;
	Int treeType = trees[treeIndex].m_treeType;
	if (treeIndex >= m_count)
		return;
	if (treeType < 0)
		return;

	UnsignedInt &sinkFrames = *reinterpret_cast<UnsignedInt *>(treeBytes + 0x19e8);
	--sinkFrames;
	Real progress = (Real)sinkFrames / (Real)treeTypes[treeType].m_data->m_toppleFrames;

	RenderObjClass *topple = *reinterpret_cast<RenderObjClass **>(treeBytes + 0x19ec);
	if (topple)
		Rva0010E87A_SetOpacity(topple, progress);
	RenderObjClass *pushAside = *reinterpret_cast<RenderObjClass **>(treeBytes + 0x19f0);
	if (pushAside)
		Rva0010E87A_SetOpacity(pushAside, 1.0f - progress);
	if (sinkFrames == 0)
		rva000E75F5(treeIndex);
}
