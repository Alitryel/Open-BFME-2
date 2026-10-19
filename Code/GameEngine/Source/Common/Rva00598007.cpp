// cl: /MD
// ?getAI@AIUnitBuilder@@QAEPAURva002A8AB1Record@@XZ @0x00598007 15B
// Evidence: leaf lookup via global and rowed Rva002A8F24 rva002A8AB1 on member at +0x30; ready caller 0x00598CBC uses eax as pointer plus 0x160.
struct Rva002A8AB1Record
{
	char _pad[0x16c];
	void *m_16c;
};

class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *p);
};

extern Rva002A8F24 *TheSkirmishAIManager;

class AIUnitBuilder
{
public:
	Rva002A8AB1Record *getAI();
	bool rva0059802E();
private:
	char _pad[0x30];
	void *m_30;
};

Rva002A8AB1Record *AIUnitBuilder::getAI()
{
	Rva002A8AB1Record *p = TheSkirmishAIManager->rva002A8AB1(m_30);
	return p;
}

bool AIUnitBuilder::rva0059802E()
{
	Rva002A8AB1Record *p = TheSkirmishAIManager->rva002A8AB1(m_30);
	return p->m_16c == 0;
}
