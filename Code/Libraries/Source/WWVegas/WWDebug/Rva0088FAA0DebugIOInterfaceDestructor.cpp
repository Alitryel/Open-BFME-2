// cl: /DNDEBUG /MD /EHa
//
// ??_GDebugIOInterface@@MAEPAXI@Z, retail 0x0003F340 (31 bytes).
//
// Base-class scalar deleting destructor of the DebugIOOds hierarchy
// (derived bodies live in Rva0088FAA0DebugIOOdsDestructor.cpp). The trivial
// inline dtor folds to a vtable store plus operator delete, and the body is
// frameless: this TU builds without /Oy-, unlike the derived /Oy- TU. The
// Rva0088FAA0Interface name in the BFME1 donor is the port's guess-label;
// retail owns the base as DebugIOInterface (upstream debug_io.h).

class DebugIOInterface
{
protected:
    virtual ~DebugIOInterface(void) {}

public:
    explicit DebugIOInterface(void) {}
    virtual int Read(char *, int) = 0;
    virtual void Write(int, const char *, const char *) = 0;
    virtual void EmergencyFlush(void) = 0;
    virtual void Execute(void) = 0;
    virtual void Delete(void) = 0;
};

// The constructor is inline in Zero Hour's debug_io.h, so every unit that
// builds a DebugIO emits it as a select-any copy; a plain definition here
// collided with each of them. Constructing the base is what makes this unit
// emit the vftable and the deleting destructor row, so the anchor below keeps
// one out-of-line call. It is not retail code.
#pragma inline_depth(0)
// ?_bfmeDebugIOInterfaceAnchor@@YAXPAVDebugIOInterface@@@Z absent-from-retail
void _bfmeDebugIOInterfaceAnchor(DebugIOInterface *io)
{
    io->DebugIOInterface::DebugIOInterface();
}
#pragma inline_depth()
