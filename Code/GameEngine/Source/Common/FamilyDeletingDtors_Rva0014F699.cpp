// cl: /O1 /MD
// ??_GRva0014F699@@UAEPAXI@Z @0x0014DC3F 28B: deleting dtor calls rowed dtor 0x0014D1E3 then operator delete 0x0002FD60 on flag. Evidence: same 0x4C element Rva0014F699Assign; chain from 0x0014D1E3; placeholder ??1 duplicates owner for codegen only.
class TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
public:
	void Add_Ref();
	void Release_Ref();
};

template<class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &other);
	~RefCountPtr() { if (Referent) Referent->Release_Ref(); }
	RefCountPtr const &operator=(RefCountPtr const &other);
private:
	T *Referent;
};

extern "C" const unsigned char __identifier("??_7Base@@6B@")[];

class Rva00BC6F24Base
{
public:
	virtual ~Rva00BC6F24Base();
};

// Same one-slot cleanup view as Rva00150558Dtor.cpp: retail resets
// vtable 0x00BC6F24, distinct from canonical Snapshot's 0x00BBB554.
// ??1Rva00BC6F24Base@@UAE@XZ present-unmatched
inline Rva00BC6F24Base::~Rva00BC6F24Base()
{
	*(const void **)this = (const void *)__identifier("??_7Base@@6B@");
}

class Rva0014F699 : public Rva00BC6F24Base
{
public:
	virtual ~Rva0014F699();
private:
	int m_04;
	int m_08;
	int m_0c;
	int m_10;
	int m_14;
	int m_18;
	int m_1c;
	int m_20;
	int m_24;
	int m_28;
	int m_2c;
	int m_30;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	int m_44;
	RefCountPtr<TextureClass> m_48;
};

// ??1Rva0014F699@@UAE@XZ present-unmatched
// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline Rva0014F699::~Rva0014F699()
{
}

// ?bfmeAnchorRva0014F699Dtor absent-from-retail
void bfmeAnchorRva0014F699Dtor(Rva0014F699 *p)
{
	p->Rva0014F699::~Rva0014F699();
}
