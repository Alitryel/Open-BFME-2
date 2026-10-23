// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata /MD /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Retail 0x00355BDA (85 bytes): destroys ArmorTemplateMap members at +0x24/+0x10
// via rowed 0x00355257, restores the Snapshot vptr, then calls the rowed
// SubsystemInterface destructor at 0x001B4E74.

#include "Common/Snapshot.h"

// ArmorTemplateMap is the Armor hash_map; its destructor is the hashtable
// destructor the 0x00355257 gen-alias row stands for (same 57-byte body).
#pragma comment(linker, "/alternatename:??1ArmorTemplateMap@@QAE@XZ=??1?$hashtable@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@W4NameKeyType@@U?$hash@W4NameKeyType@@@rts@@U?$_Select1st@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@U?$equal_to@W4NameKeyType@@@2@V?$allocator@U?$pair@$$CBW4NameKeyType@@VArmorTemplate@@@_STL@@@2@@_STL@@QAE@XZ")

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
#include "../../../../Libraries/Source/subsystem/SubsystemInterface.h"

class ArmorTemplateMap
{
public:
	ArmorTemplateMap();
	~ArmorTemplateMap();

private:
	char m_pad[0x14];
};

class __declspec(novtable) Rva00355BDA : public SubsystemInterface, public Snapshot
{
public:
	virtual ~Rva00355BDA();

private:
	ArmorTemplateMap m_map10;
	ArmorTemplateMap m_map24;
};

Rva00355BDA::~Rva00355BDA()
{
}
