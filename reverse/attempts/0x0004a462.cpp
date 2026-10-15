// ?rva0004A462@W3DDisplay@@QAE_NI@Z
// partial score=0.736 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva0004A462@W3DDisplay@@QAE_NI@Z
// partial score=0.6 date=2026-10-14
// ?rva0004A462@Rva0004A462@@QAE_NI@Z
// partial score=0.6 date=2026-10-14
// Bank draft of the W3DDisplay render-frame orchestrator at 0x0004A462
// (1425B, RET4 bool). Decoded from the retail body: DX8 thread lock,
// Prepare_Render_New_Frame, shroud/taint/shadow-map/water-reflection passes,
// the Begin_Render/RenderViews/RenderUI/End_Render sequence with the scoped
// render events, the camera/region broadcast block and the paused/selection
// tail. Virtual calls keep their retail slot offsets through the vtable.
// cl: /O1 /arch:SSE /G7 /MD /EHsc

struct Vector3 { float X, Y, Z; };

class RTS3DScene;
class CameraClass;

void BFME_DX8_Thread_Lock();
void BFME_DX8_Thread_Assert();

class WW3D
{
public:
    static bool Prepare_Render_New_Frame();
    static bool rva00118170(bool, bool, const Vector3 &, float);
    static bool End_Render(bool);
};

void Rva00755C80();
class Rva00068D43 { public: void rva00068D43(); };
extern Rva00068D43 *g_rva00DE1EACOwner;
class W3DShroud { public: void rva00073628(void *); };
class W3DTaint { public: void render(CameraClass *); };
class BFME2ScopedRenderEvent
{
public:
    BFME2ScopedRenderEvent(const char *, const char *, unsigned int);
    ~BFME2ScopedRenderEvent();
};
class W3DShadowMapManager { public: void UpdateShadowMap(RTS3DScene *); };
class WaterRenderObjClass { public: bool IsReflectionVisible(void *); };
class Rva0007F92AHost { public: void rva0007F92A(int, int); };
class Rva0007DA23ResourceManager
{
public:
    void rva0007C18E();
    void rva0007B6F3();
};
class Display { public: void DrawStaticImage(int, int); };
class Region2D { public: ~Region2D(); };
class Rva0081D520Owner { public: void broadcast(int, float, float, float, float); };
class Rva00044018 { public: void rva00044018(unsigned int); };
class BfmeSelectionState { public: bool isSelectionLocked() const; };
class GameLogic
{
public:
    bool rva0042219();
    unsigned char isGamePaused();
};
void bfmeGoKA();
class Rva00203B08 { public: bool rva0020424FF(); };
class Rva00203ACEByteField { public: unsigned char get() const; };

class Rva002A4A68Callee
{
public:
    void rva002A4A68();
};

// Unrowed data cells (extern-only placeholders; the closers own their names).
extern unsigned char *g_rva00DFE78C;
extern void *g_rva00DFDD04;
extern unsigned char *g_rva00DFE758;
extern unsigned char *g_rva00DE1EAC;
extern void *g_rva00DE1FF8;
extern void *g_rva00DE2000;
extern void *g_rva00DE1B34;
extern unsigned char *g_rva00DFEF18;
extern void *g_rva00DFEF1C;
extern void *g_rva00DFEDF0;
extern void *g_rva00DFE4CC;
extern void *g_rva00DFDCA0;
extern void *g_rva00DFEF10;
extern void *g_rva00DFE16C;
extern unsigned char g_rva00DB3C00;
extern void *g_rva00DFDC14;

class W3DDisplay : public Display
{
public:
    bool rva0004A462(unsigned int arg);
    void rva0025D205();
protected:
    void drawCurrentDebugDisplay();
private:
    unsigned char m_pad0[0x20];
    Vector3 m_20;				// +0x20
    unsigned char m_pad2c[0x30 - 0x2c];
    void *m_30;					// +0x30
    void *m_38;					// +0x38
    unsigned char m_pad3c[0xd4 - 0x3c];
    float m_d4;					// +0xd4
    unsigned char m_padD8[0xfc - 0xd8];
    float m_fc, m_100, m_104, m_108;		// +0xfc..+0x108
    unsigned char m_pad10c[0x140 - 0x10c];
    unsigned char m_140;			// +0x140
    unsigned char m_141;			// +0x141
};

#define VCALL0(obj, off) ((void (__fastcall *)(void *))((*(void ***)(obj))[(off) / 4]))(obj)
#define VCALL_R(obj, off) ((void *(__fastcall *)(void *))((*(void ***)(obj))[(off) / 4]))(obj)

// Camera view: slots 0x3c/0x40/0x44 are reachable only through an ordered
// vtable view (the 0x3c slot takes the four floats plus the int).
class Rva0004A462CameraView
{
public:
    virtual void c0(); virtual void c1(); virtual void c2(); virtual void c3();
    virtual void c4(); virtual void c5(); virtual void c6(); virtual void c7();
    virtual void c8(); virtual void c9(); virtual void c10(); virtual void c11();
    virtual void c12(); virtual void c13(); virtual void c14();
    virtual void *c15(float, float, float, float, int);
    virtual int c16();
    virtual int c17();
    virtual void c18();
};

bool W3DDisplay::rva0004A462(unsigned int arg)
{
    bool result = false;
    BFME_DX8_Thread_Lock();
    if (WW3D::Prepare_Render_New_Frame())
    {
        if (g_rva00DFE78C == 0 || g_rva00DFE78C[0x125] == 0)
        {
            VCALL0(this, 0xa0);
            Rva00755C80();
        }
        VCALL0(g_rva00DFDD04, 0x28);
        if (g_rva00DE1EAC != 0)
        {
            g_rva00DE1EACOwner->rva00068D43();
            if (g_rva00DE1EAC != 0 && *(void **)(g_rva00DE1EAC + 0x37c0) != 0)
            {
                unsigned char *cam = (unsigned char *)VCALL_R(this, 0x90);
                if (*(void **)(g_rva00DE1EAC + 0x3878) != 0)
                    ((W3DShroud *)*(void **)(g_rva00DE1EAC + 0x3878))->rva00073628(*(void **)(cam + 0x104));
                if (*(void **)(g_rva00DE1EAC + 0x387c) != 0)
                    ((W3DTaint *)*(void **)(g_rva00DE1EAC + 0x387c))->render((CameraClass *)*(void **)(cam + 0x104));
            }
        }
        if (g_rva00DFE78C == 0 || g_rva00DFE78C[0x6d] == 0)
        {
            if (g_rva00DE1FF8 != 0 && g_rva00DFE758[0x62] != 0)
            {
                BFME2ScopedRenderEvent event("UpdateShadowMap", "Frame", 0);
                ((W3DShadowMapManager *)g_rva00DE1FF8)->UpdateShadowMap((RTS3DScene *)g_rva00DE1B34);
            }
            unsigned char *cam = (unsigned char *)VCALL_R(this, 0x90);
            if (g_rva00DE2000 != 0 && cam != 0 &&
                ((WaterRenderObjClass *)g_rva00DE2000)->IsReflectionVisible(*(void **)(cam + 0x104)))
            {
                BFME2ScopedRenderEvent event("UpdateWaterReflection", "Frame", 0);
                ((Rva0007F92AHost *)g_rva00DE2000)->rva0007F92A(
                    (int)g_rva00DE1B34, (int)*(void **)(cam + 0x104));
            }
        }
        if (g_rva00DFE758[0xd36] == 0 && g_rva00DFE758[0xb6f] == 0)
        {
            Vector3 vec;
            vec.X = *(float *)(g_rva00DE1EAC + 0x37e8);
            if (WW3D::rva00118170(true, true, vec, *(float *)(g_rva00DE1EAC + 0x37e8)))
            {
                if (g_rva00DFE758[0xaf5] == 1)
                {
                    *(int *)((char *)g_rva00DFEF1C + 0x3c) = 1;
                    VCALL0(g_rva00DFEDF0, 0x30);
                    VCALL0(g_rva00DFE4CC, 0x30);
                    *(int *)((char *)g_rva00DFEF1C + 0x3c) = -1;
                    if (g_rva00DFDCA0 != 0)
                        VCALL0(g_rva00DFDCA0, 0x30);
                    WW3D::End_Render(true);
                }
                else
                {
                    *(int *)((char *)g_rva00DE1B34 + 0x7ec) = 0;
                    g_rva00DB3C00 = 1;
                    bool cameraValid = (m_d4 > 0.0f);
                    if (g_rva00DFEF18 != 0 && g_rva00DFEF18[0x18] == 0 && g_rva00DFEF18[0x19] == 0)
                    {
                        VCALL0(g_rva00DFEF18, 0x20);
                        if (*(int *)(g_rva00DFEF18 + 0x14) != 2)
                        {
                            *(int *)((char *)g_rva00DFEF1C + 0x3c) = 1;
                            VCALL0(g_rva00DFEDF0, 0x30);
                            if (!cameraValid)
                                VCALL0(g_rva00DFEDF0, 0x158);
                            VCALL0(g_rva00DFE4CC, 0x30);
                            *(int *)((char *)g_rva00DFEF1C + 0x3c) = 0;
                            VCALL0(g_rva00DFEDF0, 0x30);
                            *(int *)((char *)g_rva00DFEF1C + 0x3c) = -1;
                        }
                    }
                    else
                    {
                        {
                            BFME2ScopedRenderEvent event("RenderViews", "Frame", 0);
                            if (g_rva00DE1FF8 != 0 && g_rva00DFE758[0x62] != 0)
                                ((Rva0007DA23ResourceManager *)g_rva00DE1FF8)->rva0007C18E();
                            VCALL0(this, 0x98);
                            if (g_rva00DE1FF8 != 0 && g_rva00DFE758[0x62] != 0)
                                ((Rva0007DA23ResourceManager *)g_rva00DE1FF8)->rva0007B6F3();
                        }
                        ((Display *)this)->DrawStaticImage(0, 2);
                        ((Display *)this)->DrawStaticImage(1, 2);
                        ((Display *)this)->DrawStaticImage(2, 2);
                        if (m_38 == 0)
                            ((W3DDisplay *)this)->rva0025D205();
                        {
                            BFME2ScopedRenderEvent event("RenderUI", "Frame", 0);
                            *(int *)((char *)g_rva00DFEF1C + 0x3c) = 1;
                            VCALL0(g_rva00DFEDF0, 0x30);
                            if (!cameraValid)
                                VCALL0(g_rva00DFEDF0, 0x158);
                            VCALL0(g_rva00DFE4CC, 0x30);
                            *(int *)((char *)g_rva00DFEF1C + 0x3c) = 0;
                            VCALL0(g_rva00DFEDF0, 0x30);
                            *(int *)((char *)g_rva00DFEF1C + 0x3c) = -1;
                        }
                    }
                    ((Rva002A4A68Callee *)g_rva00DFEDF0)->rva002A4A68();
                    if (g_rva00DFDCA0 != 0)
                        VCALL0(g_rva00DFDCA0, 0x30);
                    if (m_38 != 0)
                    {
                        ((Display *)this)->DrawStaticImage(0, 1);
                        ((Display *)this)->DrawStaticImage(1, 1);
                        Rva0004A462CameraView *camera = (Rva0004A462CameraView *)m_38;
                        camera->c15(m_fc, m_100, m_104, m_108, -1);
                        ((Display *)this)->DrawStaticImage(2, 1);
                        ((W3DDisplay *)this)->rva0025D205();
                        ((Region2D *)this)->~Region2D();
                        unsigned char *list = *(unsigned char **)((char *)m_38 + 8);
                        _ReadWriteBarrier();
                        void *node = *(void **)(list + 0x18);
                        if (node != 0)
                        {
                            Rva0004A462CameraView *scene = (Rva0004A462CameraView *)m_38;
                            int slot44 = scene->c17();
                            int slot40 = scene->c16();
                            int slot20 = (int)VCALL_R(scene, 0x20);
                            ((Rva0081D520Owner *)node)->broadcast(slot20, (float)slot40, 0.0f, 0.0f, (float)slot44);
                        }
                        ((Rva00044018 *)this)->rva00044018(arg);
                        if (cameraValid)
                            VCALL0(g_rva00DFEDF0, 0x158);
                        if (!VCALL_R(this, 0x17c))
                        {
                            if (((BfmeSelectionState *)g_rva00DFEF10)->isSelectionLocked() ||
                                ((GameLogic *)g_rva00DFE78C)->rva0042219())
                            {
                                if (m_140 != 0)
                                {
                                    VCALL0(this, 0x190);
                                    bfmeGoKA();
                                }
                            }
                        }
                        if (m_141 == 0)
                            VCALL0(g_rva00DFDC14, 0x30);
                        if (m_30 != 0)
                            ((W3DDisplay *)this)->drawCurrentDebugDisplay();
                        WW3D::End_Render(true);
                    }
                }
            }
        }
        else
        {
            if (g_rva00DB3C00 != 0)
                g_rva00DB3C00 = 0;
        }
    }
    if (!((Rva00203B08 *)g_rva00DFE16C)->rva0020424FF() &&
        ((Rva00203ACEByteField *)g_rva00DFE16C)->get() == 0 &&
        ((GameLogic *)g_rva00DFE78C)->isGamePaused() == 0)
        result = true;
    BFME_DX8_Thread_Assert();
    return result;
}
