// A destructor that unhooks itself from a global head.
//
// Trimmed from the Open-BFME-1 Bfme5TinyTen.cpp donor (their retail 0x004902A0,
// same 23 bytes): the file's other two bodies (bfmeIsClear, bfmeBit) have no
// unique placement in game.dat, so only this one is claimed here.
//
// game.dat keeps the list head at 0x00E01E1C (BFME1: 0x012F3350), read from the
// two DIR32 slots of the retail body.

class ProgressIndicator
{
public:
	__declspec(noinline) ProgressIndicator(void);
	virtual ~ProgressIndicator(void);				// slot +0x00

	ProgressIndicator *m_bfmeNext;				// +0x04
};

// Descriptive name: retail's original global name is unknown. The constructor
// links this node at the head; the destructor removes it when it is the head.
ProgressIndicator *BfmeProgressIndicatorHead = 0;

ProgressIndicator::ProgressIndicator(void)
{
	m_bfmeNext = BfmeProgressIndicatorHead;
	BfmeProgressIndicatorHead = this;
}

// ??1ProgressIndicator@@UAE@XZ
ProgressIndicator::~ProgressIndicator(void)
{
	if (BfmeProgressIndicatorHead == this)
		BfmeProgressIndicatorHead = m_bfmeNext;
}

// ??0Rva00355D66@@QAE@XZ @0x00355D4E 24B (formerly Rva00355D4ECtor.cpp): derived ctor
// calling the base ProgressIndicator ctor 0x00355C60 above, then zeroing +8 and
// setting byte +0xC to 1 under vtable 0x00814E5C. Kept in this unit: both ctors
// need the base body visible (retail keeps this in edx across the call).
class GameWindow;

class Rva00355D66 : public ProgressIndicator
{
public:
	Rva00355D66();
	virtual ~Rva00355D66();
protected:
	GameWindow *m_win;
private:
	bool m_flag;
};

Rva00355D66::Rva00355D66() : m_win(0), m_flag(true)
{
}
