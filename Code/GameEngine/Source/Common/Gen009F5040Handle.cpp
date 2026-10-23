// Partition calculate recovery: BFME1 donor commit 63c2207a252634a8d48d248b11d81d5e5f6f8241,
// at verified reference 644b1863ec6ec70c7eb3313432ab438c5735d347, from
// game/Libraries/Source/partitionmanager/Gen009F5040Calculate.cpp.
// Target 0x006271D0 is the complete 225-byte calculator called by the
// already matched handle/linkNode siblings under the existing calculate name.
// Its two virtual getters, ER/ES calls and result stores establish the target
// relationship. The donor's value-returning first-stage helper preserves the
// native ESI-to-EAX copy before the bit scan. Helper types/names are source
// structure from that donor, not independently recovered target identities.
// Keep this file's BFME2 +0x11C mask/+0x120 node layout; no donor layout import.

struct Rva009F4900Stage
{
    unsigned int v;
    int r;
    // ??0Rva009F4900Stage@@QAE@IH@Z absent-from-retail
    Rva009F4900Stage(unsigned int value, int result) : v(value), r(result) {}
};
// ?step16_009F4900@@YA?AURva009F4900Stage@@U1@@Z absent-from-retail
static __forceinline Rva009F4900Stage step16_009F4900(Rva009F4900Stage s)
{
    if (s.v & 0xffff0000) {
        s.v >>= 16;
        s.r = 16;
    }
    return s;
}
struct Gen009F5040Item;

// Independently matched overlapping receiver views, both called without a
// receiver adjustment. These declarations do not assert inheritance.
class BfmeHostER
{
public:
	unsigned int bfmeIndexER(float value);
};
class BfmeHostES
{
public:
	unsigned int bfmeIndexES(float value);
};

struct Gen009F4900Value0
{
	char m_pad00[0x10];
	float m_value10;
};
struct Gen009F4900Value1
{
	float m_value00;
	float m_value04;
};

// ?remove@PartitionManagerImpl@@QAEXPAUGen009F5040Node@@@Z
//
// BFME1 donor Gen009F5040Handle.cpp shape: unlink the node from the
// secondary list, then walk the counter pyramid (mask/count halving per
// level). BFME2 repair: m_mask sits at +0x11C here, not BFME1's +0xEC
// (near-miss drift at +0x37: mov esi,[ecx+0xEC] vs [ecx+0x11C]), so the pad
// runs 0xFC, not 0xCC. B1 0x009F4E40 134B -> B2 0x00627570 134B,
// immediate-only drift. Leaf (no callees, no pins). The handle() sibling is
// recovered below at BFME2 0x00627770.
struct Gen009F5040Item;

struct Gen009F5040Node
{
	char m_pad00[4];
	Gen009F5040Item *m_item;
	char m_pad08[8];
	Gen009F5040Node **m_secondaryPreviousLink;
	Gen009F5040Node *m_secondaryNext;
	Gen009F5040Node **m_previousLink;
	Gen009F5040Node *m_next;
	volatile int m_index;
	int m_result24;
	int m_result28;
	int m_result2c;
};

struct Gen009F5040Item
{
	virtual void *getValue0();
	virtual void *getValue1();
	virtual void *getValue2();
	virtual void *getValue3();
	virtual void *getValue4();
	virtual void *getValue5();
	virtual void *getValue6();
	virtual int getIndex();
};

class BfmeRecEQR;

class BfmeHostEQR
{
public:
	void bfmeLinkEQR(BfmeRecEQR *rec);
};

struct Gen009F5040Counter
{
	int m_value;
	Gen009F5040Node *m_head;
};

struct Gen009F5040Bucket
{
	Gen009F5040Counter *m_counter;
	int m_pad04;
	int m_pad08;
};

class PartitionManagerImpl
{
public:
	__declspec(noinline) void remove(Gen009F5040Node *node);
	void handle();
	void linkNode(Gen009F5040Node *node);
	__declspec(noinline) void calculate(Gen009F5040Node *node, int *result28, int *result2c,
		int *result24);

	Gen009F5040Bucket m_buckets[2];
	Gen009F5040Counter *m_rangeBegin;
	Gen009F5040Counter *m_rangeEnd;
	char m_pad20[0xfc];
	unsigned int m_mask;
	Gen009F5040Node *m_node;
};

// ?remove@PartitionManagerImpl@@QAEXPAUGen009F5040Node@@@Z
void PartitionManagerImpl::remove(Gen009F5040Node *node)
{
	if (node->m_secondaryNext != 0)
		node->m_secondaryNext->m_secondaryPreviousLink = node->m_secondaryPreviousLink;
	*node->m_secondaryPreviousLink = node->m_secondaryNext;

	node->m_secondaryPreviousLink = 0;
	Gen009F5040Counter *counter = m_buckets[node->m_index + 2].m_counter;

	Gen009F5040Counter *rangeEnd = m_rangeEnd;
	Gen009F5040Counter *rangeBegin = m_rangeBegin;
	unsigned int mask = m_mask >> 1;
	unsigned int count = (unsigned int)(rangeEnd - rangeBegin) >> 2;
	while (count != 0) {
		if ((node->m_result24 & mask) != 0)
			return;
		--counter->m_value;
		int step = (node->m_result2c & mask) != 0 ? 2 : 0;
		step += ((node->m_result28 & mask) != 0);
		counter += step * count + 1;
		count >>= 2;
		mask >>= 1;
	}
}

void PartitionManagerImpl::handle()
{
	Gen009F5040Node *node = m_node;
	if (node == 0)
		return;

	while (node != 0) {
		if (node->m_next != 0)
			node->m_next->m_previousLink = node->m_previousLink;
		*node->m_previousLink = node->m_next;
		node->m_previousLink = 0;

		bool shouldProcess = node->m_index != node->m_item->getIndex() + 1;
		if (!shouldProcess) {
			int result28;
			int result2c;
			int result24;
			calculate(node, &result28, &result2c, &result24);
			if (result28 != node->m_result28 || result2c != node->m_result2c ||
				result24 != node->m_result24)
				shouldProcess = true;
		}
		if (shouldProcess) {
			remove(node);
			((BfmeHostEQR *)this)->bfmeLinkEQR((BfmeRecEQR *)node);
		}

		node = m_node;
	}
}

// ?linkNode@PartitionManagerImpl@@QAEXPAUGen009F5040Node@@@Z
//
// BFME1 donor Gen009F5040Handle.cpp linkNode_009F4D80 shape: recompute the
// node results, clamp the item index, walk the counter pyramid bumping
// counts, then link the node into the winning counter's secondary list.
// BFME2 repair: the clamp is index >= 20 (cmp eax,0x14), not BFME1's >= 16
// (near-miss drift at +0x31: 10 vs 14, plus mask member +0x11C already in
// this TU). B1 0x009F4D80 181B -> B2 0x006274B0 181B, immediate-only drift.
// Callees: calculate (pinned 0x6271D0) + virtual getIndex (slot 0x1C).
void PartitionManagerImpl::linkNode(Gen009F5040Node *node)
{
	calculate(node, &node->m_result28, &node->m_result2c, &node->m_result24);
	int index = node->m_item->getIndex();
	if (index < -1 || index >= 20)
		index = -1;
	Gen009F5040Counter *counter = m_buckets[index + 3].m_counter;
	unsigned int mask = m_mask >> 1;
	unsigned int count = (unsigned int)(m_rangeEnd - m_rangeBegin) >> 2;
	while (count != 0) {
		if (node->m_result24 & mask)
			break;
		++counter->m_value;
		int step = ((node->m_result2c & mask) != 0 ? 2 : 0);
		step += ((node->m_result28 & mask) != 0);
		counter += step * count + 1;
		count >>= 2;
		mask >>= 1;
	}
	Gen009F5040Node **slot = &counter->m_head;
	node->m_secondaryPreviousLink = slot;
	node->m_secondaryNext = *slot;
	if (node->m_secondaryNext != 0)
		node->m_secondaryNext->m_secondaryPreviousLink = &node->m_secondaryNext;
	*slot = node;
	node->m_index = index + 1;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeLinkEQR@BfmeHostEQR@@QAEXPAVBfmeRecEQR@@@Z=?linkNode@PartitionManagerImpl@@QAEXPAUGen009F5040Node@@@Z")

// Keep the first getter view live across the second virtual call.
// ?calculate@PartitionManagerImpl@@QAEXPAUGen009F5040Node@@PAH11@Z
void PartitionManagerImpl::calculate(Gen009F5040Node *node,
	int *result28, int *result2c, int *result24)
{
	Gen009F4900Value0 *value0 = (Gen009F4900Value0 *)node->m_item->getValue0();
	Gen009F4900Value1 *value1 = (Gen009F4900Value1 *)node->m_item->getValue1();
	float value10 = value0->m_value10;
	*result28 = ((BfmeHostER *)this)->bfmeIndexER(value1->m_value00 - value10);
	*result2c = ((BfmeHostES *)this)->bfmeIndexES(value1->m_value04 - value10);
	unsigned int difference = ((BfmeHostER *)this)->bfmeIndexER(value10 + value1->m_value00) ^ *result28;
	difference |= ((BfmeHostES *)this)->bfmeIndexES(value10 + value1->m_value04) ^ *result2c;
	*result24 = difference;
	if (difference != 0) {
		Rva009F4900Stage state(difference, 0);
		state = step16_009F4900(state);
		unsigned int v = state.v;
		int r = state.r;
		if (v & 0xff00) { v >>= 8; r |= 8; }
		if (v & 0xf0) { v >>= 4; r |= 4; }
		if (v & 0xc) { v >>= 2; r |= 2; }
		if (v & 2) r |= 1;
		unsigned int mask = ~(1u << r);
		*result28 &= mask;
		*result2c &= mask;
	}
}
