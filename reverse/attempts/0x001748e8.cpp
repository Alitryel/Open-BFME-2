// ?FlushSoftwareSkinnedRenderingTasks@FXShaderRenderer@@QAEXXZ
// partial score=0.59397 date=2026-10-14
// cl: /O1 /G7 /MD /EHsc
//
// ?FlushSoftwareSkinnedRenderingTasks@FXShaderRenderer@@QAEXXZ, retail
// 0x001748E8..0x00174A57 (367B, RET0, EH states 0-1). Sorts the 32-byte
// rendering tasks by the landed comparator 0x001736A7, sums the byte sizes of
// the tasks that claim an unclaimed +0x310 state pointer, then repeatedly
// opens a DynamicVBAccessClass (0x13B040) + WriteLock (0x13AA00), skins each
// task that fits the 0xFFFF budget through 0x173C04, and renders the batch
// (0x17438B) after Set_Vertex_Buffer (0x11D5C0); the final clear is 0x174350.
// Helper identities are rowed; only the skinning worker 0x173C04 keeps an
// address-derived spelling.
struct BfmeAssignRecord32 { char unknown[32]; };
struct Rva0017368AMesh;
struct Rva0017368ATask { Rva0017368AMesh *mesh; char unknown[28]; };
struct RvaC4 { char unknown[0x28]; int m_28; };

struct Rva0017368AMesh
{
	char unknown[0x300];
	int m_300;				// +0x300
	char unknown304[0x310 - 0x304];
	unsigned *state310;			// +0x310
};

unsigned Rva001736A7Compare(const Rva0017368ATask &a, const Rva0017368ATask &b);

// Rowed: ?sort@_STL@@YAXPAUBfmeAssignRecord32@@0P6A_NABU1@0@Z@Z
void __cdecl rva00174870(BfmeAssignRecord32 *begin, BfmeAssignRecord32 *end, void *compare);

class DynamicVBAccessClass
{
public:
	class WriteLock
	{
	public:
		WriteLock(DynamicVBAccessClass *vb);
		~WriteLock();
		void *m_data;			// +0x04
		char m_pad08[0x0C];
	};
	DynamicVBAccessClass(unsigned a, unsigned b, unsigned short count, unsigned flag);
	~DynamicVBAccessClass();
	char m_pad[0x2C];
};

class Rva0017438B { public: void rva0017438B(int begin, int end); };	// 0x17438B
class Rva00DF6F94GapFillerContext { public: void rva00174350(); };	// 0x174350
class DX8Wrapper { public: static void Set_Vertex_Buffer(const DynamicVBAccessClass &vb); };

class Rva00174A57
{
public:
	void rva00174A57();
	char m_pad00[0x0C];
	int m_start;				// +0x0C
	int m_finish;				// +0x10
};

class FXShaderRenderer : public Rva0017438B, public Rva00DF6F94GapFillerContext,
	public Rva00174A57
{
public:
	void FlushSoftwareSkinnedRenderingTasks();
	void rva00173C04(Rva0017368AMesh *mesh, void *offset);
};

void FXShaderRenderer::FlushSoftwareSkinnedRenderingTasks()
{
	BfmeAssignRecord32 *begin = (BfmeAssignRecord32 *)m_start;
	BfmeAssignRecord32 *end = (BfmeAssignRecord32 *)m_finish;
	if (begin == end)
		return;

	rva00174870(begin, end, &Rva001736A7Compare);

	int total = 0;
	BfmeAssignRecord32 *it;
	for (it = begin; it != end; it = (BfmeAssignRecord32 *)((char *)it + 0x20))
	{
		Rva0017368AMesh *mesh = *(Rva0017368AMesh **)it;
		unsigned *state = mesh->state310;
		if (state == 0 || *state == 0)
		{
			if (state)
				*state = (unsigned)mesh;
			total += ((RvaC4 *)(*(void **)((char *)mesh + 0xc4)))->m_28;
		}
	}

	BfmeAssignRecord32 *batch = begin;
	while (batch != end)
	{
		int budget = total > 0xffff ? 0xffff : total;

		DynamicVBAccessClass vb(2, 5, (unsigned short)budget, 0);
		DynamicVBAccessClass::WriteLock lock(&vb);
		void *buffer = lock.m_data;

		int used = 0;
		for (it = batch; it != end; it = (BfmeAssignRecord32 *)((char *)it + 0x20))
		{
			Rva0017368AMesh *mesh = *(Rva0017368AMesh **)it;
			unsigned *state = mesh->state310;
			int oldUsed = used;
			if (state == 0 || (unsigned)mesh == *state)
			{
				int size = ((RvaC4 *)(*(void **)((char *)mesh + 0xc4)))->m_28;
				if (used + size > budget)
					break;
				rva00173C04(mesh, (char *)buffer + used * 0x2c);
				used += size;
			}
			mesh->m_300 = oldUsed;
		}
		total -= used;
		DX8Wrapper::Set_Vertex_Buffer(vb);
		rva0017438B((int)batch, (int)it);
		batch = it;
	}
	rva00174350();
}
