// cl: /DNDEBUG /MD /EHsc /Oy-
//
// Debug::AddFrameEntry, retail 0x00038FF0 (223 bytes).
// Ported from Open-BFME-1 WWDebug/debug_debug.cpp AddFrameEntry with two
// BFME2 adaptations attested by retail bytes:
// - AddLogGroup is virtual at vtable slot 0xB4 (45), so it is declared
//   virtual here after 45 placeholder slots to reproduce the indirect call.
// - The non-log filename branch folds both '\\' and '/' via an inline byte
//   loop (no strrchr call), matching retail's separator scan.
// Dedicated TU so the GetFrameEntry TU keeps its matched bodies.

extern void *DebugAllocMemory(unsigned int size);


class Debug
{
public:
	// 45 placeholder virtuals place AddLogGroup at slot 0xB4.
	virtual void pad00();
	virtual void pad01();
	virtual void pad02();
	virtual void pad03();
	virtual void pad04();
	virtual void pad05();
	virtual void pad06();
	virtual void pad07();
	virtual void pad08();
	virtual void pad09();
	virtual void pad10();
	virtual void pad11();
	virtual void pad12();
	virtual void pad13();
	virtual void pad14();
	virtual void pad15();
	virtual void pad16();
	virtual void pad17();
	virtual void pad18();
	virtual void pad19();
	virtual void pad20();
	virtual void pad21();
	virtual void pad22();
	virtual void pad23();
	virtual void pad24();
	virtual void pad25();
	virtual void pad26();
	virtual void pad27();
	virtual void pad28();
	virtual void pad29();
	virtual void pad30();
	virtual void pad31();
	virtual void pad32();
	virtual void pad33();
	virtual void pad34();
	virtual void pad35();
	virtual void pad36();
	virtual void pad37();
	virtual void pad38();
	virtual void pad39();
	virtual void pad40();
	virtual void pad41();
	virtual void pad42();
	virtual void pad43();
	virtual void pad44();
	virtual const char *AddLogGroup(const char *fileOrGroup, const char *descr);

private:
	enum FrameStatus
	{
		Unknown,
		Skip,
		NoSkip
	};

	enum FrameType
	{
		FrameTypeAssert = 1,
		FrameTypeCheck = 2,
		FrameTypeLog = 4
	};

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
	enum { FRAME_HASH_ALLOC_COUNT = 100 };

	// vtable pointer occupies +0x00; prefix pads to frameHash at +0x18.
	char m_prefix[0x14];
	FrameHashEntry *frameHash[FRAME_HASH_SIZE];
	FrameHashEntry *nextUnusedFrameHash;
	unsigned int numAvailableFrameHash;

	FrameHashEntry *AddFrameEntry(unsigned int addr, unsigned int type,
		const char *fileOrGroup, int line);
};

// ?AddFrameEntry@Debug@@AAEPAUFrameHashEntry@1@IIPBDH@Z
Debug::FrameHashEntry *Debug::AddFrameEntry(unsigned int addr, unsigned int type,
	const char *fileOrGroup, int line)
{
	if (!numAvailableFrameHash)
	{
		numAvailableFrameHash = FRAME_HASH_ALLOC_COUNT;
		nextUnusedFrameHash = (FrameHashEntry *)DebugAllocMemory(
			numAvailableFrameHash * sizeof(FrameHashEntry));
	}
	FrameHashEntry *entry = nextUnusedFrameHash++;
	--numAvailableFrameHash;

	entry->next = frameHash[addr % FRAME_HASH_SIZE];
	entry->frameAddr = addr;
	entry->frameType = type;
	entry->line = line;
	entry->status = Unknown;
	entry->hits = 0;

	if (type & FrameTypeLog)
	{
		entry->fileOrGroup = AddLogGroup(fileOrGroup, 0);
	}
	else if (fileOrGroup)
	{
		const char *lastSeparator = fileOrGroup;
		const char *cursor = fileOrGroup;
		char current = *cursor;
		if (current)
		{
			for (;;)
			{
				if (current == '\\' || current == '/')
					lastSeparator = cursor + 1;
				current = *++cursor;
				if (!current)
					break;
			}
		}
		entry->fileOrGroup = lastSeparator;
	}
	else
	{
		entry->fileOrGroup = 0;
	}

	frameHash[addr % FRAME_HASH_SIZE] = entry;
	return entry;
}
