// cl: /Od

// basic_string<char>::insert<char*>(pos, first, last, forward tag), rowed at 0x000284D0.
struct Rva008312E0Tag;
class Rva008312E0String
{
public:
	void insertRange(char *pos, char *first, char *last, const Rva008312E0Tag &tag);
};

struct BfmePad56VMS
{
	char m[56];
};

struct BfmePadVMS
{
	char m[48];
};

struct BfmePad44VMS
{
	char m[42];
	char n[2];
};

class BfmeStrVMS
{
public:
	void bfmeFwdVMS(int a, int b, int c);
};

void BfmeStrVMS::bfmeFwdVMS(int a, int b, int c)
{
	BfmePad56VMS z0;
	BfmePadVMS z1;
	BfmePad44VMS z2;

	__asm
	{
		xor eax, eax
		mov byte ptr z2.n[1], al
		lea ecx, z2.n
		push ecx
		mov edx, dword ptr c
		push edx
		mov eax, dword ptr b
		push eax
		mov ecx, dword ptr a
		push ecx
		mov ecx, this
		call Rva008312E0String::insertRange
	}
}
