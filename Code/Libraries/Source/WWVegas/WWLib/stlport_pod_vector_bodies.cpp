// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector members instantiated with code-generation element
// views. BfmePodN names only an element size (the BfmeE16/Rva..Element
// convention); it is not an application-type claim. Some direct callers and
// non-trivial element copy/destruction paths are now target-backed, but a
// concrete identity is recorded only where that independent evidence supports
// it. char likewise stands for any 1-byte element.
//
// BfmePodN (BfmeShortPodN: 2-byte aligned) is a placeholder for the real
// N-byte element type at each site.
// Where retail's copy construct for that element is non-trivial (it calls a
// copy constructor), _Construct<BfmePodN> is pinned in symbols.csv at the
// address the byte-true call site proves; that body is not compiled from here.
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
#include <algorithm>
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
// bfme link decl-only begin
namespace _STL { template <> unsigned char * allocator<unsigned char>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end
struct BfmePod20 { int a[5]; };
struct BfmePod24 { int a[6]; };
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] < y.a[0]; }
struct BfmePod28 { int a[7]; };
// bfme link decl-only BfmePod28
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *, BfmePod28 *); }
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *); }
inline bool operator==(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] < y.a[0]; }
struct BfmePod32 { int a[8]; };
// bfme link decl-only BfmePod32
namespace _STL { template <> vector<BfmePod32, allocator<BfmePod32> >::~vector(); }
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod32> has its own pin; declare that specialization so
// this unit calls it rather than emitting a second, non-retail copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod32, BfmePod32>(BfmePod32 *__p, const BfmePod32 &__val); }
struct BfmePod36 { int a[9]; };
inline bool operator==(const BfmePod36 &x, const BfmePod36 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod36 &x, const BfmePod36 &y) { return x.a[0] < y.a[0]; }
struct BfmePod40 { int a[10]; };
// bfme link decl-only BfmePod40
namespace _STL { template <> vector<BfmePod40, allocator<BfmePod40> >::~vector(); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *, BfmePod40 *); }
inline bool operator==(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod40 &x, const BfmePod40 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod40> is pinned elsewhere; declare that
// specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod40, BfmePod40>(BfmePod40 *__p, const BfmePod40 &__val); }
struct BfmePod44 { int a[11]; };
inline bool operator==(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod44 &x, const BfmePod44 &y) { return x.a[0] < y.a[0]; }
struct BfmePod48 { int a[12]; };
inline bool operator==(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod48 &x, const BfmePod48 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod48> is pinned elsewhere; declare that
// specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod48, BfmePod48>(BfmePod48 *__p, const BfmePod48 &__val); }
struct BfmePod52 { int a[13]; };
inline bool operator==(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod52 &x, const BfmePod52 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod52> is rowed in stlport_construct_pod52_rva.cpp
// (0x001DD2DC); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod52, BfmePod52>(BfmePod52 *__p, const BfmePod52 &__val); }
struct BfmePod60 { int a[15]; };
inline bool operator==(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod60> is pinned elsewhere; declare that
// specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod60, BfmePod60>(BfmePod60 *__p, const BfmePod60 &__val); }
struct BfmePod68 { int a[17]; };
// bfme link decl-only BfmePod68
namespace _STL { template <> BfmePod68 * vector<BfmePod68, allocator<BfmePod68> >::erase(BfmePod68 *, BfmePod68 *); }
namespace _STL { template <> BfmePod68 * vector<BfmePod68, allocator<BfmePod68> >::erase(BfmePod68 *); }
template BfmePod68 * _STL::__copy(BfmePod68 *, BfmePod68 *, BfmePod68 *, const _STL::random_access_iterator_tag &, ptrdiff_t *);
inline bool operator==(const BfmePod68 &x, const BfmePod68 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod68 &x, const BfmePod68 &y) { return x.a[0] < y.a[0]; }
struct BfmePod76 { int a[19]; };
inline bool operator==(const BfmePod76 &x, const BfmePod76 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod76 &x, const BfmePod76 &y) { return x.a[0] < y.a[0]; }
struct BfmePod80 { int a[20]; };
inline bool operator==(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod80 &x, const BfmePod80 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod80> is rowed in stlport_construct_pod80_rva.cpp
// (0x0051F920); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod80, BfmePod80>(BfmePod80 *__p, const BfmePod80 &__val); }
struct BfmePod88 { int a[22]; };
// bfme link decl-only BfmePod88
namespace _STL { template <> vector<BfmePod88, allocator<BfmePod88> >::~vector(); }
// _Construct<BfmePod88> is rowed at 0x004E3706 in stlport_construct_pod88_rva.cpp
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod88, BfmePod88>(BfmePod88 *__p, const BfmePod88 &__val); }
inline bool operator==(const BfmePod88 &x, const BfmePod88 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod88 &x, const BfmePod88 &y) { return x.a[0] < y.a[0]; }
struct BfmePod92 { int a[23]; };
inline bool operator==(const BfmePod92 &x, const BfmePod92 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod92 &x, const BfmePod92 &y) { return x.a[0] < y.a[0]; }
// _Construct<BfmePod92> is the rowed non-trivial copy construct at 0x00049D44: declare it, as for Pod172.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod92, BfmePod92>(BfmePod92 *__p, const BfmePod92 &__val); }
struct BfmePod104 { int a[26]; };
inline bool operator==(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod104 &x, const BfmePod104 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod104> is rowed in StlportConstructFamily.cpp
// (0x003B8AD8); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod104, BfmePod104>(BfmePod104 *__p, const BfmePod104 &__val); }
struct BfmePod128 { int a[32]; };
inline bool operator==(const BfmePod128 &x, const BfmePod128 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod128 &x, const BfmePod128 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod128> is pinned elsewhere; declare that
// specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod128, BfmePod128>(BfmePod128 *__p, const BfmePod128 &__val); }
struct BfmePod144 { int a[36]; };
inline bool operator==(const BfmePod144 &x, const BfmePod144 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod144 &x, const BfmePod144 &y) { return x.a[0] < y.a[0]; }
// _Construct<BfmePod144> is the pinned copy construct at 0x00053DFE: declare it, as for Pod172.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod144, BfmePod144>(BfmePod144 *__p, const BfmePod144 &__val); }
struct BfmePod148 { int a[37]; };
inline bool operator==(const BfmePod148 &x, const BfmePod148 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod148 &x, const BfmePod148 &y) { return x.a[0] < y.a[0]; }
// _Construct<BfmePod148> is the rowed non-trivial copy construct at 0x00361470: declare it, as for Pod172.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod148, BfmePod148>(BfmePod148 *__p, const BfmePod148 &__val); }
struct BfmePod160 { int a[40]; };
inline bool operator==(const BfmePod160 &x, const BfmePod160 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod160 &x, const BfmePod160 &y) { return x.a[0] < y.a[0]; }
// _Construct<BfmePod160> is the pinned copy construct at 0x003A454E: declare it, as for Pod172.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod160, BfmePod160>(BfmePod160 *__p, const BfmePod160 &__val); }
struct BfmePod172 { int a[43]; };
inline bool operator==(const BfmePod172 &x, const BfmePod172 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod172 &x, const BfmePod172 &y) { return x.a[0] < y.a[0]; }
// _Construct<BfmePod172> has its own row (stlport_construct_pod172.cpp, 0x001EB9E6): declare that
// specialization so this unit calls it rather than emitting a second, duplicate copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod172, BfmePod172>(BfmePod172 *__p, const BfmePod172 &__val); }
struct BfmePod180 { int a[45]; };
inline bool operator==(const BfmePod180 &x, const BfmePod180 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod180 &x, const BfmePod180 &y) { return x.a[0] < y.a[0]; }
// _Construct<BfmePod180> is the rowed non-trivial copy construct at 0x000C2387: declare it, as for Pod172.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod180, BfmePod180>(BfmePod180 *__p, const BfmePod180 &__val); }
// The 216-byte element is CreateAHeroManager::CreateAHeroSubClass: its vector
// is CreateAHeroClass +0x14 (parseCreateAHeroSubClass push_back, CreateAHeroClass
// copy 0x0021F876); this unit keeps only its 216-byte footprint.
class CreateAHeroManager
{
public:
    class CreateAHeroSubClass { public: int a[54]; };
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline vector<CreateAHeroManager::CreateAHeroSubClass,allocator<CreateAHeroManager::CreateAHeroSubClass> >::~vector() { _Destroy(this->_M_start, this->_M_finish); } }
namespace _STL { template <> void _Destroy(CreateAHeroManager::CreateAHeroSubClass *); }
// Retail's _Construct<CreateAHeroSubClass> is rowed in stlport_construct_pod216.cpp
// (0x0021EF66); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<CreateAHeroManager::CreateAHeroSubClass, CreateAHeroManager::CreateAHeroSubClass>(CreateAHeroManager::CreateAHeroSubClass *__p, const CreateAHeroManager::CreateAHeroSubClass &__val); }
inline bool operator==(const CreateAHeroManager::CreateAHeroSubClass &x, const CreateAHeroManager::CreateAHeroSubClass &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const CreateAHeroManager::CreateAHeroSubClass &x, const CreateAHeroManager::CreateAHeroSubClass &y) { return x.a[0] < y.a[0]; }
struct BfmePod248 { int a[62]; };
namespace _STL {template<> vector<BfmePod248,allocator<BfmePod248> >::~vector();}
inline bool operator==(const BfmePod248 &x, const BfmePod248 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod248 &x, const BfmePod248 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod248> is rowed in StlportConstructFamily.cpp
// (0x000C78F3); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod248, BfmePod248>(BfmePod248 *__p, const BfmePod248 &__val); }
struct BfmePod252 { int a[63]; };
// Native calls bind the non-trivial copy helper owned at RVA 000C3717.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod252, BfmePod252>(BfmePod252 *, const BfmePod252 &); }
namespace _STL {template<> vector<BfmePod252,allocator<BfmePod252> >::~vector();}
inline bool operator==(const BfmePod252 &x, const BfmePod252 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod252 &x, const BfmePod252 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod252> is rowed in StlportConstructFamily.cpp
// (0x000C3717); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod252, BfmePod252>(BfmePod252 *__p, const BfmePod252 &__val); }
struct BfmePod260 { int a[65]; };
inline bool operator==(const BfmePod260 &x, const BfmePod260 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod260 &x, const BfmePod260 &y) { return x.a[0] < y.a[0]; }
struct BfmePod340 { int a[85]; };
inline bool operator==(const BfmePod340 &x, const BfmePod340 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod340 &x, const BfmePod340 &y) { return x.a[0] < y.a[0]; }
// Retail's _Construct<BfmePod340> is rowed in StlportConstructFamily.cpp
// (0x004D9B98); declare that specialization so this unit emits no competing copy.
namespace _STL { template <> __declspec(nothrow) void _Construct<BfmePod340, BfmePod340>(BfmePod340 *__p, const BfmePod340 &__val); }

// The 20-byte growth worker is the complete no-catch retail body at
// 0x59B809. Other element copies in this TU retain their native EH paths.
// Keep STLport 4.5.3 growth/copy/fill/release semantics for this specialization.
template <> inline void _STL::vector<BfmePod20>::_M_insert_overflow(
    BfmePod20 *__position, const BfmePod20 &__x, const _STL::__false_type &,
    unsigned int __fill_len, bool __atend)
{
    const size_type __old_size = size();
    const size_type __len = __old_size + (max)(__old_size, __fill_len);
    pointer __new_start = this->_M_end_of_storage.allocate(__len);
    pointer __new_finish = __new_start;
    __new_finish = __uninitialized_copy(this->_M_start, __position, __new_start, __false_type());
    if (__fill_len == 1) {
        _Construct(__new_finish, __x);
        ++__new_finish;
    } else
        __new_finish = __uninitialized_fill_n(__new_finish, __fill_len, __x, __false_type());
    if (!__atend)
        __new_finish = __uninitialized_copy(__position, this->_M_finish, __new_finish, __false_type());
    _M_clear();
    _M_set(__new_start, __new_finish, __new_start + __len);
}

// Target boundary 0x0007EA1F/136 is vector<char>::_M_insert_overflow for the
// true_type path: matched _M_fill_insert at 0x0007FE65 calls it with the five
// overflow arguments and the target returns with ret 0x14. The STLport 4.5.3
// donor omits retail's zero-length allocation guard (128B here); this explicit
// specialization adds that target-observed branch while retaining the donor's
// copy/fill/capacity semantics. Helpers are target-resolved as allocator<char>
// 0x307F0, __copy_trivial 0x179B0, FillN 0x24970 and _free 0x30830.
template <> void _STL::vector<char, _STL::allocator<char> >::_M_insert_overflow(
    char *position, const char &value, const _STL::__true_type &,
    unsigned int fill_len, bool at_end)
{
    const unsigned int old_size = this->_M_finish - this->_M_start;
    char *new_start;
    const unsigned int new_len = old_size + (max)(old_size, fill_len);
    if (new_len != 0)
        new_start = this->_M_end_of_storage.allocate(new_len);
    else
        new_start = 0;
    char *new_finish = (char *)_STL::__copy_trivial(this->_M_start, position, new_start);
    new_finish = _STL::fill_n(new_finish, fill_len, value);
    if (!at_end)
        new_finish = (char *)_STL::__copy_trivial(position, this->_M_finish, new_finish);
    this->_M_clear();
    this->_M_set(new_start, new_finish, new_start + new_len);
}

// Target 0x000AFB2E/136 is the byte-vector overflow sibling of 0x0007EA1F.
// Retail calls the independently rowed unsigned-char fill_n at 0x000AD829;
// allocation, trivial copying and checked free match the char specialization.
// The unsigned-byte template view follows that typed fill helper; the containing
// application type remains unknown. The zero-allocation guard is target evidence.
template <> void _STL::vector<unsigned char, _STL::allocator<unsigned char> >::_M_insert_overflow(
    unsigned char *position, const unsigned char &value, const _STL::__true_type &,
    unsigned int fill_len, bool at_end)
{
    const unsigned int old_size = this->_M_finish - this->_M_start;
    unsigned char *new_start;
    const unsigned int new_len = old_size + (max)(old_size, fill_len);
    if (new_len != 0)
        new_start = (unsigned char *)_STL::allocator<char>::allocate(new_len, 0);
    else
        new_start = 0;
    unsigned char *new_finish = (unsigned char *)_STL::__copy_trivial(this->_M_start, position, new_start);
    new_finish = _STL::fill_n(new_finish, fill_len, value);
    if (!at_end)
        new_finish = (unsigned char *)_STL::__copy_trivial(position, this->_M_finish, new_finish);
    this->_M_clear();
    this->_M_set(new_start, new_finish, new_start + new_len);
}

// Target boundary 0x00307641/63 is _Vector_base<char>::_Vector_base(count, alloc):
// ??0?$_Vector_base@DV?$allocator@D@_STL@@@_STL@@QAE@IABV?$allocator@D@1@@Z,
// pinned name, called at 0x00307C51 by vector<char> ctor 0x00307C43 (rowed
// in this TU). The STLport 4.5.3 donor emits unconditional allocate (57B via
// template class); retail skips allocate when count==0 (63B with xor-eax,
// cmp ebx,eax and je). This explicit specialization adds that target-observed
// guard while retaining donor semantics. Callees are alloc proxy 0x00007410
// and byte allocator 0x000307F0, both settled. tmp starts as the current
// (null) _M_finish to reproduce retail's eax zeroing.
template <> _STL::_Vector_base<char, _STL::allocator<char> >::_Vector_base(unsigned int __n, const _STL::allocator<char> &__a)
    : _M_start(0), _M_finish(0), _M_end_of_storage(__a, 0)
{
    char *tmp = _M_finish;
    if (__n != 0)
        tmp = _M_end_of_storage.allocate(__n);
    else
        tmp = 0;
    _M_start = tmp;
    _M_finish = tmp;
    _M_end_of_storage._M_data = tmp + __n;
}

// Rowed in stlport_byte_vector_resize_value.cpp; declared here so the
// explicit instantiation below emits no competing copy.
template <> void _STL::vector<char, _STL::allocator<char> >::resize(size_type);

namespace _STL { template <> BfmePod52 *vector<BfmePod52, allocator<BfmePod52> >::erase(BfmePod52 *, BfmePod52 *); }
template class _STL::vector<unsigned char, _STL::allocator<unsigned char> >;
template class _STL::vector<char, _STL::allocator<char > >;
template class _STL::vector<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::vector<BfmePod24, _STL::allocator<BfmePod24 > >;
template class _STL::vector<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::vector<BfmePod32, _STL::allocator<BfmePod32 > >;
template void _STL::_Construct(BfmePod36 *, const BfmePod36 &);
template BfmePod36 *_STL::__uninitialized_fill_n(BfmePod36 *, size_t, const BfmePod36 &, const _STL::__false_type &);
template BfmePod36 *_STL::__uninitialized_copy(const BfmePod36 *, const BfmePod36 *, BfmePod36 *, const _STL::__false_type &);
template BfmePod36 *_STL::uninitialized_fill_n(BfmePod36 *, size_t, const BfmePod36 &);
template class _STL::vector<BfmePod40, _STL::allocator<BfmePod40 > >;
template class _STL::vector<BfmePod44, _STL::allocator<BfmePod44 > >;
template class _STL::vector<BfmePod48, _STL::allocator<BfmePod48 > >;
template class _STL::vector<BfmePod52, _STL::allocator<BfmePod52 > >;
// This size-only view retains allocation and plain assignment operations.
template class _STL::allocator<BfmePod60>;
template BfmePod60* _STL::__copy<BfmePod60*, BfmePod60*, int>(
    BfmePod60*, BfmePod60*, BfmePod60*, const _STL::random_access_iterator_tag&, int*);
template BfmePod60* _STL::__copy_backward<BfmePod60*, BfmePod60*, int>(
    BfmePod60*, BfmePod60*, BfmePod60*, const _STL::random_access_iterator_tag&, int*);
template void _STL::fill<BfmePod60*, BfmePod60>(BfmePod60*, BfmePod60*, const BfmePod60&);
template class _STL::vector<BfmePod68, _STL::allocator<BfmePod68 > >;
template class _STL::vector<BfmePod76, _STL::allocator<BfmePod76 > >;
template class _STL::vector<BfmePod80, _STL::allocator<BfmePod80 > >;
template class _STL::vector<BfmePod88, _STL::allocator<BfmePod88 > >;
template class _STL::vector<BfmePod92, _STL::allocator<BfmePod92 > >;
template class _STL::vector<BfmePod104, _STL::allocator<BfmePod104 > >;
template class _STL::vector<BfmePod128, _STL::allocator<BfmePod128 > >;
template class _STL::vector<BfmePod144, _STL::allocator<BfmePod144 > >;
template class _STL::vector<BfmePod148, _STL::allocator<BfmePod148 > >;
template class _STL::vector<BfmePod160, _STL::allocator<BfmePod160 > >;
template class _STL::vector<BfmePod172, _STL::allocator<BfmePod172 > >;
template class _STL::vector<BfmePod180, _STL::allocator<BfmePod180 > >;
template class _STL::vector<CreateAHeroManager::CreateAHeroSubClass, _STL::allocator<CreateAHeroManager::CreateAHeroSubClass > >;
template _STL::vector<BfmePod248>::vector(const _STL::vector<BfmePod248>&);
template void _STL::vector<BfmePod248>::push_back(const BfmePod248&);
template BfmePod248* _STL::__uninitialized_fill_n<BfmePod248*,unsigned int,BfmePod248>(BfmePod248*,unsigned int,const BfmePod248&,const _STL::__false_type&);
template _STL::vector<BfmePod252>::vector(const _STL::vector<BfmePod252>&);
template void _STL::vector<BfmePod252>::push_back(const BfmePod252&);
template BfmePod252* _STL::__uninitialized_fill_n<BfmePod252*,unsigned int,BfmePod252>(BfmePod252*,unsigned int,const BfmePod252&,const _STL::__false_type&);
// Only allocation and plain assignment are claimed for this size-only view.
template class _STL::allocator<BfmePod260>;
template BfmePod260* _STL::__copy<BfmePod260*, BfmePod260*, int>(
    BfmePod260*, BfmePod260*, BfmePod260*,
    const _STL::random_access_iterator_tag&, int*);
template class _STL::vector<BfmePod340, _STL::allocator<BfmePod340 > >;
// ??$__find@PAUBfmePod20@@U1@@_STL@@YAPAUBfmePod20@@PAU1@0ABU1@ABUrandom_access_iterator_tag@0@@Z @0x002194CC 118B
// Unrolled random-access __find over 20-byte elements comparing a[0]; caller
// 0x002198BE is the 27B find wrapper that becomes ready on landing.
template BfmePod20* _STL::__find(BfmePod20*, BfmePod20*, const BfmePod20&, const _STL::random_access_iterator_tag&);
// ??$find@PAUBfmePod20@@U1@@_STL@@YAPAUBfmePod20@@PAU1@0ABU1@@Z @0x002198AD 27B
// find wrapper over the rowed __find 0x002194CC via tag local; callers
// 0x0021EAA6 0x004EDD71.
template BfmePod20* _STL::find(BfmePod20*, BfmePod20*, const BfmePod20&);
// ??$__find@PAUBfmePod40@@U1@@_STL@@YAPAUBfmePod40@@PAU1@0ABU1@ABUrandom_access_iterator_tag@0@@Z @0x0040A68F 118B
// Unrolled random-access __find over 40-byte elements comparing a[0]; caller
// 0x0040A891 is the 27B find wrapper that becomes ready on landing.
template BfmePod40* _STL::__find(BfmePod40*, BfmePod40*, const BfmePod40&, const _STL::random_access_iterator_tag&);
// ??$find@PAUBfmePod40@@U1@@_STL@@YAPAUBfmePod40@@PAU1@0ABU1@@Z @0x0040A891 27B
// find wrapper over __find 0x0040A68F via tag local.
template BfmePod40* _STL::find(BfmePod40*, BfmePod40*, const BfmePod40&);
// ?rva0040AAD5@Rva0040AAD5@@QAEPAUBfmePod40@@H@Z @0x0040AAD5 35B
// Searches vector<BfmePod40> at +0xC by first-field key via rowed find
// 0x0040A891; caller 0x0040C0FE passes [edi] int key and tests for null.
class Rva0040AAD5 {
    int _pad[3];
    BfmePod40 *_first;
    BfmePod40 *_last;
public:
    BfmePod40 *rva0040AAD5(int key);
};
BfmePod40 *Rva0040AAD5::rva0040AAD5(int key)
{
    BfmePod40 *found = _STL::find(_first, _last, (const BfmePod40 &)key);
    return found == _last ? 0 : found;
}
// ??$__find@PAUBfmePod104@@U1@@_STL@@YAPAUBfmePod104@@PAU1@0ABU1@ABUrandom_access_iterator_tag@0@@Z @0x0040A705 118B
// Unrolled random-access __find over 104-byte elements comparing a[0]; stride
// 0x68 in retail; caller 0x0040A8AC is the 27B find wrapper it unlocks.
// ??$find@PAUBfmePod104@@U1@@_STL@@YAPAUBfmePod104@@PAU1@0ABU1@@Z @0x0040A8AC 27B
// find wrapper over __find 0x0040A705 via tag local.
template BfmePod104* _STL::find(BfmePod104*, BfmePod104*, const BfmePod104&);
