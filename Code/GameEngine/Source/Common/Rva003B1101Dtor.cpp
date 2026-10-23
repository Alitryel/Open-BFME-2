// cl: /O1 /EHs /arch:SSE /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
//
// ??1Rva003B1101@@UAE@XZ @0x003B1101 (172B):
// Virtual dtor with vtable 0x00C1ED18, nine members plus virtual base
// Overridable. Members in declaration order: StringBase at +0x10, free-ptr
// at +0x24, OpaqueRef holders at +0x34/+0x38, StringBase at +0x3c/+0x40/+0x5c,
// Rva00360D26Member at +0x60/+0x78. All member dtors inline except the two
// Rva members and the base, matching the nine rowed/pinned callees.
// Caller 0x003B152A is the ??_G. Evidence: unlock lane, all callees rowed.
class Overridable {
public:
	virtual ~Overridable();
};
class Rva00360D26Member {
public:
	~Rva00360D26Member();
private:
	unsigned m_unknown;
};
class OpaqueRefCounted {
public:
	void Release_Ref();
};
extern "C" void __cdecl free(void *);
template <typename T> class StringBase {
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

typedef StringBase<char> StringBaseC;
struct OpaqueRefHolder {
	OpaqueRefCounted *m_ptr;
	~OpaqueRefHolder() { if (m_ptr) m_ptr->Release_Ref(); }
};
struct FreePtrHolder {
	void *m_ptr;
	~FreePtrHolder() { if (m_ptr) free(m_ptr); }
};
class Rva003B1101 : public Overridable {
public:
	virtual ~Rva003B1101();
private:
	char m_pad04[0x0C];
	StringBaseC m_10;
	char m_pad14[0x10];
	FreePtrHolder m_24;
	char m_pad28[0x0C];
	OpaqueRefHolder m_34;
	OpaqueRefHolder m_38;
	StringBaseC m_3c;
	StringBaseC m_40;
	char m_pad44[0x18];
	StringBaseC m_5c;
	Rva00360D26Member m_60;
	char m_pad64[0x14];
	Rva00360D26Member m_78;
};
inline Rva003B1101::~Rva003B1101()
{
}

// ??1Rva003B1101 is a header inline elsewhere: another unit emits a
// select-any copy, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRva003B1101Dtor@@YAXPAVRva003B1101@@@Z present-unmatched
void bfmeEmitRva003B1101Dtor(Rva003B1101 *p)
{
	p->Rva003B1101::~Rva003B1101();
}
#pragma inline_depth()
