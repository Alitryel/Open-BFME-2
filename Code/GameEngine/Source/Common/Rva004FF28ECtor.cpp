// cl: /O1 /G7 /arch:SSE /Oy- /DNDEBUG /MD /EHsc /ICode/Libraries/Include/Lib
//
// 0x004FF207 (135B): forwards record +0x28 to TheLivingWorldManager->+0x268's
// rowed 0x003EE980, constructs a 3D point from record +0x48, and dispatches
// TheLivingWorld slot 39 (+0x9C) with inline getters for +0x50/+0x54 and
// rowed movement duration 0x002BEDCA (WB 0x1314300 compiler-temp order).
// 0x004FF28E (50B): five-int init storing vtable 0xC63B34 plus +0x28,
// forwarding three ints to the rowed 0x4FBC4D ctor and one int to the
// 0x20E449 copy ctor.
// Returns this as int. Identities unproven.

#include "Coord3D.h"
#include "Coord2D.h"

struct Rva004FF207Point : Coord3D
{
	Rva004FF207Point(float xx, float yy) { x = xx; y = yy; z = 0.0f; }
	Rva004FF207Point(const Rva004FF207Point &v) { x = v.x; y = v.y; z = v.z; }
};
struct Rva004FF207Pair : Coord2D
{
	Rva004FF207Point point() const { return Rva004FF207Point(x, y); }
};

struct Rva004FF207Record {
	char unknown00[0x48];
	Rva004FF207Pair point;
	Coord2D values;
};
class Rva003EE980 { public: void rva003EE980(int); };
class LivingWorldManager {
public:
	char unknown00[0x268];
	Rva003EE980 *member268;
};
extern LivingWorldManager *TheLivingWorldManager;
class Rva002D3627Host {
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void slot12();
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void slot32();
	virtual void slot33();
	virtual void slot34();
	virtual void slot35();
	virtual void slot36();
	virtual void slot37();
	virtual void slot38();
	virtual void slot39(const Coord3D *, float, float, int);
	int rva002BEDCA(const Coord3D *, float);
};
class LivingWorld;
extern LivingWorld *TheLivingWorld;
class Rva004FF207 {
public:
	void rva004FF207();
	float get50() const { return record->values.x; }
	float get54() const { return record->values.y; }
private:
	char unknown00[0x28];
	Rva004FF207Record *record;
};

void Rva004FF207::rva004FF207()
{
	TheLivingWorldManager->member268->rva003EE980(reinterpret_cast<int>(record));
	Rva004FF207Point point = record->point.point();
	((Rva002D3627Host *)TheLivingWorld)->slot39(&point, get50(), get54(),
		((Rva002D3627Host *)TheLivingWorld)->rva002BEDCA(&point, get54()));
}

extern "C" const void *const vtbl_00C63B34[];  // ??_7Rva004FF2C0@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C63B34=??_7Rva004FF2C0@@6B@")

// 0x004FBC4D is the rowed Rva004FBCBE constructor and 0x0020E449 the rowed
// Rva0020E449 copy constructor; both are called in place on raw storage.
class UnicodeString;

class Rva004FBCBE
{
public:
	Rva004FBCBE(const UnicodeString &a, const UnicodeString &b, int c);
};

class Rva0020E449
{
public:
	Rva0020E449(const Rva0020E449 &other);
};

class Rva004FF28EOwner
{
public:
	int rva004FF28E(int a0, int a1, int a2, int a3, int a4);

private:
	int m_vptr;		// +0x00 = 0xC63B34
	char m_pad04[0x24];	// +0x04..0x27
	int m_28;		// +0x28 = a0
	char m_2C[16];		// +0x2C copy target for 0x20E449
};

int Rva004FF28EOwner::rva004FF28E(int a0, int a1, int a2, int a3, int a4)
{
	((Rva004FBCBE *)this)->Rva004FBCBE::Rva004FBCBE(
		*(const UnicodeString *)a2, *(const UnicodeString *)a3, a4);
	*(int *)this = ((unsigned int)vtbl_00C63B34);
	m_28 = a0;
	((Rva0020E449 *)m_2C)->Rva0020E449::Rva0020E449(*(const Rva0020E449 *)a1);
	return (int)this;
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0020E449 reads ??0Rva0020E449@@QAE@ABV0@@Z
#pragma comment(linker, "/alternatename:?rva0020E449Copy@Rva0020E449Caller@@QAEXH@Z=??0Rva0020E449@@QAE@ABV0@@Z")
//   0x004FBC4D reads ??0Rva004FBCBE@@QAE@ABVUnicodeString@@0H@Z
#pragma comment(linker, "/alternatename:?rva004FBC4D@Rva004FBC4D@@QAEXHHH@Z=??0Rva004FBCBE@@QAE@ABVUnicodeString@@0H@Z")
