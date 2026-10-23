// ?Rva00030DD0AddRef@@YAHPAURva00030DD0Lock@@@Z @ 0x00030DD0 21B
// Critical-section addref: enters the +0x00 section and increments the +0x18
// refcount, returning the new count. Evidence: IAT EnterCriticalSection at
// 0x00BBA200, CRITICAL_SECTION layout (0x18 bytes) with int at +0x18, callers
// at 0x0003186B 0x00033D6F 0x006C1AAF 0x006C1E4A, counterpart release
// (dec + LeaveCriticalSection) at 0x00030DF0. Honest address-derived name:
// identity unproven from 21 bytes. No // cl: line (defaults match the
// frameless push/call/inc shape, CriticalSectionDeleteWrapper precedent).
struct Rva00030DD0Lock
{
	Rva00030DD0Lock();
	~Rva00030DD0Lock();
	unsigned char m_cs[0x18];
	int m_ref;
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall LeaveCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall InitializeCriticalSection(void *cs);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *cs);

int Rva00030DD0AddRef(Rva00030DD0Lock *lock)
{
	EnterCriticalSection(lock);
	return ++lock->m_ref;
}

// ?Rva00030DF0Release@@YAHPAURva00030DD0Lock@@@Z @ 0x00030DF0 25B
// Critical-section release: decrements the +0x18 refcount and leaves the +0x00
// section returning the new count. Evidence: IAT LeaveCriticalSection at
// 0x00BBA204 same Rva00030DD0Lock layout as AddRef counterpart at 0x00030DD0
// callers at 0x00031881 0x006C1B39 0x006C1E8D. Honest address-derived name.
int Rva00030DF0Release(Rva00030DD0Lock *lock)
{
	int old = lock->m_ref;
	lock->m_ref = old - 1;
	LeaveCriticalSection(lock);
	return old - 1;
}

// ?Rva00030D90Init@@YAPAURva00030DD0Lock@@PAU1@@Z @ 0x00030D90 25B
// Null-safe critical-section init: zeroes the +0x18 refcount and inits the
// +0x00 section returning the lock or 0. Evidence: IAT
// InitializeCriticalSection at 0x00BBA15C same Rva00030DD0Lock layout as AddRef
// at 0x00030DD0 callers at 0x0003183B 0x00033725. Honest address-derived name.
Rva00030DD0Lock *Rva00030D90Init(Rva00030DD0Lock *lock)
{
	Rva00030DD0Lock *result = 0;
	if (lock != 0) {
		lock->m_ref = 0;
		InitializeCriticalSection(lock);
		result = lock;
	}
	return result;
}

// ??_GRva00030DD0Lock@@QAEPAXI@Z @0x00030DB0 32B.
// Non-virtual deleting dtor: inlined DeleteCriticalSection at IAT 0xBBA158
// then conditional operator delete 0x2FD60 on flag bit0. Gap between
// 0x00030D90 and 0x00030DD0 same TU defaults. __thiscall ret 4.
inline Rva00030DD0Lock::~Rva00030DD0Lock()
{
	DeleteCriticalSection(this);
}
void famgenDelete(Rva00030DD0Lock *p) { delete p; }

// ?Rva00030EF0Get@@YAKXZ @0x00030EF0 21B.
// Free function returning SYSTEM_INFO dwPageSize (+4) via IAT
// GetSystemInfo at 0xBBA3AC. Same TU defaults frameless sub/push/call.
// Honest address-derived name, DWORD return.
extern "C" __declspec(dllimport) void __stdcall GetSystemInfo(void *info);
unsigned long Rva00030EF0Get()
{
	struct SysInfo
	{
		unsigned long m_00[9];
	};
	SysInfo info;
	GetSystemInfo(&info);
	return info.m_00[1];
}

// ??0Rva00030DD0Lock@@QAE@XZ @0x00030D60 21B.
// Non-virtual ctor: zeroes +0x18 refcount then InitializeCriticalSection
// at IAT 0xBBA15C on this. Same lock layout as AddRef. __thiscall ret.
// Callers none yet. Neighbour flags defaults.
Rva00030DD0Lock::Rva00030DD0Lock()
{
	m_ref = 0;
	InitializeCriticalSection(this);
}

// ??1Rva00030DD0Lock@@QAE@XZ @0x00030D80 8B: the out-of-line copy of the
// inline destructor above (push ecx; DeleteCriticalSection; ret),
// unreferenced in retail. The anchor below (no retail counterpart) only makes
// this unit emit it.
#pragma inline_depth(0)
// ?bfmeEmitRva00030DD0LockDtor@@YAXPAURva00030DD0Lock@@@Z present-unmatched
void bfmeEmitRva00030DD0LockDtor(Rva00030DD0Lock *p)
{
	p->~Rva00030DD0Lock();
}
#pragma inline_depth()
