// ?rva0079E4DD@@YAXXZ
// partial score=0.714 date=2026-10-17
// cl: /DNDEBUG /MD /GX /DBFME_ASCII_DTOR_DECL
//
// Null-masked subobject tail: the rowed 20-byte body loads the same slot twice,
// adds the subobject offset to one copy, and selects between null and that
// pointer with neg/sbb/and before tail-jumping to the basic_string destructor.
// The parent frame slot is not recoverable from the bytes; the shape is
// reproduced with a by-value local whose destructor is the tail call.

namespace _STL
{
template <class C> class basic_string;
}

extern "C" void __cdecl free(void *block);

// The rowed basic_string destructor the tail jump resolves to.
template <>
class _STL::basic_string<char>
{
public:
	~basic_string();
};

struct Rva0079E4DDPad
{
	unsigned int v;
	unsigned char pad[12];
};

// Holder whose by-value copy in the frame forces the null-guarded subobject
// select in front of the string destructor.
struct Rva0079E4DDStringHolder
{
	unsigned int m_null;
	_STL::basic_string<char> m_value;
};

static Rva0079E4DDPad g_pad;
void rva0079E4DD()
{
	unsigned int p = *(volatile unsigned int *)&g_pad;
	unsigned int p2 = *(volatile unsigned int *)&g_pad;
	p2 += 4;
	_STL::basic_string<char> *s = (1 ? (p ? (_STL::basic_string<char> *)p2 : (_STL::basic_string<char> *)0) : (_STL::basic_string<char> *)0);
	s->~basic_string();
}
