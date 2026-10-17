// cl: /O2 /G6 /Ob2 /EHsc /DNDEBUG /MD
// Native6547C0..65482F,111B RET8. Identity and ABI come from the existing
// compiler-mangled _variant_t(long,unsigned short) comsupp.lib row and its
// exact Release/comutil.obj member, independently reproduced from retail.
// No Microsoft implementation source was used. This is an authored recovery.
// Native tag checks accept VT_I4=3,VT_ERROR=10,VT_BOOL=11; invalid input calls
// the existing stdcall _com_issue_error(E_INVALIDARG) provider654B20.
// The 16B automation value has its tag at0 and value union at8. Reserved
// words and unused union bytes are intentionally untouched, as in retail.
void __stdcall _com_issue_error(long);
class _variant_t {
public:
 _variant_t(long value,unsigned short tag);
 ~_variant_t();
private:
 unsigned short vt,reserved1,reserved2,reserved3;
 union {long integerValue; long errorValue; short booleanValue; double storage;};
};
typedef char VariantSize[sizeof(_variant_t)==16?1:-1];
_variant_t::_variant_t(long value,unsigned short tag)
{
 if(tag!=3 && tag!=10 && tag!=11) {
  _com_issue_error((long)0x80070057);
 } else if(tag==10) {
  errorValue=value;
  vt=10;
 } else if(tag==11) {
  vt=11;
  booleanValue=value ? (short)-1 : (short)0;
 } else {
  vt=3;
  integerValue=value;
 }
}

// Native 6547B0..6547BE: signed HRESULT check, 15 bytes.
namespace _com_util {
 void CheckError(long hr) {if(hr<0)_com_issue_error(hr);}
}
