// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// Open-BFME5: the two-string constructor at retail 0x00491580, 119 bytes.
//
// Both table stores are the compiler's own vfptr initialisation -- the
// linked-object base's (0x010F9AD8) and then this class's -- which is what puts
// each member receiver ahead of its pushed argument. The direct base's own
// table (0x010F9AF0) is a dead store between them.

class Rva00490350Base;

extern Rva00490350Base *g_bfmeListVX;			// retail 0x012F3350

#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"

class BfmeStrVX : private AsciiString
{
public:
	BfmeStrVX(const AsciiString &other) : AsciiString(other) {}
	~BfmeStrVX(void) {}
};

#include "GameLogicObjectLookupView.h"

class Display
{
public:
	virtual void slot00(); virtual void slot04();
	virtual void slot08(); virtual void slot0C();
	virtual void slot10(); virtual void slot14();
	virtual void slot18(); virtual void slot1C();
	virtual void slot20(); virtual void slot24();
	virtual void slot28(); virtual void slot2C();
	virtual void slot30(); virtual void slot34();
	virtual void slot38(); virtual void slot3C();
	virtual void slot40(); virtual void slot44();
	virtual void slot48(); virtual void slot4C();
	virtual void slot50(); virtual void slot54();
	virtual void slot58(); virtual void slot5C();
	virtual void slot60(); virtual void slot64();
	virtual void slot68(); virtual void slot6C();
	virtual void slot70(); virtual void slot74();
	virtual void slot78(); virtual void slot7C();
	virtual void slot80(); virtual void slot84();
	virtual void slot88(); virtual void slot8C();
	virtual void slot90(); virtual void slot94();
	virtual void slot98(); virtual void slot9C();
	virtual void slotA0(); virtual void slotA4();
	virtual void slotA8(); virtual void slotAC();
	virtual void slotB0(); virtual void slotB4();
	virtual void slotB8(); virtual void slotBC();
	virtual void slotC0(); virtual void slotC4();
	virtual void slotC8(); virtual void slotCC();
	virtual void slotD0(); virtual void slotD4();
	virtual void slotD8(); virtual void slotDC();
	virtual void slotE0(); virtual void slotE4();
	virtual void slotE8(); virtual void slotEC();

	void bfmeStopMovie(void);
};

extern GameLogic *TheGameLogic;
extern Display *TheDisplay;

class Rva00490350Base
{
public:
	__forceinline Rva00490350Base(void)
	{
		m_bfmeNext = g_bfmeListVX;

		g_bfmeListVX = this;

		m_bfmeCount = 0;
		m_bfmeArmed = true;
	}

	virtual ~Rva00490350Base(void);

	Rva00490350Base *m_bfmeNext;				// +0x04
	int m_bfmeCount;					// +0x08
	bool m_bfmeArmed;					// +0x0C
};

// Native base construction and unwind cleanup use the existing Rva00355D66
// owners at 0x00355D4E and 0x00355D66.
class Rva00355D66 : public Rva00490350Base
{
public:
	Rva00355D66(void);
	virtual ~Rva00355D66(void);
};

class Rva003560ED : public Rva00355D66
{
public:
	Rva003560ED(const AsciiString &first, const AsciiString &second);

	virtual ~Rva003560ED(void);

	BfmeStrVX m_bfmeFirst;					// +0x10
	BfmeStrVX m_bfmeSecond;					// +0x14
};

// ??0Rva003560ED@@QAE@ABVAsciiString@@0@Z
Rva003560ED::Rva003560ED(const AsciiString &first,
	const AsciiString &second)
	: m_bfmeFirst(first), m_bfmeSecond(second)
{
}
