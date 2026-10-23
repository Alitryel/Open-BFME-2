// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
//
// ?rva0021F5F8@CreateAHeroManager@@QAEXXZ, retail 0x0021F5F8..0x0021F797
// (415 bytes, EH, RET 0; caller the screen destructor 0x00513BAB; WB twin
// 0x00B7F190, unnamed): reconciles the hero save files with the manager's
// heroes. For each listed file (the 0x0021F19B file list, destroyed through
// its rowed destructor 0x0021DB35) whose suffix-stripped name (0x0021C12F)
// the hero list at +0x174 does not know (0x0040A5CF), it deletes that save
// file: the save directory (0x002DC267) plus the file name, joined by the
// wide concat materializer 0x0021C3F7, passed to kernel32 DeleteFileW (IAT
// 0xBBA324). Then each hero (0x0040A32F) that is not a system hero (+0x48,
// unless the 0x009FE34C flag is set) and has a name (+0x4C) is saved under
// its file name (0x0021A651) through 0x004098BE.
//
// Codegen evidence: both containers are STLport vectors (8-byte file
// entries, CreateAHeroData pointers); with real vectors and the WB twin's
// inline hero accessors (its isSystem/getName temporaries) cl gives retail's
// this/EBX, iterator/hero EDI allocation, which the hand-written views and
// direct member reads mirrored. Owner class and method names are unknown.
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

class GameState;
extern GameState *TheGameState;

// The game state's save directory (0x002DC267), rowed under its own spelling.
class Rva002DC267
{
public:
	UnicodeString rva002DC267() const;
};

extern unsigned char g_rva005B5C02Flag;

class CreateAHeroData;
class Rva0040A3F9
{
public:
	CreateAHeroData *rva0040A5CF(const AsciiString &name);	// 0x0040A5CF
	CreateAHeroData *rva0040A32F(int index);			// 0x0040A32F
	unsigned int size() const { return m_list.size(); }
private:
	_STL::vector<CreateAHeroData *> m_list;
};

struct Rva0021F5F8Hero
{
	unsigned char m_pad00[0x48];
	bool m_system;					// +0x48
	unsigned char m_pad49[0x4c - 0x49];
	AsciiString m_name;				// +0x4C
	bool isSystem() const { return m_system; }
	const AsciiString &getName() const { return m_name; }
};
class CreateAHeroHero { public: bool rva004098BE(const AsciiString &file, bool system); };
AsciiString Rva0021A651Filename(const AsciiString &name);
AsciiString Rva0021C12FStripName(const AsciiString &file);

struct CreateAHeroFileEntry
{
	AsciiString filename;
	bool system;
};
struct Rva0021DB35
{
	Rva0021DB35();		// 0x0021F19B
	~Rva0021DB35();		// 0x0021DB35
	_STL::vector<CreateAHeroFileEntry> m_files;
};

class BFME2WideConcatPair
{
public:
	__forceinline BFME2WideConcatPair(const UnicodeString &left, const UnicodeString &right) { m_right = &right; m_left = &left; }
	operator UnicodeString();			// 0x0021C3F7 (pinned UnicodeString spelling)
	const UnicodeString *m_left;
	const UnicodeString *m_right;
};
extern "C" __declspec(dllimport) int __stdcall DeleteFileW(const unsigned short *path);

class CreateAHeroManager
{
public:
	void rva0021F5F8();
	unsigned char m_pad000[0x174];
	Rva0040A3F9 m_heroes;			// +0x174
};

void CreateAHeroManager::rva0021F5F8()
{
	Rva0021DB35 files;
	for (_STL::vector<CreateAHeroFileEntry>::iterator it = files.m_files.begin(); it != files.m_files.end(); ++it)
	{
		AsciiString name = Rva0021C12FStripName(it->filename);
		if (!m_heroes.rva0040A5CF(name))
		{
			UnicodeString path = BFME2WideConcatPair(((const Rva002DC267 *)TheGameState)->rva002DC267(),
				UnicodeString(it->filename));
			DeleteFileW(path.str());
		}
	}
	unsigned int count = m_heroes.size();
	for (unsigned int i = 0; i < count; ++i)
	{
		Rva0021F5F8Hero *hero = (Rva0021F5F8Hero *)m_heroes.rva0040A32F(i);
		if (hero && (!hero->isSystem() || g_rva005B5C02Flag) && !hero->getName().isEmpty())
		{
			AsciiString file = Rva0021A651Filename(hero->getName());
			((CreateAHeroHero *)hero)->rva004098BE(file, hero->isSystem() || g_rva005B5C02Flag);
		}
	}
}
