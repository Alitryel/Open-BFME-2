// ??0Rva00235A21@@QAE@XZ @0x00235A21 22B
// Default ctor constructing a 22-element 24B array at +0 via the vector ctor
// iterator 0x00001423 (count 0x16, size 0x18). The element ctor at 0x00235A0E
// is retail's WeaponBonus::WeaponBonus (rowed in WeaponReloadAmmo.cpp), so it
// is declared, never defined here. Callers 0x002369BA (GlobalData ctor, its
// m_weaponBonusSet slot) and 0x002CA8BA (the WeaponBonus INI parse, which then
// runs parseWeaponBonusSet on it) identify this class as BFME 2's
// WeaponBonusSet (no vptr). It keeps its address name because Weapon.cpp still
// emits a ZH-layout ??0WeaponBonusSet COMDAT that would clash with a row.
class WeaponBonus
{
public:
	WeaponBonus();

private:
	int m_words[6];
};

class Rva00235A21
{
public:
	Rva00235A21();

private:
	WeaponBonus m_arr[22];
};

Rva00235A21::Rva00235A21()
{
}
