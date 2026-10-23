// _com_error: canonical ABI from reverse/class_contracts/_com_error.json.
// Native constructor/throw object prove16B, vptr0, HRESULT4, IErrorInfo*8,
// and opaque LocalFree allocation12. No message element type or ownership
// default is inferred. SDK supplies interface declarations only.
// The generated data skeleton is completed with evidenced API declarations;
// no implementation body is defined here.
#ifndef CANONICAL__COM_ERROR_H
#define CANONICAL__COM_ERROR_H
#include <oaidl.h>

class _com_error {
public:
 _com_error(long,IErrorInfo*,bool);
 _com_error(const _com_error&);
 virtual ~_com_error();
 static long WCodeToHRESULT(unsigned short);
private:
 long result;
 IErrorInfo *info;
 void *message;
};
typedef char ComErrorNativeSize[sizeof(_com_error)==16?1:-1];
#endif
