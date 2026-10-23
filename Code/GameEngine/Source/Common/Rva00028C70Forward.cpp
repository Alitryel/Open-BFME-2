// cl: /Od
// ?rva00028C70@Rva00028C70@@QAEHDH@Z @0x00028C70 29B leaf forwarder to rowed bfmeFwdOneSUA 0x000274D0; neighbours BfmeTwoHundredSixtySix/Seven /Od; ret 8 registers proven by call
class BfmeThingSUA
{
public:
	int bfmeFwdOneSUA(char a, int b);
};

class Rva00028C70
{
public:
	int rva00028C70(char a, int b);
};

int Rva00028C70::rva00028C70(char a, int b)
{
	return ((BfmeThingSUA *)this)->bfmeFwdOneSUA(a, b);
}
