// 0x00017B00 (33B): in-place wide-string initializer over a static empty.
//
// WHAT THE BYTES SHOW. The body spills a volatile slot and `other`
// (push ecx / push esi), loads `other` to esi, pushes the .data static at
// 0x009DEEF0 (32 zero bytes; DIR32 slot the patcher fills), points ecx at
// `other`, and calls 0x0000EA90 — the ledger's matched STLport 4.5.3
// wide-string copy constructor — then returns `other` (ret 4: thiscall with
// one stack param). So this copy-constructs a wide string at `other` from
// the static empty and hands `other` back. The volatile store lands at
// [esp+8] because the compiler sinks it past the argument push, which is
// also what makes the slot read back as the callee's-temporary area.
//
// WHY NOT THE SERVED NAME. bfme1_sweep's near queue serves this address as
// ?bfmeGoDNC / ?bfmeGoDNG (BfmeConv735/739 two-param donors, ret 8 against
// retail ret 4); the unserved one-param twin ?bfmeGoDND (BfmeConv736) has
// the right arity but all three donors call a BfmeOtherDN method while
// retail's call enters the string copy ctor (capstone: call 0xEA90, the
// matched row, not mid-body). The DN identities are therefore refuted for
// game.dat and the address keeps an opaque address-derived name. One data
// pin (the static); the callee is already rowed so no code pin.

// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /EHs-c-
// stlport
typedef unsigned short BfmeWChar;

namespace _STL
{
template <class T> class char_traits {};
template <class T> class allocator {};
template <class C, class T, class A> class basic_string
{
public:
	basic_string(const basic_string &src);
};
typedef basic_string<BfmeWChar, char_traits<BfmeWChar>, allocator<BfmeWChar> > BfmeWideString;
}

#include <new>
// bfme link decl-only begin
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
// bfme link decl-only end

// g_009DEEF0Static: matched references place it at VA 0xddeef0; zero-filled at retail, sized to the
// 0xc-byte gap before the next known global there.
unsigned char g_009DEEF0Static[12];

class Rva00017B00StringInit
{
public:
	void *init(void *other);
};

void *Rva00017B00StringInit::init(void *other)
{
	volatile int tmp = 0;
	_STL::BfmeWideString *slot = static_cast<_STL::BfmeWideString *>(other);
	const _STL::BfmeWideString &empty = *reinterpret_cast<const _STL::BfmeWideString *>(g_009DEEF0Static);
	slot->_STL::BfmeWideString::BfmeWideString(empty);
	return other;
}

// Two more initializers with the same code as Rva00017B00StringInit::init,
// each copying from its own static empty: 0x00017B30 reads VA 0xddef20 and
// 0x00019D90 reads VA 0xddef2c. bfme1_sweep places the shared donor body at
// all three addresses and the DIR32 operand separates them. Both statics are
// zero-filled at retail and unreferenced elsewhere, and each is sized like
// the first.
unsigned char g_00DDEF20Static[12];	// VA 0x00ddef20

class Rva00017B30StringInit
{
public:
	void *init(void *other);
};

void *Rva00017B30StringInit::init(void *other)
{
	volatile int tmp = 0;
	_STL::BfmeWideString *slot = static_cast<_STL::BfmeWideString *>(other);
	const _STL::BfmeWideString &empty = *reinterpret_cast<const _STL::BfmeWideString *>(g_00DDEF20Static);
	slot->_STL::BfmeWideString::BfmeWideString(empty);
	return other;
}

unsigned char g_00DDEF2CStatic[12];	// VA 0x00ddef2c

class Rva00019D90StringInit
{
public:
	void *init(void *other);
};

void *Rva00019D90StringInit::init(void *other)
{
	volatile int tmp = 0;
	_STL::BfmeWideString *slot = static_cast<_STL::BfmeWideString *>(other);
	const _STL::BfmeWideString &empty = *reinterpret_cast<const _STL::BfmeWideString *>(g_00DDEF2CStatic);
	slot->_STL::BfmeWideString::BfmeWideString(empty);
	return other;
}
