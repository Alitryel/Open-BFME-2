// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva000F8348@@QAE@XZ, retail 0x000F8348 (83 bytes). Default constructor
// of the static screen-filter object at 0x00DEC018: its only caller is the
// dynamic initializer 0x007AC8B0 (mov ecx,0x00DEC018; call; atexit), and it
// installs vtable 0x00BCF254, whose slots are the filter bodies rowed as
// Rva000F6D56Filter::preRender, Rva007D6B70::set/reset/shutdown and
// Rva007DB820::init/shutdown. Layout from the stores: vptr, ints +0x04..
// +0x0C, two texture handles +0x10/+0x14, ints +0x18/+0x1C, three floats
// +0x20..+0x28 zeroed through xmm0, an int vector at +0x2C (the rowed
// _Vector_base<int> ctor 0x00211E58 with a stack allocator temp) and ints
// +0x38..+0x44. Structural inference: the 0x000F82F5 destructor just before
// (Rva000F82F5Dtor.cpp: +0x2C buffer, +0x14/+0x10 texture handles) tears
// down the same layout. Built without EH (retail has no frame). Names
// address-derived.
#include <vector>
class TextureClass;
class Rva000F8348TextureHandle
{
public:
	Rva000F8348TextureHandle() : m_texture(0) {}
	TextureClass *m_texture;
};
class Rva000F8348
{
public:
	Rva000F8348();
	virtual int init();
private:
	int m_04;
	int m_08;
	int m_0C;
	Rva000F8348TextureHandle m_texture10;
	Rva000F8348TextureHandle m_texture14;
	int m_18;
	int m_1C;
	float m_20;
	float m_24;
	float m_28;
	_STL::vector<int> m_2C;
	int m_38;
	int m_3C;
	int m_40;
	int m_44;
};
Rva000F8348::Rva000F8348() :
	m_04(0), m_08(0), m_0C(0), m_18(0), m_1C(0), m_20(0.0f), m_24(0.0f), m_28(0.0f),
	m_38(0), m_3C(0), m_40(0), m_44(0)
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?init@Rva000F8348@@UAEHXZ=?rva000F6D4F@Rva000F6D4F@@QAEHXZ")
