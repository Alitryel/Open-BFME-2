// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS
//
// Dump-lane range 5: scratch adapter at 0x174A8A (35B). Passes a by-value
// 32-byte record to the 0x17480C grower; the record is built by the rowed
// BfmeAssignRecord32 default ctor (0x1736D6). Codegen view only (opaque
// members, declared copy/dtor force in-place construction - the same device
// as the 0x150C74 adapter). Address-derived names.

struct BfmeAssignRecord32
{
	void *m_s;
	int m_x;
	void *m_arr[6];
	BfmeAssignRecord32();
	BfmeAssignRecord32(const BfmeAssignRecord32 &other);
	~BfmeAssignRecord32();
};
class Rva0017480C
{
public:
	void rva0017480C(int n, BfmeAssignRecord32 rec);
};
class Rva00174A8A
{
public:
	void rva00174A8A(int n);
};

// ?rva00174A8A@Rva00174A8A@@QAEXH@Z
void Rva00174A8A::rva00174A8A(int n)
{
	((Rva0017480C *)this)->rva0017480C(n, BfmeAssignRecord32());
}

// The retail call in this body reads 0x0017480C, an address the ledger already
// carries as ?resize@Rva0017480CVector@@QAEXIURva0017480CRecord@@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?rva0017480C@Rva0017480C@@QAEXHUBfmeAssignRecord32@@@Z=?resize@Rva0017480CVector@@QAEXIURva0017480CRecord@@@Z")
