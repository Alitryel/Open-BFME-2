// cl: /MD /EHsc /DNDEBUG
//
// ??0Rva0009AA0F@@QAE@H@Z @0x0009AA0F 30B: derived constructor taking one
// int/pointer stored at +0x108, then installing vtable 0x00BC8900. Calls
// the rowed 563B base constructor SimpleSceneClass 0x00142960 first. Honest
// address-derived names on both sides; boundary verified (push esi at
// 0x9AA0F, pop esi + ret 4 at end).

class SimpleSceneClass
{
public:
	SimpleSceneClass();
	virtual ~SimpleSceneClass();

private:
	char m_pad04[0x108 - 4];
};

class Rva0009AA0F : public SimpleSceneClass
{
public:
	Rva0009AA0F(int v);
	virtual ~Rva0009AA0F();

private:
	int m_108;
};

// ??0Rva0009AA0F@@QAE@H@Z
Rva0009AA0F::Rva0009AA0F(int v)
{
	m_108 = v;
}
