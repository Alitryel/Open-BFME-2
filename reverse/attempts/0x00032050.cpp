// ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z
// partial score=0.9 date=2026-10-15
// ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z
// partial score=0.9 date=2026-10-14
// ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z
// partial score=0.8975 date=2026-10-13
// ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z
// partial score=0.81 date=2026-10-13
// ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z
// partial score=0.55 date=2026-10-03
// no // cl: line: base flags -O2 -GR- -EHsc-
// Banked attempt for ?rva00032050@GeneralAllocator@Allocator@EA@@QAEIPAXI@Z
// Retail 0x00032050..0x000320DC (140 bytes). Current standalone and whole-home
// builds both emit 140 bytes, with the first difference at +0x46: the order of
// the five count adjustments. The first 70 bytes, including this in EDI,
// lock in ESI, block in EBX and the masked-size spill into the argument slot,
// already match. The older 135-byte allocation description no longer applies.
// Explicit pointer-argument reuse retains 140 bytes but regresses the first
// difference to +0x39; a native-order source expression emits 141 bytes.
// The real 0x31F90 callee now has a pin, but its body remains unrowed.

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *section);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *section);

namespace EA
{
namespace Allocator
{

struct Lock
{
	unsigned char m_pad[0x18];
	int volatile m_count;
};

class GeneralAllocator
{
public:
	unsigned int rva00032050(void *block, unsigned int flags);
	int rva00031F90(void *block);

private:
	char m_pad[0x4E4];
	Lock *m_4E4;
};

unsigned int GeneralAllocator::rva00032050(void *block, unsigned int flags)
{
	Lock *lock = m_4E4;
	if (lock != 0) {
		EnterCriticalSection(lock);
		++lock->m_count;
	}

	unsigned int size = *(unsigned int *)((char *)block + 4) & 0x7FFFFFF8;
	int result;
	result = rva00031F90(block) + ((((unsigned char)(unsigned int)block) & 7) != 0) + ((((unsigned char)size) & 7) != 0) + (size < 8);
	_ReadWriteBarrier();
	result = result + (size >= flags + 0x10) + (size < 0x10);

	if (lock != 0) {
		--lock->m_count;
		LeaveCriticalSection(lock);
	}
	return result;
}

}
}
