// cl: /DNDEBUG /MD /EHsc
// Copy constructors split from V3PolyDeferredCopyCtors.cpp: their classes'
// destructors are still unprovided (0x0015E640 awaits its
// SimpleDynVecClass<Vector3> identity; 0x0028C62B/0x0028F68F the DamageInfo class
// reconciliation), so they stay out of the unit that now links.

typedef int Int;
typedef short Short;
#include "../../Include/Common/Rva0028C6D6.h"

// ---- vptr + two ints base plus derived vptr and third int (retail 0x0015E640)
// B2 body-address name: the base copy inlines (vptr 0xBC6F44 with +0x04/+0x08)
// then the derived part installs vptr 0xBC6F50 and copies +0x0C. The outlined
// base is retail 0x0015E0D0. One retail E8 caller at 0x0016855F.
class Rva0015E640Base
{
public:
	Rva0015E640Base(const Rva0015E640Base &other)
	{
		m_field04 = other.m_field04;
		m_field08 = other.m_field08;
	}
	virtual ~Rva0015E640Base();

	Int m_field04;
	Int m_field08;
};

class Rva0015E640 : public Rva0015E640Base
{
public:
	Rva0015E640(const Rva0015E640 &other);
	Rva0015E640 &operator=(const Rva0015E640 &other);
	virtual ~Rva0015E640();

	Int m_field0C;
};

Rva0015E640::Rva0015E640(const Rva0015E640 &other)
	: Rva0015E640Base(other)
{
	m_field0C = other.m_field0C;
}

// Retail 0x0015E670 (27 bytes), the matching assignment: the three fields after the vptr.
// Select-any like the copy in Rva001684D6Assign.cpp (this retail body comes first
// in link order, so it is the copy the link keeps); the anchor keeps the body emitted.
inline Rva0015E640 &Rva0015E640::operator=(const Rva0015E640 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	return *this;
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva0015E640Assign@@YAXPAVRva0015E640@@ABV1@@@Z absent-from-retail
void bfmeEmitRva0015E640Assign(Rva0015E640 *p, const Rva0015E640 &o)
{
	p->Rva0015E640::operator=(o);
}

// ----------------- vptr + twenty-three ints + three bytes (retail 0x0028C62B)
// B2 body-address name: seven dwords +0x04..+0x1C then bytes +0x20/+0x21 then
// ten dwords +0x24..+0x48 then byte +0x4C then six dwords +0x50..+0x64.
// Sits directly before 0x0028C6D6 and the retail caller 0x0028F6A4 builds
// both subobjects in one tail.
class Rva0028C62B
{
public:
	Rva0028C62B(const Rva0028C62B &other);
	virtual ~Rva0028C62B();

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	char m_field20;
	char m_field21;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
	Int m_field38;
	Int m_field3C;
	Int m_field40;
	Int m_field44;
	Int m_field48;
	char m_field4C;
	Int m_field50;
	Int m_field54;
	Int m_field58;
	Int m_field5C;
	Int m_field60;
	Int m_field64;
};

Rva0028C62B::Rva0028C62B(const Rva0028C62B &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
	m_field1C = other.m_field1C;
	m_field20 = other.m_field20;
	m_field21 = other.m_field21;
	m_field24 = other.m_field24;
	m_field28 = other.m_field28;
	m_field2C = other.m_field2C;
	m_field30 = other.m_field30;
	m_field34 = other.m_field34;
	m_field38 = other.m_field38;
	m_field3C = other.m_field3C;
	m_field40 = other.m_field40;
	m_field44 = other.m_field44;
	m_field48 = other.m_field48;
	m_field4C = other.m_field4C;
	m_field50 = other.m_field50;
	m_field54 = other.m_field54;
	m_field58 = other.m_field58;
	m_field5C = other.m_field5C;
	m_field60 = other.m_field60;
	m_field64 = other.m_field64;
}

// ---- vptr + two member subobject copies (retail 0x0028F68F)
// B2 body-address name: member at +0x04 copies with the rowed 171B body and
// member at +0x6C with the rowed 33B body. Both member copies are pure
// stores, so the compiler proves nothrow and stays frameless with two
// outlined calls, exactly like retail. (The E8 sites sit 21/33 bytes in;
// the row names the C9-C3 boundary, not the call sites.)
class Rva0028F68F
{
public:
	Rva0028F68F(const Rva0028F68F &other);
	virtual ~Rva0028F68F();

	Rva0028C62B m_member04;
	Rva0028C6D6 m_member6C;
};

Rva0028F68F::Rva0028F68F(const Rva0028F68F &other)
	: m_member04(other.m_member04)
	, m_member6C(other.m_member6C)
{
}
