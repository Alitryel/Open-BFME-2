// cl: /MD /EHsc /DNDEBUG
// ??1TeamFactory@@UAE@XZ, retail 0x003A383A, 95 bytes.
// TeamFactory dtor: stores vtables 0x0081AE2C/0x0081AE1C, calls clear via pin 0x003A2F4C, clears TheTeamFactory, destroys member at +0xB0 via rowed 0x0039FB11, restores Snapshot base BBB554 then base SubsystemInterface dtor via rowed 0x001B4E74.
// Layout: SubsystemInterface at +0 plus Snapshot at +0xC plus member at +0xB0 plus count. Evidence: unlock packet EH prolog plus singleton clear plus unblocks deleting dtor 0x003A398B; next Rva003A4322 dtor shares UAE pattern.
class Xfer;

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"


// SubsystemInterface's primary table in retail slot order (subsystem_bfme2
// shim): init is slot 1, reset slot 9 and update slot 10.
class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	virtual void init() = 0;
	virtual bool loadIniFilesFromLegend();
	virtual void postProcessLoad();
	virtual bool vslot04(int);
	virtual bool vslot05();
	virtual int vslot06();
	virtual void vslot07(int);
	virtual void vslot08();
	virtual void reset() = 0;
	virtual void update() = 0;
private:
	char m_pad04[8];
};

class Rva0039F56E
{
public:
	~Rva0039F56E();
};

class TeamFactory : public SubsystemInterface, public Snapshot
{
public:
	virtual ~TeamFactory();
	virtual void init();
	virtual void reset();
	virtual void update();
	void clear();
protected:
	// Snapshot slots of TeamFactoryCtor.cpp's table, declared so this TU's
	// ??_7TeamFactory@@6BSnapshot@@@ is the same four-slot table.
	virtual void loadPostProcess();
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
private:
	char m_pad10[0xB0 - 0x10];
	Rva0039F56E m_b0;
	char m_padB1[0xBC - 0xB1];
	unsigned int m_uniqueTeamPrototypeID;	// +0xBC
	unsigned int m_uniqueTeamID;			// +0xC0
};

extern class TeamFactory *TheTeamFactory;

TeamFactory::~TeamFactory()
{
	clear();
	TheTeamFactory = 0;
}

// Primary table 0x00C1AE2C: slot 1 (init) is 0x003A3899, a tail jump to
// clear; slot 9 (reset) is 0x003A389E, which zeroes +0xBC and +0xC0 before
// the same tail jump; slot 10 (update) is the shared empty RET 0x000B3FD0.
// Zero Hour's Team.cpp has the same three bodies, resetting the unique
// prototype id before the unique team id.
void TeamFactory::init()
{
	clear();
}

void TeamFactory::reset()
{
	m_uniqueTeamPrototypeID = 0;
	m_uniqueTeamID = 0;
	clear();
}

void TeamFactory::update()
{
}
