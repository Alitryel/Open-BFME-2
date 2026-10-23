// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva005FE0A6Element {Rva005FE0A6Element();Rva005FE0A6Element(const Rva005FE0A6Element&);Rva005FE0A6Element&operator=(const Rva005FE0A6Element&);~Rva005FE0A6Element(){}char bytes[12]; bool operator==(const Rva005FE0A6Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::fill<Rva005FE0A6Element *, Rva005FE0A6Element>(Rva005FE0A6Element *, Rva005FE0A6Element *, Rva005FE0A6Element const &);

// The retail call in this body reads 0x005FDEC7, an address the ledger already
// carries as ??4BfmeContainerRecord005FDEC7@@QAEAAU0@ABU0@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??4Rva005FE0A6Element@@QAEAAU0@ABU0@@Z=??4BfmeContainerRecord005FDEC7@@QAEAAU0@ABU0@@Z")
