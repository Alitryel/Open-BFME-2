// cl: /O1 /MD
//
// ?update@VictorySystem@@UAEXXZ @0x00405315 34B.
// VictorySystem::update: SubsystemInterface slot 10 of VictorySystem's table
// 0x008388D4 (installed by the rowed VictorySystem ctor 0x004054E1).
// Flag-gated chain: if the +0x134 byte is set run the no-arg members at
// 0x00405094 and 0x00405258 then tail to 0x00404A29, else return.
class VictorySystem
{
public:
	virtual void update();
private:
	char m_pad04[0x134 - 0x04];
	char m_134;
};

class VictorySystemGridUpdateView
{
public:
	void rva00405094();
	void rva00405258();
};

class Rva004053C2
{
public:
	void rva00404A29();
};

void VictorySystem::update()
{
	if (m_134 != 0)
	{
		((VictorySystemGridUpdateView *)this)->rva00405094();
		((VictorySystemGridUpdateView *)this)->rva00405258();
		((Rva004053C2 *)this)->rva00404A29();
	}
}
