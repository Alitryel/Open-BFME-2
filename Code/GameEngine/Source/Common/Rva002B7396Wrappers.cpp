// flags: region default (reverse/retail_inventory/flag_regions.csv)
// ??1Rva002B7396@@QAE@XZ @0x002B7396 5B
// ??4Rva002B739B@@QAEAAV0@ABV0@@Z @0x002B739B 18B
// Two wrappers over a container held at offset 0, between 0x002B738B and the
// sort-family __linear_insert at 0x002B73AD:
// - a destructor whose only work is the member destructor: a tail jmp into
//   the rowed ??1Rva002B57D5@@QAE@XZ at 0x002B62A6;
// - a copy assignment that forwards to the rowed member operator=
//   ??4Rva002B5558@@QAEAAV0@ABV0@@Z at 0x002B62DE and returns *this
//   (push esi / mov esi,ecx / call / mov eax,esi / ret 4).
// Both are the shape of an STLport map's dtor and operator= over its _M_t
// member; the owning classes are not identified, so the names are
// address-derived.

class Rva002B57D5
{
public:
	~Rva002B57D5();
private:
	void *m_handle;
	int m_count;
};

class Rva002B5558
{
public:
	Rva002B5558 &operator=(const Rva002B5558 &other);
private:
	void *m_head0;
	int m_count4;
};

class Rva002B7396
{
public:
	~Rva002B7396();
private:
	Rva002B57D5 m_tree;
};

Rva002B7396::~Rva002B7396()
{
}

class Rva002B739B
{
public:
	Rva002B739B &operator=(const Rva002B739B &other);
private:
	Rva002B5558 m_tree;
};

Rva002B739B &Rva002B739B::operator=(const Rva002B739B &other)
{
	m_tree = other.m_tree;
	return *this;
}
