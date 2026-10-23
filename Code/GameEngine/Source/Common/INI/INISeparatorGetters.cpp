// INI's four separator getters, retail 0x0002BAD5..0x0002BAEF, seven bytes each
// (mov eax,[ecx+DISP] / ret), consecutive in the INI code and followed by a
// byte getter at +0x430. Zero Hour's INI.h declares exactly these four, in this
// order, on four consecutive members (m_seps, m_sepsPercent, m_sepsColon,
// m_sepsQuote); BFME2's matched INI parsers place m_sepsColon at +0x420, so the
// set sits at +0x418..+0x424. They are header inlines; the pointers below only
// make cl emit them out of line, as the first object in retail's link order did.
// No // cl: line (defaults match the frameless seven-byte shape).

class INI
{
public:
	const char *getSeps() const { return m_seps; }
	const char *getSepsPercent() const { return m_sepsPercent; }
	const char *getSepsColon() const { return m_sepsColon; }
	const char *getSepsQuote() const { return m_sepsQuote; }

private:
	char m_unreconstructed_000[0x418];
	const char *m_seps;			// +0x418
	const char *m_sepsPercent;	// +0x41C
	const char *m_sepsColon;	// +0x420
	const char *m_sepsQuote;	// +0x424
};

typedef const char *(INI::*IniSeparatorGetter)() const;
extern const IniSeparatorGetter g_iniSeparatorGetters[4];
const IniSeparatorGetter g_iniSeparatorGetters[4] = {
	&INI::getSeps, &INI::getSepsPercent, &INI::getSepsColon, &INI::getSepsQuote
};
