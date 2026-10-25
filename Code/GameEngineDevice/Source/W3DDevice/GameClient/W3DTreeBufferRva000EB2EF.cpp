// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// W3DTreeBuffer indexed toppling update, retail 0x000EB2EF (226 bytes, ret 4): a tree that is neither held nor
// busy counts its sink frames down, fades its topple and push-aside models by the remaining fraction
// (SetOpacity 0x0010E87A) and is removed (0x000EB0E6) when the counter reaches zero; a held or busy tree is
// removed outright. Shrub twin: 0x000E7A40 (Open-BFME-1 W3DShrubBuffer_updateTopplingTree.cpp). BFME2 layout:
// 1200 records of 0xE8 at +0x5C0 (busy flags +0xC4/+0x80, sink frames +0xD4, topple model +0xD8, push-aside
// model +0xDC), count +0x44540, types of 0x5C at +0x44558 with the type data at +0x20 (topple frames +0x4C).
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class RenderObjClass;
bool Rva0010E87A_SetOpacity(RenderObjClass *object, float value);

struct Rva000EB2EFTypeData
{
	char m_pad00[0x4c];
	UnsignedInt m_toppleFrames;
};

struct Rva000EB2EFTree
{
	char m_pad00[0x40];
	Int m_treeType;
	char m_pad44[0x80 - 0x44];
	Int m_field80;
	char m_pad84[0xc4 - 0x84];
	bool m_flagc4;
	char m_padc5[0xd4 - 0xc5];
	UnsignedInt m_sinkFrames;
	RenderObjClass *m_topple;
	RenderObjClass *m_pushAside;
	char m_pade0[8];
};

struct Rva000EB2EFType
{
	char m_pad00[0x20];
	Rva000EB2EFTypeData *m_data;
	char m_pad24[0x5c - 0x24];
};

// Retain the existing native-offset view independently of the destination's
// canonical record types; this view is used only to access the rowed fields.
struct Rva000EB2EFBufferView
{
    char m_pad00[0x5c0];
    Rva000EB2EFTree m_trees[1200];
    Int m_numTrees;
    char m_pad44544[0x44558 - 0x44544];
    Rva000EB2EFType m_treeTypes[64];
};

class W3DTreeBuffer
{
public:
    void rva000EB2EF(Int treeIndex);
    void rva000EB0E6(Int index);
};

void W3DTreeBuffer::rva000EB2EF(Int treeIndex)
{
	Rva000EB2EFBufferView *buffer = reinterpret_cast<Rva000EB2EFBufferView *>(this);
	if (treeIndex >= buffer->m_numTrees)
		return;
	Int treeType = buffer->m_trees[treeIndex].m_treeType;
	if (treeType < 0)
		return;

	if (buffer->m_trees[treeIndex].m_flagc4 || buffer->m_trees[treeIndex].m_field80 != 0) {
		rva000EB0E6(treeIndex);
		return;
	}
	--buffer->m_trees[treeIndex].m_sinkFrames;
	Real progress = (Real)buffer->m_trees[treeIndex].m_sinkFrames / (Real)buffer->m_treeTypes[treeType].m_data->m_toppleFrames;
	if (buffer->m_trees[treeIndex].m_topple)
		Rva0010E87A_SetOpacity(buffer->m_trees[treeIndex].m_topple, progress);
	if (buffer->m_trees[treeIndex].m_pushAside)
		Rva0010E87A_SetOpacity(buffer->m_trees[treeIndex].m_pushAside, 1.0f - progress);
	if (buffer->m_trees[treeIndex].m_sinkFrames == 0)
		rva000EB0E6(treeIndex);
}
