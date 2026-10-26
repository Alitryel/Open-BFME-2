struct AriesUdp;
struct AriesUdp *bfme5MakeObj18();

class BfmeThingBCE
{
public:
	void bfmeGoBCE();
	unsigned char m_bfmeHead[0x2a0];
	void *m_bfmeWhat;
};

void BfmeThingBCE::bfmeGoBCE()
{
	m_bfmeWhat = (void *)bfme5MakeObj18();
}
