// Retail vtable 0x008E3410 is Rva00667260's vftable, emitted by
// InlineDtorDeletingDtors2.cpp; __identifier spells that symbol exactly.
extern "C" unsigned char __identifier("??_7Rva00667260@@6B@")[];

void bfmeFreeSizedVF(void *what, unsigned int bytes);

class BfmeThingVF
{
public:
	void *bfmeKillVF(int flags);
	void *m_bfmeVft;
};

void *BfmeThingVF::bfmeKillVF(int flags)
{
	m_bfmeVft = __identifier("??_7Rva00667260@@6B@");
	if ((flags & 1) != 0)
		bfmeFreeSizedVF(this, 0xd8);
	return this;
}
