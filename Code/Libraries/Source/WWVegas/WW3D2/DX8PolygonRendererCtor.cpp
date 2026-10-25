// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Retail 0x00187DE0..0x00187E6B (139 bytes). The constructor's semantic
// source is the BFME1 donor; target disassembly proves the split-table fields
// and MeshModelClass polygon list at +0x9C (the donor uses +0xA4).
// The current renderer header already has those split-table fields. Share it
// with the seed instead of duplicating the renderer and list declarations.
// The explicit list view preserves the target offset independently of the
// legacy MeshModelClass declaration. Add_Tail inlines to the same existing
// GenericMultiListClass::Internal_Add_Tail provider at 0x00610820.
#include "dx8polygonrenderer.h"

// ??0DX8PolygonRendererClass@@QAE@IPAVMeshModelClass@@PAVDX8TextureCategoryClass@@II_NI@Z
DX8PolygonRendererClass::DX8PolygonRendererClass(
	unsigned index_count_,
	MeshModelClass *mmc_,
	DX8TextureCategoryClass *tex_cat,
	unsigned vertex_offset_,
	unsigned index_offset_,
	bool strip_,
	unsigned pass_)
	:
	mmc(mmc_),
	texture_category(tex_cat),
	index_offset(index_offset_),
	vertex_offset(vertex_offset_),
	min_vertex_index(0),
	vertex_index_range(0),
	min_vertex_index2(0),
	vertex_index_range2(0),
	index_count(index_count_),
	strip(strip_),
	pass(pass_)
{
	WWASSERT(index_count);
	reinterpret_cast<DX8PolygonRendererList *>(reinterpret_cast<char *>(mmc) + 0x9C)->Add_Tail(this, true);
}
