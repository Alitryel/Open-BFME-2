// Retail stores the entry point at VA 0x006D7B50 in the +0x9C slot.
// Its matched provider is rva002D7B50 in VslotSmallBodiesAG.cpp; naming it
// gives the store a relocation when the linked image moves. The owner's
// identity and the slot's purpose remain unknown.
void rva002D7B50(int a, int b);

class FireLogicSystem
{
public:
	virtual void init();

	char m_lead[0x9C - 4];
	unsigned int m_value;
};

void FireLogicSystem::init()
{
	m_value = (unsigned int)&rva002D7B50;
}
