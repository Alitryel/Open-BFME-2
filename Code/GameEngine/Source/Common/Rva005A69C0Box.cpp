// cl: -Oy- -GR- -EHsc-
// NAT::reconnectPlayers @0x005A69C0 140B (WorldBuilder name, its
// __FUNCTION__ string "NAT::reconnectPlayers"; WB calls GameSlot::isHuman
// and PortNegotiationSchema::reconnectPlayers as retail does): two-slot validated swap
// prep. After the predicate and triple ushort-guard (a<8, b<8, a!=b), both
// slots must be present and human (pinned 0x3FF0F1); the +0x28 sub-object
// consumes the full (a, b, c) via the pinned 3-arg callee 0x5DC187, then
// +0x10 stamps 1 while the byte table clears the non-current index. All
// call targets read from retail REL32; true identities unproven.
// GameSlot::isHuman is rowed at 0x003FF0F1 (GameSlotHumanSaveoff.cpp).
class GameSlot
{
public:
	bool isHuman() const;
};

// The +0x28 sub-object's callees are rowed as PortNegotiationSchema members
// (PortNegotiationSchema.cpp, Rva005DBCA6Get.cpp, Rva005DB98EGet.cpp).
class PortNegotiationSchema
{
public:
	bool isConnectionDone(unsigned short j, unsigned short i);	// 0x005DBBC1
	void *peekPing(unsigned short j, unsigned short i);	// 0x005DB98E
	bool isRetryConnectingOverLimit(unsigned short i, unsigned short j);	// 0x005DBC2E
	void reconnectPlayers(unsigned short slot1, unsigned short slot2, bool resetRetries);	// 0x005DC187
};
// LINK: retail pushes the three arguments unconverted, so the rowed
// reconnectPlayers keeps that int call shape through a member-pointer cast.
typedef void (PortNegotiationSchema::*PortNegotiationReconnectShape)(int, int, int);

// The readiness gate 0x005A6709 is rowed as int Rva005A6709::rva005A6709()
// const (Rva005A6709Predicate.cpp); its callers test al, so they keep the
// bool call shape through a member-pointer cast (as Rva005A6903Box.cpp does).
class Rva005A6709
{
public:
	int rva005A6709() const;
};
typedef bool (Rva005A6709::*Rva005A6709BoolShape)() const;
#define NAT_READY(p) ((((Rva005A6709 *)(p))->*reinterpret_cast<Rva005A6709BoolShape>(&Rva005A6709::rva005A6709))())

struct NAT
{
	char pad0[8];
	GameSlot **m_8;
	int m_C;
	int m_10;
	int m_14;
	char pad1[0x28 - 0x18];
	PortNegotiationSchema m_28;
	char pad2[0x8e4 - 0x29];
	unsigned char m_8E4[8];
	int m_8EC[8];
	int *m_90C[8];

	void reconnectPlayers(int a, int b, int c);
	void rva005A6CA5();
	void rva005A6D47();
};

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();
// 0x009D35C8 (.data): the ping-age limit the pair scan compares against;
// nothing else defines it, so it is defined here at its retail value.
int g_rva005A6CA5Limit = 12000;

void NAT::reconnectPlayers(int a, int b, int c)
{
	if (!NAT_READY(this))
		return;
	if ((unsigned short)a >= 8)
		return;
	if ((unsigned short)b >= 8)
		return;
	if ((unsigned short)a == (unsigned short)b)
		return;
	int an = (unsigned short)a;
	GameSlot *oa = m_8[an];
	if (oa == 0)
		return;
	int bn = (unsigned short)b;
	if (m_8[bn] == 0)
		return;
	if (!oa->isHuman())
		return;
	if (!m_8[bn]->isHuman())
		return;
	(m_28.*reinterpret_cast<PortNegotiationReconnectShape>(&PortNegotiationSchema::reconnectPlayers))(a, b, c);
	if (an == m_14) {
		m_10 = 1;
		m_8E4[bn] = 0;
	} else {
		m_10 = 1;
		m_8E4[an] = 0;
	}
}

// NAT::rva005A6CA5 @0x005A6CA5 162B (unnamed in WB): pair scan over the 8 slots.
// For each present human slot pair (i, j) with i != j, the +0x28 sub-object
// runs its two queries; a surviving response whose +0x10 timestamp is older
// than the limit invokes the sibling reconnectPlayers(i, j, 0). Same class as reconnectPlayers: the
// sibling call passes this untouched, and Check/IsHuman reuse their pins.
void NAT::rva005A6CA5()
{
	NAT *self = this;
	if (!NAT_READY(this))
		return;
	int stamp = timeGetTime();
	int i = 0;
	do {
		GameSlot *gameSlot = m_8[i];
		if (gameSlot != 0 && gameSlot->isHuman()) {
			int j = 0;
			do {
				if (i != j) {
					GameSlot *o2 = m_8[j];
					if (o2 != 0 && o2->isHuman()) {
						PortNegotiationSchema *portNegotiationSchema = (PortNegotiationSchema *)((char *)self + 0x28);
						if (portNegotiationSchema->isConnectionDone(i, j)) {
							void *r = portNegotiationSchema->peekPing(i, j);
							if (r != 0) {
								int t = *(int *)((char *)r + 0x10);
								if (t != 0 && (unsigned)(stamp - t) > (unsigned)g_rva005A6CA5Limit)
									reconnectPlayers(i, j, 0);
							}
						}
					}
				}
				++j;
			} while (j < 8);
		}
		++i;
	} while (i < 8);
}

// NAT::rva005A6D47 @0x005A6D47 101B (unnamed in WB, twin at 0x014E3C60): the
// retry pass over the same slot pairs. For each present human pair (i, j)
// with i != j whose +0x28 schema reports the retries over their limit
// (0x5DBC2E, WB PortNegotiationSchema::isRetryConnectingOverLimit), the pair
// is reconnected with the third argument 1. WB inlines the gate the retail
// body calls (0x5A6709); its loops are the same.
void NAT::rva005A6D47()
{
	if (!NAT_READY(this))
		return;
	int i = 0;
	do {
		GameSlot *gameSlot = m_8[i];
		if (gameSlot != 0 && gameSlot->isHuman()) {
			int j = 0;
			do {
				if (i != j) {
					GameSlot *o2 = m_8[j];
					if (o2 != 0 && o2->isHuman()) {
						if (m_28.isRetryConnectingOverLimit(i, j))
							reconnectPlayers(i, j, 1);
					}
				}
				++j;
			} while (j < 8);
		}
		++i;
	} while (i < 8);
}

// ICF-folded twin of NAT::rva005A6D47 above (same 101 bytes at 0x005A6D47):
// Rva005A6D47 mirrors the NAT members this scan reads (slot array at +8,
// schema at +0x28), and the two NAT member calls keep their targets through
// layout-compatible casts, so every load, call and loop matches exactly.
class Rva005A6D47
{
public:
	void rva005A6D47();
private:
	char pad0[8];
	GameSlot **m_8;
	int m_C;
	int m_10;
	int m_14;
	char pad1[0x28 - 0x18];
	PortNegotiationSchema m_28;
};

void Rva005A6D47::rva005A6D47()
{
	if (!NAT_READY(this))
		return;
	int i = 0;
	do {
		GameSlot *gameSlot = m_8[i];
		if (gameSlot != 0 && gameSlot->isHuman()) {
			int j = 0;
			do {
				if (i != j) {
					GameSlot *o2 = m_8[j];
					if (o2 != 0 && o2->isHuman()) {
						if (m_28.isRetryConnectingOverLimit(i, j))
							((NAT *)this)->reconnectPlayers(i, j, 1);
					}
				}
				++j;
			} while (j < 8);
		}
		++i;
	} while (i < 8);
}
