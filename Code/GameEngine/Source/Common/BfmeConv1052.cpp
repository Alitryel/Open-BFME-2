// cl: /Ireference/shims/bfme2_ascii /G7 /arch:SSE /Ireference/shims/bfmecamera /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/GameEngine/Source/Common
// The matched FESL wrapper reads TID and forwards the message to 0x0066CFB0.

class BfmeI1052
{
public:
	int bfmeFind1052(char *n, int f);
};


class BfmeH1052
{
public:
	void bfmeGo1052H(BfmeI1052 *p);
	void bfmeDo1052(int a, BfmeI1052 *p, int r);
};

void BfmeH1052::bfmeGo1052H(BfmeI1052 *p)
{
	bfmeDo1052(0, p, p->bfmeFind1052((char *)"TID", 0));
}
