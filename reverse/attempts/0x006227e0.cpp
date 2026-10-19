// ?refresh@Q1Receiver0134FAAC@@QAEXXZ
// partial score=0.9975339087546239 date=2026-10-19
// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/sweep
// stlport
// Refresh at retail 006227E0..0062348C, 3244 bytes; banked, not matched.
// 2026-10-19: complete3244B, frame0xBC and EH graph exact; actual ledger
// bindings resolve every callee. Eight start-cursor displacement operands
// differ in the two final count branches: native s2,s0,s1; ours s2,s1,s0.
// See reverse/attempt_support/asset-refresh-parent-20261019/readme.md.
// Pending key/payload are target-proven unsigned / element pointer; reuse
// the corrected Rva00620A00Record and admitted insertion/copy identities.
// Source type spelling remains neutral inference, not an original name.
// The obsolete const_cast on the non-const second member is removed at parity.
//
// BFME1 009EFF50 is the semantic guide. Five matched target callers and the
// existing refresh pin establish this member's relationship to the asset
// registry receiver. Legacy field labels retain donor offsets: native lock
// is +68, hash map +4C, seven deques +80, set wrappers +198/+1AC/+1C0/+1D4,
// and output counters +1E8/+1EC. Size200 is checked below.
// The +20/+28 cost and budget are signed64: native adc/sbb0 of unsigned
// slot38 cost, signed64 comparisons. Pending entries are key+pointer pairs.
//
// Under the lock, normalize/copy the known-key sets; sweep seven queues;
// collect eligible queue3 entries in the pending multimap, move queue4
// entries to3, and evict by cost/budget. Retain/subtract key-set passes
// return queue7 entries to0 and record active deque0..2 totals.
// The volatile eight-bit queue field remains supported by native full-word
// accesses/reloads and the landed AssetManagerImplUpdate sibling. No new
// compiler barrier, volatile local, naked body or inline assembly is used.

#include <deque>
#include <hash_map>
#include <map>
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>
#include <windows.h>

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<Rva001408C0Key> Rva001408C0Set;
namespace _STL {
template <> _Rb_tree<Rva001408C0Key, Rva001408C0Key, _Identity<Rva001408C0Key>,
	less<Rva001408C0Key>, allocator<Rva001408C0Key> >::~_Rb_tree();
}

struct Gen_t_009ee8e0_k4
{
	int a[1];
	Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4(const Gen_t_009ee8e0_k4 &);
	~Gen_t_009ee8e0_k4();
	Gen_t_009ee8e0_k4 &operator=(const Gen_t_009ee8e0_k4 &);
};

bool operator<(const Gen_t_009ee8e0_k4 &, const Gen_t_009ee8e0_k4 &);
typedef _STL::set<Gen_t_009ee8e0_k4> Q1ReceiverSet;

struct Q1ReceiverTreeStorage
{
	Q1ReceiverTreeStorage(const Q1ReceiverSet &source);
	~Q1ReceiverTreeStorage()
	{
		get().~Rva001408C0Set();
	}
	Rva001408C0Set &get() { return *(Rva001408C0Set *)m_storage; }
	int m_storage[sizeof(Rva001408C0Set) / sizeof(int)];
};

struct Q1ReceiverLocalSet
{
	Q1ReceiverTreeStorage m_set;
	int m_zero;
	bool m_one;
};

class BfmeThingBVA
{
public:
	BfmeThingBVA()
	{
		m_value = 0;
		m_active = true;
	}

	BfmeThingBVA &operator=(BfmeThingBVA &other)
	{
		if (this != &other)
		{
			bfmeStepBVA(&other);
			m_active = true;
			m_value = other.m_value;
		}
		return *this;
	}

	void bfmeStepBVA(BfmeThingBVA *other);

	Rva001408C0Set m_tree;
	unsigned int m_value;
	bool m_active;
};

class Rva0061F910Set
{
public:
	Rva0061F910Set &subtract(const Rva0061F910Set &other);
	Rva0061F910Set &retain(const Rva0061F910Set &other);
};

class Rva009EF0D0Element
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void slot28();
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual int slot38();

	union
	{
		unsigned int m_word;
		struct
		{
			unsigned int m_bits00 : 16;
			volatile unsigned int m_queue : 8;
			unsigned int m_bit24 : 1;
			unsigned int m_bit25 : 1;
			unsigned int m_bit26 : 1;
		};
	};
	int m_key08;
	int m_field0c;
	unsigned int m_field10;
};

struct Rva00620A00Record
{
	Rva009EF0D0Element *m_entry;
};

typedef _STL::multimap<unsigned int, Rva00620A00Record> Q1ReceiverPending;
namespace _STL {
template <> _Rb_tree<unsigned int, pair<const unsigned int, Rva00620A00Record>,
	_Select1st<pair<const unsigned int, Rva00620A00Record> >, less<unsigned int>,
	allocator<pair<const unsigned int, Rva00620A00Record> > >::~_Rb_tree();
}
typedef _STL::pair<const unsigned int, Rva00620A00Record> Q1ReceiverPendingPair;
typedef _STL::hash_map<int, Rva009EF0D0Element *> Q1ReceiverAssetHash;
typedef _STL::deque<int> Q1ReceiverQueue;

class Q1ReceiverLock
{
public:
	explicit Q1ReceiverLock(CRITICAL_SECTION *lock) : m_lock(lock)
	{
		EnterCriticalSection(m_lock);
	}
	~Q1ReceiverLock()
	{
		LeaveCriticalSection(m_lock);
	}

	CRITICAL_SECTION *m_lock;
};

class Q1Receiver0134FAAC
{
public:
	void refresh();
	void m009EFD40(Q1ReceiverLocalSet *set);

private:
	unsigned int m_thread;
	unsigned char m_unmodelled_004[0x1C];
	__int64 m_field20;
	__int64 m_limit28;
	unsigned int m_field30;
	CRITICAL_SECTION m_lock2c;
	Q1ReceiverAssetHash m_map44;
	unsigned char m_unmodelled_058[8];
	CRITICAL_SECTION m_lock60;
	Q1ReceiverQueue m_deques78[7];
	BfmeThingBVA m_set190;
	BfmeThingBVA m_set1a4;
	BfmeThingBVA m_set1b8;
	BfmeThingBVA m_set1cc;
	unsigned int m_field1e0;
	unsigned int m_field1e4;
	unsigned char m_unmodelled_1e8[0x0C];
};

typedef char Q1ReceiverRefreshSizeCheck[sizeof(Q1Receiver0134FAAC) == 0x200 ? 1 : -1];

void Q1Receiver0134FAAC::refresh()
{
	Q1ReceiverLock lock(&m_lock60);
	m009EFD40((Q1ReceiverLocalSet *)&m_set190);
	m009EFD40((Q1ReceiverLocalSet *)&m_set1a4);

	Q1ReceiverPending pending;
	Q1ReceiverLocalSet known = { *(const Q1ReceiverSet *)&m_set190, 0, true };
	known.m_set.get().insert(m_set1b8.m_tree.begin(), m_set1b8.m_tree.end());
	known.m_one = true;

	for (int q = 0; q < 7; ++q)
	{
		for (unsigned int i = 0; i < m_deques78[q].size(); ++i)
		{
			Rva009EF0D0Element *entry = (Rva009EF0D0Element *)m_deques78[q][i];
			if ((known.m_set.get().find((Rva001408C0Key)entry->m_key08) !=
					known.m_set.get().end()) == (q < 4))
				continue;
			entry->m_bit25 = q > 3;
			if (q == 3 && !entry->m_bit26)
			{
				Q1ReceiverPendingPair value(entry->m_field10, Rva00620A00Record());
				value.second.m_entry = entry;
				pending.insert(value);
				Q1ReceiverQueue &q3 = m_deques78[3];
				q3[i] = q3[q3.size() - 1];
				q3.pop_back();
				--i;
			}
			else if (q == 4)
			{
				entry->m_queue = 3;
				m_field20 += (unsigned int)entry->slot38();
				Q1ReceiverQueue &q4 = m_deques78[4];
				m_deques78[entry->m_queue].push_back(q4[i]);
				q4[i] = q4[q4.size() - 1];
				q4.pop_back();
				--i;
			}
			else if (q == 0)
			{
				entry->m_queue = 7;
				m_deques78[q][i] = m_deques78[q][m_deques78[q].size() - 1];
				m_deques78[q].pop_back();
				--i;
			}
		}
	}

	while ((m_field20 >= m_limit28 || m_limit28 < 2) && pending.size() != 0)
	{
		Rva009EF0D0Element *entry = pending.begin()->second.m_entry;
		pending.erase(pending.begin());
		entry->m_queue = 4;
		m_field20 -= (unsigned int)entry->slot38();
		m_deques78[entry->m_queue].push_back((int)entry);
		if (m_field20 < 0)
			m_field20 = 0;
	}

	for (Q1ReceiverPending::iterator it = pending.begin(); it != pending.end(); ++it)
		m_deques78[3].push_back(*(const int *)&it->second.m_entry);

	Q1ReceiverQueue *queues = m_deques78;
	for (int pass = 0; pass < 2; ++pass)
	{
		BfmeThingBVA keys;
		if (pass == 0)
		{
			keys = m_set1a4;
			((Rva0061F910Set *)&keys)->retain(*(Rva0061F910Set *)&m_set190);
			keys.m_tree.insert(m_set1b8.m_tree.begin(), m_set1b8.m_tree.end());
			keys.m_active = true;
		}
		else
		{
			keys = m_set190;
			((Rva0061F910Set *)&keys)->subtract(*(Rva0061F910Set *)&m_set1a4);
		}

		for (Rva001408C0Set::iterator it = keys.m_tree.begin(); it != keys.m_tree.end(); ++it)
		{
			Q1ReceiverAssetHash::const_iterator found = m_map44.find((int)*it);
			if (found != m_map44.end())
			{
				Rva009EF0D0Element *asset = (*found).second;
				if (asset->m_queue == 7)
				{
					asset->m_queue = 0;
					asset->m_bit25 = 1;
					m_deques78[asset->m_queue].push_back((int)asset);
				}
			}
		}

		if (pass == 0)
			m_field1e0 = queues[0].size() + queues[1].size() + queues[2].size();
		else
			m_field1e4 = queues[0].size() + queues[1].size() + queues[2].size() - m_field1e0;
	}
}
