// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: QuadDrawModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

class QuadDrawModuleInfo
{
public:
	QuadDrawModuleInfo(const QuadDrawModuleInfo &that);
	virtual void dummy();
};

extern "C" char DefaultModuleTemplate05_vtbl0;
extern "C" char QuadDrawModuleTemplate_cvtbl4;
// QuadDrawModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bd40 (retail .rdata value 109).
extern "C" char QuadDrawModuleTemplate_csub_vtbl = 109;

class QuadDrawModuleTemplate
{
public:
	QuadDrawModuleTemplate(const QuadDrawModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0QuadDrawModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
QuadDrawModuleTemplate::QuadDrawModuleTemplate(
	const QuadDrawModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	QuadDrawModuleInfo *sub = (QuadDrawModuleInfo *)((char *)this + 8);
	sub->QuadDrawModuleInfo::QuadDrawModuleInfo(*(const QuadDrawModuleInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &QuadDrawModuleTemplate_csub_vtbl;
	m_v0 = &DefaultModuleTemplate05_vtbl0;
	m_v4 = &QuadDrawModuleTemplate_cvtbl4;
}
}
// _QuadDrawModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_QuadDrawModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")
