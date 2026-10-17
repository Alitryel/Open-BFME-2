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

// --- 0x002714B4 (22B): TheAudio (VA 0x00DFE6E8) slot 52 (+0xD0) with the
// sound handle at +0x144.
class Rva002714B4Audio
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11)
	V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35)
	V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51)
#undef V
	virtual void slot52(unsigned int handle);
};
class AudioManager;
extern AudioManager *TheAudio;
class Rva002714B4
{
public:
	void rva002714B4();
private:
	char m_pad000[0x144];
	unsigned int m_handle;
};
void Rva002714B4::rva002714B4()
{
	((Rva002714B4Audio *)TheAudio)->slot52(m_handle);
}

// --- 0x00313923 (23B, RET4): TheWindowManager (VA 0x00DFEF1C) slot 60
// (+0xF0) with the receiver and the stack argument.
class Rva00313923;
class Rva00313923Manager
{
public:
#define V(n) virtual void slot##n();
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08) V(09) V(10) V(11)
	V(12) V(13) V(14) V(15) V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31) V(32) V(33) V(34) V(35)
	V(36) V(37) V(38) V(39) V(40) V(41) V(42) V(43) V(44) V(45) V(46) V(47)
	V(48) V(49) V(50) V(51) V(52) V(53) V(54) V(55) V(56) V(57) V(58) V(59)
#undef V
	virtual void slot60(Rva00313923 *window, int value);
};
class GameWindowManager;
extern GameWindowManager *TheWindowManager;
class Rva00313923
{
public:
	void rva00313923(int value);
};
void Rva00313923::rva00313923(int value)
{
	((Rva00313923Manager *)TheWindowManager)->slot60(this, value);
}

// --- Additional receiver-adjust forwarders (8B and 11B) ---------------------
class AsciiString;
class Xfer;
class Rva004E194E;

class ArmySummarySystem
{
public:
	int rva0040D025(int);
	const AsciiString *rva0040D041(int);
};

namespace _STL
{
template <class T> class allocator;
template <class T, class A> class vector
{
public:
	void push_back(const T &);
};
}

class Rva0023D012 { public: int rva0023D012(int a); private: char m_pad[0x184]; ArmySummarySystem m_184; };
int Rva0023D012::rva0023D012(int a) { return m_184.rva0040D025(a); }

class Rva0023D01D { public: const AsciiString *rva0023D01D(int a); private: char m_pad[0x184]; ArmySummarySystem m_184; };
const AsciiString *Rva0023D01D::rva0023D01D(int a) { return m_184.rva0040D041(a); }

class Rva00566557
{
public:
	void rva00566557(const Rva004E194E &v);
private:
	char m_pad[0x6C];
	_STL::vector<Rva004E194E, _STL::allocator<Rva004E194E> > m_6c;
};
void Rva00566557::rva00566557(const Rva004E194E &v) { m_6c.push_back(v); }

struct EmitVtableTag;

#define DEFINE_THUNK_UAE(Cls, Meth, Off, ArgDecl) \
	struct Cls##_BaseA { virtual void Meth ArgDecl = 0; char m_pad[(Off) - 4]; }; \
	struct Cls##_BaseB { virtual void Meth ArgDecl = 0; }; \
	class Cls : public Cls##_BaseA, public Cls##_BaseB \
	{ \
	public: \
		Cls(EmitVtableTag *); \
		virtual void Meth ArgDecl; \
	}; \
	Cls::Cls(EmitVtableTag *) {}

#define DEFINE_THUNK_MAE(Cls, Meth, Off, ArgDecl) \
	struct Cls##_BaseA { protected: virtual void Meth ArgDecl = 0; char m_pad[(Off) - 4]; }; \
	struct Cls##_BaseB { protected: virtual void Meth ArgDecl = 0; }; \
	class Cls : public Cls##_BaseA, public Cls##_BaseB \
	{ \
	public: \
		Cls(EmitVtableTag *); \
	protected: \
		virtual void Meth ArgDecl; \
	}; \
	Cls::Cls(EmitVtableTag *) {}

// ?<Rva003A57A9::Rva003A57A9> absent-from-retail
DEFINE_THUNK_UAE(Rva003A57A9, DoXfer, 0x0C, (Xfer &))
// ?<Rva003AE94E::Rva003AE94E> absent-from-retail
DEFINE_THUNK_UAE(Rva003AE94E, xfer, 0x18, (Xfer *))
// ?<Rva0055B30F::Rva0055B30F> absent-from-retail
DEFINE_THUNK_UAE(Rva0055B30F, rva0055B30F, 0x1C, (Xfer *))
// ?<Rva0055B951::Rva0055B951> absent-from-retail
DEFINE_THUNK_UAE(Rva0055B951, rva0055B951, 0x1C, (Xfer *))
// ?<Rva0055EF39::Rva0055EF39> absent-from-retail
DEFINE_THUNK_UAE(Rva0055EF39, xfer, 0x1C, (Xfer *))
// ?<Rva0055F710::Rva0055F710> absent-from-retail
DEFINE_THUNK_UAE(Rva0055F710, rva0055F710, 0x1C, (Xfer *))
// ?<Rva0055DB41::Rva0055DB41> absent-from-retail
DEFINE_THUNK_UAE(Rva0055DB41, DoXfer, 0x1C, (Xfer &))
// ?<Rva0055CA8A::Rva0055CA8A> absent-from-retail
DEFINE_THUNK_MAE(Rva0055CA8A, xfer, 0x1C, (Xfer *))
// ?<Rva0055CD38::Rva0055CD38> absent-from-retail
DEFINE_THUNK_UAE(Rva0055CD38, rva0055CD38, 0x1C, (Xfer *))
// ?<Rva0055D3F5::Rva0055D3F5> absent-from-retail
DEFINE_THUNK_UAE(Rva0055D3F5, rva0055D3F5, 0x1C, (Xfer *))
// ?<Rva003AF22E::Rva003AF22E> absent-from-retail
DEFINE_THUNK_MAE(Rva003AF22E, xfer, 0x18, (Xfer *))
// ?<Rva0055B3D9::Rva0055B3D9> absent-from-retail
DEFINE_THUNK_UAE(Rva0055B3D9, xfer, 0x0C, (Xfer *))
// ?<Rva0055BB5C::Rva0055BB5C> absent-from-retail
DEFINE_THUNK_UAE(Rva0055BB5C, rva0055BB5C, 0x0C, (Xfer *))
// ?<Rva0055F805::Rva0055F805> absent-from-retail
DEFINE_THUNK_UAE(Rva0055F805, rva0055F805, 0x0C, (Xfer *))
// ?<Rva003AE0AF::Rva003AE0AF> absent-from-retail
DEFINE_THUNK_MAE(Rva003AE0AF, xfer, 0x10, (Xfer *))
// ?<Rva003AE2A9::Rva003AE2A9> absent-from-retail
DEFINE_THUNK_MAE(Rva003AE2A9, xfer, 0x10, (Xfer *))
// ?<Rva005E62F1::Rva005E62F1> absent-from-retail
DEFINE_THUNK_UAE(Rva005E62F1, rva0050B238, 0x20, (void *, unsigned int))

namespace FXParticleSystem
{
// ?<BoxEmissionVolumeModule::BoxEmissionVolumeModule> absent-from-retail
DEFINE_THUNK_MAE(BoxEmissionVolumeModule, xfer, 0x1C, (Xfer *))
// ?<OrthoEmissionVelocityModule::OrthoEmissionVelocityModule> absent-from-retail
DEFINE_THUNK_MAE(OrthoEmissionVelocityModule, xfer, 0x18, (Xfer *))
// ?<CylindricalEmissionVelocityModule::CylindricalEmissionVelocityModule> absent-from-retail
DEFINE_THUNK_MAE(CylindricalEmissionVelocityModule, xfer, 0x18, (Xfer *))
}
