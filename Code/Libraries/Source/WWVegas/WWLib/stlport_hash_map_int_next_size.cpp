// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// stlport
// STLport 4.5.3 integer hash-table comparison providers. Both bodies are
// instantiated directly; whole-class hash_map instantiation emitted unrelated
// non-retail helpers that belong to the other integer hash-table providers.
#include <hash_map>

typedef _STL::pair<const int, int> BfmeHashIntIntPair;
typedef _STL::_Ht_iterator<BfmeHashIntIntPair,
    _STL::_Nonconst_traits<BfmeHashIntIntPair>, int, _STL::hash<int>,
    _STL::_Select1st<BfmeHashIntIntPair>, _STL::equal_to<int>,
    _STL::allocator<BfmeHashIntIntPair> > BfmeHashIntIntIterator;
template bool _STL::operator==(const BfmeHashIntIntPair &, const BfmeHashIntIntPair &);
template bool _STL::operator==(const BfmeHashIntIntIterator &, const BfmeHashIntIntIterator &);
