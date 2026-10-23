// cl: /O1 /DNDEBUG /MD /GX
// ??1Rva007401F6@@UAE@XZ, retail 0x007401F6, 48 bytes.
// ModuleData-style dtor: destroys AsciiString at +8 via rowed releaseBuffer then restores base vtable 0x0083962C.
// Evidence: callers 0x00740229 deleting dtor plus 0x007402AE base call from 0x00740242 vtable 0x008F1600; callee rowed releaseBuffer 0x00036410.
extern "C" const void *const vtbl_00C3962C[];  // ??_7Rva0045EF90Base@@6B@
#pragma comment(linker, "/alternatename:_vtbl_00C3962C=??_7Rva0045EF90Base@@6B@")

class Xfer;
// Base is NOT Snapshot: retail restores vtable 0x00C3962C here, while canonical
// Snapshot (Common/Snapshot.h, vtable 0x00BBB554) restores 0x00BBB554. Kept
// ??1Snapshot differs, so this private view is renamed Rva007401F6Base.
class Rva007401F6Base
{
public:
	virtual ~Rva007401F6Base();
	virtual void crc(Xfer *xfer);
	virtual void loadPostProcess();
	virtual void xfer(Xfer *xfer);
};
// ??1Rva007401F6Base@@UAE@XZ present-unmatched
inline Rva007401F6Base::~Rva007401F6Base()
{
	*(const void **)this = reinterpret_cast<const void *>(((unsigned int)vtbl_00C3962C));
}
template <typename T>
class StringBase
{
public:
	~StringBase() { releaseBuffer(); }
private:
	void releaseBuffer();
	void *m_data;
};

// Existing public narrow teardown spelling resolves to the verified
// 133-byte releaseBuffer worker at RVA 0x36410. Wide teardown is unchanged.
template <> StringBase<char>::~StringBase();
#pragma comment(linker, "/alternatename:??1?$StringBase@D@@QAE@XZ=?releaseBuffer@?$StringBase@D@@AAEXXZ")

typedef StringBase<char> AsciiString;
class __declspec(novtable) Rva007401F6 : public Rva007401F6Base
{
public:
	virtual ~Rva007401F6();
private:
	int m_unused04;
	AsciiString m_str08;
};
Rva007401F6::~Rva007401F6()
{
}
