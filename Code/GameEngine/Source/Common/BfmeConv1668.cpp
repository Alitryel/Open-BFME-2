struct BfmeNodeEQB
{
	void *m_bfmeSlotEQB;
	BfmeNodeEQB *m_bfmeNextEQB;
};

extern "C" BfmeNodeEQB *g_bfmeHeadEQB;

BfmeNodeEQB * __stdcall bfmeLinkEQB(BfmeNodeEQB *node)
{
	for (BfmeNodeEQB *p = g_bfmeHeadEQB; p != 0; p = p->m_bfmeNextEQB)
		if (p == node)
			return node;
	node->m_bfmeNextEQB = g_bfmeHeadEQB;
	g_bfmeHeadEQB = node;
	return node;
}
// _g_bfmeHeadEQB: the global at VA 0xe0abb0 is ?g_Va00E0ABB0@@3HA.
#pragma comment(linker, "/alternatename:_g_bfmeHeadEQB=?g_Va00E0ABB0@@3HA")
