// ?draw@W3DDisplay@@UAEXXZ
// partial score=0.99 date=2026-10-20
// ?draw@W3DDisplay@@UAEXXZ
// partial score=0.94 date=2026-10-20
// ?draw@W3DDisplay@@UAEXXZ
// partial score=0.92 date=2026-10-19
// ?draw@W3DDisplay@@UAEXXZ
// partial score=0.91 date=2026-10-17
// ?draw@W3DDisplay@@UAEXXZ
// partial score=0.9237 date=2026-10-14
// ?draw@W3DDisplay@@UAEXXZ
// partial score=0.92 date=2026-10-13
// ?draw@W3DDisplay@@UAEXXZ
// partial score=0.9213 date=2026-10-10
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /ICode/GameEngine/Source/Common
// stlport
// ZH W3DDisplay::draw semantic guide; native 4BEF2..4C3D8.
// BFME2 separates the full render into 4A462 and adds panorama captures.
// Retail repeats while paused; array new/delete and draw slot 12 follow native evidence.
// Resume evidence: reverse/attempt_support/w8-4bef2-20261019.md.
// capturePending and captureIndex are file-static: retail loads the takeScreenShot vptr before dec [capturePending].
// The do-while runs on a keepDrawing flag as WorldBuilder 0x96E810 does; evidence: reverse/attempt_support/w6-4bef2-20261020.md.
void *__cdecl operator new[](unsigned int);
void __cdecl operator delete[](void *) throw();
#include "ascii_string.h"
#include "GameLogicObjectLookupView.h"
#include <windows.h>
#include <mmsystem.h>
#define TWO_PI 6.28318530718f
struct POINT2 { int x,y; }; struct RECT2 { int left,top,right,bottom; };
class W3DView {public:bool updateCameraMovements();};
class FrameClient {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual unsigned getFrame();
char pad[0xC8-4];bool active;};
class TimeView {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual bool isCameraMovementFinished();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual int getTimeMultiplier();
};
struct ScriptVector { void *begin, *end; bool empty() const { return begin == end; } };
class GlobalData {public:
char pad0[0x26];bool useFpsLimit; char pad27[0xAF5-0x27];bool loadScreenRender;
char padAF6[0xBBD-0xAF6];bool fastMode;char padBBE[0xC54-0xBBE];ScriptVector scripts;
char padC5C[0xEA0-0xC5C];int panoramaCount; bool panoramaIndividual; char reservedEA5;bool panoramaMode;bool panoramaLast;float panoramaStep;float panoramaAngle;
};
class Rva00084C05System {public:void update();};
class Rva00203B47Host {public:bool rva00203B47();};
extern GameLogic*TheGameLogic;extern FrameClient*TheGameClient;extern TimeView*TheTacticalView;extern GlobalData*TheWritableGlobalData;
#define TheGlobalData ((const GlobalData*)TheWritableGlobalData)
extern Rva00084C05System*TheTerrainTracksRenderObjClassSystem;class ScriptEngine;extern ScriptEngine*TheScriptEngine;
extern HWND ApplicationHWnd;
extern int g_bfmeDisplayAnimationSyncClock,g_Va00DB3BDC;
static int capturePending,captureIndex;extern int TheW3DFrameLengthInMsec;
void StatDebugDisplay();void Rva00043D69Callback();void Rva00043D96Callback();void Rva00043D3CCallback();
void Rva00079985Clear();
class WW3D {public:static void Sync(unsigned);};
class W3DDisplay {public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void draw();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void slot20();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual W3DView*getFirstView();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void takeScreenShot(const char*);
void updateAverageFPS();void rva00043FB9();protected:void gatherAnimationDebuggingInfo();public:virtual void gatherDebugStats();virtual void gatherNetworkStats();void gatherSkirmishAIStats();bool rva0004A462(unsigned);
private:
void rva00045213(char*,unsigned);void rva00047BC0(char*,unsigned,unsigned,const char*);
public:
char pad04[0x30-4]; void(*debugDisplayCallback)();char pad34[0x115-0x34];bool disabled;
};
// The slice index takes the count by const reference: retail's add eax,0xEA0 / mov ecx,[eax] in that arm is the materialized reference.
// Needs ?gatherDebugStats@W3DDisplay@@UAEXXZ (0x0004826C) resolved, and capturePending co-located with its other writer 0x0004538C (g_00DE1B28).
// Evidence: reverse/attempt_support/w1-4bef2-20261020.md.
inline int panoramaSliceIndex(int i,const int&count){return (i+count/2)%count;}
void W3DDisplay::draw(){
 if(ApplicationHWnd && IsIconic(ApplicationHWnd))return;
 updateAverageFPS();rva00043FB9();
 // compute debug statistics for display later
 if(debugDisplayCallback==StatDebugDisplay)W3DDisplay::gatherDebugStats();
 else if(debugDisplayCallback==Rva00043D69Callback)gatherAnimationDebuggingInfo();
 else if(debugDisplayCallback==Rva00043D96Callback)W3DDisplay::gatherNetworkStats();
 else if(debugDisplayCallback==Rva00043D3CCallback)gatherSkirmishAIStats();
 bool freezeTime=!TheGameClient->active;
 /// @todo: I'm assuming the first view is our main 3D view.
 W3DView*primaryW3DView=getFirstView();
 // hack to let client spin fast in network games but still do effects at the same pace. -MDC
 if((unsigned)g_Va00DB3BDC>TheGameClient->getFrame())g_Va00DB3BDC=TheGameClient->getFrame();
 unsigned delta=TheGameClient->getFrame()-g_Va00DB3BDC;
 if(freezeTime)delta=0;else g_Va00DB3BDC=TheGameClient->getFrame();
 bool fastMode=false;
 if(!TheGameLogic->isGamePaused() && TheGlobalData->fastMode)fastMode=true;
 if(((Rva00203B47Host*)TheScriptEngine)->rva00203B47())fastMode=true;
 if(!freezeTime && fastMode && !TheGameLogic->getFlag125() && TheGameClient->getFrame()%30!=0){
  primaryW3DView->updateCameraMovements();  // Update camera motion effects.
  g_bfmeDisplayAnimationSyncClock+=TheW3DFrameLengthInMsec;WW3D::Sync(g_bfmeDisplayAnimationSyncClock);return;}
 //update state of all the terrain tracks (fade, remove, etc.)
 if(TheGlobalData->loadScreenRender!=true && TheTerrainTracksRenderObjClassSystem)TheTerrainTracksRenderObjClassSystem->update();
 /// @todo Decouple framerate from timestep
 // for now, use constant time steps to avoid animations running independent of framerate
 g_bfmeDisplayAnimationSyncClock+=TheW3DFrameLengthInMsec*delta;WW3D::Sync(g_bfmeDisplayAnimationSyncClock);
 // Fast & Frozen time limits the time to 33 fps.
 int minTime=30;
 static int prevTime=timeGetTime();
 int now=timeGetTime();
 if(TheTacticalView->getTimeMultiplier()>1){
  static int timeMultiplierCounter=1;--timeMultiplierCounter;if(timeMultiplierCounter>1)return;timeMultiplierCounter=TheTacticalView->getTimeMultiplier();
  // limit the framerate, because while fast time is on, the game logic is running as fast as it can.
 }
 else prevTime=now-minTime;		 // do the first frame immediately.
 if(disabled)return;
 bool keepDrawing=false;
 do{
  if(TheGlobalData->loadScreenRender!=true){
   // limit the framerate
   while(TheGlobalData->useFpsLimit && now-prevTime<minTime-1)now=timeGetTime();prevTime=now;}
  if(capturePending>0 && TheGlobalData->panoramaCount!=0){
   TheWritableGlobalData->panoramaMode=true;TheWritableGlobalData->panoramaStep=TWO_PI/TheGlobalData->panoramaCount;
   RECT2 rect;GetClientRect(ApplicationHWnd,(RECT*)&rect);POINT2 point;point.x=rect.left;point.y=rect.top;ClientToScreen(ApplicationHWnd,(POINT*)&point);rect.left=point.x;rect.top=point.y;point.x=rect.right;point.y=rect.bottom;ClientToScreen(ApplicationHWnd,(POINT*)&point);rect.right=point.x;rect.bottom=point.y;
   int width=rect.right-rect.left;int height=rect.bottom-rect.top;
   char*image=0;
   if(!TheGlobalData->panoramaIndividual)image=new char[width*3*height*TheGlobalData->panoramaCount];
   for(int i=0;i<TheGlobalData->panoramaCount;++i){
    TheWritableGlobalData->panoramaAngle=i*-TWO_PI/TheGlobalData->panoramaCount;
    TheWritableGlobalData->panoramaLast=(i==TheGlobalData->panoramaCount-1);
    if(!rva0004A462(now))freezeTime=false;
    if(TheGlobalData->panoramaIndividual){AsciiString name;name.format("sshot_panorama_%.2d_%.4d",i,captureIndex);takeScreenShot(name.str());}
    else rva00045213(image+width*3*panoramaSliceIndex(i,TheGlobalData->panoramaCount),width*3*TheGlobalData->panoramaCount);
   }
   if(!TheGlobalData->panoramaIndividual){rva00047BC0(image,width*TheGlobalData->panoramaCount,height,0);delete[]image;}
   ++captureIndex;--capturePending;TheWritableGlobalData->panoramaMode=false;
  }else if(!rva0004A462(now))break;
  keepDrawing=freezeTime&&!TheTacticalView->isCameraMovementFinished();
  if(keepDrawing&&!TheGameLogic->isGamePaused())keepDrawing=false;
 }while(keepDrawing);
 if(capturePending>0&&TheGlobalData->panoramaCount==0&&TheGlobalData->scripts.empty()){--capturePending;takeScreenShot(0);}
 Rva00079985Clear();
}
