// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ?rva000835D0@RenderableRiverArea@@QAEXXZ, retail 0x000835D0..0x00083780
// (432 bytes, EH, RET0). Builds the river's FX parameter list: the four
// texture parameters (RiverTexture/NoiseTexture/OpacityTexture/
// SparklesTexture, type 1, path from the owner's AsciiString texture slots
// through RiverArea::getTextureName 0x0030BBA9 and the inline str()), then
// Opacity (type 5: three zeros and owner +0x5C), UVScrollPerSecond (type 3:
// the +0x0C object's +0x28 twice) and IsAdditiveBlended (type 7: its +0x2C
// byte), each added through the rowed find-or-add 0x00082EB8. It then
// refreshes the +0x54 FXShaderSetup (UpdateParameterList 0x0015265E) or
// creates it from RiverWater.fx/Default (0x00152C47, assigned through
// 0x00072A94, temporary released through RefCountClass::Release_Ref), and
// clears +0x58. Record and list spellings follow the matched sibling
// SimpleStreakRendererClass::Init (simplestreakrender.cpp); the method name
// stays address-derived (identity of the owning method unproven).
#include "ascii_string.h"
#include <vector>

struct BfmeAssignRecord36
{
	BfmeAssignRecord36(const char *, int);
	char m_prefix[28];
	int m_int;
	char m_tail[4];
};

class Rva00151288
{
public:
	void rva00151288(const char *path);
};

struct Rva0007BB16Record
{
	Rva0007BB16Record(const char *name, int type) : m_record(name, type) {}
	~Rva0007BB16Record();
	void setPath(const char *path) { ((Rva00151288 *)this)->rva00151288(path); }
	float *values() { return (float *)&m_record.m_prefix[12]; }
	BfmeAssignRecord36 m_record;
};

namespace _STL {
template <> vector<Rva0007BB16Record>::~vector();
}

struct Rva00082EB8Rec;
class Rva00082EB8 : public _STL::vector<Rva0007BB16Record>
{
public:
	void rva00082EB8(const Rva00082EB8Rec &);
	void add(const Rva0007BB16Record &rec) { rva00082EB8(*(const Rva00082EB8Rec *)&rec); }
};

class Rva00072A94
{
public:
	Rva00072A94 &operator=(const Rva00072A94 &);
};

class FXShaderSetup
{
public:
	virtual void Delete_This();
	void Release_Ref()
	{
		--NumRefs;
		if (NumRefs == 0)
			Delete_This();
	}
	bool UpdateParameterList(const _STL::vector<Rva0007BB16Record> &recs);
private:
	int NumRefs;
};

template <class T> class RefCountPtr
{
public:
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	operator const Rva00072A94 &() const { return *(const Rva00072A94 *)this; }
private:
	T *m_ptr;
};

RefCountPtr<FXShaderSetup> Rva00152C47_CreateFXShaderSetup(const char *, const char *,
	const _STL::vector<Rva0007BB16Record> *, int);

class Rva00082EF5Base8View
{
public:
	char m_pad00[0x28];
	float m_28;
	unsigned char m_2c;
};

class RiverArea
{
public:
	char m_pad00[0x5c];
	float m_5c;
	void *getTextureName(int index);
};

class RenderableRiverArea
{
public:
	void rva000835D0();
private:
	char m_pad00[0x0c];
	Rva00082EF5Base8View *m_fx;		// +0x0C
	char m_pad10[0x40 - 0x10];
	RiverArea *m_owner;	// +0x40
	char m_pad44[0x54 - 0x44];
	FXShaderSetup *m_54;			// +0x54
	unsigned char m_58;			// +0x58
};

static const char kRiverNames[4][32] =
{
	"RiverTexture",
	"NoiseTexture",
	"OpacityTexture",
	"SparklesTexture"
};

void RenderableRiverArea::rva000835D0()
{
	Rva00082EB8 records;
	for (int i = 0; i < 4; ++i)
	{
		Rva0007BB16Record rec(kRiverNames[i], 1);
		rec.setPath(((const AsciiString *)m_owner->getTextureName(i))->str());
		records.add(rec);
	}
	{
		Rva0007BB16Record rec("Opacity", 5);
		float *v = rec.values();
		v[0] = v[1] = v[2] = 0.0f;
		v[3] = m_owner->m_5c;
		records.add(rec);
	}
	{
		Rva0007BB16Record rec("UVScrollPerSecond", 3);
		float *v = rec.values();
		v[0] = m_fx->m_28;
		v[1] = m_fx->m_28;
		records.add(rec);
	}
	{
		Rva0007BB16Record rec("IsAdditiveBlended", 7);
		rec.m_record.m_tail[0] = m_fx->m_2c;
		records.add(rec);
	}
	if (m_54 != 0)
		m_54->UpdateParameterList(records);
	else
		*(Rva00072A94 *)&m_54 = Rva00152C47_CreateFXShaderSetup("RiverWater.fx", "Default", &records, 4);
	m_58 = 0;
}
