// cl: /O1 /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva00494DCA@@QAE@PAVThing@@PBVModuleData@@@Z at
// retail 0x00494DCA (47B). Opaque-base pattern (unidentified 0x88-byte
// UpdateModule-derived intermediate base 0x0044EF5E, pinned opaque as
// Rva0044EF5E); the derived body re-stores the inherited +0x0C/+0x10/+0x20
// pointer slots (address-of TU-local dummies, DIR32-patched: 0xC4D640 /
// 0xC4EB30 / 0xC4EB0C). No trailing members (factory stub news 0x88).
// Identity unproven (opaque Rva name); serves the 0x24DD98 factory stub.
class Thing;
class ModuleData;

static int s_dummy0C;
static int s_dummy10;
static int s_dummy20;

// Opaque 0x88-byte UpdateModule-derived intermediate; ctor resolves to the
// opaque pin at 0x0044EF5E. Protected slots mirror the retail stores.
class Rva0044EF5E
{
public:
	Rva0044EF5E(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva0044EF5E();

protected:
	unsigned char m_pad0[8];
	const void *m_p0C;
	const void *m_p10;
	unsigned char m_pad1[0x20 - 0x14];
	const void *m_p20;
	unsigned char m_pad2[0x88 - 0x24];
};

class Rva00494DCA : public Rva0044EF5E
{
public:
	Rva00494DCA(Thing *thing, const ModuleData *moduleData);
	virtual ~Rva00494DCA();
};

Rva00494DCA::Rva00494DCA(Thing *thing, const ModuleData *moduleData)
	: Rva0044EF5E(thing, moduleData)
{
	m_p0C = &s_dummy0C;
	m_p10 = &s_dummy10;
	m_p20 = &s_dummy20;
}

// ?Rva00494DCA::~Rva00494DCA present-unmatched
Rva00494DCA::~Rva00494DCA()
{
}
