// Seven thirty-six-byte __thiscall scalar deleting destructors with one shape:
//
//     push esi / mov esi,ecx / mov [esi],<offset vftable> / call <rel32> /
//     test byte ptr [esp+4],1 / je +9 / push esi / call operator delete /
//     add esp,4 / mov eax,esi / pop esi / ret 4
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/VptrCleanupDeletingDestructors.cpp), trimmed
// to the seven bodies the address map resolves. The donor carries twelve; the
// other five do not place uniquely in game.dat. Each callee is spelled as a
// member of a small class the object is cast to; what the bytes show is a
// __thiscall function reached with `this` in ecx. In this image the shared
// callee is the rowed ??1BfmeDirtyBase at 0x00658650 and the odd one out is
// the rowed ??1Rva00666BA0 at 0x00666BA0; both are pinned under the donor's
// address-derived run() names. The seventh callee is the SList<TagBlockIndex>
// bucket cleanup at 0x00620870 (BFME1 0x009EDD30 Remove_All, byte-identical
// modulo relocs), pinned under the donor's Rva009EDD30Cleanup::run placeholder
// until its true row lands. The delete call reaches the rowed game
// scalar operator delete at 0x0002FD60. Identity beyond the address is not
// recovered: every NAME derives from its retail address.

// These zero-argument thiscall destinations now have unique matched rows:
// the first two restore base vptrs; the third clears the TagBlockIndex SList.
#pragma comment(linker, "/alternatename:?run@Rva007EB6C0Cleanup@@QAEXXZ=??1BfmeDirtyBase@@UAE@XZ")
#pragma comment(linker, "/alternatename:?run@Rva007FA650Cleanup@@QAEXXZ=??1Rva00666BA0@@UAE@XZ")
#pragma comment(linker, "/alternatename:?run@Rva009EDD30Cleanup@@QAEXXZ=?Remove_All@?$SList@VTagBlockIndex@@@@UAEXXZ")

class Rva007EB6C0Cleanup
{
public:
	void run();
};

class Rva007FA650Cleanup
{
public:
	void run();
};

class Rva009EDD30Cleanup
{
public:
	void run();
};

#define BFME_VPTR_CLEANUP_DELETING_DTOR( NAME, CLEANUP )                      \
	class NAME                                                                \
	{                                                                         \
	public:                                                                   \
		virtual ~NAME();                                                      \
	};                                                                        \
	NAME::~NAME()                                                             \
	{                                                                         \
		( (CLEANUP *)this )->run();                                           \
	}

BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F2F50CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F37F0CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F41E0CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007F4900CleanupDeleting, Rva007FA650Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007FADF0CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva007FC120CleanupDeleting, Rva007EB6C0Cleanup )
BFME_VPTR_CLEANUP_DELETING_DTOR( Rva009EEA70CleanupDeleting, Rva009EDD30Cleanup )
