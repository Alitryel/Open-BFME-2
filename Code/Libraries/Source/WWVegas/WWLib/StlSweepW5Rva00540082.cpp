// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva00540082Element {Rva00540082Element();Rva00540082Element(const Rva00540082Element&);Rva00540082Element&operator=(const Rva00540082Element&);~Rva00540082Element(){}char bytes[40]; bool operator==(const Rva00540082Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template Rva00540082Element * _STL::__copy<Rva00540082Element *, Rva00540082Element *, int>(Rva00540082Element *, Rva00540082Element *, Rva00540082Element *, _STL::random_access_iterator_tag const &, int *);

// The retail call in this body reads 0x00540053, an address the ledger already
// carries as ??0?$pair@$$CBHURva00540053Element@@@_STL@@QAE@ABU01@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??4Rva00540082Element@@QAEAAU0@ABU0@@Z=??0?$pair@$$CBHURva00540053Element@@@_STL@@QAE@ABU01@@Z")
