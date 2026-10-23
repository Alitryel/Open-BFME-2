// cl: /MD /Ireference/shims/moduledata
// ??_GRva004147CF@@UAEPAXI@Z @0x00414AEE 28B: scalar deleting dtor calling ??1Rva004147CF at 0x00414932.
// Same-shape sibling of ??_GVersion; needs ??1 row to exist.

#include "Common/Snapshot.h"

struct EmitVtableTag;

class Rva004147CF : public Snapshot { public: Rva004147CF(EmitVtableTag *); virtual ~Rva004147CF(); };
// ?<Rva004147CF::Rva004147CF> absent-from-retail
Rva004147CF::Rva004147CF(EmitVtableTag *) {}
