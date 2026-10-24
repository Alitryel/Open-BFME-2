// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// list pop_front @0x00416939, 22B; masked twin of BfmePod12 pop_front @0x004907AA.
#include <list>
struct BfmeStringRecord00415F34 { unsigned char m_data[24]; };
namespace _STL {
template <> list<BfmeStringRecord00415F34>::iterator
list<BfmeStringRecord00415F34>::erase(iterator);
}
template void _STL::list<BfmeStringRecord00415F34>::pop_front();
