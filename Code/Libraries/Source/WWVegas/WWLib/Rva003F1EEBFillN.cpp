// cl: /DNDEBUG /MD
// ??$uninitialized_fill_n@PAV?$vector@IV?$allocator@I@_STL@@@_STL@@IV12@@_STL@@YAPAV?$vector@IV?$allocator@I@_STL@@@0@PAV10@IABV10@@Z @0x003F1EEB 27B:
// _STL::uninitialized_fill_n for _STL::vector<unsigned int> (12-byte payload).
// Untagged dispatcher: forwards (first n value) to the rowed tagged worker at
// 0x003F1A8C (rowed as ?dup_003F1A8C@@YAXXZ) with a false_type tag temporary at
// ebp-1. Calls through the dup address per Rva003F1EA8UninitCopy precedent so
// the gate resolves. Caller 0x003F35E3.
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A = allocator<T> > class vector
{
public:
	void *_M_start;
	void *_M_finish;
	void *_M_end_of_storage;
};
struct __false_type {};
}
struct Rva003F1A8CElement;
namespace _STL
{
template <class ForwardIter, class Size, class T>
ForwardIter __uninitialized_fill_n(ForwardIter first, Size n, const T &x, const __false_type &);
}
typedef _STL::vector<unsigned int, _STL::allocator<unsigned int> > FillUIntVec;
namespace _STL
{
template <class ForwardIter, class Size, class T>
ForwardIter uninitialized_fill_n(ForwardIter first, Size n, const T &x)
{
	__false_type tag;
	return (ForwardIter)__uninitialized_fill_n((Rva003F1A8CElement *)first, n, (const Rva003F1A8CElement &)x, tag);
}
}
template FillUIntVec *_STL::uninitialized_fill_n(FillUIntVec *, unsigned int, const FillUIntVec &);
