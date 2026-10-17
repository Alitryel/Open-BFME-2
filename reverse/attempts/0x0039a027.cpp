// ??0BaikonurLaunchPowerModuleData@@QAE@XZ
// partial score=0.387 date=2026-10-17
// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector<T>::_M_insert_overflow (the push_back growth path) for
// the element types of StlportVectorPushBackFamily.cpp, whose retail push_back
// rows already name these bodies through pins.  Same recipe as
// StlportVectorGrowthFootprints.cpp: each element is reduced to its footprint
// (the stride its push_back adds) with an out-of-line copy ctor and dtor, and
// _Construct is declared as an explicit specialization so the copies call the
// element's matched _Construct row.  /G7 gives retail's imul scaling;
// _STLP_NO_EXCEPTIONS drops the EH frame retail does not have.
//
// Each body is the sole retail caller-side match for its push_back's
// _M_insert_overflow REL32 and is byte-identical with relocations masked.
// _M_clear and helper bodies reached only from one of these growth paths are
// landed from this unit as well; helpers folded across several vectors are
// pinned, not rowed.

#define _STLP_NO_EXCEPTIONS 1

namespace _STL {

class allocator_base {};

}

// ---- types touched by BaikonurLaunchPowerModuleData::BaikonurLaunchPowerModuleData

class AsciiString;

// Fixed-capacity storage blob passed by value.
struct BfmeFixedStorage0004543D
{
    unsigned char data[0x1c];
    BfmeFixedStorage0004543D();
    BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &r);
};

// Bit set passed by value into Rva003623E5Member::rva00362192.
struct Rva00045411BitSet
{
    unsigned char data[0x1c];
    Rva00045411BitSet(int a, int b);
};

class Rva00045411BitSetInner;

// Small member object at +0x30 / +0x34 of the module data.
class Rva003623E5Member
{
public:
    Rva003623E5Member();
    void rva00362192(Rva00045411BitSet bits, BfmeFixedStorage0004543D s0,
                     BfmeFixedStorage0004543D s1);
    void initFromStorages(BfmeFixedStorage0004543D s0,
                          BfmeFixedStorage0004543D s1);
    void initFromStorages();
    int m_pad;
};

class Rva00397C94
{
public:
    void rva00398257();
};

class Rva00399800;
class Rva0039597C;

// std::map<int, std::vector<BfmePod128> > at +0x68 -- default ctor only.
class BfmePod128Map
{
public:
    BfmePod128Map();
};

// StringBase<char> at +0x10 / +0x14 -- only set() is reached.
class StringBaseChar
{
public:
    void set(const char *s);
};

template <class T> class BfmeVectorBase;

struct FXBoneInfo;
struct BfmeE12;

class BfmeVec12
{
public:
    BfmeVec12();
    ~BfmeVec12();
    int m_a;
    int m_b;
    int m_c;
};

class BfmePod128MapImpl
{
public:
    BfmePod128MapImpl();
    ~BfmePod128MapImpl();
    int m_a;
    int m_b;
    int m_c;
};

class BaikonurLaunchPowerModuleData
{
public:
    BaikonurLaunchPowerModuleData();
    virtual ~BaikonurLaunchPowerModuleData();

private:
    int m_vtable;                           // +0x00
    char m_pad4[4];                         // +0x04 .. +0x07
    float m_f8;                             // +0x08
    int   m_c;                              // +0x0c
    StringBaseChar m_name;                  // +0x10
    StringBaseChar m_name2;                 // +0x14
    float m_f18;                            // +0x18
    float m_f1c;                            // +0x1c
    float m_f20;                            // +0x20
    float m_f24;                            // +0x24
    float m_f28;                            // +0x28
    float m_f2c;                            // +0x2c
    Rva003623E5Member m_obj30;              // +0x30
    Rva003623E5Member m_obj34;              // +0x34
    int   m_n38;                            // +0x38
    char  m_b3c;                            // +0x3c
    char  m_b3d;                            // +0x3d
    char  m_b3e;                            // +0x3e
    char  m_pad3f[1];                       // +0x3f
    int   m_n40;                            // +0x40
    unsigned char m_pad44[4];               // +0x44 .. +0x47
    int   m_n48;                            // +0x48
    unsigned int m_n4c;                     // +0x4c
    BfmeVec12 m_vec50;                      // +0x50
    BfmeVec12 m_vec5c;                      // +0x5c
    BfmePod128MapImpl m_map68;              // +0x68 std::map
    unsigned char m_b74;                    // +0x74
    unsigned char m_b75;                    // +0x75
};

BaikonurLaunchPowerModuleData::BaikonurLaunchPowerModuleData()
{
    m_f8 = 0.0f;
    m_c = 0;
    m_vtable = 0;
    if (0) throw 1;
    *(volatile int*)&m_name = 0;
    *(volatile int*)&m_name2 = 0;
    m_map68.BfmePod128MapImpl::BfmePod128MapImpl();
    m_obj30.Rva003623E5Member::Rva003623E5Member();
    m_obj34.Rva003623E5Member::Rva003623E5Member();
    {
        unsigned char tmp = 0;
        *(volatile int*)&m_vec50.m_a = 0;
        m_vec50.BfmeVec12::BfmeVec12();
        *(volatile int*)&m_vec5c.m_a = 0;
        m_vec5c.BfmeVec12::BfmeVec12();
        *(volatile unsigned char*)&tmp;
    }
    m_name.set((1 ? "BaikonurLaunchPower" : "BaikonurLaunchPower"));
    m_name2.set((1 ? "BaikonurLaunchPower" : "BaikonurLaunchPower"));
    m_f18 = 1.0f;
    m_f1c = 2.0f;
    m_f20 = 2.0f;
    m_f24 = 5.0f;
    m_f28 = 100.0f;
    m_f2c = 0.0f;
    {
        BfmeFixedStorage0004543D s0;
        BfmeFixedStorage0004543D s1;
        m_obj30.initFromStorages(s0, s1);
        m_obj34.initFromStorages(s0, s1);
    }
    m_n38 = 0x12;
    m_n40 = 0xa;
    m_b74 = 0;
    m_b75 = 1;
}
