// ?refresh@Q1Receiver0134FAAC@@QAEXXZ
// partial score=0.99 date=2026-10-19
// ?refresh@Q1Receiver0134FAAC@@QAEXXZ
// partial score=0.993 date=2026-10-19
// ?refresh@Q1Receiver0134FAAC@@QAEXXZ
// partial score=0.979 date=2026-10-16
// cl: /O2 /G6 /arch:SSE /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /Ireference/shims/bfmealloc /Ireference/shims/sweep
// 0x006227E0 bank 2026-10-19 (claude-opus-5-5): 3244/3244, frame 0xBC, nd 10 (8 instructions + 2 unresolved) with
// two of the old three hacks gone (volatile m_word/m_bits00; the pass-loop queue update is the plain
// bitfield form; q==0 indexes m_deques78[q] directly). Left: `volatile unsigned m_queue : 8` (retail
// always touches it as a full dword and re-reads it with no store between; likely genuinely volatile in
// EA's threaded asset manager - the landed AssetManagerImplUpdate.cpp carries the same), the +0x1E0/+0x1E4
// start-term order (retail s2,s0,s1; ours s2,s1,s0; 36 term orders and 64 reference combos tried), and two
// ledger calls: 0x759BC0 _M_insert needs a fold-proof pin as the multimap<unsigned,Rva009EDBE0Value> tree
// (unsigned jae compares), 0x620A00 ~_Rb_tree owner row (StlSweepR3Rva00620A00.cpp, int key) should be
// renamed to the unsigned-key tree (+ its _M_erase pin 0x620390). Scratch: build/nbr/r10/6227e0/.
// stlport
//
// BFME 1 donor 0x009EFF50 (3186 B); BFME 2 retail 0x006227E0, 3244 B. Identity: the address pin
// plus five matched callers (m009F0BD0, m009F0CC0, m009F19E0, m009F1A60 and
// Gen009F1510::handle) call it as refresh on the g_theAssetRegistry receiver.
// BFME 1 layout (BFME 2 shifts every field past +0x20 by 8, the __int64 pair): lock +0x60, hash_map<int,Element*> +0x44,
// seven deque<Element*> from +0x78, four 0x14-byte set wrappers from +0x190.
//
// Body: under the +0x60 lock, normalise the +0x190/+0x1A4 wrappers through
// m009EFD40; copy +0x190 (0x009EE8E0) and add +0x1B8 into a local key set;
// sweep deques 0..6 marking bit 25 and moving entries whose key membership
// disagrees with (q < 4): queue 3 entries (bit 26 clear) go into a multimap
// keyed by the entry's +0x10 word, queue 4 entries go back to queue 3 (adding
// their slot-0x38 cost to the __int64 at +0x20), queue 0 entries become queue
// 7. Then evict multimap entries to queue 4 while cost >= the __int64 budget at
// +0x28 or the budget is below 2, park the rest in queue 3,
// and twice build a key set (pass 0: +0x1A4 then 0x009EC770 with +0x190 plus
// +0x1B8; pass 1: +0x190 minus +0x1A4) whose queue-7 entries return to queue 0,
// recording the deque 0..2 totals at +0x1E0 / +0x1E4.
//
// Codegen evidence: retail adds/subtracts the cost with adc/sbb 0 and compares
// +0x20 against +0x28 as signed 64-bit values (as the matched Q1ReceiverDrain
// and Rva0061EEE0Destructor layouts declare, class size 0x200); the q==3 test is one conjunction (a nested bit-26 test
// makes MSVC spend its inline budget on queue 3 instead of queue 4, where
// retail inlines _M_advance); the two size sums are separate expressions
// (retail hoists only their node terms); pass 0 adds +0x1B8 through the
// range insert, which MSVC inlines there (cached end, insert_unique(value)
// per key) while the earlier local copy keeps the out-of-line 0x0003AFD0;
// the +0x44 lookup result is a const_iterator (as in the matched
// Queue_Keys_009EFBF0), which is what puts it in memory at retail's slot.
//
// Later evidence (0.979 bank): retail calls set (0x0006BF2A) and pending-tree
// (0x00620A00, its int-key ICF twin) dtors out of line; pass 0 keeps +0x1A4
// through Rva0061F910Set::retain (0x0061FAA0) and pass 1 subtracts through
// 0x0061F910; the pending entry is pushed as an lvalue (reloaded in both
// push_back paths); a right-associated s0 + (s1 + s2) size sum gets closest.

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

struct Rva009EDBE0Value
{
	Rva009EF0D0Element *m_entry;
};

typedef _STL::multimap<unsigned int, Rva009EDBE0Value> Q1ReceiverPending;
namespace _STL {
template <> _Rb_tree<unsigned int, pair<const unsigned int, Rva009EDBE0Value>,
	_Select1st<pair<const unsigned int, Rva009EDBE0Value> >, less<unsigned int>,
	allocator<pair<const unsigned int, Rva009EDBE0Value> > >::~_Rb_tree();
}
typedef _STL::pair<const unsigned int, Rva009EDBE0Value> Q1ReceiverPendingPair;
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
				Q1ReceiverPendingPair value(entry->m_field10, Rva009EDBE0Value());
				const_cast<Rva009EDBE0Value &>(value.second).m_entry = entry;
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
