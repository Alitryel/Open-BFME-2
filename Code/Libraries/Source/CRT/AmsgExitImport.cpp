// cl: /O2 /G7 /Oy /Ob1 /MD
// Native crtexew.obj call and PE msvcr71.dll import prove the C ABI.
// Genuine typed forwarding; no inline assembly or implementation donor.

extern "C" {
extern void (__cdecl *_imp___amsg_exit)(int message);
void __cdecl _amsg_exit(int message) { _imp___amsg_exit(message); }
}
