// cl: /DNDEBUG /MD /EHs
// ??1Rva004DFED8@@UAE@XZ, RVA 0x004DFED8, 84 bytes.
// Dtor: vstore 0x008615D4, calls rowed clear 0x002827F3, frees vec buffers
// at +0x10 and +0x4 via rowed free 0x00030830.
// Evidence: deleting dtor 0x004E005E calls it; callers 0x004E0061 0x004E01AB;
// callees all rowed; twin 0x00283081 shares vtable and clear.
extern "C" void __cdecl free(void *block);

namespace _STL
{
template <class T>
class allocator
{
};

template <class T, class A>
class vector
{
public:
	~vector() { if (m_start) free(m_start); }
	T *m_start;
	T *m_finish;
	T *m_end_of_storage;
	T *erase(T *first, T *last);
};
}

// Both members are pointer vectors whose retail unwind actions are the shared
// free-first-pointer fold (same graph as twin 0x00283081), not the ledger's
// ~vector<void*> at 0x00027370, so neither member is a vector<void*>.
struct Rva004DFED8Entry4;
struct Rva004DFED8Entry10;

class Rva002827F3
{
public:
	void rva002827F3();
};

class Rva004DFED8
{
public:
	virtual ~Rva004DFED8();
private:
	_STL::vector<Rva004DFED8Entry4 *, _STL::allocator<Rva004DFED8Entry4 *> > m_vec4;
	_STL::vector<Rva004DFED8Entry10 *, _STL::allocator<Rva004DFED8Entry10 *> > m_vec10;
};

Rva004DFED8::~Rva004DFED8()
{
	((Rva002827F3 *)this)->rva002827F3();
}
