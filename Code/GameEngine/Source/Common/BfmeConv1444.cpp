// cl: /Od

struct BfmePadVMW
{
	char m[48];
};

struct BfmePad12VMW
{
	char m[11];
	char n;
};

struct BfmeObjVMW
{
	int a;
	int b;
};

// At pinned 0x000120F0, this three-word thiscall passes a char range and
// the provider's empty false-type tag; its returned string reference is ignored.
#pragma comment(linker, "/alternatename:?bfmeImplVMW@BfmeStrVMW@@QAEXHHPAD@Z=??$_M_assign_dispatch@PAD@?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAEAAV01@PAD0ABU__false_type@1@@Z")

class BfmeStrVMW
{
public:
	void bfmeFwdVMW(BfmeObjVMW *p);
	void bfmeImplVMW(int a, int b, char *q);
};

void BfmeStrVMW::bfmeFwdVMW(BfmeObjVMW *p)
{
	BfmePadVMW z0, z1;
	BfmePad12VMW z2;

	__asm
	{
		mov eax, dword ptr p
		mov ecx, dword ptr [eax+4]
		mov dword ptr [ebp-0x68], ecx
		mov edx, dword ptr p
		mov eax, dword ptr [edx]
		mov dword ptr [ebp-0x6C], eax
		xor ecx, ecx
		mov byte ptr z2.n, cl
		lea edx, z2.n
		push edx
		mov eax, dword ptr [ebp-0x68]
		push eax
		mov ecx, dword ptr [ebp-0x6C]
		push ecx
		mov ecx, this
		call bfmeImplVMW
	}
}
