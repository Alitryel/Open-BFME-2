// cl: /Ireference/shims/bfme2_ascii /MD
// Candidate identity ?getFileInfo@FileSystem@@QBE_NABVAsciiString@@PAUFileInfo@@@Z
// @0x00077BF8 33B. The 0x77D0F caller loads TheFileSystem into ECX and passes
// an AsciiString plus its FileInfo output. The target body extracts the string
// and forwards both arguments, ECX unchanged, to the const char * overload at
// 0x00600E3A.
#include "ascii_string.h"
struct FileInfo;
class FileSystem
{
public:
	bool getFileInfo(const AsciiString &filename, FileInfo *fileInfo) const;
	bool getFileInfo(const char *filename, FileInfo *fileInfo) const;
};

bool FileSystem::getFileInfo(const AsciiString &a, FileInfo *b) const
{
	return getFileInfo(a.str(), b);
}

// Legacy separately rowed 17-byte catch at 0x00077CFE. Its immediate is
// the native continuation VA. The sibling catch at 0x00077F5E belongs
// inside Rva00077E05Load and is emitted by its actual C++ try/catch.
extern "C" __declspec(dllimport) void __stdcall OutputDebugStringA( const char *text );

int Rva00077CFE()
{
	OutputDebugStringA( "Error opening file \n" );
	return 0x00477CE6;
}
