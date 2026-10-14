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
