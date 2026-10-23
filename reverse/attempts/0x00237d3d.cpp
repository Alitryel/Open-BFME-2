// ?Rva00237D3DCheck@@YAHXZ
// partial score=0.802326 date=2026-10-23
// cl: /O1 /G6 /arch:SSE /DNDEBUG /MD /EHsc
// ?Rva00237D3DCheck@@YAHXZ
// Retail: RVA 0x237D3D, extent 226. This diagnostic emits 219 bytes.
// WinTrust file=16/data=44 and stack GUID are established by retail accesses.
// The unsigned low bit is at most one, so the final predicate is always true.
// Masked bytes match through +0xCC; sixteen NOPs and the return tail differ.
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
    long status=WinVerifyTrust(0,&action,&data); unsigned long u=(unsigned long)status; LocalFree(argv); int r=0; if(((u&1u)<=1u)) goto yes; return r; yes:return r+1;
}
