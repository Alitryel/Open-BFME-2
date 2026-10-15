// ??0Rva00359E13@@QAE@XZ
// partial score=0.971553 date=2026-10-15
// ??0Rva00359E13@@QAE@XZ
// partial score=0.97 date=2026-09-30
// ??0Rva00359E13@@QAE@XZ
// partial score=0.97 date=2026-09-30
// cl: /O1 /EHsc /arch:SSE /DNDEBUG /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva00359E13@@QAE@XZ @0x00359E13 122B: ctor with Rva00330757Member base at +4 and list<Coord3D> at +0x14; vptr at +0; floats at +0x18/1c/20/24/28/2c/30/3c and ints at +0x34/38/40 zeroed; callers 0x0024408B; next row TerrainResourceManager name getter.
#include <list>
#include <vector>

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Coord3D { float x, y, z; };
struct BfmeE16 { float x, y, z, w; };

class Rva00330757Member
{
public:
	Rva00330757Member();
private:
	_STL::vector<BfmeE16> m_items;
	int m_flags;
};

class EmptyBase00359E13
{
public:
	EmptyBase00359E13() {}
	~EmptyBase00359E13();
};

class Rva00359E13 : public EmptyBase00359E13, public Rva00330757Member
{
public:
	Rva00359E13();
	virtual void dummy();
private:
	_STL::list<Coord3D> m_list;
	float m_18;
	float m_1c;
	float m_20;
	float m_24;
	float m_28;
	float m_2c;
	float m_30;
	int m_34;
	int m_38;
	float m_3c;
	int m_40;
};

// ??0Rva00359E13@@QAE@XZ present-unmatched
Rva00359E13::Rva00359E13()
{
	m_1c = 0.0f;
	m_20 = 0.0f;
	m_24 = 0.0f;
	m_28 = 0.0f;
	m_2c = 0.0f;
	m_30 = 0.0f;
	_ReadWriteBarrier();
	m_34 = 0;
	m_38 = 0;
	m_40 = 0;
	m_3c = 0.0f;
	m_18 = 0.0f;
}
