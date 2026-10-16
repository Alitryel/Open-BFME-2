// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0059E436Data@@QAE@XZ @0x0059E3BE 32B: default ctor with vector at +4 and int zero at +0x10.
// Evidence: vtable 0x00C70FC8, rowed _Vector_base<BfmeE16> 0x00211E58, caller 0x0059E456 in Rva0059E436Parse.
#include <vector>
#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
class Rva0059E436Data
{
public:
	Rva0059E436Data();
	virtual ~Rva0059E436Data();
private:
	_STL::vector<BfmeE16> m_04;
	int m_10;
};

Rva0059E436Data::Rva0059E436Data()
{
	m_10 = 0;
}
