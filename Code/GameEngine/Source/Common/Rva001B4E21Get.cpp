// cl: /O1 /MD
// ?rva001B4E21@SubsystemInterfaceList@@QAEEPAVSubsystemInterface@@PAE@Z RVA 0x001B4E21 40B
// Evidence: unlock lane; callers 0x001B509F 0x001B50D8 in 0x001B505F; free function ret 8
//   with vtable slot 0x10 call on arg1 with m_4 guard set/cleared around it.
//   Retail passes ECX=this from SubsystemInterfaceList::rva001B505F and the body never
//   reads it: a thiscall member with two stack arguments (ret 8).

class Rva001B4E21Arg
{
public:
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void v3();
	virtual bool v4(void *arg);
	unsigned char m_4;
};

class SubsystemInterface;
class SubsystemInterfaceList
{
public:
	unsigned char rva001B4E21(SubsystemInterface *arg1, unsigned char *arg2);
};

unsigned char SubsystemInterfaceList::rva001B4E21(SubsystemInterface *subsystem, unsigned char *arg2)
{
	Rva001B4E21Arg *obj = (Rva001B4E21Arg *)subsystem;
	unsigned char result = 0;
	obj->m_4 = 1;
	if (obj->v4(arg2))
		result++;
	obj->m_4 = 0;
	return result;
}
