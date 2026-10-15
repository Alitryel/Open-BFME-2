// ??1?$_Vector_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ
// partial score=0.5730462519936204 date=2026-10-15
// ??1?$_Vector_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ
// partial score=0.5730462519936204 date=2026-10-14
// ??1?$_Vector_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ
// partial score=0.5730462519936204 date=2026-10-14
// ??1?$_Vector_base@PAVObject@@V?$allocator@PAVObject@@@_STL@@@_STL@@QAE@XZ
// partial score=0.5730462519936204 date=2026-10-14
// Native 001F1609..001F1634; WB B09640 has the same pointer-triple/free spine.
// This diagnostic body is 14B; retail retains a 43B EH frame/state for empty
// allocator cleanup at this+8. Object* is a consumer-view inference.
// No matched row or independent original template identity is asserted.
// cl: /O1 /G7 /MD /EHsc
void __cdecl Rva00030830GameFree(void *);
class Object;
namespace _STL {

template<class T> class allocator {public:~allocator();};
template<class P,class T,class A> struct _STLP_alloc_proxy: A {P _M_data; };
template<class T,class A> struct _Vector_base {T *_M_start,*_M_finish;_STLP_alloc_proxy<T*,T,A> _M_end_of_storage; __declspec(noinline) ~_Vector_base();};
template<class T,class A> _Vector_base<T,A>::~_Vector_base(){if(_M_start)Rva00030830GameFree(_M_start);}

template struct _Vector_base<Object*,allocator<Object*> >;
}
