// cl: /O1 /Oi- /MD
// ?rva00603925@Rva00603925@@QAEPAXXZ @ 0x00603925 (19B).
// Returns past the NUL of the inline string at +8: this+9+strlen(this+8).
// Evidence: single caller at 0x006047CB in FUN_00a046b0 advances esi with the
// result in a counted loop; callee strlen via E8-to-thunk 0x00629170; no donor.
extern "C" unsigned int __cdecl strlen(const char *s);
class Rva00603925
{
	unsigned char m_pad[8];
	char m_str[1];
public:
	void *rva00603925();
};
void *Rva00603925::rva00603925()
{
	return (char *)this + 9 + strlen(m_str);
}
