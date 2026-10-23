extern "C" const void *const vtbl_00BBBC30[];  // ??_7?$basic_streambuf@DV?$char_traits@D@_STL@@@_STL@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00BBBC30=??_7?$basic_streambuf@DV?$char_traits@D@_STL@@@_STL@@6B@")

extern "C" unsigned char bfmeVftTL[];

class BfmeLocaleShim
{
public:
	static void bfmeLocaleCtor(void);
};

struct BfmeListNodeTL
{
	void *m_next;
	void *m_previous;
	void *m_value;
};

struct BfmeListTL
{
	BfmeListNodeTL m_head;
	unsigned char m_padding[0x14];
};

class StdioStreambufBase
{
public:
	StdioStreambufBase *bfmeBaseTL(void *what, int flag);
	StdioStreambufBase *bfmeInitTL(void *what);
	void *m_bfmeVft;
	void * volatile m_get;
	void * volatile m_put;
	BfmeListTL m_defaultGet;
	BfmeListTL m_defaultPut;
	unsigned char m_bfmeLocale[4];
	volatile unsigned int m_lock;
	void *m_file;
};

// ?bfmeBaseTL@StdioStreambufBase@@QAEPAV1@PAXH@Z		97 bytes
// The retail compiler schedules this LEA before the volatile field store;
// MSVC 7.1 does not reproduce that order from clean C++ alone.
__declspec(noinline) StdioStreambufBase *StdioStreambufBase::bfmeBaseTL(void *what, int flag)
{
	void *baseWhat = what;
	void *baseFlag = reinterpret_cast<void *>(static_cast<unsigned int>(flag));
	m_bfmeVft = reinterpret_cast<void *>(((unsigned int)vtbl_00BBBC30));
	m_get = baseWhat != 0 ? baseWhat : &m_defaultGet.m_head;
	void *resolvedBaseFlag = baseFlag != 0 ? baseFlag : &m_defaultPut.m_head;
	__asm { lea ecx, [esi+0x4c] }
	m_put = resolvedBaseFlag;
	BfmeLocaleShim::bfmeLocaleCtor();
	BfmeListNodeTL *baseWhatNode =
		(m_lock = 0, m_lock = 0,
		 static_cast<BfmeListNodeTL *>(m_get));
	if (baseWhatNode == &m_defaultGet.m_head)
	{
		baseWhatNode->m_value = 0;
		baseWhatNode->m_next = 0;
		baseWhatNode->m_previous = 0;
	}
	BfmeListNodeTL *baseFlagHead = &m_defaultPut.m_head;
	BfmeListNodeTL *baseFlagNode = static_cast<BfmeListNodeTL *>(m_put);
	if (baseFlagNode == baseFlagHead)
	{
		baseFlagNode->m_value = 0;
		baseFlagNode->m_next = 0;
		baseFlagNode->m_previous = 0;
	}
	return this;
}

StdioStreambufBase *StdioStreambufBase::bfmeInitTL(void *what)
{
	bfmeBaseTL(what, 0);
	m_file = what;
	m_bfmeVft = bfmeVftTL;
	return this;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:_bfmeVftTL=??_7stdio_streambuf_base@_SgI@@6B@")

// RTTI names the vtable installed by bfmeInitTL as _SgI::stdio_streambuf_base.
// Retail callers in ios_base::_S_initialize and sync_with_stdio invoke this
// 32-byte body at RVA 0x0001CDB0: one FILE* argument, thiscall, ret 4, and
// this returned in EAX. The existing opaque view has that same ABI and layout.
#pragma comment(linker, "/alternatename:??0stdio_streambuf_base@_SgI@@QAE@PAU_iobuf@@@Z=?bfmeInitTL@StdioStreambufBase@@QAEPAV1@PAX@Z")
