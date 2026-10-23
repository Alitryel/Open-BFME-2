// cl: /O1 /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
// ??_ERva0035A18D@@QAEPAXI@Z, retail 0x0035A18D, 75 bytes.
// Vector deleting destructor for honest 0x10-byte element Rva0035A18D
// (basic_string at +0 plus int at +0x0C). Element dtor is declared only and
// pinned as an ICF twin at the rowed 14B body 0x0007FAB3 (BasicStringCharDtor
// frees [ecx+0]; int needs nothing). Array branch destroys via ??_M with
// that dtor and size 0x10 then frees via rowed vector delete 0x0002FD80;
// scalar calls the pinned dtor then rowed scalar delete 0x0002FD60.
// The anchor exists only to emit the destructor through delete[].
// Precedent Rva004D9A3CVectorDeletingDtor (75B). Evidence: push 0x10 plus
// dtor 0x0007FAB3 plus ??_M 0x00629110, ret 4, callers at 0x0035A21F.
// `BasicStringCharDtor_dup` is the row at 0x0007FAB3 whose object symbol is
// the narrow basic_string destructor. This element is that string at +0 with
// an inert int at +0x0C, so its destructor is the same function; bind the
// address-derived wrapper dtor to the row's actual COFF symbol.
#pragma comment(linker, "/alternatename:??1Rva0035A18D@@QAE@XZ=??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ")
#include <string>

void operator delete[](void *p);

class Rva0035A18D
{
public:
	~Rva0035A18D();
private:
	_STL::basic_string<char> m_str;
	int m_x;
};

// ?Rva0035A18DDeleteArray@@YAXPAVRva0035A18D@@@Z present-unmatched
void Rva0035A18DDeleteArray(Rva0035A18D *p)
{
	delete[] p;
}
