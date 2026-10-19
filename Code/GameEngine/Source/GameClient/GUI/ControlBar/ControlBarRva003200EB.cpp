// cl: /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /Ireference/shims/ini_bfme2 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/open-bfme-1/Code/GameEngine/Source/Common/System /Ireference/open-bfme-1/Code/GameEngine/Include /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// stlport
// ??0ControlBarSchemeManager@@QAE@XZ @0x003200EB 81B.
// Ctor: current scheme@+0 zeroed, multiplier@+4/+8 default 1.0f via shared
// literal at 0x00BBB8D8, scheme list@+0xC default-constructed then cleared.
// Identity: retail's only caller is ControlBar::init (0x0031C87C), which
// stores the new object as its scheme manager (+0x44, the ZH
// m_controlBarSchemeManager); the layout is the canonical
// ControlBarSchemeManagerView.h one, whose dtor 0x003204D9 clears the same
// list. Donor: ZH ControlBarSchemeManager::ControlBarSchemeManager.
#include "ControlBarSchemeManagerView.h"

// The scheme list's base constructor is the ICF-folded pointer-list body at
// 0x004EC36C; this unit emits retail's copy of it (fold-proof pin).

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<ControlBarScheme *, allocator<ControlBarScheme *> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<ControlBarScheme *, allocator<ControlBarScheme *> >::~_List_base();
}

// list<ControlBarScheme *> destruction otherwise instantiates the allocator<_List_node<ControlBarScheme *>>
// deallocate COMDAT (one byte shape per TU flags); an explicit
// dllimport+forceinline specialization takes those calls inline so this
// TU emits no external copy. Body is verbatim primary (assert included).
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<ControlBarScheme *> >::deallocate(_List_node<ControlBarScheme *>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<ControlBarScheme *> *, _List_node<ControlBarScheme *>, allocator<_List_node<ControlBarScheme *> > >::deallocate(_List_node<ControlBarScheme *> *__p, size_t __n) {
  allocator<_List_node<ControlBarScheme *> >().deallocate(__p, __n);
}
}

ControlBarSchemeManager::ControlBarSchemeManager()
{
	m_currentScheme = 0;
	m_schemeList.clear();
	m_multiplyer.x = m_multiplyer.y = 1.0f;
}
