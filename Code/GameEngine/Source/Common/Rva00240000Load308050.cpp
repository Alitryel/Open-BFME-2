// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?rva00307EDC@@YA_NPAVAsciiString@@PAURva00240000ByteVector@@@Z, retail
// 0x00307EDC (372B, cdecl). Reads a whole file into a byte vector: open it
// through TheFileSystem (access 0x141), size it, read it into a local
// vector<char>, and when CompressionManager reports the data compressed,
// decompress into a second vector and swap that in. The result is swapped
// into the caller's vector (the +4 vector of the 0x00240000 stream, whose
// load member 0x00308050 is the caller and owns this spelling).
//
// Evidence (target): the File virtual slots used (size +0x2C, read +0x0C,
// close +0x08 -- Zero Hour's file.h slot order), the openFile call with
// (name, 0x141, 0), the rowed vector<char> resize 0x000826E3 and count ctor
// 0x00307C43, the rowed CompressionManager statics, and the out-of-line
// _Vector_base ctor 0x0007FAEA and swap 0x003079C1 (ICF-shared bodies).
// The loader's original name is unknown; the name stays address-derived.
#include <stl/_algobase.h>
namespace _STL { static inline const unsigned int &max(const unsigned int &a, const unsigned int &b) { return a < b ? b : a; } }
#include <vector>
#include "ascii_string.h"
namespace _STL { extern template char *fill_n<unsigned int>(char *, unsigned int, const char &); }
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *p, size_t n) { allocator<char>::deallocate(p,n); } }


// game.dat's STLport passes vector<char>::resize's fill by value (the rowed
// 0x000826E3 body; the call site pushes the byte itself), so this unit
// specializes vector<char> to that interface. The count constructor and
// resize are the rowed out-of-line bodies; swap is STLport's inline one.
// The members resize reaches keep STLport 4.5.3's bodies, so the compiler
// sees that the vector's address is not retained across the file calls.
namespace _STL
{
template <>
class vector<char, allocator<char> > : public _Vector_base<char, allocator<char> >
{
public:
	typedef allocator<char> allocator_type;
	typedef unsigned int size_type;

	explicit vector(const allocator_type &a = allocator_type()) : _Vector_base<char, allocator<char> >(a) {}
	explicit vector(size_type n);

	char *begin() { return this->_M_start; }
	char *end() { return this->_M_finish; }
	size_type size() const { return size_type(this->_M_finish - this->_M_start); }
	char *erase(char *first, char *last)
	{
		char *i = __copy_ptrs(last, this->_M_finish, first, __true_type());
		_Destroy(i, this->_M_finish);
		this->_M_finish = i;
		return first;
	}
	void _M_clear()
	{
		_Destroy(this->_M_start, this->_M_finish);
		this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
	}
	void _M_set(char *s, char *f, char *e)
	{
		this->_M_start = s;
		this->_M_finish = f;
		this->_M_end_of_storage._M_data = e;
	}
	void _M_insert_overflow(char *position, const char &x, const __true_type &, size_type fillLen, bool atEnd = false)
	{
		const size_type oldSize = size();
		const size_type len = oldSize + (max)(oldSize, fillLen);
		char *newStart = this->_M_end_of_storage.allocate(len);
		char *newFinish = (char *)__copy_trivial(this->_M_start, position, newStart);
		newFinish = fill_n(newFinish, fillLen, x);
		if (!atEnd)
			newFinish = (char *)__copy_trivial(position, this->_M_finish, newFinish);
		_M_clear();
		_M_set(newStart, newFinish, newStart + len);
	}
	void _M_fill_insert(char *position, size_type n, const char &x);

	char &operator[](size_type n) { return this->_M_start[n]; }
	void resize(size_type newSize, char x)
	{
		if (newSize < size())
			erase(begin() + newSize, end());
		else
			_M_fill_insert(end(), newSize - size(), x);
	}
	void swap(vector<char, allocator<char> > &x)
	{
		_STLP_STD::swap(this->_M_start, x._M_start);
		_STLP_STD::swap(this->_M_finish, x._M_finish);
		_STLP_STD::swap(this->_M_end_of_storage, x._M_end_of_storage);
	}
};

inline void vector<char, allocator<char> >::_M_fill_insert(char *position, size_type n, const char &x)
{
	if (n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= n) {
			char xCopy = x;
			const size_type elemsAfter = this->_M_finish - position;
			char *oldFinish = this->_M_finish;
			if (elemsAfter > n) {
				__uninitialized_copy(this->_M_finish - n, this->_M_finish, this->_M_finish, __true_type());
				this->_M_finish += n;
				__copy_backward_ptrs(position, oldFinish - n, oldFinish, __true_type());
				_STLP_STD::fill(position, position + n, xCopy);
			} else {
				uninitialized_fill_n(this->_M_finish, n - elemsAfter, xCopy);
				this->_M_finish += n - elemsAfter;
				__uninitialized_copy(position, oldFinish, this->_M_finish, __true_type());
				this->_M_finish += elemsAfter;
				_STLP_STD::fill(position, oldFinish, xCopy);
			}
		} else
			_M_insert_overflow(position, x, __true_type(), n);
	}
}
}

class File
{
public:
	virtual ~File();
	virtual bool open(const char *filename, int access);
	virtual void close();
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, int mode);
	virtual bool nextLine(char *buf, int bufSize);
	virtual bool scanInt(int &newInt);
	virtual bool scanReal(float &newReal);
	virtual bool scanString(AsciiString &newString);
	virtual bool print(const char *format, ...);
	virtual int size();
};

class FileSystem
{
public:
	File *openFile(const char *filename, int access, int flags);
};

extern FileSystem *TheFileSystem;

class CompressionManager
{
public:
	static bool isDataCompressed(const void *mem, int len);
	static int getUncompressedSize(const void *mem, int len);
	static int decompressData(const void *src, int srcLen, void *dest, int destLen);
};

struct Rva00240000ByteVector : public std::vector<char>
{
};

// Closes the file when the read scope ends, on every path.
struct Rva00307EDCFileCloser
{
	Rva00307EDCFileCloser(File *file) : m_file(file) {}
	~Rva00307EDCFileCloser()
	{
		if (m_file != NULL)
			m_file->close();
	}
	File *m_file;
};

bool rva00307EDC(AsciiString *path, Rva00240000ByteVector *data);

class Rva00240000
{
public:
	bool rva00308050(AsciiString path);

private:
	const void *m_00;
	Rva00240000ByteVector m_04;
	const void *m_10;
	char *m_14;
	char *m_18;
	char *m_1C;
};

bool Rva00240000::rva00308050(AsciiString path)
{
	bool loaded = false;
	if (rva00307EDC(&path, &m_04))
	{
		char *end = m_04.begin() + m_04.size();
		m_14 = m_18 = m_04.begin();
		m_1C = end;
		loaded = true;
	}
	return loaded;
}

bool rva00307EDC(AsciiString *path, Rva00240000ByteVector *data)
{
	std::vector<char> bytes;
	int size;
	char *buffer;
	{
		Rva00307EDCFileCloser file(TheFileSystem->openFile(path->str(), 0x141, 0));
		if (file.m_file == NULL)
			return false;

		size = file.m_file->size();
		if (size <= 0)
			return false;

		bytes.resize(size, 0);
		buffer = &bytes[0];
		if (file.m_file->read(buffer, size) != size)
			return false;
	}

	if (CompressionManager::isDataCompressed(buffer, size))
	{
		int uncompressedSize = CompressionManager::getUncompressedSize(buffer, size);
		std::vector<char> uncompressed(uncompressedSize);
		int result = CompressionManager::decompressData(buffer, size, &uncompressed[0], uncompressedSize);
		if (result == 0)
			return false;
		if (result == uncompressedSize)
			bytes.swap(uncompressed);
	}

	data->swap(bytes);
	return true;
}
