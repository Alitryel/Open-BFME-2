// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Two more SpecialPowerTemplate field getters in the shape of Zero Hour's
// inline accessors (getSpecialPowerType 0x002AAE3D reads +0x14,
// getRequiredScience 0x0028F8D7 reads +0x1C): each reads one dword of the
// final override returned by the rowed Overridable::friend_getFinalOverride
// 0x00288609. Retail keeps these out-of-line copies with no direct caller.
// The fields they read are not identified, so the names are address-derived.

class Overridable
{
public:
	const Overridable *friend_getFinalOverride() const;	// 0x00288609
};

class SpecialPowerTemplate : public Overridable
{
public:
	int rva004210EF() const;
	int rva0044EB4B() const;

private:
	char m_pad00[0x30];
	int m_30;	// +0x30
	char m_pad34[0x44 - 0x34];
	int m_44;	// +0x44
};

// 0x004210EF (9B)
int SpecialPowerTemplate::rva004210EF() const
{
	return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_30;
}

// 0x0044EB4B (9B)
int SpecialPowerTemplate::rva0044EB4B() const
{
	return ((const SpecialPowerTemplate *)friend_getFinalOverride())->m_44;
}
