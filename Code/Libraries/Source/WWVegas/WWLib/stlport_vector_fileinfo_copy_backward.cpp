// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// ??$copy_backward@PAUFileInfoStruct@MixFileCreator@@PAU12@@_STL@@YAPAUFileInfoStruct@MixFileCreator@@PAU12@00@Z @0x00217B93 27B
// STL 3-arg copy_backward wrapper forwarding to rowed __copy_backward_ptrs at 0x002177B0
// with false_type temp at ebp-1. Evidence: ebp frame plus push ecx plus lea eax ebp-1
// plus 3 ptr args plus call 0x002177B0 plus add esp 0x10; caller at 0x00217F30.
#include <stl/_algobase.h>
#include "ascii_string.h"

class MixFileCreator
{
public:
	struct FileInfoStruct
	{
		FileInfoStruct();
		FileInfoStruct(const FileInfoStruct &src);
		FileInfoStruct &operator=(const FileInfoStruct &src);
		unsigned long CRC;
		unsigned long Offset;
		unsigned long Size;
		AsciiString Filename;
	};
};

// GameFont.cpp includes the allocator shim's <stl/_algobase.h>, which
// defines copy_backward and marks __copy_backward_aux/_ptrs __forceinline.
// Retail keeps the stock STLport shape here (aux inlined, ptrs called), so
// this pointer pair is spelled as an explicit specialization of the shim's
// template with the aux step written out.
namespace _STL
{
	// The worker is its own rowed body (0x002177B0): declared, not inlined.
	template <>
	MixFileCreator::FileInfoStruct *__copy_backward_ptrs<MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *>(
		MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *, const __false_type &);

	template <>
	MixFileCreator::FileInfoStruct *copy_backward<MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct *>(
		MixFileCreator::FileInfoStruct *first, MixFileCreator::FileInfoStruct *last, MixFileCreator::FileInfoStruct *result)
	{
		__false_type t;
		return __copy_backward_ptrs(first, last, result, t);
	}
}
