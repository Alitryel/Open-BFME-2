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

// --- 0x000A47AE (8B): cdecl read of the dword at +0x58 of its argument.
struct Rva000A47AERecord
{
	unsigned char m_pad00[0x58];
	int m_58;
};

int Rva000A47AEGet(const Rva000A47AERecord *record)
{
	return record->m_58;
}

// --- 0x000D1D2B / 0x000D1EA2 (8B each): cdecl addresses of the link words
// at +8 and +4 of a tree-node-like record (the shape of STLport's
// _Rb_tree _S_left / _S_parent; the instantiation is not recovered).
struct Rva000D1D2BNode
{
	int m_color;
	Rva000D1D2BNode *m_parent;
	Rva000D1D2BNode *m_left;
	Rva000D1D2BNode *m_right;
};

Rva000D1D2BNode **Rva000D1D2BLeft(Rva000D1D2BNode *node)
{
	return &node->m_left;
}

Rva000D1D2BNode **Rva000D1EA2Parent(Rva000D1D2BNode *node)
{
	return &node->m_parent;
}

// --- 0x000E0F0E (8B): sets the byte flag at +0x44555.
class Rva000E0F0E
{
public:
	void rva000E0F0E();
private:
	unsigned char m_pad00[0x44555];
	bool m_44555;
};

void Rva000E0F0E::rva000E0F0E()
{
	m_44555 = true;
}

// --- 0x0009DBF4 (17B): log10 of a float through the msvcr71 import
// (thunk 0x0062997C), returned as double.
extern "C" double __cdecl log10(double);

double __cdecl Rva0009DBF4Log10(float value)
{
	return log10(value);
}

// --- 0x000A87E1 (18B): a constructor that only runs the rowed
// ??0Rva0073F4F3@@QAE@PAX@Z (0x0073F468) on itself with its argument.
class Rva0073F4F3
{
public:
	Rva0073F4F3(void *source);
};

class Rva000A87E1 : public Rva0073F4F3
{
public:
	Rva000A87E1(void *source);
};

Rva000A87E1::Rva000A87E1(void *source) : Rva0073F4F3(source)
{
}
