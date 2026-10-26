// cl: /DNDEBUG /MD /EHsc
//
// ?startThreads@Pinger@@UAEXXZ retail 0x0054FB78, 156 bytes: slot 1 of the
// Pinger vtable 0x0086AB90 (slots 3-10 are the rowed Pinger members
// areThreadsRunning/addRequest/getRequest/getResponse/getPing, as in Zero
// Hour's PingThread.cpp declaration order). Zero Hour's body is the model:
// endThreads (slot 2, the rowed 0x0054FC14), then ten new worker threads at
// +0x80, each started with Execute. BFME 2 adds, before the workers, a lock
// on the Pinger's mutex at +0xA8 held in the +0xB0 holder (rowed set
// 0x000998EA; endThreads clears it first), and hands each worker that mutex.
// The worker is the rowed 0x54-byte Rva0054F93F (ctor 0x0054F93F keeps its
// argument at +0x50; its pinned name types that argument as int).

class MutexClass
{
public:
	class LockClass
	{
	public:
		LockClass(MutexClass &mutex, int time);	// 0x00613A70
	private:
		MutexClass &m_mutex;
		int m_failed;
	};
private:
	void *m_handle;
	unsigned int m_locked;
};

class Rva0009990D
{
public:
	void set(void *object);		// 0x000998EA
private:
	void *m_object;
};

class ThreadClass
{
public:
    ThreadClass(const char *name);
    virtual ~ThreadClass();
    virtual void Execute();
    void Set_Priority(int priority);
    __declspec(noinline) bool Is_Running();
    __declspec(noinline) void Stop();

protected:
    virtual void Thread_Function() = 0;

private:
    char m_name[0x40];
    unsigned int m_threadId;
    void *m_handle;
    int m_priority;
};

class Rva0054F93F : public ThreadClass
{
public:
	virtual void Thread_Function();
	Rva0054F93F(int mutex);		// 0x0054F93F
private:
	int m_mutex50;
};

static const int NumWorkerThreads = 10;

class Pinger
{
public:
	virtual ~Pinger();
	virtual void startThreads(void);
	virtual void endThreads(void);
private:
	char m_pad04[0x80 - 4];
	ThreadClass *m_workerThreads[NumWorkerThreads];	// +0x80
	MutexClass m_threadMutex;			// +0xA8
	Rva0009990D m_threadLock;			// +0xB0
};

void Pinger::startThreads(void)
{
	endThreads();
	m_threadLock.set(new MutexClass::LockClass(m_threadMutex, -1));
	for (int i = 0; i < NumWorkerThreads; ++i)
	{
		m_workerThreads[i] = new Rva0054F93F((int)&m_threadMutex);
		m_workerThreads[i]->Execute();
	}
}
