// ?rva0054034A@Rva0054034A@@QAE_NH@Z
// partial score=0.95 date=2026-10-16
// ?rva0054034A@Rva0054034A@@QAE_NH@Z
// W9-O2 bank: whole home TU Code/GameEngine/Source/Common/Rva0054034ALocate.cpp
// with the class's +0x10 key vector as a real KeyVector40 member (inline
// size()/empty(), the matched 0x00541641 sibling's shape incl. its outer
// equal-arm block): fast path and slow-path call/store block now exact (rows
// 0x00540301 and 0x00540A26 in this TU stay exact). Residue: the tail keeps
// key in EAX (loaded once before jae) where retail reloads [ebp+8] at both
// compares (as if the --hint store may alias key).
// cl: /O1 /Oy- /DNDEBUG /MD /EHsc /G7
//
// ?rva00540301@@YAPAUBfmePod40@@PAU1@0ABU1@@Z @ 0x00540301 35B
// Evidence: lower_bound wrapper mirror of the verified 0x005414C2 wrap
// (less temp plus null distance tag around the rowed Pod40
// __lower_bound at 0x00540253). The 200B sorted-key locator caller at
// 0x0054034A is banked as a partial (same TU shape stashed) pending
// fast-path regalloc work: hint must stay in ECX with late push-edi,
// EDI divisor and real imul-40 (this TU's /G7 emits the imul).
// Names are generated.
struct BfmePod40
{
	int m_00;
	char m_pad04[0x24];
};

namespace _STL
{
	template <class _Tp>
	struct less
	{
	};
	template <class _Fwd, class _T, class _C, class _D>
	_Fwd __lower_bound(_Fwd, _Fwd, const _T &, _C, _D *);
	template <class T>
	class allocator
	{
	};
	template <class T, class A>
	class vector
	{
	public:
		void push_back(const T &x);
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

BfmePod40 *rva00540301(BfmePod40 *first, BfmePod40 *last, const BfmePod40 &value)
{
	return _STL::__lower_bound(first, last, value, _STL::less<BfmePod40>(), (int *)0);
}

class Rva0054000B
{
public:
	Rva0054000B();
	int m_00;
private:
	char m_pad04[0x24];
};

// The retail class this view spells Rva0054034A: the rowed ctor at 0x00540B03
// (Rva00540B03Ctors.cpp) ends with a call to rva00540A26 below on a
// reinterpret_cast<Rva0054034A *> view, and Rva00540888CameraTransform.cpp
// holds one at +0x24. Layout: a 40-byte sorted key vector (begin +0x10, end
// +0x14) plus an int hint at +0x1C.

struct KeyVector40
{
	unsigned int size() const { return m_end - m_begin; }
	bool empty() const { return m_begin == m_end; }
	BfmePod40 *m_begin, *m_end, *m_capacity;
};
class Rva0054034A
{
public:
	void rva005404CF(int value);
	void rva00540A26();
	bool rva0054034A(int key);
private:
	char m_pad00[0x10];
	KeyVector40 m_keys;
	int m_hint1C;
};

void Rva0054034A::rva00540A26()
{
	typedef _STL::vector<Rva0054000B, _STL::allocator<Rva0054000B> > Vec4000B;
	BfmePod40 **vec = &m_keys.m_begin;
	while ((unsigned int)(((char *)vec[1] - (char *)vec[0]) / 40) > 1)
		rva005404CF(m_keys.m_begin[1].m_00);
	Rva0054000B tmp;
	tmp.m_00 = 0;
	((Vec4000B *)vec)->push_back(tmp);
}

bool Rva0054034A::rva0054034A(int key)
{
if ((m_keys.m_end != 0 || m_keys.m_end == 0)) {
	int h = m_hint1C;
	if (h >= 0 && (unsigned)h < m_keys.size()) {
		BfmePod40 *b = m_keys.m_begin;
		int cur = b[h].m_00;
		if (key >= cur && ((unsigned)(h + 1) >= (unsigned)(m_keys.m_end - b) || key < b[h + 1].m_00))
			return cur == key;
	}
	if (m_keys.empty())
	{
		m_hint1C = -1;
		return false;
	}
	int &hint = m_hint1C;
	BfmePod40 *b = m_keys.m_begin;
	hint = rva00540301(b, m_keys.m_end, *reinterpret_cast<const BfmePod40 *>(&key)) - b;
	if ((unsigned)hint >= (unsigned)(m_keys.m_end - b) || (hint > 0 && b[hint].m_00 != key))
		--hint;
	return m_keys.m_begin[m_hint1C].m_00 == key;
}
}
