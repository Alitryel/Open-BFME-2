// cl: /O1 /EHsc /MD /D_CRTIMP=
// STLport 4.5.3 tree destructor. Semantic donor: _tree.h at BFME1
// 071013b3c6f1228dfda315732197bed0fd191209. Target 0x00221E02..0x00221E39
// calls this specialization's verified clear at 0x00221CAE, then free30830.
// The matching insertion/copy/erase chain in stlport_rb_tree_hint_00221e3a.cpp
// establishes AsciiString keys and opaque reference-counted pointer values.
// Application type remains unknown. This TU exposes only destruction's layout;
// the header base and throwing C++ allocator declaration preserve the EH store.

class AsciiString;
struct TreeHintRef00221D6B;

namespace _STL {
void __cdecl free(void *block);
template<class T> class allocator {};
template<class First, class Second> struct pair;
template<class Pair> struct _Select1st;
template<class T> struct less {};
template<class Value> struct _Rb_tree_node;

// ?_Rb_tree_base::~_Rb_tree_base present-unmatched
template<class Value, class Alloc> struct _Rb_tree_base {
    _Rb_tree_node<Value> *header;
    inline ~_Rb_tree_base() {
        if (header != 0)
            free(header);
    }
};

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
class _Rb_tree : public _Rb_tree_base<Value, Alloc> {
public:
    ~_Rb_tree();
    void clear();
private:
    unsigned int nodeCount;
    Compare keyCompare;
};

typedef pair<const AsciiString, TreeHintRef00221D6B> HintValue;
typedef _Rb_tree<AsciiString, HintValue, _Select1st<HintValue>,
    less<AsciiString>, allocator<HintValue> > HintTree;

template<class Key, class Value, class KeyOfValue, class Compare, class Alloc>
_Rb_tree<Key, Value, KeyOfValue, Compare, Alloc>::~_Rb_tree() {
    clear();
}
}

template _STL::_Rb_tree<AsciiString, _STL::HintValue, _STL::_Select1st<_STL::HintValue>,
    _STL::less<AsciiString>, _STL::allocator<_STL::HintValue> >::~_Rb_tree();

// Native221FF5 tail JMP221E02: unchanged ECX and no stack arguments.
// Existing tree type is reused; original wrapper identity is unknown.
struct Rva00221FF5TreeCleanupForward { void cleanup(); };
void Rva00221FF5TreeCleanupForward::cleanup() {
    reinterpret_cast<_STL::HintTree *>(this)->~_Rb_tree();
}
