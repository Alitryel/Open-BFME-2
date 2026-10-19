// cl: /O2 /G7 /Oy /Ob1 /MD
// Retail msvcr71.dll exception import veneer; the public ABI forwards two pointers.
// _ThrowInfo is the compiler-provided type: preserve its native modifiers.
// __identifier names the actual IAT symbol without an alias or substitute datum.
extern "C" {
typedef void (__stdcall *CxxThrowProc)(void *, _ThrowInfo *);
extern CxxThrowProc __identifier("_imp___CxxThrowException@8");
void __stdcall _CxxThrowException(void *object, _ThrowInfo *info) {
    __identifier("_imp___CxxThrowException@8")(object, info);
}
}
