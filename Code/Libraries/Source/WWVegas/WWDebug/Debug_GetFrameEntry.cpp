// cl: /DNDEBUG /MD /EHsc
//
// Debug::GetFrameEntry, retail 0x0003A1B0 (91 bytes).
// Ported from the Open-BFME-1 conversion
// (Libraries/Source/WWVegas/WWDebug/Debug_GetFrameEntry_Thunk.cpp), which
// itself tracks the Zero Hour debug_debug.h layout: a 10007-entry hash table
// at +0x18 holding FrameHashEntry chains (next at +0, frame address at +4,
// status at +0x18). A miss calls AddFrameEntry, then UpdateFrameStatus runs
// when the entry is still Unknown.
// Dedicated TU so Debug_LogBegin_0088B8F0.cpp keeps its matched LogBegin:
// defining this beside that caller would let MSVC see the callee and change
// the caller's register save set (docs/matching.md pattern five).

// Upstream body and layout:
// reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
class Debug
{
private:
	enum FrameStatus
	{
		Unknown,
		Skip,
		NoSkip
	};

	// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_debug.h
	struct FrameHashEntry
	{
		FrameHashEntry *next;
		unsigned int frameAddr;
		unsigned int frameType;
		const char *fileOrGroup;
		int line;
		int hits;
		FrameStatus status;
	};

	enum { FRAME_HASH_SIZE = 10007 };

	char m_prefix[0x18];
	FrameHashEntry *frameHash[FRAME_HASH_SIZE];

	FrameHashEntry *AddFrameEntry(unsigned int addr, unsigned int type,
		const char *fileOrGroup, int line);
	void UpdateFrameStatus(FrameHashEntry &entry);

	__forceinline FrameHashEntry *LookupFrame(unsigned int addr)
	{
		for (FrameHashEntry *entry = frameHash[addr % FRAME_HASH_SIZE]; entry;
			entry = entry->next)
		{
			if (entry->frameAddr == addr)
				return entry;
		}
		return 0;
	}

	FrameHashEntry *GetFrameEntry(unsigned int addr, unsigned int type,
		const char *fileOrGroup, int line);

public:
	static void bfmeEmitDebugGetFrameEntry(Debug *p);
};

// ?GetFrameEntry@Debug@@AAEPAUFrameHashEntry@1@IIPBDH@Z
inline Debug::FrameHashEntry *Debug::GetFrameEntry(unsigned int addr, unsigned int type,
	const char *fileOrGroup, int line)
{
	FrameHashEntry *entry = LookupFrame(addr);
	if (!entry)
		entry = AddFrameEntry(addr, type, fileOrGroup, line);
	if (entry->status == Unknown)
		UpdateFrameStatus(*entry);
	return entry;
}

// This file owns the row, but another file emits the same function as an
// inline copy it cannot stop emitting, so a strong definition here was a
// duplicate symbol in the linked build. The anchor below emits the select-any
// copy for the ledger row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitDebugGetFrameEntry@Debug@@SAXPAV1@@Z present-unmatched
void Debug::bfmeEmitDebugGetFrameEntry(Debug *debug)
{
	debug->GetFrameEntry(0, 0, 0, 0);
}
#pragma inline_depth()
