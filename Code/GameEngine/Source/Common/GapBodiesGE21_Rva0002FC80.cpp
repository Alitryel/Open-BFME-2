// cl: /O2 /G7 /arch:SSE /MD /DNDEBUG
// Split from GapBodiesGE21.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
// CRT replacement shims from .text gaps no Ghidra function covers, between
// the matched wwmath wrappers (0x0002FBC0) and mem_ops.cpp's operator
// new/delete (0x0002FD60..0x0002FDE0). Each begins after its neighbour's
// padding and ends in its own ret or tail jump. They route the C heap through
// the game's pluggable memory-manager slots, the counterparts of BFME 1's
// Rva00881D70CrtShims.cpp (donor shapes only: BFME 2's allocate slot takes a
// third tag word, read from these bodies). The inlined strlen/strcpy loops and
// the rep stos memset are the /O2 intrinsic forms. Names stay address-derived
// except the two operator new overloads, whose ABI is the one Zero Hour's
// GameMemory.h declares for the file/line forms.
#include <string.h>
#include <stdlib.h>

typedef void *(__cdecl *GameAllocateFunction)(unsigned int, int, const void *);
extern "C" GameAllocateFunction __gameMemAllocatePtr;	// VA 0x00DE0404

namespace _STL
{
	template <class T> class allocator;
	template <> class allocator<char>
	{
	public:
		static char *allocate(unsigned int n, const void *hint);	// 0x000307F0
	};
}

// Tag the duplicating shims pass to the byte allocator: the multi-character
// constant 'str' (dword 0x00737472 in the pushes).
#define GAP_RTS_TAG ((const void *)'str')




// --- 0x0002FC80 (24B): _msize: the block's size through the null-guarded
// block-size forwarder 0x00030860, with the heap word the block-heap slot
// (VA 0x00DE03F0, ?_GetBlockHeap@MemoryPool@@YAIPAX@Z) reports.
extern void *g_00DE03F0;
unsigned int rva00030860(void *block, unsigned int heap);

unsigned int rva0002FC80(void *block)
{
	return rva00030860(block, ((unsigned int (__cdecl *)(void *))g_00DE03F0)(block));
}

// --- 0x0002FCA0 (24B): realloc through the resize slot VA 0x00DE0400 with
// two zero words.
extern void *g_00DE0400;

void *rva0002FCA0(void *block, unsigned int size)
{
	return ((void *(__cdecl *)(void *, unsigned int, int, int))g_00DE0400)(block, size, 0, 0);
}



// --- 0x0002FD50 (6B): _mbsdup forwarder (tail jump through the import).
extern "C" __declspec(dllimport) unsigned char *__cdecl _mbsdup(const unsigned char *s);




// --- 0x0002FFA0 (25B): run the resolver 0x00030730 (its WorldBuilder
// identity MemoryPool::InitFunctionPointers), register the slot at
// VA 0x00DE040C with atexit, then tail-call the slot at VA 0x00DE0410.
namespace MemoryPool { void InitFunctionPointers(); }
extern void *g_00DE040C;
extern void *g_00DE0410;

void rva0002FFA0()
{
	MemoryPool::InitFunctionPointers();
	atexit((void (__cdecl *)(void))g_00DE040C);
	((void (__cdecl *)(void))g_00DE0410)();
}

// --- 0x0002F980 (22B): the registry block's once-gate on its own, ahead of
// the getters at 0x0002F9C0 that inline the same test; tail-jumps to the
// rowed LoadRegistryValues 0x0002F840.
extern bool g_registryValuesLoaded;
void LoadRegistryValues();


// Unreferenced leaves from the /O2 regions (twins.tsv leads): the full
// dword store and the load-then-test byte read are /O2 forms.
// 0x000657B3 (9B): constructor zeroing the word at +0.
class Rva000657B3
{
public:
	Rva000657B3();
private:
	int m_00;
};


// 0x0001D1D0 (11B): whether the byte at +0x0E is set.
class Rva0001D1D0
{
public:
	bool rva0001D1D0() const;
private:
	char m_pad[0x0E];
	unsigned char m_0E;
};


// 0x00030E10 (8B): the word at +0x18 of a record passed by pointer (the
// shape of STLport's _FILE_I_begin over a stdio FILE).
struct Rva00030E10Record
{
	char m_pad[0x18];
	int m_18;
};


// Unreferenced virtual-slot forwarders: each calls one slot of its own
// object with no arguments, a tail jump through the vtable (mov eax,[ecx];
// jmp [eax+4*slot]). Owners are address-derived views of the slots used.
// 0x00013280: slot 6.
class Rva00013280Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	void rva00013280();
};


// 0x00013290: slot 10.
class Rva00013290Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	void rva00013290();
};


// 0x00013380, 0x00013390, 0x000133A0: slots 4, 5 and 7, three CC-padded
// forwarders in the STLport fstream run. Lead only: slots 4/5/7 of the
// codecvt vftables (0x007BBB08, 0x007BBB2C) are do_encoding,
// do_always_noconv and do_max_length, so these read as codecvt's encoding(),
// always_noconv() and max_length(); the char and wchar_t instantiations are
// byte-identical and nothing references these copies, so the owner stays an
// address-derived view.
class Rva00013380Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	void rva00013380();
	void rva00013390();
	void rva000133A0();
};




// 0x000184E0: slot 8.
class Rva000184E0Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	void rva000184E0();
};


// 0x000184F0: slot 12.
class Rva000184F0Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	void rva000184F0();
};


// 0x0001C8B0: slot 11.
class Rva0001C8B0Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10();
	virtual void slot11();
	void rva0001C8B0();
};


// 0x0001D170: slot 3.
class Rva0001D170Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	void rva0001D170();
};


// 0x00035790: slot 0.
class Rva00035790Slots
{
public:
	virtual void slot00();
	void rva00035790();
};


// 0x000357F0: slot 2.
class Rva000357F0Slots
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	void rva000357F0();
};


