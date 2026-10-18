// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1?$vector@UEvaMessageInfo@@V?$allocator@UEvaMessageInfo@@@_STL@@@_STL@@QAE@XZ retail 0x000B0254 63B
// Evidence: unlock same 63B EH shape as 0x0002CC70 via Destroy 0x000AFF52 plus free 0x00030830; callers 0x001021A0 0x001021AC 0x000B0834 0x001023F2
#include <vector>

class BfmeStringRecord00111ACF { public: ~BfmeStringRecord00111ACF(); };
struct EvaMessageInfo
{
	// Destruction is the rowed ??1BfmeStringRecord00111ACF, reached by a qualified call.
	__declspec(dllimport) __forceinline ~EvaMessageInfo() { ((BfmeStringRecord00111ACF *)this)->BfmeStringRecord00111ACF::~BfmeStringRecord00111ACF(); }
};

template _STL::vector<EvaMessageInfo>::~vector();
