// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// Split from Rva0054BBB5.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// SimpleObjectIterator::insert (WorldBuilder name, SimpleObjectIterator.cpp line 62: deque push_back of the pair); 0x0054B414 (deque clear) is on the same class.
// stlport
//
// was ?rva0054BBB5@Rva0054BBB5@@QAEXHM@Z, retail 0x0054BBB5, 37 bytes.
// Packs (int, float) into BfmeE8 temp and deque push_back at this+0x14.
// Evidence: prev 0x0054B850 deque push_back rowed, retail movss plus
// lea [ebp-8] plus add ecx 0x14 plus ret 8, 15 callers.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>

struct BfmeE8
{
	int a;
	float b;
};

// The existing cleanup provider names only the established eight-byte record
// width. Its external declaration preserves the native potentially-throwing
// member cleanup, including the base destructor's exceptional path.
struct BfmeTrivialDequeElement8 { unsigned char opaque[8]; };
namespace _STL {
template<> deque<BfmeTrivialDequeElement8,allocator<BfmeTrivialDequeElement8> >::~deque();
}

// Native tables C6A68C and C6A698 share the empty base destructor and two
// iterator slots. Keep the existing base owner spelling rather than guessing
// a new name. Its layout is four bytes; the derived cursor occupies +4..+14.
class Rva00549C74 {
public:
	__declspec(dllimport) __forceinline Rva00549C74() {}
	virtual ~Rva00549C74() {}
	virtual int first() = 0;
	virtual int next() = 0;
};


#include <algorithm>
// bfme link decl-only begin
namespace _STL { template <> void deque<BfmeE8, allocator<BfmeE8> >::_M_push_back_aux_v(BfmeE8 const &); }
// bfme link decl-only end
struct Foo00549DCB;
struct BfmeCopyRecord8 {
 Foo00549DCB *a; float b;
 BfmeCopyRecord8() {}
 BfmeCopyRecord8(const BfmeCopyRecord8 &o): a(o.a),b(o.b) {}
};
struct BfmeCopyRecord8Cmp { bool operator()(const BfmeCopyRecord8 &, const BfmeCopyRecord8 &) const; };
struct BfmeCopyRecord8CmpDescending { bool operator()(const BfmeCopyRecord8 &, const BfmeCopyRecord8 &) const; };
struct BfmeCopyRecord8KeyAscending { bool operator()(const BfmeCopyRecord8 &, const BfmeCopyRecord8 &) const; };
struct BfmeCopyRecord8KeyDescending { bool operator()(const BfmeCopyRecord8 &, const BfmeCopyRecord8 &) const; };
typedef _STL::_Deque_iterator<BfmeCopyRecord8,_STL::_Nonconst_traits<BfmeCopyRecord8> > CopyRecord8Iterator;
namespace _STL {
template<> void sort(CopyRecord8Iterator,CopyRecord8Iterator,BfmeCopyRecord8Cmp);
template<> void sort(CopyRecord8Iterator,CopyRecord8Iterator,BfmeCopyRecord8CmpDescending);
template<> void sort(CopyRecord8Iterator,CopyRecord8Iterator,BfmeCopyRecord8KeyAscending);
template<> void sort(CopyRecord8Iterator,CopyRecord8Iterator,BfmeCopyRecord8KeyDescending);
}
// Zero Hour ObjectIter.h supplies the order names. Native 54C64A dispatches
// 1..4 to the four already-owned float/key sorts in that order.
enum IterOrderType {
 ITER_FASTEST,
 ITER_SORTED_NEAR_TO_FAR,
 ITER_SORTED_FAR_TO_NEAR,
 ITER_SORTED_CHEAP_TO_EXPENSIVE,
 ITER_SORTED_EXPENSIVE_TO_CHEAP
};

class SimpleObjectIterator : public Rva00549C74
{
public:
	SimpleObjectIterator();
	virtual ~SimpleObjectIterator();
	virtual int first();
	virtual int next();
	void insert(int a, float b);
 void sort(IterOrderType);
	void rva0054B414();

private:
	_STL::deque<BfmeTrivialDequeElement8>::iterator m_cursor;
	_STL::deque<BfmeTrivialDequeElement8> m_deque;
};

SimpleObjectIterator::SimpleObjectIterator() {}

// Native 54B81A..54B850: the deque cleanup at +14 and the base-vtable
// restoration independently establish the two destructor stages. The named
// insert, constructor call sites and the three-slot vtable establish this
// class; Zero Hour's ObjectIter.h supplies the empty-base destructor lead.
SimpleObjectIterator::~SimpleObjectIterator() {}

void SimpleObjectIterator::insert(int a, float b)
{
	BfmeE8 tmp;
	tmp.a = a;
	tmp.b = b;
	// Preserve the existing provider's typed ABI view over the proven 8-byte
	// deque storage. The original record type remains unrecovered.
	reinterpret_cast<_STL::deque<BfmeE8> &>(m_deque).push_back(tmp);
}
