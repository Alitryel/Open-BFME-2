// cl: /MD
//
// Static-init and atexit bodies for four file-scope object arrays, from the
// startup strip and the cleanup-thunk strip. Each array's initializer runs
// the CRT eh vector constructor iterator (0x00629512) over the elements and
// registers the matching cleanup with atexit; each cleanup runs the eh vector
// destructor iterator (0x00629110). As in BfmeConv667.cpp, the iterators are
// reached through their existing stdcall pins, and the element constructor
// and destructor are referenced only as DIR32 function addresses, so their
// spellings here are address-named.
//
//   0x007AEA2C / 0x007B7BBE  20 x 4-byte AsciiString-shaped slots at VA 0x00E01D60
//                            (ctor 0x00326BE6, dtor ~AsciiString 0x0048BA39)
//   0x007AF10C / 0x007B7DD1  2 x 12-byte chat-history vectors g_00E022F8
//                            (LANChatHistory.cpp; ctor closure 0x00256646,
//                            dtor 0x00381AE0)
//   0x007AC207 / 0x007B6C84  the cursorTextures table at VA 0x00DE4B40
//                            (0x498 4-byte texture handles; ctor 0x00326BE6,
//                            dtor 0x0017098D)
//   0x007ABF7B / 0x007B6BB9  8 x 4-byte texture handles at VA 0x00DE1F8C
//                            (ctor 0x00326BE6, dtor 0x0017098D)
//   0x007B93EC               cleanup of the function-local static array of 30
//                            12-byte points at VA 0x00E060B8 that the unrowed
//                            body around 0x0055DDF8 builds under guard bit
//                            0x00E06220 (ctor 0x0047A6A9, empty dtor 0x000B3FD0)

extern "C" int __cdecl atexit(void (__cdecl *)(void));

void __stdcall rva00906340VecCtor(void *obj, unsigned int size, int count, void (*ctor)(void *), void (*dtor)(void *));
void __stdcall bfmeRegisterDAB(void *obj, unsigned int size, unsigned int count, void (*dtor)(void *));

extern "C" void Rva00326BE6NullFirstWordCtor(void *);
extern "C" void Rva0048BA39AsciiStringDtor(void *);
extern "C" void Rva00256646VectorCtorClosure(void *);
extern "C" void Rva00381AE0VectorDtor(void *);
extern "C" void Rva0017098DTextureHandleDtor(void *);
extern "C" void Rva000B3FD0EmptyPointDtor(void *);

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A> class vector;
}
struct BfmeStringRecord005DDD40;
extern _STL::vector<BfmeStringRecord005DDD40, _STL::allocator<BfmeStringRecord005DDD40> > g_00E022F8[2];

struct CursorTextureSlot;
extern CursorTextureSlot cursorTextures[][21];

extern unsigned g_Va00E01D60[20];
extern unsigned g_Va00DE1F8C[8];
extern unsigned g_Va00E060B8[90];

void __cdecl rva007B7BBE()
{
	bfmeRegisterDAB(g_Va00E01D60, 4, 0x14, Rva0048BA39AsciiStringDtor);
}

void __cdecl rva007B7DD1()
{
	bfmeRegisterDAB(g_00E022F8, 0xC, 2, Rva00381AE0VectorDtor);
}

void __cdecl rva007B6C84()
{
	bfmeRegisterDAB(cursorTextures, 4, 0x498, Rva0017098DTextureHandleDtor);
}

void __cdecl rva007B6BB9()
{
	bfmeRegisterDAB(g_Va00DE1F8C, 4, 8, Rva0017098DTextureHandleDtor);
}

void __cdecl rva007B93EC()
{
	bfmeRegisterDAB(g_Va00E060B8, 0xC, 0x1E, Rva000B3FD0EmptyPointDtor);
}

struct Rva007AEA2CArrayInits
{
	static void rva007AEA2C();
	static void rva007AF10C();
	static void rva007AC207();
	static void rva007ABF7B();
};

void Rva007AEA2CArrayInits::rva007AEA2C()
{
	rva00906340VecCtor(g_Va00E01D60, 4, 0x14, Rva00326BE6NullFirstWordCtor, Rva0048BA39AsciiStringDtor);
	atexit(rva007B7BBE);
}

void Rva007AEA2CArrayInits::rva007AF10C()
{
	rva00906340VecCtor(g_00E022F8, 0xC, 2, Rva00256646VectorCtorClosure, Rva00381AE0VectorDtor);
	atexit(rva007B7DD1);
}

void Rva007AEA2CArrayInits::rva007AC207()
{
	rva00906340VecCtor(cursorTextures, 4, 0x498, Rva00326BE6NullFirstWordCtor, Rva0017098DTextureHandleDtor);
	atexit(rva007B6C84);
}

void Rva007AEA2CArrayInits::rva007ABF7B()
{
	rva00906340VecCtor(g_Va00DE1F8C, 4, 8, Rva00326BE6NullFirstWordCtor, Rva0017098DTextureHandleDtor);
	atexit(rva007B6BB9);
}
