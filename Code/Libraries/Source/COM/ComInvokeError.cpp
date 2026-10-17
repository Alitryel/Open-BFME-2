// cl: /Ob2 /EHsc /DNDEBUG /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
#include <oaidl.h>
// Authored from retail and the MSVC 7.1 invkerr.obj symbol identities.
// SDK headers supply declarations only; no implementation source was read.
// The message field is an opaque allocation pointer; its element type is not claimed.
// Native comraise constructor654C90 proves the vptr/long/pointer/pointer layout.
// Only the static API is defined here; no object or virtual body is emitted.
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
typedef char ComErrorSize[sizeof(_com_error)==16?1:-1];
long _com_error::WCodeToHRESULT(unsigned short code) {
 return code>=0xfe00 ? (long)0x8004ffff : (long)(0x80040200+(unsigned int)code);
}

extern "C" const _GUID IID_IErrorInfo={0x1cf2b120,0x547d,0x101b,{0x8e,0x65,0x08,0x00,0x2b,0x2b,0xd1,0x19}};
extern "C" const _GUID IID_IDispatch={0x00020400,0,0,{0xc0,0,0,0,0,0,0,0x46}};
long __stdcall _com_handle_excepinfo(EXCEPINFO& excep,IErrorInfo **out) {
 if(excep.pfnDeferredFillIn)excep.pfnDeferredFillIn(&excep);
 ICreateErrorInfo *created=0;
 if(out && CreateErrorInfo(&created)>=0) {
  created->SetGUID(IID_IDispatch);
  if(excep.bstrSource)created->SetSource(excep.bstrSource);
  if(excep.bstrDescription)created->SetDescription(excep.bstrDescription);
  if(excep.bstrHelpFile)created->SetHelpFile(excep.bstrHelpFile);
  created->SetHelpContext(excep.dwHelpContext);
  if(created->QueryInterface(IID_IErrorInfo,(void**)out)<0)*out=0;
  created->Release();
 }
 if(excep.bstrSource)SysFreeString(excep.bstrSource);
 if(excep.bstrDescription)SysFreeString(excep.bstrDescription);
 if(excep.bstrHelpFile)SysFreeString(excep.bstrHelpFile);
 if(excep.wCode)return _com_error::WCodeToHRESULT(excep.wCode);
 return excep.scode;
}
