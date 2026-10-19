// ?Rva00237D3DCheck@@YAHXZ
// partial score=0.791 date=2026-10-17
// ?Rva00237D3DCheck@@YAHXZ
// partial score=0.628 date=2026-10-15
// ?Rva00237D3DCheck@@YAHXZ
// partial score=0.887 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// Native237D3D..237E1F,226B. Caller238646 consumes int EAX.
// Win32 import identities and the inlined GUID establish executable signature
// verification. Native237E0A..237E1A contains16 internal NOP bytes; result is
// unconditionally1 despite preserving WinVerifyTrust's status in EBX.
struct TrustGuid { unsigned long a; unsigned short b,c; unsigned char d[8]; };
struct TrustFile { unsigned long size; const unsigned short *path; void *file; TrustGuid *subject; };
struct TrustData { unsigned long size; void *policy,*sip; unsigned long ui,revocation,choice; TrustFile *file; unsigned long state; void *stateData; const unsigned short *url; unsigned long flags; };
extern "C" {
void *__cdecl memset(void *,int,unsigned int);
__declspec(dllimport) unsigned short *__stdcall GetCommandLineW();
__declspec(dllimport) unsigned short **__stdcall CommandLineToArgvW(const unsigned short *,int *);
__declspec(dllimport) void *__stdcall LocalFree(void *);
long __stdcall WinVerifyTrust(void *,TrustGuid *,TrustData *);
}
int Rva00237D3DCheck() {
    TrustFile file;
    memset(&file,0,sizeof(file));
    file.size=sizeof(file);
    file.file=0;
    file.subject=0;
    int argc=0;
    unsigned short **argv=CommandLineToArgvW(GetCommandLineW(),&argc);
    file.path=argv[0];
    TrustGuid action={0x00AAC56B,0xCD44,0x11D0,{0x8C,0xC2,0,0xC0,0x4F,0xC2,0x95,0xEE}};
    TrustData data;
    memset(&data,0,sizeof(data));
    data.size=sizeof(data);
    data.policy=0;
    data.sip=0;
    data.ui=2;
    data.revocation=0;
    data.choice=1;
    data.file=&file;
    data.state=0;
    data.stateData=0;
    data.url=0;
    data.flags=0x210;
    WinVerifyTrust(0,&action,&data);
    LocalFree(argv);
    return 1;
}
