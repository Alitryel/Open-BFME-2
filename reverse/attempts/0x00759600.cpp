// ?UpdateSort@CollisionManagerImpl@@QAEXXZ
// partial score=0.81 date=2026-10-17
// ?UpdateSort@CollisionManagerImpl@@QAEXXZ
// partial score=0.787 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?UpdateSort@CollisionManagerImpl@@QAEXXZ
// partial score=0.78 date=2026-10-14
// ?UpdateSort@CollisionManagerImpl@@QAEXXZ
// partial score=0.78 date=2026-10-14
// Draft from the BFME1 donor bank reference/open-bfme-1/targets/game/reverse/
// attempts/0x009a3ad0.cpp (b1 0x009A3AD0 refresh) against WB 1804B90
// CollisionManagerImpl::UpdateSort (collisionmanager_impl.cpp:467..607) and
// retail 0x00759600 (1244B). Layouts are the rowed collision-family views.
// cl: /O2 /DNDEBUG /MD

typedef float Real;

void __cdecl operator delete(void *block);

namespace CollisionManager
{
	class Data
	{
	public:
		int UpdateCoord(bool removeAndReInsert);
	};
}

class Rva009A45A0CollisionData;
class Rva009A36F0Thing;
struct Rva009A3540OpaqueOwner;

struct Rva009A3AD0Endpoint
{
	Rva009A3AD0Endpoint *m_prev;	// +0x00
	Rva009A3AD0Endpoint *m_next;	// +0x04
	Rva009A45A0CollisionData *m_node;	// +0x08
	bool m_isMax : 1;	// +0x0c
	Real m_value;	// +0x10

	bool isMin() const { return !m_isMax; }
};

struct Rva009A3AD0Interval
{
	Rva009A3AD0Endpoint m_min;
	Rva009A3AD0Endpoint m_max;
};

class Rva009A45A0CollisionData
{
public:
	~Rva009A45A0CollisionData();

	void *m_owner;	// +0x00
	void *m_source;	// +0x04
	void *m_rootPrev;	// +0x08
	Rva009A45A0CollisionData *m_rootNext;	// +0x0c
	void *m_dirtyPrev;	// +0x10
	Rva009A45A0CollisionData *m_dirtyNext;	// +0x14
	Rva009A45A0CollisionData **m_openPrev;	// +0x18
	Rva009A45A0CollisionData *m_openNext;	// +0x1c
	int m_rva009A3AD0_020;	// +0x20
	union
	{
		Rva009A3AD0Endpoint m_endpoints[6];	// +0x24
		Rva009A3AD0Interval m_intervals[3];
	};
};

class BfmeLinkXX
{
public:
	void bfmeDropXX();
};

class Rva007589F0
{
public:
	void collectAll();
};

class Rva00758B20
{
public:
	void collectAll();
};

// 0x00759490 is rowed as Rva009A3540PairOwner::rva00759490 (the donor's
// CollisionManagerImpl::_AddOverlap); 0x007586F0 is still an unrowed placeholder.
class Rva009A3540PairOwner
{
public:
	void rva00759490(Rva009A3540OpaqueOwner *a, Rva009A3540OpaqueOwner *b);
};

class Rva007586F0Callee
{
public:
	void rva007586F0();
};

class CollisionManagerImpl
{
public:
	void UpdateSort();
	void unlinkChain(Rva009A36F0Thing *thing);
	void _RemoveOverlap(Rva009A3540OpaqueOwner *a, Rva009A3540OpaqueOwner *b);
	void rva009A2750();
	void insertSorted(Rva009A45A0CollisionData *node, Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head);
	void pushFront(Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head);

	Rva009A45A0CollisionData *m_root;	// +0x00
	unsigned int m_nodeCount;	// +0x04
	Rva009A45A0CollisionData *m_dirty;	// +0x08
	Rva009A3AD0Endpoint *m_axisHeads[3];	// +0x0c
	unsigned char m_table[0xAE10 - 0x18];
	unsigned char m_table2[0xC068 - 0xAE10];
	unsigned int m_axisCount;	// +0xc068
	bool m_rebuild;	// +0xc06c
};

__forceinline void CollisionManagerImpl::insertSorted(Rva009A45A0CollisionData *node, Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head)
{
	Rva009A3AD0Endpoint *cur = *head;
	Rva009A3AD0Endpoint *prev = 0;
	Rva009A45A0CollisionData *open = 0;
	Real value = axis->m_max.m_value;
	while (cur != 0 && !(cur->m_value > value))
	{
		if (cur->isMin())
		{
			cur->m_node->m_openPrev = &open;
			cur->m_node->m_openNext = open;
			if (cur->m_node->m_openNext != 0)
				cur->m_node->m_openNext->m_openPrev = &cur->m_node->m_openNext;
			open = cur->m_node;
		}
		else
		{
			if (cur->m_node->m_openNext != 0)
				cur->m_node->m_openNext->m_openPrev = cur->m_node->m_openPrev;
			*cur->m_node->m_openPrev = cur->m_node->m_openNext;
			cur->m_node->m_openPrev = 0;
		}
		prev = cur;
		cur = cur->m_next;
	}

	axis->m_max.m_prev = prev;
	axis->m_max.m_next = cur;
	if (prev != 0)
		prev->m_next = &axis->m_max;
	else
		*head = &axis->m_max;
	if (cur != 0)
		axis->m_max.m_next->m_prev = &axis->m_max;
	prev = &axis->m_max;

	if (cur != 0)
	{
		while (open != 0)
		{
			((Rva009A3540PairOwner *)this)->rva00759490((Rva009A3540OpaqueOwner *)open, (Rva009A3540OpaqueOwner *)node);
			Rva009A45A0CollisionData *closed = open;
			if (closed->m_openNext != 0)
				closed->m_openNext->m_openPrev = closed->m_openPrev;
			*closed->m_openPrev = closed->m_openNext;
			closed->m_openPrev = 0;
		}
		value = axis->m_min.m_value;
		do
		{
			if (!(cur->m_value < value))
				break;
			if (cur->isMin())
				((Rva009A3540PairOwner *)this)->rva00759490((Rva009A3540OpaqueOwner *)cur->m_node, (Rva009A3540OpaqueOwner *)node);
			prev = cur;
			cur = cur->m_next;
		}
		while (cur != 0);
	}

	axis->m_min.m_prev = prev;
	axis->m_min.m_next = cur;
	prev->m_next = &axis->m_min;
	if (cur != 0)
		axis->m_min.m_next->m_prev = &axis->m_min;
}

__forceinline void pushHead(Rva009A3AD0Endpoint *endpoint, Rva009A3AD0Endpoint **head)
{
	endpoint->m_prev = 0;
	endpoint->m_next = *head;
	if (endpoint->m_next != 0)
		endpoint->m_next->m_prev = endpoint;
	*head = endpoint;
}

__forceinline void CollisionManagerImpl::pushFront(Rva009A3AD0Interval *axis, Rva009A3AD0Endpoint **head)
{
	pushHead(&axis->m_min, head);
	pushHead(&axis->m_max, head);
}

void CollisionManagerImpl::UpdateSort()
{
	unsigned int totalScore = 0;
	Rva009A45A0CollisionData *node = m_dirty;
	while (node != 0)
	{
		unsigned int score = ((CollisionManager::Data *)node)->UpdateCoord(true);
		if (score == 0)
		{
			node = node->m_dirtyNext;
			continue;
		}
		totalScore += score;
		unlinkChain((Rva009A36F0Thing *)node);
		Rva009A45A0CollisionData *next = node->m_dirtyNext;
		if (node->m_source != 0)
		{
			if (node->m_endpoints[0].m_prev != 0)
			{
				unsigned int index = 0;
				do
				{
					Rva009A3AD0Endpoint *endpoint = &node->m_endpoints[index];
					if (endpoint->m_prev != 0)
						endpoint->m_prev->m_next = endpoint->m_next;
					else
						m_axisHeads[index >> 1] = endpoint->m_next;
					if (endpoint->m_next != 0)
						endpoint->m_next->m_prev = endpoint->m_prev;
					endpoint->m_prev = 0;
					endpoint->m_next = 0;
					++index;
				}
				while (index < 6);
			}

			unsigned int k = 0;
			do
			{
				if (k < m_axisCount && !m_rebuild)
					insertSorted(node, &node->m_intervals[k], &m_axisHeads[k]);
				else
					pushFront(&node->m_intervals[k], &m_axisHeads[k]);
				++k;
			}
			while (k < 3);

			((BfmeLinkXX *)node)->bfmeDropXX();
		}
		else
		{
			delete node;
		}
		node = next;
	}

	while (m_dirty != 0)
	{
		totalScore += ((CollisionManager::Data *)m_dirty)->UpdateCoord(false);
		((BfmeLinkXX *)m_dirty)->bfmeDropXX();
	}

	if (m_root == 0)
		return;

	if (totalScore * 100 <= m_nodeCount * 100 && !m_rebuild)
	{
		for (unsigned int k = 0; k < m_axisCount; ++k)
		{
			Rva009A3AD0Endpoint **head = &m_axisHeads[k];
			Rva009A3AD0Endpoint *cur = (*head)->m_next;
			while (cur != 0)
			{
				if (cur->m_prev->m_value <= cur->m_value)
				{
					cur = cur->m_next;
					continue;
				}
				Rva009A3AD0Endpoint *pos = cur;
				if (cur->m_prev != 0)
				{
					do
					{
						Rva009A3AD0Endpoint *before = pos->m_prev;
						if (!(before->m_value > cur->m_value))
							break;
						if (before->m_isMax && cur->isMin())
							((Rva009A3540PairOwner *)this)->rva00759490((Rva009A3540OpaqueOwner *)before->m_node, (Rva009A3540OpaqueOwner *)cur->m_node);
						else if (before->isMin() && cur->m_isMax)
							_RemoveOverlap(
								(Rva009A3540OpaqueOwner *)before->m_node,
								(Rva009A3540OpaqueOwner *)cur->m_node);
						pos = pos->m_prev;
					}
					while (pos->m_prev != 0);
				}

				Rva009A3AD0Endpoint *next = cur->m_next;
				if (cur->m_prev != 0)
					cur->m_prev->m_next = cur->m_next;
				else
					*head = cur->m_next;
				if (cur->m_next != 0)
					cur->m_next->m_prev = cur->m_prev;
				cur->m_prev = 0;
				cur->m_next = 0;

				cur->m_prev = pos->m_prev;
				cur->m_next = pos;
				pos->m_prev = cur;
				if (cur->m_prev != 0)
					cur->m_prev->m_next = cur;
				else
					*head = cur;
				cur = next;
			}
		}
		return;
	}

	m_rebuild = false;
	((Rva007589F0 *)((char *)this + 0x18))->collectAll();
	((Rva00758B20 *)((char *)this + 0xAE10))->collectAll();
	for (Rva009A45A0CollisionData *root = m_root; root != 0; root = root->m_rootNext)
		root->m_rva009A3AD0_020 = 0;
	((Rva007586F0Callee *)this)->rva007586F0();

	for (unsigned int k = 0; k < m_axisCount; ++k)
	{
		Rva009A45A0CollisionData *open = 0;
		for (Rva009A3AD0Endpoint *cur = m_axisHeads[k]; cur != 0; cur = cur->m_next)
		{
			if (cur->isMin())
			{
				for (Rva009A45A0CollisionData *other = open; other != 0; other = other->m_openNext)
					((Rva009A3540PairOwner *)this)->rva00759490((Rva009A3540OpaqueOwner *)other, (Rva009A3540OpaqueOwner *)cur->m_node);
				cur->m_node->m_openPrev = &open;
				cur->m_node->m_openNext = open;
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = &cur->m_node->m_openNext;
				open = cur->m_node;
			}
			else
			{
				if (cur->m_node->m_openNext != 0)
					cur->m_node->m_openNext->m_openPrev = cur->m_node->m_openPrev;
				*cur->m_node->m_openPrev = cur->m_node->m_openNext;
				cur->m_node->m_openPrev = 0;
			}
		}
	}
}
