// ?rva006D17F0@AptLinker@@QAEXXZ
// partial score=0.98 date=2026-10-19
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
#include <string.h>

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
	__forceinline int decreaseCount() { return --m_useCount; }
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
class Rva006CEB10Playback;
extern Rva006CEB10Playback *g_aptPlaybackCheckpoints;
extern void *g_rva00A176CC;
// Diagnostics state (0x00E176F0, 0x00E17708, 0x00E17740, 0x00E17754).
extern int g_rva00891FA0Value;
extern int g_rva00891FA0Ready;
extern "C" void (__cdecl *Rva00891FA0SendRecord)(const void *, unsigned int);
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
	BfmeHolderDB(BfmeRefDB *ref) : m_bfmeRef(ref) { if (ref) ++ref->m_bfmeCount; }
	BfmeHolderDB(const BfmeHolderDB &other)
	{
		BfmeRefDB *ref = other.m_bfmeRef;
		m_bfmeRef = ref;
		if (ref)
			++ref->m_bfmeCount;
	}
	~BfmeHolderDB(void)
	{
		BfmeRefDB *counted = m_bfmeRef;
		if (counted && (--counted->m_bfmeCount, counted->m_bfmeCount == 0))
		{
			Rva006D0280 *object = (Rva006D0280 *)m_bfmeRef;
			object->~Rva006D0280();
			g_pChainBlockAllocator->freeBlock(object, 0x1c);
		}
	}
	BfmeRefDB *m_bfmeRef;	// +0x00
};

class Gen_00895650
{
public:
	BfmeHolderDB bfmeGet(void) const;
	int m_bfmeHead;		// +0x00
	__forceinline int decreaseCount() { return --m_bfmeHead; }
	Rva006D0280 *m_holder;	// +0x04
	void *m_cih;		// +0x08
	unsigned char m_state;	// +0x0c
};

class Rva006D17F0ValueHandle
{
public:
    Rva006D17F0ValueHandle(Gen_00895650 *value) : m_value(value)
    {
        if (value) ++value->m_bfmeHead;
    }
    ~Rva006D17F0ValueHandle()
    {
        if (m_value && m_value->decreaseCount() == 0)
        {
            Rva006D0280 *load = m_value->m_holder;
            if (load && load->decreaseCount() == 0)
            {
                Rva006D0280 *object = m_value->m_holder;
                if (object)
                {
                    object->~Rva006D0280();
                    g_pChainBlockAllocator->freeBlock(object, 0x1c);
                }
            }
            g_pChainBlockAllocator->freeBlock(m_value, 0x10);
        }
    }
    Gen_00895650 *m_value;
};

class Rva008A2BA0Handle
{
public:
	Rva008A2BA0Handle(BfmeRefDB *ref) : m_ref((int *)ref) { if (m_ref) ++*m_ref; }
	Rva008A2BA0Handle(const Rva008A2BA0Handle &other) : m_ref(other.m_ref) { if (m_ref) ++*m_ref; }
	~Rva008A2BA0Handle()
    {
        int *counted = m_ref;
        if (counted && (--*counted, *counted == 0))
        {
            Rva006D0280 *object = (Rva006D0280 *)m_ref;
            object->~Rva006D0280();
            g_pChainBlockAllocator->freeBlock(object, 0x1c);
        }
    }
	int *m_ref;
};

class Rva008A2C80
{
public:
	Rva008A2C80(Rva008A2BA0Handle handle);
	virtual ~Rva008A2C80();
	static void *operator new(unsigned int n) { return ((Rva006DB160 *)g_pChainBlockAllocator)->allocBlock(n); }
	static void operator delete(void *p, unsigned int n) { g_pChainBlockAllocator->freeBlock(p, n); }
	char m_unknown04[0x34];
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
	void ClearCIH(int clear);
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
	int m_value;
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

inline void rva006D17F0IteratorCheck(bool, const char *) {}

struct Rva006D17F0Iterator
{
    bool operator!=(const Rva006D17F0Iterator &other) const
    {
        rva006D17F0IteratorCheck(begin == other.begin && end == other.end, "Iterators are not in same range");
        return position != other.position;
    }
    int *&operator*() const
    {
        rva006D17F0IteratorCheck(position >= begin && position < end, "Trying to dereference an invalid iterator");
        return *position;
    }
    int **position;
    int **begin;
    int **end;
    Rva006D17F0Iterator(int **p, int **b, int **e) : position(p), begin(b), end(e) {}
};

struct BfmeLoadNode
{
	Gen_00895650 *m_value;	// +0x00
	BfmeLoadNode *m_next;	// +0x04
};

class Rva006D17F0Vector
{
public:
    int size() const { return m_count; }
    Rva006D17F0Iterator begin() { return Rva006D17F0Iterator(m_data, m_data, m_data + m_count); }
    Rva006D17F0Iterator end() { return Rva006D17F0Iterator(m_data + m_count, m_data, m_data + m_count); }
    int m_count;
    int m_capacity;
    int **m_data;
    int *m_inline[2];
};

class AptLinker
{
public:
    void rva006D17F0();
    BfmeLoadNode *m_chain;
    Rva006D17F0Vector m_pending;
};

// +0x00
// +0x04
// +0x08
// +0x0c

#define SPRITE_ASSERT(cih) do { \
	if (((BfmeAptValue006DCD20 *)(cih))->isUndefined() || \
		(((Rva006DBB30SarDwordField *)(cih))->get() != 0xd && \
		 ((Rva006DBB30SarDwordField *)(cih))->get() != 0x12)) { \
		g_bfmeAptAssertAtE17734("isSpriteInstBase()", \
			"c:\\projects\\bfme2patch103\\bfme2\\code\\libraries\\source\\apt\\AptCIH.h", 0x7d); \
		if (g_bfmeAptBreakOnAssertAtDDC01C) \
			__debugbreak(); } } while (0)

class AptValueNameEntry
{
public:
    EAStringC m_name;
    int m_value;
};
typedef AptValueNameEntry PlaybackItem;
inline void iteratorCheck(bool, const char *) {}
class PlaybackIterator
{
    PlaybackItem *cur, *first, *last;
public:
    PlaybackIterator(PlaybackItem *c, PlaybackItem *f, PlaybackItem *l) : cur(c), first(f), last(l) {}
    PlaybackIterator &operator++() { ++cur; return *this; }
    PlaybackItem &operator*()
    {
        iteratorCheck(cur >= first && cur < last, "Trying to dereference an invalid iterator");
        return *cur;
    }
    bool operator!=(const PlaybackIterator &other)
    {
        iteratorCheck(first == other.first && last == other.last, "Iterators are not in same range");
        return cur != other.cur;
    }
};
class PlaybackRange
{
    PlaybackItem *first, *last;
public:
    PlaybackRange(PlaybackItem *f, PlaybackItem *l) : first(f), last(l) {}
    PlaybackIterator begin() { return PlaybackIterator(first, first, last); }
    PlaybackIterator end() { return PlaybackIterator(last, first, last); }
};
class Rva006CEB10Playback
{
public:
    int size, capacity;
    PlaybackItem *items;
    PlaybackItem inlineItems[2];
    PlaybackIterator begin() { return PlaybackRange(items, items + size).begin(); }
    PlaybackIterator end() { return PlaybackRange(items, items + size).end(); }
    __forceinline bool readyFor(int a, int b)
    {
        for (PlaybackIterator it = begin(); it != end(); ++it)
            if ((*it).m_value != a && (*it).m_value != b) return false;
        return true;
    }
};

__forceinline void *AptCIH::rva006CFF40() const
{
    SPRITE_ASSERT(this);
    return *(void **)((char *)this + 0x4c);
}

struct Rva006D17F0Record
{
    int value;
    unsigned char kind;
    char text[255];
};

void AptLinker::rva006D17F0()
{
    ((Rva006D0A30List *)g_rva00A176CC)->rva006D1680();
    if (g_bfmeAptFlagAtE176D4 &&
        !g_aptPlaybackCheckpoints->readyFor(3, 2)) return;

    int savedCount = m_pending.size();
    Rva006D17F0Iterator cursor = m_pending.begin();
    for (;;)
    {
        if (!(cursor != m_pending.end())) break;
        bool restarted = false;
        Rva008A2BA0Handle element(*(const Rva008A2BA0Handle *)&*cursor);
        for (BfmeLoadNode *node = m_chain; node; node = node->m_next)
        {
            Rva006D17F0ValueHandle owner(node->m_value);
            Gen_00895650 *value = owner.m_value;
            if (((Rva006D0280 *)value->bfmeGet().m_bfmeRef == (Rva006D0280 *)element.m_ref) && value->m_state == 0)
            {
                Rva008A2C80 *inst = new Rva008A2C80(element);
                AptCIH *cih = (AptCIH *)value->m_cih;
                if (Rva006CD220Get() == 0)
                    Rva006CD210Set(((AptCharacterAnimationInst *)inst)->getSwfVersion());
                cih->ClearCIH(1);
                ((BfmeAptValue006DCD20 *)cih)->setTypeAt006DBBC0(0x12);
                *(void **)((char *)cih + 0x4c) = inst;
                ((AptValue *)cih)->setIsDefined(true);
                void *base = cih->rva006CFF40();
                *(int *)((char *)base + 0x18) = -1;
                base = cih->rva006CFF40();
                *(int *)((char *)base + 0x1c) |= 0x1000000;
                cih->rva006E2D60();
                value->m_state = 1;
                if (g_rva00A17754)
                {
                    g_rva00A17754(((Rva006D0280 *)element.m_ref)->m_name8.rva00620090(),
                        ((EAStringC *)((char *)cih + 8))->rva00620090());
                }
                if (g_rva00891FA0Ready)
                {
                    EAStringC *name = &((Rva006D0280 *)element.m_ref)->m_name8;
                    unsigned int len = name->rva006D3750();
                    Rva006D17F0Record record;
                    record.value = g_rva00891FA0Value;
                    record.kind = 6;
                    strcpy(record.text, name->rva00620090());
                    Rva00891FA0SendRecord(&record, len + 6);
                }
                if (savedCount != m_pending.size())
                {
                    cursor = m_pending.begin();
                    savedCount = m_pending.size();
                    restarted = true;
                    break;
                }
            }
        }
        if (!restarted) ++cursor.position;
    }
    if (g_bfmeAptFlagAtE176D4)
        ((Gen_uw_00893e70 *)g_aptPlaybackCheckpoints)->Rva00895340();
    if (savedCount > 0)
    {
        ModuleTagString temp;
        ((ModuleTagString *)&m_pending)->swap(temp);
        ((AptAnimationPoolData *)g_bfmeAptPtrAtE176D0)->rva006E6540();
    }
}

// Checked iterators preserve range expressions; owners release on both restart and normal exit.
// Evidence and remaining scheduling differences: reverse/attempt_support/aptlinker-006d17f0-w5.md.
