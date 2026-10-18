// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc
// ??1Rva0030C1FCOwner@@UAE@XZ, retail 0x0030C40A..0x0030C4A6 (156 bytes,
// EH): the base-object destructor of the owner whose broadcast slots
// Rva0030C1FCNotifiers.cpp rows; sibling of Rva0030CAA9OwnerDtor.cpp. It
// installs its tables (0x00C088FC at +0, 0x00C088E0 on the shared virtual
// base behind its vtordisp), tells every listener through slot 0 (the
// generic vcall thunk), and then its parts die: the +0x68 buffer
// (GameFree), the four AsciiStrings at +0x40 (eh vector destructor
// iterator), the listener list -- a second base at +0x30, as retail's
// null-checked unwind conversion shows -- and the primary base (destructor
// body 0x00538133, pinned under the same virtual-dtor view). The unwind
// funclets reach the list and buffer destructors through the shared
// free-first-pointer body 0x0007FAB3. The virtual base sits at +0x90.
#include "ascii_string.h"

void __cdecl Rva00030830GameFree(void *);

class VBase00C6EE28
{
public:
	virtual void s0() = 0;
	~VBase00C6EE28() {}
};

// The slot-0 virtual of the primary base: retail's table holds this owner's
// destructor there (0x00C088FC slot 0 is the rowed ??_G), so declare the root's
// phantom slot as its destructor instead of the undefined placeholder s1;
// Rva0053805DBase then overrides it, and the unresolved name disappears.
class Rva00538133Root
{
public:
	virtual ~Rva00538133Root();
private:
	unsigned char m_pad04[0x18 - 4];
};

class Rva0053805DBase : public Rva00538133Root, public virtual VBase00C6EE28
{
public:
	virtual ~Rva0053805DBase();
	virtual void s0();
private:
	unsigned char m_pad1C[0x30 - 0x1C];
};

class Rva0030C1FCOwner;

class Rva0030C1FCListener
{
public:
	virtual void notify00(Rva0030C1FCOwner *owner);
};

class Rva0030C185List
{
public:
	~Rva0030C185List() { if (m_begin) Rva00030830GameFree(m_begin); }
	void forEach(void (Rva0030C1FCListener::*notify)(Rva0030C1FCOwner *), Rva0030C1FCOwner *owner);
private:
	Rva0030C1FCListener **m_begin;
	Rva0030C1FCListener **m_end;
	Rva0030C1FCListener **m_capacity;
	unsigned int m_index;
};

struct Rva0030C40ABuffer
{
	~Rva0030C40ABuffer() { if (m_data) Rva00030830GameFree(m_data); }
	void *m_data;
};

class Rva0030C1FCOwner : public Rva0053805DBase, public Rva0030C185List
{
public:
	virtual ~Rva0030C1FCOwner();
	// 0x0030C1FC is rowed as Rva0030C1FCOwner::rva0030C1FC
	// (Rva0030C1FCNotifiers.cpp, the vcall-thunk broadcast slot): the placeholder
	// virtual-base override s0 is that row's call, so bind it to the rowed name.
	virtual void s0() { rva0030C1FC(); }
	void rva0030C1FC();
private:
	AsciiString m_records[4];		// +0x40
	unsigned char m_pad50[0x68 - 0x50];
	Rva0030C40ABuffer m_buffer68;		// +0x68
	unsigned char m_pad6C[0x8C - 0x6C];
};

Rva0030C1FCOwner::~Rva0030C1FCOwner()
{
	forEach(&Rva0030C1FCListener::notify00, this);
}
