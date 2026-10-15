// cl: /O1 /DNDEBUG /MD /EHsc
// Legacy BFME1 donor placement at 41DFB has no victory-conditions identity:
// it allocates C4 bytes and calls ctor4CDCD, whose native body installs two
// unrelated vtables and constructs an array. GameEngine registers the actual
// VictoryConditions factory420353, allocating94 and calling ctor42017F.
// Preserve the verified legacy factory under an opaque address owner.
class Rva0004CDCD {
public:
    Rva0004CDCD();
    virtual ~Rva0004CDCD();
private:
    char m_storage[0xc0];
};
// The constructor 0x0004CDCD is rowed as ??0Rva004CE36; same 0xC4 allocation.
class Rva004CE36 {
public:
    Rva004CE36();
private:
    char m_storage[0xc4];
};
Rva0004CDCD *Rva00041DFBCreateOwner() { return (Rva0004CDCD *)new Rva004CE36; }

