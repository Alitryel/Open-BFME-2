// ?rva0078a729@@YAXXZ
// partial score=1.0 date=2026-10-18
// cl: /DNDEBUG /MD /EHs
// ??1StancesBehavior@@UAE@XZ retail 0x0045F001 103B
// Own vptrs C424DC (+0), BEFF90 (+0xC) and C424D0 (+0x10); under EH state 1
// the listener list at +0x20 broadcasts this object through the rowed forEach
// 0x0045EF37 with a member-function pointer to the slot-0 forwarder 0x001FF3A9;
// the list's inline dtor frees its block through the rowed CRT free, then the
// rowed first-base dtor ??1UpdateModule@@UAE@XZ 0x0024A797 runs. Native20B
// cleanup 78A729 null-adjusts this to the listener storage at+20: it is a
// secondary base, not a direct member. Constructor45EF80 independently builds
// its16B storage through330757. The two polymorphic secondary views have no
// destructors (no restores); the ownership of opaque bytes14..1F is unknown.
// Same recipe as Rva005C9B76Dtor.cpp; TU-local view of the class.

extern "C" void __cdecl free(void *);

class Rva0045EF37Listener
{
public:
	virtual void notify(void *);
};

class Rva0045EF37List
{
public:
	void forEach(void (Rva0045EF37Listener::*notify)(void *), void *arg);
	~Rva0045EF37List() throw()
	{
		if (m_begin)
			free(m_begin);
	}
	Rva0045EF37Listener **m_begin;
	Rva0045EF37Listener **m_end;
	Rva0045EF37Listener **m_capacity;
	unsigned int m_index;
};

class Rva001FF3A9
{
public:
	virtual void rva001FF3A9();
};

class UpdateModule
{
public:
	virtual ~UpdateModule();
private:
	char m_pad04[8];
};

class StancesBehaviorInterfaceA
{
public:
	virtual void stancesInterfaceA() = 0;
};

class StancesBehaviorInterfaceB
{
public:
	virtual void stancesInterfaceB() = 0;
private:
	// Opaque prefix storage before the proven listener base at+20. This view
	// does not establish the original interface's declared size or fields.
	char m_pad04[12];
};

class StancesBehavior : public UpdateModule, public StancesBehaviorInterfaceA, public StancesBehaviorInterfaceB, private Rva0045EF37List
{
public:
	virtual ~StancesBehavior();
	virtual void stancesInterfaceA();
	virtual void stancesInterfaceB();
private:
	int m_30;
};

StancesBehavior::~StancesBehavior()
{
	Rva0045EF37List::forEach((void (Rva0045EF37Listener::*)(void *))&Rva001FF3A9::rva001FF3A9, this);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?stancesInterfaceA@StancesBehavior@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")
#pragma comment(linker, "/alternatename:?stancesInterfaceB@StancesBehavior@@UAEXXZ=?update@StancesBehavior@@UAE?AW4UpdateSleepTime@@XZ")
