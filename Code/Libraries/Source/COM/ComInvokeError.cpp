// cl: /Ob2 /EHsc /DNDEBUG /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
#include <oaidl.h>
// Authored from retail and the MSVC 7.1 invkerr.obj symbol identities.
// SDK headers supply declarations only; no implementation source was read.
// The message field is an opaque allocation pointer; its element type is not claimed.
// Native comraise constructor654C90 proves the vptr/long/pointer/pointer layout.
// Only the static API is defined here; no object or virtual body is emitted.
class _com_error {
public:
 _com_error(long,IErrorInfo*,bool=true);
 _com_error(const _com_error&);
 virtual ~_com_error();
 static long WCodeToHRESULT(unsigned short);
private:
 long result;
 IErrorInfo *info;
 void *message;
};
typedef char ComErrorSize[sizeof(_com_error)==16?1:-1];
long _com_error::WCodeToHRESULT(unsigned short code) {
 return code>=0xfe00 ? (long)0x8004ffff : (long)(0x80040200+(unsigned int)code);
}
