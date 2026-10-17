// ?Rva00434621Fallback@@YAHHH@Z
// partial score=0.316 date=2026-10-17
// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
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

// Callees referenced by the retail body (declared only).
int Rva00434091Get();
int Rva00434621Helper(int, int);
int Rva00225A93Get(int, int, int, int, int);
short Rva0056DD8DSecond(int, int, char *);
int Rva00226156Helper(int, int);

struct Rva00434621Node {
    unsigned char m_pad00[0x18];
    unsigned int m_word18;
};

int Rva00434621Fallback(int a, int b)
{
    int padA[8];
    volatile int c1 = (int)0xCFCECDCC;
    volatile int c2 = 0x83462E;
    volatile int c3 = 1;
    volatile int c4 = 0;
    volatile int c5 = (int)0xCFCECDCC;
    int got;
    {
        int t = Rva00434091Get();
        *(volatile int*)&got = t;
    }
    int r1 = Rva00434621Helper(got, a);
    int r2 = (a ? Rva00434621Helper(got, b) : Rva00434621Helper(got, b));
    char flag;
    short s = Rva0056DD8DSecond(r1, r2, &flag);
    int s32 = s;
    *(volatile int*)&s32 = s32;
    int v = Rva00225A93Get(3, 1, *(volatile int*)&r1, *(volatile int*)&r2, *(volatile int*)&s32);
    int result;
    if (*(volatile int*)&v == 0 && *(volatile int*)&r1 == 1) {
        ((Rva00434621Node *)got)->m_word18 = 0;
    }
    if (1) {
        s32 = (short)b;
    }
    if (0) {
        result = r1;
    } else {
        result = Rva00226156Helper(got, s32);
    }
    return result;
}
