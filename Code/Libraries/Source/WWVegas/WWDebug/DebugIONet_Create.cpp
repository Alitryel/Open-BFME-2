// cl: /DNDEBUG /MD /EHa /Oy-

// Preserve placement construction and unwind without an unused competing
// external placement-new copy (the established WWDebug factory spelling).
#define __PLACEMENT_NEW_INLINE
#include <new>
__declspec(dllimport) __forceinline void *__cdecl operator new(size_t, void *memory) throw()
{
    return memory;
}
inline void __cdecl operator delete(void *, void *) throw()
{
}

extern void *DebugAllocMemory(unsigned size);

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

class DebugIONet : public DebugIOInterface
{
public:
    DebugIONet(void) {}
    virtual ~DebugIONet(void);
	virtual int Read(char *buf, int maxchar);
	virtual void Write(StringType type, const char *src, const char *str);
	virtual void EmergencyFlush(void);
	virtual void Execute(class Debug &dbg, const char *cmd, bool structuredCmd, unsigned argn, const char *const *argv);
	virtual void Delete(void);
    static DebugIOInterface *Create(void);

private:
    void *m_pipe;
};

// ?Create@DebugIONet@@SAPAVDebugIOInterface@@XZ
DebugIOInterface *DebugIONet::Create(void)
{
    return new (DebugAllocMemory(sizeof(DebugIONet))) DebugIONet();
}
