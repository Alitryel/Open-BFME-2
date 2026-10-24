// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <string>
// Suppress this TU's non-retail copy of ??1?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> >::~basic_string(); }

struct Rva0021FDD3Element { ~Rva0021FDD3Element(); // declared only: retail's destructor is the rowed body at its pinned address
 unsigned prefix[1];_STL::basic_string<wchar_t> strings[2];unsigned suffix[1]; bool operator<(const Rva0021FDD3Element&)const; bool operator==(const Rva0021FDD3Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<Rva0021FDD3Element *>(Rva0021FDD3Element *, Rva0021FDD3Element *, _STL::__false_type const &);
// The declared destructor binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??1Rva0021FDD3Element@@QAE@XZ=??1CreateAHeroClass@CreateAHeroManager@@QAE@XZ")
