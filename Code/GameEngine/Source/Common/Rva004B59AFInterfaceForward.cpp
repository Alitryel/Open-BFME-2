// cl: /O1 /arch:SSE /G7 /MD
// ?rva004B59AF@Rva004B59AF@@QAEXXZ, retail 0x004B59AF (8 bytes): forward to
// virtual slot 8 of the interface subobject at +0x10 as a tail jump. The
// owner and the slot's identity are not established; names are
// address-derived.
class Rva004B59AFInterface
{
public:
	virtual void v0(); virtual void v1(); virtual void v2(); virtual void v3();
	virtual void v4(); virtual void v5(); virtual void v6(); virtual void v7();
	virtual void slot8();
};

class Rva004B59AF
{
public:
	void rva004B59AF();
private:
	Rva004B59AFInterface *iface() { return (Rva004B59AFInterface *)m_iface; }
	char m_pad00[0x10];
	char m_iface[4];	// +0x10, polymorphic subobject
};

void Rva004B59AF::rva004B59AF()
{
	iface()->slot8();
}
