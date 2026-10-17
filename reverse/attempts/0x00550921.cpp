// ?Rva00550921Dispatch@@YAXHHH@Z
// partial score=0.552 date=2026-10-17
// cl: /O1 /DNDEBUG /MD
//
// Small constructors that install a vtable, in two shapes of rowed bodies:
//   18 bytes as ??0Rva005CB22A (V3PolyCopyCtors.cpp): store the vtable, then the
//     pointer argument at +4;
//   13 bytes as ??0NetCommandWrapperList: zero +4, then store the vtable, the
//     order an inlined base constructor followed by the derived vtable store gives.
// Each copy differs from its template only in the vtable it installs. One class
// per copy names that vtable; its destructor is inline and empty so the vtable
// the compiler emits resolves in this unit. The owning classes are not
// recovered, so each keeps its address.

inline void *operator new(unsigned int, void *p) { return p; }
struct RvaSmallVtableZeroBase
{
	void *m_04;
	RvaSmallVtableZeroBase() : m_04(0) {}
};

// ??0Rva000ABD56@@QAE@PAX@Z @0x000ABD56 18B, vtable VA 0xbc957c
class Rva000ABD56
{
public:
	Rva000ABD56(void *p);
	virtual ~Rva000ABD56() {}
private:
	void *m_04;
};

// Structure whose first dword is a sentinel; the handler validates it before
// doing the vtable-style dispatch below.
struct Rva00550921Header
{
	int m_tag;			// must be 0xffffff34
};

// Object with a virtual method at vtable offset +0x20.
struct Rva00550921Sink
{
	virtual void method0();
	virtual void method1();
	virtual void method2();
	virtual void method3();
	virtual void method4();
	virtual void method5();
	virtual void method6();
	virtual void method7();
	virtual void dispatch3(int a, int b, int c);
};

extern Rva00550921Sink *g_pSink_e05fbc;
extern char g_flag_e05fc0;
extern char g_flag_e05fc1;

// Stack scratch record used by the vtable slot call.
struct Rva00550921Args
{
	int m_00;			// = 6
	int m_pad04;
	int m_08;			// = 4
	int m_pad0c;
	int m_10;			// = 6
	char m_pad14[0x80];
	int m_94;			// = 1
	char m_pad98[4];
};

void Rva00550921Dispatch(int a, int b, int c)
{
	if (a != 0)
	{
		if (a == 4)
			g_flag_e05fc0 = 1;
		return;
	}

	Rva00550921Sink *p = (Rva00550921Sink *)c;
	if (!p)
		return;
	if (*(int *)b != (int)0xffffff34)
		return;

	{
		struct { Rva00550921Args v; unsigned char pad[0x7c8]; } args;
		Rva00550921Sink *pSink = g_pSink_e05fbc;
		int parg = (int)&args.v;
		args.v.m_00 = 6;
		args.v.m_08 = 4;
		args.v.m_10 = 6;
		args.v.m_94 = 1;

		pSink->dispatch3(parg, 0, 0);
	}
}
