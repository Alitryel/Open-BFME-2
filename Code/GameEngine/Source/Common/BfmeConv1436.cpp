// cl: /Od

struct BfmePad56VMO
{
	char m[56];
};

struct BfmePadVMO
{
	char m[48];
};

struct BfmePad44VMO
{
	char m[42];
	char n[2];
};

// At pinned 0x0002AE50, this five-word thiscall forwards four range pointers
// and the provider's empty tag reference; its returned string reference is ignored.
#pragma comment(linker, "/alternatename:?bfmeImplVMO@BfmeStrVMO@@QAEXHHHH@Z=?bfmeReplaceAliasedRange@Rva008312E0String@@QAEAAV1@PAD000ABURva008312E0Tag@@@Z")

class BfmeStrVMO
{
public:
	void bfmeFwdVMO(int a, int b, int c, int d);
	void bfmeImplVMO(int a, int b, int c, int d);
};

void BfmeStrVMO::bfmeFwdVMO(int a, int b, int c, int d)
{
	BfmePad56VMO z0;
	BfmePadVMO z1;
	BfmePad44VMO z2;

	__asm
	{
		xor eax, eax
		mov byte ptr z2.n[1], al
		lea ecx, z2.n
		push ecx
		mov edx, dword ptr d
		push edx
		mov eax, dword ptr c
		push eax
		mov ecx, dword ptr b
		push ecx
		mov edx, dword ptr a
		push edx
		mov ecx, this
		call bfmeImplVMO
	}
}
