// cl: /O1 /G7 /MD /EHsc /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native1F206E..1F20D6 is the complete104-byte Object-pointer vector copy.
// WB B095A0 corroborates allocator/count construction and reference-tag copying.
// Target creator1F1634 returns the 12-byte storage; consumer1F2F0E indexes
// four-byte entries and calls Object::findModule on them. This supports Object*
// independently of the STLport4.5.3 algorithm used as the source guide.
// Use the stock reference-tag algobase for this measured caller; bfmealloc's
// by-value tag applies to other units. The typed helper is separately rowed.
// Native state0 cleanup76B19E calls the existing vector-base destructor pin
// at1F1609. Main bytes, EH data and the cleanup's REL32 are verified separately.
// The allocator and storage constructors stay out of line: visible helper
// definitions change EH liveness and no longer reproduce this body.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include <vector>
class Object;
namespace _STL {
template<> Object** __copy_aux<Object**,Object**>(Object**,Object**,Object**,const __true_type&);
template<> _Vector_base<Object*,allocator<Object*> >::~_Vector_base();
template<> _Vector_base<Object*,allocator<Object*> >::_Vector_base(unsigned int,const allocator<Object*>&);
template<> allocator<Object*> vector<Object*>::get_allocator() const;
}
namespace _STL {
template<> vector<Object*>::vector(const vector<Object*>&r)
 : _Vector_base<Object*,allocator<Object*> >(r.size(),r.get_allocator()) {
 _M_finish=__copy_aux(r._M_start,r._M_finish,_M_start,__true_type());
}
}
template _STL::vector<Object*>::vector(const _STL::vector<Object*>&);
