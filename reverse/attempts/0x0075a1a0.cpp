// ?rva0075A1A0@BfmeThingCGD@@QAEXXZ
// partial score=0.99 date=2026-10-17
// ?rva0075A1A0@BfmeThingCGD@@QAEXXZ
// partial score=0.92 date=2026-10-15
// cl: /MD /EHsc /Ob2 /G6 /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// BANK NOTE: 0.925 under /O2 /G6 without /arch:SSE (FLAG_DEFAULTS=off; region default /arch:SSE emits cmova in the max scans,
// retail has jbe/mov). Remaining residue: retail inlines one level of _Rb_tree::_M_erase inside clear() (loop calling
// _M_erase 0x7590B0 on the right child + free); MSVC 7.1 here refuses to inline the recursive _M_erase (inline, /Ob2,
// inline_recursion(on) all no-op; an inline/__forceinline explicit specialization inlines it into clear but then clear stays out of line).
// Needs pins: operator[] -> 0x0075A120, _M_erase -> 0x007590B0, ~_Rb_tree -> 0x00759B40 (address-named key: placeholder names).
// BfmeThingCGD::bfmeOneCGD, retail 0x00758D10, 193B. Sibling definition lives
// in BfmeConv597.cpp, which already carries the rowed 41B bfmeGoCGD driver
// (0x0075A490) that calls this; the two units agree on one class layout.
//
// The class declares bfmeOneCGD and bfmeTwoCGD but defines neither. This file
// supplies bfmeOneCGD only; bfmeTwoCGD remains the missing 333B provider that
// keeps the home unlinked, and it is NOT claimed here.
//
// Target proof: Ghidra entry 0x00758D10/193, and the only observed native
// entry call at 0x0075A49F lies inside that already byte-verified driver.
// The receiver table at +0xAE10 with 0x493 buckets, the active list at
// +0xC05C, index +0xC064, cursor +0xC068, node links +0x2C/+0x30 and the
// subobject flags at +0x04/+0x10 are target instruction facts, read straight
// off the native body.
//
// BfmeThingCGD and the node/sub-object names are address-derived placeholders:
// retail ties no string, vtable slot or BFME helper to them. The original
// subsystem, class and flag meanings stay unproven. Only the two list links
// carry a role name, being the intrusive-hash-chain idiom already landed in
// Rva009A3770HashChainInsert.cpp and Rva009A2BE0HashIterNext.cpp.
//
// Whole clean BFME1 donor game/Libraries/Source/collisionmanager/
// BfmeConv597.cpp at revision 6583b3c1ff21db4a561285717028fdafc780b7db,
// final /O2. Donor comments describe BFME1 addresses, not target facts.

struct Rva009A2FE0Node;

struct Rva009A2FE0Sub
{
	unsigned char m_pad0[4];
	unsigned m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
};

struct Rva009A2FE0Node
{
	Rva009A2FE0Sub *m_bfme00;
	Rva009A2FE0Sub *m_bfme04;
	unsigned char m_pad8[8];
	unsigned m_bfme10;
	unsigned char m_pad14[0x18];
	Rva009A2FE0Node **m_backSlot;
	Rva009A2FE0Node *m_next;
};

class BfmeThingCGD
{
public:
	void bfmeOneCGD();
	void bfmeTwoCGD();
	void bfmeGoCGD();
	void rva0075A1A0();
	Rva009A2FE0Node *nextNode();
	Rva009A2FE0Node *nextNode2();
	void *m_bfmeFirst;
	unsigned char m_bfmeGap[0x18 - 4];
	Rva009A2FE0Node *m_buckets2[0x2b7b];
	Rva009A2FE0Node *m_active2;
	int m_index2;
	Rva009A2FE0Node *m_cur2;
	Rva009A2FE0Node *m_buckets[0x493];
	Rva009A2FE0Node *m_active;
	int m_index;
	Rva009A2FE0Node *m_cur;
	unsigned char m_bfmeGap1[0xc06d - 0xc068];
	bool m_bfmeBusy;
};

void bfmeGlobalCGD();

// Walk the 0x493-slot table at this+0xAE10 from the cursor at this+0xC064 and
// move every node out of its bucket chain and onto the second list at this+0xC05C
// according to the two sub-object flags.
void BfmeThingCGD::bfmeOneCGD()
{
	Rva009A2FE0Node *nil = 0;
	Rva009A2FE0Node **curp = &m_cur;

	m_index = 0;
	m_cur = m_buckets[0];
	for (;;)
	{
		while (m_cur == nil)
		{
			int i = m_index + 1;

			if (i == 0x493)
				return;
			m_index = i;
			m_cur = m_buckets[i];
		}

		Rva009A2FE0Node *n = m_cur;

		m_cur = m_cur->m_next;
		if (n == nil)
			return;

		if (n->m_bfme00->m_bfme10 == 0 && n->m_bfme04->m_bfme10 == 0)
			continue;

		if (n->m_bfme00->m_bfme04 == 0 || n->m_bfme04->m_bfme04 == 0)
		{
			if (*curp == n)
				*curp = (*curp)->m_next;
			if (n->m_next != nil)
				n->m_next->m_backSlot = n->m_backSlot;
			*n->m_backSlot = n->m_next;
			n->m_backSlot = (Rva009A2FE0Node **)nil;
			n->m_next = m_active;
			m_active = n;
		}
		else
		{
			n->m_bfme10 = 0;
		}
	}
}

// Retail 0x0075A1A0 (747B, RET0 thiscall), sited just before the rowed
// bfmeGoCGD driver 0x0075A490. WorldBuilder twin 0x018062E0 (1212B) is the
// same walk with "collisionmanager_stat" / "Contacts:" / "max on obj "
// debug output; retail keeps only the counting. Target instruction facts:
// both bucket tables are walked through their +0xC060/+0xC064 and
// +0xAE08/+0xAE0C cursors, every node's two sub-object pointers (+0, +4) are
// counted in a local map (find, else operator[] 0x0075A120 = 1), the unsigned
// maximum is scanned (result unused) and the map is cleared between tables
// (_M_erase 0x007590B0) and destroyed at exit (0x00759B40). The key type is
// the address-named sub-object view; the original key/value spelling is
// unproven (retail folds every pointer->unsigned map onto those bodies).

#include <map>

typedef _STL::map<Rva009A2FE0Sub *, unsigned int> Rva0075A1A0Counts;

inline Rva009A2FE0Node *BfmeThingCGD::nextNode()
{
	while (m_cur == 0)
	{
		int i = m_index + 1;

		if (i == 0x493)
			return 0;
		m_index = i;
		m_cur = m_buckets[i];
	}
	Rva009A2FE0Node *n = m_cur;
	m_cur = m_cur->m_next;
	return n;
}

inline Rva009A2FE0Node *BfmeThingCGD::nextNode2()
{
	while (m_cur2 == 0)
	{
		int i = m_index2 + 1;

		if (i == 0x2b7b)
			return 0;
		m_index2 = i;
		m_cur2 = m_buckets2[i];
	}
	Rva009A2FE0Node *n = m_cur2;
	m_cur2 = m_cur2->m_next;
	return n;
}

static inline void rva0075A1A0Count(Rva0075A1A0Counts &counts, Rva009A2FE0Sub *const &key)
{
	Rva0075A1A0Counts::iterator it = counts.find(key);
	if (it == counts.end())
		counts[key] = 1;
	else
		++(*it).second;
}

static inline unsigned int rva0075A1A0Max(Rva0075A1A0Counts &counts)
{
	unsigned int most = 0;
	for (Rva0075A1A0Counts::iterator it = counts.begin(); it != counts.end(); ++it)
		if ((*it).second > most)
			most = (*it).second;
	return most;
}

void BfmeThingCGD::rva0075A1A0()
{
	Rva0075A1A0Counts counts;
	Rva009A2FE0Node *n;

	m_index = 0;
	m_cur = m_buckets[0];
	while ((n = nextNode()) != 0)
	{
		rva0075A1A0Count(counts, n->m_bfme00);
		rva0075A1A0Count(counts, n->m_bfme04);
	}
	{
		unsigned int most = 0;
		for (Rva0075A1A0Counts::iterator it = counts.begin(); it != counts.end(); ++it)
			if ((*it).second > most)
				most = (*it).second;
	}
	counts.clear();

	m_index2 = 0;
	m_cur2 = m_buckets2[0];
	while ((n = nextNode2()) != 0)
	{
		rva0075A1A0Count(counts, n->m_bfme00);
		rva0075A1A0Count(counts, n->m_bfme04);
	}
	rva0075A1A0Max(counts);
}
