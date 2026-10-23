// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
// Carried from the Open-BFME-1 donor at submodule revision 5cae4bdf
// (game/Libraries/Source/STLport/Rva0084AC60Open.cpp). Target evidence: the 84B
// body places uniquely in BFME2 .text at 0x0001DFB0 (donor b1 0x0084AC60) though
// BFME1 ICF-folded it with its siblings. The name is the carried donor name; no
// target evidence recovers the owner identity.
#include <fstream>

// Retail RVA 0084AC60, 84 bytes, surrounded by int3 padding.
// The +8 stream buffer, +54 _Filebuf_base, virtual-base ios access and
// failbit path witness the STLport file-input-stream layout. The character
// specialization is not established by a caller, so keep an opaque owner.
// char is a layout view here: this body only calls the non-template
// _Filebuf_base::_M_open and ios_base::_M_throw_failure.
struct Rva0084AC60 : _STL::basic_ifstream<char, _STL::char_traits<char> >
{
    void open(const char *name, _STL::ios_base::openmode mode);
};

void Rva0084AC60::open(const char *name, _STL::ios_base::openmode mode)
{
    if (!rdbuf()->open(name, mode | _STL::ios_base::in, 0x80))
        setstate(_STL::ios_base::failbit);
}
