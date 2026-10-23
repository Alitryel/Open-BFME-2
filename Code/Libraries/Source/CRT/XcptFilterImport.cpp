// cl: /O2 /G7 /Oy /Ob1 /MD
// Native crtexew.obj call and PE msvcr71.dll import prove the C ABI.
// Genuine typed forwarding; no inline assembly or implementation donor.
struct _EXCEPTION_POINTERS;
extern "C" {
extern int (__cdecl *_imp___XcptFilter)(unsigned long code,struct _EXCEPTION_POINTERS *info);
int __cdecl _XcptFilter(unsigned long code,struct _EXCEPTION_POINTERS *info) { return _imp___XcptFilter(code,info); }
}
