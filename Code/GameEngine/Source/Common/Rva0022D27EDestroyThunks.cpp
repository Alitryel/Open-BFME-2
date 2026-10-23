// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0022D27EDestroy@@YAXPAVBfmeNarrowRecord00427F75@@@Z @0x0022D27E 9B
// ?Rva0022D287Destroy@@YAXPAVRva0022CD2A@@@Z @0x0022D287 9B
// Two STLport-style _Destroy(p) instances: mov ecx,[esp+4] then a tail jmp
// into the rowed non-virtual dtors at 0x0022CCEF and 0x0022CD2A. They sit
// right after the dtor family block 0x0022CCEF..0x0022D249 and before the
// 0x0022D290 body. Identity of the element types is address-derived; the
// real template spelling is not proven, so the names are address-derived.

class BfmeNarrowRecord00427F75
{
public:
	~BfmeNarrowRecord00427F75();
};

class Rva0022CD2A
{
public:
	~Rva0022CD2A();
};

void __cdecl Rva0022D27EDestroy(BfmeNarrowRecord00427F75 *p)
{
	p->~BfmeNarrowRecord00427F75();
}

void __cdecl Rva0022D287Destroy(Rva0022CD2A *p)
{
	p->~Rva0022CD2A();
}
