// Native constructor at RVA 0x005F3750, 227 bytes.
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/GameClient/System/FXParticleSystem/T1Base005F3750Ctor.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: T1Base_005F3750::T1Base_005F3750 0x0055C903 (157B),
// AssetList::AssetList 0x0006D577 (20B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// The matched T1Derived_005E24B0 constructor forwards to this existing
// address-derived identity. It is not DefaultModule<6> (whose constructor
// is at 0x005E5840). The matched copy constructor at 0x005EB730 installs
// the same vtables: 0x01112E78 at +0, 0x01112E74 at +0x14,
// and 0x01112E60 at +0x18. The inlined info base installs 0x01110920.
// Native base and local AssetList lifetimes generate the retail unwind states.
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
// stlport

#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <set>

#include "ascii_string.h"
// Suppress this TU's non-retail copy of ??1?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *, allocator<Rva001408C0Target *> >::~_Rb_tree_base(); }
// Suppress this TU's non-retail copy of ??0?$_Rb_tree_base@PAURva001408C0Target@@V?$allocator@PAURva001408C0Target@@@_STL@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_base<Rva001408C0Target *, allocator<Rva001408C0Target *> >::_Rb_tree_base(const allocator<Rva001408C0Target *> &); }
// Suppress this TU's non-retail copy of ?_M_erase@?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> void _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::_M_erase(_Rb_tree_node<Rva001408C0Target *> *); }
// Suppress this TU's non-retail copy of ??1?$_Rb_tree@PAURva001408C0Target@@PAU1@U?$_Identity@PAURva001408C0Target@@@_STL@@U?$less:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree<Rva001408C0Target *, Rva001408C0Target *, _Identity<Rva001408C0Target *>, less<Rva001408C0Target *>, allocator<Rva001408C0Target *> >::~_Rb_tree(); }
// Suppress this TU's non-retail copy of ?deallocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEXPAU?$_Rb_:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> void allocator<_Rb_tree_node<Rva001408C0Target *> >::deallocate(_Rb_tree_node<Rva001408C0Target *> *, size_t) const; }
// Suppress this TU's non-retail copy of ?allocate@?$allocator@U?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@@_STL@@QBEPAU?$_Rb_tre:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *allocator<_Rb_tree_node<Rva001408C0Target *> >::allocate(size_t, const void *) const; }
// Suppress this TU's non-retail copy of ?allocate@?$_STLP_alloc_proxy@PAU?$_Rb_tree_node@PAURva001408C0Target@@@_STL@@U12@V?$alloc:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct Rva001408C0Target;
namespace _STL { template <> _Rb_tree_node<Rva001408C0Target *> *_STLP_alloc_proxy<_Rb_tree_node<Rva001408C0Target *> *, _Rb_tree_node<Rva001408C0Target *>, allocator<_Rb_tree_node<Rva001408C0Target *> > >::allocate(size_t); }

class Xfer;

namespace FXParticleSystem {
class DefaultDrawModuleInfo {
public:
    DefaultDrawModuleInfo() {}
    virtual ~DefaultDrawModuleInfo();
    virtual const char *GetSnapshotName();
    virtual void LoadPostProcess();
    virtual void DoXfer(Xfer &xfer);
};

}

class T1A1_005DD290 {
public:
    T1A1_005DD290(void *first, void *second);
    virtual void primarySlot();
    virtual ~T1A1_005DD290();

    unsigned int m_storage[4];
};

class ParticleModuleInterface005F2CA0 {
public:
    virtual void interfaceSlot();
};

class ParticleModule005F2CA0
    : public T1A1_005DD290,
      public ParticleModuleInterface005F2CA0 {
public:
    ParticleModule005F2CA0(void *first, void *second);
    virtual void moduleSlot();
};

struct Rva001408C0Target;
typedef Rva001408C0Target *Rva001408C0Key;
typedef _STL::set<
    Rva001408C0Key,
    _STL::less<Rva001408C0Key>,
    _STL::allocator<Rva001408C0Key> > Rva001408C0Set;

class AssetList {
public:
    AssetList()
        : m_treeLayoutPad(0),
          m_changed(true) {
    }

    AssetList &operator<<(const AsciiString &name);

private:
    Rva001408C0Set m_prototypes;
    unsigned int m_treeLayoutPad;
    bool m_changed;
};

class ParticleSystemZA;
extern ParticleSystemZA *bfmeNullSystemZA();
extern void bfmeMergeReceiverKeys(int value);
class Rva009EB960;
extern Rva009EB960 *Rva0134FAA0;
#define Rva0134FAA0 ((void *)::Rva0134FAA0)

class T1Base_005F3750
    : public ::ParticleModule005F2CA0,
      public FXParticleSystem::DefaultDrawModuleInfo {
public:
    T1Base_005F3750(void *first, void *second);
    virtual ~T1Base_005F3750();
};

T1Base_005F3750::T1Base_005F3750(
    void *first,
    void *second)
    : ::ParticleModule005F2CA0(first, second)
    , FXParticleSystem::DefaultDrawModuleInfo() {
    if (Rva0134FAA0 != 0) {
        AssetList assets;
        ParticleSystemZA *systemObject =
            *(ParticleSystemZA **)((unsigned char *)this + 4);
        if (systemObject == 0)
            systemObject = bfmeNullSystemZA();
        assets << *(const AsciiString *)((unsigned char *)systemObject + 0x10);
        bfmeMergeReceiverKeys((int)&assets);
    }
}
