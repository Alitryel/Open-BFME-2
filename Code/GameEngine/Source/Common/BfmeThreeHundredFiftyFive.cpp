// flags: region default (reverse/retail_inventory/flag_regions.csv)
// Retail vtable 0x007CEFAC is VectorClass<Vector3>'s vftable, emitted by
// vector_class_vector3_ctor.cpp; __identifier spells that symbol exactly.
extern "C" unsigned char __identifier("??_7?$VectorClass@VVector3@@@@6B@")[];


// The destructor body is the rowed VectorClass<int>::Clear at 0x000F0CD4
// (WWLib/vector_class_resize.cpp), called directly.
template <class T>
class VectorClass
{
public:
	virtual void Clear();
};

class BfmeThingUD
{
public:
	void *bfmeKillUD(int flags);
	void *m_bfmeVft;
};

void *BfmeThingUD::bfmeKillUD(int flags)
{
	m_bfmeVft = __identifier("??_7?$VectorClass@VVector3@@@@6B@");
	((VectorClass<int> *)this)->VectorClass<int>::Clear();
	if ((flags & 1) != 0)
		::operator delete(this);
	return this;
}
