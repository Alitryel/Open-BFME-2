// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Member forwarders from unrowed .text gaps: each adjusts or loads the
// receiver and tail-jumps a rowed callee, called through that row's own
// spelling. Owners are not recovered, so each keeps an address-derived name
// and a view of only the member it reaches. Skeletons match the matched
// wide-adjust forwarders (RvaWideAdjustFwds.cpp) and the guarded
// member-pointer forwarders.

class Rva0040A59B
{
public:
	void rva0040A59B();
};

class Dict;
class TeamsInfoRec
{
public:
	int addTeam(const Dict *d);
};

class BfmeDfe6e4
{
public:
	void _M_rva00625476();
};

// --- 0x00219435 (11B): +0x174 then the rowed 0x0040A59B.
class Rva00219435
{
public:
	void rva00219435();
private:
	char m_pad000[0x174];
	Rva0040A59B m_174;
};
void Rva00219435::rva00219435()
{
	m_174.rva0040A59B();
}

// --- 0x0023C60E (11B): +0xF44 then the rowed TeamsInfoRec::addTeam
// 0x0032DA4E with the stack argument passed through (the shape of Zero
// Hour's inline SidesList::addTeam forwarding to its team record; the owner
// is not proven here).
class Rva0023C60E
{
public:
	int rva0023C60E(const Dict *d);
private:
	char m_pad000[0xF44];
	TeamsInfoRec m_teams;
};
int Rva0023C60E::rva0023C60E(const Dict *d)
{
	return m_teams.addTeam(d);
}

// --- 0x0023C4A1 (12B): calls the rowed 0x00225476 on the pointer at +0
// when it is set.
class Rva0023C4A1
{
public:
	void rva0023C4A1();
private:
	BfmeDfe6e4 *m_target;
};
void Rva0023C4A1::rva0023C4A1()
{
	if (m_target)
		m_target->_M_rva00625476();
}

// --- 8-byte receiver-adjust forwarders (add ecx, imm8; jmp rowed callee),
// the skeleton of ??1PlayerPosition 0x0022D920. Stack arguments pass
// through; each callee keeps its ledger spelling.
class RvaSmartPtr12
{
public:
	RvaSmartPtr12 &operator=(const RvaSmartPtr12 &other);	// 0x0004CC3D
private:
	void *m_ptr;
};
class Rva00283002 { public: void rva00283002(); };	// 0x00283002 (list clear)
enum ScienceType { };
class Player { public: bool hasScience(ScienceType science) const; };	// 0x002AB7D5
class DataChunkInput;
class ElevatedAreaPolygon { public: void parse(DataChunkInput &file, int val); };	// 0x0030BB87
struct Rva0030B7C2Point;
class Rva002E37B1 { public: bool rva002E37B1(const Rva0030B7C2Point *point); };	// 0x002E37B1
class Rva003184B8 { public: void rva003184B8(); };	// 0x003184B8
class Rva0030B719Shape { public: float rva0030B706() const; };	// 0x0030B706

// --- 0x001F4A1A: +0x78 then RvaSmartPtr12::operator=.
class Rva001F4A1A
{
public:
	RvaSmartPtr12 &rva001F4A1A(const RvaSmartPtr12 &other);
private:
	char m_pad00[0x78];
	RvaSmartPtr12 m_78;
};
RvaSmartPtr12 &Rva001F4A1A::rva001F4A1A(const RvaSmartPtr12 &other)
{
	return m_78 = other;
}

// --- 0x0028339B: +0x64 then the rowed list clear 0x00283002.
class Rva0028339B
{
public:
	void rva0028339B();
private:
	char m_pad00[0x64];
	Rva00283002 m_64;
};
void Rva0028339B::rva0028339B()
{
	m_64.rva00283002();
}

// --- 0x002B118A: from a sub-object at +4 of a Player back to
// Player::hasScience.
class Rva002B118A
{
public:
	bool rva002B118A(ScienceType science) const;
};
bool Rva002B118A::rva002B118A(ScienceType science) const
{
	return ((const Player *)((const char *)this - 4))->hasScience(science);
}

// --- 0x002E36AF: +8 then ElevatedAreaPolygon::parse.
class Rva002E36AF
{
public:
	void rva002E36AF(DataChunkInput &file, int val);
private:
	char m_pad00[8];
	ElevatedAreaPolygon m_08;
};
void Rva002E36AF::rva002E36AF(DataChunkInput &file, int val)
{
	m_08.parse(file, val);
}

// --- 0x002E37C3: from a sub-object at +0x38 back to the rowed 0x002E37B1.
class Rva002E37C3
{
public:
	bool rva002E37C3(const Rva0030B7C2Point *point);
};
bool Rva002E37C3::rva002E37C3(const Rva0030B7C2Point *point)
{
	return ((Rva002E37B1 *)((char *)this - 0x38))->rva002E37B1(point);
}

// --- 0x003187A0: from a sub-object at +0xC back to the rowed 0x003184B8.
class Rva003187A0
{
public:
	void rva003187A0();
};
void Rva003187A0::rva003187A0()
{
	((Rva003184B8 *)((char *)this - 0xC))->rva003184B8();
}

// --- 0x00330A9E: +8 then the rowed shape getter 0x0030B706 (float).
class Rva00330A9E
{
public:
	float rva00330A9E() const;
private:
	char m_pad00[8];
	Rva0030B719Shape m_08;
};
float Rva00330A9E::rva00330A9E() const
{
	return m_08.rva0030B706();
}
