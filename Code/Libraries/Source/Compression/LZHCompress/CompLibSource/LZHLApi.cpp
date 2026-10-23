// cl: /DNDEBUG /MD /GX- /DLZHLINTERNAL -ICode/Libraries/Source/Compression/LZHCompress/CompLibHeader

// LZHLCreateCompressor, retail 0x0068EC80 (24B), LZHLCompress,
// retail 0x0068ECA0 (25B) and LZHLDestroyCompressor,
// retail 0x0068ED60 (27B).
// Ported from Open-BFME-1 Code/Libraries/Source/Compression/LZHCompress/CompLibSource/LZHLApi.cpp
// (BFME1 0x00823200, 0x00823130 and 0x00823210). The donor's maxbuf helper
// stays out, so the unmatched-definition gate passes. Retail shuffles the
// four cdecl slots into thiscall shape (this = handle, push dst/src/size)
// and tail-returns the member answer through the single pinned call site.

#include "_huff.h"
#include "_lz.h"

// ?LZHLCreateCompressor@@YAPAXXZ, retail 0x0068EC80 (24B).
// Matched CompressFile calls this named API (retail 0x0068A880 calls it at
// 0x0068A922); the operator-new plus constructor tail-jump shape is the
// callee tiebreak against the byte-twin decompressor factory. sizeof is the
// canonical 0x18 from the vendored _lz.h declaration.
void *LZHLCreateCompressor()
{
	return new LZHLCompressor;
}

// ?LZHLCompress@@YAIPAX00I@Z, retail 0x0068ECA0 (25B).
unsigned int LZHLCompress(void *handle, void *destination, void *source, unsigned int sourceSize)
{
	return static_cast<LZHLCompressor *>(handle)->compress(
		static_cast<BYTE *>(destination), static_cast<const BYTE *>(source), sourceSize);
}

// ?LZHLDestroyCompressor@@YAXPAX@Z, retail 0x0068ED60 (27B).
// The compressor-dtor call (0x00691080) at +11 is the callee tiebreak against
// the byte-twin decompressor destroy at 0x0068ED80 (dtor 0x00692300).
void LZHLDestroyCompressor(void *handle)
{
	delete static_cast<LZHLCompressor *>(handle);
}

// Retail 0x0068ED20 (9B), between LZHLDecompress and the decompressor's
// deleting destructor: reset a decompressor handle's decoder tables through
// the rowed 0x00692360 (tail jump, ECX = handle). The API name is not in the
// references; the spelling is address-derived.
struct Rva00826840Owner
{
	void resetTables();
};

void Rva0068ED20ResetDecompressor(void *handle)
{
	static_cast<Rva00826840Owner *>(handle)->resetTables();
}
