// ?Rva0030BFE8Equal@@YAHPBURva0030BFE8Range@@0@Z
// partial score=0.93 date=2026-09-30
// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ?Rva0030BFE8Equal@@YAHPBURva0030BFE8Range@@0@Z retail 0x0030BFE8 61B: range equal via len xor plus rowed float equal.
// Evidence: sub sub xor test fffffff0 jne plus call equal with add esp C then test branchy tail; caller pushes 3 args.

bool __cdecl Rva0030BF0CEqual(const float *first1, const float *last1, const float *first2);

struct Rva0030BFE8Range
{
	const float *begin;
	const float *end;
};

int __cdecl Rva0030BFE8Equal(const Rva0030BFE8Range *lhs, const Rva0030BFE8Range *rhs)
{
	int len1 = (const char *)lhs->end - (const char *)lhs->begin;
	int len2 = (const char *)rhs->end - (const char *)rhs->begin;
	if ((((len1 ^ len2) & 0xfffffff0) == 0) && Rva0030BF0CEqual(lhs->begin, lhs->end, rhs->begin))
		return 1;
	return 0;
}
