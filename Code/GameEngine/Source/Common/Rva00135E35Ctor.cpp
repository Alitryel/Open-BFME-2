// cl: /GX /MD /DNDEBUG /DWIN32 /D_WINDOWS
// ??0Rva00135E35@@QAE@XZ @0x00135E23 (18B). Default constructor of the opaque class whose scalar
// deleting destructor is rowed at 0x00135F19 (OpaqueScalarDeletingDtorsB02.cpp; vtable
// 0x00BD28F0, destructor 0x00135E35): GenBase009EB7D0 base via rowed 0x0061ED40, then the
// vtable store. No other state. Owner/identity unproven; address name stays.
class GenBase009EB7D0
{
public:
	GenBase009EB7D0();
	virtual ~GenBase009EB7D0();
};

class Rva00135E35 : public GenBase009EB7D0
{
public:
	Rva00135E35();
	virtual ~Rva00135E35();
};

Rva00135E35::Rva00135E35()
{
}

// The retail call in this body reads 0x00135E35, an address the ledger already
// carries as ?rva00135E35@BfmeThingUB@@QAEXXZ. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:??1Rva00135E35@@UAE@XZ=?rva00135E35@BfmeThingUB@@QAEXXZ")
