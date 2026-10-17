// ?FlushSoftwareSkinnedRenderingTasks@FXShaderRenderer@@QAEXXZ
// partial score=0.895 date=2026-10-17
// ?FlushSoftwareSkinnedRenderingTasks@FXShaderRenderer@@QAEXXZ
// partial score=0.82 date=2026-10-15
// cl: /O1 /G7 /MD /EHsc
//
// ?FlushSoftwareSkinnedRenderingTasks@FXShaderRenderer@@QAEXXZ, retail
// 0x001748E8 (367B). WB 0x00A21A90 names it. Sorts the pending 32-byte
// rendering tasks (+0x0C..+0x10) with the rowed comparator 0x001736A7,
// sums the skinned vertex counts of the meshes that claim their shared
// state (mesh +0x310), then fills dynamic vertex buffers of at most 0xFFFF
// vertices batch by batch: each claiming mesh is skinned into the locked
// buffer (0x00173C04) at its running offset, which every task's mesh
// records at +0x300, the buffer is bound, the batch's tasks are rendered
// (0x0017438B), and finally the task list is cleared (0x00174350).
//
// Evidence (target): every call (the rowed DynamicVBAccessClass, its
// WriteLock and destructors, DX8Wrapper::Set_Vertex_Buffer, the existing
// sort / render / clear spellings), the 0x2C-byte skinned vertex stride and
// the mesh fields +0xC4 (+0x28 vertex count), +0x300, +0x310. The task and
// mesh record names are address-derived.

struct Rva0017368ATask;

// The skinned mesh as the flush reads it.
struct Rva0017368AMeshCounts
{
	char m_pad00[0x28];
	int m_vertexCount; // +0x28
};

struct Rva0017368AMesh
{
	char m_pad000[0xC4];
	Rva0017368AMeshCounts *m_counts; // +0xC4
	char m_pad0C8[0x300 - 0xC8];
	int m_vertexOffset;              // +0x300
	char m_pad304[0x310 - 0x304];
	Rva0017368AMesh **m_state;       // +0x310
};

struct Rva0017368ATask
{
	Rva0017368AMesh *mesh;
	char unknown[28];
};

unsigned Rva001736A7Compare(const Rva0017368ATask &a, const Rva0017368ATask &b);
void rva00174870(int begin, int end, int compare);

class DynamicVBAccessClass
{
public:
	DynamicVBAccessClass(unsigned type, unsigned format_index, unsigned short vertex_count, unsigned declaration);
	~DynamicVBAccessClass();

	class WriteLock
	{
	public:
		WriteLock(DynamicVBAccessClass *vb);
		~WriteLock();
		void *Get_Data() const { return m_data; }
	private:
		DynamicVBAccessClass *m_owner;
		void *m_data;
		int m_guard;
	};

private:
	const void *m_format;
	unsigned m_type, m_formatIndex, m_declaration;
	unsigned short m_vertexCount, m_vertexOffset;
	void *m_buffer;
};

class DX8Wrapper
{
public:
	static void Set_Vertex_Buffer(const DynamicVBAccessClass &vb);
};

class Rva0017438B { public: void rva0017438B(int begin, int end); };
class Rva00DF6F94GapFillerContext { public: void rva00174350(); };

class FXShaderRenderer
{
public:
	void FlushSoftwareSkinnedRenderingTasks();
	void rva00173C04(Rva0017368AMesh *mesh, void *vertices);
private:
	char m_pad00[0x0C];
	// The pending task list (an STLport vector of 32-byte tasks).
	struct TaskList
	{
		bool empty() const { return m_begin == m_end; }
		Rva0017368ATask *begin() const { return m_begin; }
		Rva0017368ATask *end() const { return m_end; }
		Rva0017368ATask *m_begin;
		Rva0017368ATask *m_end;
	} m_tasks; // +0x0C
};

// ?FlushSoftwareSkinnedRenderingTasks@FXShaderRenderer@@QAEXXZ @0x001748E8
void FXShaderRenderer::FlushSoftwareSkinnedRenderingTasks()
{
	if (m_tasks.empty())
		return;

	rva00174870((int)m_tasks.begin(), (int)m_tasks.end(), (int)&Rva001736A7Compare);

	int remaining = 0;
	Rva0017368ATask *it = m_tasks.begin();
	do
	{
		Rva0017368AMesh *mesh = it->mesh;
		Rva0017368AMesh **state = (1 ? mesh->m_state : mesh->m_state);
		if (!state || !*state)
		{
			if (state)
				*state = mesh;
			remaining += mesh->m_counts->m_vertexCount;
		}
		++it;
	} while (it != m_tasks.end());

	Rva0017368ATask *batchInit = m_tasks.begin();
	for (Rva0017368ATask *batch = batchInit; batch != m_tasks.end(); )
	{
		Rva0017368ATask *task = batch;
		int budget = remaining;
		if (budget > 0xFFFF)
			budget = 0xFFFF;

		int used = 0;
		DynamicVBAccessClass vb(2, 5, (unsigned short)budget, 0);
		used = 0;
		{
			DynamicVBAccessClass::WriteLock lock(&vb);
			char *vertices = (char *)lock.Get_Data();
			int offset = 0;
			for (; m_tasks.end() != task; ++task)
			{
				Rva0017368AMesh *mesh = task->mesh;
				Rva0017368AMesh **state = (1 ? mesh->m_state : mesh->m_state);
				Rva0017368AMesh *claimed = (state != 0 ? *state : *state);
				if (mesh == claimed)
				{
					if (mesh->m_counts->m_vertexCount + used > budget)
						break;
					rva00173C04(mesh, vertices + used * 0x2C);
					offset = used;
					used += mesh->m_counts->m_vertexCount;
				}
				mesh->m_vertexOffset = offset;
			}
			remaining = *(volatile int *)&remaining - used;
		}
		DX8Wrapper::Set_Vertex_Buffer(vb);
		((Rva0017438B *)this)->rva0017438B((int)batch, (int)task);
		batch = task;
	}
	((Rva00DF6F94GapFillerContext *)this)->rva00174350();
}
