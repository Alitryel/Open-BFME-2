// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/moduledata /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /DBFME_MODULE_NO_MPO
// The shared headers declare these members with the access/virtual spelling
// the referring objects use; this TU emits the paired definition spelling.
// Same function, same address: bind the header spelling here.
#pragma comment(linker, "/alternatename:??1CreateModuleData@@QAE@XZ=??1CreateModuleData@@UAE@XZ")

// stlport
#include "PreRTS.h"	// This must go first in EVERY cpp file int the GameEngine

#include "GameLogic/Module/LockWeaponCreate.h"

LockWeaponCreateModuleData::LockWeaponCreateModuleData()
{
	m_slotToLock = PRIMARY_WEAPON;
}

// ??1LockWeaponCreate@@MAE@XZ present-unmatched
LockWeaponCreate::~LockWeaponCreate()
{
}

// 0x0024FC20. The base call reaches CreateModule's constructor at 0x0024F450
// through ILT 0x00026CAB, and the three vtable stores that follow are this
// class's own (0x010B18E4 / 0x010B1820 / 0x010B180C) -- the constructor the
// name getter, destructor and pool glue at 0x0024FC60..0x0024FD70 belong to.
LockWeaponCreate::LockWeaponCreate( Thing *thing, const ModuleData *moduleData )
	: CreateModule( thing, moduleData )
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?onCreate@LockWeaponCreate@@UAEXXZ=??1Coord2D@@QAE@XZ")
#pragma comment(linker, "/alternatename:?crc@LockWeaponCreate@@MAEXPAVXfer@@@Z=??_GRva004B8C3E@@UAEPAXI@Z")
#pragma comment(linker, "/alternatename:?loadPostProcess@LockWeaponCreate@@MAEXXZ=?Rva004B8C38Get@@YAHXZ")
