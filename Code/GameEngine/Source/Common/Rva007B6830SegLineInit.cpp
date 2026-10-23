// cl: /MD
// ?rva007B6830@@YAXXZ @0x007B6830 22B: file-scope SegLineRendererClass
// initializer. Retail: ecx = VA 0x00E1F4E8, call the rowed default ctor
// ??0SegLineRendererClass@@QAE@XZ (0x00191140), then atexit(0x007B9CC0), the
// rowed cleanup thunk that runs ~SegLineRendererClass on the same storage.
// Same initializer shape as the matched 0x007B6760/0x007B6780 pair. The owning
// TU is unrecovered, so the storage keeps its address-named extern (defined in
// Rva007B6880Thunks.cpp beside its cleanup thunk).

class SegLineRendererClass
{
public:
	SegLineRendererClass();
};

inline void *operator new(unsigned int, void *where)
{
	return where;
}

extern unsigned int g_Va00A1F4E8;

void __cdecl rva007B9CC0();

extern "C" int __cdecl atexit(void (__cdecl *callback)());

void rva007B6830()
{
	new (&g_Va00A1F4E8) SegLineRendererClass;
	atexit(rva007B9CC0);
}
