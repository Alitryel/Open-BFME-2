// ?Rva004346FBFallback@@YAHHH@Z
// partial score=0.24 date=2026-10-17
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
int Rva00434091Get();
unsigned int Rva00434097Add(unsigned int, unsigned int, unsigned int);
int Rva00225A93Get(int, int, int, int, int);
int BfmeLookup00226156(int, int);

// Opaque node layout used by the retail body (only the touched member is modelled).
struct BfmeNode004346FB {
    unsigned char m_pad[0x18];
    unsigned int m_word18;
};

int Rva004346FBFallback(int a, int b)
{
    struct { int v; unsigned char pad[3]; } ctxS; struct { int v; unsigned char pad[3]; } firstS; struct { int v; unsigned char pad[3]; } secondS;
    struct { unsigned char v; unsigned char pad[3]; } flagS;
    volatile unsigned int dummyArr[4];
    dummyArr[0] = 0xCFCECDCC; dummyArr[1] = 0x00834708; dummyArr[2] = 1; dummyArr[3] = 0;
    *(volatile unsigned int*)&dummyArr[0] = 0xCFCECDCC;
    ctxS.v = 0;
    int ctxTmp = Rva00434091Get();
    ctxS.v = ctxTmp;
    int ctx = ctxS.v;

    int first = BfmeLookup00226156((1 ? ctx : ctx), a);
    int second = BfmeLookup00226156(ctx, b);

    {
        unsigned char flagTmp = 0;
        *(volatile unsigned char*)&flagS.v = flagTmp;
    }
    if (0) { AsciiString d; }
    unsigned char flag = *(volatile unsigned char*)&flagS.v;
    unsigned int sum = Rva00434097Add((unsigned int)second, (unsigned int)first, (1 ? (unsigned int)flag : (unsigned int)flag));
    int sumSigned = (int)(short)sum;

    int result = Rva00225A93Get(3, 2, first, second, sumSigned);

    if (result == 0) {
        if (first == 1) {
            ((BfmeNode004346FB *)ctx)->m_word18 = 0;
        }
        int out = (int)(short)b;
        if (result == 0) {
            out = first;
        } else {
            out = BfmeLookup00226156(ctx, out);
        }
        return out;
    }

    return BfmeLookup00226156(ctx, sumSigned);
}
