// cl: /EHsc /MD
//
// ??0Rva0017FF77@@QAE@PBDHH@Z @0x0017FF77 (77B):
// Ctor with a 0x14-byte base plus the four-byte StringClass at 0x18.
// Native unwind action 0x00768190 destroys the completed base at receiver+0
// through the existing 0x00135E35 worker. The old empty secondary base
// incorrectly moved that cleanup receiver to +0x14.
// Evidence: unlock lane callees GenBase 0x0061ED40 StringClass 0x000F0ED1 caller 0x001800EE.
class BfmeThingUB { public: void rva00135E35(); };
extern "C" char GenBase009EB7D0_vtbl;
class __declspec(novtable) GenBase009EB7D0
{
public:
	__declspec(noinline) GenBase009EB7D0();
	// ??1GenBase009EB7D0@@QAE@XZ absent-from-retail
	// Its unused out-of-line copy has no independent retail entry: every
	// JMP to 135E35 belongs to an EH action after loading its receiver.
	__forceinline ~GenBase009EB7D0() { reinterpret_cast<BfmeThingUB *>(this)->rva00135E35(); }
	virtual void handle();
private:
	unsigned int m_flags;
	unsigned int m_zero08;
	unsigned int m_zero0c;
	unsigned int m_zero10;
};
class StringClass
{
public:
	StringClass(const char *name, bool flag);
private:
	char *m_Buffer;
};
class Rva0017FF77 : public GenBase009EB7D0
{
public:
	Rva0017FF77(const char *name, int a, int b);
private:
	int m_14;
	StringClass m_str18;
	int m_1c;
	int m_20;
};

Rva0017FF77::Rva0017FF77(const char *name, int a, int b) : m_14(0), m_str18(name, false), m_1c(a), m_20(b)
{
}
