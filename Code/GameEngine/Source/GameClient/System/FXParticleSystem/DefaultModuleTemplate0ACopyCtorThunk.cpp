// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: DefaultModuleTemplate (N=0) copy ctor
// Retail: base copy; null-preserving sub at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

class DefaultColorModuleInfo
{
public:
	DefaultColorModuleInfo(const DefaultColorModuleInfo &that);
	virtual void dummy();
};

// DefaultModuleTemplate0A_vtbl0: matched references place it at VA 0xc1baa0 (retail .rdata value -18).
extern "C" char DefaultModuleTemplate0A_vtbl0 = -18;
extern "C" char DefaultModuleTemplate0A_vtbl4;
// DefaultModuleTemplate0A_sub_vtbl: matched references place it at VA 0xc1bab0 (retail .rdata value -99).
extern "C" char DefaultModuleTemplate0A_sub_vtbl = -99;

template <int N>
class DefaultModuleTemplate
{
public:
	DefaultModuleTemplate(const DefaultModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

template <int N>
DefaultModuleTemplate<N>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	DefaultColorModuleInfo *sub = (DefaultColorModuleInfo *)((char *)this + 8);
	sub->DefaultColorModuleInfo::DefaultColorModuleInfo(*(const DefaultColorModuleInfo *)sub_src);
	*(void **)sub = &DefaultModuleTemplate0A_sub_vtbl;
	m_v0 = &DefaultModuleTemplate0A_vtbl0;
	m_v4 = &DefaultModuleTemplate0A_vtbl4;
}

template DefaultModuleTemplate<0>::DefaultModuleTemplate(const DefaultModuleTemplate &);
}
// _DefaultModuleTemplate0A_vtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_DefaultModuleTemplate0A_vtbl4=?vftable_0112B89C@@3HA")
