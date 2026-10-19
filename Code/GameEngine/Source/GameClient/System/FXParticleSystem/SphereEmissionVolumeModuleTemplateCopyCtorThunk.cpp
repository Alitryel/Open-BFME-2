// cl: /DNDEBUG /MD /GX- /Ob2

// Open-BFME5: SphereEmissionVolumeModuleTemplate copy ctor
// Retail: base copy; null-preserving sub copy at +8; dual outer vtbl + sub vtbl.

namespace FXParticleSystem
{

template <int CATEGORY>
class CategoryModuleTemplate
{
public:
	CategoryModuleTemplate(const CategoryModuleTemplate &that);
};

class SphereEmissionVolumeInfo
{
public:
	SphereEmissionVolumeInfo(const SphereEmissionVolumeInfo &that);
	virtual void dummy();
};

// SphereEmissionVolumeModuleTemplate_cvtbl0: matched references place it at VA 0xc1bb80 (retail .rdata value 13).
extern "C" char SphereEmissionVolumeModuleTemplate_cvtbl0 = 13;
extern "C" char SphereEmissionVolumeModuleTemplate_cvtbl4;
// SphereEmissionVolumeModuleTemplate_csub_vtbl: matched references place it at VA 0xc1bb70 (retail .rdata value 37).
extern "C" char SphereEmissionVolumeModuleTemplate_csub_vtbl = 37;

class SphereEmissionVolumeModuleTemplate
{
public:
	SphereEmissionVolumeModuleTemplate(const SphereEmissionVolumeModuleTemplate &);

private:
	void *m_v0;
	void *m_v4;
	char m_sub[4];
};

// ??0SphereEmissionVolumeModuleTemplate@FXParticleSystem@@QAE@ABV01@@Z
SphereEmissionVolumeModuleTemplate::SphereEmissionVolumeModuleTemplate(
	const SphereEmissionVolumeModuleTemplate &that)
{
	const void *src = &that;
	((CategoryModuleTemplate<0> *)this)->CategoryModuleTemplate<0>::CategoryModuleTemplate(
		*(const CategoryModuleTemplate<0> *)src);
	const void *sub_src = src ? (const char *)src + 8 : 0;
	SphereEmissionVolumeInfo *sub = (SphereEmissionVolumeInfo *)((char *)this + 8);
	sub->SphereEmissionVolumeInfo::SphereEmissionVolumeInfo(*(const SphereEmissionVolumeInfo *)sub_src);
	// Sub vtbl then outer dual vtbls (retail store order).
	*(void **)sub = &SphereEmissionVolumeModuleTemplate_csub_vtbl;
	m_v0 = &SphereEmissionVolumeModuleTemplate_cvtbl0;
	m_v4 = &SphereEmissionVolumeModuleTemplate_cvtbl4;
}
}
// _SphereEmissionVolumeModuleTemplate_cvtbl4: the global at VA 0xc1c780 is ?vftable_0112B89C@@3HA.
#pragma comment(linker, "/alternatename:_SphereEmissionVolumeModuleTemplate_cvtbl4=?vftable_0112B89C@@3HA")
