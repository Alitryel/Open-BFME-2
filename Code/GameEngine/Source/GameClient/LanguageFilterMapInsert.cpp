// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
/*
** Copyright 2025 Electronic Arts Inc.
** SPDX-License-Identifier: GPL-3.0-or-later
*/
// Donor STLport insertion family for LanguageFilter's map at +0xC.
// Target nodes hold pair<const UnicodeString, bool> at +0x10 and occupy 24 bytes.
// init stores through operator[]; its hint passes through the vendor insert chain.
#define _BFME_RETAIL_TREE_INSERT_LAYOUT
#include <map>

#include "unicode_string.h"


struct UnicodeStringLessThan
{
    bool operator()(UnicodeString a, UnicodeString b) const
    {
        return static_cast<const StringBase<unsigned short>&>(a).compareNoCase(
            static_cast<const StringBase<unsigned short>&>(b)) < 0;
    }
};

typedef _STL::pair<const UnicodeString, bool> LanguageFilterValue;
typedef _STL::map<UnicodeString, bool, UnicodeStringLessThan,
    _STL::allocator<LanguageFilterValue> > LanguageFilterMap;

// The node allocator<...>::allocate and its proxy are referenced here only
// out of line by each other; retail's allocate copy (0x00154A00) is
// LanguageFilter.cpp's region shape, which this unit's flags do not give.
// The same dllimport+__forceinline route as TerrainLogicCtor keeps both
// inline-only so this unit emits neither COMDAT; bodies are the primary's.
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<LanguageFilterValue> *allocator<_Rb_tree_node<LanguageFilterValue> >::allocate(size_t __n, const void *) const
{ return __n != 0 ? reinterpret_cast<_Rb_tree_node<LanguageFilterValue> *>(allocator<char>::allocate(__n * sizeof(_Rb_tree_node<LanguageFilterValue>), 0)) : 0; }
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<LanguageFilterValue> *_STLP_alloc_proxy<_Rb_tree_node<LanguageFilterValue> *, _Rb_tree_node<LanguageFilterValue>, allocator<_Rb_tree_node<LanguageFilterValue> > >::allocate(size_t __n)
{ return __stl_alloc_rebind(static_cast<allocator<_Rb_tree_node<LanguageFilterValue> > &>(*this), (_Rb_tree_node<LanguageFilterValue> *)0).allocate(__n, 0); }
}

template bool &LanguageFilterMap::operator[](const UnicodeString&);
