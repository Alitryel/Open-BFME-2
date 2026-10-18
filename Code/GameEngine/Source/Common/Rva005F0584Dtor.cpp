// cl: /DNDEBUG /MD /EHsc
// ??1Rva005F0584@@QAE@XZ retail 0x005F0584 75B
// Non-virtual MI dtor reached through the thunk-reached scalar deleting dtor
// 0x005F06D3. Own vftables at +0 and +4; notifies the listener at +0x14
// through its slot 0 with this, then the two inline base dtors restore their
// vftables (0x00BC6F20 at +4, 0x00BFBCBC at +0).
class Rva005F0584;

class Rva005F0584Listener
{
public:
	virtual void onRelease(Rva005F0584 *owner);
};

class Rva005F0584Base0
{
public:
	virtual void rva005F0584Base0Slot();
	~Rva005F0584Base0() {}
};

class Rva005F0584Base1
{
public:
	virtual void rva005F0584Base1Slot();
	~Rva005F0584Base1() {}
};

class Rva005F0584 : public Rva005F0584Base0, public Rva005F0584Base1
{
public:
	~Rva005F0584();
	virtual void rva005F0584Base0Slot();
	virtual void rva005F0584Base1Slot();
private:
	char m_pad08[0x14 - 0x08];
	Rva005F0584Listener *m_listener; // +0x14
};

Rva005F0584::~Rva005F0584()
{
	if (m_listener)
		m_listener->onRelease(this);
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?rva005F0584Base0Slot@Rva005F0584@@UAEXXZ=__purecall")
#pragma comment(linker, "/alternatename:?rva005F0584Base0Slot@Rva005F0584Base0@@UAEXXZ=__purecall")
#pragma comment(linker, "/alternatename:?rva005F0584Base1Slot@Rva005F0584@@UAEXXZ=__purecall")
#pragma comment(linker, "/alternatename:?rva005F0584Base1Slot@Rva005F0584Base1@@UAEXXZ=??_GRva0007DF07@@UAEPAXI@Z")
