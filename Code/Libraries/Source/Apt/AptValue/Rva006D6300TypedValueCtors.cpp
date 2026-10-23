// cl: /O1 /DNDEBUG /MD
// Two pass-through Apt value constructors with one shape: construct the
// AptValue base through the rowed single-int constructor 0x006DCCC0 with the
// caller's type code, then install the derived vtable.
//
// ??0Rva006D6300Value@@QAE@H@Z  @0x006D6300 25B  vtable 0x00CE8BA0
// ??0Rva006D6320Value@@QAE@H@Z  @0x006D6320 25B  vtable 0x00CEA1EC
//
// Neither class has a recovered name; both are address-derived. The base
// spelling follows AptScalarValueConstructors.cpp.

class BfmeAptValue006DCD20
{
    virtual void vtableSlot0();
    unsigned int m_flags;
public:
    BfmeAptValue006DCD20(int type);
};

class Rva006D6300Value : public BfmeAptValue006DCD20
{
public:
    Rva006D6300Value(int type);
    virtual void vtableSlot0();
};

Rva006D6300Value::Rva006D6300Value(int type) : BfmeAptValue006DCD20(type)
{
}

class Rva006D6320Value : public BfmeAptValue006DCD20
{
public:
    Rva006D6320Value(int type);
    virtual void vtableSlot0();
};

Rva006D6320Value::Rva006D6320Value(int type) : BfmeAptValue006DCD20(type)
{
}

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?vtableSlot0@Rva006D6300Value@@UAEXXZ=?AddRef@AptValue@@UAEXXZ")
#pragma comment(linker, "/alternatename:?vtableSlot0@Rva006D6320Value@@UAEXXZ=?AddRef@AptValue@@UAEXXZ")
