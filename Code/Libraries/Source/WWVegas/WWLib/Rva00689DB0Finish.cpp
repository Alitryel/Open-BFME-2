// ??1?$vector@URva001D28F0Element@@V?$allocator@URva001D28F0Element@@@_STL@@@_STL@@QAE@XZ
// cl: /EHs /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva001D28F0Element
{
	char m_body[0x1c];
	~Rva001D28F0Element();
};

typedef _STL::vector<Rva001D28F0Element> Rva001D28F0Vector;

template Rva001D28F0Vector::~Rva001D28F0Vector();
