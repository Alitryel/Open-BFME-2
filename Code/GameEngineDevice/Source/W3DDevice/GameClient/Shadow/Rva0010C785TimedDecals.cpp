// cl: /O1 /G7 /arch:SSE /MD /EHs /DNDEBUG /Ireference/shims/bfmealloc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva0010BE72@Rva0010C785@@UAEXXZ @ 0x0010BE72 499B, ret
//
// Slot 1 of the projected-shadow manager vtable 0x007CF9C4 (see
// Rva0010C785Lifecycle.cpp); nothing else reaches it. Once per call it walks
// the decal list (+0x08) and then the shadow list (+0x04). Timed decals (type
// 0x400 or 0x800) past their end frame (+0x3C) are collected and released
// through Shadow vtable slot 2; the rest have their opacity faded in and out
// against the client frame using the frame and opacity values at
// +0x38 .. +0x54, through the rowed Shadow::setOpacity (0x003308F6).
//
// Donor: Open-BFME-1 W3DProjectedShadowManagerRva007B4620.cpp (BFME 1 retail
// 0x007B4620, slot 1 of that game's manager vtable), the same walk with the
// same field offsets. Target deltas read from retail: the projected shadow's
// list link sits at +0x114 (BFME 1: +0xD4), and the fade value rounds
// through the dllimport ceil (slot 0x00BBA578). The method name is
// address-derived; neither image names the slot. Each fade rounds the
// lerp through the <math.h> float ceil overload (ceil(float) -> ceilf ->
// the dllimport ceil): those two inline levels give retail's x87 pop order
// around the double argument store. The list's base constructor, destructor,
// clear and insert are the ICF-folded STLport pointer-list bodies, pinned
// with this unit as their fold proof. Those bodies free nodes with a direct
// call to _free (0x00030830), as /D_CRTIMP= gives the other units proving
// these folds, while ceil stays imported, so _CRTIMP is emptied only after
// <math.h>.

#include <math.h>
#undef _CRTIMP
#define _CRTIMP
#include <list>
// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper
// (retail keeps one _List_iterator_base::operator!=; BfmeAptScreenLanLobbyOnInitGadget.cpp pattern).
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

class GameClient
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot0A(); virtual void slot0B();
	virtual void slot0C(); virtual void slot0D(); virtual void slot0E(); virtual void slot0F();
	virtual void slot10(); virtual void slot11(); virtual void slot12(); virtual void slot13();
	virtual void slot14(); virtual void slot15(); virtual void slot16(); virtual void slot17();
	virtual void slot18(); virtual void slot19(); virtual void slot1A(); virtual void slot1B();
	virtual void slot1C(); virtual void slot1D(); virtual void slot1E();
	virtual UnsignedInt getFrame();
};
extern GameClient *TheGameClient;

class Shadow
{
public:
	virtual void vslot00(void);
	virtual void vslot04(void);
	virtual void release(void);
	void setOpacity(Int value);

	unsigned char m_pad04[0x30];
	UnsignedInt m_type;
	UnsignedInt m_value38;
	UnsignedInt m_value3C;
	UnsignedInt m_value40;
	UnsignedInt m_value44;
	UnsignedInt m_value48;
	UnsignedInt m_value4C;
	UnsignedInt m_value50;
	UnsignedInt m_value54;
};

class W3DProjectedShadow : public Shadow
{
public:
	unsigned char m_pad58[0x114 - 0x58];
	W3DProjectedShadow *m_next;		// +0x114
};

class Rva0010C785
{
public:
	virtual ~Rva0010C785();
	virtual void rva0010BE72(void);

private:
	W3DProjectedShadow *m_shadowList;	// +0x04
	W3DProjectedShadow *m_decalList;	// +0x08
};

void Rva0010C785::rva0010BE72(void)
{
	_STL::list<W3DProjectedShadow *> expired;
	UnsignedInt frame = TheGameClient->getFrame();

	for (Int i = 0; i <= 1; ++i)
	{
		for (W3DProjectedShadow *shadow = i ? m_shadowList : m_decalList; shadow; shadow = shadow->m_next)
		{
			if (shadow->m_type == 0x400 || shadow->m_type == 0x800)
			{
				if (shadow->m_value3C <= frame)
					expired.push_back(shadow);
				else
				{
					UnsignedInt value38 = shadow->m_value38;
					UnsignedInt value40 = shadow->m_value40;
					UnsignedInt value44 = shadow->m_value44;
					UnsignedInt value48 = shadow->m_value48;
					UnsignedInt value4C = shadow->m_value4C;
					UnsignedInt value50 = shadow->m_value50;
					UnsignedInt value54 = shadow->m_value54;
					if (frame < value38)
						shadow->setOpacity(0);
					else if (frame < value44)
					{
						double from = value40;
						shadow->setOpacity(fast_float2long_round(ceil((float)(from + (Real)(frame - value38) / (Real)(value44 - value38) * (value48 - from)))));
					}
					else if (frame < value4C)
						shadow->setOpacity(value48);
					else if (frame < value50)
					{
						double from = value48;
						shadow->setOpacity(fast_float2long_round(ceil((float)(from + (Real)(frame - value4C) / (Real)(value50 - value4C) * (value54 - from)))));
					}
					else
						shadow->setOpacity(value54);
				}
			}
		}
	}

	for (_STL::list<W3DProjectedShadow *>::iterator it = expired.begin(); it != expired.end(); ++it)
		(*it)->release();

	expired.clear();
}
