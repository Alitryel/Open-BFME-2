// ?reinitializeAudioSystem@MilesAudioManager@@QAEXXZ
// partial score=0.417 date=2026-10-17
// cl: /Oy- /Oi- /Ob1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
#include <windows.h>

typedef bool Bool;
typedef __int64 Time64;
extern "C" __declspec(dllimport) Time64 __cdecl _time64(Time64 *);
extern "C" __declspec(dllimport) void __stdcall AIL_set_redist_directory(const char *);
extern "C" __declspec(dllimport) void __stdcall AIL_startup();
extern "C" __declspec(dllimport) int __stdcall AIL_quick_startup(int,int,int,int,int);
extern "C" __declspec(dllimport) int __stdcall AIL_quick_handles(void **,void *,void *);
class GlobalData { public: char unknown[0x99c]; Bool m_audioOn; };
extern GlobalData *TheWritableGlobalData;
struct AudioSettings {
 char unknown[0x54]; Bool m_useDigital; Bool m_useMidi; char pad[2];
 int m_outputRate; int m_outputBits; int m_outputChannels;
};
class OptionPreferences {
public:
 OptionPreferences(); virtual ~OptionPreferences(); Bool getUseEAX3();
private: char body[0x10];
};
class Rva000A8903AudioDevice {
public: Rva000A8903AudioDevice(void *driver);
private: char body[0x5c];
};
class Rva00053D66DeviceRef {
public: void assign(Rva000A8903AudioDevice *device);
private: void *object;
};
void *__cdecl bfmeMake_009CB5F0(void *);

class XferSave {
public:
 XferSave();
 virtual ~XferSave();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void xferSnapshot(void *p);
 void *Open(void *f, int a, int b);
 void Close();
private:
 char body[0x60];
};

class MilesAudioManager {
public:
 virtual void v0();
 virtual void v1();
 virtual void v2();
 virtual void v3();
 virtual void v4();
 virtual void v5();
 virtual void v6();
 virtual void v7();
 virtual void v8();
 virtual void v9();
 virtual void v10();
 virtual void v11();
 virtual void v12();
 virtual void v13();
 virtual void v14();
 virtual void v15();
 virtual void v16();
 virtual void v17();
 virtual void v18();
 virtual void v19();
 virtual void v20();
 virtual void v21();
 virtual void v22();
 virtual void v23();
 virtual void v24();
 virtual void v25();
 virtual void v26();
 virtual void v27();
 virtual void v28();
 virtual void v29();
 virtual void v30();
 virtual void v31();
 virtual void v32();
 virtual void v33();
 virtual void v34();
 virtual void v35();
 virtual void v36();
 virtual void v37();
 virtual void v38();
 virtual void v39();
 virtual void v40();
 virtual void v41();
 virtual void v42();
 virtual void v43();
 virtual void v44();
 virtual void v45();
 virtual void v46();
 virtual void v47();
 virtual void v48();
 virtual void v49();
 virtual void v50();
 virtual void v51();
 virtual void v52();
 virtual void v53();
 virtual void v54();
 virtual void v55();
 virtual void v56();
 void setOn(Bool turnOn,int which);
 virtual void v58();
 virtual void v59();
 virtual void v60();
 virtual void v61();
 virtual void v62();
 virtual void v63();
 virtual void v64();
 virtual void v65();
 virtual void v66();
 virtual void v67();
 virtual void v68();
 virtual void v69();
 virtual void refreshCachedVariables();
 void openDevice();
 void reinitializeAudioSystem();
private:
 void buildProviderList();
 void selectProvider(Bool accelerated);
 void initSamplePools();
protected:
 void initDelayFilter();
public:
 char prefix[0xc];
 int m_snapshotRef;
 char pad10[0x9cc-0x10];
 unsigned m_providerCount;
 unsigned m_selectedProvider;
 char pad9d4[8];
 void *m_digitalHandle;
 char pad9e0[0xb90-0x9e0];
 Rva00053D66DeviceRef m_device;
 char padb94[0xc00-0xb94];
 unsigned char m_reinitLock;
};

void MilesAudioManager::reinitializeAudioSystem()
{
 unsigned char *lockPtr = (unsigned char*)((char*)this + 0xc00);
 unsigned char saved = *lockPtr;
 void *f;
 f = bfmeMake_009CB5F0((void*)(volatile unsigned char*)lockPtr);
 *lockPtr = 1;
 if (f != 0) {
  XferSave xfer;
  XferSave &rXfer = xfer;
  rXfer.Open(f, 0, 0);
  rXfer.xferSnapshot(this ? (void*)((char*)this + 0xc) : (void*)0);
  rXfer.Close();
  m_reinitLock = saved;
  return;
 }
 m_reinitLock = saved;
}
