// cl: /DNDEBUG /MD /EHa
// Open-BFME: Debug I/O net destructor. Stores the net vtable, CloseHandle on
// the pipe at +4 unless it is INVALID_HANDLE_VALUE, then restores the
// DebugIOInterface vtable.

typedef void *HANDLE;

extern "C" __declspec(dllimport) int __stdcall CloseHandle(HANDLE handle);

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug/debug_io.h
class Debug;
// Retail's base deleting destructor uses the default frameless codegen.
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

// The derived destructor and its EH graph retain their retail frame pointer.
#pragma optimize("y", off)

class DebugIONet : public DebugIOInterface
{
	HANDLE m_pipe;

public:
	virtual ~DebugIONet();
	// Rowed in debug_io_net.cpp; declared so this unit's vftable is DebugIONet's.
	virtual int Read(char *buf, int maxchar);
	virtual void Write(StringType type, const char *src, const char *str);
	virtual void EmergencyFlush(void);
	virtual void Execute(class Debug &dbg, const char *cmd, bool structuredCmd, unsigned argn, const char *const *argv);
	virtual void Delete(void);
};

// ??1DebugIONet@@UAE@XZ (stores vftable 0x007C09C8, ??_7DebugIONet)
DebugIONet::~DebugIONet()
{
	if (m_pipe != (HANDLE)-1)
		CloseHandle(m_pipe);
}
