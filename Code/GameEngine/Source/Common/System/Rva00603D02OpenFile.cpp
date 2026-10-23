// cl: /O1 /G7 /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii
//
// Rva00603C0F::rva00603D02, retail 0x00603D02 (334 B). Opens a file out of the archive file system:
// copies and normalizes the name (rowed 0x00605365), looks the entry up in the two-level table
// (rowed 0x00603C0F on this), creates a RAMFile (or a StreamingArchiveFile when the access has the
// streaming bit) flagged delete-on-close, and fills it from the archive's File under that File's
// lock via RAMFile::openFromArchive (slot 18) at entry offset + the optional range offset for the
// range length (the entry size when zero); with write access the data is copied to a file opened
// through TheArchiveFileSystem (slot 3) and the RAMFile is closed. BFME1's Win32BIGFile::openFile
// (Win32BIGFileOpenArchived.cpp) is the structural donor; BFME2 takes the range through a pointer
// and normalizes the name first. Evidence: target bytes and the donor; class names stay address-derived.
#include "ascii_string.h"

typedef bool Bool;
extern "C" char *__cdecl strcpy(char *, const char *);

class File
{
public:
	enum { READ = 0x01, WRITE = 0x02, TEXT = 0x20, BINARY = 0x40, STREAMING = 0x100 };

	virtual ~File();
	virtual Bool open(const char *filename, int access);
	virtual void close(void);
	virtual int read(void *buffer, int bytes);
	virtual int write(const void *buffer, int bytes);
	virtual int seek(int bytes, int mode);
	virtual void nextLine(char *buf, int bufSize);
	virtual Bool scanInt(int &newInt);
	virtual Bool scanReal(float &newReal);
	virtual Bool scanString(AsciiString &newString);
	virtual Bool print(const char *format, ...);
	virtual int size(void);
	virtual int position(void);
	virtual char *readEntireAndClose(void);
	virtual File *convertToRAMFile(void);
	virtual void lock(void);
	virtual void unlock(void);

	void deleteOnClose(void) { m_deleteOnClose = true; }

protected:
	char m_head[0x09];
	Bool m_deleteOnClose;
	char m_tail[0x06];
};

class RAMFile : public File
{
public:
	RAMFile();
	virtual void reserved17(void);
	virtual Bool openFromArchive(File *archiveFile, const AsciiString &filename, int offset, int size);
	virtual Bool copyDataToFile(File *localFile);
protected:
	char m_ramFileFields[0x0c];
};

class StreamingArchiveFile : public RAMFile
{
public:
	StreamingArchiveFile();
protected:
	char m_streamingFields[0x0c];
};

class ArchiveFileSystem
{
public:
	virtual ~ArchiveFileSystem();
	virtual void A1();
	virtual void A2();
	virtual File *openFile(const char *filename, int access, int unk);
};
extern ArchiveFileSystem *TheArchiveFileSystem;

struct Rva00603D02Range
{
	int offset;
	int length;
};

struct Rva00603D02Entry
{
	File *archive;
	int offset;
	int size;
};

char *__cdecl Rva00605365(char *path);	// rowed 0x00605365

class Rva00603C0F
{
public:
	const void *rva00603C0F(const char *path, const char *normalized);	// rowed 0x00603C0F
	File *rva00603D02(const char *filename, int access, const Rva00603D02Range *range);
};

File *Rva00603C0F::rva00603D02(const char *filename, int access, const Rva00603D02Range *range)
{
	char path[260];
	strcpy(path, filename);
	const char *normalized = Rva00605365(path);
	const Rva00603D02Entry *entry = (const Rva00603D02Entry *)rva00603C0F(path, normalized);
	if (entry == 0)
		return 0;

	int rangeOffset = 0;
	int length = 0;
	if (range)
	{
		rangeOffset = range->offset;
		length = range->length;
	}

	RAMFile *entryFile;
	if (access & File::STREAMING)
		entryFile = new StreamingArchiveFile;
	else
		entryFile = new RAMFile;

	entryFile->deleteOnClose();
	entry->archive->lock();
	if (length == 0)
		length = entry->size;

	bool failed = !entryFile->openFromArchive(entry->archive, AsciiString(filename), entry->offset + rangeOffset, length);
	entry->archive->unlock();
	if (failed)
	{
		entryFile->close();
		return 0;
	}

	if ((access & File::WRITE) == 0)
		return entryFile;

	File *localFile = TheArchiveFileSystem->openFile(normalized, access, 0);
	if (localFile != 0)
		entryFile->copyDataToFile(localFile);
	entryFile->close();
	return localFile;
}
