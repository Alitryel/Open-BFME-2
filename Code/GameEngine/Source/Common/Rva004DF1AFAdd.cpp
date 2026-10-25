// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?rva004DF1AF@Energy@@QAEXH@Z, RVA 0x004DF1AF, 34 bytes.
// Adds delta to consumption +8, then if owner +0xC is non-null calls rowed
// Player::onPowerBrownOutChange 0x002AB8D0 with (production +4 < consumption).
// Evidence: callers 0x004DF1FF 0x004DF21F 0x004DF247;
// sibling 0x004DF18D adds to m_energyProduction with same notify shape.
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

void Energy::rva004DF1AF(int delta)
{
	m_energyConsumption += delta;
	if (m_owner)
		m_owner->onPowerBrownOutChange(m_energyProduction < m_energyConsumption);
}
