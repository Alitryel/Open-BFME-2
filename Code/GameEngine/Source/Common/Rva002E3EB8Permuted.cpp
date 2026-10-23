// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
//
// ??0PolygonTrigger@@QAE@H@Z, retail 0x002e3eb8, 166 bytes. Banked partial (score 0.9) closed by tools/permute.py;
// the body is the banked one up to statement/operand order and local types.
// Native constructor 0x2E3EB8..0x2E3F5E; WB 0xAB9AE0.
// Native secondary interface has one pure virtual at C1C780 and trivial destruction;
// native derived entry C04C78 points to this-38 thunk002E37C3 ->002E37B1.
// Primary vtable C04C7C has13 entries; this provisional base declaration is incomplete.
// Native 330C50..330CC2: primary vptr +0, vbptr +4, container +8,
// flag +34, vtordisp +38, seven-slot virtual interface +3C.
// The vbtable contains {-4, 0x38}; interface thunks 2E3E80..2E3EB0
// each subtract the vtordisp before dispatching the corresponding member.
#include "../../../Libraries/Include/Lib/Region2D.h"
struct Rva0030B72CPoint {
 Rva0030B72CPoint() {}
 __forceinline Rva0030B72CPoint(const Rva0030B72CPoint &p):x(p.x),y(p.y) {}
 float x,y;
};

class Rva00330C50Interface
{
public:
	~Rva00330C50Interface() {}
	virtual int slot0() const = 0;
	virtual Rva0030B72CPoint slot1(int index) const = 0;
	virtual int slot2() const = 0;
	virtual Region2D slot3() = 0;
	virtual float slot4() const = 0;
	virtual float slot5() const = 0;
	virtual Rva0030B72CPoint slot6() const = 0;
};

class Rva0030B9DD
{
public:
	Rva0030B9DD(int);
	~Rva0030B9DD();
private:
	char unknown00[0x2C];
};

class Rva00330C50 : public virtual Rva00330C50Interface
{
public:
	Rva00330C50();
	virtual ~Rva00330C50();
	virtual int slot0() const;
	virtual Rva0030B72CPoint slot1(int index) const;
	virtual int slot2() const;
	virtual Region2D slot3();
	virtual float slot4() const;
	virtual float slot5() const;
	virtual Rva0030B72CPoint slot6() const;
private:
	Rva0030B9DD container;
	bool changed;
};


#include <ascii_string.h>
class Rva002E3EB8Base { public: virtual void slot()=0; };
class PolygonTrigger;
class PolygonLink { public: PolygonLink():next(0){} PolygonTrigger* next; };
class PolygonTrigger:public PolygonLink,public Rva00330C50,public Rva002E3EB8Base {
public:
 PolygonTrigger(int);
 virtual ~PolygonTrigger();
 virtual void slot() = 0;
 void rva002E36B7(int);
private:
 AsciiString name;
 int id;
 void* unknown48;
 AsciiString layer;
 char unknown50[12];
 static int s_currentID;
};
typedef char PolygonExtent[sizeof(PolygonTrigger)==100?1:-1];
PolygonTrigger::PolygonTrigger(int n):id(s_currentID++) { rva002E36B7(n); }

// The class's destructor: this unit's constructor row stores the vftable whose slot 0 is the
// deleting destructor at 0x002E424F, and its body calls 0x002E4049, where the destructor row lives.
#pragma comment(linker, "/alternatename:??1PolygonTrigger@@UAE@XZ=??1Rva002E4049@@UAE@XZ")
