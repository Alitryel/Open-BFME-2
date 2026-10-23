// Open-BFME1 donor: reference/open-bfme-1/Code/GameEngine/Source/Common/BfmeConv1039.cpp
// BFME1 byte-identical donor for bfmeGo1039E; b1 0x009903E0.
// Distinct TU because Code/GameEngine/Source/Common/BfmeConv1039.cpp already
// holds Go1039C (see its header comment: Go1039E lives elsewhere).

struct BfmeRec1039
{
	int m_bfmeKind;
	char m_bfmePad[4];
	int m_bfmeVal;
	char m_bfmePad2[4];
};

struct BfmeQ1039
{
	BfmeRec1039 *m_bfmeCur;
	char m_bfmePad[4];
	BfmeRec1039 *m_bfmeEnd;
};

struct lua_State;
extern "C" void luaD_checkstack(lua_State *L, int n);

void bfmeGo1039E(BfmeQ1039 *q, int v)
{
	q->m_bfmeCur->m_bfmeKind = 6;
	q->m_bfmeCur->m_bfmeVal = v;

	if (q->m_bfmeCur == q->m_bfmeEnd)
		luaD_checkstack((lua_State *)q, 1);

	q->m_bfmeCur++;
}
