// cl: /GX- /MD
// ?rva00109D5F@Rva00109D5F@@QAEXXZ, retail 0x00109D5F (5B): re-runs the
// rowed shadow-prefix initializer ?initialize@Rva000EFA4E@@QAEXXZ
// (0x000EFA4E) on itself as a tail jump. The 0x00109D8C constructor nearby
// reuses that prefix (see Rva000EFA4EBase.cpp), so the owner is modelled as
// deriving from it; its name and the rest of its layout are not recovered.
// No direct caller reaches it in retail.
#include "BfmeShadowPrefix.h"

class Rva00109D5F : public Rva000EFA4E
{
public:
	void rva00109D5F();
};

void Rva00109D5F::rva00109D5F()
{
	initialize();
}
