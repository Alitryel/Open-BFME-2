// cl: /EHsc /MD
// ??1Rva0018BEC7@@UAE@XZ, retail 0x0018BE87, 64 bytes.
// Ctor registers "WW3D" (rowed 0x0018BEC7), dtor erases "WW3D"; vtable at +0
// plus member vptr at +4, both reset to the base vtable in the dtor. Evidence:
// dtor stores the derived vtable then Erase then both to the base vtable;
// callers 0x0017414B/0x0018BF0C. A trailing _ReadWriteBarrier (no code) holds
// the EH epilogue scheduling retail uses.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
void __cdecl Rva001532E1Erase(const char *name);

class FXShaderParameterBinder;
class FXShaderParameterSourceNamespace {
public:
    virtual ~FXShaderParameterSourceNamespace() {}
    virtual void ResolveBindings(const char *, const char *, FXShaderParameterBinder *) = 0;
};

class FXShaderParameterSourceNamespaceWW3D : public FXShaderParameterSourceNamespace {
public:
    class SourceNamespace_Fog : public FXShaderParameterSourceNamespace {
    public:
        ~SourceNamespace_Fog() {}
        virtual void ResolveBindings(const char *, const char *, FXShaderParameterBinder *);
    };
    virtual ~FXShaderParameterSourceNamespaceWW3D();
    FXShaderParameterSourceNamespaceWW3D();
    virtual void ResolveBindings(const char *, const char *, FXShaderParameterBinder *);
    SourceNamespace_Fog m_member;
    float m_opacityOverride;
};

FXShaderParameterSourceNamespaceWW3D::~FXShaderParameterSourceNamespaceWW3D()
{
    Rva001532E1Erase("WW3D");
    _ReadWriteBarrier();
}
