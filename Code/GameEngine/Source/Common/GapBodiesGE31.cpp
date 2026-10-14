// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
// Small bodies from .text gaps no Ghidra function covers (thirty-first
// batch; see GapBodiesGE01.cpp). Each begins after its neighbour's padding or
// ret and ends in its own ret. Retail bytes establish every shape; owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches. Callees and globals use the ledger's
// existing spellings, private statics reached through a friend view.

// --- 0x00072882 (16B): RefCountClass's inline constructor (vtable 0x00BC650C,
// one reference); 0x000728B6 (16B): a class deriving from it (vtable
// 0x00BC6514), the base's vtable store folded away.
// Match donor refcount.h and the existing consumer declarations: Delete_This
// is slot zero, followed by the protected destructor. Keep the constructor
// inline so byte-identical consumer copies remain interchangeable COMDATs;
// leave Delete_This to its existing providers rather than emitting a helper.
class RefCountClass
{
public:
	RefCountClass() : NumRefs(1) {}
	virtual void Delete_This();
protected:
	virtual ~RefCountClass() {}
private:
	int NumRefs;
};

class Rva000728B6 : public RefCountClass
{
public:
	Rva000728B6();
	virtual ~Rva000728B6() {}
};

Rva000728B6::Rva000728B6()
{
}

// --- 0x000752D5 (12B): CPUDetectClass::TotalPhysicalMemory.
class Rva000752D5;

class CPUDetectClass
{
	friend class Rva000752D5;
	static unsigned __int64 TotalPhysicalMemory;
};

class Rva000752D5
{
public:
	static unsigned __int64 rva000752D5();
};

unsigned __int64 Rva000752D5::rva000752D5()
{
	return CPUDetectClass::TotalPhysicalMemory;
}

// --- 0x000752E1 / 0x000852B3 (17B each): float exp / acos through the
// msvcr71 thunks.
extern "C" double __cdecl acos(double x);
extern "C" double __cdecl exp(double x);

float rva000752E1(float x)
{
	return (float)exp(x);
}

float rva000852B3(float x)
{
	return (float)acos(x);
}

// --- 0x00078930 (17B): address of the i-th 0x1C-byte record at +0x110.
struct GapRecord1C
{
	char m_bytes[0x1C];
};

class Rva00078930
{
public:
	GapRecord1C *rva00078930(int i);
private:
	char m_pad00[0x110];
	GapRecord1C m_records[1];								// +0x110
};

GapRecord1C *Rva00078930::rva00078930(int i)
{
	return &m_records[i];
}

// --- 0x0007B275 (10B): WW3D::IsCurrentlyRenderingShadowMap store.
class Rva0007B275;

class WW3D
{
	friend class Rva0007B275;
	static bool IsCurrentlyRenderingShadowMap;
};

class Rva0007B275
{
public:
	static void rva0007B275(bool on);
};

void Rva0007B275::rva0007B275(bool on)
{
	WW3D::IsCurrentlyRenderingShadowMap = on;
}

// --- 0x0007B27F (30B): 1024, 1000.0f, 0.0f.
class Rva0007B27F
{
public:
	Rva0007B27F();
private:
	int m_count;
	float m_range;
	float m_zero;
};

Rva0007B27F::Rva0007B27F() : m_count(0x400), m_range(1000.0f), m_zero(0.0f)
{
}

// --- 0x0007B342 / 0x0007B367 (37B each): componentwise min / max with
// another float pair.
class Rva0007B342
{
public:
	void rva0007B342(const Rva0007B342 &o);
	void rva0007B367(const Rva0007B342 &o);
private:
	float x;
	float y;
};

void Rva0007B342::rva0007B342(const Rva0007B342 &o)
{
	if (x > o.x)
		x = o.x;
	if (y > o.y)
		y = o.y;
}

void Rva0007B342::rva0007B367(const Rva0007B342 &o)
{
	if (o.x > x)
		x = o.x;
	if (o.y > y)
		y = o.y;
}

// --- 0x0007DE26 (67B): four floats scaled, returned by value.
class Rva0007DE26
{
public:
	Rva0007DE26() {}
	Rva0007DE26(float a, float b, float c, float d) : x(a), y(b), z(c), w(d) {}
	Rva0007DE26 rva0007DE26(float s) const;
private:
	float x;
	float y;
	float z;
	float w;
};

Rva0007DE26 Rva0007DE26::rva0007DE26(float s) const
{
	return Rva0007DE26(x * s, y * s, z * s, w * s);
}

// --- 0x0007DF14 (40B): sign of a float as 1, -1 or 0.
float rva0007DF14(float x)
{
	if (x > 0.0f)
		return 1.0f;
	if (x < 0.0f)
		return -1.0f;
	return 0.0f;
}

// --- 0x0007E9DF (13B): a (container, index 0) cursor; 0x0007E9EC (22B):
// its post-increment.
class Rva0007E9DF;

struct GapCursor
{
	GapCursor(const Rva0007E9DF *owner, int index) : m_owner(owner), m_index(index) {}
	GapCursor rva0007E9EC(int);
	const Rva0007E9DF *m_owner;
	int m_index;
};

class Rva0007E9DF
{
public:
	GapCursor rva0007E9DF() const;
};

GapCursor Rva0007E9DF::rva0007E9DF() const
{
	return GapCursor(this, 0);
}

GapCursor GapCursor::rva0007E9EC(int)
{
	GapCursor old = *this;
	++m_index;
	return old;
}

// --- 0x0007EB3C (21B): _STL::operator!= over the rowed operator== 0x0007E394.
struct Rva0007E394Element;

namespace _STL
{
	template <class T1, class T2> struct pair
	{
		T1 first;
		T2 second;
	};
	template <class T1, class T2> bool operator==(const pair<T1, T2> &a, const pair<T1, T2> &b);
	template <class T1, class T2> inline bool operator!=(const pair<T1, T2> &a, const pair<T1, T2> &b)
	{
		return !(a == b);
	}
}

template bool _STL::operator!=(const _STL::pair<const unsigned int, Rva0007E394Element *> &, const _STL::pair<const unsigned int, Rva0007E394Element *> &);

// --- 0x000824E3 / 0x000824EE (11B each), 0x00058AD3 (11B): owners clearing a
// leading vector through its rowed erase (0x000819EC / 0x00239EA5); retail
// keeps separate copies, so each owner is its own view.
struct TreeHintRef00217D4C;
struct OpaqueRefElement4;

namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> > class vector
	{
	public:
		T *erase(T *first, T *last);
		void clear() { erase(m_start, m_finish); }
	private:
		T *m_start;
		T *m_finish;
		T *m_endOfStorage;
	};
}

class Rva000824E3
{
public:
	void rva000824E3();
	void rva000824EE();
private:
	_STL::vector<TreeHintRef00217D4C> m_hints;
};

void Rva000824E3::rva000824E3()
{
	m_hints.clear();
}

void Rva000824E3::rva000824EE()
{
	m_hints.clear();
}

class Rva00058AD3
{
public:
	void rva00058AD3();
private:
	_STL::vector<OpaqueRefElement4> m_refs;
};

void Rva00058AD3::rva00058AD3()
{
	m_refs.clear();
}

// --- 0x00085265 (17B): float at +0xB0; 0x00085276 (15B): store a word to
// VA 0x00DFF490 unless it is -1.
class Rva00085265
{
public:
	void rva00085265(float value);
private:
	char m_pad00[0xB0];
	float m_B0;
};

void Rva00085265::rva00085265(float value)
{
	m_B0 = value;
}

extern int g_00DFF490;

void rva00085276(int value)
{
	if (value != -1)
		g_00DFF490 = value;
}

// --- 0x0008552B (16B): copy three words in.
struct GapWords3
{
	int a;
	int b;
	int c;
};

class Rva0008552B
{
public:
	void rva0008552B(const GapWords3 &value);
private:
	GapWords3 m_value;
};

void Rva0008552B::rva0008552B(const GapWords3 &value)
{
	m_value = value;
}

// --- 0x0008557F / 0x00085599 (26B each): fade parameter setters (restart
// the fade, store frames and direction) of ScreenBWFilter's public statics
// and of the 0x00DEBFF8..0x00DEC000 triple.
class ScreenBWFilter
{
public:
	static int m_curFadeFrame;
	static int m_fadeFrames;
	static int m_fadeDirection;
};

extern int g_00DEC000;
extern int g_00DEBFFC;
extern int g_00DEBFF8;

void rva0008557F(int frames, int direction)
{
	ScreenBWFilter::m_curFadeFrame = 0;
	ScreenBWFilter::m_fadeFrames = frames;
	ScreenBWFilter::m_fadeDirection = direction;
}

void rva00085599(int frames, int direction)
{
	g_00DEC000 = 0;
	g_00DEBFFC = frames;
	g_00DEBFF8 = direction;
}

// --- 0x000855BA (23B): the larger of two floats.
float rva000855BA(float a, float b)
{
	if (a > b)
		return a;
	return b;
}

// --- 0x00094AA0 / 0x00094AB3 (19B each): the +0x30 / +0x3C float triples
// returned by value.
struct GapTriple3
{
	float x;
	float y;
	float z;
};

class Rva00094AA0
{
public:
	GapTriple3 rva00094AA0() const;
	GapTriple3 rva00094AB3() const;
private:
	char m_pad00[0x30];
	GapTriple3 m_30;
	GapTriple3 m_3C;
};

GapTriple3 Rva00094AA0::rva00094AA0() const
{
	return m_30;
}

GapTriple3 Rva00094AA0::rva00094AB3() const
{
	return m_3C;
}

// --- 0x0008564A (45B): fill a record from another of a different layout,
// returning this: the string at +0x0C from the source's +8 through the
// rowed narrow StringBase<char>::set (0x000366F0), then the three words at
// +0 from the source's +0x0C and the word at +0x10 from its +4.
template <class T> class StringBase
{
public:
	void set(const StringBase &other);
private:
	T *m_data;
};

struct GapWords3B
{
	int w[3];
};

struct Rva0008564ASource
{
	int m_00;
	int m_04;
	StringBase<char> m_08;
	GapWords3B m_0C;
};

class Rva0008564A
{
public:
	Rva0008564A &rva0008564A(const Rva0008564ASource &source);
private:
	GapWords3B m_00;
	StringBase<char> m_0C;
	int m_10;
};

Rva0008564A &Rva0008564A::rva0008564A(const Rva0008564ASource &source)
{
	m_0C.set(source.m_08);
	m_00 = source.m_0C;
	m_10 = source.m_04;
	return *this;
}

// ---------------------------------------------------------------------------
// Unreferenced leaves whose skeletons match rowed twins (twins.tsv leads);
// each is verified on its own bytes. Owners are address-derived views.

class AsciiString;
class RenderObjClass;

// 0x0005CE73 (11B): forward a key to the rowed Rva00056CF8::rva0005B633
// (0x0005B633) of the member at +0x1B8, a tail jump.
class Rva00056CF8
{
public:
	unsigned int rva0005B633(const AsciiString &key);
};

class Rva0005CE73
{
public:
	unsigned int rva0005CE73(const AsciiString &key);
private:
	char m_pad[0x1B8];
	Rva00056CF8 m_1B8;
};

unsigned int Rva0005CE73::rva0005CE73(const AsciiString &key)
{
	return m_1B8.rva0005B633(key);
}

// 0x0006F23F (11B): remove a render object from the RefMultiListClass at
// +0x114 (rowed Remove 0x0006EF4E), a tail jump.
template <class T> class RefMultiListClass
{
public:
	bool Remove(T *obj);
};

class Rva0006F23F
{
public:
	bool rva0006F23F(RenderObjClass *obj);
private:
	char m_pad[0x114];
	RefMultiListClass<RenderObjClass> m_114;
};

bool Rva0006F23F::rva0006F23F(RenderObjClass *obj)
{
	return m_114.Remove(obj);
}

// 0x0007E0CE / 0x0007E0F8 (11B each): addresses of dword slots in the
// arrays at +0x50 and +0x44; 0x0007E0E2 (8B): the rowed
// RiverArea::getTextureName (0x0030BBA9) of the pointer at +0x40, a tail
// jump.
class RiverArea
{
public:
	void *getTextureName(int index);
};

class Rva0007E0CE
{
public:
	void *rva0007E0CE(int index);
	void *rva0007E0E2(int index);
	void *rva0007E0F8(int index);
private:
	char m_pad[0x40];
	RiverArea *m_40;
	int m_44[3];
	int m_50[4];
};

void *Rva0007E0CE::rva0007E0CE(int index)
{
	return &m_50[index];
}

void *Rva0007E0CE::rva0007E0E2(int index)
{
	return m_40->getTextureName(index);
}

void *Rva0007E0CE::rva0007E0F8(int index)
{
	return &m_44[index];
}

// 0x0004CAA7 (10B) / 0x0007DEBE (10B): static setters of the byte at
// VA 0x00DB5F7D and of bfmeCameraProjectionOverride (VA 0x00DEDA05).
extern unsigned char g_Va00DB5F7D;
extern bool bfmeCameraProjectionOverride;

void rva0004CAA7(unsigned char value)
{
	g_Va00DB5F7D = value;
}

void rva0007DEBE(bool value)
{
	bfmeCameraProjectionOverride = value;
}

// 0x00063343 (10B): set the flag at +9.
class Rva00063343
{
public:
	void rva00063343(bool value);
private:
	char m_pad[9];
	bool m_09;
};

void Rva00063343::rva00063343(bool value)
{
	m_09 = value;
}

// 0x0007FAAA (9B): address of a character at an offset from the buffer
// pointer at +0.
class Rva0007FAAA
{
public:
	const char *rva0007FAAA(unsigned int offset) const;
private:
	const char *m_00;
};

const char *Rva0007FAAA::rva0007FAAA(unsigned int offset) const
{
	return m_00 + offset;
}

// 0x00054F32 (9B): run the rowed Rva0005333FHolder::rva0005333F
// (0x0005333F) on an element in place, a tail jump (_Destroy's shape).
class Rva0005333FHolder
{
public:
	void rva0005333F();
};

void rva00054F32(Rva0005333FHolder *p)
{
	p->rva0005333F();
}
