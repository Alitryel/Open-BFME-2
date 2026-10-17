// cl: /O2 /G7 /Oy /Ob1 /MD
// Native crtexew.obj call and PE msvcr71.dll import prove the C ABI.
// Genuine typed forwarding; no inline assembly or implementation donor.
typedef void (__cdecl *InitProc)();
extern "C" {
extern void (__cdecl *_imp___initterm)(InitProc *first,InitProc *last);
void __cdecl _initterm(InitProc *first,InitProc *last) { _imp___initterm(first,last); }
}
