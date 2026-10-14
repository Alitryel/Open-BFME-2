// flags: region default (reverse/retail_inventory/flag_regions.csv)
extern "C" unsigned char bfmeVftUD[];


class BfmeThingUD
{
public:
	void bfmeDtorUD();
	void *bfmeKillUD(int flags);
	void *m_bfmeVft;
};

void *BfmeThingUD::bfmeKillUD(int flags)
{
	m_bfmeVft = bfmeVftUD;
	bfmeDtorUD();
	if ((flags & 1) != 0)
		::operator delete(this);
	return this;
}
