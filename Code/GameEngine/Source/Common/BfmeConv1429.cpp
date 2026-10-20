// cl: /Od

// basic_string<char>::insert<char*>(pos, first, last, forward tag), rowed at 0x000284D0.
struct Rva008312E0Tag;
class Rva008312E0String
{
public:
	void insertRange(char *pos, char *first, char *last, const Rva008312E0Tag &tag);
};

struct BfmePadVMG
{
	int m[12];
};

class BfmeStrVMG
{
public:
	void bfmeFwdVMG(int a, int b, int c, int d);
};

void BfmeStrVMG::bfmeFwdVMG(int a, int b, int c, int d)
{
	char n;
	BfmePadVMG z0, z1, z2;

	((Rva008312E0String *)this)->insertRange((char *)a, (char *)b, (char *)c, *(const Rva008312E0Tag *)&n);
}
