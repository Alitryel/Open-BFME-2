// cl: /DNDEBUG /MD
// Reference: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d,
// inputs/vendor/stlport/stl/_set.h, erase(const key_type&).
// Target 0x000A7E99..0x000A7E9E is the complete unadjusted tail call to
// the rowed tree erase at 0x000A7E31. The next instruction is the separately
// recovered 0x000A7E9E entry. Receiver and key ABI come from that callee;
// no direct callers or target evidence establish the enclosing container's
// original name. Keep its identity address-derived and reuse the callee's
// existing opaque key spelling. Only an offset-zero tree view is needed.

struct Rva000A7E31Key;
namespace _STL {
template<class T> struct _Identity;
template<class T> struct less;
template<class T> class allocator;
template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree {
public:
    unsigned int erase(const Key &key);
};
}

typedef _STL::_Rb_tree<Rva000A7E31Key, Rva000A7E31Key,
    _STL::_Identity<Rva000A7E31Key>, _STL::less<Rva000A7E31Key>,
    _STL::allocator<Rva000A7E31Key> > Rva000A7E99Tree;

class Rva000A7E99 {
public:
    unsigned int erase(const Rva000A7E31Key &key);
};

unsigned int Rva000A7E99::erase(const Rva000A7E31Key &key)
{
    return reinterpret_cast<Rva000A7E99Tree *>(this)->erase(key);
}
