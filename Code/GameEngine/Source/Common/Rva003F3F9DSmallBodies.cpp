// cl: /O1 /arch:SSE /G7 /MD
// Three small bodies from the 0x003F3F9D..0x003FBB99 range, owners and
// names address-derived:
//  - 0x003F3F9D (25B, RET 4): constructor storing its argument at +0 and
//    clearing the four dwords after it.
//  - 0x003F814B (35B, RET 4): whether any pointer in the vector at +0x14
//    names an entry whose +8 field equals the id.
//  - 0x003FBB80 (25B, RET 4): copy a 12-byte coordinate into +0x5C and
//    hand it to the object's own vslot 7.
struct Rva003F3F9D
{
	Rva003F3F9D(int value);
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
};

Rva003F3F9D::Rva003F3F9D(int value)
	: m_00(value), m_04(0), m_08(0), m_0C(0), m_10(0)
{
}

struct Rva003F814BEntry
{
	char m_pad00[8];
	int m_id;	// +0x08
};

class Rva003F814B
{
public:
	bool contains(int id) const;
private:
	char m_pad00[0x14];
	Rva003F814BEntry **m_begin;	// +0x14
	Rva003F814BEntry **m_end;	// +0x18
};

bool Rva003F814B::contains(int id) const
{
	for (Rva003F814BEntry **it = m_begin; it != m_end; ++it)
	{
		if ((*it)->m_id == id)
			return true;
	}
	return false;
}

struct Rva003FBB80Coord { float x, y, z; };

class Rva003FBB80
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06();
	virtual void slot07(const Rva003FBB80Coord *pos);
	void rva003FBB80(const Rva003FBB80Coord *pos);
private:
	char m_pad04[0x5C - 0x04];
	Rva003FBB80Coord m_5C;
};

void Rva003FBB80::rva003FBB80(const Rva003FBB80Coord *pos)
{
	m_5C = *pos;
	slot07(&m_5C);
}
