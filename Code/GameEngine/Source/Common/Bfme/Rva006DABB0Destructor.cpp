// cl: /DNDEBUG /MD /EHsc
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Bfme/Rva006DABB0Destructor.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva006DABB0::~Rva006DABB0 0x000D1BA6 (68B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// Retail 0x006DABB0 (92 bytes). Virtual destructor: derived vtable 0x0111E134,
// unregister through global 0x012EF4F0, decrement instance count 0x012F801C,
// then base vtable 0x01073744. Scalar deleting dtor at 0x006DB540 calls this.
// Twin constructor is 0x006DB470 (same vtable and counter).

extern int g_012F801C;

class Rva006DABB0;

extern class G00DFF080Obj *TheTerrainVisual;

class Rva009FF080Manager
{
public:
	virtual void _slot00() = 0;
	virtual void _slot01() = 0;
	virtual void _slot02() = 0;
	virtual void _slot03() = 0;
	virtual void _slot04() = 0;
	virtual void _slot05() = 0;
	virtual void _slot06() = 0;
	virtual void _slot07() = 0;
	virtual void _slot08() = 0;
	virtual void _slot09() = 0;
	virtual void _slot10() = 0;
	virtual void _slot11() = 0;
	virtual void _slot12() = 0;
	virtual void _slot13() = 0;
	virtual void _slot14() = 0;
	virtual void _slot15() = 0;
	virtual void _slot16() = 0;
	virtual void _slot17() = 0;
	virtual void _slot18() = 0;
	virtual void _slot19() = 0;
	virtual void _slot20() = 0;
	virtual void _slot21() = 0;
	virtual void _slot22() = 0;
	virtual void _slot23() = 0;
	virtual void _slot24() = 0;
	virtual void _slot25(void *arg) = 0;
};

#define TheRva009FF080Manager (*(Rva009FF080Manager **)&TheTerrainVisual)

class Manager012EF4F0
{
public:
	// Out of line in retail at 0x00306769 (the rowed Rva00306769Forward body):
	// hands obj to TheTerrainVisual's slot 25 when both are set.
	__declspec(noinline) void unregister(Rva006DABB0 *obj)
	{
		Rva009FF080Manager *manager = TheRva009FF080Manager;
		if (manager == 0)
			return;
		if (obj == 0)
			return;
		manager->_slot25(obj);
	}
};

// g_012EF4F0 is only an alias of the owned global TheBuffLogic (ledger names column); this unit reads the owner through its own view type.
extern class BuffLogic *TheBuffLogic;
#define g_012EF4F0 (*(Manager012EF4F0 * *)&TheBuffLogic)

class Rva006DABB0Base
{
public:
	virtual ~Rva006DABB0Base() {}
};

class Rva006DABB0 : public Rva006DABB0Base
{
public:
	virtual ~Rva006DABB0();
};

Rva006DABB0::~Rva006DABB0()
{
	if (g_012EF4F0)
		g_012EF4F0->unregister(this);
	--g_012F801C;
}
