// cl: /O1 /arch:SSE /G7 /EHsc /MD
// ?rva005F3F9A@Rva005F3F9A@@QAEXXZ @0x005F3F9A 90B.
// Slot-target of the 8-byte tail jump at 0x005F3FF4: marks the byte at +0x15,
// fetches a counted reference from the source object at +4 (its fourth virtual,
// returned by value through a hidden slot), assigns it to the reference member
// at +0x10 through the shared intrusive-reference assignment (0x002174A4), drops
// the temporary through the rowed release (0x0007DEEF), and hands the member to
// the host at +8 (direct call of the 4-byte forwarder at 0x001FF3A9) when set.
// Layout views are neutral: only the witnessed offsets are named.
struct TargetRef00217D4C;
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

class AptCommandMap;
template <class T>
class AptRef
{
public:
	AptRef() : m_ptr(0) {}
	~AptRef()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
	AptRef &operator=(const AptRef &other);
	TargetRef00217D4C *m_ptr;
};

class Rva005F3F9ASource
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual void slot2();
	virtual AptRef<AptCommandMap> getReference();
};

class Rva003FE20FBase
{
public:
	virtual void slot0();
	virtual void slot1(void *arg);
};

class Rva005F3F9A
{
public:
	void rva005F3F9A();
private:
	void *m_00;
	Rva005F3F9ASource *m_source;
	Rva003FE20FBase *m_host;
	int m_0C;
	AptRef<AptCommandMap> m_reference;
	unsigned char m_14;
	unsigned char m_applied;
};

void Rva005F3F9A::rva005F3F9A()
{
	m_applied = 1;
	m_reference = m_source->getReference();
	if (m_reference.m_ptr)
		m_host->Rva003FE20FBase::slot1(&m_reference);
}
