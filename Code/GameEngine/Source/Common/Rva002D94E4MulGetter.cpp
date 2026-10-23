// ?rva002D94E4@Rva002D94E4@@QBEMXZ @ 0x002D94E4 7B
// Float product getter: returns m_60 * m_5C.
// Evidence: honest address name; __thiscall const float via fld/fmul and ret; callers in FUN_00459ad0 and FUN_0045f2bb; neighbours Rva002D94DDMulGetter.cpp and Disp8DwordFieldSetters.cpp.
class Rva002D94E4
{
public:
	float rva002D94E4() const;
	char m_pad[0x5C];
	float m_5C;
	float m_60;
};
float Rva002D94E4::rva002D94E4() const
{
	return m_60 * m_5C;
}
