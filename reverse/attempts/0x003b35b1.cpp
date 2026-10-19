// ??1Script@@MAE@XZ
// partial score=0.966 date=2026-10-19
// ??1Rva003B35B1@@UAE@XZ
// partial score=0.9661 date=2026-10-18
// ??1Rva003B35B1@@UAE@XZ
// partial score=0.95 date=2026-10-13
// ??1Rva003B35B1@@UAE@XZ
// partial score=0.95 date=2026-10-01
// ??1Rva003B35B1@@UAE@XZ
// cl: /O1 /MD /EHsc
// ??1Rva003B35B1@@UAE@XZ retail 0x003B35B1 177B. Vtable 0x0081F424, base
// Snapshot (vtable 0x007BB554 restored last). Retail's unwind map: base at
// +0, narrow strings at +4/+8/+0xC, a 16-byte record with a string at +0xC
// placed at +0x10 (dtor folds with GeometryRecord's 0x0004F82B), string at
// +0x44. Owned pointers at +0x30 and +0x34[2] are released through slot 0
// with flag 0, then operator delete (also for null).
// NEAR MISS (2026-10-19 seat5): `::delete` through a real virtual dtor is the
// honest spelling of the slot-0(0)+operator-delete shape (same bytes as the
// old v0(0) model). Two 177B families each leave 10 differing bytes:
//  (a) THIS BODY: pp declared/initialised before the m_30 release. The loop
//      is byte-exact to retail (memory counter [ebp-0x10], unmerged zero,
//      late add edi,4); only `lea edi,[esi+0x34]` is hoisted into the first
//      release block (before its je) instead of after its pop ecx.
//  (b) pp declared after the release and read as `*pp++`: lea placed right
//      but add edi,4 hoisted before the null test.
// Every other shape (index form, ++pp as its own statement, while/do/for,
// countdown, inline helpers, accessors, references, braces, decl position,
// 13 flag sets) emits 166B: ebx counter + xor eax/cmp ecx,eax merged zero
// in both releases. Handoff: reverse/attempt_support/script-dtor-loop-shapes-20261019.md
template <typename T> class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

class Snapshot
{
public:
	virtual ~Snapshot() {}
	virtual void crc();
	virtual void loadPostProcess();
	virtual void xfer();
};

class Rva003B35B1Owned
{
public:
	virtual ~Rva003B35B1Owned();
};

struct Rva003B35B1Record
{
	int m_00;
	int m_04;
	int m_08;
	StringBase<char> m_0C;
};

class Rva003B35B1 : public Snapshot
{
public:
	virtual ~Rva003B35B1();
private:
	StringBase<char> m_04;
	StringBase<char> m_08;
	StringBase<char> m_0C;
	Rva003B35B1Record m_10;
	char m_pad20[0x10];
	Rva003B35B1Owned *m_30;
	Rva003B35B1Owned *m_34[2];
	char m_pad3C[0x08];
	StringBase<char> m_44;
};

Rva003B35B1::~Rva003B35B1()
{
	Rva003B35B1Owned **pp = m_34;
	::delete m_30;
	for (int i = 0; i < 2; ++i)
	{
		::delete *pp;
		++pp;
	}
}
