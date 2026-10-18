// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport 4.5.3 vector copy constructor, moved without reconstruction from
// stlport_uninitialized_copy.cpp. The complete 93-byte body and handler are
// byte-verified; this legacy element spelling and its pinned copy callee
// still need reconciliation, so keep its conflicting helper emissions out
// of the independently verified uninitialized-copy worker family.
#include <memory>
#include <vector>
#include "ascii_string.h"

struct TreeKey00242F5E
{
public:
	TreeKey00242F5E();
	TreeKey00242F5E(const TreeKey00242F5E &other);
	char m_body[8];
};
namespace _STL {
template<> void _Construct<TreeKey00242F5E, TreeKey00242F5E>(TreeKey00242F5E *, const TreeKey00242F5E &);
}
template _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> >::vector(const _STL::vector<TreeKey00242F5E, _STL::allocator<TreeKey00242F5E> > &);
