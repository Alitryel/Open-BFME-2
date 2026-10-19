// ??0CastleBehaviorModuleData@@QAE@XZ
// partial score=0.9744245524296675 date=2026-10-19
// cl: /O1 /arch:SSE /G7 /GX /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
#if 0
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

#endif
// Native factory 0x0024AA99 is registered as CastleBehavior and calls this body.
// The inherited bank above is inactive evidence; its name, types and operations are superseded.
// Two ESP-witness/ECX instruction pairs still differ; vtable and helper bindings need admission.
#include <vector>
#include <map>
#include "ascii_string.h"

class Rva002618A2
{
public:
    Rva002618A2 *rva002618FA(int, int, int, int, int, int);
protected:
    unsigned m_words[7];
};
class Rva00045411BitSet : public Rva002618A2
{
public:
    Rva00045411BitSet(int, int);
    Rva00045411BitSet(const Rva00045411BitSet &);
    __declspec(dllimport) __forceinline Rva00045411BitSet(int a, int b, int c, int d, int e, int f)
    { rva002618FA(a, b, c, d, e, f); }
};
class BfmeFixedStorage0004543D : public Rva00045411BitSet
{
public:
    BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
    __declspec(dllimport) __forceinline BfmeFixedStorage0004543D(int a, int b) : Rva00045411BitSet(a,b) {}
};
extern const BfmeFixedStorage0004543D g_defaultStorage009FEFA4;
class Rva003623E5Member
{
public:
    Rva003623E5Member();
    ~Rva003623E5Member();
    void rva00362192(Rva00045411BitSet, BfmeFixedStorage0004543D);
    void initFromStorages(BfmeFixedStorage0004543D, BfmeFixedStorage0004543D);
private:
    int m_handle;
};
struct RvaPair0039973B { AsciiString m_key; int m_value; ~RvaPair0039973B(); };
struct Rva00395D77 { unsigned char m_bytes[12]; ~Rva00395D77(); };
namespace _STL { template <> inline void vector<RvaPair0039973B>::clear() { erase(this->_M_start, this->_M_finish); } template <> inline void vector<Rva00395D77>::clear() { erase(this->_M_start, this->_M_finish); } }
struct BfmeStringRecord004071F7 { AsciiString m_templateName; unsigned m_count1, m_count2; };
class Rva00397C94 { public: void rva00398257(); };
#include "Common/Snapshot.h"
extern const void *const BfmeCastleBehaviorModuleDataVtable[];
class __declspec(novtable) Rva0039A027Base : public Snapshot
{
public:
    __forceinline Rva0039A027Base() : m_f08(0.0f), m_n0c(0)
    { *(const void *const **)this = BfmeCastleBehaviorModuleDataVtable; }
    virtual ~Rva0039A027Base() {}
private:
    unsigned m_unknown04;
    float m_f08;
    unsigned m_n0c;
};
class __declspec(novtable) CastleBehaviorModuleData : public Rva0039A027Base
{
public:
    CastleBehaviorModuleData();
    virtual ~CastleBehaviorModuleData();
private:
    AsciiString m_str10, m_str14;
    float m_f18, m_f1c, m_f20, m_f24, m_f28, m_f2c;
    Rva003623E5Member m_filter30, m_filter34;
    int m_n38;
    bool m_b3c, m_b3d, m_b3e;
    int m_n40, m_n44, m_n48, m_n4c;
    _STL::vector<RvaPair0039973B> m_vec50;
    _STL::vector<Rva00395D77> m_vec5c;
    _STL::map<int, BfmeStringRecord004071F7> m_map68;
    bool m_b74, m_b75;
};
CastleBehaviorModuleData::CastleBehaviorModuleData()
{
    ((Rva00397C94 *)&m_map68)->rva00398257();
    ((StringBase<char> *)&m_str10)->set("");
    m_vec50.clear();
    m_vec5c.clear();
    ((StringBase<char> *)&m_str14)->set("");
    m_f18 = 1.0f;
    m_f1c = 2.0f;
    m_f20 = 2.0f;
    m_f24 = 5.0f;
    m_f28 = 100.0f;
    m_f2c = 0.0f;
    m_b74 = false;
    m_filter30.rva00362192(Rva00045411BitSet(0,7,0x3c,0x68,0x99,0x73), BfmeFixedStorage0004543D(0,0x88));
    m_filter34.initFromStorages(g_defaultStorage009FEFA4, g_defaultStorage009FEFA4);
    m_n38 = 0x12;
    m_n48 = 0;
    m_n44 = 0;
    m_n40 = 0xa;
    m_b3c = false;
    m_b3d = false;
    m_n4c = -1;
    m_b3e = false;
    m_b75 = true;
}

typedef char Rva0039A027BaseSize[(sizeof(Rva0039A027Base) == 0x10) ? 1 : -1];
typedef char Rva0039A027StringSize[(sizeof(AsciiString) == 4) ? 1 : -1];
typedef char Rva0039A027FilterSize[(sizeof(Rva003623E5Member) == 4) ? 1 : -1];
typedef char Rva0039A027MaskSize[(sizeof(Rva00045411BitSet) == 28 && sizeof(BfmeFixedStorage0004543D) == 28) ? 1 : -1];
typedef char Rva0039A027PairSize[(sizeof(RvaPair0039973B) == 8) ? 1 : -1];
typedef char Rva0039A027RecordSize[(sizeof(BfmeStringRecord004071F7) == 12) ? 1 : -1];
typedef char Rva0039A027VectorSize[(sizeof(_STL::vector<RvaPair0039973B>) == 12 && sizeof(_STL::vector<Rva00395D77>) == 12) ? 1 : -1];
typedef char Rva0039A027MapSize[(sizeof(_STL::map<int, BfmeStringRecord004071F7>) == 12) ? 1 : -1];
typedef char Rva0039A027DataSize[(sizeof(CastleBehaviorModuleData) == 0x78) ? 1 : -1];
