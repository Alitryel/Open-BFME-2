// cl: /O1 /DNDEBUG /MD
// Existing B07 wrappers with unresolved or non-retail destructor providers.
// Keep them together without excluding the independent exact B07 siblings.
// Native wrapper/destructor/vtable relationships remain documented in B07.
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"
extern "C" void __cdecl free(void *);
struct EmitVtableTag;

class Rva0036B8E6
{
public:
	Rva0036B8E6(EmitVtableTag *);
public:
	virtual ~Rva0036B8E6();
};

// ?<Rva0036B8E6::Rva0036B8E6> absent-from-retail
Rva0036B8E6::Rva0036B8E6(EmitVtableTag *)
{
}


class __declspec(novtable) Rva0037381CBase0
{
public:
	virtual ~Rva0037381CBase0();
private:
	char m_unmodelled_04[0xC - 0x04];
};

// Secondary base at +0xC: the this-adjusting deleting-destructor thunk
// (sub ecx, 0xC) in its vtable is target evidence for it.
class __declspec(novtable) Rva0037381CBaseC
{
public:
	virtual ~Rva0037381CBaseC();
};
class MineshaftPortalNetworkManager : public Rva0037381CBase0, public Rva0037381CBaseC
{
public:
	MineshaftPortalNetworkManager(EmitVtableTag *);
public:
	virtual ~MineshaftPortalNetworkManager();
};

// ?<MineshaftPortalNetworkManager::MineshaftPortalNetworkManager> absent-from-retail
MineshaftPortalNetworkManager::MineshaftPortalNetworkManager(EmitVtableTag *)
{
}


class ThreadClass {
public:
    ThreadClass(const char *name);
    virtual ~ThreadClass();
    virtual void Execute();
    bool Is_Running();
    static void Switch_Thread();
protected:
    virtual void Thread_Function() = 0;
private:
    char m_name[0x40];
    unsigned int m_threadId;
    void *m_handle;
    int m_priority;
};

class PeerThreadClass : public ThreadClass
{
public:
    PeerThreadClass(EmitVtableTag *);
    virtual ~PeerThreadClass();
    virtual void Thread_Function();
};

// ?<PeerThreadClass::PeerThreadClass> absent-from-retail
PeerThreadClass::PeerThreadClass(EmitVtableTag *) : ThreadClass(0)
{
}


class Rva003ED1FC
{
public:
	Rva003ED1FC(EmitVtableTag *);
public:
	virtual ~Rva003ED1FC();
};

// ?<Rva003ED1FC::Rva003ED1FC> absent-from-retail
Rva003ED1FC::Rva003ED1FC(EmitVtableTag *)
{
}

class Rva003EE1BE
{
public:
	Rva003EE1BE(EmitVtableTag *);
public:
	virtual ~Rva003EE1BE();
};

// ?<Rva003EE1BE::Rva003EE1BE> absent-from-retail
Rva003EE1BE::Rva003EE1BE(EmitVtableTag *)
{
}

// Complete destructors the deleting destructors above call, bound to the rows at their retail
// addresses (the dtor column of the table at the top of OpaqueScalarDeletingDtorsB07.cpp).
#pragma comment(linker, "/alternatename:??1Rva0036B8E6@@UAE@XZ=??1GiantBirdAIUpdate@@MAE@XZ")
#pragma comment(linker, "/alternatename:??1Rva003EE1BE@@UAE@XZ=??1LargeGroupAudioAudioMap@@UAE@XZ")
