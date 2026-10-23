// cl: /Od
//
// Two one-off helpers from the 0x00025B00 neighbourhood, just past
// stlport_vector_voidptr's max_size/get_allocator cluster. 0x00025B00 is an
// unsigned int fill loop with a dead byte flag; 0x00025B50 is a bool
// inequality against two dereferenced ints. The inequality snapshots both
// inputs and uses unsigned arithmetic and a byte conversion for its two
// boolean normalizations. The fill loop retains its recovered assembly.

int *rva0025B00Fill(int *first, unsigned count, const int *value)
{
	char pad[12];

	__asm
	{
		xor eax, eax
		mov byte ptr [ebp-1], al
		mov ecx, dword ptr [ebp+0xc]
		mov dword ptr [ebp-8], ecx
		mov edx, dword ptr [ebp+8]
		mov dword ptr [ebp-0xc], edx
		jmp c3_test
	c3_body:
		mov eax, dword ptr [ebp-8]
		sub eax, 1
		mov dword ptr [ebp-8], eax
		mov ecx, dword ptr [ebp-0xc]
		add ecx, 4
		mov dword ptr [ebp-0xc], ecx
	c3_test:
		cmp dword ptr [ebp-8], 0
		jbe c3_end
		mov edx, dword ptr [ebp-0xc]
		mov eax, dword ptr [ebp+0x10]
		mov ecx, dword ptr [eax]
		mov dword ptr [edx], ecx
		jmp c3_body
	c3_end:
		mov eax, dword ptr [ebp-0xc]
	}
}

bool rva0025B50NotEqual(const int *a, const int *b)
{
	struct Values
	{
		int right;
		int left;
	} values;
	values.left = *a;
	values.right = *b;
	return !static_cast<unsigned char>(static_cast<unsigned>(!(static_cast<unsigned>(values.left) - static_cast<unsigned>(values.right))));
}
