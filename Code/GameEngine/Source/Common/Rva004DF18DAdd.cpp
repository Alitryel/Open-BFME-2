// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004DF18D@Energy@@QAEXH@Z, RVA 0x004DF18D, 34 bytes.
// Adds delta to production +4, then if owner +0xC is non-null calls rowed
// Player::onPowerBrownOutChange 0x002AB8D0 with (production < consumption +8).
// Evidence: callers 0x004DF1EA 0x004DF229 0x004DF253 0x004DF26C 0x004DF288;
// callees all rowed; add plus test plus setl plus push shape.
class Player
{
public:
	void onPowerBrownOutChange(bool brownOut);
};

class Object;
struct Rva004DF207Outer;

class Energy
{
public:
	void adjustPower(int powerDelta, bool adding);
private:
	void *m_vptrPad;
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

void Energy::rva004DF18D(int delta)
{
	m_energyProduction += delta;
	if (m_owner)
		m_owner->onPowerBrownOutChange(m_energyProduction < m_energyConsumption);
}
