// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Native 4ABCFE clears an owning tree and frees its header. The registry
// cleanup 4ABE53 passes its +4 member here; its key-list method is 4ABDDC.
// Header0 and count4 come from clear4ABC5C. The remaining word is opaque.
// Original key/value types and class names are not established. The existing
// library spelling below binds only that already owned clear implementation.
#include <map>

typedef _STL::pair<const int, void *> Rva004ABCFEClearValue;
typedef _STL::_Rb_tree<int, Rva004ABCFEClearValue,
    _STL::_Select1st<Rva004ABCFEClearValue>, _STL::less<int>,
    _STL::allocator<Rva004ABCFEClearValue> > Rva004ABCFEClearView;

// Use the kept provider; do not emit a private clear/erase COMDAT family.
namespace _STL {
template <> void Rva004ABCFEClearView::clear();
}

struct Rva004ABCFEHeader
{
    void *m_header;
    ~Rva004ABCFEHeader()
    {
        if (m_header)
            free(m_header);
    }
};

struct Rva004ABCFETree : public Rva004ABCFEHeader
{
    unsigned m_node_count;
    unsigned char m_opaque08[4];
    ~Rva004ABCFETree();
};

Rva004ABCFETree::~Rva004ABCFETree()
{
    ((Rva004ABCFEClearView *)this)->clear();
}
