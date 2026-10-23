// cl: /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// ?rva004638C5@Rva004638C5@@QAEPAURva004638C5Node@@ABUTreeKey00242F5E@@@Z 0x004638C5 34B
// TreeKey tree create_node as a thiscall member with unused receiver (both
// 0x463F73 call sites set ecx): alloc 0x18 via rowed byte allocator 0x307F0
// then the typed placement-copy owner 0x4634DC at +0x10; returns node.
// Original application type remains unknown. Same shape as member 0x4634BA (34B).
struct TreeKey00242F5E
{
	char _d[8];
};

struct Rva004638C5Node
{
	char _head[0x10];
	char _val[8];
};

namespace _STL
{
template <class _Tp>
class allocator;
template <>
class allocator<char>
{
public:
	static char *allocate(unsigned int n, const void *hint);
};
}

void Rva004634DCConstruct(TreeKey00242F5E *, const TreeKey00242F5E &);

class Rva004638C5
{
public:
	struct Rva004638C5Node *rva004638C5(const struct TreeKey00242F5E &x);
};

struct Rva004638C5Node *Rva004638C5::rva004638C5(const struct TreeKey00242F5E &x)
{
	char *mem = _STL::allocator<char>::allocate(0x18, 0);
	Rva004634DCConstruct((TreeKey00242F5E *)(mem + 0x10), x);
	return (struct Rva004638C5Node *)mem;
}
