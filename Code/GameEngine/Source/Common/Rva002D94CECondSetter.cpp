// ?rva002D94CE@Rva002D94CE@@QAEXH@Z @ 0x002D94CE 15B
// Conditional dword setter: if value != m_30 store it.
// Evidence: honest address name; __thiscall void int via mov cmp je mov and ret 4; callers in FUN_00455a58 and others; neighbours Disp32ByteGetters.cpp and Rva002D94DDMulGetter.cpp.
class Rva002D94CE
{
public:
	void rva002D94CE(int value);
	char m_pad[0x30];
	int m_value;
};
void Rva002D94CE::rva002D94CE(int value)
{
	if (value != m_value)
		m_value = value;
}
