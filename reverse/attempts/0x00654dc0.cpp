// ?_com_invoke_helper@@YAJPAUIDispatch@@JGGPAXPBGPADPAPAUIErrorInfo@@@Z
// partial score=0.75 date=2026-10-17
// cl: /O2 /G6 /Ob2 /EHsc /GR /DNDEBUG /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// Authored from retail INVKPRXY code, native symbols and SDK declarations only.
#include <oaidl.h>
#include <stdarg.h>
#include <malloc.h>
#include <string.h>
struct __declspec(uuid("00000000-0000-0000-0000-000000000000")) NullDispatchIID;
long __stdcall _com_handle_excepinfo(EXCEPINFO&,IErrorInfo**);
long __cdecl _com_invoke_helper(IDispatch *dispatch,long id,unsigned short flags,unsigned short retType,void *result,const unsigned short *types,char *args,IErrorInfo **out) {
 if(!dispatch)return E_POINTER;
 if(out)*out=0;
 DISPPARAMS dp={0};
 if(types)dp.cArgs=lstrlenW((LPCWSTR)types);
 DISPID named=DISPID_PROPERTYPUT;
 if(flags & (DISPATCH_PROPERTYPUT|DISPATCH_PROPERTYPUTREF)) {
  if(!dp.cArgs)return E_INVALIDARG;
  dp.cNamedArgs=1;dp.rgdispidNamedArgs=&named;
 }
 if(dp.cArgs>0) {
  VARIANTARG *base;
  __try {base=(VARIANTARG*)_alloca(dp.cArgs*sizeof(VARIANTARG));}
  __except(1) {return HRESULT_FROM_WIN32(GetLastError());}
  memset(base,0,dp.cArgs*sizeof(VARIANTARG));
  dp.rgvarg=base;
  const unsigned short *type=types;
  VARIANTARG *arg=base+dp.cArgs-1;
  for(;*type;--arg,++type) {
   arg->vt=*type & 0xF7FF;
   switch(arg->vt) {
   case VT_I2: case VT_UI2: arg->iVal=va_arg(args,short);break;
   case VT_I4: case VT_ERROR: case VT_UI4: case VT_HRESULT: arg->lVal=va_arg(args,long);break;
   case VT_BSTR: arg->bstrVal=va_arg(args,BSTR);break;
   case VT_DISPATCH: arg->pdispVal=va_arg(args,IDispatch*);break;
   case VT_UNKNOWN: arg->punkVal=va_arg(args,IUnknown*);break;
   case VT_INT: arg->intVal=va_arg(args,int);break;
   case VT_UINT: arg->uintVal=va_arg(args,unsigned);break;
   case VT_RECORD: arg->byref=va_arg(args,void*);break;
   case VT_R4: arg->vt=VT_R8;
   case VT_R8: case VT_DATE: memcpy(&arg->dblVal,&va_arg(args,double),sizeof(double));break;
   case VT_I8: arg->llVal=va_arg(args,LONGLONG);break;
   case VT_UI8: arg->ullVal=va_arg(args,ULONGLONG);break;
   case VT_CY: arg->cyVal=*va_arg(args,CY*);break;
   case VT_BOOL: arg->boolVal=va_arg(args,short)?VARIANT_TRUE:VARIANT_FALSE;break;
   case VT_VARIANT: *arg=*va_arg(args,VARIANT*);break;
   case VT_DECIMAL: arg->decVal=*va_arg(args,DECIMAL*);arg->vt=VT_DECIMAL;break;
   case VT_I1: case VT_UI1: arg->bVal=va_arg(args,BYTE);break;
#define REF(T) case VT_BYREF|T:
   REF(VT_I2) REF(VT_I4) REF(VT_R4) REF(VT_R8) REF(VT_CY) REF(VT_DATE)
   REF(VT_BSTR) REF(VT_DISPATCH) REF(VT_ERROR) REF(VT_BOOL) REF(VT_VARIANT)
   REF(VT_UNKNOWN) REF(VT_DECIMAL) REF(VT_I1) REF(VT_UI1) REF(VT_UI2)
   REF(VT_UI4) REF(VT_I8) REF(VT_UI8) REF(VT_INT) REF(VT_UINT) REF(VT_HRESULT) REF(VT_RECORD)
    arg->byref=va_arg(args,void*);break;
#undef REF
   default: if(arg->vt&VT_ARRAY)arg->parray=va_arg(args,SAFEARRAY*);else return E_INVALIDARG;
   }
  }
  arg=base+dp.cNamedArgs;
  const unsigned short *tailType=types+dp.cArgs-dp.cNamedArgs-1;
  unsigned removed=0;
  for(;tailType>=types;++arg,--tailType) {
   if((*tailType & ~VT_BYREF)!=0x080C)break;
   VARIANT *probe=(*tailType & VT_BYREF)?arg->pvarVal:arg;
   if(probe->vt!=VT_ERROR || probe->scode!=DISP_E_PARAMNOTFOUND)break;
   ++removed;
  }
  if(removed>0) {
   for(unsigned i=0;i<dp.cNamedArgs;++i)base[i+removed]=base[i];
   dp.cArgs-=removed;dp.rgvarg+=removed;
  }
 }
 VARIANT value;VariantInit(&value);
 EXCEPINFO ex={0};unsigned argerr=-1;
 long hr=dispatch->Invoke(id,__uuidof(NullDispatchIID),0,flags,&dp,retType?&value:0,&ex,&argerr);
 if(hr<0) {
  VariantClear(&value);
  if(hr==DISP_E_EXCEPTION)return _com_handle_excepinfo(ex,out);
  return hr;
 }
 if(retType && result) {
  if(retType!=VT_VARIANT && retType!=value.vt) {
   hr=VariantChangeType(&value,&value,0,retType);
   if(hr<0) {VariantClear(&value);return hr;}
  }
  switch(retType) {
  case VT_I2: case VT_UI2: *(short*)result=value.iVal;break;
  case VT_I4: case VT_ERROR: case VT_UI4: case VT_HRESULT: *(long*)result=value.lVal;break;
  case VT_R4: *(float*)result=value.fltVal;break;
  case VT_BSTR: *(BSTR*)result=value.bstrVal;break;
  case VT_INT: *(int*)result=value.intVal;break;
  case VT_DISPATCH: *(IDispatch**)result=value.pdispVal;break;
  case VT_UNKNOWN: *(IUnknown**)result=value.punkVal;break;
  case VT_UINT: *(unsigned*)result=value.uintVal;break;
  case VT_RECORD: *(void**)result=value.byref;break;
  case VT_R8: case VT_DATE: *(double*)result=value.dblVal;break;
  case VT_BOOL: *(VARIANT_BOOL*)result=value.boolVal;break;
  case VT_VARIANT: *(VARIANT*)result=value;break;
  case VT_DECIMAL: *(DECIMAL*)result=value.decVal;break;
  case VT_I1: *(char*)result=value.cVal;break;
  case VT_UI1: *(BYTE*)result=value.bVal;break;
  case VT_I8: *(LONGLONG*)result=value.llVal;break;
  case VT_UI8: *(ULONGLONG*)result=value.ullVal;break;
  case VT_CY: *(CY*)result=value.cyVal;break;
#define REF(T,F,P) case VT_BYREF|T: *(P**)result=value.F;break;
  REF(VT_I2,piVal,short) REF(VT_R8,pdblVal,double) REF(VT_BSTR,pbstrVal,BSTR)
  REF(VT_BOOL,pboolVal,VARIANT_BOOL) REF(VT_DECIMAL,pdecVal,DECIMAL) REF(VT_UI2,puiVal,unsigned short)
  REF(VT_UINT,puintVal,unsigned)
  REF(VT_I4,plVal,long) REF(VT_DATE,pdate,DATE) REF(VT_DISPATCH,ppdispVal,IDispatch*)
  REF(VT_VARIANT,pvarVal,VARIANT) REF(VT_I1,pcVal,char) REF(VT_UI4,pulVal,unsigned long)
  REF(VT_I8,pllVal,LONGLONG)
  REF(VT_R4,pfltVal,float) REF(VT_CY,pcyVal,CY) REF(VT_ERROR,pscode,SCODE)
  REF(VT_UNKNOWN,ppunkVal,IUnknown*) REF(VT_UI1,pbVal,BYTE) REF(VT_UI8,pullVal,ULONGLONG)
  REF(VT_INT,pintVal,int) REF(VT_HRESULT,plVal,long) REF(VT_RECORD,byref,void)
#undef REF
  default:
   if(retType&VT_ARRAY)*(SAFEARRAY**)result=value.parray;
   else {VariantClear(&value);return E_INVALIDARG;}
  }
 }
 return hr;
}
long __cdecl _com_dispatch_raw_method(IDispatch *dispatch,long id,unsigned short flags,unsigned short type,void *result,const unsigned short *types,...) {
 va_list args;va_start(args,types);IErrorInfo *error;
 long hr=_com_invoke_helper(dispatch,id,flags,type,result,types,args,&error);
 if(hr<0)SetErrorInfo(0,error);return hr;
}
long __stdcall _com_dispatch_raw_propget(IDispatch *dispatch,long id,unsigned short type,void *result) {
 return _com_dispatch_raw_method(dispatch,id,2,type,result,0);
}
long __cdecl _com_dispatch_raw_propput(IDispatch *dispatch,long id,unsigned short type,...) {
 unsigned short types[2]={type,0};unsigned short flags=(type==9 || type==13)?8:4;
 va_list args;va_start(args,type);IErrorInfo *error;
 long hr=_com_invoke_helper(dispatch,id,flags,0,0,types,args,&error);
 if(hr<0)SetErrorInfo(0,error);return hr;
}


