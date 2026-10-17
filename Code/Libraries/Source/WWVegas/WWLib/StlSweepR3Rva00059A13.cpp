// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// 0x00059A13 (18B), unreferenced in retail: a container holding the
// Rva0005893DRecord hashtable at +0, copy-constructed through the rowed
// out-of-line hashtable copy constructor (0x0005893D), returning this. The
// declaration-only specialisation keeps that call out of line here, as in
// retail. Owner name address-derived.
#include <hash_map>
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
// bfme link decl-only end

struct Rva0005893DRecord {Rva0005893DRecord();Rva0005893DRecord(const Rva0005893DRecord&);~Rva0005893DRecord();Rva0005893DRecord&operator=(const Rva0005893DRecord&);char bytes[1];bool operator<(const Rva0005893DRecord&)const;bool operator==(const Rva0005893DRecord&)const;};

typedef _STL::hashtable<_STL::pair<const int,Rva0005893DRecord>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<const int,Rva0005893DRecord> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<const int,Rva0005893DRecord> > > Rva0005893DTable;

namespace _STL {
template <> Rva0005893DTable::hashtable(const Rva0005893DTable &);
}

class Rva00059A13
{
public:
	Rva00059A13(const Rva00059A13 &other);
private:
	Rva0005893DTable m_ht;
};

Rva00059A13::Rva00059A13(const Rva00059A13 &other) : m_ht(other.m_ht)
{
}
