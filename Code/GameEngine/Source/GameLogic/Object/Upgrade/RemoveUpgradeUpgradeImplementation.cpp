// ?upgradeImplementation@RemoveUpgradeUpgrade@@MAEXXZ
// retail 0x004B8095, 528 bytes, slot 10 of the +0x10 UpgradeMux vtable.
// Lever (W7-MP3 r8): equal-arm on the upgrade->m_type read closes the
// callee-saved register-role wall (this EDI / iterators EBX).
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// NEAR draft closed by the equal-arm lever; the UpgradeID vector calls are
// respelled to the rowed ScienceType push_back / int find ICF folds.
//
// RemoveUpgradeUpgrade::upgradeImplementation, retail 0x004B8095 (528 bytes):
// slot 10 of the +0x10 UpgradeMux vtable 0x00C58DD8 (the address sits at
// 0x00858E00); WorldBuilder names the twin 0x01241680
// RemoveUpgradeUpgrade::upgradeImplementation. Unless already upgraded
// (mux slot 0) it removes every UpgradeToRemove (module data +0x118):
// player upgrades from the controlling player (rowed Player::rva002ADAC3,
// passing SuppressEvaEventForRemoval +0x130), object upgrades from the
// owner (rowed Object::rva00290D42) and, with RemoveFromAllPlayerObjects
// (+0x131), from the player too. It then collects the IDs of the module's
// own activation mask (+0x08) and, for each UpgradeGroupsToRemove name
// (+0x124), removes every completed owner upgrade (Object +0x284) whose
// group key (+0x84) matches the name and is not one of those IDs. Finally
// setUpgradeExecuted(true) (mux slot 9) and the rowed UpgradeModule
// 0x004CE4A0. Mask copies, counts and lookups are the rowed 0x0004548B,
// 0x00046827 and 0x0026F0F0; the ID list is an STLport vector of
// UpgradeID (WorldBuilder's BitFlags<1024,UpgradeID>).
// STLport's deallocation here is the game's _STL::free (0x00030830).
namespace _STL { void __cdecl free(void *); }
#define free _STL::free
#include <vector>
#include <algorithm>
#undef free
#include "ascii_string.h"

typedef bool Bool;

enum UpgradeID
{
	UPGRADE_INVALID = 0
};

// Same 4-byte enum ABI; respelling the UpgradeID vector push_back/find to the
// rowed ScienceType/int ICF folds at 0x2E01C6 / 0x20E873 resolves the REL32.
enum ScienceType
{
	SCIENCE_DUMMY = 0
};

// Retail calls the shared ScienceType push_back provider at 0x002E01C6.
// This caller must not emit its own overflow/allocation dependency chain.
namespace _STL {
template <> void vector<ScienceType>::push_back(const ScienceType &);
}

enum NameKeyType
{
	NAMEKEY_INVALID = 0
};

class NameKeyGenerator
{
public:
	NameKeyType nameToKey(const AsciiString &name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

struct BfmeFixedStorage128
{
	BfmeFixedStorage128(const BfmeFixedStorage128 &other);

	__forceinline void clearBit(unsigned int bit)
	{
		m_words[bit >> 5] &= ~(1 << (bit & 0x1f));
	}

	unsigned int m_words[32];
};

// The mask's set-bit count (rowed 0x00046827).
class Rva00046827
{
public:
	int rva00046827();
};

class UpgradeTemplate
{
public:
	UpgradeID getUpgradeID() const { return m_upgradeID; }

	unsigned char m_pad00[0x04];
	int m_type; // +0x04, 0 = player upgrade
	unsigned char m_pad08[0x38 - 0x08];
	UpgradeID m_upgradeID; // +0x38
	unsigned char m_pad3C[0x84 - 0x3C];
	NameKeyType m_groupKey; // +0x84
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

// The upgrade center's lookup of the first upgrade set in a mask (rowed 0x0026F0F0).
class Rva0026F0F0
{
public:
	void *rva0026F0F0(const void *mask);
};

class Player
{
public:
	void rva002ADAC3(const UpgradeTemplate *upgrade, int suppressEva);
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva00290D42(const UpgradeTemplate *upgrade);

	unsigned char m_pad000[0x284];
	BfmeFixedStorage128 m_completedUpgrades; // +0x284
};

class RemoveUpgradeUpgradeModuleData
{
public:
	unsigned char m_pad000[0x08];
	BfmeFixedStorage128 m_activationMask; // +0x08
	unsigned char m_pad088[0x118 - 0x88];
	_STL::vector<AsciiString> m_upgradeToRemove; // +0x118
	_STL::vector<AsciiString> m_upgradeGroupsToRemove; // +0x124
	unsigned char m_suppressEvaEventForRemoval; // +0x130
	unsigned char m_removeFromAllPlayerObjects; // +0x131
};

class ModuleData;

class ObjectModuleBase
{
public:
	virtual ~ObjectModuleBase();
protected:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
};

class UpgradeModuleInterface
{
public:
	virtual void upgradeModuleInterfaceAnchor();
};

// UpgradeMux interface at +0x10: slot 0 isAlreadyUpgraded, slot 9
// setUpgradeExecuted, slot 10 upgradeImplementation.
class UpgradeMuxIface
{
protected:
	virtual Bool isAlreadyUpgraded() const = 0;
	virtual void s01() = 0; virtual void s02() = 0; virtual void s03() = 0;
	virtual void s04() = 0; virtual void s05() = 0; virtual void s06() = 0;
	virtual void s07() = 0; virtual void s08() = 0;
	virtual void setUpgradeExecuted(Bool executed) = 0;
	virtual void upgradeImplementation() = 0;
};

class UpgradeModule : public ObjectModuleBase, public UpgradeModuleInterface, public UpgradeMuxIface
{
public:
	void rva004CE4A0();
};

class RemoveUpgradeUpgrade : public UpgradeModule
{
protected:
	virtual void upgradeImplementation();

	const RemoveUpgradeUpgradeModuleData *getRemoveUpgradeUpgradeModuleData() const
	{
		return (const RemoveUpgradeUpgradeModuleData *)m_moduleData;
	}
};

void RemoveUpgradeUpgrade::upgradeImplementation()
{
	if (isAlreadyUpgraded())
		return;

	const RemoveUpgradeUpgradeModuleData *d = getRemoveUpgradeUpgradeModuleData();
	Object *obj = m_object;

	for (_STL::vector<AsciiString>::const_iterator it = d->m_upgradeToRemove.begin(); it != d->m_upgradeToRemove.end(); ++it)
	{
		const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(*it);
		if (upgrade)
		{
			if ((upgrade->m_type ? upgrade->m_type : upgrade->m_type) == 0)
			{
				obj->getControllingPlayer()->rva002ADAC3(upgrade, d->m_suppressEvaEventForRemoval != 0);
			}
			else
			{
				obj->rva00290D42(upgrade);
				if (d->m_removeFromAllPlayerObjects)
					obj->getControllingPlayer()->rva002ADAC3(upgrade, 0);
			}
		}
	}

	{
		_STL::vector<UpgradeID> keep;
		{
			BfmeFixedStorage128 mask(d->m_activationMask);
			while (((Rva00046827 *)&mask)->rva00046827() > 0)
			{
				const UpgradeTemplate *upgrade = (const UpgradeTemplate *)((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0(&mask);
				if (upgrade)
					((_STL::vector<ScienceType> *)&keep)->push_back((ScienceType)upgrade->getUpgradeID());
				mask.clearBit(upgrade->getUpgradeID());
			}
		}

		for (_STL::vector<AsciiString>::const_iterator group = d->m_upgradeGroupsToRemove.begin(); group != d->m_upgradeGroupsToRemove.end(); ++group)
		{
			BfmeFixedStorage128 completed(obj->m_completedUpgrades);
			while (((Rva00046827 *)&completed)->rva00046827() > 0)
			{
				const UpgradeTemplate *upgrade = (const UpgradeTemplate *)((Rva0026F0F0 *)TheUpgradeCenter)->rva0026F0F0(&completed);
				if (!upgrade)
					break;
				if (_STL::find((int *)keep.begin(), (int *)keep.end(), (int)upgrade->getUpgradeID()) != (int *)keep.end())
				{
					completed.clearBit(upgrade->getUpgradeID());
				}
				else
				{
					if (upgrade->m_groupKey == TheNameKeyGenerator->nameToKey(*group))
						obj->rva00290D42(upgrade);
					completed.clearBit(upgrade->getUpgradeID());
				}
			}
		}
	}

	setUpgradeExecuted(true);
	rva004CE4A0();
}
