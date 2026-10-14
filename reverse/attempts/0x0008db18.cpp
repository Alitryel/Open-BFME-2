// ?rva0008DB18@W3DView@@QAEXXZ
// partial score=0.9568875281310514 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /I.
// Complete retail 0x0008DB18..0x0008DE1C (772 bytes); WB 0x0099A350.
// BFME-specific W3DView camera control absent from the BFME1 and ZH W3DView donors.
// Retail removes WB's unused turret-aim path. The historical method name is unknown.
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
struct OrbitCoord3D { float x,y,z; };
struct OrbitObjectFields { char beforePosition[0x38]; OrbitCoord3D position; };
class OrbitDisplay {
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
 virtual unsigned int v16();
 virtual unsigned int v17();
};
extern OrbitDisplay *g_Va00DFE9D8;
struct OrbitInput { char pad[0x4f0c]; int x,y; };
extern OrbitInput *g_Va00DFDCA0;
struct OrbitDrawable { char pad[0xb0]; float opacity; };
extern OrbitDrawable *g_Va00DE2078;
extern bool g_Va00DB4580, g_Va00DE201C;
extern float g_Va00DB4540,g_Va00DB4544,g_Va00DB4548;
extern float g_Va00DB454C,g_Va00DB4550,g_Va00DB4560,g_Va00DB4564;
extern float g_Va00DB4568,g_Va00DB456C;
extern float g_Va00DE2044,g_Va00DE2020,g_Va00DE2040;
#define PI 3.14159265359f
#pragma auto_inline(off)
static void normAngle(float &angle) {
 if(angle < -10*PI) angle=0;
 if(angle > 10*PI) angle=0;
 while(angle < -PI) angle+=2*PI;
 while(angle > PI) angle-=2*PI;
}
#pragma auto_inline(on)
class W3DView {
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
 virtual void v28(bool);
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
 virtual void v57();
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
 virtual void v70();
 virtual void v71();
 virtual void v72();
 virtual void v73();
 virtual void v74();
 virtual void v75();
 virtual void v76();
 virtual void v77();
 virtual void v78();
 virtual void v79();
 virtual void v80();
 virtual void v81();
 virtual void v82();
 virtual void v83();
 virtual void v84();
 virtual void v85();
 virtual void v86();
 virtual void v87();
 virtual void v88();
 virtual void v89();
 virtual void v90();
 virtual void v91();
 virtual void v92();
 virtual void v93();
 virtual void v94();
 virtual void v95();
 virtual void v96();
 virtual void v97();
 virtual void v98();
 virtual void v99();
 virtual void v100();
 virtual void v101();
 virtual void v102();
 virtual void v103();
 virtual void v104();
 virtual void v105();
 virtual void v106();
 virtual void v107();
 virtual void v108();
 virtual void v109();
 virtual void v110();
 virtual void v111();
 virtual void v112();
 virtual void v113();
 virtual void v114();
 virtual bool v115();
 virtual void v116();
 virtual ObjectID v117();
 void rva0008DB18();
private:
 void setCameraTransform();
 char beforePosition[0x0c-4];
 OrbitCoord3D position;
 char beforeAngle[0x28-0x18];
 float angle;
 char beforeZoom[0x70-0x2c];
 float zoom;
 char beforeRotateFlag[0x1dc-0x74];
 bool rotateFlag;
 char beforeFlag27d[0x27d-0x1dd];
 bool flag27d;
 char beforeMoveFlag[0x2354-0x27e];
 int moveFlag;
 char beforeMode[0x24a0-0x2358];
 int mode;
};
void W3DView::rva0008DB18() {
 if(v115() && !TheGameLogic->isGamePaused()) {
  if(!g_Va00DB4580) {
   if(!g_Va00DE201C) {
    float margin=g_Va00DFE9D8->v16()*g_Va00DB4540;
    float mouse=(float)g_Va00DFDCA0->x;
    float delta=mouse-margin;
    if(delta>0) {
     delta=mouse-(g_Va00DFE9D8->v16()-margin);
     if(delta<0) delta=0;
    }
    g_Va00DE2044-=delta*g_Va00DB4544;
    g_Va00DE2044-=g_Va00DE2044*g_Va00DB4548;
    float rotation=g_Va00DE2044;
    if(rotation!=0) {
     if(!g_Va00DE201C) { angle+=g_Va00DE2020;g_Va00DE2020=0; }
     angle+=rotation;
     normAngle(angle);
    }
   }
   float top=g_Va00DFE9D8->v17()*g_Va00DB454C;
   float bottom=g_Va00DFE9D8->v17()*g_Va00DB4550;
   float mouse=(float)g_Va00DFDCA0->y;
   float delta=mouse-top;
   if(delta>0) {
    delta=mouse-(g_Va00DFE9D8->v17()-bottom);
    if(delta<0) delta=0;
   }
   if((delta>0 && zoom<g_Va00DB4560) || (delta<0 && zoom>g_Va00DB4564))
    g_Va00DE2040+=delta*g_Va00DB4568;
   g_Va00DE2040-=g_Va00DE2040*g_Va00DB456C;
   if(g_Va00DE2040!=0) zoom+=g_Va00DE2040;
  }
  Object *obj=TheGameLogic->findObjectByID(v117());
  if(obj && !g_Va00DE201C) {
   OrbitObjectFields *fields=(OrbitObjectFields*)obj;
   OrbitCoord3D newPosition={fields->position.x,fields->position.y,0};
   moveFlag=0;
   position=newPosition;
   rotateFlag=false;
   v28(false);
   flag27d=false;
   setCameraTransform();
  }
  if(g_Va00DE2078) { g_Va00DE2078->opacity=1;g_Va00DE2078=0; }
  g_Va00DFE9D8->v16();
  g_Va00DFE9D8->v17();
 } else if(mode==4) setCameraTransform();
}
