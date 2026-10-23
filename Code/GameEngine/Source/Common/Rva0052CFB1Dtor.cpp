// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /GX
// ??1LivingWorldCampaign@@UAE@XZ @0x0052CFB1 157B: dtor with AsciiStrings vectors and twin deletes via get plus Snapshot base BBB554.
// Evidence: vtable 0x00868780 at +0, releaseBuffer +0x04 +0x30 +0x34, vectors +0x0C +0x24 rowed, deletes +0x1C +0x20 via virtual get, base 0xBBB554, caller 0x0052D305, neighbours ConstIntGetters4 RvaVectorDtorFamily.
#include "ascii_string.h"
#define BFME_SNAPSHOT_NAME_SLOT
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

class Xfer;
void __cdecl operator delete(void *);
struct RvaItem0052CFB1 { virtual void *get(int x); };
struct Rva0052CA2D { void *m_start; void *m_finish; void *m_end; ~Rva0052CA2D(); };
struct Rva0052CA6C { void *m_start; void *m_finish; void *m_end; ~Rva0052CA6C(); };
class LivingWorldCampaign : public Snapshot {
public:
	virtual ~LivingWorldCampaign();
	virtual void loadPostProcess();
	virtual const char *GetSnapshotName() const;
	virtual void xfer(Xfer *);
private:
	AsciiString m_04;
	int m_08;
	Rva0052CA2D m_0c;
	int m_18;
	RvaItem0052CFB1 *m_1c;
	RvaItem0052CFB1 *m_20;
	Rva0052CA6C m_24;
	AsciiString m_30;
	AsciiString m_34;
};
LivingWorldCampaign::~LivingWorldCampaign()
{
	delete (m_1c ? m_1c->get(0) : 0);
	delete (m_20 ? m_20->get(0) : 0);
}

// Other units' matched DIR32 witnesses name Snapshot's table at VA 0x00BBB554
// g_00BBB554; bind that name to the canonical emitted table.
#pragma comment(linker, "/alternatename:?g_00BBB554@@3QBQBXB=??_7Snapshot@@6B@")
