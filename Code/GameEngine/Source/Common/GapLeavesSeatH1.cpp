// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG
//
// Small bodies from unrowed .text gaps in the /O1 /arch:SSE /G7 region, each
// bounded by its neighbour's ret or padding and its own ret. Retail bytes
// establish every shape. The original classes are not recovered, so each body
// keeps an address-derived name and a view of only what it touches.

// --- 0x003390AF (3B): the all-ones byte.
char Rva003390AFGet()
{
	return -1;
}

// --- 0x00452D49 (9B): the out-of-line constructor of a pure interface: it
// stores the vftable at 0x008633C0, fifteen _purecall slots (any fifteen-slot
// pure interface folds onto it; Rva004FAC6B's constructor stores it too) and
// returns this. No xrefs; the interface name is not recovered.
class Rva00452D49Interface
{
public:
	Rva00452D49Interface();
	virtual void slot00() = 0;
	virtual void slot01() = 0;
	virtual void slot02() = 0;
	virtual void slot03() = 0;
	virtual void slot04() = 0;
	virtual void slot05() = 0;
	virtual void slot06() = 0;
	virtual void slot07() = 0;
	virtual void slot08() = 0;
	virtual void slot09() = 0;
	virtual void slot10() = 0;
	virtual void slot11() = 0;
	virtual void slot12() = 0;
	virtual void slot13() = 0;
	virtual void slot14() = 0;
};
Rva00452D49Interface::Rva00452D49Interface()
{
}

// --- 0x003955A0 (15B, RET 4): when its argument is set, a tail call through
// the compiler's vcall thunk for virtual slot 10 (+0x28), the rowed
// ??_9@$BCI@AE at 0x001F34BA that the listener notifier member-pointer
// family (Rva0030C1FCNotifiers.cpp) also reaches. Spelled as that call
// through a constant member-function pointer; no xrefs, owner not recovered.
class Rva003955A0Listener
{
public:
	virtual void slot00();
	virtual void slot01();
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual void slot06();
	virtual void slot07();
	virtual void slot08();
	virtual void slot09();
	virtual void slot10(void *value);
	void rva003955A0(void *value);
};
void Rva003955A0Listener::rva003955A0(void *value)
{
	if (value)
		(this->*(&Rva003955A0Listener::slot10))(value);
}
