// ?rva000E2FBD@FlatHeightMapRenderObjClass@@QAEXAAVRenderInfoClass@@@Z
// partial score=0.43 date=2026-10-14
// ?rva000E2FBD@FlatHeightMapRenderObjClass@@QAEXAAVRenderInfoClass@@@Z
// partial score=0.43 date=2026-10-14
// Bank draft of the BFME2 terrain-system render coordinator at 0x004E2FBD
// (2768B, RET4). Decoded from the retail body: DoTerrainSystems scope, the
// terrain texture slots, RenderTerrain/RenderRoads/RenderFloors/RenderScorches/
// RenderTreeShadows/RenderTerrainParticles/RenderBridges/RenderTerrainTracks/
// RenderWaypoints/RenderOrders/RenderBibs/RenderProps scopes, the light
// environment build and the 0xDEE7C4 terrain matrix stores.
// cl: /O1 /arch:SSE /G7 /MD /EHsc
#include <new>

class RenderInfoClass;
class TextureBaseClass { public: void Release_Ref(); };
class LightClass
{
public:
    enum LightType { LT_DEFAULT = 0, LT_DIRECTIONAL = 1 };
    LightClass(LightType);
    int m_ref;
};
class LightEnvironmentClass
{
public:
    LightEnvironmentClass();
    void Add_Light(const LightClass &);
};
class BFME2ScopedRenderEvent
{
public:
    BFME2ScopedRenderEvent(const char *, const char *, unsigned int);
    ~BFME2ScopedRenderEvent();
};
struct BFME2TextureRef { void *Ptr; };
void BFME2Set_Texture(unsigned int slot, const BFME2TextureRef &ref);
void Rva000685E2Reset();
void Rva0004CB5FSet(int);

class Rva000D79CBCallee
{
public:
    void rva000D79CB(RenderInfoClass &, int, int, int, int, int, void *);
};
class Rva000DF776Callee
{
public:
    void rva000DF776(RenderInfoClass &, int);
};
class DX8Wrapper { public: static void Apply_Render_State_Changes(); };
void DX8_Assert();
class W3DWaypointBuffer { public: void drawWaypoints(RenderInfoClass &); };
class W3DBibBuffer { public: void renderBibs(); };
class W3DPropBuffer { public: void drawProps(RenderInfoClass &); };
class TerrainTracksRenderObjClassSystem { public: void flush(); };
class BaseHeightMapRenderObjClass { public: void drawScorches(); };
class Rva00069DB1 { public: void draw(); };
class Rva000E0856Callee { public: void rva000E0856(RenderInfoClass &); };
class Rva000E5AADCallee { public: void rva000E5AAD(RenderInfoClass &); };
class Rva00044018;

// Unrowed data cells (extern-only placeholders; the closers own their names).
extern unsigned char *g_rva00DFE758;
extern unsigned char g_rva00DEC3D8;
extern unsigned char g_rva00DFE7A8;
extern unsigned char g_rva00DEC404;
extern unsigned char g_rva00DEDA05;
extern unsigned char g_rva00DB621C;
extern unsigned char g_rva00DEC4F4;
extern unsigned char g_rva00DEC4F5;
extern void *g_rva00DEE5DC;
extern void *g_rva00DEDA34;
extern int g_rva00DEDA98;
extern void *g_rva00DFE1E4;
extern void *g_rva00DE2014;
extern float g_rva00DEE7C4[16];

class FlatHeightMapRenderObjClass
{
public:
    void renderTerrain(RenderInfoClass &, int *, int *, int *, int *);
    void rva000E2FBD(RenderInfoClass &info);

private:
    unsigned char m_pad18[0x18];
    float m_18, m_1c, m_20, m_24, m_28, m_2c, m_30, m_34;
    float m_38, m_3c, m_40, m_44;		// +0x38..+0x47
    unsigned char m_pad48[0x78 - 0x48];
    unsigned char *m_78;			// +0x78
    unsigned char m_pad7c[0x37c0 - 0x7c];
    unsigned char *m_37c0;			// +0x37c0
    unsigned char m_pad37c4[0x3850 - 0x37c4];
    unsigned char *m_3850, *m_3854, *m_3858, *m_385c, *m_3860, *m_3864, *m_3868, *m_386c, *m_3870;
    unsigned char m_pad3874[0x3880 - 0x3874];
    unsigned char m_3880;			// +0x3880
    unsigned char m_pad3881[0x3938 - 0x3881];
    void *m_3938;				// +0x3938
};

#define BFME_SET_TEXTURE(slot) do { \
    void *handle = 0; \
    BFME2Set_Texture(slot, *(const BFME2TextureRef *)&handle); \
    if (handle != 0) \
        ((TextureBaseClass *)handle)->Release_Ref(); } while (0)

void FlatHeightMapRenderObjClass::rva000E2FBD(RenderInfoClass &info)
{
    if (m_3880 != 0)
        return;

    BFME2ScopedRenderEvent doTerrainSystems("DoTerrainSystems", "Frame", 0);
    {
        void *p = ((void *(__fastcall *)(void *))((*(void ***)this)[0x190 / 4]))(this);
        if (p != 0)
            return;
        if (g_rva00DEC3D8 != 0)
            return;
        if (m_3850 != 0)
            m_3850[0x44555] = 1;
        if (m_3854 != 0)
            m_3854[0x4fb6d] = 1;

        if (g_rva00DFE7A8 != 0)
        {
            BFME_SET_TEXTURE(0);
            BFME_SET_TEXTURE(1);
            Rva000685E2Reset();
            g_rva00DB621C = 1;
            if (g_rva00DEE5DC != 0)
            {
                unsigned char *p2 = (unsigned char *)g_rva00DEE5DC;
                p2 += 4;
                if (--*(int *)p2 == 0)
                    (*(void (__fastcall **)(void *))g_rva00DEE5DC)(g_rva00DEE5DC);
            }
            g_rva00DEC4F4 |= 0x4000;
            g_rva00DEE5DC = 0;
            if (m_3858 != 0)
                ((W3DPropBuffer *)m_3858)->drawProps(info);
            BFME_SET_TEXTURE(0);
            BFME_SET_TEXTURE(1);
            Rva000685E2Reset();
            g_rva00DB621C = 1;
            if (g_rva00DEE5DC != 0)
            {
                unsigned char *p2 = (unsigned char *)g_rva00DEE5DC;
                p2 += 4;
                if (--*(int *)p2 == 0)
                    (*(void (__fastcall **)(void *))g_rva00DEE5DC)(g_rva00DEE5DC);
            }
            g_rva00DEC4F4 |= 0x4000;
            g_rva00DEE5DC = 0;
            return;
        }

        LightEnvironmentClass lightEnv;
        if (g_rva00DFE758[0x49] != 0 && *(int *)(g_rva00DFE758 + 0x988) > 0)
        {
            LightClass *light = (LightClass *)operator new(0x120);
            if (light != 0)
                light = new (light) LightClass(LightClass::LT_DIRECTIONAL);
            float dx = *(float *)(g_rva00DFE758 + 0x8fc);
            float dy = *(float *)(g_rva00DFE758 + 0x900);
            float dz = *(float *)(g_rva00DFE758 + 0x904);
            if (((int (__fastcall *)(void *))((*(void ***)this)[0x24c / 4]))(this) < 1)
            {
                dx *= *(float *)(g_rva00DFE758 + 0x944);
                dy *= *(float *)(g_rva00DFE758 + 0x948);
                dz *= *(float *)(g_rva00DFE758 + 0x94c);
            }
            if (g_rva00DFE1E4 != 0 &&
                ((unsigned char (__fastcall *)(void *))((*(void ***)g_rva00DFE1E4)[0x3c / 4]))(g_rva00DFE1E4))
            {
                float f[3];
                ((void (__fastcall *)(void *, float *))((*(void ***)g_rva00DFE1E4)[0x48 / 4]))(g_rva00DFE1E4, f);
                dx = (1.0f - f[0]) * dx;
                ((void (__fastcall *)(void *, float *))((*(void ***)g_rva00DFE1E4)[0x48 / 4]))(g_rva00DFE1E4, f);
                dy = (1.0f - f[1]) * dy;
                ((void (__fastcall *)(void *, float *))((*(void ***)g_rva00DFE1E4)[0x48 / 4]))(g_rva00DFE1E4, f);
                dz = (1.0f - f[2]) * dz;
            }
            *(float *)((char *)light + 0xe0) = dx;
            *(float *)((char *)light + 0xe4) = dy;
            *(float *)((char *)light + 0xe8) = dz;
            float m[12];
            m[0] = 1.0f; m[1] = 0.0f; m[2] = *(float *)(g_rva00DFE758 + 0x920);
            m[3] = 0.0f; m[4] = 0.0f; m[5] = 1.0f;
            m[6] = *(float *)(g_rva00DFE758 + 0x924);
            m[7] = 0.0f; m[8] = 0.0f; m[9] = 0.0f;
            m[10] = *(float *)(g_rva00DFE758 + 0x928);
            m[11] = 0.0f;
            ((void (__fastcall *)(void *, float *))((*(void ***)light)[0x54 / 4]))(light, m);
            lightEnv.Add_Light(*light);
            if (--light->m_ref == 0)
                (*(void (__fastcall **)(void *))light)(light);
        }
        *(LightEnvironmentClass **)((char *)&info + 0x28) = &lightEnv;

        g_rva00DEE7C4[0] = m_18;
        g_rva00DEE7C4[1] = m_28;
        g_rva00DEE7C4[2] = m_38;
        g_rva00DEE7C4[3] = 0.0f;
        g_rva00DEE7C4[4] = m_1c;
        g_rva00DEE7C4[5] = m_2c;
        g_rva00DEE7C4[6] = m_3c;
        g_rva00DEE7C4[7] = 0.0f;
        g_rva00DEE7C4[8] = m_20;
        g_rva00DEE7C4[9] = m_30;
        g_rva00DEE7C4[10] = m_40;
        g_rva00DEE7C4[11] = 0.0f;
        g_rva00DEE7C4[12] = m_24;
        g_rva00DEE7C4[13] = m_34;
        g_rva00DEE7C4[14] = m_44;
        g_rva00DEE7C4[15] = 1.0f;
        {
            unsigned int flags = *(unsigned int *)&g_rva00DEC4F4;
            flags &= 0xfffbffff;
            flags |= 1;
            *(unsigned int *)&g_rva00DEC4F4 = flags;
        }

        int a = *(int *)(m_37c0 + 8);
        int b = *(int *)(m_37c0 + 0xc);
        int c = 0;
        {
            BFME2ScopedRenderEvent ev("RenderTerrain", "Frame", 0);
            int d = 0;
            renderTerrain(info, &d, &a, &b, &c);
        }
        ((void (__fastcall *)(void *, void *))((*(void ***)g_rva00DEDA34)[0x170 / 4]))(g_rva00DEDA34, this);
        g_rva00DEDA98++;
        ((void (__fastcall *)(void *, void *))((*(void ***)g_rva00DEDA34)[0x1ac / 4]))(g_rva00DEDA34, this);
        g_rva00DEDA98++;

        Rva000685E2Reset();
        BFME_SET_TEXTURE(0);
        BFME_SET_TEXTURE(1);
        g_rva00DB621C = 1;

        if (g_rva00DEC404 == 0 && g_rva00DEDA05 == 0)
        {
            if (g_rva00DFE758[0x3e] != 0 && m_78 != 0)
            {
                unsigned char *prop = m_78 + 0x114;
                int propPtr = *(int *)(prop + 8);
                if (m_386c != 0)
                {
                    BFME2ScopedRenderEvent ev("RenderRoads", "Frame", 0);
                    void *iter = 0;
                    ((Rva000D79CBCallee *)m_386c)->rva000D79CB(info,
                        c - *(int *)(m_37c0 + 0x10), a - *(int *)(m_37c0 + 0x10),
                        b - *(int *)(m_37c0 + 0x10), propPtr, 0, 0);
                }
            }
            {
                BFME2ScopedRenderEvent ev("RenderFloors", "Frame", 0);
                ((Rva000E5AADCallee *)m_3860)->rva000E5AAD(info);
            }
            BFME_SET_TEXTURE(0);
            BFME_SET_TEXTURE(1);
            Rva000685E2Reset();
            g_rva00DB621C = 1;
            {
                BFME2ScopedRenderEvent ev("RenderScorches", "Frame", 0);
                ((BaseHeightMapRenderObjClass *)this)->drawScorches();
            }
            {
                BFME2ScopedRenderEvent ev("RenderTreeShadows", "Frame", 0);
                ((Rva00069DB1 *)this)->draw();
            }
            {
                BFME2ScopedRenderEvent ev("RenderTerrainParticles", "Frame", 0);
                Rva0004CB5FSet(0);
            }
        }

        ((Rva000DF776Callee *)m_3870)->rva000DF776(info, 0);
        BFME_SET_TEXTURE(0);
        BFME_SET_TEXTURE(1);
        Rva000685E2Reset();
        g_rva00DB621C = 1;
        DX8Wrapper::Apply_Render_State_Changes();
        if (g_rva00DEC404 == 0)
        {
            if (g_rva00DE2014 != 0)
            {
                BFME2ScopedRenderEvent ev("RenderTerrainTracks", "Frame", 0);
                ((TerrainTracksRenderObjClassSystem *)g_rva00DE2014)->flush();
            }
            DX8Wrapper::Apply_Render_State_Changes();
            if (m_3864 != 0)
            {
                BFME2ScopedRenderEvent ev("RenderWaypoints", "Frame", 0);
                ((W3DWaypointBuffer *)m_3864)->drawWaypoints(info);
                g_rva00DEE7C4[0] = m_18; g_rva00DEE7C4[1] = m_28; g_rva00DEE7C4[2] = m_38; g_rva00DEE7C4[3] = 0.0f;
                g_rva00DEE7C4[4] = m_1c; g_rva00DEE7C4[5] = m_2c; g_rva00DEE7C4[6] = m_3c; g_rva00DEE7C4[7] = 0.0f;
                g_rva00DEE7C4[8] = m_20; g_rva00DEE7C4[9] = m_30; g_rva00DEE7C4[10] = m_40; g_rva00DEE7C4[11] = 0.0f;
                g_rva00DEE7C4[12] = m_24; g_rva00DEE7C4[13] = m_34; g_rva00DEE7C4[14] = m_44; g_rva00DEE7C4[15] = 1.0f;
                {
                    unsigned int flags = *(unsigned int *)&g_rva00DEC4F4;
                    flags &= 0xfffbffff;
                    flags |= 1;
                    *(unsigned int *)&g_rva00DEC4F4 = flags;
                }
                DX8Wrapper::Apply_Render_State_Changes();
            }
            if (m_3868 != 0)
            {
                BFME2ScopedRenderEvent ev("RenderOrders", "Frame", 0);
                ((Rva000E0856Callee *)m_3868)->rva000E0856(info);
            }
            {
                BFME2ScopedRenderEvent ev("RenderBibs", "Frame", 0);
                ((W3DBibBuffer *)m_385c)->renderBibs();
            }
        }

        *(int *)((char *)&info + 0x28) = 0;
        if (m_3858 != 0)
        {
            BFME2ScopedRenderEvent ev("RenderProps", "Frame", 0);
            ((W3DPropBuffer *)m_3858)->drawProps(info);
        }
        BFME_SET_TEXTURE(0);
        BFME_SET_TEXTURE(1);
        Rva000685E2Reset();
        g_rva00DB621C = 1;
        if (g_rva00DEE5DC != 0)
        {
            unsigned char *p2 = (unsigned char *)g_rva00DEE5DC;
            p2 += 4;
            if (--*(int *)p2 == 0)
                (*(void (__fastcall **)(void *))g_rva00DEE5DC)(g_rva00DEE5DC);
        }
        g_rva00DEC4F5 |= 0x40;
        g_rva00DEE5DC = 0;
        DX8_Assert();
    }
}
