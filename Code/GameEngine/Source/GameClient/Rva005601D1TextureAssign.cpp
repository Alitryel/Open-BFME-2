// cl: /DNDEBUG /MD
//
// ?rva005601D1@Rva005601D1@@QAEXABV?$RefCountPtr@VTextureClass@@@@@Z @ 0x005601D1 8B
//
// Unreferenced member that assigns a texture smart pointer into the
// RefCountPtr<TextureClass> member at +0x14: `add ecx,0x14` then a tail jump
// into the rowed RefCountPtr<TextureClass>::operator= (0x000424D0). It sits
// between the QuadDrawModuleInfo constructor and QuadDrawModule::doParticles;
// the owning class and the original name are not established (an ICF-folded
// setter is likely), so the name is address-derived.

class TextureClass;

template <class T>
class RefCountPtr
{
public:
	RefCountPtr const &operator=(RefCountPtr const &other);
private:
	T *Referent;
};

class Rva005601D1
{
public:
	void rva005601D1(RefCountPtr<TextureClass> const &texture);
private:
	unsigned char m_pad0[0x14];
	RefCountPtr<TextureClass> m_texture;
};

void Rva005601D1::rva005601D1(RefCountPtr<TextureClass> const &texture)
{
	m_texture = texture;
}
