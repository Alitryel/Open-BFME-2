// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// ?rva0025D358@Display@@QAEXVUnicodeString@@MMHHH@Z, retail 0x0025D358, 112 bytes.
// Sets the +0xB0 display block: Unicode string via set plus ints at +0xB4/+0xB8/+0xBC
// and floats at +0xC0/+0xC4; the by-value string is released at the end.
// Evidence: same +0xB0/+0xD0/+0xF0 layout as the dtor 0x0025D686 (BfmeStrVM0Dtor.cpp)
// and ctor 0x0025D489; callees rowed StringBase<G>::set 0x00037150 and
// releaseBuffer 0x00036E70. The parameter is a UnicodeString: the only caller,
// 0x00356AC1 (Rva003560EDEngineRefresh.cpp), passes a UnicodeString copy of the
// fetched "GUI:Loading" text. Moved out of BfmeStrVM0Dtor.cpp, whose private
// StringBase view cannot spell UnicodeString (the canonical header owns it).
#include "unicode_string.h"

class GameFont;

// The display string TheDisplayStringManager hands out; only the virtual slots
// 0x0025D3C8 reaches are spelled (slot names follow Zero Hour's DisplayString,
// a structural inference).
class DisplayString
{
public:
	virtual void s00();
	virtual void setText(UnicodeString text);				// +0x04
	virtual void s02(); virtual void s03(); virtual void s04(); virtual void s05();
	virtual void setFont(GameFont *font);					// +0x18
	virtual void s07(); virtual void s08(); virtual void s09();
	virtual void setWordWrap(int a, int b);					// +0x28
	virtual void s11(); virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual unsigned int getWidth(int charPos);				// +0x40
};

class DisplayStringManager
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13();
	virtual DisplayString *newDisplayString();				// +0x38
};
extern DisplayStringManager *TheDisplayStringManager;

class Display
{
public:
	void rva0025D358(UnicodeString s, float fC0, float fC4, int iB4, int iB8, int iBC);
	DisplayString *rva0025D3C8();
private:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual unsigned int v16();								// +0x40
	virtual unsigned int v17();								// +0x44
	char m_pad04[0xB0 - 4];
	UnicodeString m_sB0;
	int m_iB4;
	int m_iB8;
	int m_iBC;
	float m_fC0;
	float m_fC4;
	float m_fC8;
	float m_fCC;
};

void Display::rva0025D358(UnicodeString s, float fC0, float fC4, int iB4, int iB8, int iBC)
{
	StringBase<unsigned short> &dst = m_sB0;
	dst.set(s);
	m_iB4 = iB4;
	m_iB8 = iB8;
	m_iBC = iBC;
	m_fC0 = fC0;
	m_fC4 = fC4;
}

// Retail 0x0025D3C8 (193B): NULL for an empty +0xB0 text; otherwise a new
// display string from TheDisplayStringManager given the +0xB4 font, the text
// and the +0xB8/+0xBC pair, after which +0xC8 holds half the unsigned width
// left over beside it (this slot 0x40 minus the string's width) and +0xCC the
// unsigned slot 0x44 value scaled by +0xC4. Returns the display string.
DisplayString *Display::rva0025D3C8()
{
	if (m_sB0.isEmpty())
		return 0;
	DisplayString *ds = TheDisplayStringManager->newDisplayString();
	if (ds) {
		ds->setFont((GameFont *)m_iB4);
		ds->setText(m_sB0);
		ds->setWordWrap(m_iB8, m_iBC);
		unsigned int width = ds->getWidth(-1);
		m_fC8 = (float)((v16() - width) >> 1);
		m_fCC = (float)v17() * m_fC4;
	}
	return ds;
}
