// cl: /DNDEBUG /MD /EHsc
// ??0Rva0054F93F@@QAE@H@Z retail 0x0054F93F 29B.
// ThreadClass-derived ctor: base ThreadClass(NULL) plus int at +0x50.
// Evidence: base ctor 0x00610430; vtable 0x0086AB40; member +0x50;
// caller 0x0054FBE9; prev Disp0 setter 0x0054F91B; next PingThread 0x0054F99E.
#include <string.h>

class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();

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
	Rva0054F93F(int val);
	// Empty: retail's vtable 0x0086AB40 slot 0 0x00419E1C calls 0x00419E38,
	// one jump to the base dtor 0x00610480.
	virtual ~Rva0054F93F() {}

private:
	int m_val50;
};

Rva0054F93F::Rva0054F93F(int val) : ThreadClass(0), m_val50(val)
{
}
