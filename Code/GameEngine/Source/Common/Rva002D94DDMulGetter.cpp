// ?rva002D94DD@Rva002D94DD@@QBEMXZ @ 0x002D94DD 7B
// Float product getter: returns m_58 * m_54.
// Evidence: honest address name; __thiscall const float via fld/fmul and ret; callers in FUN_0045b256 and others; neighbours Disp32ByteGetters.cpp and Disp8DwordFieldSetters.cpp.
class Rva002D94DD
{
public:
	float rva002D94DD() const;
	char m_pad[0x54];
	float m_54;
	float m_58;
};
float Rva002D94DD::rva002D94DD() const
{
	return m_58 * m_54;
}
