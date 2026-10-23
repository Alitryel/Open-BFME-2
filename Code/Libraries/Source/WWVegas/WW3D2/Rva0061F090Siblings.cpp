// cl: /MD
// Sibling of rowed Animatable3DObjClass::Get_Bone_Name at 0x001A4B90 (21B),
// matched on mnemonic shape only -- the identity differs. Retail 0x0061F090
// (21B) forwards through the singleton pointer at 0x00E09C0C and otherwise
// returns 100. The tail jump targets the incremental-link thunk at
// 0x00620DA0, rowed as the 5-byte tail jump Rva00620DA0::forward
// (TailJumpWrappers5B.cpp); retail truth never follows a padded jmp, so the
// call names that row rather than its target bfmeForward (0x006208B0).
class Rva00620DA0
{
public:
	int forward();
};

extern "C" Rva00620DA0 *g_bfme00E09C0C;

int __cdecl rva0061F090()
{
	if (g_bfme00E09C0C)
		return g_bfme00E09C0C->forward();
	return 100;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:_g_bfme00E09C0C=?TheQ1Receiver@@3PAVQ1Receiver0134FAAC@@A")
