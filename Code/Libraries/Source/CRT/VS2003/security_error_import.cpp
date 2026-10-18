// Visual C++ 7.1 CRT import: msvcr71.dll!__security_error_handler.
// VS2003 stdlib.h establishes the cdecl (int, void *) signature.
// Retail's complete six-byte FF25 thunk reads named IAT slot VA 00BBA478.
// An ordinary typed tail call preserves the generated owner's C++ coverage.
// cl: /O1 /G6 /MD
extern "C" {
typedef void (__cdecl *SecurityErrorHandler)(int, void *);
extern SecurityErrorHandler _imp____security_error_handler;

void __cdecl __security_error_handler(int code, void *argument)
{
    _imp____security_error_handler(code, argument);
}
}
