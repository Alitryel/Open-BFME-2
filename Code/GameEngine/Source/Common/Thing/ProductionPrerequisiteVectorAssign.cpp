// cl: /O1 /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@VProductionPrerequisite@@V?$allocator@VProductionPrerequisite@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x002D1033 206B: vector ProductionPrerequisite assign via allocate_and_copy 0x002D0F09 plus clear 0x002D02DF plus CopyRange 0x002D0F36 plus Destroy 0x002CFBAE plus uninitialized_copy 0x0033E0B7. Evidence: chain lane calls rowed CopyRange forwarder; same 3-path shape as StringRecord assign 0x002D0726 with idiv 0x24 stride.
class ProductionPrerequisite
{
public:
	ProductionPrerequisite();
	ProductionPrerequisite(const ProductionPrerequisite &other);
	~ProductionPrerequisite();
	ProductionPrerequisite &operator=(const ProductionPrerequisite &other);
private:
	void *m_unreconstructed[9];
};

typedef char ProductionPrerequisiteSizeCheck[sizeof(ProductionPrerequisite) == 0x24 ? 1 : -1];

ProductionPrerequisite *Rva002D0F36CopyRange(ProductionPrerequisite *first, ProductionPrerequisite *last, ProductionPrerequisite *result, int dummy);
void __cdecl dup_002cfbae(void);
void __cdecl dup_0033e0b7(void);

namespace _STL
{
struct __false_type
{
	__false_type()
	{
	}
};
template <class Type>
class allocator
{
};
template <class Type, class Allocator>
class vector
{
public:
	typedef Type *pointer;
	typedef const Type *const_pointer;
	typedef unsigned int size_type;
	vector &operator=(const vector &x);
	pointer begin() { return m_start; }
	const_pointer begin() const { return m_start; }
	pointer end() { return m_finish; }
	const_pointer end() const { return m_finish; }
	// Out-of-line size is owned by the rowed ThingFactory.cpp instantiation.
	__declspec(dllimport) __forceinline size_type size() const { return size_type(m_finish - m_start); }
	size_type capacity() const { return size_type(m_endOfStorage - m_start); }
protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
	void _M_clear();
private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};
}

typedef void (__cdecl *PrereqDestroyFn)(ProductionPrerequisite *, ProductionPrerequisite *);
typedef ProductionPrerequisite *(__cdecl *PrereqUninitFn)(ProductionPrerequisite *, ProductionPrerequisite *, ProductionPrerequisite *, const _STL::__false_type &);

inline _STL::vector<ProductionPrerequisite, _STL::allocator<ProductionPrerequisite> > &_STL::vector<ProductionPrerequisite, _STL::allocator<ProductionPrerequisite> >::operator=(const vector &x)
{
	if (&x != this)
	{
		size_type xsize = x.size();
		_STL::__false_type tag;
		if (xsize > capacity())
		{
			pointer tmp = _M_allocate_and_copy(xsize, const_cast<pointer>(x.begin()), const_cast<pointer>(x.end()));
			_M_clear();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			pointer new_finish = Rva002D0F36CopyRange(const_cast<pointer>(x.begin()), const_cast<pointer>(x.end()), m_start, (int)((char *)&tag + 3));
			((PrereqDestroyFn)&dup_002cfbae)(new_finish, m_finish);
		}
		else
		{
			Rva002D0F36CopyRange(const_cast<pointer>(x.begin()), const_cast<pointer>(x.begin() + size()), m_start, (int)((char *)&tag + 3));
			((PrereqUninitFn)&dup_0033e0b7)(const_cast<pointer>(x.begin() + size()), const_cast<pointer>(x.end()), m_finish, *(_STL::__false_type *)((char *)&tag + 3));
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// operator= is a header inline in STLport (another unit emits a select-any
// copy), so a strong definition here was a duplicate in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is
// not retail code.
#pragma inline_depth(0)
// ?bfmeEmitProductionPrerequisiteVectorAssign@@YAXPAV?$vector@VProductionPrerequisite@@V?$allocator@VProductionPrerequisite@@@_STL@@@_STL@@ABV12@@Z present-unmatched
void bfmeEmitProductionPrerequisiteVectorAssign(_STL::vector<ProductionPrerequisite, _STL::allocator<ProductionPrerequisite> > *p, const _STL::vector<ProductionPrerequisite, _STL::allocator<ProductionPrerequisite> > &x)
{
	*p = x;
}
#pragma inline_depth()
