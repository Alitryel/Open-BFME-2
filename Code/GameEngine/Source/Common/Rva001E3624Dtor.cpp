// cl: /DNDEBUG /MD
// Overridable restores its table at VA 0x00BDDC48 before clearing its chain.
// The next override at +4 is destroyed through slot 0 and globally deallocated.

class Overridable
{
public:
	virtual ~Overridable();

private:
	Overridable *m_next;	// +4
};

Overridable::~Overridable()
{
	if (m_next)
		::delete m_next;
	m_next = 0;
}
