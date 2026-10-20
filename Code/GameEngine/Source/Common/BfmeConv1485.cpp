// cl: /Od

// basic_string<char>::insert<char*>(pos, first, last, forward tag), rowed at 0x000284D0.
struct Rva008312E0Tag;
class Rva008312E0String
{
public:
	void insertRange(char *pos, char *first, char *last, const Rva008312E0Tag &tag);
};

class BfmeStrV43
{
public:
	void bfmeThrowV43();
	void bfmeLenErrV43();

	char *b;
	char *e;
};

void __stdcall bfmeInsertRangeV43(int pos, BfmeStrV43 *other, int opos, int n)
{
	void *at;
	char pad[172];

	__asm
	{
		mov dword ptr [ebp-0xB0], ecx
		mov eax, dword ptr [ebp-0xB0]
		mov ecx, dword ptr [ebp-0xB0]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+8], edx
		ja grow
		mov eax, dword ptr [ebp+0x0C]
		mov ecx, dword ptr [ebp+0x0C]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		cmp dword ptr [ebp+0x10], edx
		jbe skip_throw
	grow:
		mov ecx, dword ptr [ebp-0xB0]
		call BfmeStrV43::bfmeThrowV43
	skip_throw:
		mov eax, dword ptr [ebp+0x0C]
		mov ecx, dword ptr [ebp+0x0C]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		sub edx, dword ptr [ebp+0x10]
		mov dword ptr [ebp-8], edx
		mov eax, dword ptr [ebp-8]
		cmp eax, dword ptr [ebp+0x14]
		jnb use_n
		lea ecx, dword ptr [ebp-8]
		mov dword ptr [ebp-0xB4], ecx
		jmp got_n
	use_n:
		lea edx, dword ptr [ebp+0x14]
		mov dword ptr [ebp-0xB4], edx
	got_n:
		mov eax, dword ptr [ebp-0xB4]
		mov dword ptr [ebp-0x0C], eax
		mov ecx, dword ptr [ebp-0x0C]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-4], edx
		mov eax, dword ptr [ebp-0xB0]
		mov ecx, dword ptr [ebp-0xB0]
		mov edx, dword ptr [eax+4]
		sub edx, dword ptr [ecx]
		mov eax, 0xFFFFFFFE
		sub eax, dword ptr [ebp-4]
		cmp edx, eax
		jbe do_ins
		mov ecx, dword ptr [ebp-0xB0]
		call BfmeStrV43::bfmeLenErrV43
	do_ins:
		mov ecx, dword ptr [ebp-0xB0]
		mov edx, dword ptr [ecx]
		mov dword ptr [ebp-0x10], edx
		mov eax, dword ptr [ebp+0x0C]
		mov ecx, dword ptr [eax]
		add ecx, dword ptr [ebp+0x10]
		add ecx, dword ptr [ebp-4]
		mov dword ptr [ebp-0xA8], ecx
		mov edx, dword ptr [ebp+0x0C]
		mov eax, dword ptr [edx]
		add eax, dword ptr [ebp+0x10]
		mov dword ptr [ebp-0xAC], eax
		xor ecx, ecx
		mov byte ptr [ebp-0x11], cl
		lea edx, dword ptr [ebp-0x12]
		push edx
		mov eax, dword ptr [ebp-0xA8]
		push eax
		mov ecx, dword ptr [ebp-0xAC]
		push ecx
		mov edx, dword ptr [ebp-0x10]
		add edx, dword ptr [ebp+8]
		push edx
		mov ecx, dword ptr [ebp-0xB0]
		call Rva008312E0String::insertRange
		mov eax, dword ptr [ebp-0xB0]
	}
}
