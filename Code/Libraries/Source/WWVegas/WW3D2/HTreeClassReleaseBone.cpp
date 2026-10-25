// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2htree /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
// Use the same target HTree and math declarations as the destination TU.
#include <windows.h>
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
#include "../../../../../reference/shims/bfme2htree/htree.h"
//
// ?Release_Bone@HTreeClass@@QAEXH@Z, retail 0x001661F0, 70 bytes.
//
// BFME 2 rewrote Zero Hour's per-pivot IsCaptured flag clear as a sorted
// vector erase of 36-byte captured-bone records (Begin at +0x1C, End at
// +0x20, Index first). Same record model as the landed Is_Bone_Captured unit
// (HTreeClassIsBoneCaptured.cpp) and Control_Bone (htree_control.cpp); the
// tail copy reaches the same random-access copy helper at 0x00161350 the
// vector erase at 0x001661C0 and Free's clear use, with by-reference tag and
// null distance pointer. Identity: pin at 0x001661F0 read from the REL32 at
// the byte-verified Animatable3DObjClass forwarder 0x001A4EE0 (jmp at
// 0x001A4EEA in animobj.cpp). Donor Zero Hour htree.cpp Release_Bone only
// clears a flag; retail follows the vector-erase shape.
// Retail reloads End after the find loop; the volatile read reproduces that
// second load, which /O2+G7 would otherwise CSE away.
// The copy helper 0x00161350 is rowed as STLport's random-access __copy over
// 36-byte BfmePod36 records (int distance); declared only, so the call keeps
// that name. The element and tag take those spellings here.
#include <iterator>
namespace _STL {
template <class _RandomAccessIter, class _OutputIter, class _Distance>
_OutputIter __copy(_RandomAccessIter __first, _RandomAccessIter __last, _OutputIter __result,
	const random_access_iterator_tag &, _Distance *);
}
struct BfmePod36 { int Index; unsigned char m_pad[32]; };
typedef BfmePod36 BfmeRva00161350Elem;

void HTreeClass::Release_Bone(int boneindex)
{
    BfmeRva00161350Elem *p = reinterpret_cast<BfmeRva00161350Elem *>(OwnedSequence1C[0]);
    BfmeRva00161350Elem *end = reinterpret_cast<BfmeRva00161350Elem *>(OwnedSequence1C[1]);
    if (p == end)
        return;
    do {
        if (p->Index == boneindex)
            goto found;
        ++p;
    } while (p != end);
    return;
found:
    BfmeRva00161350Elem *finish = *(BfmeRva00161350Elem * volatile *)&OwnedSequence1C[1];
    BfmeRva00161350Elem *next = p + 1;
    if (next != finish) {
        _STL::random_access_iterator_tag tag;
        _STL::__copy(next, finish, p, tag, (int *)0);
    }
    OwnedSequence1C[1] -= sizeof(BfmeRva00161350Elem);
}
