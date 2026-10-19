// ?Rva004346FBFallback@@YAHHH@Z
// partial score=0.24 date=2026-10-17
// cl: /Od /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ??1?$pair@$$CBVAsciiString@@UTreeHintOpaque0043671B@@@_STL@@QAE@XZ @0x00434513 53B: pair<const AsciiString, TreeHintOpaque0043671B> dtor destroys mapped 0x00229840 at +4 then narrow StringBase<D> releaseBuffer 0x00036410 at +0; layout from pair copy 0x00435DAA and mapped copy 0x0022D106; unwind caller 0x00787FB8 and tree insert context prove pair identity.
// The node allocates 0xE08 bytes and constructs its 0xDF8-byte value at node+16; same flags as stlport_rb_tree_hint_00436e3b.cpp.
#include <map>
#include "ascii_string.h"
#include "unicode_string.h"

struct BfmeSubobject0022CE19 {
    virtual ~BfmeSubobject0022CE19();
    unsigned char m_opaque[0xDE4];
    BfmeSubobject0022CE19(const BfmeSubobject0022CE19 &);
};
struct TreeHintOpaque0043671B {
    UnicodeString m_text;
    BfmeSubobject0022CE19 m_subobject;
    unsigned int m_wordDEC, m_wordDF0;
    TreeHintOpaque0043671B();
    TreeHintOpaque0043671B(const TreeHintOpaque0043671B &);
    ~TreeHintOpaque0043671B();
};
inline bool operator<(const AsciiString &, const AsciiString &);
typedef _STL::pair<const AsciiString, TreeHintOpaque0043671B> TreeHintPair0043671B;
template void _STL::_Destroy<TreeHintPair0043671B>(TreeHintPair0043671B *);
template TreeHintPair0043671B::pair(const AsciiString &, const TreeHintOpaque0043671B &);

// Callees referenced by the retail body (ledger rows).
int Rva00434091Get();
unsigned int __stdcall Rva00434097Add(unsigned int, unsigned int);
int Rva00225A93Get(int, int, int, int, int);
int BfmeLookup003EFEB2(int, int);
int BfmeLookup00226156(int, int);

// Retail is a SecuROM-marked /Od body: the marker blocks (push eax / mov eax,imm x5 / pop eax)
// and the constant-false (xor eax,eax / je) branches have no effect. The zeroed byte at
// [ebp-0x15] only travels in ECX to the __stdcall adder, which ignores it.
int Rva004346FBFallback(int a, int b)
{
    int ctx = Rva00434091Get();
    int first = BfmeLookup003EFEB2(ctx, a);
    int second = BfmeLookup003EFEB2(ctx, b);
    int sum = (short)Rva00434097Add((unsigned int)first, (unsigned int)second);
    int result = Rva00225A93Get(3, 2, first, second, sum);
    return BfmeLookup00226156(ctx, result);
}
