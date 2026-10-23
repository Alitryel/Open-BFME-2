// ?releasePair@@YAXXZ
// BFME 2: Open-BFME-1's SmallGaps/releasePair.cpp (submodule 10af19f44a, BFME 1
// 0x008A4AC0), byte-identical in game.dat at 0x006E97C0. bfme1_sweep lists it as
// ambiguous with its twin bfmeGo1062B, already rowed at 0x006E8EF0: masked, the
// two are the same bytes. The DIR32 operands tell them apart. The twin releases
// VA 0xe1816c/0xe18170 (BfmeConv1062.cpp's globals) and this copy releases
// VA 0xe18190/0xe18194, so those two globals are defined here (zero-filled .bss;
// no other unit references them).
struct Rva008A4AC0Object { virtual void slot0(); virtual void release(); };
Rva008A4AC0Object* Rva008A4AC0First;	// VA 0x00e18190
Rva008A4AC0Object* Rva008A4AC0Second;	// VA 0x00e18194
void releasePair()
{
	if (Rva008A4AC0First) { Rva008A4AC0First->release(); Rva008A4AC0First = 0; }
	if (Rva008A4AC0Second) { Rva008A4AC0Second->release(); Rva008A4AC0Second = 0; }
}
