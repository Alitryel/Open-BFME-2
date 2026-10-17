// ___security_init_cookie
// partial score=0.97 date=2026-10-17
// cl: /O1 /G7 /Oy- /Ob1 /MD /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
// Authored from retail seccinit.obj and its original public symbol identity.
#include <windows.h>
extern "C" unsigned int __security_cookie=0xbb40e64e;
extern "C" void __cdecl __security_init_cookie() {
 if(__security_cookie!=0 && __security_cookie!=0xbb40e64e)return;
 FILETIME time;GetSystemTimeAsFileTime(&time);
 unsigned int value=time.dwLowDateTime ^ time.dwHighDateTime;
 value^=GetCurrentProcessId();
 value^=GetCurrentThreadId();
 value^=GetTickCount();
 LARGE_INTEGER counter;QueryPerformanceCounter(&counter);
 value ^= counter.LowPart ^ counter.HighPart;
 __security_cookie=value;
 if(value==0)__security_cookie=0xbb40e64e;
}

