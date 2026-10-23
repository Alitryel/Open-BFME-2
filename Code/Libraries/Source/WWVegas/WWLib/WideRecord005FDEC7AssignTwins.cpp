// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
//
// ICF twins of ??4BfmeContainerRecord005FDEC7@@QAEAAU0@ABU0@@Z (0x005FDEC7,
// stlport_vector_wide_record_5fdec7.cpp): the 12-byte record assignment
// (words +0/+4, wide string +8) that the STLport copy loops at 0x005FDEEA
// and 0x005FE0C3 call for their elements. Compiled with the owner's flags.
#include "unicode_string.h"

struct Rva005FDEEAElement
{
	unsigned int word0;
	unsigned int word4;
	UnicodeString text08;
	__declspec(nothrow) Rva005FDEEAElement &operator=(const Rva005FDEEAElement &other);
};

__declspec(nothrow) Rva005FDEEAElement &Rva005FDEEAElement::operator=(const Rva005FDEEAElement &other)
{
	word0 = other.word0;
	word4 = other.word4;
	text08 = other.text08;
	return *this;
}

struct Rva005FE0C3Element
{
	unsigned int word0;
	unsigned int word4;
	UnicodeString text08;
	__declspec(nothrow) Rva005FE0C3Element &operator=(const Rva005FE0C3Element &other);
};

__declspec(nothrow) Rva005FE0C3Element &Rva005FE0C3Element::operator=(const Rva005FE0C3Element &other)
{
	word0 = other.word0;
	word4 = other.word4;
	text08 = other.text08;
	return *this;
}
