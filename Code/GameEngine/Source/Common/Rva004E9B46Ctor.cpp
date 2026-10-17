// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva004E9B46@@QAE@H@Z @0x004E9B46 42B ctor base Rva00506B1B + int at +8 + vector<BfmeE16> at +0xc vtable 0x00862874 callees 0x00506B1B 0x00211E58 caller 0x004EC488
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
class Rva00506B1B
{
public:
    Rva00506B1B();
    virtual void v0();
    virtual void v1();
    bool m_04;
};
class Rva004E9B46 : public Rva00506B1B
{
public:
    int m_08;
    _STL::vector<BfmeE16, _STL::allocator<BfmeE16> > m_vec;
    Rva004E9B46(int x);
};

Rva004E9B46::Rva004E9B46(int x) : m_08(x)
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?v0@Rva00506B1B@@UAEXXZ=??_GRva004E9B46@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?v1@Rva00506B1B@@UAEXXZ=?update@AIWallBuilder@@QAEXXZ")
