// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Rva00055864Free@@YGXPAURva00055864Node@@@Z @ 0x00055864 (28B).
// Opaque node deleter calling the rowed holder release 0x0005333F on the
// +4 value, then free.
// Evidence: sole caller is deque clear loop 0x00056DA2; same flags as neighbours.
class Rva0005333FHolder
{
public:
	void rva0005333F();
	void *m_vtable;
};

struct Rva00055864Node
{
	void *m_next;
	Rva0005333FHolder m_val;
};

extern "C" void __cdecl free(void *block);

void __stdcall Rva00055864Free(Rva00055864Node *p)
{
	p->m_val.rva0005333F();
	if (p) {
		free(p);
	}
}
