// cl: /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// STLport 4.5.3 money_get<wchar_t>::do_get over string_type (stl/_monetary.c).
// Retail RVA 0x00012190 is one 2802-byte function, split by Ghidra into the
// 122-byte head and the 2680-byte tail at 0x0001220A; its ret 0x24 ends at
// 0x00012C82 and the five switch-table words that follow are data.
//
// Retail's destruction map: the wide string destructor ~_String_base<wchar_t>
// (0xB3C0) is called out of line at the 13 cold sites (ternary temporaries,
// the currency symbol's scope end, both early-exit groups) and inlined, with
// no inner EH state, at the final exit; narrow strings and ~locale are inline
// everywhere. MSVC 7.1 sizes an inline candidate by its out-of-line compiled
// body: cold sites are outlined above about 80 bytes, the hot final exit stays
// inline up to about 96. The TU-local ~_String_base<wchar_t> below adds empty
// member-destructor calls (7 bytes each out of line, nothing once inlined) to
// land in that window, and the visible _M_assign_dispatch<wchar_t*> uses its
// __false_type tag so the caller keeps the tag's zero store and bool slot.
// The vendor allocator keeps the inlined copies free of proxy EH states.
/*
 * Copyright (c) 1999
 * Silicon Graphics Computer Systems, Inc.
 *
 * Copyright (c) 1999 
 * Boris Fomitchev
 *
 * This material is provided "as is", with absolutely no warranty expressed
 * or implied. Any use is at your own risk.
 *
 * Permission to use or copy this software for any purpose is hereby granted 
 * without fee, provided the above notices are retained on all copies.
 * Permission to modify the code and to distribute modified code is granted,
 * provided the above notices are retained, and a notice that the code was
 * modified is included with the above copyright notice.
 *
 */ 

// Suppress stdlib.h so free retains the C++ linkage and throwing declaration
// needed for retail's direct call and exception-state stores. These are the
// declarations consumed by the vendor cstdlib wrapper.
#define _INC_STDLIB

typedef unsigned int size_t;

typedef struct { int quot; int rem; } div_t;
typedef struct { long quot; long rem; } ldiv_t;

void __cdecl free(void *block);

extern "C" {
void __cdecl abort(void);
int __cdecl abs(int value);
int __cdecl atexit(void (__cdecl *routine)(void));
double __cdecl atof(const char *string);
int __cdecl atoi(const char *string);
long __cdecl atol(const char *string);
void *__cdecl bsearch(const void *key, const void *base, size_t count,
        size_t width, int (__cdecl *compare)(const void *, const void *));
void *__cdecl calloc(size_t count, size_t size);
div_t __cdecl div(int numerator, int denominator);
void __cdecl exit(int status);
char *__cdecl getenv(const char *name);
long __cdecl labs(long value);
ldiv_t __cdecl ldiv(long numerator, long denominator);
void *__cdecl malloc(size_t size);
int __cdecl mblen(const char *ch, size_t count);
size_t __cdecl mbstowcs(unsigned short *dest, const char *source, size_t count);
int __cdecl mbtowc(unsigned short *dest, const char *source, size_t count);
void __cdecl qsort(void *base, size_t count, size_t width,
        int (__cdecl *compare)(const void *, const void *));
int __cdecl rand(void);
void *__cdecl realloc(void *block, size_t size);
void __cdecl srand(unsigned int seed);
double __cdecl strtod(const char *string, char **end);
long __cdecl strtol(const char *string, char **end, int radix);
unsigned long __cdecl strtoul(const char *string, char **end, int radix);
int __cdecl system(const char *command);
size_t __cdecl wcstombs(char *dest, const unsigned short *source, size_t count);
int __cdecl wctomb(char *dest, unsigned short ch);
}

// Only pointer calls to streambuf are needed here. Keeping this interface
// opaque preserves the retail sbumpc call inside inline iterator increment.
#define _STLP_INTERNAL_STREAMBUF
#include <stl/_alloc.h>
// Use the rowed malloc allocator provider instead of emitting a competing copy.
namespace _STL { template <> void *__malloc_alloc<0>::allocate(size_t); }
#include <memory>
enum { _MONEY_LEAKS_CHECK = 0 };
#include <string>
// The rowed wide insert helper is supplied by stlport_wide_string_insert_aux.cpp.
namespace _STL {
template <> wchar_t *basic_string<wchar_t>::_M_insert_aux(wchar_t *, wchar_t);
}
// allocate binds to the rowed retail copy (0x00025090, STLMallocAlloc0Allocate.cpp): this
// unit's own out-of-line copy is not retail's and is first in link order.
namespace _STL { template<> void* __malloc_alloc<0>::allocate(size_t); }
namespace _STL {
struct _MoneyLeak { ~_MoneyLeak() { if (_MONEY_LEAKS_CHECK) free(0); } };
struct _MoneyPhantom { _MoneyLeak l; };
template <> inline _String_base<unsigned short, allocator<unsigned short> >::~_String_base() {
  _M_deallocate_block();
  // Nine empty member destructors: each adds out-of-line cost and nothing
  // once inlined (see the file comment).
  ((_MoneyPhantom *)this)->~_MoneyPhantom();
  ((_MoneyPhantom *)this)->~_MoneyPhantom();
  ((_MoneyPhantom *)this)->~_MoneyPhantom();
  ((_MoneyPhantom *)this)->~_MoneyPhantom();
  ((_MoneyPhantom *)this)->~_MoneyPhantom();
  ((_MoneyPhantom *)this)->~_MoneyPhantom();
  ((_MoneyPhantom *)this)->~_MoneyPhantom();
  ((_MoneyPhantom *)this)->~_MoneyPhantom();
  ((_MoneyPhantom *)this)->~_MoneyPhantom();
}
template <> template <> basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >&
basic_string<wchar_t, char_traits<wchar_t>, allocator<wchar_t> >::_M_assign_dispatch<wchar_t*>(wchar_t* __f, wchar_t* __l, const __false_type& __t) {
    pointer __cur = this->_M_start;
    while (__f != __l && __cur != this->_M_finish) {
      traits_type::assign(*__cur, *__f);
      ++__f;
      ++__cur;
    }
    if (__f == __l)
      erase(__cur, end());
    else
      append(__f, __l);
    // The tag is "used", so the caller keeps retail's zero store for it.
    ((_MoneyPhantom *)&__t)->~_MoneyPhantom();
    return *this;
}
}
#include <locale>

namespace _STL {
template<> class basic_streambuf<wchar_t, char_traits<wchar_t> > {
public:
  typedef char_traits<wchar_t>::int_type int_type;
  int_type sbumpc();
  int_type sgetc();
};
}


// The locale implementation is opaque in _locale.h. Its three vtable slots
// are established by stlport_locale.cpp; visibility here inlines _M_decr.
namespace _STL {
class _Locale_impl {
public:
    virtual ~_Locale_impl();
    virtual void _M_incr();
    virtual void _M_decr();
    locale::facet **_M_facets;
    unsigned int _M_count;
};
inline locale::~locale() _STLP_NOTHROW { _M_impl->_M_decr(); }

}
// Keep the vendor _M_getc body visible for MSVC's side-effect analysis while
// preserving retail's out-of-line calls. A declaration alone makes the compiler
// spill the iterator instead of retaining it in ebp/ebx across those calls.
namespace _STL
{
template <>
__declspec(noinline) void istreambuf_iterator<wchar_t, char_traits<wchar_t> >::_M_getc() const
{
    if (_M_have_c)
        return;
    int_type c = _M_buf->sgetc();
    _M_c = traits_type::to_char_type(c);
    _M_eof = traits_type::eq_int_type(c, traits_type::eof());
    _M_have_c = true;
}
}
namespace _STL {
template <> __declspec(noinline) bool
istreambuf_iterator<wchar_t, char_traits<wchar_t> >::equal(const istreambuf_iterator<wchar_t, char_traits<wchar_t> >& other) const {
    if (_M_buf) _M_getc();
    if (other._M_buf) other._M_getc();
    return _M_eof == other._M_eof;
}
template <> __forceinline istreambuf_iterator<wchar_t, char_traits<wchar_t> >&
istreambuf_iterator<wchar_t, char_traits<wchar_t> >::operator++() {
    _M_buf->sbumpc();
    _M_have_c = false;
    return *this;
}
// These string operations are separate functions in this retail instantiation.
}
namespace _STL {
typedef istreambuf_iterator<wchar_t, char_traits<wchar_t> > _MoneyIn;
template <> bool __get_monetary_value(_MoneyIn& __first, _MoneyIn __last, back_insert_iterator<basic_string<wchar_t> > __out, const ctype<wchar_t>& _c_type, wchar_t __point, int __frac_digits, wchar_t __sep, const string& __grouping, bool& __syntax_ok);

template <> __forceinline pair<_MoneyIn, bool> __get_string(_MoneyIn first, _MoneyIn last, const wchar_t* start, const wchar_t* end) {
  pair<_MoneyIn, const wchar_t*> result = mismatch(first, last, start);
  return make_pair(result.first, result.second == end);
}

// Same operation as __get_string; retail inlines only the symbol case.
__forceinline pair<_MoneyIn, bool> __get_symbol(_MoneyIn first, _MoneyIn last, const wchar_t* start, const wchar_t* end) {
  pair<_MoneyIn, const wchar_t*> result = mismatch(first, last, start);
  return make_pair(result.first, result.second == end);
}
template <> _MoneyIn money_get<wchar_t, _MoneyIn>::do_get(_MoneyIn __s, _MoneyIn __end, bool __intl, ios_base& __str, ios_base::iostate& __err, basic_string<wchar_t>& __digits) const
{
  typedef wchar_t _CharT;
  typedef _MoneyIn _InputIter;
  if (__s == __end) {
    __err |= ios_base::eofbit;
    return __s;
  }

  typedef moneypunct<_CharT, false> _Punct;
  typedef moneypunct<_CharT, true>  _Punct_intl;
  typedef ctype<_CharT>             _Ctype;

  locale __loc = __str.getloc();
  const _Punct&      __punct      = use_facet<_Punct>(__loc) ;
  const _Punct_intl& __punct_intl = use_facet<_Punct_intl>(__loc) ;
  const _Ctype&      __c_type      = use_facet<_Ctype>(__loc) ;
                   
  money_base::pattern __format = __intl ? __punct_intl.neg_format()
                                        : __punct.neg_format();
  string_type __ns = __intl ? __punct_intl.negative_sign()
                            : __punct.negative_sign();
  string_type __ps = __intl ? __punct_intl.positive_sign()
                            : __punct.positive_sign();
  int __i;
  bool __is_positive = true;
  bool __symbol_required = (__str.flags() & ios_base::showbase) !=0;
  string_type __buf;
  back_insert_iterator<string_type> __out(__buf);

  for (__i = 0; __i < 4; ++__i) {
    switch (__format.field[__i]) {
    case (char) money_base::none:
      if (__i == 3) {
        if (__c_type.is(ctype_base::space, *__s)) {
          __err = ios_base::failbit;
          return __s;
        }
        break;
      }
      while (__s != __end && __c_type.is(ctype_base::space, *__s))
        ++__s;
      break;
    case (char) money_base::space:
      if (!__c_type.is(ctype_base::space, *__s)) {
        __err = ios_base::failbit;
        return __s;
      }
      ++__s;
      while (__s != __end && __c_type.is(ctype_base::space, *__s))
        ++__s;
      break;
    case money_base::symbol: {
      string_type __cs = __intl ? __punct_intl.curr_symbol()
                                : __punct.curr_symbol();
      pair<iter_type, bool>
      __result  = __get_symbol(__s, __end, __cs.begin(), __cs.end());
      if (!__result.second && __symbol_required)
        __err = ios_base::failbit;
      __s = __result.first;
      break;
    }
    case money_base::sign: {
      if (__s == __end) {
        if (__ps.size() == 0)
          break;
        if (__ns.size() == 0) {
          __is_positive = false;
          break;
        }
        __err = ios_base::failbit;
        return __s;
      }
      else {
        if (__ps.size() == 0) {
          if (__ns.size() == 0)
            break;
          if (*__s == ++__ns[0]) {
            ++__s;
            __is_positive = false;
            break;
          }
          __err = ios_base::failbit;
        } 
        else {
          if (*__s == __ps[0]) {
            ++__s;
            break;
          }
          if (__ns.size() == 0)
            break;
          if (*__s == __ns[0]) {
            ++__s;
            __is_positive = false;
            break;
          }
          __err = ios_base::failbit;
        }
      }
      return __s;
    }
    case money_base::value: {
      _CharT __point = __intl ? __punct_intl.decimal_point()
                              : __punct.decimal_point();
      int __frac_digits = __intl ? __punct_intl.frac_digits()
                                 : __punct.frac_digits();
      string __grouping = __intl ? __punct_intl.grouping()
                                 : __punct.grouping();
      bool __syntax_ok = true;

      bool __result;

      _CharT __sep = __grouping.size() == 0 ? _CharT() : 
	__intl ? __punct_intl.thousands_sep() : __punct.thousands_sep();

      __result = __get_monetary_value(__s, __end, __out, __c_type,
                                      __point, __frac_digits,
                                      __sep,
                                      __grouping, __syntax_ok);      

      if (!__syntax_ok)
        __err |= ios_base::failbit;
      if (!__result) {
        __err = ios_base::failbit;
        return __s;
      }
      break;
      
    }                           // Close money_base::value case


    }                           // Close switch statement
  }                             // Close for loop

  if (__is_positive) {
    if (__ps.size() > 1) {
      pair<_InputIter, bool>
        __result = __get_string(__s, __end, ((const string_type&)__ps).begin() + 1, ((const string_type&)__ps).end());
      __s = __result.first;
      if (!__result.second)
	__err |= ios::failbit;
    }
    if (!(__err & ios_base::failbit))
      __digits = __buf;
  }
  else {
    if (__ns.size() > 1) {
      pair<_InputIter, bool>
        __result = __get_string(__s, __end, ((const string_type&)__ns).begin() + 1, ((const string_type&)__ns).end());
      __s = __result.first;
      if (!__result.second)
	__err |= ios::failbit;
    }
    if (!(__err & ios::failbit)) {
      __buf.insert(__buf.begin(),__c_type.widen('-'));
      __digits = __buf;
    }
  }
  if (__s == __end)
    __err |= ios::eofbit;

  return __s;
}
}
