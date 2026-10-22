// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// The element is ProductionPrerequisite::PrereqUnitRec: this _M_clear's destroy
// call goes to the rowed _Destroy<PrereqUnitRec *> at 0x002D02A8
// (ProductionPrerequisiteCtor.cpp), and ThingTemplate and the prerequisite
// vector's insert-overflow unit emit this same body under that name.
#include <vector>

class ProductionPrerequisite
{
public:
	struct PrereqUnitRec
	{
		char m_bytes[0x14];
		~PrereqUnitRec();
	};
};

// Declared only: the rowed copy serves the call.
namespace _STL { template <> void _Destroy<ProductionPrerequisite::PrereqUnitRec *>(ProductionPrerequisite::PrereqUnitRec *, ProductionPrerequisite::PrereqUnitRec *); }

template void _STL::vector<ProductionPrerequisite::PrereqUnitRec, _STL::allocator<ProductionPrerequisite::PrereqUnitRec> >::_M_clear(void);
