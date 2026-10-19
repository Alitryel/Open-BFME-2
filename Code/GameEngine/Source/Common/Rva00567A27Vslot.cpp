// cl: /Ireference/shims/bfme2_ascii /EHsc /MD
// ?OnMouseOver@Rva00567960@@QAEXXZ @0x00567A27 66B
// vslot 2 of 0x0086CEF0 (+8 of Rva00567960): BfmeMsgDN msg(holder+0x14, this+0xc) then ControlBar::bfmeShowDN via g_bfmeWorldRV.
// Evidence: ret no args thiscall; pin ?bfmeShowDN@ControlBar@@QAEXPAUBfmeMsgDN@@@Z 0x00405C04; global g_bfmeWorldRV ?g_bfmeWorldRV@@3PAUBfmeWorldRV@@A; this+8 deref +0x14 and this+0xc; donor BfmeConv1941 BfmeMsgDN virtual dtor plus 2-int inline ctor.
struct BfmeMsgDN
{
	BfmeMsgDN(int a, int b)
	{
		m_04 = a;
		m_08 = b;
	}
	virtual ~BfmeMsgDN() {}
	int m_04;
	int m_08;
};

struct BfmeWorldRV;
extern class ControlBar *TheControlBar;

class BfmeThingGX;
class Rva00405A50
{
public:
	void rva00405C04(BfmeThingGX *thing);
};

struct Rva00567A27Holder
{
	char m_pad[20];
	int m_14;
};

class Rva00567960
{
public:
	void OnMouseOver();
private:
	char m_pad00[8];
	Rva00567A27Holder *m_08;
	int m_0c;
};

void Rva00567960::OnMouseOver()
{
	BfmeMsgDN msg(m_08->m_14, m_0c);
	((Rva00405A50 *)((BfmeWorldRV *)TheControlBar))->rva00405C04((BfmeThingGX *)&msg);
}
