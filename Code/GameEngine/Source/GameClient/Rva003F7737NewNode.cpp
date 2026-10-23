// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva003F7737@Rva003F7737@@QAEPAXPBX@Z @0x003F7737 37B
// Hashtable new-node for 16-byte node (4 next + 12 BfmeStringRecord004071F7).
// Same shape as sibling 0x0022356C in Rva00223547NewNode.cpp: allocate 0x10
// via 0x000307F0, zero next, placement-copy the 12-byte record via the typed helper
// 0x003F7674 (twin of rowed _Construct for BfmeStringRecord004071F7 via rowed
// copy 0x004071F7), return node. Evidence: caller at 0x003F78EF sets ecx plus
// one record arg and links the returned node into the bucket; landing this
// unblocks 0x003F78A9. The callee uses its unique typed owner.
// Record layout (AsciiString text + 2 words)
// from Code/GameEngine/Source/Common/StringRecordCopyBFME2.cpp.
#define _STLP_NO_EXCEPTIONS 1
#include <memory>

struct Rva003F7737Val
{
	char m_body[12];
};

struct BfmeStringRecord004071F7;
void Rva003F7674Construct(BfmeStringRecord004071F7 *, const BfmeStringRecord004071F7 &);

struct Rva003F7737Node
{
	void *_M_next;
	Rva003F7737Val _M_val;
};

class Rva003F7737
{
public:
	void *rva003F7737(const void *obj);
};

void *Rva003F7737::rva003F7737(const void *obj)
{
	Rva003F7737Node *n = (Rva003F7737Node *)_STL::allocator<char>().allocate(16, 0);
	n->_M_next = 0;
	Rva003F7674Construct((BfmeStringRecord004071F7 *)&n->_M_val,
        *(const BfmeStringRecord004071F7 *)obj);
	return n;
}
