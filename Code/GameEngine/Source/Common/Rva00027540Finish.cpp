// cl: /Od
//
// Rva00028B90Thing::bfmeDoPF(char*, int, int) at 0x00027540, 117 bytes.
// The thiscall spelling of the BFME1 donor ?bfmeFindV20@@YGHPBDII@Z
// (Code/GameEngine/Source/Common/BfmeConv1460.cpp): the object carries the
// haystack begin/end at +0/+4, the guard is (pos + n) <= size, the needle
// [s, s+n) is searched in [begin+pos, end) through the worker at 0x0026C90,
// and the result is the found offset or -1. The existing pin
// ?bfmeDoPF@Rva00028B90Thing@@QAEXPADPAXH@Z at this address names the caller's
// view; this row spells the two integer operands directly, hence PADHH.
//
// 0x0026C90 is unpinned; its address-derived name is used for the call.

class Rva00028B90Thing
{
public:
	char *m_begin; // +0
	char *m_end;   // +4

	int bfmeDoPF(char *s, int pos, int n);
};

char *rva0026c90(char *first1, char *last1, char *first2, char *last2, char tag);

int Rva00028B90Thing::bfmeDoPF(char *s, int pos, int n)
{
	char *found;
	char tag;
	if ((unsigned int)(pos + n) > (unsigned int)(m_end - m_begin))
		return -1;
	found = rva0026c90(m_begin + pos, m_end, s, s + n, tag);
	return found != m_end ? (int)(found - m_begin) : -1;
}
