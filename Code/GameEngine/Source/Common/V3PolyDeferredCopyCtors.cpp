// cl: /DNDEBUG /MD /EHsc
// Copy/holder owners awaiting their destructor or vtable providers.
// Partitioned intact from V3PolyCopyCtors.cpp so independent owners can link.

typedef int Int;
typedef short Short;
#include "../../Include/Common/Rva0028C6D6.h"

// Retail RVA 0x003AE20D, 93 bytes.
// Rva005EA0D0 copy constructor: vptr plus thirteen scalar dwords (0x38).
// Ported from Open-BFME-1 V3PolyCopyCtors.cpp, which documents the family:
// the class identity is not recovered, so the B1 body-address name carries
// over; the vptr dword is a DIR32 site the gate takes from the target.
// /O1, not the base /O2: the one-int sibling below needs the size-optimizer
// scratch choice (mov ecx,[ecx+4], not edx), and the thirteen-int body is
// identical under both.

class Rva005EA0D0
{
public:
	Rva005EA0D0(const Rva005EA0D0 &other);
	virtual ~Rva005EA0D0();

	Int m_field04;
	Int m_field08;
	Int m_field0C;
	Int m_field10;
	Int m_field14;
	Int m_field18;
	Int m_field1C;
	Int m_field20;
	Int m_field24;
	Int m_field28;
	Int m_field2C;
	Int m_field30;
	Int m_field34;
};

Rva005EA0D0::Rva005EA0D0(const Rva005EA0D0 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
	m_field10 = other.m_field10;
	m_field14 = other.m_field14;
	m_field18 = other.m_field18;
	m_field1C = other.m_field1C;
	m_field20 = other.m_field20;
	m_field24 = other.m_field24;
	m_field28 = other.m_field28;
	m_field2C = other.m_field2C;
	m_field30 = other.m_field30;
	m_field34 = other.m_field34;
}

// ------------------------------------ vptr + one int (retail 0x003AE07D)
// B2 body-address name: B1 holds two identical one-int classes, so no B1
// name is justified for this body.
// Its default constructor is retail 0x003A5773 (17 bytes): the same vtable
// 0x00C1B568 and a 0.0f store to +4. The vtable's DoXfer (0x003A578A)
// transfers +4 as a float, so the dword is a Real the copy moves raw.
class Rva003AE07D
{
public:
	Rva003AE07D();
	Rva003AE07D(const Rva003AE07D &other);
	virtual ~Rva003AE07D();

	union
	{
		Int m_field04;
		float m_real04;
	};
};

Rva003AE07D::Rva003AE07D() : m_real04(0.0f)
{
}

Rva003AE07D::Rva003AE07D(const Rva003AE07D &other)
{
	m_field04 = other.m_field04;
}

// ------------------------- vptr + two ints + a byte (retail 0x003AE315)
// B2 body-address name: B1's Rva005EA240 has this shape but is a different
// class (different vtable), so the B2 address names the body.
class Rva003AE315
{
public:
	Rva003AE315(const Rva003AE315 &other);
	virtual ~Rva003AE315();

	Int m_field04;
	Int m_field08;
	char m_field0C;
};

Rva003AE315::Rva003AE315(const Rva003AE315 &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
}

// ------------------------- vptr + three ints (retail 0x00318B5C)
// B2 body-address name: same head as the 33-byte pair but the +0x0C member
// is a dword (8B49/8948) not a byte. Retail caller 0x00318D6F guards on
// null then tail-calls into this body.
class Rva00318B5C
{
public:
	Rva00318B5C(const Rva00318B5C &other);
	virtual ~Rva00318B5C();

	Int m_field04;
	Int m_field08;
	Int m_field0C;
};

// Select-any like the other TU's copy (this retail body comes first in link
// order, so it is the copy the link keeps); the anchor keeps the body emitted.
inline Rva00318B5C::Rva00318B5C(const Rva00318B5C &other)
{
	m_field04 = other.m_field04;
	m_field08 = other.m_field08;
	m_field0C = other.m_field0C;
}

// Retain the inline body's ledger emission without changing its callers.
// ?bfmeEmitRva00318B5CCopy@@YAXPAVRva00318B5C@@ABV1@@@Z absent-from-retail
void bfmeEmitRva00318B5CCopy(Rva00318B5C *p, const Rva00318B5C &o)
{
	p->Rva00318B5C::Rva00318B5C(o);
}

// Retail 0x00318D63 (18B): null-guarded copy-construct of one Rva00318B5C
// (vptr + three ints, 0x10 bytes) via its rowed copy ctor. Callers are the
// 0x10-stride loops at 0x00318D83 0x00318DAE 0x00319FAD 0x0031A13B.
inline void *__cdecl operator new(unsigned int, void *p) { return p; }
inline void __cdecl operator delete(void *, void *) {}
void Rva00318D63Copy(Rva00318B5C *dest, const Rva00318B5C &src)
{
	if (dest)
		new (dest) Rva00318B5C(src);
}

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

// ---- vptr + two ints base plus derived vptr and third int (retail 0x00168040)
// B2 body-address name: same inlined-base shape as 0x0015E640 with vtables
// 0xBD41AC/0xBD41B8. One retail E8 caller at 0x00168571.
class Rva00168040Base
{
public:
	Rva00168040Base(const Rva00168040Base &other)
	{
		m_field04 = other.m_field04;
		m_field08 = other.m_field08;
	}
	virtual ~Rva00168040Base();

	Int m_field04;
	Int m_field08;
};

class Rva00168040 : public Rva00168040Base
{
public:
	Rva00168040(const Rva00168040 &other);
	virtual ~Rva00168040();

	Int m_field0C;
};

Rva00168040::Rva00168040(const Rva00168040 &other)
	: Rva00168040Base(other)
{
	m_field0C = other.m_field0C;
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

// ------------------------- vptr + held pointer (retail 0x005CB22A)
// B2 body-address name: the +0x04 member takes the argument pointer itself
// (89 48 04 with no dereference) so this keeps rather than copies. The held
// type is not recovered so it is void. Retail caller 0x00572C5F installs a
// derived vptr right after the call. Six retail E8 callers.
class Rva005CB22A
{
public:
	Rva005CB22A(void *held);
	virtual ~Rva005CB22A();

	void *m_field04;
};

Rva005CB22A::Rva005CB22A(void *held)
{
	m_field04 = held;
}

// Retail RVA 0x005DAA48 (18B). Address name: only the pointer-hold
// constructor shape and its distinct vtable are established by the target.
struct Rva005DAA48Base
{
	Rva005DAA48Base(void *held) { m_field04 = held; }
	void *m_field04;
};

class Rva005DAA48 : public Rva005DAA48Base
{
public:
	Rva005DAA48(void *held);
	virtual ~Rva005DAA48();
};

Rva005DAA48::Rva005DAA48(void *held)
	: Rva005DAA48Base(held)
{
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

// ------------------------- vptr + held pointer (retail 0x005DAA5A 18B)
// B2 body-address name: same holder shape as 0x005DAA36 with a different
// vtable (0x008765A0) so a different class. Caller 0x005971A9.
struct Rva005DAA5A_Hold
{
	Rva005DAA5A_Hold(void *held) { m_field04 = held; }
	void *m_field04;
};

class Rva005DAA5A : public Rva005DAA5A_Hold
{
public:
	Rva005DAA5A(void *held);
	virtual ~Rva005DAA5A();
};

Rva005DAA5A::Rva005DAA5A(void *held)
	: Rva005DAA5A_Hold(held)
{
}
