// cl: /O1 /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// Tagged binary Xfer stream -> readable text dump at retail 0x0060DFB5 (4,377B),
// with file-static companions taggedPrint (0x0060D594, 68B) and taggedIndent
// (0x0060D5D8, 26B). Corroborated by WorldBuilder 0x0165F550.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;
typedef __int64 Int64;
typedef signed char Byte;
typedef unsigned char UnsignedByte;
typedef short Short;
typedef unsigned short UnsignedShort;
#define TRUE true
#define FALSE false

#include "ascii_string.h"
#include "unicode_string.h"
// stlport
#include <stdlib.h>
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <string>
#include <vector>
#undef free
#include <stdarg.h>
#include <string.h>

extern "C" __declspec(dllimport) int __cdecl _vsnprintf(char *, unsigned int, const char *, va_list);
#pragma function(strlen)

class File
{
public:
	virtual ~File();
	virtual Bool open(const char *name, Int access);
	virtual void close();
	virtual Int read(void *buffer, Int bytes);
	virtual Int write(const void *buffer, Int bytes);
	virtual Int seek(Int bytes, Int mode);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException();
	char *text;
	int tagValue;
};

static __declspec(noinline) void taggedPrint(File *output, const char *format, ...)
{
	char buffer[1024];
	va_list args;
	va_start(args, format);
	_vsnprintf(buffer, sizeof(buffer), format, args);
	va_end(args);
	output->write(buffer, strlen(buffer));
}

static __declspec(noinline) void taggedIndent(File *output, Int depth)
{
	while (depth-- != 0)
		output->write("\t", 1);
}

Bool Rva0060DFB5(File *input, File *output)
{
	Int enumFour;
	UnsignedInt magic;
	UnsignedInt streamVersion;
	UnsignedInt options;
	UnsignedInt flags;

	if (input->read(&magic, 4) != 4)
		return FALSE;
	if (input->read(&streamVersion, 4) != 4)
		return FALSE;
	if (magic != 'EALA' || (streamVersion != 'RTS1' && streamVersion != 'RTS2'))
		return FALSE;
	options = 0;
	if (streamVersion != 'RTS1')
		input->read(&options, 4);
	if (input->read(&flags, 4) != 4 || (flags & 1) == 0)
		return FALSE;

	std::vector<std::string> blocks;
	std::vector<std::string> names;
	UnsignedInt type;
	Bool afterBlock = FALSE;

	for (;;)
	{
		if (input->read(&type, 4) != 4)
			throw XferException(1, 0);
		if (type == 'END')
			return TRUE;
		switch (type)
		{
			case 'c2d':
			{
				Real v[2];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "x:%1.6f,y:%1.6f (0xX:%08x,0xY:%08x) [coord2d]\n",
					v[0], v[1], *(UnsignedInt *)&v[0], *(UnsignedInt *)&v[1]);
				afterBlock = FALSE;
				break;
			}
			case 'c3d':
			{
				Real v[3];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				input->read(&v[2], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "x:%1.6f,y:%1.6f,z:%1.6f (HexX:%08x,HexY:%08x,HexZ:%08x) [coord3d]\n",
					v[0], v[1], v[2], *(UnsignedInt *)&v[0], *(UnsignedInt *)&v[1], *(UnsignedInt *)&v[2]);
				afterBlock = FALSE;
				break;
			}
			case 'i64':
			{
				Int64 v;
				input->read(&v, 8);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%I64i=0x%I64x [int64]\n", v, v);
				afterBlock = FALSE;
				break;
			}
			case 'int':
			{
				Int v;
				input->read(&v, 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i=0x%x [int]\n", v, v);
				afterBlock = FALSE;
				break;
			}
			case 'r2d':
			{
				Real v[4];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				input->read(&v[2], 4);
				input->read(&v[3], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "x:%1.6f,y:%1.6f to x:%1.6f,y:%1.6f (0xX:%08x,0xY:%08x to 0xX:%08x,0xY:%08x) [region2d]\n",
					v[0], v[1], v[2], v[3], *(UnsignedInt *)&v[0], *(UnsignedInt *)&v[1], *(UnsignedInt *)&v[2], *(UnsignedInt *)&v[3]);
				afterBlock = FALSE;
				break;
			}
			case 'r3d':
			{
				Real v[6];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				input->read(&v[2], 4);
				input->read(&v[3], 4);
				input->read(&v[4], 4);
				input->read(&v[5], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "x:%1.6f,y:%1.6f,z:%1.6f to x:%1.6f,y:%1.6f,z:%1.6f (0xX:%08x,0xY:%08x,0xZ:%08x to 0xX:%08x,0xY:%08x,0xZ:%08x) [region3d]\n",
					v[0], v[1], v[2], v[3], v[4], v[5], *(UnsignedInt *)&v[0], *(UnsignedInt *)&v[1], *(UnsignedInt *)&v[2], *(UnsignedInt *)&v[3], *(UnsignedInt *)&v[4], *(UnsignedInt *)&v[5]);
				afterBlock = FALSE;
				break;
			}
			case 'raw':
			{
				if (afterBlock)
				{
					taggedPrint(output, "\n");
					afterBlock = FALSE;
				}
				UnsignedInt len;
				input->read(&len, 4);
				if (len == 0)
				{
					taggedIndent(output, blocks.size());
					taggedPrint(output, "--- 0 raw bytes\n");
					break;
				}
				Byte buffer[16];
				UnsignedInt limit = 16;
				for (UnsignedInt at = 0; at < len; at += 16, limit += 16)
				{
					UnsignedInt count = limit <= len ? 16 : len - at;
					input->read(buffer, count);
					taggedIndent(output, blocks.size());
					taggedPrint(output, "%04x", at);
					for (UnsignedInt i = 0; i < 16; ++i)
					{
						if ((i & 7) == 0)
							taggedPrint(output, " ");
						if (at + i < len)
							taggedPrint(output, " %02x", (UnsignedByte)buffer[i]);
						else
							taggedPrint(output, "   ");
					}
					taggedPrint(output, "  ");
					for (UnsignedInt i = 0; i < 16; ++i)
					{
						if (at + i >= len)
							break;
						taggedPrint(output, "%c", (UnsignedByte)buffer[i] > 0x20 ? (UnsignedByte)buffer[i] : '.');
					}
					taggedPrint(output, "\n");
				}
				break;
			}
			case 'rgb':
			{
				Real v[3];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				input->read(&v[2], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "r:%1.3f,g:%1.3f,b:%1.3f (0xR:%08x,0xG:%08x,0xB:%08x) [rgb]\n",
					v[0], v[1], v[2], *(UnsignedInt *)&v[0], *(UnsignedInt *)&v[1], *(UnsignedInt *)&v[2]);
				afterBlock = FALSE;
				break;
			}
			case 'ver':
			{
				UnsignedByte v;
				input->read(&v, 1);
				taggedIndent(output, blocks.size());
				taggedPrint(output, "version: %i\n", (UnsignedInt)v);
				afterBlock = FALSE;
				break;
			}
			case 'BLOK':
			case 'DSCR':
			{
				UnsignedByte len;
				if (input->read(&len, 1) != 1)
					throw XferException(1, 0);
				char name[256];
				if (len == 0)
				{
					name[0] = 0;
				}
				else if (len == 0xff)
				{
					UnsignedInt index;
					if (input->read(&index, 4) != 4)
						throw XferException(1, 0);
					if (index >= names.size())
						throw XferException(0, 0);
					strcpy(name, names[index].c_str());
				}
				else
				{
					if (input->read(name, len) != len)
						throw XferException(1, 0);
					name[len] = 0;
					std::string value(name);
					names.push_back(value);
				}
				if (type == 'BLOK')
					input->seek(4, 1);
				if (type == 'BLOK' || !afterBlock)
					taggedIndent(output, blocks.size());
				if (type == 'BLOK')
				{
					taggedPrint(output, "<%s>\n", name);
					std::string value(name);
					blocks.push_back(value);
				}
				else
				{
					taggedPrint(output, "%s: ", name);
					afterBlock = TRUE;
				}
				break;
			}
			case 'EBLK':
			{
				if (blocks.empty())
					throw XferException(0, 0);
				taggedIndent(output, blocks.size() - 1);
				taggedPrint(output, "</%s>\n", blocks.back().c_str());
				blocks.pop_back();
				break;
			}
			case 'astr':
			{
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				UnsignedInt len = 0;
				input->read(&len, 1);
				if (len == 0xff)
					input->read(&len, 4);
				AsciiString buffer;
				if (len != 0)
				{
					input->read(reinterpret_cast<StringBase<char> *>(&buffer)->getBufferForRead(len), len);
					reinterpret_cast<StringBase<char> *>(&buffer)->getBufferForRead(len)[len] = 0;
				}
				taggedPrint(output, "'%s' [ascii]\n", buffer.str());
				afterBlock = FALSE;
				break;
			}
			case 'bool':
			{
				Bool v;
				input->read(&v, 1);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i [bool]\n", (Int)(UnsignedByte)v);
				afterBlock = FALSE;
				break;
			}
			case 'byte':
			{
				Byte v;
				input->read(&v, 1);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i=0x%x [byte]\n", (Int)v, (Int)v);
				afterBlock = FALSE;
				break;
			}
			case 'enu1':
			{
				UnsignedInt v = 0;
				input->read(&v, 1);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i [enum]\n", v);
				afterBlock = FALSE;
				break;
			}
			case 'enu2':
			{
				UnsignedInt v = 0;
				input->read(&v, 2);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i [enum]\n", v);
				afterBlock = FALSE;
				break;
			}
			case 'enu3':
			{
				UnsignedInt v = 0;
				input->read(&v, 3);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i [enum]\n", v);
				afterBlock = FALSE;
				break;
			}
			case 'enu4':
			{
				enumFour = 0;
				input->read(&enumFour, 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i [enum]\n", enumFour);
				afterBlock = FALSE;
				break;
			}
			case 'ic2d':
			{
				Int v[2];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "x:%i,y:%i [icoord2d]\n", v[0], v[1]);
				afterBlock = FALSE;
				break;
			}
			case 'ic3d':
			{
				Int v[3];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				input->read(&v[2], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "x:%i,y:%i,z:%i [icoord3d]\n", v[0], v[1], v[2]);
				afterBlock = FALSE;
				break;
			}
			case 'ir2d':
			{
				Int v[4];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				input->read(&v[2], 4);
				input->read(&v[3], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "x:%i,y:%i to x:%i,y:%i [iregion2d]\n", v[0], v[1], v[2], v[3]);
				afterBlock = FALSE;
				break;
			}
			case 'ir3d':
			{
				Int v[6];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				input->read(&v[2], 4);
				input->read(&v[3], 4);
				input->read(&v[4], 4);
				input->read(&v[5], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "x:%i,y:%i,z:%i to x:%i,y:%i,z:%i [iregion3d]\n", v[0], v[1], v[2], v[3], v[4], v[5]);
				afterBlock = FALSE;
				break;
			}
			case 'real':
			{
				Real v;
				input->read(&v, 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%1.6f (0x%08x) [float]\n", v, *(UnsignedInt *)&v);
				afterBlock = FALSE;
				break;
			}
			case 'rgbi':
			{
				Int v[4];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				input->read(&v[2], 4);
				input->read(&v[3], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "r:%i,g:%i,b:%i,a:%i [irgba]\n", v[0], v[1], v[2], v[3]);
				afterBlock = FALSE;
				break;
			}
			case 'rgbr':
			{
				Real v[4];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				input->read(&v[2], 4);
				input->read(&v[3], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "r:%1.3f,g:%1.3f,b:%1.3f,a:%1.3f (0xR:%08x,0xG:%08x,0xB:%08x,0xA:%08x) [rgba]\n",
					v[0], v[1], v[2], v[3], *(UnsignedInt *)&v[0], *(UnsignedInt *)&v[1], *(UnsignedInt *)&v[2], *(UnsignedInt *)&v[3]);
				afterBlock = FALSE;
				break;
			}
			case 'rnge':
			{
				Real v[2];
				input->read(&v[0], 4);
				input->read(&v[1], 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%1.6f to %1.6f (0x:%08x to 0x:%08x) [range]\n",
					v[0], v[1], *(UnsignedInt *)&v[0], *(UnsignedInt *)&v[1]);
				afterBlock = FALSE;
				break;
			}
			case 'shrt':
			{
				Short v;
				input->read(&v, 2);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i=0x%x [short]\n", (Int)v, (Int)v);
				afterBlock = FALSE;
				break;
			}
			case 'ubyt':
			{
				UnsignedByte v;
				input->read(&v, 1);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i=0x%x [ubyte]\n", (UnsignedInt)v, (UnsignedInt)v);
				afterBlock = FALSE;
				break;
			}
			case 'uint':
			{
				UnsignedInt v;
				input->read(&v, 4);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%u=0x%x [uint]\n", v, v);
				afterBlock = FALSE;
				break;
			}
			case 'usht':
			{
				UnsignedShort v;
				input->read(&v, 2);
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				taggedPrint(output, "%i=0x%x [ushort]\n", (UnsignedInt)v, (UnsignedInt)v);
				afterBlock = FALSE;
				break;
			}
			case 'ustr':
			{
				if (!afterBlock)
					taggedIndent(output, blocks.size());
				UnsignedInt len = 0;
				input->read(&len, 1);
				if (len == 0xff)
					input->read(&len, 4);
				UnicodeString buffer;
				if (len != 0)
				{
					input->read(reinterpret_cast<StringBase<unsigned short> *>(&buffer)->getBufferForRead(len), len * 2);
					reinterpret_cast<StringBase<unsigned short> *>(&buffer)->getBufferForRead(len)[len] = 0;
				}
				taggedPrint(output, "'%S' [unicode]\n", buffer.str());
				afterBlock = FALSE;
				break;
			}
			default:
				throw XferException(0, "Unknown data type ID 0x%08x", type);
		}
	}
}
