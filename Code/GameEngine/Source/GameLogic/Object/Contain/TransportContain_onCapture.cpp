// cl: /MD
// ?onCapture@TransportContain@@UAEXHH@Z @0x004672B7 99B: slot 9 Contain method with early-out plus flag-gated subobject virtuals.
// Evidence: slots 9 of six Contain vtables 0x00844278 0x00845C38 0x00845EB8 0x00846D28 0x008470F8 0x008474A0, ret 8 two args, flag byte at +0x1c8 bit 0x20 via +0x08, subobject at +0x20 slots 0x80 0x8c 0xa8 0xd8 0xe0.
// The +0x20 subobject is the interface TransportContain.cpp calls
// TransportConditionInterface (its slot 60 is 0x004673C0 per the constructor
// 0x00468559's secondary table); this file spells the same view so the body
// merges into TransportContain.cpp unchanged.

#define V(n) virtual void slot##n();
#define CSLOT(n) virtual void cslot##n();

class Object
{
public:
	unsigned char m_pad000[0x1C8];
	unsigned char m_flags1C8;	// bit 0x20 tested by onCapture
};

class TransportConditionInterface
{
public:
	CSLOT(00) CSLOT(01) CSLOT(02) CSLOT(03) CSLOT(04) CSLOT(05) CSLOT(06) CSLOT(07) CSLOT(08) CSLOT(09)
	CSLOT(10) CSLOT(11) CSLOT(12) CSLOT(13) CSLOT(14) CSLOT(15) CSLOT(16) CSLOT(17) CSLOT(18) CSLOT(19)
	CSLOT(20) CSLOT(21) CSLOT(22) CSLOT(23) CSLOT(24) CSLOT(25) CSLOT(26) CSLOT(27) CSLOT(28) CSLOT(29)
	CSLOT(30) CSLOT(31)
	virtual void cslot32(int);
	CSLOT(33) CSLOT(34)
	virtual void cslot35(int);
	CSLOT(36) CSLOT(37) CSLOT(38) CSLOT(39) CSLOT(40) CSLOT(41)
	virtual void cslot42(int);
	CSLOT(43) CSLOT(44) CSLOT(45) CSLOT(46) CSLOT(47) CSLOT(48) CSLOT(49)
	CSLOT(50) CSLOT(51) CSLOT(52) CSLOT(53)
	virtual bool cslot54();
	CSLOT(55)
	virtual int cslot56();
	CSLOT(57) CSLOT(58) CSLOT(59)
	virtual void rva004673C0() = 0;	// slot 60
};

class TransportContainPrimary
{
public:
	V(00) V(01) V(02) V(03) V(04) V(05) V(06) V(07) V(08)
	virtual void onCapture(int oldOwner, int newOwner);	// slot 9
protected:
	const void *m_moduleData;	// +0x04
	Object *m_object;			// +0x08
private:
	unsigned char m_pad0C[0x20 - 0x0C];
};

class TransportContain : public TransportContainPrimary, public TransportConditionInterface
{
public:
	virtual void onCapture(int oldOwner, int newOwner);
	virtual void rva004673C0();
};

void TransportContain::onCapture(int oldOwner, int newOwner)
{
	if (oldOwner == newOwner)
		return;
	if (m_object->m_flags1C8 & 0x20)
	{
		cslot42(0);
		return;
	}
	cslot32(2);
	if (cslot54())
	{
		if (cslot56() != newOwner)
			cslot35(2);
	}
}
