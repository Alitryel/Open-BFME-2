// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// vector<Rva0040CB11Entry>::reserve, retail 0x0040E135 (104 bytes). STLport
// 4.5.3 reserve body over the rowed Rva0040CB11Entry allocate_and_copy and
// allocate; its _M_clear resolves to the Rva004F69C3 _M_clear body ICF
// folded at 0x004F89F9 (pinned as an alias). Built from the banked attempt
// reverse/attempts/0x0040e135.cpp.
class Rva004F6093Holder
{
public:
	Rva004F6093Holder(const Rva004F6093Holder &other);
private:
	void *m_ptr;
};
class Rva0040CB11Entry
{
public:
	Rva0040CB11Entry();
	Rva0040CB11Entry(const Rva0040CB11Entry &other);
	~Rva0040CB11Entry();
private:
	int m_first;
	Rva004F6093Holder m_second;
};
#include <memory>
namespace _STL {
template<> void _Construct<Rva0040CB11Entry, Rva0040CB11Entry>(Rva0040CB11Entry *, const Rva0040CB11Entry &);
template<> void _Destroy<Rva0040CB11Entry *>(Rva0040CB11Entry *, Rva0040CB11Entry *);
}
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void _Construct<Rva0040CB11Entry, Rva0040CB11Entry>(Rva0040CB11Entry *, Rva0040CB11Entry const &); }
// bfme link decl-only end
template <>
inline void _STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> >::reserve(size_type __n)
{
  if (capacity() < __n) {
    const size_type __old_size = size();
    pointer __tmp;
    if (this->_M_start) {
      __tmp = _M_allocate_and_copy(__n, (const_pointer)this->_M_start, (const_pointer)this->_M_finish);
      _M_clear();
    } else {
      __tmp = this->_M_end_of_storage.allocate(__n);
    }
    _M_set(__tmp, __tmp + __old_size, __tmp + __n);
  }
}

// vector<Rva0040CB11Entry>::reserve is a header inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the linked build. This
// anchor only makes this unit emit its copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitStlportVectorRva0040CB11EntryReserve@@YAXPAV?$vector@VRva0040CB11Entry@@V?$allocator@VRva0040CB11Entry@@@_STL@@@_STL@@@Z present-unmatched
void bfmeEmitStlportVectorRva0040CB11EntryReserve(_STL::vector<Rva0040CB11Entry, _STL::allocator<Rva0040CB11Entry> > *p)
{
	p->reserve(0);
}
#pragma inline_depth()
