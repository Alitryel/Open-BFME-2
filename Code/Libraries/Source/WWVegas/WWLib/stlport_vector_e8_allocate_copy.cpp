// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// Dedicated no-EH instantiation of vector<BfmeE8>::_M_allocate_and_copy.
// stlport_vector_e8_o1.cpp uses /EHsc and emits an EH frame; retail is the
// 45-byte ebp+tag body twin of vector<AsciiString>::_M_allocate_and_copy.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
struct BfmeE8 { int a, b; };
// insert(pos, x) is AreaPolygon's /O1 body 0x0030B9F3; call it, emit no copy.
namespace _STL { template <> vector<BfmeE8>::iterator vector<BfmeE8>::insert(iterator, const BfmeE8 &); }
template class _STL::vector<BfmeE8, _STL::allocator<BfmeE8 > >;

// MilesAudioManager's 8-byte trigger-area record: retail folds its push_back
// and reserve onto the BfmeE8 bodies (0x00539A2E and 0x0030B876, called by
// 0x000587C6).
struct AudioTriggerArea { int a, b; };
template void _STL::vector<AudioTriggerArea, _STL::allocator<AudioTriggerArea > >::push_back(const AudioTriggerArea &);
template void _STL::vector<AudioTriggerArea, _STL::allocator<AudioTriggerArea > >::reserve(size_t);

// Its saved form, filled by MilesAudioManager::xfer (0x0005E3E5), folds onto
// the same push_back (0x00539A2E).
struct AudioTriggerAreaSave { int a, b; };
template void _STL::vector<AudioTriggerAreaSave, _STL::allocator<AudioTriggerAreaSave > >::push_back(const AudioTriggerAreaSave &);

// GameLogic's created-object record is two pointers, the native 8-byte fold.
class Object; class MapObject;
struct Rva0024622FEntry { Object *obj; MapObject *mapObj; };
template void _STL::vector<Rva0024622FEntry>::push_back(const Rva0024622FEntry &);
