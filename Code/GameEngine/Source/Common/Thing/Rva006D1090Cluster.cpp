// cl: /EHsc
//
// 0x006D1090 neighbourhood cluster (Nugget-chain block family, near
// Rva006D0F20Release.cpp).  The complete destructor walks a singly linked list
// whose head lives at +0 (the base sub-object's own field) and calls the opaque
// per-node helper on each node; the base sub-object destructor then clears the
// pool.  Helper identity is unproven, so it keeps an address-derived member name.

struct Rva006D1090Node
{
	void *m_field00;
};

class Rva006CE380
{
public:
	~Rva006CE380();

	Rva006D1090Node *m_head;
};

class Rva006D1090 : public Rva006CE380
{
public:
	~Rva006D1090();
	void rva006D0D70(void *arg);
};

Rva006D1090::~Rva006D1090()
{
	while (m_head != 0)
		rva006D0D70((char *)m_head->m_field00 + 8);
}
