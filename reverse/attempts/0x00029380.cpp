// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z
// partial score=0.99473 date=2026-10-14
// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z
// partial score=0.96 date=2026-10-13
// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z
// partial score=0.96 date=2026-10-13
// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z
// partial score=0.96 date=2026-10-06
// cl: /Od /Ob1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Oy-
// stlport
// Current /Oy- lifetime variant reached permutation fitness 0.9014; the
// explain remains 270B versus 272B with its first residue at +0x96.
// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z 0x00029380 272 retail append(n,c); callers _M_xsputnc/bfmeAssign/bfmeResize; donor stlport-4.5.3
namespace _STL
{
struct __true_type {};
void __cdecl fill(char *first, char *last, const char &val);
template<class Size> inline char *fill_n(char *first,Size n,const char &value){fill(first,first+n,value);return first+n;}
template<class Iter,class Size,class T> inline Iter __uninitialized_fill_n(Iter first,Size n,const T &value,const __true_type &){return fill_n(first,n,value);}
template<class Iter,class Size,class T> inline Iter uninitialized_fill_n(Iter first,Size n,const T &value){return __uninitialized_fill_n(first,n,value,__true_type());}
template <class T>
class char_traits
{
public:
	static void __cdecl assign(char &a, const char &b);
};
template <class T>
class allocator
{
public:
	typedef unsigned int size_type;
};
template <class Pointer, class Value, class Alloc>
class _STLP_alloc_proxy : public Alloc
{
public:
	Pointer _M_data;
};
template<class CharT,class Alloc> class _String_base {
public: void _M_throw_length_error() const;
};
template <class CharT, class Traits, class Alloc>
class basic_string : public _String_base<CharT,Alloc>
{
public:
	typedef unsigned int size_type;
	typedef CharT *pointer;
	void reserve(size_type count);
	size_type capacity() const
	{
		return static_cast<size_type>(_M_end_of_storage._M_data - _M_start) - 1;
	}
	size_type size() const
	{
		return static_cast<size_type>(_M_finish - _M_start);
	}
	size_type max_size() const
	{
		return size_type(-2);
	}
	// ?append@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV12@ID@Z present-unmatched
	basic_string &append(size_type n, CharT c);
private:
	void _M_construct_null_aux(pointer p,const __true_type &) { *p=0; }
	void _M_construct_null(pointer p){_M_construct_null_aux(p,__true_type());}
	pointer end(){return _M_finish;}
	CharT *_M_start;
	CharT *_M_finish;
	_STLP_alloc_proxy<CharT *, CharT, Alloc> _M_end_of_storage;
};
}
template <class CharT, class Traits, class Alloc>
_STL::basic_string<CharT, Traits, Alloc> &
_STL::basic_string<CharT, Traits, Alloc>::append(size_type n, CharT c)
{
	if (n > max_size() || size() > max_size() - n)
		this->_M_throw_length_error();
	if (size() + n > capacity())
	{
		const size_type *p;
		size_type old = size();
		p = old < n ? &n : &old;
		reserve(size() + *p);
	}
	if (n > 0)
	{
        _STL::uninitialized_fill_n(_M_finish+1,n-1,c);
        _M_construct_null(_M_finish+n);
        Traits::assign(*end(),c);
        _M_finish+=n;
	}
	return *this;
}
template _STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > &
_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> >::append(unsigned int, char);
