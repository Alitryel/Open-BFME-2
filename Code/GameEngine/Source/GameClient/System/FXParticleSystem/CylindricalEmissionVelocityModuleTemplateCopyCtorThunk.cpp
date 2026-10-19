// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: CylindricalEmissionVelocityModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

class CylindricalEmissionVelocityInfo
{
public:
	CylindricalEmissionVelocityInfo(const CylindricalEmissionVelocityInfo &that);
	virtual void dummy();
};

// CylindricalEmissionVelocityModuleTemplate_cvtbl0: matched references place it at VA 0xc1bc70 (retail .rdata value 20).
extern "C" char CylindricalEmissionVelocityModuleTemplate_cvtbl0 = 20;
extern "C" char CylindricalEmissionVelocityModuleTemplate_cvtbl4;
// CylindricalEmissionVelocityModuleTemplate_csub_vtbl: VA 0xc1bc80 (retail 6B vtable at 0x0081BC80, shared with Outward; local link placeholder).
extern "C" char CylindricalEmissionVelocityModuleTemplate_csub_vtbl = 0;

class CylindricalEmissionVelocityModuleTemplate
{
public:
	CylindricalEmissionVelocityModuleTemplate(const CylindricalEmissionVelocityModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0CylindricalEmissionVelocityModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
CylindricalEmissionVelocityModuleTemplate::CylindricalEmissionVelocityModuleTemplate(
	const CylindricalEmissionVelocityModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	CylindricalEmissionVelocityInfo *sub = (CylindricalEmissionVelocityInfo *)((char *)this + 8);
	sub->CylindricalEmissionVelocityInfo::CylindricalEmissionVelocityInfo(*(const CylindricalEmissionVelocityInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &CylindricalEmissionVelocityModuleTemplate_csub_vtbl;
	m_v0 = &CylindricalEmissionVelocityModuleTemplate_cvtbl0;
	m_v4 = &CylindricalEmissionVelocityModuleTemplate_cvtbl4;
}
}
// _CylindricalEmissionVelocityModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_CylindricalEmissionVelocityModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")
