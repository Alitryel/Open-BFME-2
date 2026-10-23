// cl: /Ireference/shims/bfme2_ascii /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// Retail 0x00355B61 (85 bytes): SubsystemInterface plus Snapshot bases and two
// 0x14-byte ArmorTemplateMap members. The map calls must use the already-owned
// constructor/dtor COMDATs at 0x00355B42 and 0x00355257, not local instantiations.
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class SnapshotBase
{
public:
	virtual ~SnapshotBase();
};

class ArmorTemplateMap
{
public:
	ArmorTemplateMap();
	~ArmorTemplateMap();

private:
	char m_pad[0x14];
};

class Rva00355B61 : public SubsystemInterface, public SnapshotBase
{
public:
	Rva00355B61();
	virtual ~Rva00355B61();
	void init() { }
	void reset();	// slot 9, defined at 0x00355141 (Rva00355141Clear.cpp)
	void update() { }

private:
	ArmorTemplateMap m_map1;
	ArmorTemplateMap m_map2;
};

Rva00355B61::Rva00355B61()
{
}

// Destructor names this unit's vftable and unwind reference, bound to the rows the retail bytes lead to:
// ??1Rva00355B61@@UAE@XZ: the deleting destructor 0x00355BBE calls 0x00355BDA
#pragma comment(linker, "/alternatename:??1Rva00355B61@@UAE@XZ=??1Rva00355BDA@@UAE@XZ")
// ??1SnapshotBase@@UAE@XZ: that destructor finishes by calling ~SubsystemInterface (0x001B4E74), its base
#pragma comment(linker, "/alternatename:??1SnapshotBase@@UAE@XZ=??1SubsystemInterface@@UAE@XZ")
