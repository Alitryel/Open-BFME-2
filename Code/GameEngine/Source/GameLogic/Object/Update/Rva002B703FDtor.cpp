// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /GX /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@URva0040DC56Element@@V?$allocator@URva0040DC56Element@@@_STL@@@_STL@@QAE@XZ @ 0x002B703F 63B
// Evidence: EH vector destroy plus free of Rva0040DC56Element range; calls rowed __EH_prolog and rowed _Destroy 0x002B61C5 and rowed _free 0x00030830; unblocks 0x002B707E 0x002BB281; beside prev Member44 dtor 0x002B6B4C.
#include <vector>

struct Rva0040DC56Element
{
	~Rva0040DC56Element();
	void *m_holder; // native destroy2B44C1 advances four bytes; release2B2F49 uses +0
};

// Bind the verified24B range forwarder2B61C5; its27B destroy loop2B44C1
// releases each four-byte holder through2B2F49 with flag0.
namespace _STL {
template <> void _Destroy<Rva0040DC56Element *>(Rva0040DC56Element *, Rva0040DC56Element *);
}

template _STL::vector<Rva0040DC56Element>::~vector();
