// ?bfmeAddEQR@BfmeHostEQR@@QAEXPAVBfmeThingEQR@@@Z
//
// BFME1 donor BfmeConv1945.cpp shape: null/slot6 guards, allocate a link
// record through the owner list head, publish via slot5, then link. BFME2
// repair: the list head sits at +0x114 here, not BFME1's +0xE4 (near-miss
// drift at +0x47: lea ecx,[ebx+0xE4] vs [ebx+0x114]). B1 0x009F50E0 131B ->
// B2 0x00627810 131B, immediate-only drift. Record ctor resolves via pin at
// 0x006257C0 (alongside the matched BfmeChainRecord row); link resolves via
// pin at 0x006274B0. NOTE: an opaque ShroudManager pin names this address
// (live caller in PartitionManagerShroudThunks.cpp); left undisturbed per
// the Rva008859D0 precedent — donor evidence carries this row.
class BfmeRecEQR
{
public:
	BfmeRecEQR(void *first, void *second, BfmeRecEQR **ownerLink);

	unsigned char m_bfmeBodyEQR[0x30];
};

class BfmeThingEQR
{
public:
	virtual void bfmeSlot0EQR();
	virtual void bfmeSlot1EQR();
	virtual void bfmeSlot2EQR();
	virtual void bfmeSlot3EQR();
	virtual void bfmeSlot4EQR();
	virtual void bfmeSlot5EQR(BfmeRecEQR *rec);
	virtual void *bfmeSlot6EQR();
};

class BfmeHostEQR
{
public:
	void bfmeAddEQR(BfmeThingEQR *thing);
	void bfmeLinkEQR(BfmeRecEQR *rec);

	unsigned char m_bfmeHeadEQR[0x114];
	BfmeRecEQR *m_bfmeListEQR;
};

// ?bfmeAddEQR@BfmeHostEQR@@QAEXPAVBfmeThingEQR@@@Z
void BfmeHostEQR::bfmeAddEQR(BfmeThingEQR *thing)
{
	if (thing == 0)
		return;

	if (thing->bfmeSlot6EQR() != 0)
		return;

	BfmeRecEQR *rec = new BfmeRecEQR(this, thing, &m_bfmeListEQR);

	thing->bfmeSlot5EQR(rec);
	bfmeLinkEQR(rec);
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?Rva00627810@ShroudManager@@QAEXPAX@Z=?bfmeAddEQR@BfmeHostEQR@@QAEXPAVBfmeThingEQR@@@Z")
