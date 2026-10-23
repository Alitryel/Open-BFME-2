// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <deque>
#include <string>
// Suppress this TU's non-retail copy of ??1?$basic_string@GV?$char_traits@G@_STL@@V?$allocator@G@2@@_STL@@QAE@XZ:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL { template <> basic_string<unsigned short,char_traits<unsigned short>,allocator<unsigned short> >::~basic_string(); }

struct Rva000AFF52Element { unsigned prefix[2];_STL::basic_string<wchar_t> strings[1];unsigned suffix[2]; bool operator<(const Rva000AFF52Element&)const; bool operator==(const Rva000AFF52Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::__destroy_aux<Rva000AFF52Element *>(Rva000AFF52Element *, Rva000AFF52Element *, _STL::__false_type const &);
