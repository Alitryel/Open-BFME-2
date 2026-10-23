// cl: /O1 /arch:SSE /G7 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// ?rva005047AE@Rva005047AE@@QBE_NXZ, retail 0x005047AE (130 bytes): a
// consistency check over the vector of 16-byte keys at +8/+0xC. Empty is
// valid; mode +0 == 1 needs the first key's +8 to be zero and mode +4 == 1
// the last key's +0xC; and every adjacent pair must share its +4 value,
// with the earlier key's +0xC and the later key's +8 zero. The keys look
// like curve segments (value at +4, in/out tangents at +8/+0xC), but no
// name is established; names are address-derived.
#include <vector>

struct Rva005047AEKey
{
	float m_00;
	float m_value;	// +0x04
	float m_in;	// +0x08
	float m_out;	// +0x0C
};

class Rva005047AE
{
public:
	bool rva005047AE() const;
private:
	int m_startMode;				// +0x00
	int m_endMode;					// +0x04
	_STL::vector<Rva005047AEKey> m_keys;		// +0x08
};

bool Rva005047AE::rva005047AE() const
{
	if (m_keys.empty())
		return true;
	const Rva005047AEKey &last = m_keys.back();
	_STL::vector<Rva005047AEKey>::const_iterator it = m_keys.begin();
	if (m_startMode == 1 && it->m_in != 0.0f)
		return false;
	if (m_endMode == 1 && last.m_out != 0.0f)
		return false;
	for (_STL::vector<Rva005047AEKey>::const_iterator next = it + 1; it != &last; ++it, ++next)
	{
		if (it->m_value != next->m_value)
			return false;
		if (it->m_out != 0.0f)
			return false;
		if (next->m_in != 0.0f)
			return false;
	}
	return true;
}
