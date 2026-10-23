// cl: /O2 /G7 /Oy /Ob1 /MD
// Typed callable import veneer. The public rtcapi.h declares this exact ABI;
// native init.obj and PE msvcr71.dll!_CRT_RTC_INIT independently bind its target.
#include <rtcapi.h>
extern "C" {
extern _RTC_error_fn (__cdecl *_imp___CRT_RTC_INIT)(void*,void**,int,int,int);
_RTC_error_fn __cdecl _CRT_RTC_INIT(void *p0,void **p1,int p2,int p3,int p4) {
 return _imp___CRT_RTC_INIT(p0,p1,p2,p3,p4);
}
}
