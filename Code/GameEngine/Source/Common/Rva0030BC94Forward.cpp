// cl: /DNDEBUG /MD
//
// Retail 0x0030BC94 (26 B, RET 4): forwards its argument to the 239-byte leaf
// 0x0053841C on the member at +0x68, then calls virtual slot 10 (+0x28). Same
// shape as the rowed 0x00330ABE (VtableSlotBodiesR4.cpp: container push on +0x08,
// then slot 12). Owner and argument types are unrecovered; names stay
// address-derived.

struct Rva0053841CArg;

class Rva0053841C
{
public:
	void rva0053841C(const Rva0053841CArg *arg);
};

class Rva0030BC94
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09();
	virtual void changed();	// slot 10

	void rva0030BC94(const Rva0053841CArg *arg);

private:
	char m_pad04[0x68 - 0x04];
	char m_member68[4];	// +0x68
};

void Rva0030BC94::rva0030BC94(const Rva0053841CArg *arg)
{
	((Rva0053841C *)m_member68)->rva0053841C(arg);
	changed();
}
