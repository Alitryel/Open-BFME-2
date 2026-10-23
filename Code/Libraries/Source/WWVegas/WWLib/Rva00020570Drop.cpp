// cl: /MD
//
// The 38-byte free-pair helper at 0x00020570, ported from Open-BFME-1's donor
// game/GameEngine/Source/Common/BfmeTwoHundredFifteen.cpp (donor revision:
// reference/open-bfme-1 @ a38d345e). tools/bfme1_sweep.py finds this body
// byte-identical between lotrbfme.exe and game.dat once relocation slots are
// set aside.
//
// The name is address-derived on purpose. The donor's own two names for these
// bytes -- ?bfmeDropJB@@YAXPAUBfmeThingJB@@@Z (b1 0x0084D240) and
// ?bfmeDropJF@@YAXPAUBfmeThingJF@@@Z (b1 0x0084D310) -- are placeholders, and
// lotrbfme.exe ICF-folded the two, so the sweep cannot tell which one game.dat
// means (tier T3). Both are the same body, and per AGENTS.md a folded address
// gets an address-derived name rather than a guessed one. The layout below is
// read off retail: the buffer it releases sits at +0x14.
//
// Boundary: 0x0002056D, 0x0002056E and 0x0002056F are int3 padding and the six
// bytes at 0x00020596 are the next function's own padding, so the body is
// exactly 0x00020570..0x00020595 -- 38 bytes, the size the sweep claims.
//
// Neighbours place this one in STLport 4.5.3's Win32 locale cluster
// (_my_ltoa at 0x000204F0, __Locale_time_destroy at 0x000205A0), which is why
// it lives here; the identity itself is not proven, so it is not asserted.
//
// No reverse/symbols.csv pin: the only reference is the CRT free import, which
// resolves through the ledger.

extern "C" __declspec(dllimport) void __cdecl free(void *memory);

struct Rva00020570Thing
{
	unsigned char m_pad[0x14];	// 0x00
	void *m_buffer;				// 0x14
};

void Rva00020570Drop(void *what)
{
	Rva00020570Thing *thing = (Rva00020570Thing *)what;

	if (thing != 0)
	{
		if (thing->m_buffer != 0)
			free(thing->m_buffer);

		free(thing);
	}
}
