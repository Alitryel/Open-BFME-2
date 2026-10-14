// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies from .text gaps no ledger row covered (seat-5
// batch A). Retail bytes establish every shape; owning classes are not
// recovered, so each keeps an address-derived name and a view of only the
// members it touches. Callees and globals use the ledger's existing spellings.

class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

// --- 0x005742CD (80B): the object the rowed 0x0042D71A getter yields, when
// it and TheLivingWorldLogic exist, gets virtual +4 with the logic's +0xFC
// count plus one, then virtual +0x14 with the rowed 0x002B3DD0 value when the
// rowed 0x002B2BAA guard holds, else a tail call of virtual +0x18.
class Rva005742CDTarget
{
public:
	virtual void v00();
	virtual void v04(int value);
	virtual void v08();
	virtual void v0C();
	virtual void v10();
	virtual void v14(int value);
	virtual void v18();
};

class Rva002B4650
{
public:
	bool rva002B2BAA();										// 0x002B2BAA
	int rva002B3DD0();										// 0x002B3DD0
};

struct Rva005742CDLogicView
{
	char m_pad00[0xFC];
	int m_FC;
};

class Rva0042D71A
{
public:
	int get() const;										// 0x0042D71A
	void rva005742CD();
};

void Rva0042D71A::rva005742CD()
{
	Rva005742CDTarget *target = (Rva005742CDTarget *)get();
	if (target && TheLivingWorldLogic)
	{
		target->v04(((Rva005742CDLogicView *)TheLivingWorldLogic)->m_FC + 1);
		if (((Rva002B4650 *)TheLivingWorldLogic)->rva002B2BAA())
		{
			int value = ((Rva002B4650 *)TheLivingWorldLogic)->rva002B3DD0();
			target->v14(value);
		}
		else
			target->v18();
	}
}

// --- 0x0057431D (27B): derived constructor over the rowed 0x005CB8AC base
// (vtable 0x00874DA8); stores its argument at +8 under vtable 0x00C6E39C.
// The CommonBehavior::Impl constructor (0x005752F0) calls it for its +0x48
// member.
class Rva005CB4E6Elem;
class Rva005CB8D4
{
public:
	Rva005CB8D4();											// 0x005CB8AC
	virtual ~Rva005CB8D4();									// 0x005CB8D4
private:
	Rva005CB4E6Elem *m_elem;
};

class Rva0057431D : public Rva005CB8D4
{
public:
	Rva0057431D(void *owner);
	virtual ~Rva0057431D();
private:
	void *m_owner;
};

Rva0057431D::Rva0057431D(void *owner)
{
	m_owner = owner;
}

// --- 0x00574479 (32B): derived constructor over the rowed 0x00221635 base
// (its int argument passed through), vtable 0x00C6E3A8, +8 and +0xC zeroed.
// The zeroing runs after the vptr store, as member constructors do: plain
// int members let cl schedule the stores ahead of the vptr.
class Rva00221635
{
public:
	Rva00221635(int arg);									// 0x00221635
	virtual void _pure() = 0;
private:
	void *m_ptr;
};

struct Rva00574479Slot
{
	Rva00574479Slot() : m_ptr(0) {}
	void *m_ptr;
};

class Rva00574479 : public Rva00221635
{
public:
	Rva00574479(int arg);
	virtual void _pure();
private:
	Rva00574479Slot m_08;
	Rva00574479Slot m_0C;
};

Rva00574479::Rva00574479(int arg) : Rva00221635(arg)
{
}

// --- 0x00580154 (30B): three-way compare of two flags: 0 when equal, else 1
// when the first is set and -1 when it is clear. No direct reference.
class Rva00580154
{
public:
	int rva00580154(bool a, bool b) const;
};

int Rva00580154::rva00580154(bool a, bool b) const
{
	return a != b ? (a ? 1 : -1) : 0;
}

// --- 0x005C43CF, 0x005C459E, 0x005C47F0 (24B each): derived constructors
// over the rowed registration base 0x0052B894 (name passed through), each
// then installing its own vtable (0x00C745A0, 0x00C74698, 0x00C7475C).
class AsciiString;
class Rva0052B894Registration
{
public:
	Rva0052B894Registration(const AsciiString &name);		// 0x0052B894
	virtual void slot0();
};

#define SEAT5_REGISTRATION_CTOR(RVA) \
class Rva##RVA##Registration : public Rva0052B894Registration \
{ \
public: \
	Rva##RVA##Registration(const AsciiString &name); \
	virtual void slot0(); \
}; \
Rva##RVA##Registration::Rva##RVA##Registration(const AsciiString &name) \
	: Rva0052B894Registration(name) \
{ \
}

SEAT5_REGISTRATION_CTOR(005C43CF)
SEAT5_REGISTRATION_CTOR(005C459E)
SEAT5_REGISTRATION_CTOR(005C47F0)

// --- 0x005F5FD9 (24B): Apt callback shape of the rowed
// ArmyMemberIconMovieClip::Impl::OnClicked (0x005FC6B7): unless the Apt
// window manager's +0x318 mode is set, forward to virtual slot 3 of the +0
// owner.
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;

struct Rva005F5FD9AptMode
{
	unsigned char m_pad000[0x318];
	int m_mode;
};

class Rva005F5FD9Owner
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
};

class Rva005F5FD9
{
public:
	void rva005F5FD9(const char *path);
private:
	Rva005F5FD9Owner *m_owner;
};

void Rva005F5FD9::rva005F5FD9(const char *)
{
	if (((Rva005F5FD9AptMode *)g_bfmeAptWindowManager)->m_mode == 0)
		m_owner->v03();
}
