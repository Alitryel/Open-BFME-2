// ?rva00307EDC@@YA_NPAVAsciiString@@PAURva00240000ByteVector@@@Z
// partial score=0.935 date=2026-10-17
// ?rva00307EDC@@YA_NPAVAsciiString@@PAURva00240000ByteVector@@@Z
// partial score=0.86 date=2026-10-15
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
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
#include <vector>
#include "ascii_string.h"

// game.dat's STLport passes vector<char>::resize's fill by value (the rowed
// 0x000826E3 body; the call site pushes the byte itself), so this unit
// specializes vector<char> to that interface. The count constructor and
// resize are the rowed out-of-line bodies; swap is STLport's inline one.
namespace _STL
{
template <>
class vector<char, allocator<char> > : public _Vector_base<char, allocator<char> >
{
public:
	typedef allocator<char> allocator_type;
	typedef unsigned int size_type;

	explicit vector(const allocator_type &a = allocator_type()) : _Vector_base<char, allocator<char> >(a) {}
	explicit vector(size_type n) : _Vector_base<char, allocator<char> >(n, allocator_type())
	{
		this->_M_finish = uninitialized_fill_n(this->_M_start, n, char());
	}

	char *begin() { return this->_M_start; }
	char *end() { return this->_M_finish; }
	size_type size() const { return size_type(this->_M_finish - this->_M_start); }
	char *erase(char *first, char *last);
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

bool rva00307EDC(AsciiString *path, Rva00240000ByteVector *data)
{
	std::vector<char> bytes;
	int size;
	char *buffer;
	{
		File *opened = TheFileSystem->openFile(path->str(), 0x141, 0);
		Rva00307EDCFileCloser file(opened);
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
		if (CompressionManager::decompressData(buffer, size, &uncompressed[0], uncompressedSize) == 0)
			return false;
		if (CompressionManager::decompressData(buffer, size, &uncompressed[0], uncompressedSize) == uncompressedSize)
			bytes.swap(uncompressed);
	}

	data->swap(bytes);
	return true;
}
