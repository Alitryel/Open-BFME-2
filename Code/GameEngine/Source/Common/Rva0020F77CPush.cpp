// cl: /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva0020F77C@Rva0020F77C@@QAEXPAVObjectCreationNugget@@@Z @0x0020F77C 25B.
// Vector push-back through the ICF-shared ObjectCreationNugget* push_back
// at 0x004DFCB0 (pinned): the int/pointer param is copied to a same-slot
// temporary (the redundant mov pair retail keeps) whose address feeds the
// by-ref push into the vector at this+0x5C. Strict holder type unproven;
// the nugget spelling is for the shared worker.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>

class ObjectCreationNugget;

class Rva0020F77C
{
public:
	void rva0020F77C(ObjectCreationNugget *x);
private:
	char m_pad00[0x5C];
	_STL::vector<ObjectCreationNugget *> m_vec5C;
};

// bfme link decl-only begin
namespace _STL { template <> void vector<ObjectCreationNugget *,_STL::allocator<ObjectCreationNugget *> >::_M_clear(); }
namespace _STL { template <> void vector<ObjectCreationNugget *,_STL::allocator<ObjectCreationNugget *> >::_M_insert_overflow(ObjectCreationNugget * *,ObjectCreationNugget * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> ObjectCreationNugget * * _STLP_alloc_proxy<ObjectCreationNugget * *,ObjectCreationNugget *,_STL::allocator<ObjectCreationNugget *> >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> ObjectCreationNugget * * allocator<ObjectCreationNugget *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<ObjectCreationNugget * *,ObjectCreationNugget *,_STL::allocator<ObjectCreationNugget *> >::deallocate(ObjectCreationNugget * *,unsigned int); }
namespace _STL { template <> void __node_alloc<1,0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<ObjectCreationNugget *>::deallocate(ObjectCreationNugget * *,unsigned int) const; }
namespace _STL { template <> void vector<ObjectCreationNugget *,_STL::allocator<ObjectCreationNugget *> >::push_back(ObjectCreationNugget * const &); }
// bfme link decl-only end
void Rva0020F77C::rva0020F77C(ObjectCreationNugget *x)
{
	ObjectCreationNugget *y = x;
	m_vec5C.push_back(y);
}
