// cl: /DNDEBUG /MD /EHa /Oy-
// readable body of ??0DebugIONet@@QAE@XZ: Code/Libraries/Source/WWVegas/WWDebug/debug_io_net.cpp
// Open-BFME: empty DebugIONet ctor. Inlines the DebugIOInterface vtable
// store, then stores the derived vtable, with the EH state around the
// derived store because the base has a virtual destructor.

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_io.h
// Full DebugIOInterface view (debug_io.h order), as DebugIONetPipeDestructorThunk.cpp
// declares it: every unit then emits the same DebugIOInterface/DebugIONet vftables.
class Debug;
class DebugIOInterface
{
protected:
	virtual ~DebugIOInterface() {}

public:
	DebugIOInterface() {}
	enum StringType { Assert = 0, Check, Log, Crash, Exception, CmdReply, StructuredCmdReply, Other, MAX };
	virtual int Read(char *buf, int maxchar) = 0;
	virtual void Write(StringType type, const char *src, const char *str) = 0;
	virtual void EmergencyFlush(void) = 0;
	virtual void Execute(class Debug &dbg, const char *cmd, bool structuredCmd, unsigned argn, const char *const *argv) = 0;
	virtual void Delete(void) = 0;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/internal_io.h
class DebugIONet : public DebugIOInterface
{
public:
	explicit DebugIONet(void);
	virtual ~DebugIONet();
	virtual int Read(char *buf, int maxchar);
	virtual void Write(StringType type, const char *src, const char *str);
	virtual void EmergencyFlush(void);
	virtual void Execute(class Debug &dbg, const char *cmd, bool structuredCmd, unsigned argn, const char *const *argv);
	virtual void Delete(void);
};

// ??0DebugIONet@@QAE@XZ
inline DebugIONet::DebugIONet(void)
{
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeDebugIONetInlineAnchor@@YAXPAVDebugIONet@@@Z absent-from-retail
void _bfmeDebugIONetInlineAnchor(DebugIONet *debugIONet)
{
    debugIONet->DebugIONet::DebugIONet();
}
#pragma inline_depth()
