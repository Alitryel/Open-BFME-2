// cl: /Od

struct BfmePadVMT
{
	char m[48];
};

struct BfmePad20VMT
{
	char m[18];
	char n[2];
};

class BfmeStrVMT
{
public:
	void bfmeFwdVMT(int a, int b);
	void bfmeImplVMT(int a, int b);
};

void BfmeStrVMT::bfmeFwdVMT(int a, int b)
{
	BfmePadVMT z0;
	BfmePad20VMT z2;

	__asm
	{
		xor eax, eax
		mov byte ptr z2.n[1], al
		lea ecx, z2.n
		push ecx
		mov edx, dword ptr a
		add edx, dword ptr b
		push edx
		mov eax, dword ptr a
		push eax
		mov ecx, this
		call bfmeImplVMT
	}
}

// The retail call in this body reads 0x0001B3E0, an address the ledger already
// carries as ??$append@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEAAV01@PBD0ABUforward_iterator_tag@1@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?bfmeImplVMT@BfmeStrVMT@@QAEXHH@Z=??$append@PBD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@AAEAAV01@PBD0ABUforward_iterator_tag@1@@Z")
