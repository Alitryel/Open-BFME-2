// cl: /O1 /G7 /Oi- /DNDEBUG /MD
//
// StringClass::StringClass(int, bool), retail 0x00065F34, 39 bytes.
// Dedicated TU so no other unit sees this definition. Snapshot-name temp
// ctor used by the DX8 cached-state setters as (0, true): empty-inits the
// buffer from the static, pre-sizes through Get_String, then stamps the
// lead byte from the global. Straight-line flow stays frameless under the
// assign TU's flags.

class StringClass
{
public:
	StringClass(int value, bool flag);

private:
	void Get_String(int new_len, bool flag);

	static char *m_EmptyString;
	static char m_NullChar;
	static char m_LeadByte;
	char *m_Buffer;
};

// StringClass::m_EmptyString: defined in wwstring.cpp (= &m_NullChar).
char StringClass::m_LeadByte;

// ??0StringClass@@QAE@H_N@Z
inline StringClass::StringClass(int value, bool flag)
{
	m_Buffer = m_EmptyString;
	Get_String(value, flag);
	// wwstring.cpp's m_NullChar (VA 0x00A08C18), as the 33 other copies of this
	// inline ctor spell the lead-byte global.
	m_Buffer[0] = m_NullChar;
}

// StringClass int-bool ctor is a header inline elsewhere: other units emit
// select-any copies, so a strong definition here was a duplicate in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitwwstring_ctor_int_bool@@YAXPAVStringClass@@H_N@Z present-unmatched
void bfmeEmitwwstring_ctor_int_bool(StringClass *string, int value, bool flag)
{
	string->StringClass::StringClass(value, flag);
}
#pragma inline_depth()
