// ?do_get@?$money_get@GV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@_STL@@@_STL@@MBE?AV?$istreambuf_iterator@GV?$char_traits@G@_STL@@@2@V32@0_NAAVios_base@2@AAHAAV?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@2@@Z
// partial score=0.9766 date=2026-10-20
// cl: /Ob1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
// STLport4.5.3 wide money_get string parser; complete source, partial bytes.
// Native 12190..12C82 is 2802 B code; 20 B switch table follows before padding.
// Retire both the 122 B head 12190 and the 2680 B tail 1220A only on full verification.
// claudeb4 2026-10-20: fit 0.9766, nd 21, 2820 B. A leaks-check shim on
// ~allocator<unsigned short> reproduces retail's dtor map exactly (13 out-of-line
// wide dtor calls, inline free at the final exit and for narrow temps; the call
// sequence with EH states equals retail's). Residue: (1) _M_assign_dispatch is
// visible, so c2 drops retail's zero store of the __false_type tag and moves the
// bool slot (an opaque callee fixes it, but every decl-only form ICEs); (2) the
// three inlined final-exit dtors carry proxy states 0x16..0x18 (retail: none);
// (3) edx load order at 0x12bf3. Handoff:
// reverse/attempt_support/wide-money-get-string-12190-20261020/handoff.md
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
struct _MoneyStorageTag {};
__forceinline void *operator new(size_t, void *storage, _MoneyStorageTag) { return storage; }
#include <memory>
enum { _MONEY_LEAKS_CHECK = 0 };
namespace _STL {
template <> inline allocator<unsigned short>::~allocator() { if (_MONEY_LEAKS_CHECK) free(0); }
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
typedef basic_string<wchar_t> _MoneyString;
class _MoneyNameStorage {
 union { unsigned char storage[sizeof(_MoneyString)]; void *alignment; };
public:
 __forceinline _MoneyNameStorage() { new(storage,_MoneyStorageTag()) _MoneyString; }
 __forceinline _MoneyNameStorage(const _MoneyString &value) { new(storage,_MoneyStorageTag()) _MoneyString(value); }
 __forceinline ~_MoneyNameStorage() { wchar_t *p=ref().begin(); if(p) free(p); }
 __forceinline _MoneyString &ref() { return *reinterpret_cast<_MoneyString *>(storage); }
 __forceinline const _MoneyString &ref() const { return *reinterpret_cast<const _MoneyString *>(storage); }
 __forceinline operator _MoneyString &() { return ref(); }
 __forceinline operator const _MoneyString &() const { return ref(); }
 __forceinline const wchar_t *data() const { return ref().data(); }
 __forceinline size_t size() const { return ref().size(); }
 __forceinline wchar_t *begin() { return ref().begin(); }
 __forceinline wchar_t &operator[](size_t i) { return ref()[i]; }
 __forceinline void insert(wchar_t *p,wchar_t c) { ref().insert(p,c); }
};
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
