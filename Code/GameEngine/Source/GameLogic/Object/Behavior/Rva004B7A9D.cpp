// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD
//
// ?upgradeImplementation@Rva004B7A9D@@QAEXXZ, retail 0x004B7A9D, 62 bytes.
// Chain from Drawable 0x00274C88: get Drawable via Thing at this-8 then
// push AsciiStrings at base+0x118 and +0x11C via rowed 0x002793AF and
// rowed 0x00274C88 then set global g_bfmeWorldRV +0x28 to 1.
// Evidence: caller none plus callees rowed getDrawable 0x005508E2 plus
// rowed 0x002793AF plus rowed 0x00274C88 plus global g_bfmeWorldRV.
//
#include "ascii_string.h"

class Thing
{
public:
	class Drawable *getDrawable() const;
};

class Drawable
{
public:
	void rva00274C88(AsciiString *src);
};

class Rva002793AF
{
public:
	void rva002793AF(const AsciiString &name);
};

struct BfmeWorldRV
{
	unsigned char m_pad[0x28];
	unsigned char m_28;
};

extern class ControlBar *TheControlBar;

class Rva004B7A9D
{
public:
	void upgradeImplementation();
};

void Rva004B7A9D::upgradeImplementation()
{
	Thing *thing = *(Thing **)((char *)this - 8);
	Drawable *drawable = thing->getDrawable();
	if (drawable != 0) {
		((Rva002793AF *)drawable)->rva002793AF(*(const AsciiString *)(*(char **)((char *)this - 0xC) + 0x118));
		drawable->rva00274C88((AsciiString *)(*(char **)((char *)this - 0xC) + 0x11C));
	}
	(*(BfmeWorldRV **)&TheControlBar)->m_28 = 1;
}
