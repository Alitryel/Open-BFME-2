// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva00153D16@@QAE@XZ, retail 0x00153D16, 61 bytes.
// Holder with COM-style surface at +0 released via vtable[2] __stdcall then nulled plus vector<Rva00153729> at +4.
// Evidence: EH_prolog with [ebp-4] 0 then -1 around Release-then-null plus rowed vector dtor 0x153BED at 0x153D41; same Release shape as W3DRadarResetSurface dtor; callers 0x1513ED deleting dtor plus 0x15177E and 0x151810.
#include <vector>
// The native range destructor at 0x00153BB6 advances by 0x4C. Its element
// destructor at 0x00153729 destroys six 12-byte vectors after the first word.
// Keep that layout here too so the emitted range helper agrees with its owner.
struct Rva005F8F96;
struct Rva00153729
{
	~Rva00153729();
	int m_00;
	_STL::vector<Rva005F8F96> m_04[6];
};
typedef char AssertRva00153729Size[sizeof(Rva00153729) == 0x4C ? 1 : -1];
typedef void (__stdcall *SurfaceRelease)(void *surface);
class Rva00153D16
{
	void *m_ptr;
	_STL::vector<Rva00153729> m_vec;
public:
	~Rva00153D16();
};
Rva00153D16::~Rva00153D16()
{
	void *p = m_ptr;
	if (p)
	{
		((SurfaceRelease *)(*(void ***)p))[2](p);
		m_ptr = 0;
	}
}
