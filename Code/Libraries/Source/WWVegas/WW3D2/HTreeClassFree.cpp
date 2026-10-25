// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2htree /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport
//
// HTreeClass::Free at 0x00166510.
//
// BFME 2's version of Zero Hour's Free: release the pivot array, reset the
// count and the scale factor, empty the +0x1C member, and drop the buffer held
// at +0x2C along with the words around it.
//
// The +0x1C member is emptied the way STLport's vector::erase(first, last)
// does it: copy the tail [last, finish) down to first through the random-
// access copy helper at 0x00161350 -- by-reference dispatch tag, null distance
// pointer, hence retail's extra pushed zero -- and make the result the new
// finish.  The element type and the helper have no recovered identity and keep
// address-derived names; the member is the same +0x1C object whose copy
// constructor HTreeClassCopyConstructor.cpp reaches at 0x00166110.

#include <windows.h>
#include "../../../../../reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
#include "../../../../../reference/shims/bfme2htree/htree.h"
#include <stl/_iterator_base.h>

// The copy helper 0x00161350 is rowed as STLport's random-access __copy over
// 36-byte BfmePod36 records (int distance); declared only, so the call keeps
// that name. The element and tag take those spellings here.
namespace _STL {
struct random_access_iterator_tag;
template <class _RandomAccessIter, class _OutputIter, class _Distance>
_OutputIter __copy(_RandomAccessIter __first, _RandomAccessIter __last, _OutputIter __result,
	const random_access_iterator_tag &, _Distance *);
}
struct BfmePod36;
typedef BfmePod36 BfmeRva00161350Elem;

// The +0x1C member: start, finish, end of storage.  Clear is STLport's
// erase(begin(), end()).
struct BfmeRva00166110
{
	void Clear();
	BfmeRva00161350Elem *Start;
	BfmeRva00161350Elem *Finish;
	BfmeRva00161350Elem *EndOfStorage;
};

// Keep this matched helper emitted independently when Free is split away.
void BfmeRva00166110::Clear()
{
	BfmeRva00161350Elem *first = Start;
	BfmeRva00161350Elem *last = Finish;
	_STL::random_access_iterator_tag tag;
	BfmeRva00161350Elem *i = _STL::__copy(last, Finish, first, tag, (int *)0);
	Finish = i;
}

void HTreeClass::Free(void)
{
	if (Pivot != 0) {
		delete [] (char *)Pivot;
		Pivot = 0;
	}
	NumPivots = 0;
	ScaleFactor = 1.0f;

	// Retail inlines the erase here; keep its separately rowed Clear provider
	// independent so a TU carve can retain that body in the residual.
	BfmeRva00166110 &sequence = *reinterpret_cast<BfmeRva00166110 *>(OwnedSequence1C);
	BfmeRva00161350Elem *first = sequence.Start;
	BfmeRva00161350Elem *last = sequence.Finish;
	_STL::random_access_iterator_tag tag;
	sequence.Finish = _STL::__copy(last, sequence.Finish, first, tag, (int *)0);

	Unknown28 = 0;
	delete [] reinterpret_cast<char *>(Unknown2C);
	Unknown2C = 0;
	Unknown30 = 0;
}
