// cl: /O1 /DNDEBUG /MD
// ??0MouseThreadClass@@QAE@XZ @0x00098D8A 20B: MouseThreadClass ctor.
// Evidence: calls rowed ThreadClass 1-arg ctor 0x00610430 with null; installs vtable 0x007C86CC; next row is dtor 0x00098D9E; donor BFME1 W3DMouse.cpp.
class ThreadClass
{
public:
	ThreadClass(const char *name);
	virtual ~ThreadClass();
	virtual void Execute();
	void Stop();
protected:
	virtual void Thread_Function() = 0;
private:
	unsigned char m_threadStorage[0x4c];
};

class MouseThreadClass : public ThreadClass
{
public:
	MouseThreadClass();
	virtual ~MouseThreadClass();
	virtual void Thread_Function();
};

MouseThreadClass::MouseThreadClass() : ThreadClass(0)
{
}

