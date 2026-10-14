// ?rva002BA654@Rva002BA654@@QAEXPAX00@Z
// partial score=0.647718 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /ICode/Libraries/Include/Lib
// stlport
//
// ?rva002BA654@Rva002BA654@@QAEXPAX00@Z, retail 0x002BA654..0x002BA822
// (471B, RET 12, EH states 0-6). Unified-region notification: when the
// +0xE4/+0xDC gates pass and the player test accepts, fetch the
// LW:UnifiedRegionTitle/Text strings, format them with the region/army
// strings, build a 0x48-byte message (0x4FF28E ctor), copy the position from
// +0x48/+0x4C through the tactical view (0x00DFEF18) transform 0x002BF5B0,
// then queue it on the +0x13C vector. Statement order and the two inline
// string fetches follow the landed sibling 0x002BA3F2 in the same unit.
#include "ascii_string.h"
#include "unicode_string.h"
#include "Coord3D.h"

typedef float Real;

class UnicodeString;
class Vector3 { public: Real X, Y, Z; };

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual void slot34() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

class Rva002E0687
{
public:
	bool rva002E0687() const;
	unsigned char m_pad00[0x1c];
	UnicodeString m_name;			// +0x1C
};
class Rva002E071E;

class Rva0020E89C
{
public:
	UnicodeString rva0020E89C();
	unsigned char m_pad00[0x3c];
	void *m_3c;				// +0x3C
	Real m_48;				// +0x48
	Real m_4c;				// +0x4C
};

class Rva003F1241
{
public:
	UnicodeString rva003F1241();
};

class Rva004FF28EOwner
{
public:
	int rva004FF28E(void *a, void *b, const UnicodeString *title,
		const UnicodeString *text, int arg);
	char m_pad04[0x14 - 0x04];
	void *m_14;				// +0x14
	char m_pad18[0x48 - 0x18];
};

class Rva004FBC02
{
public:
	void rva004FBC02(const void *src);
};

class Rva002BF4F3
{
public:
	bool rva002BF5B0(const Vector3 *in, Vector3 *out);
};
extern Rva002BF4F3 *g_00DFEF18;

struct Rva002B9062Element
{
	void *m_object;
	Rva002B9062Element(void *object);
	~Rva002B9062Element();
};

#include <vector>
namespace _STL { template<> void vector<Rva002B9062Element>::push_back(const Rva002B9062Element &); }

class Rva002BA654
{
public:
	void rva002BA654(void *a, void *b, void *c);

private:
	unsigned char m_pad00[0xDC];
	int m_dc;				// +0xDC
	unsigned char m_padE0[0xE4 - 0xE0];
	int m_e4;				// +0xE4
	unsigned char m_padE8[0x13C - 0xE8];
	_STL::vector<Rva002B9062Element> m_messages;	// +0x13C
};

void Rva002BA654::rva002BA654(void *a, void *b, void *c)
{
	if (m_e4 == 0 && m_dc <= 0)
		return;
	Rva002E0687 *player = (Rva002E0687 *)a;
	if (!player->rva002E0687())
		return;

	Rva0020E89C *region = (Rva0020E89C *)b;
	Rva003F1241 *army = (Rva003F1241 *)c;

	UnicodeString title = TheGameText->fetch("LW:UnifiedRegionTitle");
	UnicodeString s1 = region->rva0020E89C();
	title.format(&title, s1.str());

	UnicodeString text = TheGameText->fetch("LW:UnifiedRegionText");
	UnicodeString s2 = army->rva003F1241();
	UnicodeString s3 = region->rva0020E89C();
	text.format(&text, s3.str(), s2.str());

	Rva004FF28EOwner *message = (Rva004FF28EOwner *)operator new(0x48);
	if (message)
	{
		reinterpret_cast<Rva004FF28EOwner *>(message)->rva004FF28E(
			region, army, &title, &text, 0);
		message->m_14 = region->m_3c;
	}

	Vector3 from;
	Vector3 to;
	from.X = region->m_48;
	from.Y = region->m_4c;
	from.Z = 0.0f;
	to = from;
	g_00DFEF18->rva002BF5B0(&to, &from);
	((Rva004FBC02 *)message)->rva004FBC02(&to);

	Rva002B9062Element element(message);
	m_messages.push_back(element);
}
