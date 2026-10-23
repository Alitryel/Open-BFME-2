// cl: /MD
//
// ?rva0007BB4B@Rva0007DA23ResourceManager@@QAE?AV?$RefCountPtr@VTextureClass@@@@XZ
// @ 0x0007BB4B (46B): by-value RefCountPtr<TextureClass> getter selecting
// between the two texture refs at +0x14 and +0x18. Its only caller, the
// shadow texture-matrix update 0x0007C18E (W3DShadowMapManagerTextureMatrix.cpp),
// calls it on the same Rva0007DA23ResourceManager and passes the result
// straight to the rowed FXShaderParameterSourceNamespaceSAS::SetShadowMapInfo
// (0x0014F778), whose by-value third parameter is RefCountPtr<TextureClass>,
// so this getter is spelled as that class's member returning that type.
// Retail copies into the hidden return buffer via the 21B owning-handle copy
// 0x000424BB (rowed as AssetReference's copy ctor and, as here, as
// RefCountPtr<TextureClass>'s converting ctor from the native handle, the
// shape MaterialInfoClass::Peek_Texture uses), returning +0x18 only when the
// flag byte at 0x009E1FFC is set and the +0x18 ref holds a counted object (its
// first dword, the pointer, is nonzero), else +0x14.
// Shape follows the proven sibling Rva000F5D1BGet (0x000F5D1B, same
// frame/slot/call/leave/ret sequence, // cl: /O1 /MD): two return sites
// tail-merge to one E8, and the EBP frame plus zeroed [ebp-4] slot are the
// compiler's by-value-return machinery, not a source local. The class keeps
// the caller's address-derived name (owner unproven).

class AssetReference
{
public:
	void *m_object;
};

class TextureBaseClass { public: void Release_Ref(); };
class TextureClass : public TextureBaseClass {};

template <class T>
class RefCountPtr
{
public:
	AssetReference m_native;
	RefCountPtr(const RefCountPtr &);
	template <class Native> __declspec(noinline) RefCountPtr(const Native &other)
	{
		m_native.m_object = other.m_object;
		if (m_native.m_object)
			++*(unsigned short *)((char *)m_native.m_object + 4);
	}
	~RefCountPtr()
	{
		T *p = (T *)m_native.m_object;
		if (p)
			p->Release_Ref();
	}
};

extern unsigned char g_009E1FFC;
// g_009E1FFC: matched references place it at VA 0xde1ffc (zero-filled .bss).
unsigned char g_009E1FFC;

class Rva0007DA23ResourceManager
{
public:
	RefCountPtr<TextureClass> rva0007BB4B();

private:
	int m_pad00[5];
	AssetReference m_ref14;
	AssetReference m_ref18;
};

RefCountPtr<TextureClass> Rva0007DA23ResourceManager::rva0007BB4B()
{
	if (g_009E1FFC != 0 && m_ref18.m_object != 0)
		return RefCountPtr<TextureClass>(m_ref18);
	return RefCountPtr<TextureClass>(m_ref14);
}
