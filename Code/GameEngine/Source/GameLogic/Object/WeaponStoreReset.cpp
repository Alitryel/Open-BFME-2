// cl: /O1 /G7 /arch:SSE /DNDEBUG /DWIN32 /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Donor: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d
// game/GameEngine/Source/GameLogic/Object/WeaponStore_reset.cpp.
// Native BFME 2 table C02114 slot 9 and WB BB4430 establish WeaponStore::reset.
// WB BB43D0 indexes the active vector at +0x0C and calls the empty
// WeaponTemplate::reset. Preserve the real STLport operations: their visible
// definitions retain the 28-byte counted loop that a hand-written empty loop
// loses. The target's template successor is +0x04, as in the donor.

#define _STLP_NO_EXCEPTIONS 1

#include <vector>

typedef int Int;

// Layout fields are supported by native reset and the matched override unit.
class WeaponTemplate
{
public:
	virtual ~WeaponTemplate();

	__declspec(dllimport) void reset( void ) { }

	WeaponTemplate *friend_clearNextTemplate( void ) { WeaponTemplate *ret = m_nextTemplate; m_nextTemplate = 0; return ret; }
	bool isOverride( void ) { return m_nextTemplate != 0; }

private:
	WeaponTemplate *m_nextTemplate;							///< this+0x04
};

typedef _STL::vector<WeaponTemplate *> WeaponTemplateVector;

class WeaponStore
{
public:
	virtual void reset();

protected:
	void resetWeaponTemplates( void )
	{
		for (Int i = 0; i < m_weaponTemplateVector.size(); i++)
		{
			WeaponTemplate* wt = m_weaponTemplateVector[i];
			wt->reset();
		}
	}

private:
	unsigned char m_unmodelled004[0x8];
	WeaponTemplateVector m_weaponTemplateVector;			///< this+0x0C
};

void WeaponStore::reset()
{
	// clean up any overriddes.
	for (WeaponTemplateVector::iterator it = m_weaponTemplateVector.begin(); it != m_weaponTemplateVector.end(); ++it)
	{
		WeaponTemplate *wt = *it;
		if (wt->isOverride())
		{
			WeaponTemplate *override = wt;
			wt = wt->friend_clearNextTemplate();
			// Native dispatch uses destructor flag 0 then global delete.
			::delete override;
			*it = wt;
		}
	}

	resetWeaponTemplates();
}
