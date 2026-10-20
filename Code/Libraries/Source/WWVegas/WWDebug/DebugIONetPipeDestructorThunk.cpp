// cl: /DNDEBUG /MD /EHa
// Open-BFME: Debug I/O net destructor. Stores the net vtable, CloseHandle on
// the pipe at +4 unless it is INVALID_HANDLE_VALUE, then restores the
// DebugIOInterface vtable. Named apart from ??1DebugIONet which is already
// claimed on the FreeConsole ICF body.

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

class Rva0088FB30NetIO : public DebugIOInterface
{
	HANDLE m_pipe;

public:
	virtual ~Rva0088FB30NetIO();
};

// ??1Rva0088FB30NetIO@@UAE@XZ
Rva0088FB30NetIO::~Rva0088FB30NetIO()
{
	if (m_pipe != (HANDLE)-1)
		CloseHandle(m_pipe);
}
