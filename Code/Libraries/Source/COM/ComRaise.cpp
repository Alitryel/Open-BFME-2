// cl: /O2 /G6 /Ob2 /EHsc /GR /DNDEBUG /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// Authored from retail and native MSVC7.1 comraise.obj identities.
// Shared ABI is recorded in class_contracts/_com_error.json; source uses
// canonical SDK declarations, not Microsoft implementation source.
#include "ComError.h"
void __cdecl operator delete(void*);
_com_error::_com_error(long value,IErrorInfo *error,bool addRef)
 :result(value),info(error),message(0)
{
 if(info && addRef)info->AddRef();
}

_com_error::_com_error(const _com_error& other)
 :result(other.result),info(other.info),message(0)
{
 if(info)info->AddRef();
}

_com_error::~_com_error()
{
 if(info)info->Release();
 if(message)LocalFree((HLOCAL)message);
}

void __stdcall _com_raise_error(long value,IErrorInfo *error)
{
 throw _com_error(value,error,false);
}
