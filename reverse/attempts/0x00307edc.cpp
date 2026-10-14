// ?rva00307EDC@@YA_NPAVAsciiString@@PAURva00240000ByteVector@@@Z
// partial score=0.69 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfmealloc
// stlport
// ?rva00307EDC@@YA_NPAVAsciiString@@PAURva00240000ByteVector@@@Z @0x00307EDC
// 372B, retail-guided: open the file, read its bytes into a temp vector, run
// CompressionManager on compressed data, then swap into the out vector.
class AsciiString;
class File;
class FileSystem
{
public:
	File *openFile(const char *name, int mode, int flags);
};
extern FileSystem *TheFileSystem;

class File
{
public:
	virtual void v0();
	virtual void v1();
	virtual void close();
	virtual int read(void *buf, int size);
	virtual void v4();
	virtual void v5();
	virtual void v6();
	virtual void v7();
	virtual void v8();
	virtual void v9();
	virtual void v10();
	virtual int size();
};

class CompressionManager
{
public:
	static bool isDataCompressed(const void *data, int size);
	static int getUncompressedSize(const void *data, int size);
	static int decompressData(const void *src, int srcSize, void *dst, int dstSize);
};

struct Rva00240000ByteVector
{
	unsigned char *m_begin; // +0x00
	unsigned char *m_end;   // +0x04
	unsigned char *m_cap;   // +0x08
	~Rva00240000ByteVector();

	void rva0047FAEA();                            // default ctor
	void rva00707C43(unsigned int n);              // fill ctor
	void rva004826E3(unsigned int n, unsigned char val); // resize
	void rva007079C1(Rva00240000ByteVector &other);      // swap
};

bool rva00307EDC(AsciiString *path, Rva00240000ByteVector *out)
{
	Rva00240000ByteVector tmp;
	tmp.rva0047FAEA();
	const char *name = (*(char **)path) ? (const char *)((char *)(*(char **)path) + 8) : (const char *)0x00BBAC1C;
	File *f = TheFileSystem->openFile(name, 0x141, 0);
	if (!f)
		return false;
	int size = f->size();
	if (size <= 0)
	{
		f->close();
		return false;
	}
	tmp.rva004826E3(size, 0);
	unsigned char *buf = tmp.m_begin;
	if (f->read(buf, size) != size)
	{
		f->close();
		return false;
	}
	f->close();
	if (CompressionManager::isDataCompressed(buf, size))
	{
		int usize = CompressionManager::getUncompressedSize(buf, size);
		Rva00240000ByteVector tmp2;
		tmp2.rva00707C43(usize);
		if (CompressionManager::decompressData(buf, size, tmp2.m_begin, usize) == usize)
			tmp.rva007079C1(tmp2);
	}
	out->rva007079C1(tmp);
	return true;
}
