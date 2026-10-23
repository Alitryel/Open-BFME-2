// cl: /Ireference/shims/bfme2_ascii /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??4?$vector@UFileInfoStruct@MixFileCreator@@V?$allocator@UFileInfoStruct@MixFileCreator@@@_STL@@@_STL@@QAEAAV01@ABV01@@Z @0x0006454B 186B: vector FileInfoStruct assign via allocate_and_copy 0x64432 plus destroy-free 0x21887C plus copy 0x4F4F8 plus destroy 0x217B1E plus uninitialized_copy 0x642AF. Evidence: same 3-path 186B shape as BfmeRecord assign 0x0040B61A; sar 4 stride 16 throughout; chain from 0x0021887C; caller 0x00064605.
#include "ascii_string.h"

class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		FileInfoStruct();
		FileInfoStruct(const FileInfoStruct &src);
		FileInfoStruct &operator=(const FileInfoStruct &src);
		unsigned long CRC;
		unsigned long Offset;
		unsigned long Size;
		AsciiString Filename;
	};
};

struct GeometryRecord;

class Rva0021887C
{
public:
	void rva0021887C();
private:
	GeometryRecord *m_first;
	GeometryRecord *m_last;
};

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
	size_type size() const { return size_type(m_finish - m_start); }
	size_type capacity() const { return size_type(m_endOfStorage - m_start); }
protected:
	template <class ForwardIter>
	pointer _M_allocate_and_copy(size_type n, ForwardIter first, ForwardIter last);
private:
	pointer m_start;
	pointer m_finish;
	pointer m_endOfStorage;
};

template <class InputIter, class OutputIter>
OutputIter __copy_ptrs(InputIter first, InputIter last, OutputIter result, const __false_type &tag);

template <class InputIter, class OutputIter>
OutputIter __uninitialized_copy(InputIter first, InputIter last, OutputIter result, const __false_type &tag);

template <class ForwardIter>
void _Destroy(ForwardIter first, ForwardIter last);
}

inline _STL::vector<MixFileCreator::FileInfoStruct, _STL::allocator<MixFileCreator::FileInfoStruct> > &_STL::vector<MixFileCreator::FileInfoStruct, _STL::allocator<MixFileCreator::FileInfoStruct> >::operator=(const vector &x)
{
	if (&x != this)
	{
		size_type xsize = x.size();
		if (xsize > capacity())
		{
			pointer tmp = _M_allocate_and_copy(xsize, x.m_start, x.m_finish);
			reinterpret_cast<Rva0021887C *>(this)->rva0021887C();
			m_start = tmp;
			m_endOfStorage = tmp + xsize;
		}
		else if (size() >= xsize)
		{
			GeometryRecord *new_finish = _STL::__copy_ptrs(const_cast<GeometryRecord *>(reinterpret_cast<const GeometryRecord *>(x.begin())), const_cast<GeometryRecord *>(reinterpret_cast<const GeometryRecord *>(x.end())), reinterpret_cast<GeometryRecord *>(m_start), _STL::__false_type());
			_STL::_Destroy(new_finish, reinterpret_cast<GeometryRecord *>(m_finish));
		}
		else
		{
			_STL::__copy_ptrs(const_cast<GeometryRecord *>(reinterpret_cast<const GeometryRecord *>(x.begin())), const_cast<GeometryRecord *>(reinterpret_cast<const GeometryRecord *>(x.begin() + size())), reinterpret_cast<GeometryRecord *>(m_start), _STL::__false_type());
			_STL::__uninitialized_copy(x.m_start + size(), x.m_finish, m_finish, _STL::__false_type());
		}
		m_finish = m_start + xsize;
	}
	return *this;
}

// This vector assignment is a header inline in the copier unit; the anchor is not retail code.
typedef _STL::vector<MixFileCreator::FileInfoStruct,
		_STL::allocator<MixFileCreator::FileInfoStruct> > FileInfoVector;
#pragma inline_depth(0)
// ?_bfmeFileInfoVectorAssignInlineAnchor@@YAXXZ absent-from-retail
void _bfmeFileInfoVectorAssignInlineAnchor()
{
	FileInfoVector *vector = static_cast<FileInfoVector *>(0);
	*vector = *vector;
}
#pragma inline_depth()
