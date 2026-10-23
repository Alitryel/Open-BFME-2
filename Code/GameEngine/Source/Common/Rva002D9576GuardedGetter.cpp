// ?rva002D9576@Rva002D9576@@QAEHXZ @ 0x002D9576 13B
// Guarded int getter: if state at +0x38 is 1 return value at +0x34 else 0.
// Evidence: honest address name; __thiscall int via cmp/mov/xor and ret; callers in FUN_00454899 and FUN_004570c8; neighbours ConstZeroGetters.cpp and Weapon.cpp; same 0x34/0x38 family as 0x002D9531 and 0x002D954D.
class Rva002D9576
{
public:
	int rva002D9576();
	char m_pad[0x34];
	int m_value;
	int m_state;
};
int Rva002D9576::rva002D9576()
{
	if (m_state == 1)
		return m_value;
	return 0;
}
