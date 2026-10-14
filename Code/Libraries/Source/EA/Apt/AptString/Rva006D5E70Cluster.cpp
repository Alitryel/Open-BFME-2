// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc
//
// EAStringC::rva006d5e70 at 0x006D5E70, 22 bytes. Address-derived thin worker:
// it hands the string's UTF-8 payload (m_pData + 8, the layout the rowed
// EAStringCMid.cpp uses) and its integer argument to the cursor worker at
// 0x006D4D40. Seat 6 is recovering 0x006D4D40 itself; the name below is an
// address-derived pin and the orchestrator reconciles it at landing.

class Rva006D5E70String
{
public:
	void rva006d5e70(int count);
	int rva006d5e90(int index);

private:
	char *m_pData; // +0, payload at +8
};

void *rva006d4d40(void *payload, int count);
int rva006d3e40(const char *cursor);

void Rva006D5E70String::rva006d5e70(int count)
{
	rva006d4d40(m_pData + 8, count);
}

// Native6D5E90..6D5EBC RET4: the codepoint at a character index, or -1 for a
// negative index or one past the end: advance the payload cursor with the
// same worker 0x006D4D40, then decode with the rowed UTF-8 decoder
// 0x006D3E40. Address name.
int Rva006D5E70String::rva006d5e90(int index)
{
	if (index < 0)
		return -1;
	void *cursor = rva006d4d40(m_pData + 8, index);
	if (!cursor)
		return -1;
	return rva006d3e40((const char *)cursor);
}
