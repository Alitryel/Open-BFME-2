// ?rva0009CD9B@Rva0009C134Host@@QAEXXZ
// partial score=0.0 date=2026-10-17
// ?rva0009CD9B@Rva0009C134Host@@QAEXXZ
// partial score=0.27 date=2026-10-14
// ?rva0009CD9B@Rva0009C134Host@@QAEXXZ
// partial score=0.27 date=2026-10-14
// Bank draft of the LM_SunRays customized-render setup at 0x0009CD9B (1984B).
// Decoded from the retail body: two Create_Render_Obj calls (the host's +0xD4
// and "LM_SunRays" +0x188), the +0x18C/+0x190/+0x194 sub-object bindings via
// rva0009C0EB, the mesh texture assignment, two sun-ray matrix builds with
// sin/cos, the livingworld.txt atof pass into the DE5E00 globals and the
// SegmentedLineClass setup. Unrowed 0x9C18A/0x9B28C keep Rva-named methods.
// cl: /O1 /arch:SSE /G7 /MD /EHsc
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <new>
extern "C" __declspec(dllimport) void *__cdecl fopen(const char *, const char *);
extern "C" __declspec(dllimport) char *__cdecl fgets(char *, int, void *);
extern "C" __declspec(dllimport) double __cdecl atof(const char *);
extern "C" __declspec(dllimport) int __cdecl fclose(void *);
extern "C" __declspec(dllimport) double __cdecl cos(double);
extern "C" __declspec(dllimport) double __cdecl sin(double);
#pragma intrinsic(cos)
#pragma intrinsic(sin)

class Vector3 { public: float X, Y, Z; };

class RenderObjClass;

class Rva0009C134Host;
template<class T> class StringBase
{
    friend class Rva0009C134Host;
private:
    StringBase(const char *);
    ~StringBase();
    void *m_data;
};
typedef StringBase<char> AsciiString;

class TextureClass
{
public:
    virtual void slot0();
    virtual void slot1();
    unsigned short m_refCount;
    unsigned short m_pad06;
    void Release_Ref();
};

template<class T> class RefCountPtr
{
public:
    T *Ptr;
    RefCountPtr() : Ptr(0) {}
    RefCountPtr(const RefCountPtr<T> &o) : Ptr(o.Ptr) { if (Ptr) ++((TextureClass *)Ptr)->m_refCount; }
    ~RefCountPtr() { if (Ptr) ((TextureClass *)Ptr)->Release_Ref(); }
    const RefCountPtr<T> &operator=(const RefCountPtr<T> &o) { Ptr = o.Ptr; return *this; }
    void rva00132FE9(bool release);
};

class MeshModelClass
{
public:
    virtual void Release();
    int m_ref;					// +4
    RefCountPtr<TextureClass> rva0009B266(int, int, int) const;
};

class MeshClass
{
public:
    MeshModelClass *Get_Model();
};

class Rva0009C0EBRef;
class Rva0009C0EB
{
public:
    void rva0009C0EB(Rva0009C0EBRef **out, const AsciiString *name);
};

class ShaderClass { public: int m_value; };

class BFME2ParticleTextureHandle
{
public:
    TextureClass *Ptr;
    BFME2ParticleTextureHandle() : Ptr(0) {}
    BFME2ParticleTextureHandle(const BFME2ParticleTextureHandle &o) : Ptr(o.Ptr) { if (Ptr) ++Ptr->m_refCount; }
    ~BFME2ParticleTextureHandle() { if (Ptr) Ptr->Release_Ref(); }
};

class TextureAsset
{
public:
    static BFME2ParticleTextureHandle Get(const char *, int, int);
};

class SegLineRendererClass
{
public:
    enum TextureMapMode { MAP_NONE = 0, MAP_LINEAR = 1, MAP_PERSPECTIVE = 2 };
};

class SegmentedLineClass
{
public:
    SegmentedLineClass();
    void Set_Texture(const RefCountPtr<TextureClass> &texture);
    void Set_Shader(ShaderClass shader);
    void Set_Width(float width);
    void Set_Color(const Vector3 &color);
    void Set_Texture_Mapping_Mode(SegLineRendererClass::TextureMapMode mode);
    void Set_Disable_Sorting(int disable);
};

class Rva0009C134C4
{
public:
    virtual void slot0();
    virtual void slot1();
    virtual void ReleaseChild(void *child);
};

class Rva0009C134MatrixView
{
public:
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
    virtual void Set_Transform(void *matrix);
};

RenderObjClass *Create_Render_Obj(const char *name);

// Unrowed data cells (extern-only placeholders; the closers own their names).
extern void *g_rva00DFE1C8;
extern unsigned char g_rva00DB5F84;
extern void *g_rva00DE5DFC;
extern float g_rva00DE5E38, g_rva00DE5E2C, g_rva00DE5E24, g_rva00DE5E1C;
extern float g_rva00DE5E14, g_rva00DE5E0C, g_rva00DE5E08, g_rva00DE5E04;
extern float g_rva00DE5E00, g_rva00DE5E44, g_rva00DB4AA8, g_rva00DB4AAC;
extern float g_rva00DB4AB0;
extern void *g_rva00DFE758;
extern int g_rva00DB622C;
extern const char g_rva00BBAC1C;
extern const char g_rva00BBE444[];

class Rva0009C134Host
{
public:
    void rva0009CD9B();
    void rva0009C18A();
    void rva0009B28C(void *src);

private:
    unsigned char m_pad0[0xc4];
    Rva0009C134C4 *m_c4;			// +0xc4
    void *m_c8;					// +0xc8
    Rva0009C134MatrixView *m_cc;		// +0xcc
    Rva0009C134MatrixView *m_d0;		// +0xd0
    RenderObjClass *m_d4;			// +0xd4
    float m_d8;					// +0xd8
    float m_dc;					// +0xdc
    Vector3 m_e0;				// +0xe0
    unsigned char m_padE4[0x13c - 0xec];
    int m_13c;					// +0x13c
    unsigned char m_pad140[0x188 - 0x140];
    RenderObjClass *m_188;			// +0x188
    Rva0009C0EBRef *m_18c;			// +0x18c
    Rva0009C0EBRef *m_190;			// +0x190
    Rva0009C0EBRef *m_194;			// +0x194
    unsigned char m_pad198[0x1cc - 0x198];
    SegmentedLineClass *m_1cc;			// +0x1cc
    RefCountPtr<TextureClass> m_1d0;		// +0x1d0
};

static __forceinline void bfmeSetRayMatrix(Rva0009C134MatrixView *obj, const float *src,
    float angleDeg, float centerDeg, float value38, float value3c)
{
    float m[12];
    float a1 = angleDeg * 0.017453292f;
    float a2 = centerDeg * 0.017453292f + 1.5707964f;
    float s1 = (float)sin(a1);
    float c1 = (float)cos(a1);
    float s2 = (float)sin(a2);
    float c2 = (float)cos(a2);
    m[0] = 0.0f; m[1] = 0.0f; m[2] = 0.0f;
    m[3] = 0.0f; m[4] = 0.0f; m[5] = 0.0f;
    m[6] = value38; m[7] = value3c; m[8] = s2 * c1;
    m[9] = 1.0f; m[10] = s2 * s1; m[11] = c2;
    obj->Set_Transform(m);
}

void Rva0009C134Host::rva0009CD9B()
{
    m_d4 = 0;
    m_188 = 0;
    char *src = (char *)g_rva00DFE1C8 + 0x14;
    *(volatile char*)&g_rva00DB5F84 = *(volatile char*)&g_rva00DB5F84;
    g_rva00DB5F84 = 0;
    const char *name = *(char **)src != 0 ? (*(char **)src + 8) : &g_rva00BBAC1C;
    RenderObjClass *tmpD4 = Create_Render_Obj(name);
    m_d4 = tmpD4;
    RenderObjClass *tmp188 = (1 ? Create_Render_Obj("LM_SunRays") : Create_Render_Obj("LM_SunRays"));
    m_188 = tmp188;
    { struct { char v; unsigned char pad[3]; } pbA; pbA.v = 0; *(volatile char*)&pbA.v = pbA.v; }
    if ((m_d4 != 0) ? 1 : 1)
    {
        m_c4->ReleaseChild(m_d4);
        rva0009C18A();
        Rva0009C0EB *binder = (Rva0009C0EB *)this;
        binder->rva0009C0EB(&m_18c, (const AsciiString *)(src + 0x180));
        binder->rva0009C0EB(&m_190, (const AsciiString *)(src + 0x184));
        AsciiString tmp("plane03");
        binder->rva0009C0EB(&m_194, &tmp);
        if (m_190 != 0)
        {
            MeshClass *mesh = (MeshClass *)m_190;
            MeshModelClass *model = mesh->Get_Model();
            if (model != 0)
            {
                RefCountPtr<TextureClass> tex;
                tex.Ptr = 0;
                RefCountPtr<TextureClass> got = model->rva0009B266(0, 0, 0);
                tex = got;
                tex.rva00132FE9(true);
                if (--model->m_ref == 0)
                    model->Release();
            }
        }
    }
    { struct { char v; unsigned char pad[3]; } pbA2; pbA2.v = 0; *(volatile char*)&pbA2.v = pbA2.v; }
    if (m_188 != 0)
        m_c4->ReleaseChild(m_188);

    m_e0.X = *((float *)src + 0x38 / 4);
    m_e0.Y = *((float *)src + 0x3c / 4);
    m_e0.Z = *((float *)src + 0x40 / 4);
    rva0009B28C(src + 0x44);
    if (m_c8 != 0)
        m_c4->ReleaseChild(m_c8);

    if (m_cc != 0)
    {
        bfmeSetRayMatrix(m_cc, (const float *)src, *((float *)src + 0x5c / 4), *((float *)src + 0x58 / 4),
            *((float *)src + 0x60 / 4), *((float *)src + 0x64 / 4));
        m_c4->ReleaseChild(m_cc);
    }
    if (m_d0 != 0)
    {
        bfmeSetRayMatrix(m_d0, (const float *)src, *((float *)src + 0x70 / 4), *((float *)src + 0x6c / 4),
            *((float *)src + 0x74 / 4), *((float *)src + 0x78 / 4));
        m_c4->ReleaseChild(m_d0);
    }

    {
        char line[0x64];
        struct { char v; unsigned char pad[3]; } pb2; pb2.v = 0; *(volatile char*)&pb2.v = pb2.v;
        { struct { int v; unsigned char pad[11]; } pb; pb.v = 0; *(volatile int*)&pb.v = pb.v; }
        int offset = 0;
        void *fp = 0;
        fp = fopen("livingworld.txt", (const char *)g_rva00BBE444);
        ((void **)g_rva00DE5DFC)[1] = *(void **)(src + 0x1d0);
        if (fp != 0)
        {
            while (fgets(line, 0x64, fp) != 0)
            {
                *(float *)((char *)&g_rva00DE5E38 + offset) = (float)(atof(line) * 0.017453293005625408);
                if (fgets(line, 0x64, fp) == 0)
                {
                    _ReadWriteBarrier();
                    break;
                }
                *(float *)((char *)&g_rva00DE5E2C + offset) = (float)(atof(line) * m_dc);
                if (offset == 8)
                    break;
                if (fgets(line, 0x64, fp) == 0)
                    break;
                *(float *)((char *)&g_rva00DE5E24 + offset) = (float)atof(line);
                if (fgets(line, 0x64, fp) == 0)
                    break;
                *(float *)((char *)&g_rva00DE5E1C + offset) = (float)atof(line);
                if (fgets(line, 0x64, fp) == 0)
                    break;
                *(float *)((char *)&g_rva00DE5E14 + offset) = (float)atof(line);
                if (fgets(line, 0x64, fp) == 0)
                    break;
                *(float *)((char *)&g_rva00DE5E0C + offset) = (float)atof(line);
                offset += 4;
                if (offset >= 0xc)
                    break;
            }
            if (fgets(line, 0x64, fp) != 0)
                g_rva00DE5E08 = (float)atof(line);
            if (fgets(line, 0x64, fp) != 0)
                g_rva00DE5E04 = (float)atof(line);
            if (fgets(line, 0x64, fp) != 0)
                g_rva00DE5E00 = (float)atof(line);
            fclose(fp);
        }
    }

    int index = 0;
    if (g_rva00DFE758 != 0 && *((unsigned char *)g_rva00DFE758 + 0xd2e) != 0)
        index = 1;
    m_13c = *(int *)((char *)&g_rva00DE5E38 + index * 4);
    m_d8 = *(float *)((char *)&g_rva00DE5E2C + index * 4);
    g_rva00DE5E44 = *(float *)((char *)&g_rva00DE5E24 + index * 4);
    g_rva00DB4AA8 = *(float *)((char *)&g_rva00DE5E1C + index * 4);
    g_rva00DB4AAC = *(float *)((char *)&g_rva00DE5E14 + index * 4);
    g_rva00DB4AB0 = *(float *)((char *)&g_rva00DE5E0C + index * 4);

    const char *texName;
    if (*(char **)(src + 0x114) != 0)
        texName = *(char **)(src + 0x114) + 8;
    else
        texName = &g_rva00BBAC1C;
    BFME2ParticleTextureHandle handle = TextureAsset::Get(texName, 0, 0);
    ShaderClass shader;
    *(int *)&shader = g_rva00DB622C;
    SegmentedLineClass *line = new SegmentedLineClass();
    m_1cc = line;
    m_1d0.Ptr = handle.Ptr;
    line->Set_Texture(m_1d0);
    line->Set_Shader(shader);
    line->Set_Disable_Sorting(1);
    line->Set_Width(*((float *)src + 0xec / 4));
    Vector3 color;
    color.X = *((float *)src + 0xf0 / 4);
    color.Y = *((float *)src + 0xf4 / 4);
    color.Z = *((float *)src + 0xf8 / 4);
    line->Set_Color(color);
    line->Set_Texture_Mapping_Mode(SegLineRendererClass::MAP_PERSPECTIVE);
}
