// ?slot3@Rva00330C50@@$4PPPPPPPM@GM@AE?AURegion2D@@XZ
// partial score=0.8454545454545455 date=2026-10-14
// cl: /O1 /arch:SSE /G7 /EHsc /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii
//
// ??0Rva0030902E@@QAE@H@Z, retail 0x00308E63 (366 bytes, EH, RET 8: one int
// and the hidden most-derived flag): the constructor of the standing water
// area whose destructor 0x0030902E is rowed in Rva0030902EDtor.cpp; its
// matched callers (StandingWaterAreasDataChunkParser::parse 0x003091B1 and
// two more) bind it through the pin ??0Rva00308E63@@QAE@H_N@Z. Target
// evidence: the rowed bases Rva0053805DBase 0x005380A8 (+0), Rva00330C50
// 0x00330C50 (+0x30) and the listener list 0x00330757 (+0x68) over the shared
// interface 0x00C6EE28 at +0xD8 (behind a vtordisp); tables 0x00C07F80,
// 0x00C07F4C and 0x00C07F30; the int sizes the secondary base's container
// (rowed 0x00330AA6). Defaults: textures "WaterRippleBump.tga" and
// "SkyEnv.tga" (+0x78), "LUTDepthTint.tga" (+0x8C), model
// "WaterCaribbean.w3d" (+0x80), 1.0 at +0xA4, three cleared three-int
// arrays and the +0x9C, +0x88 and +0xD0 flags set. Field meanings are not
// established; names are address-derived.
#include "ascii_string.h"

struct Rva00330C35Record {float x,y;};
struct Region2D {float loX,loY,hiX,hiY;};
struct Rva0030B72CPoint {float x,y;};
class VBase00C6EE28 {
public:
 ~VBase00C6EE28() {}
	virtual int slot0() const = 0;
	virtual Rva00330C35Record *slot1(Rva00330C35Record*,int) = 0;
	virtual int slot2() const = 0;
	virtual Region2D slot3() = 0;
	virtual float slot4() const = 0;
	virtual float slot5() const = 0;
	virtual Rva0030B72CPoint slot6() const = 0;
};

// The base as Rva0053805DBaseCtor.cpp lays it out.
class __declspec(novtable) Rva0007DF07
{
public:
	Rva0007DF07() : count(0) {}
	virtual ~Rva0007DF07();
private:
	unsigned int count;
};

class Rva00330757Member
{
public:
	Rva00330757Member() throw();
	~Rva00330757Member();
private:
	void *m_begin;
	void *m_end;
	void *m_capacity;
	unsigned int m_index;
};

class Rva0053805DBase : public Rva0007DF07, public Rva00330757Member,
	public virtual VBase00C6EE28
{
public:
	Rva0053805DBase();
	virtual ~Rva0053805DBase();
	virtual bool slot1() const;
	virtual void rva0053805D();
	virtual void rva0053806C();
	virtual void rva0053807B();
	virtual void rva0053808A();
	virtual void primary6(int);
private:
	unsigned char m_pad1C[0x30 - 0x1C];
};

class Rva00330C50 : public virtual VBase00C6EE28
{
public:
	Rva00330C50();
	void rva00330AA6(int);
	virtual ~Rva00330C50();
	virtual int slot0() const;
	virtual Rva00330C35Record *slot1(Rva00330C35Record*,int);
	virtual int slot2() const;
	virtual Region2D slot3();
	virtual float slot4() const;
	virtual float slot5() const;
	virtual Rva0030B72CPoint slot6() const;
	virtual void primary1();
	virtual void primary2();
	virtual void primary3();
	virtual void primary4();
	virtual void primary5();
	virtual void primary6(int);
private:
	unsigned char m_pad08[0x38 - 8];
};

class Rva0030902ERef;

class Rva0030902E : public Rva0053805DBase, public Rva00330C50, public Rva00330757Member
{
public:
	Rva0030902E(int count);
	virtual ~Rva0030902E();
	virtual void primary6(int);
private:
	AsciiString m_78[2];			// +0x78
	AsciiString m_80;			// +0x80
	Rva0030902ERef *m_84;			// +0x84
	bool m_88;				// +0x88
	AsciiString m_8C;			// +0x8C
	int m_90;
	int m_94;
	unsigned char *m_98;			// +0x98
	bool m_9C;				// +0x9C
	int m_A0;
	float m_A4;
	int m_A8;
	int m_AC[3];				// +0xAC
	int m_B8[3];				// +0xB8
	int m_C4[3];				// +0xC4
	bool m_D0;				// +0xD0
};

Rva0030902E::Rva0030902E(int count)
{
	rva00330AA6(count);
	m_78[0] = "WaterRippleBump.tga";
	m_78[1] = "SkyEnv.tga";
	m_8C = "LUTDepthTint.tga";
	m_98 = 0;
	m_90 = 0;
	m_94 = 0;
	m_9C = true;
	m_80 = "WaterCaribbean.w3d";
	m_84 = 0;
	m_88 = true;
	m_A0 = 0;
	m_A4 = 1.0f;
	m_A8 = 0;
	for (int i = 0; i < 3; ++i)
	{
		m_AC[i] = 0;
		m_B8[i] = 0;
		m_C4[i] = 0;
	}
	m_D0 = true;
}
