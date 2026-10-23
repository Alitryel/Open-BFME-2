// Open-BFME5 conversion (BfmeConv1335).
//
// An #import-style COM raise wrapper: call the raw interface method through
// the vtable, and on a failed HRESULT hand it to _com_issue_errorex with the
// interface IID. The BFME1 donor named the error helper by placeholder; retail
// calls the matched _com_issue_errorex, declared here with its real signature.
// The donor TU's other bodies have no masked retail match here and are left out.

struct IUnknown;
struct _GUID;
void __stdcall _com_issue_errorex(long hr, IUnknown *punk, const _GUID &riid);

struct BfmeGuidUKA
{
	char m_bfmeBytes[16];
};

extern BfmeGuidUKA g_bfmeIidUKA;
// Both retail references resolve to VA 0x00BD4E3C with the same 16 bytes.
// Reuse the existing GUID storage without asserting a separate IID identity.
#pragma comment(linker, "/alternatename:?g_bfmeIidUKA@@3UBfmeGuidUKA@@A=?g_bfmeIidTSA@@3U_GUID@@A")

class BfmeThingUKA;

struct BfmeVtUKA
{
	void *m_bfmeSlot0;
	void *m_bfmeSlot1;
	void *m_bfmeSlot2;
	void *m_bfmeSlot3;
	void *m_bfmeSlot4;
	void *m_bfmeSlot5;
	void *m_bfmeSlot6;
	long (__stdcall *m_bfmeCallUKA)(BfmeThingUKA *self, void *a);
};

class BfmeThingUKA
{
public:
	long bfmeGoUKA(void *a);
	BfmeVtUKA *m_bfmeVt;
};

long BfmeThingUKA::bfmeGoUKA(void *a)
{
	long hr = m_bfmeVt->m_bfmeCallUKA(this, a);
	if (hr < 0)
		_com_issue_errorex(hr, (IUnknown *)this, *(const _GUID *)&g_bfmeIidUKA);
	return hr;
}
