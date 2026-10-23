// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0Rva000F9C3C@@QAE@XZ, retail 0x000F9C3C (97 bytes). Default constructor
// of the static object at VA 0x00DEC080: its only caller is the dynamic
// initializer 0x007AC8E0 (Rva007ABBB3CtorInits.cpp: construct, then atexit
// 0x007B6EC2 -> the rowed destructor 0x000F9BD7). It installs vtable
// 0x00BCF270, the slot after the screen filter 0x000F8348's 0x00BCF254, and
// has that filter's layout plus a second buffer: vptr, ints +0x04..+0x0C,
// two texture handles +0x10/+0x14, ints +0x18/+0x1C, three floats
// +0x20..+0x28 zeroed through xmm0, vectors at +0x2C and +0x38 (the rowed
// _Vector_base ctor 0x00211E58 with a stack allocator temp each) and ints
// +0x44..+0x50. Target facts: the stores and calls above, and the
// destructor 0x000F9BD7 freeing the +0x38/+0x2C buffers and releasing the
// +0x14/+0x10 texture handles. Structural inference: the element type of
// the two vectors (int here; the ctor body is shared by every _Vector_base
// instantiation) and the vtable slot (declared only to give the class its
// vptr). Built without EH (retail has no frame). Names address-derived.
#include <vector>
class TextureClass;
class Rva000F9C3CTextureHandle
{
public:
	Rva000F9C3CTextureHandle() : m_texture(0) {}
	TextureClass *m_texture;
};
class Rva000F9C3C
{
public:
	Rva000F9C3C();
	virtual int slot0();
private:
	int m_04;
	int m_08;
	int m_0C;
	Rva000F9C3CTextureHandle m_texture10;
	Rva000F9C3CTextureHandle m_texture14;
	int m_18;
	int m_1C;
	float m_20;
	float m_24;
	float m_28;
	_STL::vector<int> m_2C;
	_STL::vector<int> m_38;
	int m_44;
	int m_48;
	int m_4C;
	int m_50;
};
Rva000F9C3C::Rva000F9C3C() :
	m_04(0), m_08(0), m_0C(0), m_18(0), m_1C(0), m_20(0.0f), m_24(0.0f), m_28(0.0f),
	m_44(0), m_48(0), m_4C(0), m_50(0)
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?slot0@Rva000F9C3C@@UAEHXZ=?init@Rva007DB820@@QAEHXZ")
