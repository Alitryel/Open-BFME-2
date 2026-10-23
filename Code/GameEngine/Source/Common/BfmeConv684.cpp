
class BfmeOtherDFC
{
public:
	void *bfmeMakeDFC(void *info, int flag);
};

class BfmeThingDFC
{
public:
	BfmeThingDFC *bfmeGoDFC(BfmeOtherDFC *other);
	void *m_bfmeVal;
};

BfmeThingDFC *BfmeThingDFC::bfmeGoDFC(BfmeOtherDFC *other)
{
	m_bfmeVal = other->bfmeMakeDFC((char *)"NUM-LOBBIES", 0);
	return this;
}

// ?rva00661D10@Rva00661D10@@QAEPAV1@PAVBfmeOtherDFC@@@Z @0x00661D10 27B.
// Same skeleton as bfmeGoDFC above with the "PID" key (retail literal at VA
// 0x00CE2D70) through the same folded maker 0x00655990. BFME 1 offers two
// donor names for this body (DFI/DFJ) and bytes cannot tell them apart, so it
// keeps an address-derived name.
class Rva00661D10
{
public:
	Rva00661D10 *rva00661D10(BfmeOtherDFC *other);
	void *m_bfmeVal;
};

Rva00661D10 *Rva00661D10::rva00661D10(BfmeOtherDFC *other)
{
	m_bfmeVal = other->bfmeMakeDFC((char *)"PID", 0);
	return this;
}
