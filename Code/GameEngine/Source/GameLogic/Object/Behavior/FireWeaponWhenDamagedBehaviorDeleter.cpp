// cl: /O1 /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD
//
// ??_GRva004A4C19@@UAEPAXI@Z, retail 0x004A4D54 (28 bytes).
// Scalar deleting destructor: calls the dtor at 0x004A4C19 (rowed opaque as
// ??1Rva004A4C19 in Rva0024A797Grandchildren.cpp) then conditional global
// operator delete (matched 0x002FD60).
// Identity (target facts): 0x004A4D54 is slot 0 of vftable 0x00C52868, the
// set the dtor 0x004A4C19 and the ctor 0x004A4CC7 install; that ctor is rowed
// ??0RubbleRiseUpdate. FireWeaponWhenDamagedBehavior's own vftable 0x00C4965C
// (ctor 0x00482803, dtor 0x00482551) has its deleting dtor at 0x00482A4D, so
// this body was misnamed; it keeps the opaque class of its rowed dtor.
// The dtor is declared-not-defined so this TU calls it out-of-line.

class Thing;
class ModuleData;

class Rva004A4C19
{
public:
	virtual ~Rva004A4C19();
	Rva004A4C19();
};

// ??0Rva004A4C19@@QAE@XZ present-unmatched
Rva004A4C19::Rva004A4C19()
{
}

void Rva004A4C19Deleter(Rva004A4C19 *doomed)
{
	delete doomed;
}
