// cl: /O2 /G7 /Oy /Ob1 /MD
// Native atonexit.obj names __dllonexit and passes callback plus two table
// bounds by address. Retail PE msvcr71.dll!__dllonexit at IAT 0x00BBA43C.
// Typed C++ forwarding; independently reconstructed from native call evidence.
typedef int (__cdecl *ExitProc)();
extern "C" {
extern ExitProc (__cdecl *_imp____dllonexit)(ExitProc,ExitProc **,ExitProc **);
ExitProc __cdecl __dllonexit(ExitProc callback,ExitProc **begin,ExitProc **end) {
 return _imp____dllonexit(callback,begin,end);
}
}
