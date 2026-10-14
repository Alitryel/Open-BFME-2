// Small accessors from .text gaps no ledger row covered (each begins after
// its neighbour's padding or return and ends in its own ret), none reached by
// a direct caller in retail. Retail bytes establish every shape; the owning
// classes are not recovered, so each keeps an address-derived name and a view
// of only the members it touches.

// --- 0x000AD711 (12B): address of 16-bit element `index` of the array whose
// base pointer is at +0.
class Rva000AD711
{
public:
	unsigned short *rva000AD711(int index);
private:
	unsigned short *m_items;
};

unsigned short *Rva000AD711::rva000AD711(int index)
{
	return &m_items[index];
}

// --- 0x000B3F5B (12B): address of 64-byte record `index` of the array whose
// base pointer is at +0.
struct Rva000B3F5BRecord
{
	unsigned char m_data[0x40];
};

class Rva000B3F5B
{
public:
	Rva000B3F5BRecord *rva000B3F5B(int index);
private:
	Rva000B3F5BRecord *m_records;
};

Rva000B3F5BRecord *Rva000B3F5B::rva000B3F5B(int index)
{
	return &m_records[index];
}

// --- 0x00135F0C (13B): address of dword `index` of the array whose base
// pointer is at +4.
class Rva00135F0C
{
public:
	int *rva00135F0C(int index);
private:
	int m_00;
	int *m_items;
};

int *Rva00135F0C::rva00135F0C(int index)
{
	return &m_items[index];
}

// --- 0x000CF0FF (12B): element count of a [begin,end) range of 0x4C-byte
// records held at +0/+4.
struct Rva000CF0FFRecord
{
	unsigned char m_data[0x4C];
};

class Rva000CF0FF
{
public:
	int rva000CF0FF() const;
private:
	Rva000CF0FFRecord *m_begin;
	Rva000CF0FFRecord *m_end;
};

int Rva000CF0FF::rva000CF0FF() const
{
	return m_end - m_begin;
}

// --- 0x000B2B7C (11B): scales its argument by 0.001 (the constant at
// VA 0x00BC28F8), e.g. milliseconds to seconds.
float Rva000B2B7CScale(float value)
{
	return value * 0.001f;
}
