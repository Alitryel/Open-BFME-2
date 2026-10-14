// ??1Rva0078B83@@UAE@XZ
// partial score=0.97 date=2026-10-14
// cl: /DNDEBUG /MD
extern int TheW3DHordeModelDrawCount;
class Rva000789A0Outer
{
public:
	char m_pad[0x2E8];
	void *m_holder;			// +0x2E8
};
class W3DHordeModelDrawManager
{
public:
	__declspec(noinline) void rva0007898BClear(Rva000789A0Outer *obj)
	{
		if (obj->m_holder != 0)
			*(int *)((char *)obj->m_holder + 4) = 0;
	}
};
extern W3DHordeModelDrawManager *TheW3DHordeModelDrawManager;

class W3DScriptedModelDraw
{
public:
	virtual ~W3DScriptedModelDraw() throw();
private:
	char m_pad04[8];
};
class MiBase1 { public: virtual void f1(); };
class Rva0078B83_B2 { public: virtual void f2(); private: char m_pad04[0x2D4]; };
class Rva0078B83 : public W3DScriptedModelDraw, public MiBase1, public Rva0078B83_B2
{
public:
	virtual ~Rva0078B83() throw();
private:
	int m_2E8;
	int m_2EC;
	int m_2F0;
};
Rva0078B83::~Rva0078B83() throw()
{
	--TheW3DHordeModelDrawCount;
	if (m_2E8)
		TheW3DHordeModelDrawManager->rva0007898BClear((Rva000789A0Outer *)this);
}
