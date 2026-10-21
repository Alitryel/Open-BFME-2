// cl: /Od

// Const-source range insertion (pos, first, last, forward tag), rowed at 0x00028820.
struct BfmeRangeTag;
class Rva008314E0String
{
public:
	void insertRange(char *pos, char *first, char *last, const BfmeRangeTag &tag);
};

struct BfmePadVMF
{
	int m[10];
};

class BfmeStrVMF
{
public:
	void bfmeFwdVMF(int a, int b, int c, int d);
};

void BfmeStrVMF::bfmeFwdVMF(int a, int b, int c, int d)
{
	char n;
	BfmePadVMF z0, z1, z2;

	((Rva008314E0String *)this)->insertRange((char *)a, (char *)b, (char *)c, *(const BfmeRangeTag *)&n);
}
