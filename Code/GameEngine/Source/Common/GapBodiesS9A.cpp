// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small GameEngine bodies with no caller and no table reference (out-of-line
// copies of inline members), found by their instruction skeletons matching
// rowed bodies. Owners are not recovered: each keeps an address-derived
// name and a view of only the members it touches.

// --- 0x0042665E (9B): raise the byte at +5 and clear the one at +6; the
// shape of GameInfo::endGame 0x003FF296.
class Rva0042665E
{
public:
	void rva0042665E();

private:
	char m_pad00[5];
	bool m_05;
	bool m_06;
};

void Rva0042665E::rva0042665E()
{
	m_05 = true;
	m_06 = false;
}

// --- 0x004F5FCF (9B): zero the float at +0xC; the shape of
// Rva00094BA0Float::zero 0x00094BA0 (SSE zero store).
class Rva004F5FCF
{
public:
	void zero();

private:
	char m_pad00[0xC];
	float m_0C;
};

void Rva004F5FCF::zero()
{
	m_0C = 0.0f;
}

// --- 0x003BA655 (10B): store the bool argument at +0x4A (ret 4); the shape
// of DockUpdate::setDockCrippled 0x00589661.
class Rva003BA655
{
public:
	void set(bool value);

private:
	char m_pad00[0x4A];
	bool m_4A;
};

void Rva003BA655::set(bool value)
{
	m_4A = value;
}
