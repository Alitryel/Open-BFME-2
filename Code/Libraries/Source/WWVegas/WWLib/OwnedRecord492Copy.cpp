// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Target strings, bit vector and overlapping payload copies establish this layout.
// Anonymous union alternatives reproduce the observed member-copy order.
// Original record and payload names are unknown; BFME1 PeerResponse supplied
// the related GameSpy record pattern, without establishing this record's name.
#include <string>
#include <vector>
#include <stddef.h>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _Bit_iter<_Bit_reference, _Bit_reference *> copy<_Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *> >(_Bit_iter<bool, bool const *>, _Bit_iter<bool, bool const *>, _Bit_iter<_Bit_reference, _Bit_reference *>); }
namespace _STL { template <> _String_base<char, allocator<char> >::_String_base(allocator<char> const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(basic_string<char, char_traits<char>, allocator<char> > const &); }
namespace _STL { template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string(); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::basic_string(); }
namespace _STL { template <> unsigned int * _Bvector_base<allocator<bool> >::_M_bit_alloc(unsigned int); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_terminate_string(); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *) const; }
// bfme link decl-only end
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}
// Suppress this TU's non-retail proxy<char> allocate copy (family2-LK3 row 30):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> char *_STLP_alloc_proxy<char*, char, allocator<char> >::allocate(size_t);
}

struct BfmeOpaqueOwnedRecord492 {
	BfmeOpaqueOwnedRecord492();
	~BfmeOpaqueOwnedRecord492();
	int unknown_00;
	std::string unknown_04;
	std::wstring unknown_10;
	std::string unknown_1c;
	std::string unknown_28;
	std::string unknown_34;
	std::string unknown_40;
	std::string unknown_4c;
	std::string unknown_58;
	std::string unknown_64;
	std::string unknown_70[8];
	unsigned int unknown_d0[10];
	std::string unknown_f8;
	std::vector<bool> unknown_104;
	union {
		struct { int word; } payload_word0;
		struct { int word; } payload_word1;
		struct { int word; } payload_word2;
		struct { bool value; } payload_flag0;
		struct { bool value; } payload_flag1;
		struct { int word; } payload_word3;
		struct { int words[15]; } payload_60;
		struct { int words[53]; } payload_212a;
		struct { bool value; } payload_flag2;
		struct { int words[26]; } payload_104;
		struct { int words[7]; } payload_28;
		struct { int first; int second; } payload_8c;
	};
};

typedef char Record492Extent[
	sizeof(BfmeOpaqueOwnedRecord492) == 492 ? 1 : -1];
typedef char Record492ArrayOffset[
	offsetof(BfmeOpaqueOwnedRecord492, unknown_70) == 0x70 ? 1 : -1];
typedef char Record492RawOffset[
	offsetof(BfmeOpaqueOwnedRecord492, unknown_d0) == 0xd0 ? 1 : -1];
typedef char Record492VectorOffset[
	offsetof(BfmeOpaqueOwnedRecord492, unknown_104) == 0x104 ? 1 : -1];
typedef char Record492PayloadStart[
	offsetof(BfmeOpaqueOwnedRecord492, payload_word0) == 0x118 ? 1 : -1];

BfmeOpaqueOwnedRecord492::BfmeOpaqueOwnedRecord492() {}

template void _STL::_Construct<BfmeOpaqueOwnedRecord492,
	BfmeOpaqueOwnedRecord492>(BfmeOpaqueOwnedRecord492 *,
	const BfmeOpaqueOwnedRecord492 &);

BfmeOpaqueOwnedRecord492::~BfmeOpaqueOwnedRecord492() {}
