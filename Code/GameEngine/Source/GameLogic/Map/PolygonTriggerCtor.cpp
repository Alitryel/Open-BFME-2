// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// PolygonTrigger::PolygonTrigger(int identifier, int count), retail
// 0x002E3FAB..0x002E4049 (158 B, ret 12 with the hidden most-derived flag).
// WorldBuilder AB9C60 is the constructor and the chunk parser's new(0x64)
// supplies the two int arguments. Layout measured from the constructor and
// its thunks (2E3E80..2E3EB0): primary Rva00330C50 (vptr +0, vbptr +4,
// container +8, flag +34, vtordisp +38) with the virtual interface at +0x3C,
// a secondary polymorphic base at +0x38 whose vptr is stored after the base
// call, and a plain {next} base at +0x3C stored BEFORE it. Declaring the
// next-link base FIRST in the base list is what orders its store ahead of
// the Rva00330C50 call (construction order is declaration order, layout
// puts the data-only base after the polymorphic ones). The rowed
// Rva00330C50 constructor (0x00330C50) and the 0x002E36B7 initialiser are
// declared only; their bodies live in Common/Rva00330C50Ctor.cpp and
// PolygonTrigger.cpp. The names are address-derived; the base roles are
// inferred from bytes.
class Rva00330C50Interface
{
public:
	~Rva00330C50Interface() {}
	virtual void slot0() = 0;
	virtual void slot1() = 0;
	virtual void slot2() = 0;
	virtual void slot3() = 0;
	virtual void slot4() = 0;
	virtual void slot5() = 0;
	virtual void slot6() = 0;
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
	void rva00330AA6(int);
	virtual ~Rva00330C50();
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
private:
	Rva0030B9DD container;
	bool changed;
};

#include "ascii_string.h"
class PolygonTrigger;
class PolygonNext { public: PolygonNext():next(0){} PolygonTrigger *next; };
class PolygonSecondary {
public:
 PolygonSecondary(){}
 virtual PolygonTrigger* secondarySlot()=0;
};
class PolygonTrigger : public PolygonNext, public Rva00330C50, public PolygonSecondary {
public:
 PolygonTrigger(int,int);
 virtual ~PolygonTrigger();
 virtual PolygonTrigger* secondarySlot();
 void rva002E36B7(int);
 AsciiString name;
 int id;
 bool flag48;
 AsciiString layer;
 bool flag50;
 int field54,field58;
};
PolygonTrigger::PolygonTrigger(int identifier,int count):id(identifier)
{ rva002E36B7(count); }
