// cl: /O1 /arch:SSE /G7 /MD
//
// ?finish@XmlNameSlotList@@QAEHXZ @0x00542890 121B: the markup lexer's
// advance to the next element (the BfmeLexEAN object of BfmeConv2008.cpp,
// named XmlNameSlotList by the matched Lua token parsers that call it).
// A pending "/>" closes the element (2); otherwise the pending output byte
// is flushed and whitespace and <!-- --> comments are skipped. At the end
// of the text the tail and mark reset and 0 is returned; at '<' the
// element scanner (0x005424C4, unrowed, address-named) takes over, anything
// else is character data (bfmeScanEAN). Retail returns EAX (2 / 0 / the
// callee results), so the int spelling is the retail one.
//
// Target evidence: native 0x00542890..0x00542909 (RET), callees read from
// its REL32 sites. Shape facts: retail calls bfmeFailEAN at its first site
// without reloading ECX and tail-merges the other two failure sites into
// it; that needs the flush (0x005427F1) and comment-skip (0x0054273B)
// bodies compiled earlier in this unit as ordinary out-of-line definitions
// (inline or noinline COMDAT copies are generated too late to help) so cl
// knows both leave ECX alone; their rows moved here from the one-function
// units Rva005427F1Flush.cpp and Rva0054273BComment.cpp, whose bodies
// match unchanged under these flags. The "/>" arm written with one result
// variable keeps the failure call ahead of "return 2". The element-scanner
// tail jump precedes the character-data one because the '<' test is the
// positive arm.

class BfmeLexEAN
{
public:
	int bfmeScanEAN();							// 0x00542791, character data
	int bfmeFailEAN(int code);					// 0x00542459
};

class Rva005423F0
{
public:
	char *rva005423F0(char *text);				// 0x005423F0, skip whitespace
};

class Rva005427F1
{
public:
	void rva005427F1();
private:
	char m_pad[0x20];
	char *m_out;
	unsigned char m_ch;
};

// ?rva005427F1@Rva005427F1@@QAEXXZ @0x005427F1 21B: flush the pending
// output byte: if +0x20 is non-null store the +0x24 byte there, then clear
// both (retail bytes; neighbours Rva005426DBDecode and Rva00542806Init use
// the same +0x20/+0x24 layout).
void Rva005427F1::rva005427F1()
{
	if (m_out != 0) {
		*m_out = (char)m_ch;
		m_out = 0;
		m_ch = 0;
	}
}

class Rva0054273B
{
public:
	bool rva0054273B();
private:
	char *m_ptr;
};

// ?rva0054273B@Rva0054273B@@QAE_NXZ @0x0054273B 86B: XML comment-end skip:
// after +2 expects "--", then scans to "-->", returning true on '>' and
// false on NUL (retail bytes).
bool Rva0054273B::rva0054273B()
{
	m_ptr += 2;
	if (*m_ptr != '-')
		return false;
	++m_ptr;
	if (*m_ptr != '-')
		return false;
	++m_ptr;
	if (*m_ptr == 0)
		return false;
	for (;;) {
		char *p = m_ptr;
		while (*p != 0 && *p != '-')
			++p;
		m_ptr = p;
		if (*p == 0)
			return false;
		++p;
		m_ptr = p;
		if (*p == 0)
			return false;
		if (*p != '-')
			continue;
		++p;
		m_ptr = p;
		if (*p == 0)
			return false;
		if (*p != '>')
			continue;
		++p;
		m_ptr = p;
		return true;
	}
}

class XmlNameSlotList
{
public:
	int finish();
	int rva005424C4();							// 0x005424C4, scan an element

private:
	char *m_pos;								// +0x00
	char m_pad04[0x0C];
	bool m_inTag;								// +0x10
	char m_pad11[0x0B];
	char *m_tail;								// +0x1C
	char m_pad20[0x08];
	int m_mark;									// +0x28
};

// ?finish@XmlNameSlotList@@QAEHXZ
int XmlNameSlotList::finish()
{
	if (m_inTag && *m_pos == '/') {
		int r;
		++m_pos;
		if (*m_pos != '>')
			r = ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
		else {
			++m_pos;
			r = 2;
		}
		return r;
	}
	((Rva005427F1 *)this)->rva005427F1();
	if (m_pos == 0)
		return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
	for (;;) {
		m_pos = ((Rva005423F0 *)this)->rva005423F0(m_pos);
		if (*m_pos == 0)
			break;
		if (*m_pos == '<') {
			if (m_pos[1] != '!')
				return rva005424C4();
			if (!((Rva0054273B *)this)->rva0054273B())
				return ((BfmeLexEAN *)this)->bfmeFailEAN(-1);
		} else
			return ((BfmeLexEAN *)this)->bfmeScanEAN();
	}
	m_tail = 0;
	m_mark = 0;
	return 0;
}
