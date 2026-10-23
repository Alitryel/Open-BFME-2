// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// pair<const int, Rva0050055D>(key, value) at 0x0050078D: stores the key, then
// copies the value at +4 through the rowed Rva0050055D copy constructor
// (0x0050055D, Rva0050055DCopy.cpp), which names the mapped type. Only the
// rowed member is instantiated.
#include <utility>

class Rva0050055D
{
public:
	Rva0050055D(const Rva0050055D &other);
private:
	char m_bytes[0x18];
};

template _STL::pair<const int, Rva0050055D>::pair(const int &, const Rva0050055D &);
