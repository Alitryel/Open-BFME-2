// cl: /O1 /arch:SSE /G7 /MD
// Retail 0x0033ADA5/27 (RET 8): a pair-shaped constructor that
// copy-constructs a BitFlags<117> key at +0 through the pinned
// ??0?$BitFlags@$0HF@@@QAE@ABV0@@Z 0x002CF108 and stores a pointer-sized
// value at +0x10. Instruction-for-instruction the shape of the rowed
// pair<const string, unsigned int> constructor 0x0038A4EA. It sits beside
// the rowed SparseMatchFinder<..., BitFlags<117> > MapHelper bodies
// (0x0033AD13, 0x0033AD5C), but no caller is named, so the pair's mapped
// type is not established and the name is address-derived.
template<int N> class BitFlags
{
public:
	BitFlags(const BitFlags &that);
	unsigned int m_words[(N + 31) / 32];
};

struct Rva0033ADA5Entry
{
	Rva0033ADA5Entry(const BitFlags<117> &key, const void *const &value);
	BitFlags<117> first;
	const void *second;
};

Rva0033ADA5Entry::Rva0033ADA5Entry(const BitFlags<117> &key, const void *const &value)
	: first(key), second(value)
{
}
