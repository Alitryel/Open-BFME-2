// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Receiver-adjust forwarders into rowed STLport vector members: add ecx,
// imm8 then a tail jump, stack arguments passed through (skeleton of
// ??1PlayerPosition 0x0022D920). The vector members are only declared so
// the calls stay out of line as in retail; owners are unresolved and
// address-named, element types are the ledger's stand-ins for those rows.
#include <vector>
#include "../../../Include/Lib/BfmeE16.h"

struct Rva00318203Element { int a[2]; };

namespace _STL {
template <> BfmeE16 &vector<BfmeE16>::operator[](vector<BfmeE16>::size_type);
template <> void vector<Rva00318203Element>::push_back(const Rva00318203Element &);
}

// --- 0x0030BC01 (8B): +0x68 then vector<BfmeE16>::operator[] 0x00567B4D.
class Rva0030BC01
{
public:
	BfmeE16 &rva0030BC01(unsigned int index);
private:
	char m_pad00[0x68];
	_STL::vector<BfmeE16> m_68;
};
BfmeE16 &Rva0030BC01::rva0030BC01(unsigned int index)
{
	return m_68[index];
}

// --- 0x0031823A (8B): +0x24 then vector<Rva00318203Element>::push_back
// 0x00318203.
class Rva0031823A
{
public:
	void rva0031823A(const Rva00318203Element &value);
private:
	char m_pad00[0x24];
	_STL::vector<Rva00318203Element> m_24;
};
void Rva0031823A::rva0031823A(const Rva00318203Element &value)
{
	m_24.push_back(value);
}
