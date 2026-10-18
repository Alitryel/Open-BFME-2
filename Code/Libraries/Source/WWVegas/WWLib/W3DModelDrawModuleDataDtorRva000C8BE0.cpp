// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /GX /MD /DNDEBUG /Ireference/shims/moduledata
// ??1W3DModelDrawModuleData@@UAE@XZ @0x000C8BE0 292B
// Banked attempt reverse/attempts/0x000c8be0.cpp, re-verified exact against the current ledger
// (its callees have since been rowed or pinned); landed unchanged by the
// banked-attempt sweep. Identity and evidence: see reverse/re_attempts.log.
//
// ??1W3DModelDrawModuleData@@UAE@XZ, retail 0x000C8BE0, 292 bytes (Ghidra FUN_004c8be0).
// W3DModelDraw ModuleData base dtor: reinstalls vtable 0xBCADE8, tears down
// the +0x160 array via ehvec 0x629110, 7 vectors, 9 strings via folded
// 0x36410, record 0x79554, then restores Snapshot base 0xBBB554.
// Anchors: 3 matched subclass dtors call base pin 0xC8BE0 (Supply 0xCAF30,
// Tank 0xCE764, Truck 0xCB28E) + matched deleting wrapper 0xC8DC3 (slot 0
// of 0xBCADE8, calls 0xC8BE0 + 0x2FD60). Primary guide: clean BFME1
// W3DModelDrawModuleDataDestructorThunk.cpp (empty dtor shape, /DNDEBUG
// /MD /EHsc, member-then-base ordering). Ghidra 292B boundary verified:
// C9 C3 at 0xC8D03, next FUN_004c8d04 (overflow 191B) at 0xC8D04, no overlap
// with writer-12 C8EEF (599B at 0xC8EEF). Seat-51 r23 596B funclet-conflated
// extent NOT used. No fake empty provider (DeletingDtors scaffold untouched).
// 51r24 recipe unavailable (no r24 file, only through r23).

#include "Common/Snapshot.h"

#include "ascii_string.h"

// Rowed providers (declare-only, resolve to ledger rows, no definitions here).
// Empty allocator tag: every vector member's default construction calls the
// one ICF-folded empty _Vector_base ctor at 0x00211E58 with a reused
// one-byte allocator temporary ([ebp-0xD] in retail).
struct Rva00211E58Alloc
{
	Rva00211E58Alloc() {}
};

// The 12-byte start/finish/end triple every vector member shares; its
// out-of-line ctor is that folded empty _Vector_base ctor.
struct Rva00211E58VectorBase
{
	void *m_start;
	void *m_finish;
	void *m_end;
	Rva00211E58VectorBase(const Rva00211E58Alloc &alloc) throw();
};
struct Rva000C0495 : Rva00211E58VectorBase
{
	Rva000C0495(const Rva00211E58Alloc &alloc = Rva00211E58Alloc()) : Rva00211E58VectorBase(alloc) {}
	~Rva000C0495();
};

class BfmeNarrowRecord00079C23 { public: BfmeNarrowRecord00079C23(); };
struct Rva00079554Record
{
	unsigned char m_pad[0x2C];
	// Construction is the rowed ??0BfmeNarrowRecord00079C23, reached by a qualified call.
	__declspec(dllimport) __forceinline Rva00079554Record() { ((BfmeNarrowRecord00079C23 *)this)->BfmeNarrowRecord00079C23::BfmeNarrowRecord00079C23(); }
	~Rva00079554Record();
};

// Opaque 0x4C bulk-zero member (rowed ctor 0x00042526, no destructor).
class Rva0042526Member
{
public:
	Rva0042526Member() throw();
private:
	unsigned char m_bytes[0x4C];
};

// 248-byte record pushed once into the +0x24 vector (rowed ctor 0x000C6A4D,
// dtor 0x000C6D44); only its leading AsciiString is touched here.
struct BfmePod248
{
	AsciiString m_s00;
	unsigned char m_rest[0xF8 - 4];
	BfmePod248();
	~BfmePod248();
};

// Unrowed +0x08 vector (Ghidra 63B FUN_004c7720) and +0x160 array element
// (0x14 bytes, ehvec 0x629110 with element dtor). Declared here for
// measurement; bodies are placeholders to be replaced by genuine
// RvaVectorDtorFamily-style specialization (Destroy 0xC4DEF rowed) and
// honest element identity. No donor identity claimed for these two.
// Template vector placeholders (12B each) with declared dtors so the empty
// dtor emits calls + EH states in retail order; each must resolve to its
// rowed instantiation (0xC68C2/0xC1C6A/0x2CC70/0xC8B83/0xC8216) in the final
// version via genuine element types -- this measurement TU uses opaque
// wrappers to prove offsets/states without claiming element identity.
struct Rva000C68C2Wrap : Rva00211E58VectorBase
{
	Rva000C68C2Wrap(const Rva00211E58Alloc &alloc = Rva00211E58Alloc()) : Rva00211E58VectorBase(alloc) {}
	void *erase(void *first, void *last);
	void *begin() { return m_start; }
	void *end() { return m_finish; }
	void clear() { erase(begin(), end()); }
	~Rva000C68C2Wrap();
};

struct Rva000C1C6AWrap : Rva00211E58VectorBase
{
	Rva000C1C6AWrap(const Rva00211E58Alloc &alloc = Rva00211E58Alloc()) : Rva00211E58VectorBase(alloc) {}
	void *erase(void *first, void *last);
	void *begin() { return m_start; }
	void *end() { return m_finish; }
	void clear() { erase(begin(), end()); }
	~Rva000C1C6AWrap();
};

struct Rva0002CC70Wrap : Rva00211E58VectorBase
{
	Rva0002CC70Wrap(const Rva00211E58Alloc &alloc = Rva00211E58Alloc()) : Rva00211E58VectorBase(alloc) {}
	~Rva0002CC70Wrap();
};

struct Rva000C8B83Wrap : Rva00211E58VectorBase
{
	Rva000C8B83Wrap(const Rva00211E58Alloc &alloc = Rva00211E58Alloc()) : Rva00211E58VectorBase(alloc) {}
	void push_back(const struct BfmePod248 &value);
	~Rva000C8B83Wrap();
};

struct Rva000C8216Wrap : Rva00211E58VectorBase
{
	Rva000C8216Wrap(const Rva00211E58Alloc &alloc = Rva00211E58Alloc()) : Rva00211E58VectorBase(alloc) {}
	~Rva000C8216Wrap();
};

struct Rva000C7720Vec : Rva00211E58VectorBase
{
	Rva000C7720Vec(const Rva00211E58Alloc &alloc = Rva00211E58Alloc()) : Rva00211E58VectorBase(alloc) {}
	~Rva000C7720Vec();
};

struct W3DModelDrawArrayElement
{
	unsigned char m_pad[0x14];
	W3DModelDrawArrayElement();
	~W3DModelDrawArrayElement();
};

// Measurement note: Rva000C7720Vec and W3DModelDrawArrayElement dtors are
// intentionally left undefined here so the containing dtor emits calls +
// EH states for +0x08/+0x160 without intra-TU folding; each resolves
// through its genuine provider in the final version (C7720 via
// RvaVectorDtorFamily-style specialization on rowed Destroy 0xC4DEF;
// array element via honest identity, never a fake empty). No donor
// identity is claimed for these two.

// Full layout from retail byte decode (capstone) + rowed callee identities.
// Declaration order is increasing offset so the empty dtor tears down in
// reverse (retail states 0x11..0): +0x160 array, +0x11C vec, 4 strings
// +0x118..+0x10C, +0x8C record, +0x7C/+0x70 vecs, 4 strings +0x48..+0x3C,
// +0x30/+0x24/+0x18 vecs, +0x14 string, +0x08 vec. Scalar runs are padding;
// only member offsets matter for the dtor. Vector placeholders are 12-byte
// start/finish/end triples; each must resolve to its rowed dtor
// (0xC0495/0xC68C2/0xC1C6A/0x2CC70/0xC8B83/0xC8216/0xC7720) in the final
// version -- this measurement TU uses void triples to prove the shape.
class W3DModelDrawModuleData : public Snapshot
{
public:
	W3DModelDrawModuleData();
	virtual ~W3DModelDrawModuleData();

private:
	unsigned char m_pad04[4]; // +0x04..+0x07 (Snapshot is vptr-only)
	Rva000C7720Vec m_08; // +0x08
	AsciiString m_14; // +0x14
	Rva000C8216Wrap m_18; // +0x18 vector via rowed 0xC8216 shape
	Rva000C8B83Wrap m_24; // +0x24 vector<BfmePod248> via rowed 0xC8B83 shape
	Rva0002CC70Wrap m_30; // +0x30 vector via rowed 0x2CC70 shape
	AsciiString m_3C; // +0x3C
	AsciiString m_40; // +0x40
	AsciiString m_44; // +0x44
	AsciiString m_48; // +0x48
	int m_4C; // +0x4C default state (-1)
	unsigned int m_50; // +0x50
	float m_54; // +0x54
	float m_58; // +0x58
	float m_5C; // +0x5C
	float m_60; // +0x60
	int m_64; // +0x64
	bool m_68; // +0x68
	bool m_69; // +0x69
	bool m_6A; // +0x6A
	bool m_6B; // +0x6B
	bool m_6C; // +0x6C
	unsigned char m_pad6D[3];
	Rva000C1C6AWrap m_70; // +0x70 vector via rowed 0xC1C6A shape
	Rva000C68C2Wrap m_7C; // +0x7C vector via rowed 0xC68C2 shape
	bool m_88; // +0x88
	unsigned char m_pad89[3];
	Rva00079554Record m_8C; // +0x8C record 0x2C
	bool m_B8; // +0xB8
	unsigned char m_padB9[3];
	Rva0042526Member m_BC; // +0xBC opaque 0x4C member
	bool m_108; // +0x108
	unsigned char m_pad109[3];
	AsciiString m_10C; // +0x10C
	AsciiString m_110; // +0x110
	AsciiString m_114; // +0x114
	AsciiString m_118; // +0x118
	Rva000C0495 m_11C; // +0x11C vector via rowed 0xC0495
	bool m_128; // +0x128
	bool m_129; // +0x129
	bool m_12A; // +0x12A
	bool m_12B; // +0x12B
	float m_12C; // +0x12C
	float m_130; // +0x130
	bool m_134; // +0x134
	bool m_135; // +0x135
	bool m_136; // +0x136
	bool m_137; // +0x137
	bool m_138; // +0x138
	bool m_139; // +0x139
	unsigned char m_pad13A[2];
	int m_13C; // +0x13C
	int m_140; // +0x140
	float m_144; // +0x144
	float m_148; // +0x148
	float m_14C; // +0x14C
	unsigned int m_150; // +0x150
	bool m_154; // +0x154
	unsigned char m_pad155[3];
	int m_158; // +0x158
	bool m_15C; // +0x15C
	bool m_15D; // +0x15D
	bool m_15E; // +0x15E
	bool m_15F; // +0x15F
	W3DModelDrawArrayElement m_160[2]; // +0x160 array[2] 0x14 (ehvec 0x629110)
};

// ??1W3DModelDrawModuleData@@UAE@XZ @0xC8BE0
W3DModelDrawModuleData::~W3DModelDrawModuleData()
{
}

// ??0W3DModelDrawModuleData@@QAE@XZ @0x000C8EEF 599B
// Member initialisation in declaration order (EH states 0..0x12 in retail
// order), then the body: recoil constants 2/3/0.4/0.065 (BFME1
// W3DModelDraw.cpp donor semantics), both +0x70/+0x7C vectors cleared, and a
// default "<DefaultEmptyIdleAnimationState>" record pushed into +0x24.
W3DModelDrawModuleData::W3DModelDrawModuleData() :
	m_4C(-1),
	m_64(0),
	m_68(false),
	m_69(false),
	m_6A(false),
	m_6B(true),
	m_6C(false),
	m_88(false),
	m_B8(false),
	m_108(false),
	m_128(false),
	m_129(false),
	m_12A(false),
	m_12B(false),
	m_144(0.0f),
	m_148(0.0f),
	m_14C(1.0f),
	m_150(0),
	m_154(false),
	m_158(-1),
	m_15D(false),
	m_15E(true),
	m_15F(false)
{
	m_50 = 0;
	m_54 = 2.0f;
	m_58 = 3.0f;
	m_5C = 0.4f;
	m_60 = 0.065f;

	m_70.clear();
	m_7C.clear();

	m_12C = 0.0f;
	m_130 = 0.0f;
	m_134 = false;
	m_135 = false;
	m_136 = false;
	m_137 = false;
	m_138 = false;

	BfmePod248 temp;
	temp.m_s00 = "<DefaultEmptyIdleAnimationState>";
	m_24.push_back(temp);

	m_139 = false;
	m_13C = m_140 = 0x60;
	m_15C = false;
}
