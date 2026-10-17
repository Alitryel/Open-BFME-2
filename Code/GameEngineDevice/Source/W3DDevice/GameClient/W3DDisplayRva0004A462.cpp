// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc
// ?rva0004A462@W3DDisplay@@QAE_NI@Z @0x0004A462 1425B: one W3DDisplay frame render pass,
// called by the unrowed 0x0004BEF2. Returns false while the script engine or game logic
// freezes time.
// Target evidence (retail bytes): the DX8 thread lock/assert pair brackets the whole body
// with EH state 0; Prepare_Render_New_Frame gates the pre-render (particle, terrain shroud
// and taint, shadow-map and water-reflection updates); Begin_Render receives the clear
// colour at +0x20 and the terrain's float at +0x37E8; the loading-screen branch (global
// byte +0xAF5) draws only the UI windows. The function-local couldRender byte and the
// 0x140-byte BFME2ScopedRenderEvent labels "UpdateShadowMap", "UpdateWaterReflection",
// "RenderViews", "RenderUI" are retail's. Every callee except InGameUI 0x002A4A68 is rowed.
// Donor: Zero Hour W3DDisplay::draw (static couldRender, Begin_Render, loadScreenRender,
// the freezeTime test of isTimeFrozenScript/isTimeFrozenDebug/isGamePaused) supplies the
// structure; BFME 2's split into this helper, its slot numbers and the field offsets are
// read from retail only. Slot and field names are opaque where neither source names them.
#include "../../../../GameEngine/Source/Common/GameLogicObjectLookupView.h"

class Vector3 { public: float X, Y, Z; };
class RTS3DScene;
class CameraClass;
class GlobalData;
class ScriptEngine;
class ParticleSystemManager;
class BaseHeightMapRenderObjClass;
class LivingWorld;
class LivingWorldLogic;
class GameWindowManager;
class BfmeAptWindowManager;
class Mouse;
class GameWindowTransitionsHandler;

void BFME_DX8_Thread_Lock();
bool BFME_DX8_Thread_Assert();
class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

class WW3D
{
public:
	static bool Prepare_Render_New_Frame();
	static bool Begin_Render(bool, bool, const Vector3 &, float);
	static bool End_Render(bool);
};

class BFME2ScopedRenderEvent
{
	char Label[256];
	char Group[64];
public:
	BFME2ScopedRenderEvent(const char *, const char *, unsigned int);
	~BFME2ScopedRenderEvent();
};

void Rva00755C80();
class Rva00068D43 { public: void rva00068D43(); };
class W3DShroud { public: void rva00073628(void *); };
class W3DTaint { public: void render(CameraClass *); };
class W3DShadowMapManager { public: void UpdateShadowMap(RTS3DScene *); };
class WaterRenderObjClass { public: bool IsReflectionVisible(void *); };
class Rva0007F92AHost { public: void rva0007F92A(int, int); };
class Rva0007DA23ResourceManager { public: void rva0007C18E(); void rva0007B6F3(); };
class Rva000B3FD0 { public: void rva000B3FD0(); };
class Rva0081D520Owner { public: void broadcast(int, float, float, float, float); };
class Rva00044018 { public: void rva00044018(unsigned int); };
class BfmeSelectionState { public: bool isSelectionLocked() const; };
void bfmeGoKA();
class Rva00203B08 { public: bool rva0020424FF(); };
class Rva00203ACEByteField { public: unsigned char get() const; };
class InGameUI { public: void rva002A4A68(); };

extern GameLogic *TheGameLogic;
extern GlobalData *TheWritableGlobalData;
extern ScriptEngine *TheScriptEngine;
extern ParticleSystemManager *TheParticleSystemManager;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern Rva0007DA23ResourceManager *Rva00DE1FF8Manager;
extern void *W3DGCData00DE2000;
extern LivingWorld *TheLivingWorld;
extern GameWindowManager *TheWindowManager;
extern InGameUI *TheInGameUI;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern Mouse *TheMouse;
extern LivingWorldLogic *TheLivingWorldLogic;
extern GameWindowTransitionsHandler *TheTransitionHandler;

// Display's vtable as this body calls it (0x194 bytes, slots by offset).
class Display
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void v020();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual unsigned int getWidth();
	virtual unsigned int getHeight();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual unsigned char *getView();
	virtual void v094();
	virtual void drawViews();
	virtual void v09c();
	virtual void sA0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void v0d4();
	virtual void v0d8();
	virtual void v0dc();
	virtual void v0e0();
	virtual void v0e4();
	virtual void v0e8();
	virtual void v0ec();
	virtual void v0f0();
	virtual void v0f4();
	virtual void v0f8();
	virtual void v0fc();
	virtual void v100();
	virtual void s104(int);
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11c();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12c();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13c();
	virtual void v140();
	virtual void v144();
	virtual void v148();
	virtual void v14c();
	virtual void v150();
	virtual void v154();
	virtual void v158();
	virtual void v15c();
	virtual void v160();
	virtual void v164();
	virtual void v168();
	virtual void v16c();
	virtual void v170();
	virtual void v174();
	virtual void v178();
	virtual void v17c();
	virtual void v180();
	virtual void v184();
	virtual void v188();
	virtual void v18c();
	virtual void s190();
	void DrawStaticImage(int, int);
};

// The sub-view at W3DDisplay +0x38.
class W3DDisplaySubView
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual int s20();
	virtual void v024();
	virtual void v028();
	virtual void v02c();
	virtual void v030();
	virtual void v034();
	virtual void v038();
	virtual int s3c(float, float, float, float, int);
};

// The common slots the manager globals are called through.
class Rva0004A462SystemView
{
public:
	virtual void v000();
	virtual void v004();
	virtual void v008();
	virtual void v00c();
	virtual void v010();
	virtual void v014();
	virtual void v018();
	virtual void v01c();
	virtual void s20();
	virtual void v024();
	virtual void s28();
	virtual void v02c();
	virtual void s30();
	virtual void v034();
	virtual void v038();
	virtual void v03c();
	virtual void v040();
	virtual void v044();
	virtual void v048();
	virtual void v04c();
	virtual void v050();
	virtual void v054();
	virtual void v058();
	virtual void v05c();
	virtual void v060();
	virtual void v064();
	virtual void v068();
	virtual void v06c();
	virtual void v070();
	virtual void v074();
	virtual void v078();
	virtual void v07c();
	virtual void v080();
	virtual void v084();
	virtual void v088();
	virtual void v08c();
	virtual void v090();
	virtual void v094();
	virtual void v098();
	virtual void v09c();
	virtual void v0a0();
	virtual void v0a4();
	virtual void v0a8();
	virtual void v0ac();
	virtual void v0b0();
	virtual void v0b4();
	virtual void v0b8();
	virtual void v0bc();
	virtual void v0c0();
	virtual void v0c4();
	virtual void v0c8();
	virtual void v0cc();
	virtual void v0d0();
	virtual void v0d4();
	virtual void v0d8();
	virtual void v0dc();
	virtual void v0e0();
	virtual void v0e4();
	virtual void v0e8();
	virtual void v0ec();
	virtual void v0f0();
	virtual void v0f4();
	virtual void v0f8();
	virtual void v0fc();
	virtual void v100();
	virtual void v104();
	virtual void v108();
	virtual void v10c();
	virtual void v110();
	virtual void v114();
	virtual void v118();
	virtual void v11c();
	virtual void v120();
	virtual void v124();
	virtual void v128();
	virtual void v12c();
	virtual void v130();
	virtual void v134();
	virtual void v138();
	virtual void v13c();
	virtual void v140();
	virtual void v144();
	virtual void v148();
	virtual void v14c();
	virtual void v150();
	virtual void v154();
	virtual void s158();
	virtual void v15c();
	virtual void v160();
	virtual void v164();
	virtual void v168();
	virtual void v16c();
	virtual void v170();
	virtual void v174();
	virtual void v178();
	virtual bool s17c();
};

#define SYS(p) ((Rva0004A462SystemView *)(p))
#define TWGD ((unsigned char *)TheWritableGlobalData)
#define TERRAIN ((unsigned char *)TheTerrainRenderObject)
#define LIVINGWORLD ((unsigned char *)TheLivingWorld)
#define WINDOWMODE (*(int *)((char *)TheWindowManager + 0x3c))

class W3DDisplay : public Display
{
public:
	bool rva0004A462(unsigned int now);
	void rva0025D205();
	static RTS3DScene *m_3DScene;
protected:
	void drawCurrentDebugDisplay();
private:
	unsigned char m_pad4[0x20 - 0x4];
	Vector3 m_20;                   // +0x20, Begin_Render clear colour
	unsigned char m_pad2c[0x30 - 0x2c];
	void *m_30;                     // +0x30, debug display
	unsigned char m_pad34[4];
	W3DDisplaySubView *m_38;        // +0x38
	unsigned char m_pad3c[0xd4 - 0x3c];
	float m_d4;                     // +0xd4
	unsigned char m_padD8[0xfc - 0xd8];
	float m_fc, m_100, m_104, m_108;
	unsigned char m_pad10c[0x140 - 0x10c];
	unsigned char m_140;
	unsigned char m_141;
};

bool W3DDisplay::rva0004A462(unsigned int now)
{
    BFMEDX8DeviceLock lock;
    static bool couldRender = true;
    if (WW3D::Prepare_Render_New_Frame())
    {
        if (!TheGameLogic->getFlag125())
        {
            sA0();
            Rva00755C80();
        }
        SYS(TheParticleSystemManager)->s28();
        if (TheTerrainRenderObject != 0)
        {
            ((Rva00068D43 *)TheTerrainRenderObject)->rva00068D43();
            if (TheTerrainRenderObject != 0 && *(void **)(TERRAIN + 0x37c0) != 0)
            {
                unsigned char *view = getView();
                if (*(void **)(TERRAIN + 0x3878) != 0)
                    ((W3DShroud *)*(void **)(TERRAIN + 0x3878))->rva00073628(*(void **)(view + 0x104));
                if (*(void **)(TERRAIN + 0x387c) != 0)
                    ((W3DTaint *)*(void **)(TERRAIN + 0x387c))->render((CameraClass *)*(void **)(view + 0x104));
            }
        }
        if (TheGameLogic == 0 || !TheGameLogic->m_6d)
        {
            if (Rva00DE1FF8Manager != 0 && TWGD[0x62] != 0)
            {
                BFME2ScopedRenderEvent event("UpdateShadowMap", "Frame", 0);
                ((W3DShadowMapManager *)Rva00DE1FF8Manager)->UpdateShadowMap(m_3DScene);
            }
            unsigned char *view = getView();
            if (W3DGCData00DE2000 != 0 && view != 0 &&
                ((WaterRenderObjClass *)W3DGCData00DE2000)->IsReflectionVisible(*(void **)(view + 0x104)))
            {
                BFME2ScopedRenderEvent event("UpdateWaterReflection", "Frame", 0);
                ((Rva0007F92AHost *)W3DGCData00DE2000)->rva0007F92A((int)m_3DScene, (int)*(void **)(view + 0x104));
            }
        }
        if (TWGD[0xd36] == 0 && TWGD[0xb6f] == 0 &&
            WW3D::Begin_Render(true, true, m_20, *(float *)(TERRAIN + 0x37e8)))
        {
            if (TWGD[0xaf5] == 1)
            {
                WINDOWMODE = 1;
                SYS(TheInGameUI)->s30();
                SYS(g_bfmeAptWindowManager)->s30();
                WINDOWMODE = -1;
                if (TheMouse != 0)
                    SYS(TheMouse)->s30();
                WW3D::End_Render(true);
                return true;
            }
            *(int *)((char *)m_3DScene + 0x7ec) = 0;
            couldRender = 1;
            bool cameraValid = m_d4 > 0.0f;
            if (TheLivingWorld != 0 && LIVINGWORLD[0x18] != 0 && LIVINGWORLD[0x19] == 0)
            {
                SYS(TheLivingWorld)->s20();
                if (*(int *)(LIVINGWORLD + 0x14) != 2)
                {
                    WINDOWMODE = 1;
                    SYS(TheInGameUI)->s30();
                    if (!cameraValid)
                        SYS(TheInGameUI)->s158();
                    SYS(g_bfmeAptWindowManager)->s30();
                    WINDOWMODE = 0;
                    SYS(TheInGameUI)->s30();
                    WINDOWMODE = -1;
                }
            }
            else
            {
                {
                    BFME2ScopedRenderEvent event("RenderViews", "Frame", 0);
                    if (Rva00DE1FF8Manager != 0 && TWGD[0x62] != 0)
                        Rva00DE1FF8Manager->rva0007C18E();
                    drawViews();
                    if (Rva00DE1FF8Manager != 0 && TWGD[0x62] != 0)
                        Rva00DE1FF8Manager->rva0007B6F3();
                }
                DrawStaticImage(0, 2);
                DrawStaticImage(1, 2);
                DrawStaticImage(2, 2);
                if (m_38 == 0)
                    rva0025D205();
                {
                    BFME2ScopedRenderEvent event("RenderUI", "Frame", 0);
                    WINDOWMODE = 1;
                    SYS(TheInGameUI)->s30();
                    if (!cameraValid)
                        SYS(TheInGameUI)->s158();
                    SYS(g_bfmeAptWindowManager)->s30();
                    WINDOWMODE = 0;
                    SYS(TheInGameUI)->s30();
                    WINDOWMODE = -1;
                }
            }
            TheInGameUI->rva002A4A68();
            if (TheMouse != 0)
                SYS(TheMouse)->s30();
            if (m_38 != 0)
            {
                DrawStaticImage(0, 1);
                DrawStaticImage(1, 1);
                s104(m_38->s3c(m_fc, m_100, m_104, m_108, -1));
                DrawStaticImage(2, 1);
                rva0025D205();
                ((Rva000B3FD0 *)this)->rva000B3FD0();
                Rva0081D520Owner *node = *(Rva0081D520Owner **)(*(unsigned char **)((unsigned char *)m_38 + 8) + 0x18);
                if (node != 0)
                {
                    node->broadcast(m_38->s20(), 0.0f, 0.0f, (float)getWidth(), (float)getHeight());
                }
            }
            ((Rva00044018 *)this)->rva00044018(now);
            if (cameraValid)
                SYS(TheInGameUI)->s158();
            if (!SYS(TheInGameUI)->s17c() &&
                (((BfmeSelectionState *)TheLivingWorldLogic)->isSelectionLocked() || TheGameLogic->rva0042219()) &&
                m_140 != 0)
            {
                s190();
                bfmeGoKA();
            }
            if (m_141 == 0)
                SYS(TheTransitionHandler)->s30();
            if (m_30 != 0)
                drawCurrentDebugDisplay();
            WW3D::End_Render(true);
        }
        else
        {
            if (couldRender != 0)
                couldRender = 0;
        }
    }
    if (((Rva00203B08 *)TheScriptEngine)->rva0020424FF() || ((Rva00203ACEByteField *)TheScriptEngine)->get() ||
        TheGameLogic->isGamePaused())
        return false;
    return true;
}
