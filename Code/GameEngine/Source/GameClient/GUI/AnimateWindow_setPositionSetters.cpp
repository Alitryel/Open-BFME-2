// Ported from Open-BFME-1's game/GameEngine/Source/GameClient/GUI/
// AnimateWindow_setPositionSetters.cpp (donor revision: reference/open-bfme-1
// @ a38d345e) via tools/bfme1_sweep.py. The donor's DebugDisplay.cpp carries the
// same 17 masked bytes and places at the same address; the AnimateWindow donor
// is the one whose shape this TU reproduces, and both are named below.
//
// The donor must be carried in pieces: it defines functions the sweep never
// placed and .githooks/pre-commit's find_declared_unmatched refuses a source with
// any definition the ledger lacks. This TU carries ONLY the body that places
// (donor b1 0x00495370, 17B -> game.dat 0x0065D740, 17B).
//
// The name is address-derived, not the donor's: lotrbfme.exe folded this body
// across three addresses, so `?setStartPos@AnimateWindow@@QAEXUICoord2D@@@Z`
// (and the DebugDisplay twin `?setCursorPos@DebugDisplay@@UAEXHH@Z`) are picks
// the sweep cannot tell apart, and AGENTS.md forbids spending a guessed name on
// a folded address. The BYTES are not in doubt -- the sweep placed the 17 masked
// bytes uniquely at 0x0065D740, and retail there is a whole function:
//
//   8b 44 24 04   mov eax, [esp+4]     ; first value
//   8b 54 24 08   mov edx, [esp+8]     ; second value
//   89 41 08      mov [ecx+8], eax     ; m_first  = first
//   89 51 0c      mov [ecx+0xc], edx   ; m_second = second
//   c2 08 00      ret 8
//
// which is a two-integer setter in either reading: a pair of Int members, or an
// ICoord2D passed by value. 0x0065D739..0x0065D73F is int3 padding before it, so
// the boundary is proven.

class Rva0065D740Owner
{
public:
	void set( int first, int second );

private:
	char m_pad[8];							// +0x00, before the values
	int m_first;							// +0x08
	int m_second;							// +0x0c
};

void Rva0065D740Owner::set( int first, int second )
{
	m_first = first;
	m_second = second;
}
