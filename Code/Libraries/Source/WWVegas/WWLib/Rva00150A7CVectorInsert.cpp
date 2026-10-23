// cl: /O1 /G7 /MD /EHsc
// Reference: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d,
// inputs/vendor/stlport/stl/_vector.h: vector::insert(iterator,size_type,const T&).
// The complete native five-byte entry at RVA 0x00150A7C tail-calls the
// independently rowed same-instantiation _M_fill_insert at 0x0015079D.
// This ABI-only template view needs no vector layout or element fields;
// retain the existing element identity, which is address-derived where named so.
struct Rva0015079DElement;
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
template void _STL::vector<Rva0015079DElement,_STL::allocator<Rva0015079DElement> >::insert(Rva0015079DElement*,unsigned,const Rva0015079DElement&);
