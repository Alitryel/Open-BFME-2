// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva0051F87B@@QAE@XZ @ 0x0051FAFC size 86.
// Default ctor for 0x50-byte record with vtable 0x0086745C at +0: UnicodeString
// at +4, int at +8, AsciiString at +0xC, int at +0x10, vector<SaveMapPreview>
// at +0x14 (Rva0051ECC3 view), vector<PrereqUnitRec> at +0x20 (Rva0051ED0A view),
// three vector<unsigned> at +0x2C/+0x38/+0x44. Evidence: same vtable as rowed
// copy 0x0051F87B; offsets from lea pairs; empty Vector_base folds to 0x00211E58.
#include <vector>
// vector<unsigned int>'s allocator constructor inlines at every use here;
// imported force-inline so this unit emits no COMDAT copy of it (its copy
// differs from retail's kept /Od body at 0x00025100). The vector base
// constructor stays a declared nothrow call to its kept copy (0x00211E58).
namespace _STL {
template <> _Vector_base<unsigned int,allocator<unsigned int> >::_Vector_base(const allocator<unsigned int> &) throw();
template <> __declspec(dllimport) __forceinline
vector<unsigned int, allocator<unsigned int> >::vector(const allocator<unsigned int> &__a)
	: _Vector_base<unsigned int, allocator<unsigned int> >(__a) {}
}

#include "ascii_string.h"
#include "unicode_string.h"

struct SaveMapPreview
{
	int m00;
	int m04;
	int m08;
	int m0C;
	int m10;
};

struct PrereqUnitRec
{
	unsigned int m_data[3];
};

class Rva0051F87B
{
public:
	virtual ~Rva0051F87B();
	Rva0051F87B();
private:
	UnicodeString m_04;
	int m_08;
	AsciiString m_0C;
	int m_10;
	_STL::vector<SaveMapPreview, _STL::allocator<SaveMapPreview> > m_14;
	_STL::vector<PrereqUnitRec, _STL::allocator<PrereqUnitRec> > m_20;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_2C;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_38;
	_STL::vector<unsigned int, _STL::allocator<unsigned int> > m_44;
};

Rva0051F87B::Rva0051F87B()
{
}
