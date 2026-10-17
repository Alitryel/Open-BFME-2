// ?Rva00434548Fallback@@YAIII@Z
// partial score=0.36 date=2026-10-17
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

// Callees referenced by the retail body.
int Rva00434091Get(void);
int Rva00225A93Get(int, int, int, int, int);
short rva00523630(short, short);
unsigned int rva_00434548_call1(int, unsigned int);
unsigned int rva_00434548_call2(int, int);

// Node layout: 0x18 is the tree-link field cleared by the retail body.
struct FallbackNode00434548 {
    unsigned char m_pad[0x18];
    unsigned int m_link;
};

// Missing: ?Rva00434548Fallback@@YAIII@Z is unsigned int __cdecl (unsigned int, unsigned int); TU declared 3 params (YAIIII@Z).
unsigned int Rva00434548Fallback(unsigned int a, unsigned int b)
{
    if (0) throw 1;
    volatile unsigned int pad0 = 0xCFCECDCC;
    volatile unsigned int pad1 = 0x00834555;
    volatile unsigned int pad2 = 1;
    volatile unsigned int pad3 = 0;
    volatile unsigned int pad4 = 0xCFCECDCC;
    volatile unsigned int pad5 = 0;
    volatile int key = Rva00434091Get();
    volatile unsigned int v8 = (unsigned int)rva_00434548_call1(key, a);
    volatile unsigned int v14 = (unsigned int)rva_00434548_call1(key, b);
    struct { unsigned char v; unsigned char pad[3]; } flag;
    flag.v = 0;
    *(volatile unsigned char*)&flag.v;
    short s = rva00523630((short)v8, (short)v14);
    int v10 = s;
    v10 = Rva00225A93Get(3, 0xe, v8, v14, v10);
    *(volatile int*)&v10;
    if ((1 ? (v8 == 1) : (v8 == 1))) {
        ((FallbackNode00434548 *)key)->m_link = 0;
    }
    int vB = (int)(short)b;
    int vCopy = (int)v8;
    unsigned int vc = (unsigned int)(vCopy == 1 ? rva_00434548_call2(key, v10) : rva_00434548_call2(key, vB));
    return (1 ? vc : vc);
}
