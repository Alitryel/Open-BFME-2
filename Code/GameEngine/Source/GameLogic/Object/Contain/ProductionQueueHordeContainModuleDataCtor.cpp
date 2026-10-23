// cl: /DNDEBUG /MD
// stlport
//
// ??0ProductionQueueHordeContainModuleData@@QAE@XZ, retail 0x00481776,
// 36 bytes. ModuleData ctor over the rowed HordeGarrisonContainModuleData
// base (0x47A251, 88B): the implicit _STL::vector<int> member at +0xD4
// builds through the folded Vector_base at 0x211E58 (int spelling reuses
// the existing pin), and the compiler installs the derived vtable 0x00C490F8
// between the vector setup and call (TransitionDamageFX precedent: only
// compiler stores split setup/call; the base carries a non-dtor virtual so
// no EH prolog draws). Class size 0xE0 proven by the
// ProductionQueueHordeContain data factory (news 0xE0, sole caller at
// 0x24C1B3). Row supersedes the ctor pin.

#include <vector>

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *m_name;
	INIFieldParseProc m_parser;
	const void *m_userData;
	int m_offset;
};

// Rowed parse proc (retail 0x004816F4).


class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class HordeGarrisonContainModuleData
{
public:
	HordeGarrisonContainModuleData();
	virtual ~HordeGarrisonContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

protected:
	// +0x00 vptr; remainder opaque to 0x58 (rowed base size).
	unsigned char m_opaque[0x54];
};

class ProductionQueueHordeContainModuleData : public HordeGarrisonContainModuleData
{
public:
	ProductionQueueHordeContainModuleData();
	virtual ~ProductionQueueHordeContainModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);

private:
	// +0x58 pad to the vector member.
	unsigned char m_pad58[0x7C];
	// +0xD4 vector (implicit default init; ends at the rowed 0xE0 size).
	_STL::vector<int> m_vectorD4;
public:
	static void iniParseTemplateContainer(INI *ini, void *instance, void *store, const void *userData);
};

// ??0ProductionQueueHordeContainModuleData@@QAE@XZ @0x00481776
ProductionQueueHordeContainModuleData::ProductionQueueHordeContainModuleData()
	: HordeGarrisonContainModuleData()
{
}

// ?buildFieldParse@ProductionQueueHordeContainModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0048175B
void ProductionQueueHordeContainModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	HordeGarrisonContainModuleData::buildFieldParse(parse);

	// Own table (retail .data 0x00C490D4): one entry and the terminator.
	static const FieldParse dataFieldParse[] =
	{
		{ "DestinationTemplate", ProductionQueueHordeContainModuleData::iniParseTemplateContainer, 0, 0xD4 },
		{ 0, 0, 0, 0 }
	};
	parse.add(dataFieldParse, 0);
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
