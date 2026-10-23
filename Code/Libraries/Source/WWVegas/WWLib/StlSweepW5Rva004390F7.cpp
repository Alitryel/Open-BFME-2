// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>

struct Rva004390F7Element {Rva004390F7Element();Rva004390F7Element(const Rva004390F7Element&);Rva004390F7Element&operator=(const Rva004390F7Element&);virtual void slot0();virtual ~Rva004390F7Element();char bytes[4]; bool operator<(const Rva004390F7Element&)const; bool operator==(const Rva004390F7Element&)const;};

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<Rva004390F7Element, _STL::allocator<Rva004390F7Element> >::push_back(Rva004390F7Element const &);

// Retail's push_back calls the rowed list insert at 0x004390A2; suppress this TU's own copy (which would call the element copy constructor, defined nowhere) and bind the template name to that row.
namespace _STL { template <> list<Rva004390F7Element, allocator<Rva004390F7Element> >::iterator list<Rva004390F7Element, allocator<Rva004390F7Element> >::insert(iterator, const Rva004390F7Element &); }
#pragma comment(linker, "/alternatename:?insert@?$list@URva004390F7Element@@V?$allocator@URva004390F7Element@@@_STL@@@_STL@@QAE?AU?$_List_iterator@URva004390F7Element@@U?$_Nonconst_traits@URva004390F7Element@@@_STL@@@2@U32@ABURva004390F7Element@@@Z=?insert@?$list@UBfmePod196@@V?$allocator@UBfmePod196@@@_STL@@@_STL@@QAE?AU?$_List_iterator@UBfmePod196@@U?$_Nonconst_traits@UBfmePod196@@@_STL@@@2@U32@ABUBfmePod196@@@Z")
