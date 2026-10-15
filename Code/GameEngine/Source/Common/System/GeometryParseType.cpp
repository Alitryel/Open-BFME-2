// cl: /O2 /DNDEBUG /MD /GX- /Ob2
// BFME2 adaptation: PC C0EBF0 Geometry -> ABFEE0; full105B.
// Existing BFME1 donor reproduced below. PC scanIndexList is a member;
// retail default construction also sets shape flag +21 to true.
// Open-BFME: GeometryInfo::parseGeometryType, retail 0x00880480.
//
// ThingTemplate registers this callback for both Geometry fields.  The body
// parses through the canonical GeometryNames table, grows GeometryInfo's
// 0x24-byte shape vector at +0x2C, writes the selected type into its first
// element, and tail-calls calcBoundingStuff.
//
// Modeling the real nested Coord3D and string members is material here.  Their
// inline default construction preserves retail's constant/load schedule; a
// flat collection of volatile scalar fields emits the same stores in a
// different order around the saved scan result.

#define BFME_SNAPSHOT_CAPITALIZED_SLOTS
#define BFME_SNAPSHOT_REFERENCE_XFER
#define BFME_SNAPSHOT_NAME_SLOT
class Xfer;

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"

// Native9DBFE0..9DBFF0: three enum names followed by the null sentinel.
// The parser's scanIndexList consumes the table; unrelated scalar defaults
// begin at9DBFF0, establishing the complete16B extent.
extern const char *const GeometryNames[] = { "SPHERE", "CYLINDER", "BOX", 0 };

class INI
{
public:
	const char *getNextToken(const char *separators) throw();
	int scanIndexList(const char *token, const char *const *names) throw();
};

struct BfmeCoord3D
{
	__forceinline BfmeCoord3D() throw() : x(0.0f), y(0.0f), z(0.0f) {}

	float x;
	float y;
	float z;
};

class BfmeAsciiString
{
public:
	__forceinline BfmeAsciiString() throw() : m_data(0) {}

private:
	char *m_data;
};

struct BfmeElem60
{
	__forceinline BfmeElem60() throw()
		: m_type(0), m_height(1.0f), m_majorRadius(1.0f),
		  m_minorRadius(1.0f), m_center(), m_name(), m_enabled(true), m_flag21(true)
	{
	}

	__forceinline BfmeElem60(const BfmeElem60 &other) throw()
	{
		m_type = other.m_type;
		m_height = other.m_height;
		m_majorRadius = other.m_majorRadius;
		m_minorRadius = other.m_minorRadius;
		m_center = other.m_center;
		m_name = other.m_name;
		m_enabled = other.m_enabled;
        m_flag21 = other.m_flag21;
	}

	int m_type;
	float m_height;
	float m_majorRadius;
	float m_minorRadius;
	BfmeCoord3D m_center;
	BfmeAsciiString m_name;
	unsigned char m_enabled;
	unsigned char m_flag21;
    unsigned char m_padding[2];
};

class BfmeVec60
{
public:
	void resize(unsigned int count, BfmeElem60 value) throw();
	void resize(unsigned int count) throw();
	int size() const { return m_end - m_begin; }

	BfmeElem60 *m_begin;
	BfmeElem60 *m_end;
	BfmeElem60 *m_capacity;
};

struct GeometryXferVersion
{
	GeometryXferVersion(unsigned char minimum, unsigned char current) : m_minimum(minimum), m_current(current) {}
	unsigned char m_minimum;
	unsigned char m_current;
};

// Retail string 0x00CE7AA8 "GeometryType" (defined in ConstIntGettersAddr.cpp).
extern const char s_geometryTypeString[];

class Xfer
{
public:
	virtual ~Xfer();
	virtual bool slot01();
	virtual bool slot02();
	virtual bool slot03();
	virtual bool slot04();	// true: nothing to xfer (the body returns at once)
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void xferVersion(GeometryXferVersion *version);
	virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16();
	virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22();
	virtual void slot23();
	virtual void xferCoord3D(BfmeCoord3D *value);
	virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void xferReal(float *value);
	virtual void slot29(); virtual void slot30();
	virtual void xferInt(int *value);
	virtual void slot32(); virtual void slot33(); virtual void slot34();
	virtual void slot35();
	virtual void xferBool(unsigned char *value);
	virtual void xferUser(const char *name, void *value, unsigned int size);
};

class GeometryInfo : public Snapshot
{
public:
	static void parseGeometryType(INI *, void *, void *, const void *);
	virtual void DoXfer(Xfer &xfer);

private:
	unsigned char m_isSmall; // +0x04
	char m_pad05[3];
	int m_08;
	int m_0c;
	float m_boundingCircleRadius; // +0x10
	float m_boundingSphereRadius; // +0x14
	BfmeCoord3D m_center18; // +0x18
	float m_24;
	float m_28;
	BfmeVec60 m_shapes; // +0x2C
	char m_38[12];
	BfmeCoord3D m_44;
	BfmeCoord3D m_50;

public:
private:
	void calcBoundingStuff() throw();
	friend class BfmeAsciiString;
	friend class BfmeCoord3D;
	friend class BfmeElem60;
	friend class BfmeVec60;
	friend class INI;
};

void GeometryInfo::parseGeometryType(INI *ini, void *, void *store, const void *)
{
	int type = ini->scanIndexList(ini->getNextToken(0), GeometryNames);
	GeometryInfo *geometry = (GeometryInfo *)store;
	geometry->m_shapes.resize(1, BfmeElem60());
	geometry->m_shapes.m_begin->m_type = type;
	geometry->calcBoundingStuff();
}

// ?resize@BfmeVec60@@QAEXI@Z @0x006BFE60 63B: the one-argument resize, which
// builds a default BfmeElem60 straight into the by-value argument slot and
// calls the rowed two-argument resize 0x006BFCB0.
void BfmeVec60::resize(unsigned int count) throw()
{
	resize(count, BfmeElem60());
}

// ?DoXfer@GeometryInfo@@UAEXAAVXfer@@@Z retail 0x006C0030..0x006C01B0
// (384 bytes, ret 4): slot 3 of the GeometryInfo snapshot table 0x00BC4E94.
// Target facts: skipped under the light CRC (Xfer slot 4); xfers a
// two-byte version {1, 2} (slot 10), the +0x04 isSmall flag (slot 36), the
// shape count (slot 31) of the 0x24-byte shape vector at +0x2C, resizes it
// through the inline one-argument resize (a default shape built straight
// into the by-value argument of the rowed two-argument resize 0x006BFCB0,
// matching the out-of-line copy 0x006BFE60), then per shape xfers the type
// through slot 37 with the "GeometryType" string 0x00CE7AA8 and size 4,
// height/major/minor radii (slot 28), the offset Coord3D (slot 24) and,
// for version > 1, the enabled byte at +0x20; finally +0x10/+0x14/+0x24/+0x28
// (slot 28) and the Coord3Ds +0x18/+0x44/+0x50 (slot 24).
// Donor carry: Zero Hour Geometry.cpp GeometryInfo::xfer field order
// (type, height, major, minor; then bounding radii); BFME 2's shape vector,
// version byte pair and Coord3D members are target facts from retail. The
// member names past the shape vector are structural, not donor-proven.
void GeometryInfo::DoXfer(Xfer &xfer)
{
	if (xfer.slot04())
		return;

	GeometryXferVersion version(1, 2);
	xfer.xferVersion(&version);
	xfer.xferBool(&m_isSmall);

	int count = m_shapes.size();
	xfer.xferInt(&count);
	m_shapes.resize(count);
	for (int i = 0; i < count; ++i)
	{
		BfmeElem60 *shape = &m_shapes.m_begin[i];
		xfer.xferUser(s_geometryTypeString, &shape->m_type, sizeof(shape->m_type));
		xfer.xferReal(&shape->m_height);
		xfer.xferReal(&shape->m_majorRadius);
		xfer.xferReal(&shape->m_minorRadius);
		xfer.xferCoord3D(&shape->m_center);
		if (version.m_current > 1)
			xfer.xferBool(&shape->m_enabled);
	}

	xfer.xferReal(&m_boundingCircleRadius);
	xfer.xferReal(&m_boundingSphereRadius);
	xfer.xferReal(&m_24);
	xfer.xferReal(&m_28);
	xfer.xferCoord3D(&m_center18);
	xfer.xferCoord3D(&m_44);
	xfer.xferCoord3D(&m_50);
}
