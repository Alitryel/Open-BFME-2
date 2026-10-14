// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.
class BfmeArg985
{
public:
	char bfmeHas985C(int v);
};

// 0x00290D2B is rowed as Object::rva00290D2B(const UpgradeTemplate *) const
// (ObjectRva00290D2B.cpp); the argument is the upgrade template.
class UpgradeTemplate;
class Object
{
public:
	bool rva00290D2B(const UpgradeTemplate *upgrade) const;
};

class BfmeC985
{
public:
	char bfmeGo985C(BfmeArg985 *a);

	char m_bfmePad[8];
	int m_bfmeVal;
};

char BfmeC985::bfmeGo985C(BfmeArg985 *a)
{
	if (a->bfmeHas985C(m_bfmeVal) && !((Object *)a)->rva00290D2B((const UpgradeTemplate *)m_bfmeVal))
		return 1;

	return 0;
}
