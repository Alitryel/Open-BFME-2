// cl: /Ob0

// The vtable set() installs at +0 is Gen008030A0's (0x00CE3ED4), the table
// Y2ScalarDeleters.cpp emits and BfmeConv1343.cpp binds the same store to.
extern "C" const void *__identifier("??_7Gen008030A0@@6B@")[];

class Rva00803080
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;

public:
	Rva00803080 &set(int a);
};

Rva00803080 &Rva00803080::set(int a)
{
	m_04 = a;
	m_00 = (void *)__identifier("??_7Gen008030A0@@6B@");
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	return *this;
}
