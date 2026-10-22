// STLport 4.5.3 deque<Rva00056DEBElement> destructor, retail 0x000579DE (87B).
// The element destructor declaration arms the rowed _Destroy range helper
// 0x56DEB; the _Deque_base destructor declaration without an exception
// specification gives the or [ebp-4],-1 trylevel reset retail shows before the
// base-destructor call. The base body itself is emitted by the ICF alias row
// at 0x54FAAC from StlportDequeBaseSweepRva00056DEB.cpp.
// stlport
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
#include <deque>
// Suppress this TU's non-retail copy of ??$__destroy_aux@U?$_Deque_iterator@URva00056DEBElement@@U?$_Nonconst_traits@URva00056DEBE:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva00056DEBElement;
namespace _STL { template <> void __destroy_aux<_Deque_iterator<Rva00056DEBElement,_Nonconst_traits<Rva00056DEBElement> > >(_Deque_iterator<Rva00056DEBElement,_Nonconst_traits<Rva00056DEBElement> >,_Deque_iterator<Rva00056DEBElement,_Nonconst_traits<Rva00056DEBElement> >,__false_type const &); }

struct Rva00056DEBElement { char bytes[1]; ~Rva00056DEBElement(); bool operator<(const Rva00056DEBElement&)const; bool operator==(const Rva00056DEBElement&)const; };

namespace _STL { template<> _Deque_base<Rva00056DEBElement, allocator<Rva00056DEBElement> >::~_Deque_base(); }

template _STL::deque<Rva00056DEBElement>::~deque();
