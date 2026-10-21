// cl: /O1 /MD /EHs
//
// Scalar deleting-destructor wrappers with audited owner attributions.
// Target facts: 28-byte flag-test wrappers, their call destinations, and the
// vtable slot-0 links below. Owner evidence is stated per body; retail module
// registrations and class-name strings are distinguished from donor-derived
// class spellings. A named slot alone does not establish the complete owner.
// See docs/reconstruction/deleting-destructor-identity-audit.md.
//
// ActiveBody now carries its complete verified layout (three vptr bases plus
// the +0xE0 pointer and +0xF8 string proven by ??1 at 0x004BF951); the
// deleting-destructor anchor below still emits the ??_G COMDAT from the
// visible destructor, and the wrapper call resolves through the ledger row.

// ??_GActiveBody@@UAEPAXI@Z @0x004BF9D1 28B: slot 0 of vtable 0x00C5B038; calls ??1 at 0x004BF951.
// Owner evidence (audited 2026-09-26): retail slot 4 -> RVA 0x004BF848 uses class-name string "ActiveBody".
// ?releaseBuffer@?$StringBase@D@@AAEXXZ is rowed in StringBaseWideReleaseBuffer.cpp
extern "C" void free(void *block);

template <typename T>
class StringBase
{
public:
// ??1?$StringBase@D@@QAE@XZ present-unmatched
	~StringBase() { releaseBuffer(); }

private:
	void releaseBuffer();
	T *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")


struct FreePtr
{
// ??1FreePtr@@QAE@XZ present-unmatched
	~FreePtr()
	{
		if (m_ptr != 0)
			free(m_ptr);
	}
	void *m_ptr;
};

class Rva004BD763
{
public:
	virtual ~Rva004BD763();

private:
	char m_pad04[8];
};

class ActiveBodyB1
{
public:
	virtual void f1() {}
};

class ActiveBodyB2
{
public:
	virtual void f2() {}
};

// ??1ActiveBody@@UAE@XZ @0x004BF951 (100B): three vptr stores (+0/+0xC/+0x10
// over two trivial MI bases), AsciiString member release at +0xF8 (EH state 1
// via rowed releaseBuffer), conditional free of the +0xE0 pointer (EH state 0
// via rowed _free under /EHs: extern-C callees need /EHs), then the rowed
// ??1Rva004BD763 base (EH state -1). Callers linkNode/handle prove the class;
// member order ptr-then-string proven by EH states 0-then-1.
class ActiveBody : public Rva004BD763, public ActiveBodyB1, public ActiveBodyB2
{
public:
	virtual ~ActiveBody();

private:
	char m_pad14[0xE0 - 0x14];
	FreePtr m_ptrE0;
	char m_padE4[0xF8 - 0xE4];
	StringBase<char> m_strF8;
};

inline ActiveBody::~ActiveBody()
{
}

void ActiveBody_Delete(ActiveBody *activeBody) { delete activeBody; }

// ??1ActiveBody is a header inline elsewhere: other units emit select-any
// copies, so a strong definition here was a duplicate in the linked build.
// This anchor only makes this unit emit its copy for the ledger row; it is
// not retail code.
#pragma inline_depth(0)
// ?bfmeEmitBodyModuleDeletingDtors@@YAXPAVActiveBody@@@Z present-unmatched
void bfmeEmitBodyModuleDeletingDtors(ActiveBody *activeBody)
{
	activeBody->ActiveBody::~ActiveBody();
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1Rva004BF951@@UAE@XZ=??1ActiveBody@@UAE@XZ")
