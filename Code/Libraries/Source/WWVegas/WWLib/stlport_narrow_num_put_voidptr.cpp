// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC
// stlport
//
// num_put<char>::do_put(const void*), vtable slot 1 of 0x007BBA2C - MSVC 7.1
// lays a name's overloads out in reverse declaration order, so the pointer
// overload STLport declares last is the first do_put slot and the bool
// overload declared first is the last.
//
// This one body cannot come from the whole-class instantiation in
// stlport_narrow_num_put.cpp, because the shipped source opens with
//
//     locale __loc = __f.getloc();
//
// which nothing below it reads. Retail has no getloc call and no EH frame: it
// is 107 bytes of straight-line code. The dead line is absent from the source
// the game was built against, so the definition is supplied here as an
// explicit specialisation instead, identical but for that line.

#include <locale>

_STLP_BEGIN_NAMESPACE

typedef ostreambuf_iterator<char, char_traits<char> > _NarrowOut;

_STLP_TEMPLATE_NULL
inline _NarrowOut
num_put<char, _NarrowOut>::do_put(_NarrowOut __s, ios_base& __f, char,
                                  const void* __val) const
{
  const ctype<char>& __c_type = *(const ctype<char>*)__f._M_ctype_facet();
  ios_base::fmtflags __save_flags = __f.flags();

  __f.setf(ios_base::hex, ios_base::basefield);
  __f.setf(ios_base::showbase);
  __f.setf(ios_base::internal, ios_base::adjustfield);
  __f.width((sizeof(void*) * 2) + 2);
  _NarrowOut result = this->do_put(__s, __f, __c_type.widen('0'),
                                 __REINTERPRET_CAST(unsigned _STLP_LONG_LONG, __val));
  __f.flags(__save_flags);
  return result;
}

// num_put<char>::do_put(const void*) is a header inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked build. This
// anchor only makes this unit emit its copy for the ledger row; it is not retail code.
struct bfmeNumPutVoidPtrEmitter : num_put<char, _NarrowOut>
{
	static void emit(const bfmeNumPutVoidPtrEmitter *p, _NarrowOut s, ios_base &f, char c, const void *v);
};
#pragma inline_depth(0)
// ?emit@bfmeNumPutVoidPtrEmitter@_STL@@SAXPBU12@V?$ostreambuf_iterator@DV?$char_traits@D@_STL@@@2@AAVios_base@2@DPBX@Z present-unmatched
void bfmeNumPutVoidPtrEmitter::emit(const bfmeNumPutVoidPtrEmitter *p, _NarrowOut s, ios_base &f, char c, const void *v)
{
	p->num_put<char, _NarrowOut>::do_put(s, f, c, v);
}
#pragma inline_depth()

_STLP_END_NAMESPACE
