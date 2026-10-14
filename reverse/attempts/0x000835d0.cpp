// ?rva000835D0@RenderableRiverArea@@QAEXXZ
// partial score=0.856 date=2026-10-14
// ?rva000835D0@RenderableRiverArea@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
//
// RenderableRiverArea FX-parameter rebuild, retail 0x000835D0 (432 B, EH,
// RET0). Builds a 36-byte Rva0007BB16Record vector from the four texture
// names (RiverTexture/NoiseTexture/OpacityTexture/SparklesTexture, each with
// the record's +4 set to 1 and the +8 path set from RiverArea::getTextureName),
// then Opacity (4 floats, last = owner+0x5C), UVScrollPerSecond (two floats
// from the +0x0C object's +0x28) and IsAdditiveBlended (byte from +0x2C);
// finally either refreshes the +0x54 FXShaderSetup through UpdateParameterList
// or creates it from RiverWater.fx/Default, then clears +0x58.
#include <stl/_algobase.h>
#include "ascii_string.h"
#include <vector>

class Rva00151248
{
public:
	void rva00151248();
};

struct Rva0007BB16Record
{
public:
	Rva0007BB16Record(const char *s, int v);
	void rva00151288(const char *path);
	~Rva0007BB16Record();
	AsciiString m_s00;
	int m_04;
	AsciiString m_s08;
	float m_vals[4];
	int m_1c;
	unsigned char m_20;
	char m_pad21[3];
};

class Rva00072A94
{
public:
	void *m_ptr;
	Rva00072A94 &operator=(const Rva00072A94 &rhs);
};

class FXShaderSetup
{
public:
	bool UpdateParameterList(const _STL::vector<Rva0007BB16Record> &recs);
};

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
	Rva00072A94 m_54;			// +0x54
	unsigned char m_58;			// +0x58
};

extern Rva00072A94 Rva00152C47_CreateFXShaderSetup(const char *name, const char *def, const _STL::vector<Rva0007BB16Record> *recs, int n);

static const char kRiverNames[4][32] =
{
	"RiverTexture",
	"NoiseTexture",
	"OpacityTexture",
	"SparklesTexture"
};

void RenderableRiverArea::rva000835D0()
{
	_STL::vector<Rva0007BB16Record> records;
	for (int i = 0; i < 4; ++i)
	{
		Rva0007BB16Record rec(kRiverNames[i], 1);
		void *tex = m_owner->getTextureName(i);
		const char *path = "";
		if (tex != 0)
		{
			void *d = *(void **)tex;
			if (d != 0)
				path = (const char *)d + 8;
		}
		rec.rva00151288(path);
		records.push_back(rec);
	}
	{
		Rva0007BB16Record rec("Opacity", 5);
		rec.m_vals[0] = 0.0f;
		rec.m_vals[1] = 0.0f;
		rec.m_vals[2] = 0.0f;
		rec.m_vals[3] = m_owner->m_5c;
		records.push_back(rec);
	}
	{
		Rva0007BB16Record rec("UVScrollPerSecond", 3);
		rec.m_vals[0] = m_fx->m_28;
		rec.m_vals[1] = m_fx->m_28;
		records.push_back(rec);
	}
	{
		Rva0007BB16Record rec("IsAdditiveBlended", 7);
		rec.m_20 = m_fx->m_2c;
		records.push_back(rec);
	}
	if (m_54.m_ptr != 0)
		((FXShaderSetup *)m_54.m_ptr)->UpdateParameterList(records);
	else
		m_54 = Rva00152C47_CreateFXShaderSetup("RiverWater.fx", "Default", &records, 4);
	m_58 = 0;
}
