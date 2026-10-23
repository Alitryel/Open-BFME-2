// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// BFME2's /O2 allocator<16-byte element>::allocate at RVA 0x00169F10 (30B:
// shl-4 size computation, the shared byte-allocator call 0x307F0, and a
// separate `ret 8` per arm, which the /O1 copies merge). It sits in the
// WW3D2/WWLib /O2 region and nothing in the image calls or references it,
// so its element type is unknown: the shl 4 proves only a 16-byte element.
// BfmePod16's allocate is already emitted /O1 by four units, so naming this
// /O2 body after it would make those copies COMDAT losers; the address-named
// placeholder carries the size and claims no identity (POD-PLACEHOLDER LAW:
// element construction never passes through here).
struct BfmePod16Rva00169F10 { int a[4]; };
#include <memory>
// Only allocate (the rowed body) is instantiated, as in the Pod160 shard: a
// whole-class instantiation also emits allocator::construct.
template BfmePod16Rva00169F10 *_STL::allocator<BfmePod16Rva00169F10>::allocate(unsigned int, const void *) const;
