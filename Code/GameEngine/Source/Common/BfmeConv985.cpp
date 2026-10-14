// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
class BfmeArg985;

// 0x00290D2B is rowed as Object::rva00290D2B(const UpgradeTemplate *) const
// (ObjectRva00290D2B.cpp); the argument is the upgrade template.
class UpgradeTemplate;
class Object
{
public:
	bool rva00290D2B(const UpgradeTemplate *upgrade) const;
	bool affectedByUpgrade(const UpgradeTemplate *upgrade) const;
};

// Slot 1 (allow) of partition filter vftable 0x00C51150.
class Rva00261130Filter
{
public:
	virtual ~Rva00261130Filter();
	virtual bool allow(Object *a);

	char m_bfmePad[4];
	int m_bfmeVal;
};

bool Rva00261130Filter::allow(Object *a)
{
	if (a->affectedByUpgrade((const UpgradeTemplate *)m_bfmeVal) && !a->rva00290D2B((const UpgradeTemplate *)m_bfmeVal))
		return true;

	return false;
}
