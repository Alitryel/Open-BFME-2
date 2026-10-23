// cl: /MD
// ?rva0030F3A5@Rva0030F388@@QAEXABM@Z @ 0x0030F3A5 26B: store the value at
// +0x18 then broadcast slot 1 to the listener list at +4.
// Evidence: rowed forEach 0x0030F34D (Rva0030F2E0ListenerWalks.cpp) called
// with list at +4 and this, as in the rowed siblings 0x0030F36B/0x0030F388;
// the pushed code 0x005CB260 is the slot +0x04 vcall thunk; +0x18 is the
// float the rowed 0x0030F3BF clamps. Names are address-derived.
class Rva0030F34DListener
{
public:
	virtual void notify0(void *);
	virtual void notify1(void *);
};

class Rva0030F34DList
{
public:
	void forEach(void (Rva0030F34DListener::*notify)(void *), void *arg);
private:
	Rva0030F34DListener **m_begin;
	Rva0030F34DListener **m_end;
	Rva0030F34DListener **m_capacity;
	unsigned int m_index;
};

class Rva0030F388
{
public:
	void rva0030F3A5(const float &value);
private:
	char m_00[4];
	Rva0030F34DList m_list;
	char m_pad14[4];
	float m_18;
	bool m_flag;
};

void Rva0030F388::rva0030F3A5(const float &value)
{
	m_18 = value;
	m_list.forEach(&Rva0030F34DListener::notify1, this);
}
