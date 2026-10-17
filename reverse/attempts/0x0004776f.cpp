// ?rva0044776F@Rva0044776F@@QAEXPAXMMMMKH@Z
// partial score=0.187 date=2026-10-17
// ?rva0044776F@Rva0044776F@@QAEXPAXMMMMKH@Z
// partial score=0.414 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?rva0044776F@Rva0044776F@@QAEXPAXMMMMKH@Z
// partial score=0.4 date=2026-10-14
// ?rva0044776F@Rva0044776F@@QAEXPAXMMMMKH@Z
// partial score=0.4 date=2026-10-14
// Bank draft of the clipped textured-quad draw at 0x0044776F (1105B, RET1C).
// Retail-only transcription (the WB twin 0x972E60 is a different revision:
// it has the lazy shader constants and Set2DShader the retail body lacks).
// Structure: render-state switch, texture handle getter + set, the clip
// clamp/interpolate path for m_17C != 0, Add_Tri x2 or Add_Quad, then the
// render-state restore.
// cl: /O1 /arch:SSE /G7 /MD /EHsc

class TextureClass { public: unsigned short m_refCount; void Release_Ref(); };
class Render2DClass;
class Vector2 { public: float X, Y; };
class RectClass { public: Vector2 Min, Max; };
class Rva000470D5Source;
class BFME2ParticleTextureHandle
{
public:
    TextureClass *Ptr;
    BFME2ParticleTextureHandle() : Ptr(0) {}
    BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle &o) : Ptr(o.Ptr) { if (Ptr) ++Ptr->m_refCount; }
    ~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
};
class Rva000470D5Getter
{
public:
    BFME2ParticleTextureHandle rva000470D5(const Rva000470D5Source *);
};
class Rva000456C9
{
public:
    void rva000456C9(const BFME2ParticleTextureHandle *);
};
class Render2DClass
{
public:
    int m_0;					// +0x00
    unsigned char m_pad4[0x48 - 4];
    unsigned char m_48;				// +0x48
    void Set2DShader(int);
    void Add_Tri(const Vector2 &, const Vector2 &, const Vector2 &,
        const Vector2 &, const Vector2 &, const Vector2 &, unsigned long);
    void Add_Quad(const RectClass &, const RectClass &, unsigned long, unsigned long,
        unsigned long, unsigned long);
};

class Rva0044776F
{
public:
    void rva0044776F(void *texture, float x1, float y1, float x2, float y2,
        unsigned long color, int mode);

private:
    unsigned char m_pad0[0x168];
    Render2DClass *m_render;			// +0x168
    int m_16c, m_170, m_174, m_178;		// +0x16c..+0x178
    unsigned char m_17c;			// +0x17c
};

#define BFME_GET_PARTICLE_TEXTURE(src) \
    ((Rva000470D5Getter *)(src))->rva000470D5((const Rva000470D5Source *)(src))

void Rva0044776F::rva0044776F(void *texture, float x1, float y1, float x2, float y2,
    unsigned long color, int mode)
{
    if (texture == 0)
        return;
    m_render->m_48 = 1;
    switch (mode)
    {
    case 0: m_render->m_0 = 0; break;
    case 1: m_render->m_0 = 3; break;
    case 3: m_render->m_0 = 1; break;
    case 4: m_render->m_0 = 4; break;
    case 5: m_render->m_0 = 6; break;
    default: break;
    }

    ((Rva000456C9 *)m_render)->rva000456C9(&BFME_GET_PARTICLE_TEXTURE(texture));

    float *tex = (float *)((char *)texture + 0x14);
    unsigned int texFlag = *(unsigned int *)((char *)texture + 0x30);
    float u0 = tex[0];
    float v0 = tex[1];
    float u1 = tex[2];
    float v1 = tex[3];

    Vector2 p0, p1, p2, p3, p4, p5;
    RectClass screenRect, uvRect;
    if (m_17c == 0)
    {
        screenRect.Min.X = x1;
        screenRect.Min.Y = y1;
        screenRect.Max.X = x2;
        screenRect.Max.Y = y2;
        uvRect.Min.X = u0;
        uvRect.Min.Y = v0;
        uvRect.Max.X = u1;
        uvRect.Max.Y = v1;
        p0.X = x1; p0.Y = y1;
        p1.X = x1; p1.Y = y2;
        p2.X = x2; p2.Y = y1;
        p3.X = u1; p3.Y = v0;
        p4.X = u0; p4.Y = v0;
        p5.X = u1; p5.Y = v1;
        _ReadWriteBarrier();
    }
    else
    {
        if ((float)m_16c >= x2)
            return;
        if ((float)m_170 >= y2)
            return;
        float a, b, c, d;
        float U0, U1, V0, V1;
        _ReadWriteBarrier();
        a = x1 > (float)m_16c ? x1 : (float)m_16c;
        _ReadWriteBarrier();
        b = x2 < (float)m_174 ? x2 : (float)m_174;
        c = y1 > (float)m_170 ? y1 : (float)m_170;
        d = y2 < (float)m_178 ? y2 : (float)m_178;
        {
            float w = x2 - x1;
            float h = v1 - v0;
            float hh = y2 - y1;
            U0 = (a - x1) / w * h + v0;
            U1 = (b - x1) / w * h + v0;
            V0 = u1 - (c - y1) / hh * (u1 - u0);
            V1 = u1 - (d - y1) / hh * (u1 - u0);
            p0.X = a; p0.Y = c;
            p1.X = a; p1.Y = d;
            p2.X = b; p2.Y = c;
            p3.X = V1; p3.Y = U0;
            p4.X = V0; p4.Y = U0;
            p5.X = V1; p5.Y = U1;
        }
        screenRect.Min.X = a;
        screenRect.Min.Y = c;
        screenRect.Max.X = b;
        screenRect.Max.Y = d;
        uvRect.Min.X = U0;
        uvRect.Min.Y = U1;
        uvRect.Max.X = V0;
        uvRect.Max.Y = V1;
    }

    if ((texFlag & 1) != 0)
    {
        m_render->Add_Tri(p0, p1, p2, p3, p4, p5, color);
        m_render->Add_Tri(p2, p3, p4, p5, p0, p1, color);
    }
    else
    {
        m_render->Add_Quad(screenRect, uvRect, color, color, color, color);
    }

    if (mode != 2)
        m_render->m_0 = 2;
}
