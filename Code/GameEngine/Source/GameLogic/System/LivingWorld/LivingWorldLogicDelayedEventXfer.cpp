// cl: /Ireference/shims/moduledata /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native 2BB49C..2BB5DD RET8: counted transfer of a delayed-event pointer
// vector, called twice by both stream bodies 2BB5DD and 2BBA45 (this, xfer,
// vector). Load reads a kind through rowed 2B2275 and builds one of four
// events: inlined ctors installing vtables BFE024 (kind 1) and BFE1B0
// (kind 2), each nulling +0x0C; BFE058 (kind 4, 0x20-byte object); rowed
// ctor 2BAE57 (kind 8, 0x1C bytes); then the event's xfer slot and the
// rowed 49-byte push_back 4DFCB0. Save takes each element's kind from slot
// 6, transfers it, then calls the element's xfer slot. Event class names
// remain address-derived; their common base is a structural inference from
// the shared slot use, not a target name.
#include <vector>
#include "Common/Snapshot.h"

typedef int Int;
typedef bool Bool;

class Xfer {public:
virtual void s0(); virtual bool IsLoading() const; virtual void s2(); virtual bool IsCRC() const;
virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7(); virtual void s8();
virtual void s9(); virtual void s10(); virtual void s11(); virtual void s12(); virtual void s13();
virtual void s14(); virtual void s15(); virtual void s16(); virtual void s17(); virtual void s18();
virtual void s19(); virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27(); virtual void s28();
virtual void s29(); virtual void s30(); virtual void xferInt(Int*);
};

struct Rva002B2275Obj;
int __cdecl Rva002B2275Get(Rva002B2275Obj *xfer, void *type);

class Rva002BB49CEvent : public Snapshot
{
public:
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual Bool slot4();
	virtual void slot5();
	virtual Int getType();
};

class OpaqueRefCounted;
struct Rva000A8C9B
{
	OpaqueRefCounted *m_ptr;
	Rva000A8C9B() : m_ptr(0) {}
};
class Rva003FD3EF : public Rva002BB49CEvent
{
public:
	virtual ~Rva003FD3EF();
	char m_pad04[8];
	Rva000A8C9B m_0c;
};

template <typename T> class StringBase
{
public:
	StringBase() : m_data(0) {}
	T *m_data;
};
class Rva003FD4DA : public Rva002BB49CEvent
{
public:
	virtual ~Rva003FD4DA();
	char m_pad04[8];
	StringBase<char> m_0c;
};

class Rva002B30CA : public Rva002BB49CEvent
{
public:
	virtual ~Rva002B30CA();
	char m_pad04[0x1C];
};

class Rva003C2F40Owner : public Rva002BB49CEvent
{
public:
	Rva003C2F40Owner();
	virtual ~Rva003C2F40Owner();
	char m_pad04[0x18];
};

struct RecVec : public _STL::vector<Rva002BB49CEvent *> {};

class Rva002BB49C {public: void rva002BB49C(Xfer *, RecVec *);};

void Rva002BB49C::rva002BB49C(Xfer *xfer, RecVec *records)
{
	Int count = records->size();
	xfer->xferInt(&count);
	if (xfer->IsLoading())
	{
		for (Int i = 0; i < count; ++i)
		{
			Int type;
			Rva002B2275Get((Rva002B2275Obj *)xfer, &type);
			switch (type)
			{
				case 1:
				{
					Rva003FD3EF *event = new Rva003FD3EF;
					event->xfer(xfer);
					records->push_back(event);
					break;
				}
				case 2:
				{
					Rva003FD4DA *event = new Rva003FD4DA;
					event->xfer(xfer);
					records->push_back(event);
					break;
				}
				case 4:
				{
					Rva002B30CA *event = new Rva002B30CA;
					event->xfer(xfer);
					records->push_back(event);
					break;
				}
				case 8:
				{
					Rva003C2F40Owner *event = new Rva003C2F40Owner;
					event->xfer(xfer);
					records->push_back(event);
					break;
				}
			}
		}
	}
	else
	{
		for (Int i = 0; i < count; ++i)
		{
			Int type = (*records)[i]->getType();
			Rva002B2275Get((Rva002B2275Obj *)xfer, &type);
			(*records)[i]->xfer(xfer);
		}
	}
}
