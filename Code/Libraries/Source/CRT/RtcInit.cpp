// cl: /O1 /G7 /Ob1 /MD
// Native init.obj public identities and retail code; public header declarations only.
// No CRT implementation source was read. The original private once flag
// is a one-byte bool at RVA 0x00A1F540, initialized to zero.
// Public rtcapi.h establishes the reserved five-argument callback ABI.
#include <rtcapi.h>
void __cdecl _RTC_InitBase() {
 static bool init=false;
 if(!init) {
  init=true;
  _RTC_SetErrorFunc(_CRT_RTC_INIT(0,0,0,1,0));
 }
}
void __cdecl _RTC_Shutdown() {
 _CRT_RTC_INIT(0,0,0,1,1);
}
