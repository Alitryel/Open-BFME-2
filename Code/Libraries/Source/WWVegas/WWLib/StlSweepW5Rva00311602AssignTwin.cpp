// cl: /O1 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii /DWIN32 /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /Ireference/shims/bfmealloc/stl
// stlport
//
// ICF twin of ??4Rva003A35A0Element@@QAEAAU0@ABU0@@Z (0x00311537,
// Containers/Rva003A35A0Element.cpp): the element of the STLport sweep at
// 0x00311602 is the same 184-byte record, and its compiler-generated
// assignment is that body. Layout, includes and flags copied from the owner.
#define _STLP_NO_EXCEPTIONS 1
#include <cstddef>
#include "_alloc.h"
#include <vector>
// Keep this inlined unsigned max overload local; retail has one external owner.
#pragma optimize("t", on)
namespace _STL {
static inline const unsigned int& max(const unsigned int& a, const unsigned int& b) { return a < b ? b : a; }
}
#pragma optimize("", on)
#include "ascii_string.h"
#include <new>
#include "../../../Include/Lib/Coord3D.h"
struct Rva00311FE2Words {
    // Native copy uses raw dwords; native default initialization uses SSE
    // zero stores. These two views describe storage and codegen only.
    union {
        struct {unsigned int word00,word04,word08;};
        struct {float zero00,zero04,zero08;};
    };
    // ?Rva00311FE2Words::rva003118DFZero absent-from-retail
    void rva003118DFZero() {zero00=0.0f;zero04=0.0f;zero08=0.0f;}
    // ?Rva00311FE2Words::Rva00311FE2Words absent-from-retail
    Rva00311FE2Words() {}
    // ?Rva00311FE2Words::Rva00311FE2Words present-unmatched
    Rva00311FE2Words(const Rva00311FE2Words& s) {word00=s.word00;word04=s.word04;word08=s.word08;}
};
struct Rva00311602Element {
    unsigned int word00;
    float values[10];
    Coord3D points[10];
    Rva00311FE2Words point;
    AsciiString text;
    unsigned int wordB4;
};
// Emit the compiler-generated memberwise assignment.
Rva00311602Element& (Rva00311602Element::*emitRva00311602Assign)(const Rva00311602Element&)=&Rva00311602Element::operator=;
