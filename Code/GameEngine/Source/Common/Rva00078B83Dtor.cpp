// cl: /DNDEBUG /MD /Gy
// ??1Rva0078B83@@UAE@XZ, retail 0x00078B83 (56 B): destructor of the scripted
// horde model draw (W3DScriptedModelDraw plus two further polymorphic bases).
// The rowed holder clear at 0x0007898B is defined out of line ahead of the
// destructor (/Gy keeps the duplicate a COMDAT): with the callee's register
// use visible cl keeps `this` in EDX across the call and tail-jumps to the
// base destructor, as retail does.
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
	void rva0007898BClear(Rva000789A0Outer *obj);
};
// ?rva0007898BClear@W3DHordeModelDrawManager@@QAEXPAVRva000789A0Outer@@@Z present-unmatched
// (thiscall spelling of the body rowed at 0x0007898B as ?Rva0007898BClear@@YG...; pinned)
void W3DHordeModelDrawManager::rva0007898BClear(Rva000789A0Outer *obj)
{
	if (obj->m_holder != 0)
		*(int *)((char *)obj->m_holder + 4) = 0;
}
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

// Placeholder virtuals this unit's vftables hold.  In retail each such slot
// holds a rowed function; the vftable's address is proven by the vptr stores in
// the matched destructors, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?f2@Rva0078B83_B2@@UAEXXZ=?rva000BFB76@Rva000BFB76Interface@@UAEXABVModelConditionFlags@@_NH@Z")
