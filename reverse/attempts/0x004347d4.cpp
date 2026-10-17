// ?Rva004347D4Fallback@@YAHHH@Z
// partial score=0.276 date=2026-10-17
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

int Rva00434091Get(void);

struct Rva004340A4 {
    int m_ctx;
    short operator()(int, int) const;
};

int Rva00225A93Get(int, int, int, int, int);
int Rva00226156Get(void *, int);

int Rva004347D4Fallback(int a, int b) {
    struct { unsigned char pad[12]; int v; } pv;
    *(volatile int *)&pv.v = 0;
    char pad2[4];
    *(volatile char *)&pad2[0] = 0;
    int v = pv.v;
    int r1 = Rva00434091Get();
    *(volatile int *)&r1 = r1;
    int r2 = Rva00226156Get((void *)r1, a);
    *(volatile int *)&r2 = r2;
    int r3 = Rva00226156Get((void *)r1, b);
    *(volatile int *)&r3 = r3;

    Rva004340A4 h;
    int r4 = h((1 ? r2 : r2), (1 ? r3 : r3));
    int r5 = Rva00225A93Get(3, 0xd, r2, r3, r4);
    char local;
    *(volatile char *)&local = 0;
    if (r2 == 1) {
        *(volatile int *)((char *)r1 + 0x18) = 0;
    }
    if (r5 != 0) {
        v = r2;
    } else {
        v = Rva00226156Get((void *)r1, b);
    }
    return v;
}
