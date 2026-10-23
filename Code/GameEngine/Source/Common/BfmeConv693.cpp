class BfmeThingDGG;

class Gen007F0130
{
public:
	static void *operator new(unsigned int size);
};

class Rva007FA990
{
public:
	Rva007FA990(void *arg) throw();
};

inline void *operator new(unsigned int, void *p)
{
	return p;
}

BfmeThingDGG *bfmeGoDGG(void *a)
{
	void *p = Gen007F0130::operator new(0xd8);
	if (p != 0)
		return (BfmeThingDGG *)new (p) Rva007FA990(a);
	return 0;
}
