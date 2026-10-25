// cl: /DBFME_WWSTRING_NATIVE_CSTR_ASSIGN /Ireference/shims/wwstring_teardown/bfme /Ireference/shims/bfmerendobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep
// Retail 0x00187E90..0x00187F25 (149 bytes). Semantic source is the BFME1
// constructor; retail proves the copied split-table fields and MeshModel list
// at +0x9C. Share the seed renderer header as the primary constructor does,
// and keep the target list offset independent of the donor mesh declaration.
// Add_Tail inlines to the existing Internal_Add_Tail provider at 0x00610820.
#include "dx8polygonrenderer.h"

// ??0DX8PolygonRendererClass@@QAE@ABV0@PAVMeshModelClass@@@Z
DX8PolygonRendererClass::DX8PolygonRendererClass(const DX8PolygonRendererClass& src,MeshModelClass* mmc_)
	:
	mmc(mmc_),
	texture_category(src.texture_category),
	index_offset(src.index_offset),
	vertex_offset(src.vertex_offset),
	min_vertex_index(src.min_vertex_index),
	vertex_index_range(src.vertex_index_range),
	min_vertex_index2(src.min_vertex_index2),
	vertex_index_range2(src.vertex_index_range2),
	index_count(src.index_count),
	strip(src.strip),
	pass(src.pass)
{
	reinterpret_cast<DX8PolygonRendererList *>(reinterpret_cast<char *>(mmc) + 0x9C)->Add_Tail(this, true);
}
