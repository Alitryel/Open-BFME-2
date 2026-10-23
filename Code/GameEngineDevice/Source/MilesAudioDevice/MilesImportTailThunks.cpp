// cl: /O2 /Oi-
// Miles import wrappers omitted by the region-/O1 generated thunk batch.
// The named import gate proves each IAT slot. ABI views follow the existing
// MilesAudioManager and Rva0010F42AFinish declarations; no SDK ownership claim.
extern "C" {
__declspec(dllimport) void __stdcall AIL_set_3D_orientation(void*,float,float,float,float,float,float);
__declspec(dllimport) int __stdcall AIL_quick_startup(int,int,int,int,int);
__declspec(dllimport) int __stdcall AIL_stream_info(void*,int*,int*,int*,int*);
void __stdcall ji_00629d92(void*p,float a,float b,float c,float d,float e,float f) { AIL_set_3D_orientation(p,a,b,c,d,e,f); }
int __stdcall ji_00629ea0(int a,int b,int c,int d,int e) { return AIL_quick_startup(a,b,c,d,e); }
int __stdcall ji_00629ef4(void*p,int*a,int*b,int*c,int*d) { return AIL_stream_info(p,a,b,c,d); }
}
