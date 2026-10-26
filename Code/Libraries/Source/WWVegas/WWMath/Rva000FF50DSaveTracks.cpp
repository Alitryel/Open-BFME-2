// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/shims/sweep
// ?saveTracks@Rva000FF50D@@QAEXXZ, retail 0x000FF50D, 217 bytes.
// Evidence: unlock lane; .wak/.wb literals plus fopen/fwrite/fclose IAT;
// WaterTracks saveTracks donor (W3DWaterTracks.cpp saveTracks with .wak,
// wb, fwrite start/end/type plus count) ported to member filename at +0x28
// and list at +0x10; WaterTracksObj +0x58/+0x60 8B +0x30 4B +0x68 flag
// +0xB0 next; caller 0xFF8FA; neighbours Rva000FE9E3 + pod containers.
#include "ascii_string.h"
#include <stdio.h>
#include <string.h>

extern "C" char *__cdecl _mbscpy(char *dst, const char *src);
extern "C" unsigned int __cdecl strlen(const char *s);
extern "C" __declspec(dllimport) struct _iobuf *__cdecl fopen(const char *path, const char *mode);
extern "C" __declspec(dllimport) unsigned int __cdecl fwrite(const void *ptr, unsigned int size, unsigned int count, struct _iobuf *file);
extern "C" __declspec(dllimport) int __cdecl fclose(struct _iobuf *file);

#include "../../../../../reference/shims/wwmath/Vector2.h"

// These field spellings agree with the matched WaterTracksObj initializer.
// Native save and init independently access type30, endpoints58/60, offset68
// and nextB0; this reconciles the existing view without asserting a new class name.
class WaterTracksObj
{
public:
	char m_pad00[0x30];
	int type;
	char m_pad34[0x58 - 0x34];
	Vector2 initStart;
	Vector2 initEnd;
	int initOffset;
	char m_pad6C[0xB0 - 0x6C];
	WaterTracksObj *next;
};

class Rva000FF50D
{
public:
	void saveTracks();
	char m_pad00[0x10];
	WaterTracksObj *m_used;
	char m_pad14[0x28 - 0x14];
	AsciiString m_file;
};

void Rva000FF50D::saveTracks()
{
	AsciiString fileName = m_file;
	char path[256];
	const char *data = *(const char **)&fileName;
	_mbscpy(path, data ? data + 8 : "");
	unsigned int len = strlen(path);
	_mbscpy(path + len - 4, ".wak");
	int trackCount = 0;
	struct _iobuf *file = fopen(path, "wb");
	if (file != 0)
	{
		WaterTracksObj *track = m_used;
		while (track != 0)
		{
			if (track->initOffset == 0)
			{
				fwrite(&track->initStart, 8, 1, file);
				fwrite(&track->initEnd, 8, 1, file);
				fwrite(&track->type, 4, 1, file);
				++trackCount;
			}
			track = track->next;
		}
		fwrite(&trackCount, 4, 1, file);
		fclose(file);
	}
}
