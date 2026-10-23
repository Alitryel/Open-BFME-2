// cl: /EHsc /MD
// ??0Rva0018BEC7@@QAE@XZ, retail 0x0018BEC7, 66 bytes.
// Ctor registering "WW3D" via rowed Rva00153565Register; vtable at +0 plus member vtable at +4.
// Evidence: disassembly stores 0x007D5BE4/0x007D5BD4 then calls Register("WW3D", this);
// caller0x0017414B; namespace base at0 arms state0, namespace member at4 state1.
void __cdecl Rva00153565Register(const char *name, void *obj);

// Both native cleanup states reach the complete7B namespace-base dtorE14BD.
// The primary namespace interface comes from the verified binder/namespace
// units; member ctor18BE7E and tableBD5BD4 establish its primary vptr at4.
// Native member slot1 names SourceNamespace_Fog::ResolveBindings18BFCE.
// BD5BD4 slot1 is the rowed Fog binder18BFCE. Its WorldBuilder counterpart
// asserts FXShaderParameterSourceNamespaceWW3D::SourceNamespace_Fog at
// fxshadernamespaceww3d.cpp:102, identifying this member's nested class.
class FXShaderParameterBinder;
typedef const char *D3DXHANDLE;
class FXShaderParameterSourceNamespace {
public:
    virtual ~FXShaderParameterSourceNamespace() {}
    virtual void ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *) = 0;
};

class FXShaderParameterSourceNamespaceWW3D : public FXShaderParameterSourceNamespace {
public:
    class SourceNamespace_Fog : public FXShaderParameterSourceNamespace {
    public:
        SourceNamespace_Fog();
        virtual ~SourceNamespace_Fog() {}
        virtual void ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *);
    };
    virtual ~FXShaderParameterSourceNamespaceWW3D();
    FXShaderParameterSourceNamespaceWW3D();
    virtual void ResolveBindings(const char *, D3DXHANDLE, FXShaderParameterBinder *);
    SourceNamespace_Fog m_member;
    float m_opacityOverride;
};

// Native18BE7E installs BD5BD4 and returns this (complete9B).
FXShaderParameterSourceNamespaceWW3D::SourceNamespace_Fog::SourceNamespace_Fog()
{
}

FXShaderParameterSourceNamespaceWW3D::FXShaderParameterSourceNamespaceWW3D()
{
    Rva00153565Register("WW3D", this);
}
