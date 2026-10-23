// cl: /O1 /arch:SSE /G7 /MD
// Native constructor 0x00740E78..0x00740E85. The original derived class name,
// complete size and pure-virtual signatures are not recovered; this view
// describes only the observed eight-byte base prefix and three vtable slots.
// Its table at VA 0x00CF1630 holds the deleting destructor at 0x00740E85,
// then _purecall twice. The deleting destructor calls the existing virtual
// base destructor at 0x004102A4, which installs the one-slot base table
// 0x00C3962C. The independently matched base constructor at 0x00410297
// establishes the -1 field initializer. Its source view is reused below.
// Keeping the real empty base destructor visible makes the derived destructor
// emit the same full seven bytes, including the base vtable relocation. Retail
// folds them at 0x004102A4; its deleting wrapper still makes that direct call.
class Rva0045EF90Base
{
public:
    Rva0045EF90Base() : m_base((unsigned)-1) {}
    virtual ~Rva0045EF90Base() {}
protected:
    unsigned m_base;
};

class Rva00740E78 : public Rva0045EF90Base
{
public:
    Rva00740E78();
    virtual ~Rva00740E78() {}
    // Opaque slots: only their purecall entries are established. No calls
    // through these provisional signatures are made by this source.
    virtual void unknownSlot04() = 0;
    virtual void unknownSlot08() = 0;
};

Rva00740E78::Rva00740E78()
{
}
