// cl: /O1 /G7 /MD /EHsc
// Reference: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d,
// inputs/vendor/stlport/stl/_vector.h: vector::insert(iterator,size_type,const T&).
// The complete native five-byte entry at RVA 0x000B0657 tail-calls the
// independently rowed same-instantiation _M_fill_insert at 0x000B0478.
// This ABI-only template view needs no vector layout or element fields;
// retain the existing element identity, which is address-derived where named so.
struct BfmePod36;
namespace _STL {
template<class T> class allocator;
template<class T,class Alloc> class vector {
public:
    void _M_fill_insert(T *position,unsigned count,const T &value);
    void insert(T *position,unsigned count,const T &value) {
        _M_fill_insert(position,count,value);
    }
};
}
template void _STL::vector<BfmePod36,_STL::allocator<BfmePod36> >::insert(BfmePod36*,unsigned,const BfmePod36&);
