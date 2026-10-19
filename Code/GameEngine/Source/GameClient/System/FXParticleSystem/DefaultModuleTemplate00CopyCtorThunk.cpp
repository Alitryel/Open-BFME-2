// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: DefaultModuleTemplate (ledger $00 / N=1) copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

class DefaultAlphaModuleInfo
{
public:
	DefaultAlphaModuleInfo(const DefaultAlphaModuleInfo &that);
	virtual void dummy();
};

// DefaultModuleTemplate00_vtbl0: matched references place it at VA 0xc1ba70 (retail .rdata value -117).
extern "C" char DefaultModuleTemplate00_vtbl0 = -117;
extern "C" char DefaultModuleTemplate00_vtbl4;
// DefaultModuleTemplate00_sub_vtbl: matched references place it at VA 0xc1ba80 (retail .rdata value 61).
extern "C" char DefaultModuleTemplate00_sub_vtbl = 61;

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

// MSVC mangles DefaultModuleTemplate<1> as @$00
template <int N>
DefaultModuleTemplate<N>::DefaultModuleTemplate(const DefaultModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	DefaultAlphaModuleInfo *sub = (DefaultAlphaModuleInfo *)((char *)this + 8);
	sub->DefaultAlphaModuleInfo::DefaultAlphaModuleInfo(*(const DefaultAlphaModuleInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &DefaultModuleTemplate00_sub_vtbl;
	m_v0 = &DefaultModuleTemplate00_vtbl0;
	m_v4 = &DefaultModuleTemplate00_vtbl4;
}

template DefaultModuleTemplate<1>::DefaultModuleTemplate(const DefaultModuleTemplate &);
}
// _DefaultModuleTemplate00_vtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_DefaultModuleTemplate00_vtbl4=?vftable_0112B89C@@3HA")
