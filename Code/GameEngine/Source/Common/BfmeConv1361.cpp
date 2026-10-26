// Copy a VHE message, preserving a keyed field.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv1361.cpp); trimmed to the single T1
// body the sweep places.

class BfmeMsgVHE
{
public:
	int bfmeGetVHE(void *k, int d);
	void bfmeSetVHE(void *k, int v);
	int m_bfme00;
	int m_bfme04;
	int m_bfme08;
	int m_bfme0c;
	char m_bfmePad[0xc];
	int m_bfme1c;
};


void __stdcall copyMessageHeader(BfmeMsgVHE *dst, BfmeMsgVHE *src)
{
	dst->m_bfme1c = src->m_bfme1c;
	int transactionId = src->bfmeGetVHE((int *)"TID", -1);
	if (transactionId != -1)
		dst->bfmeSetVHE((int *)"TID", transactionId);
	dst->m_bfme04 = src->m_bfme04;
	dst->m_bfme08 = src->m_bfme08;
	dst->m_bfme0c = src->m_bfme0c;
}
