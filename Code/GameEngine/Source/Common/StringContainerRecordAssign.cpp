// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Oy-
// stlport
// ?rva0004B1D2@Rva0004B1D2@@QAEPAUBfmeContainerRecord00048139@@PAU2@PBD@Z @0x0004B1D2 51B
// Range assign updating +4 via rowed copyRecordRangeWithScratch 0x0004811C
// and rowed _Destroy 0x0004A9F3. Evidence: callers 0x0004B228 0x0004B5DC
// 0x0004BEA7; neighbours 0x0004B193 0x0004B205.
#include <vector>
#include "ascii_string.h"

struct BfmeContainerRecord00048139 {
	AsciiString text0;
	AsciiString text1;
	unsigned char m_pad[0x5C - 8];
	~BfmeContainerRecord00048139();
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void _Destroy<BfmeContainerRecord00048139>(BfmeContainerRecord00048139 *p) { typedef BfmeContainerRecord00048139 BfmeDestroyT; p->~BfmeDestroyT(); } }

BfmeContainerRecord00048139 *copyRecordRangeWithScratch(const char *first, const char *last, BfmeContainerRecord00048139 *dest, void *outerCtx);

class Rva0004B1D2 {
public:
	void *m_00;
	BfmeContainerRecord00048139 *m_04;
	BfmeContainerRecord00048139 *rva0004B1D2(BfmeContainerRecord00048139 *a1, const char *a2);
	void rva0004B223();
};

BfmeContainerRecord00048139 *Rva0004B1D2::rva0004B1D2(BfmeContainerRecord00048139 *a1, const char *a2)
{
	BfmeContainerRecord00048139 *newEnd = copyRecordRangeWithScratch(a2, (const char *)m_04, a1, (void *)(((char *)&a1) + 3));
	_STL::_Destroy(newEnd, m_04);
	m_04 = newEnd;
	return a1;
}

// ?rva0004B223@Rva0004B1D2@@QAEXXZ @0x0004B223 11B, unreferenced: the clear
// over the same storage, the range erase above (call site 0x0004B228) from
// the start pointer at +0 to the end at +4.
void Rva0004B1D2::rva0004B223()
{
	rva0004B1D2((BfmeContainerRecord00048139 *)m_00, (const char *)m_04);
}
