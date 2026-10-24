// cl: /O1 /EHa /DNDEBUG /MD /Gy
//
// ?swapEntries@@YIXPAVRva005FA98C@@HHHHHH@Z @0x005FA98C 84B: fastcall
// guarded swap (this in ecx, edx unused, then five stack words) with an ebp
// frame: d==e returns; b/c are checked against o->m_04->m_18/m_1C, else
// return; the rowed thiscall 0x005FA8F5 (Rva005FA8F5Find.cpp) finds the
// entries for d/e on the same object, the rowed forward 0x00600062 gets their
// +4 words on m_04+8, then the two +4 words are exchanged. ret 0x14.
//
// Evidence for the callee body: retail keeps `this` in ecx across both finds
// (b and c are compared through edx; no esi/edi copy of this), i.e. the
// compiler knew 0x005FA8F5 leaves ecx alone. MSVC only tracks callee register
// use for out-of-line functions defined earlier in the same TU, so the find
// body is defined here ahead of the caller. Its existing 39-byte retail row
// belongs here too; the redundant Rva005FA8F5Find.cpp owner was removed.
// Target: search stride-8 keys at +0x34 using the signed count at +0x4C,
// returning the matching entry or one-past-end (calls at 0x005FA9AE/5FA9B8).
struct Rva005FA8F5Entry
{
	int m_key;
	int m_04;
};

struct Rva005FA8F5 {
	char m_pad[0x34];
	Rva005FA8F5Entry m_entries[3];
	int m_count;
	Rva005FA8F5Entry *findEntry(int key);
};

struct Rva00A00062Sub
{
	char m_pad[0x10];
};
struct Rva00600062SwapForward { void forward(int a, int b); };

struct Rva005FA98CM04
{
	char m_pad[8];
	Rva00A00062Sub m_movieClip;
	int m_sideIndex;
	int m_playerIndex;
};

class Rva005FA98C
{
public:
	char m_pad[4];
	Rva005FA98CM04 *m_04;
};

Rva005FA8F5Entry *Rva005FA8F5::findEntry(int key)
{
	int i = 0;
	for (; i < m_count; ++i) {
		if (m_entries[i].m_key == key)
			break;
	}
	return m_entries + i;
}
void __fastcall swapEntries(Rva005FA98C *o, int fwd, int unused, int sideIndex, int playerIndex, int firstKey, int secondKey)
{
	if (firstKey == secondKey)
		return;
	Rva005FA98CM04 *m = o->m_04;
	if (sideIndex != m->m_sideIndex)
		return;
	if (playerIndex != m->m_playerIndex)
		return;
	Rva005FA8F5Entry *firstEntry = ((Rva005FA8F5 *)o)->findEntry(firstKey);
	Rva005FA8F5Entry *secondEntry = ((Rva005FA8F5 *)o)->findEntry(secondKey);
	((Rva00600062SwapForward *)&m->m_movieClip)->forward(firstEntry->m_04, secondEntry->m_04);
	int t = firstEntry->m_04;
	firstEntry->m_04 = secondEntry->m_04;
	secondEntry->m_04 = t;
}
