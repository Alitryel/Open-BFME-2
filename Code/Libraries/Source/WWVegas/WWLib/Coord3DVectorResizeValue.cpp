// cl: /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// Retail evidence: 0x000CA2F3 is the 73-byte vector<Coord3D> two-argument
// resize body. Its identity is supported by the rowed one-argument forwarder
// at 0x000CA33C and the direct DockUpdate call. The body calls rowed 12-byte
// range erase 0x002A133B and the rowed fill insertion at 0x000CA1EE decoded
// from its REL32; both are called by their row names (the Coord3D erase name
// rows the distinct body at 0x00081A24). Coord3D uses the existing three-float
// codegen view; the body proves stride and calls, not the target's complete
// source layout.
#include "../../../Include/Lib/Coord3D.h"
struct Gen_p12pod;
class Rva000CA1EEVector {
public:
	void fillInsert(Coord3D *position, unsigned int count, const Coord3D &value);
};
namespace _STL {
template <class T> class allocator {};
template <class T, class A = allocator<T> > class vector {
public:
	typedef unsigned int size_type;
	typedef T *iterator;
	iterator erase(iterator first, iterator last);
	void resize(size_type n, T value) {
		T *start = _M_start;
		T *finish = _M_finish;
		const size_type size = (size_type)(finish - start);
		if (n < size) {
			((vector<Gen_p12pod> *)this)->erase((Gen_p12pod *)(start + n), (Gen_p12pod *)finish);
		} else {
			((Rva000CA1EEVector *)this)->fillInsert(_M_finish, n - (size_type)(_M_finish - start), value);
		}
	}
private:
	T *_M_start;
	T *_M_finish;
	T *_M_end;
};
template void vector<Coord3D, allocator<Coord3D> >::resize(unsigned int, Coord3D);
}
