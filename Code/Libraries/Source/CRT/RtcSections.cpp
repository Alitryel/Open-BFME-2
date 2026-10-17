// cl: /Oy- /Ob1 /MD
// Region O1/G7 defaults reproduce the native code.
// Each loop protects an individual callback with SEH and continues on failure.
// Four native four-byte null sentinels bound linker-sorted callback sections.
// Authored from retail and initsect.obj identities; no CRT implementation read.
typedef void (__cdecl *RtcCallback)();
extern "C" {
#pragma section(".rtc$IAA",read)
#pragma section(".rtc$IZZ",read)
#pragma section(".rtc$TAA",read)
#pragma section(".rtc$TZZ",read)
__declspec(allocate(".rtc$IAA")) RtcCallback __rtc_iaa[]={0};
__declspec(allocate(".rtc$IZZ")) RtcCallback __rtc_izz[]={0};
__declspec(allocate(".rtc$TAA")) RtcCallback __rtc_taa[]={0};
__declspec(allocate(".rtc$TZZ")) RtcCallback __rtc_tzz[]={0};
#pragma comment(linker,"/MERGE:.rtc=.rdata")
void __cdecl _RTC_Initialize() {
 for(RtcCallback *p=__rtc_iaa+1;p<__rtc_izz;++p) {
  __try {if(*p)(*p)();}
  __except(1) {}
 }
}
}
