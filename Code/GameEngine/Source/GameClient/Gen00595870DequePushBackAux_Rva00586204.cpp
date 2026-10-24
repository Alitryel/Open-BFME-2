// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Native586204 is push_back45B, calling construction2CA82C and auxiliary585B1E.
// The auxiliary copies three scalar floats to a temporary, reserves one map
// slot, allocates120B and advances the end iterator. The payload's application
// identity is unknown. The BFME1 donor6d943426 supplied the STL operation lead;
// its owning-string payload guess is disproven by the native copy helpers.
#include <deque>
#include "../../../Libraries/Source/WWVegas/WWLib/Gen00595870Payload.h"

// Map reservation uses the existing verified deque storage view. Both
// containers have two16B iterators followed by the map pointer and size.
// Reservation does not read element data; no element identity is asserted.
struct BfmeE12 { float x,y,z; };
namespace _STL { template<> void deque<BfmeE12>::_M_reserve_map_at_back(size_type); }
class Rva00586204ReserveView : public _STL::deque<BfmeE12> {
public:
    __forceinline void reserveOne(unsigned count) { _M_reserve_map_at_back(count); }
};
namespace _STL {
template<> __forceinline void deque<Gen_t_00595870_p12cd>::_M_reserve_map_at_back(size_type count)
{
    ((Rva00586204ReserveView *)this)->reserveOne(count);
}
}
template void _STL::deque<Gen_t_00595870_p12cd>::push_back(const Gen_t_00595870_p12cd &);
template void _STL::deque<Gen_t_00595870_p12cd>::_M_push_back_aux_v(const Gen_t_00595870_p12cd &);
