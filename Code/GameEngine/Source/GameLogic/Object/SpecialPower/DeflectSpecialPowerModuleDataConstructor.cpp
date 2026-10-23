// cl: /DNDEBUG /MD /EHsc

// DeflectSpecialPowerModuleData's constructor, retail 0x0025A600. Eighteen bytes: the
// base's constructor and then this class's own vftable pointer, nothing else.
//
// The name used to sit on 0x00852130, which is INI::initFromINIMultiProc - a
// seventy-nine byte function that clears two sixteen-entry tables and is not a
// module-data constructor at all. It was one of seven names aliased onto those
// bytes; that claim is retracted here.

class DeflectSpecialPowerModuleDataBase
{
public:
	DeflectSpecialPowerModuleDataBase();

	virtual void moduleDataAnchor();
};

class DeflectSpecialPowerModuleData : public DeflectSpecialPowerModuleDataBase
{
public:
	DeflectSpecialPowerModuleData();
};

DeflectSpecialPowerModuleData::DeflectSpecialPowerModuleData()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?moduleDataAnchor@DeflectSpecialPowerModuleDataBase@@UAEXXZ=??_GDeflectSpecialPowerModuleData@@UAEPAXI@Z")
