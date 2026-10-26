// Private receiver views shared by the Energy power helpers and Xfer body.
// Retail accesses establish production +4, consumption +8, owner +0xC,
// and the owning player's index +0x54. The three unnamed virtual slots
// retain EnergyXfer's existing dispatch prefix; no complete class recovery.
#ifndef BFME_ENERGY_VIEW_H
#define BFME_ENERGY_VIEW_H

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

class Object;
struct Rva004DF207Outer;

class Player
{
public:
	char m_unrecovered00[0x54];
	int m_playerIndex;
	void onPowerBrownOutChange(bool brownOut);
};

class Energy
{
protected:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void xfer(Xfer *xfer);
public:
	void adjustPower(int powerDelta, bool adding);
private:
	int m_energyProduction;
private:
	int m_energyConsumption;
private:
	Player *m_owner;
private:
	void addProduction(int amount)
	{
		m_energyProduction += amount;
		if (m_owner == 0)
			return;
		m_owner->onPowerBrownOutChange(m_energyProduction < m_energyConsumption);
	}
private:
	void addConsumption(int amount)
	{
		m_energyConsumption += amount;
		if (m_owner == 0)
			return;
		m_owner->onPowerBrownOutChange(m_energyProduction < m_energyConsumption);
	}
public:
	void objectEnteringInfluence(Object *obj);
public:
	void objectLeavingInfluence(Object *obj);
public:
	void rva004DF25B(Rva004DF207Outer *arg);
public:
	void rva004DF274(Rva004DF207Outer *arg);
public:
	void rva004DF18D(int delta);
public:
	void rva004DF1AF(int delta);
public:
	float getEnergySupplyRatio() const;
};

#endif
