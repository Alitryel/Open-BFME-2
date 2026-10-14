// cl: /Ireference/shims/bfme2_ascii /O1 /EHsc /MD
//
// ICF twin of ??4FXBoneInfo@@QAEAAU0@ABU0@@Z (0x001D9990, ModuleFactory.cpp):
// the element of the STLport sweep at 0x00254D65 is the same 8-byte record
// (bone name, FX list pointer), and its assignment is that body.
#include "ascii_string.h"

class FXList;

struct Rva00254D65Element
{
	AsciiString boneName;
	const FXList *fx;
	Rva00254D65Element &operator=(const Rva00254D65Element &other);
};

Rva00254D65Element &Rva00254D65Element::operator=(const Rva00254D65Element &other)
{
	boneName = other.boneName;
	fx = other.fx;
	return *this;
}
