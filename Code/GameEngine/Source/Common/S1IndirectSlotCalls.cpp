// Two bodies whose call goes through a DWORD SLOT (FF 15 + DIR32 into .idata).
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/S1IndirectSlotCalls.cpp); trimmed to the two
// T1 bodies the sweep places. BFME2's PE import directory identifies their
// native slots as winmm!timeGetTime (BBA918) and mss32!_AIL_lock_mutex@0
// (BBAAC4), so use those imports rather than the donor's slot globals.

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
extern "C" __declspec(dllimport) void __stdcall AIL_lock_mutex();

// Constructor: call a different slot, then set one byte at offset 0.
class Rva00694BC0
{
public:
	Rva00694BC0();
	bool m_flag;
};

Rva00694BC0::Rva00694BC0()
{
	AIL_lock_mutex();
	m_flag = true;
}

// Void: store the slot's dword result into a member far out in the object.
class Rva006629A0
{
public:
	void refresh();
	char m_lead[ 0x34C ];
	int m_value;
};

void Rva006629A0::refresh()
{
	m_value = timeGetTime();
}
