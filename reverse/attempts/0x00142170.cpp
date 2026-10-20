// ?rva00142170@BfmeSceneVector@@QAEXPAPAUGen_00943CF0_Node@@PAUSceneCollectCell@@IHHHHHHH@Z
// partial score=0.99 date=2026-10-20
// ?rva00142170@BfmeSceneVector@@QAEXPAPAUGen_00943CF0_Node@@PAUSceneCollectCell@@IHHHHHHH@Z
// partial score=0.488 date=2026-10-17
// ?rva00142170@BfmeSceneVector@@QAEXPAPAUGen_00943CF0_Node@@PAUSceneCollectCell@@IHHHHHHH@Z
// partial score=0.7 date=2026-10-12
// cl: /Ireference/shims/bfme2ray /Ireference/shims/bfme2scene /Ireference/shims/bfme2renderobj /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep /O2 /G7 /arch:SSE
// ?rva00142170@BfmeSceneVector@@QAEXPAPAUGen_00943CF0_Node@@PAUSceneCollectCell@@IHHHHHHH@Z,
// retail 0x00142170, 443 bytes: recursive 28-byte-stride quadrant-tree
// rectangle query. Drains each visited cell's object list into the pooled
// output list, then recurses the overlapping quadrants. The landed wrapper
// rva00142330 establishes the helper signature; node stride 28, quadrant
// subdivision, list offsets and pool are native evidence.
// Original function names are unknown; no donor name is asserted.
// Shape of BFME 1's Rva009441D0Recurse: early return on an empty subtree,
// in-place halving, repeated midpoint sums and a tail call for the last quadrant.
#include "rendobj.h"
#include "aabox.h"
#include "scene.h"

struct Gen_00943CF0_Node
{
	Gen_00943CF0_Node *m_next;
	void *m_value;
};

class Rva0006EFC8
{
public:
	bool rva0006EFC8(int arena, int size);

	int m_00;
	void *m_04;
	void *m_head;
	void *(__cdecl *m_alloc)(int size, int arg);
	void (__cdecl *m_free)(void *ptr, int arg);
	int m_14;
};

extern Rva0006EFC8 g_BfmeSceneNodePool;

// Pops an 8-byte node, growing the pool until it has one; the operation of 0x00141800, inlined here.
inline void *bfmeSceneNodePoolPop()
{
	void *node;
retry:
	if (g_BfmeSceneNodePool.m_head) goto found;
	{
		int size = g_BfmeSceneNodePool.m_00 * 8 + 4;
		if (g_BfmeSceneNodePool.rva0006EFC8(0, size))
			goto retry;
	}
	return 0;
found:
	node = g_BfmeSceneNodePool.m_head;
	g_BfmeSceneNodePool.m_head = *(void **)node;
	return node;
}

struct SceneCollectCell
{
	unsigned count;
	MultiListClass<RenderObjClass> objects;
};
typedef char SceneCollectCellSize[(sizeof(SceneCollectCell) == 28) ? 1 : -1];

class BfmeSceneVector
{
public:
	void rva00142170(Gen_00943CF0_Node **out, SceneCollectCell *node, unsigned n, int xmin, int ymin, int xmax, int ymax, int ox, int oy, int extent);
	float bounds[6];
	SceneCollectCell *vector;
	int vector_max;
	float scale;
	unsigned int level_mask;
};

void BfmeSceneVector::rva00142170(Gen_00943CF0_Node **out, SceneCollectCell *node, unsigned n, int xmin, int ymin, int xmax, int ymax, int ox, int oy, int extent)
{
	if (!node->objects.Is_Empty()) {
		MultiListIterator<RenderObjClass> it(&node->objects);
		for (; !it.Is_Done(); it.Next()) {
			RenderObjClass *object = it.Peek_Obj();
			Gen_00943CF0_Node *item = (Gen_00943CF0_Node *)bfmeSceneNodePoolPop();
			void **valuePtr = (void **)((char *)item + 4);
			if (valuePtr) *valuePtr = object;
			item->m_next = 0;
			item->m_next = *out;
			*out = item;
		}
	}
	if (node->count == 0)
		return;
	extent /= 2;
	++node;
	if (ymin < oy + extent) {
		if (xmin < ox + extent) rva00142170(out, node, n >> 2, xmin, ymin, xmax, ymax, ox, oy, extent);
		if (xmax >= ox + extent) rva00142170(out, node + n, n >> 2, xmin, ymin, xmax, ymax, ox + extent, oy, extent);
	}
	if (ymax >= oy + extent) {
		if (xmin < ox + extent) rva00142170(out, node + 2 * n, n >> 2, xmin, ymin, xmax, ymax, ox, oy + extent, extent);
		if (xmax >= ox + extent) rva00142170(out, node + 3 * n, n >> 2, xmin, ymin, xmax, ymax, ox + extent, oy + extent, extent);
	}
}
