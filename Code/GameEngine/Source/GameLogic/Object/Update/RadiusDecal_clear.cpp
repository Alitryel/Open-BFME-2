// cl: /DNDEBUG /MD
//
// RadiusDecal::clear, retail 0x00330DBA, 28 bytes.
// Zero the object pointer at +0, Release the holder at +4 (vtable+8),
// then store 1 in the byte at +8.
//
// RadiusDecal::~RadiusDecal, retail 0x00330DD6, 5 bytes. All members are
// trivial, so the destructor only runs clear(); MSVC 7.1 tail-calls it
// into a bare jmp.

class RadiusDecalObject
{
public:
	virtual void _M_slot_00();
	virtual void _M_slot_04();
	virtual void Release();
};

class Shadow;

class RadiusDecal
{
	int m_decalTemplate;
	Shadow *m_shadow;
	bool m_empty;

public:
	~RadiusDecal();
	void clear();
};

RadiusDecal::~RadiusDecal()
{
	clear();
}

void RadiusDecal::clear()
{
	RadiusDecalObject *object = reinterpret_cast<RadiusDecalObject *>(m_shadow);
	m_decalTemplate = 0;
	if (object)
		object->Release();
	m_shadow = 0;
	m_empty = true;
}
