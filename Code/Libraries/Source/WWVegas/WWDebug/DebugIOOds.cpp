// cl: /DNDEBUG /MD /EHa
//
// ??0DebugIOOds@@QAE@XZ, retail 0x0003F380 (70 bytes), plus the
// ??_GDebugIOOds@@UAEPAXI@Z scalar deleting destructor at 0x0003F430
// (33 bytes). The implicit ??1DebugIOOds@@UAE@XZ at 0x0003F460
// and its unwind action are rowed from this unit too.
//
// Ported from Open-BFME-1
// Code/Libraries/Source/WWVegas/WWDebug/Rva0088FAA0DebugIOOdsDestructor.cpp:
// same memberless two-vtable DebugIO hierarchy (DebugIOOds::Create already
// landed from DebugIOOds_Create.cpp, so the factory is left out here). The
// Rva0088FAA0 names in the donor are the port's guess-labels for this class;
// retail owns it as DebugIOOds (Create/Write rows + upstream debug_io_ods.h).
// Same implicit-dtor shape as ??1DebugCmdInterfaceDebug at 0x00039980
// (the ambiguous twin that differs only in the vtable constant); the ctor
// is the 70B two-store EH shape of ??0DebugCmdInterfaceDebug.

class Debug;
class DebugIOInterface
{
protected:
    virtual ~DebugIOInterface(void) {}

public:
    DebugIOInterface(void) {}
    enum StringType { Assert = 0, Check, Log, Crash, Exception, CmdReply, StructuredCmdReply, Other, MAX };
    virtual int Read(char *, int) = 0;
    virtual void Write(StringType, const char *, const char *) = 0;
    virtual void EmergencyFlush(void) = 0;
    virtual void Execute(Debug &, const char *, bool, unsigned, const char *const *) = 0;
    virtual void Delete(void) = 0;
};

// The base deleting destructor is frameless; the derived native bodies retain EBP,
// as in the existing DebugIONetPipeDestructorThunk.cpp compiler boundary.
#pragma optimize("y", off)

class DebugIOOds : public DebugIOInterface
{
public:
    explicit DebugIOOds(void);
    virtual int Read(char *, int) { return 0; }
    virtual void Write(StringType, const char *, const char *);
    virtual void EmergencyFlush(void) {}
    virtual void Execute(Debug &, const char *, bool, unsigned, const char *const *) {}
    virtual void Delete(void);
};

// ??0DebugIOOds@@QAE@XZ
inline DebugIOOds::DebugIOOds(void)
{
}

// ?Delete@DebugIOOds@@UAEXXZ absent-from-retail
void DebugIOOds::Delete(void)
{
    this->~DebugIOOds();
}

// Preserve the inline constructor emitted by its factory consumers.
#pragma inline_depth(0)
// ?_bfmeDebugIOOdsInlineAnchor absent-from-retail
void _bfmeDebugIOOdsInlineAnchor(DebugIOOds *io)
{
    io->DebugIOOds::DebugIOOds();
}
#pragma inline_depth()
