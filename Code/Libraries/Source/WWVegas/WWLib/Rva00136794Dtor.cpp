// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /arch:SSE
// stlport
// ??1Rva00136794@@UAE@XZ @0x00136AA5 185B
// Dtor for Rva00136794 (vtable 0x007D2970; layout from the rowed ctor TU
// Rva00136794Ctor.cpp): refcounted m_54 release plus erase of three
// vector<AsciiString> members in user code, then implicit teardown in reverse
// (rowed vector dtor 0x0002CC70 x3, inlined StringBase dtor -> rowed
// releaseBuffer 0x00036410 x2), then base GenBase009EB7D0 dtor inlined to the
// rowed bfmeResetUB 0x0061ED80 with this (retail state -1 trailing this-call,
// base at +0 with no rowed dtor so inline). Evidence: vtable store, ref-dec
// plus indirect vf0 matching rowed rva00135E6D 0x00135E6D, rowed erase
// 0x0002CCFC, caller 0x00136F3F deleting dtor.
class AsciiString;

namespace _STL {
template <typename T>
class allocator
{
};
template <typename T, typename A>
class vector
{
public:
    typedef AsciiString *iterator;
    iterator begin() { return m_start; }
    iterator end() { return m_finish; }
    iterator erase(iterator first, iterator last);
    ~vector();
private:
    iterator m_start;
    iterator m_finish;
    iterator m_endOfStorage;
};
}

class BfmeThingUB
{
public:
    void bfmeResetUB();
};

class __declspec(novtable) GenBase009EB7D0
{
public:
    __declspec(noinline) GenBase009EB7D0();
    virtual ~GenBase009EB7D0() { ((BfmeThingUB *)this)->bfmeResetUB(); }
    virtual void handle();
private:
    unsigned int m_flags;
    unsigned int m_zero08;
    unsigned int m_zero0c;
    unsigned int m_zero10;
};

template <typename T>
class StringBase
{
public:
    ~StringBase() { releaseBuffer(); }
private:
    StringBase(const T *str);
    friend class Rva00136794;
    void releaseBuffer();
    struct Header
    {
        int ref_count;
        unsigned short length;
        unsigned short capacity;
        T data[1];
    };
    Header *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


class Rva0013101E
{
public:
    Rva0013101E &rva0013101E(Rva0013101E const *src) throw();
    unsigned m_a : 3;
    unsigned m_b : 27;
    unsigned m_c : 1;
    unsigned m_keep : 1;
    unsigned m_d1;
    unsigned m_d2;
    unsigned m_d3;
};

struct RefM54 {
    virtual void vf0();
    int m_ref;
};

class Rva00136794 : public GenBase009EB7D0
{
public:
    Rva00136794(const char *s1, const char *s2, float f, const Rva0013101E *r, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v1, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v2, const _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v3);
    virtual ~Rva00136794();
private:
    StringBase<char> m_s1;
    StringBase<char> m_s2;
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > m_v1;
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > m_v2;
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > m_v3;
    float m_f40;
    Rva0013101E m_r44;
    struct RefM54 *m_54;
};

inline Rva00136794::~Rva00136794()
{
    RefM54 *p = m_54;
    if (p) {
        if (--p->m_ref == 0)
            p->vf0();
        m_54 = 0;
    }
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v1 = m_v1;
    v1.erase(v1.begin(), v1.end());
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v2 = m_v2;
    v2.erase(v2.begin(), v2.end());
    _STL::vector<AsciiString, _STL::allocator<AsciiString> > &v3 = m_v3;
    v3.erase(v3.begin(), v3.end());
}
#pragma inline_depth(0)
// ?bfmeEmitRva00136794Dtor@@YAXPAVRva00136794@@@Z present-unmatched
void bfmeEmitRva00136794Dtor(Rva00136794 *p)
{
    p->Rva00136794::~Rva00136794();
}
#pragma inline_depth()
