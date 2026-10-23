// cl: /MD
//
// The 35-byte constructor at 0x0061FC70, ported from Open-BFME-1's donor
// game/GameEngineDevice/Source/W3DDevice/GameLogic/Rva009EB960Ctor.cpp (donor
// revision: reference/open-bfme-1 @ a38d345e). tools/bfme1_sweep.py finds this
// body byte-identical between lotrbfme.exe and game.dat once relocation slots
// are set aside.
//
// The name is address-derived on purpose: lotrbfme.exe ICF-folded this body
// across five addresses, so the donor's own name for it is a pick among twins
// and the sweep cannot tell which one game.dat means (tier T3). What the body
// does is not in doubt, and it is what the layout below encodes:
//
//   mov [edx], vtable        the object has a vtable, so the class is virtual
//   mov [edx+0x2BF40], 1     one trailing dword initialised to 1
//   rep stosd, 0xAFCF dwords zero-fill from +4, which ends exactly at +0x2BF40
//   mov eax, edx             return this
//
// so the object is 0x2BF44 bytes: a vptr, 0xAFCF payload dwords, and a last
// dword of 1. In the donor that same layout is the 0x2BF44-byte block its
// Rva009EB960 constructor allocates with ::operator new and placement-news this
// class into. The identity of the class is still not asserted, so it is not
// named: Rva0061FC70CleanupDeleting is the address plus the donor's own hint.
//
// Boundary: 0x0061FC69 is the previous function's own `ret` followed by six
// int3 bytes, and 0x0061FC93 opens the next thirteen -- so the body is exactly
// 0x0061FC70..0x0061FC92, the 35 bytes the sweep claims.
//
// No reverse/symbols.csv pin: the body reaches no global and calls nothing. The
// vtable operand is a relocation slot, so it is masked out of the byte compare;
// the one the compiler emits for this class is what stands there.

class Rva0061FC70CleanupDeleting
{
public:
	Rva0061FC70CleanupDeleting();
	virtual ~Rva0061FC70CleanupDeleting();

private:
	unsigned int m_data[0xAFCF];
	unsigned int m_last;
};

typedef char Rva0061FC70CleanupDeletingSizeCheck[
	sizeof(Rva0061FC70CleanupDeleting) == 0x2BF44 ? 1 : -1];

Rva0061FC70CleanupDeleting::Rva0061FC70CleanupDeleting()
	: m_last(1)
{
	for (unsigned int index = 0; index < 0xAFCF; ++index)
		m_data[index] = 0;
}
