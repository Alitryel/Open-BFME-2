// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
// Address-derived recovery of 0x0015B110 (136B), a ref-counted object factory.
// Retail: operator new(0x34) 0x002FDA0, copy-construct this via FXShaderSetup's
// copy ctor 0x00152DE9 (vtable 0x00BD3B1C, refcount at +4), store into the hidden
// return pointer, then the smart pointer's copy AddRef ([p+4]+=1) and
// temporary Release ([p+4]-=1, deleting through vtable[0] on zero). The
// hidden-pointer ret 4 and AssetReference-style temp match the rowed
// sharebuf/RefCount family. Ctor and class names are address-derived.

class RefCountClass
{
public:
    virtual void Delete();
    int m_refCount;

    void AddRef() { ++m_refCount; }
    int Release() { return --m_refCount; }
};

// The constructor at 0x00152DE9 is FXShaderSetup's copy constructor (rowed in
// fxshadersetup.cpp): the factory copies its own object.
class FXShaderSetup : public RefCountClass
{
public:
    FXShaderSetup(const FXShaderSetup &that);

    char m_pad[0x2C];
};

class RefPtr
{
public:
    RefCountClass *m_ptr;

    RefPtr(RefCountClass *p) : m_ptr(p) {}
    RefPtr(const RefPtr &other) : m_ptr(other.m_ptr)
    {
        if (m_ptr)
            m_ptr->AddRef();
    }
    // Release through the pointer already loaded: retail's one out-of-line
    // copy is 0x0007B724 (17 B, as MeshMatDescUniqueArrays.cpp builds it);
    // re-reading m_ptr after the decrement emitted a 19-byte copy.
    ~RefPtr()
    {
        RefCountClass *p = m_ptr;
        if (p && p->Release() == 0)
            p->Delete();
    }
};

class Rva0015B110Owner
{
public:
    RefPtr rva0015b110();
};

RefPtr Rva0015B110Owner::rva0015b110()
{
    RefPtr temp(new FXShaderSetup(*reinterpret_cast<const FXShaderSetup *>(this)));
    return temp;
}
