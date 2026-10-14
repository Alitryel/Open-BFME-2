// cl: /O1 /MD
//
// ??0Rva0056DC4C@@QAE@PAX@Z @0x0056DC4C 31B.
// Constructor: run matched 0x002D2C34 base, set +0x58 to the argument,
// clear +0x5C via AND-zero, install 0x00C6DB78 at +0. Sibling of the
// rowed 0x0056AF94 tiny ctor. Honest address-derived name.
class Rva005248D0
{
public:
	Rva005248D0();
};

extern "C" const void *const vtbl_00C6DB78[];

class Rva0056DC4C
{
public:
	Rva0056DC4C(void *arg);
private:
	char m_pad[0x58];
	void *m_58;
	int m_5C;
};

Rva0056DC4C::Rva0056DC4C(void *arg)
{
	((Rva005248D0 *)this)->Rva005248D0::Rva005248D0();
	m_58 = arg;
	m_5C &= 0;
	*(unsigned int *)this = ((unsigned int)vtbl_00C6DB78);
}
