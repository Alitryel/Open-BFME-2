// ?rva002BB49C@Rva002BB49C@@QAEXPAVXfer@@PAURecVec@@@Z
// partial score=0.708758 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
//
// ?rva002BB49C@Rva002BB49C@@QAEXPAVXfer@@PAURecVec@@@Z, retail
// 0x002BB49C..0x002BB5DD (321B, RET 8). Kind factory shared by the
// LivingWorldLogic snapshot xfer: reads the record count, xfers it, and on a
// loading pass builds one of four record kinds (1/2/4/8) and pushes each into
// the vector; on a saving pass it xfers each record's slot-6 value and then
// its slot-0xc payload. The three small kinds carry the vtables at
// 0x00BFE024 (=0x10), 0x00BFE1B0 (=0x10) and 0x00BFE058 (=0x20); the 0x1C
// kind has a real constructor (retail 0x6BAE57). All callees rowed.
typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class Xfer
{
public:
	virtual void slot00();
	virtual Bool isLoading();			// +0x04
	virtual void slot08();
	virtual Bool isCRC();				// +0x0C
	virtual void slot10();
	virtual void slot14();
	virtual void slot18();
	virtual void slot1C();
	virtual void slot20();
	virtual void slot24();
	virtual void xferVersion(void *version);	// +0x28
	virtual void slot2C();
	virtual void slot30();
	virtual void slot34();
	virtual void slot38();
	virtual void slot3C();
	virtual void slot40();
	virtual void slot44();
	virtual void slot48();
	virtual void slot4C();
	virtual void slot50();
	virtual void slot54();
	virtual void slot58();
	virtual void slot5C();
	virtual void slot60();
	virtual void slot64();
	virtual void slot68();
	virtual void slot6C();
	virtual void slot70();
	virtual void slot74();
	virtual void xferUnsignedInt(UnsignedInt &value);	// +0x78
	virtual void xferInt(Int &value);		// +0x7C
	virtual void slot80();
	virtual void slot84();
	virtual void slot88();
	virtual void slot8C();
	virtual void xferBool(Bool &value);		// +0x90
};

// A record kind. Slot 3 (offset 0xC) transfers its payload; slot 6
// (offset 0x18) returns the value the saving pass xfers.
class Rva002BB4Rec
{
public:
	virtual void v0();			// +0x00
	virtual void v1();			// +0x04
	virtual void v2();			// +0x08
	virtual void v3(Xfer *xfer);		// +0x0C
	virtual void v4();			// +0x10
	virtual void v5();			// +0x14
	virtual Int v6();			// +0x18
};

class Rva002BB4Kind1 : public Rva002BB4Rec
{
public:
	char m_pad[0x8];
	Int m_c;				// +0x0C
};

class Rva002BB4Kind2 : public Rva002BB4Rec
{
public:
	char m_pad[0x8];
	Int m_c;				// +0x0C
};

class Rva002BB4Kind4 : public Rva002BB4Rec
{
public:
	char m_pad[0x1C];
};

class Rva002BB4Kind8 : public Rva002BB4Rec
{
public:
	__declspec(noinline) Rva002BB4Kind8();
	char m_pad[0x18];
};

int __cdecl Rva002B2275Get(Xfer *xfer, void *out);

__declspec(noinline) Rva002BB4Kind8::Rva002BB4Kind8()
{
	Rva002B2275Get(0, 0);
}

// retail 0x6B2275: two-way xfer of the discriminated value.
int __cdecl Rva002B2275Get(Xfer *xfer, void *out);

struct RecVec
{
public:
	Rva002BB4Rec **m_begin;			// +0x00
	Rva002BB4Rec **m_end;			// +0x04
	Rva002BB4Rec **m_cap;			// +0x08
	int size() const { return (int)(m_end - m_begin); }
	Rva002BB4Rec *&operator[](int i) { return m_begin[i]; }
	void rva008DFCB0(Rva002BB4Rec *const &value);	// retail 0x8DFCB0
};

class Rva002BB49C
{
public:
	void rva002BB49C(Xfer *xfer, RecVec *records);
};

void Rva002BB49C::rva002BB49C(Xfer *xfer, RecVec *records)
{
	int count = records->size();
	xfer->xferInt(count);
	if (xfer->isLoading())
	{
		for (int i = 0; i < count; i++)
		{
			int kind;
			Rva002B2275Get(xfer, &kind);
			Rva002BB4Rec *item = 0;
			switch (kind)
			{
			case 1: item = new Rva002BB4Kind1(); break;
			case 2: { Rva002BB4Kind2 *k2 = new Rva002BB4Kind2(); k2->m_c = 0; item = k2; } break;
			case 4: item = new Rva002BB4Kind4(); break;
			case 8: item = new Rva002BB4Kind8(); break;
			default: break;
			}
			item->v3(xfer);
			records->rva008DFCB0(item);
		}
	}
	else
	{
		for (int i = 0; i < count; i++)
		{
			Rva002BB4Rec *item = (*records)[i];
			int value = item->v6();
			Rva002B2275Get(xfer, &value);
			item->v3(xfer);
		}
	}
}
