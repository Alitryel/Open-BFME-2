// ?rva006D17F0@AptLinker@@QAEXXZ
// partial score=0.407 date=2026-10-17
// ?rva006D17F0@AptLinker@@QAEXXZ
// partial score=0.601 date=2026-10-15
// ?rva006D17F0@AptLinker@@QAEXXZ
// partial score=0.6 date=2026-10-14
// ?rva006D17F0@AptLinker@@QAEXXZ
// partial score=0.6 date=2026-10-14
// Bank draft of the Apt linker tick. WB 1752E70 (1211B) is the same source at
// 1.03x; body transcribed from WB + retail 0x006D17F0 (1175B). Containers are
// the EA Apt {count,capacity,data} vector at this+4 and the {value,next} node
// chain at this+0. Unrowed data globals are extern-only placeholders.
// cl: /O2 /MD /EHsc
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <new>

class EAStringC
{
public:
	const char *rva00620090() const;
	unsigned int rva006D3750() const;
private:
	void *m_data;
};

class Rva006D0280
{
public:
	int m_useCount;		// +0x00
	int m_unused4;		// +0x04
	EAStringC m_name8;	// +0x08
	int m_typeC;		// +0x0c
	int m_argument10;	// +0x10
	void *m_object14;	// +0x14
	void *m_buffer18;	// +0x18
	~Rva006D0280();
};

class Rva006DB270
{
public:
	void freeBlock(void *block, int size);
};

class Rva006DB160
{
public:
	void *allocBlock(int size);
};

class Rva006D0A30List
{
public:
	void rva006D1680();
};

// 0x00E176E8 chain-block allocator singleton.
extern Rva006DB270 *g_pChainBlockAllocator;
// 0x00E176D4 playback flag; 0x00E176EC checkpoints; 0x00E176CC load list.
extern int g_bfmeAptFlagAtE176D4;
extern void *g_aptPlaybackCheckpoints;
extern void *g_rva00A176CC;
// Diagnostics state (0x00E176F0, 0x00E17708, 0x00E17740, 0x00E17754).
extern int g_rva00891FA0Value;
extern int g_rva00891FA0Ready;
extern void (__cdecl *Rva00891FA0SendRecord)(const void *, unsigned int);
extern void (__cdecl *g_rva00A17754)(const char *, const char *);

class BfmeRefDB
{
public:
	int m_bfmeCount;	// +0x00
};

class BfmeHolderDB
{
public:
	BfmeHolderDB(void) { m_bfmeRef = 0; }
	BfmeHolderDB(const BfmeHolderDB &other)
	{
		BfmeRefDB *ref = other.m_bfmeRef;
		m_bfmeRef = ref;
		if (ref)
			++ref->m_bfmeCount;
	}
	~BfmeHolderDB(void)
	{
		if (m_bfmeRef && --m_bfmeRef->m_bfmeCount == 0)
		{
			((Rva006D0280 *)m_bfmeRef)->~Rva006D0280();
			g_pChainBlockAllocator->freeBlock(m_bfmeRef, 0x1c);
		}
	}
	BfmeRefDB *m_bfmeRef;	// +0x00
};

class Gen_00895650
{
public:
	BfmeHolderDB bfmeGet(void) const;
	int m_bfmeHead;		// +0x00
	Rva006D0280 *m_holder;	// +0x04
	void *m_cih;		// +0x08
	unsigned char m_state;	// +0x0c
};

class Rva008A2BA0Handle
{
public:
	Rva008A2BA0Handle(BfmeRefDB *ref) : m_ref((int *)ref) { if (m_ref) ++*m_ref; }
	Rva008A2BA0Handle(const Rva008A2BA0Handle &other) : m_ref(other.m_ref) { if (m_ref) ++*m_ref; }
	~Rva008A2BA0Handle() { if (m_ref) --*m_ref; }
	int *m_ref;
};

class Rva008A2C80
{
public:
	Rva008A2C80(Rva008A2BA0Handle handle);
};

class AptCharacterAnimationInst
{
public:
	int getSwfVersion();
};

extern int Rva006CD220Get();
extern void Rva006CD210Set(int version);

class AptCIH
{
public:
	void rva006E2690(int clear);
	void *rva006CFF40() const;
	void rva006E2D60();
};

class AptValue
{
public:
	void setIsDefined(bool defined);
};

class AptLinker;
class BfmeAptValue006DCD20
{
private:
	friend class AptLinker;
	void setTypeAt006DBBC0(int type);
public:
	bool isUndefined() const;
};

class Rva006DBB30SarDwordField
{
public:
	int get() const;
};

class AptAnimationPoolData
{
public:
	void rva006E6540();
};

class Rva004A9DF3Element
{
public:
	Rva004A9DF3Element();
	~Rva004A9DF3Element();
private:
	void *m_value;	// retail's array helper constructs 2 elements of 4 bytes
};

class ModuleTagString
{
public:
	ModuleTagString() : m_count(0), m_capacity(0), m_data(m_inline) {}
	void swap(ModuleTagString &other);
	~ModuleTagString();
private:
	int m_count;		// +0x00
	int m_capacity;		// +0x04
	void *m_data;		// +0x08
	Rva004A9DF3Element m_inline[2];	// +0x0c
};

class Gen_uw_00893e70
{
public:
	void Rva00895340();
};
extern void (__cdecl *g_bfmeAptAssertAtE17734)(const char *test, const char *file, int line);
extern int g_bfmeAptBreakOnAssertAtDDC01C;
extern void *g_bfmeAptPtrAtE176D0;

struct BfmeLoadNode
{
	Gen_00895650 *m_value;	// +0x00
	BfmeLoadNode *m_next;	// +0x04
};

class AptLinker
{
public:
	void rva006D17F0();
	BfmeLoadNode *m_chain;	// +0x00
	int m_count;		// +0x04
	int m_capacity;		// +0x08
	int **m_data;		// +0x0c
};

#define SPRITE_ASSERT(cih) do { \
	if (((BfmeAptValue006DCD20 *)(cih))->isUndefined() || \
		(((Rva006DBB30SarDwordField *)(cih))->get() != 0xd && \
		 ((Rva006DBB30SarDwordField *)(cih))->get() != 0x12)) { \
		g_bfmeAptAssertAtE17734("isSpriteInstBase()", \
			"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d); \
		if (g_bfmeAptBreakOnAssertAtDDC01C) \
			__debugbreak(); } } while (0)

void AptLinker::rva006D17F0()
{
	((Rva006D0A30List *)g_rva00A176CC)->rva006D1680();

	int i = 0;
	if ((1 ? g_bfmeAptFlagAtE176D4 != 0 : g_bfmeAptFlagAtE176D4 != 0))
	{
		int *cp = (int *)g_aptPlaybackCheckpoints;
		char *items = (char *)cp[2];
		int n = cp[0];
		for (; (1 ? i != n : i != n); ++i)
		{
			int state = *(int *)(items + 4);
			if ((1 ? state != 3 : state != 3) && state != 2)
				return;
			items += 8;
		}
	}

	int savedCount = (1 ? m_count : m_count);
	AptLinker *self = this;
	int **cursor = m_data;
	int zero = 0;
	*(volatile int*)&zero = zero;
	for (;;)
	{
		int **end = m_data + m_count;
		if ((1 ? (cursor == end) : (cursor == end)))
			break;
		Rva006D0280 *elem = (Rva006D0280 *)*cursor;
		if (elem)
			++elem->m_useCount;

		for (BfmeLoadNode *node = self->m_chain; node != 0; node = node->m_next)
		{
			Gen_00895650 *value = node->m_value;
			if (value)
				_ReadWriteBarrier();
				++value->m_bfmeHead;
			bool match;
			{
				BfmeHolderDB holder = value->bfmeGet();
				match = ((Rva006D0280 *)holder.m_bfmeRef == elem) && (value->m_state == 0);
			}
			if (match)
			{
				Rva008A2C80 *inst = 0;
				void *raw = ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(0x38);
				if (raw)
					inst = new (raw) Rva008A2C80(Rva008A2BA0Handle((BfmeRefDB *)elem));
				AptCIH *cih = (AptCIH *)value->m_cih;
				if (Rva006CD220Get() == 0)
					Rva006CD210Set(((AptCharacterAnimationInst *)inst)->getSwfVersion());
				cih->rva006E2690(1);
				((BfmeAptValue006DCD20 *)cih)->setTypeAt006DBBC0(0x12);
				*(void **)((char *)cih + 0x4c) = inst;
				((AptValue *)cih)->setIsDefined(true);

				SPRITE_ASSERT(cih);
				void *base = cih->rva006CFF40();
				*(int *)((char *)base + 0x18) = -1;
				SPRITE_ASSERT(cih);
				base = cih->rva006CFF40();
				*(int *)((char *)base + 0x1c) |= 0x1000000;
				cih->rva006E2D60();

				value->m_state = 1;

				if (g_rva00A17754 != 0)
				{
					const char *a = ((EAStringC *)((char *)cih + 8))->rva00620090();
					const char *b = ((EAStringC *)((char *)elem + 8))->rva00620090();
					g_rva00A17754(a, b);
				}
				if (g_rva00891FA0Ready != 0)
				{
					_ReadWriteBarrier();
					EAStringC *name = (EAStringC *)((char *)elem + 8);
					unsigned int len = name->rva006D3750();
					char record[0x108];
					*(volatile int *)(record + 0) = g_rva00891FA0Value;
					record[4] = 6;
					const char *src = name->rva00620090();
					char *dst = record + 5;
					while ((*dst++ = *src++) != 0) {}
					Rva00891FA0SendRecord(record, len + 6);
				}
			}

			if (value)
			{
				if (--value->m_bfmeHead == 0)
				{
					Rva006D0280 *load = value->m_holder;
					if (load != 0 && --load->m_useCount == 0)
					{
						load->~Rva006D0280();
						g_pChainBlockAllocator->freeBlock(load, 0x1c);
					}
					g_pChainBlockAllocator->freeBlock(value, 0x10);
				}
			}
		}

		if (elem)
		{
			if (--elem->m_useCount == 0)
			{
				elem->~Rva006D0280();
				g_pChainBlockAllocator->freeBlock(elem, 0x1c);
			}
		}

		if (m_count != savedCount)
		{
			savedCount = m_count;
			cursor = m_data;
		}
		else
		{
			++cursor;
		}
	}

	if (g_bfmeAptFlagAtE176D4)
		((Gen_uw_00893e70 *)g_aptPlaybackCheckpoints)->Rva00895340();

	if (savedCount > 0)
	{
		{ ModuleTagString temp;
		((ModuleTagString *)&m_count)->swap(temp);
		((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->rva006E6540();
		}
	}
}
