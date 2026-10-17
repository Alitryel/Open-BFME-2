// cl: /Ob2 /EHsc /DNDEBUG /MD
// Authored from retail and the existing MSVC 7.1 comsupp.obj identities.
// No Microsoft implementation source was read. The whole six-routine member
// is recovered together; native entry points and signatures come from its
// mangled symbols. Data bytes independently establish the callback and GUID.
// IUnknown slots 0..2 and ISupportErrorInfo slot 3 are proven by these calls.
#include <stdarg.h>
struct _GUID {unsigned long Data1;unsigned short Data2,Data3;unsigned char Data4[8];};
struct IErrorInfo;
struct IDispatch;
struct IUnknown {
 virtual long __stdcall QueryInterface(const _GUID&,void**)=0;
 virtual unsigned long __stdcall AddRef()=0;
 virtual unsigned long __stdcall Release()=0;
};
struct ISupportErrorInfo : IUnknown {
 virtual long __stdcall InterfaceSupportsErrorInfo(const _GUID&)=0;
};
extern "C" const _GUID IID_ISupportErrorInfo={0xdf0b3d60,0x548f,0x101b,{0x8e,0x65,0x08,0x00,0x2b,0x2b,0xd1,0x19}};
extern "C" __declspec(dllimport) long __stdcall GetErrorInfo(unsigned long,IErrorInfo**);
void __stdcall _com_raise_error(long,IErrorInfo*);
typedef void (__stdcall *ErrorHandler)(long,IErrorInfo*);
ErrorHandler __errorPfn=_com_raise_error;
long __cdecl _com_invoke_helper(IDispatch*,long,unsigned short,unsigned short,void*,const unsigned short*,char*,IErrorInfo**);

void __stdcall _com_issue_errorex(long hr,IUnknown *unknown,const _GUID& iid) {
 IErrorInfo *error=0;
 if(unknown && unknown->QueryInterface(IID_ISupportErrorInfo,(void**)&unknown)>=0) {
  long support=((ISupportErrorInfo*)unknown)->InterfaceSupportsErrorInfo(iid);
  unknown->Release();
  if(support==0 && GetErrorInfo(0,&error)!=0)error=0;
 }
 __errorPfn(hr,error);
}

void __stdcall _set_com_error_handler(ErrorHandler callback) {__errorPfn=callback;}
