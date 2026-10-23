// cl: /O1 /MD
// Native6CFDD0..6CFDDB: cdecl store of the second argument into the first
// argument's +0x04 dword. It sits between the rowed +0x0C byte setter
// 0x006CFDC0 and the static pointer increment 0x006CFDE0. No caller or name
// is recovered; the name is address-derived.
struct Rva006CFDD0Pair
{
	int m_first;
	int m_second;
};

void Rva006CFDD0StoreSecond(Rva006CFDD0Pair *pair, int value)
{
	pair->m_second = value;
}
