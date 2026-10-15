// ?rva004F9F39@Rva004F9F39@@QAEXXZ
// partial score=0.94 date=2026-10-15
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
namespace _STL
{
template <class T> class allocator
{
public:
	allocator() {}
};
template <class T, class A> class _Vector_base
{
public:
	_Vector_base(const A &a);
	T *_M_start;
	T *_M_finish;
	T *_M_end_of_storage;
};
template <class T, class A = allocator<T> > class vector
{
public:
	void reserve(unsigned int n);
	T *erase(T *first, T *last);
	void push_back(const T &x);
};
template <class It, class Cmp> void sort(It first, It last, Cmp cmp);
}

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);
struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other) : m_ptr(other.m_ptr)
	{
		if (m_ptr)
			++m_ptr->references;
	}
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			ReleaseTreeHintRef00217D4C(m_ptr);
	}
};

struct MedianKey004F60EC
{
	int _00[2];
	int m_key;
};
struct Rva004F6352
{
	MedianKey004F60EC *m_ptr;
	int m_04;
	TreeHintRef00217D4C m_08;
};
struct Rva004F6352Cmp
{
	bool operator()(const Rva004F6352 &a, const Rva004F6352 &b) const;
};
struct Rva004F691E
{
	int m_00;
	int m_04;
	TargetRef00217D4C *m_08;
	Rva004F691E(int a, int b, const TreeHintRef00217D4C &ref) throw();
	operator const Rva004F6352 &() const { return *(const Rva004F6352 *)this; }
	~Rva004F691E()
	{
		if (m_08)
			ReleaseTreeHintRef00217D4C(m_08);
	}
};

// The local record vector (dtor rowed 0x004F887C; its base ctor is the folded
// _Vector_base<int> 0x00211E58).
struct Rva004F887C : public _STL::_Vector_base<int, _STL::allocator<int> >
{
	Rva004F887C() : _STL::_Vector_base<int, _STL::allocator<int> >(_STL::allocator<int>()) {}
	~Rva004F887C();
	_STL::vector<Rva004F6352> *records() { return (_STL::vector<Rva004F6352> *)this; }
	Rva004F6352 *begin() const { return (Rva004F6352 *)_M_start; }
	Rva004F6352 *end() const { return (Rva004F6352 *)_M_finish; }
};

class Rva00417FBA
{
public:
	int *rva00417FBA(int key);
};
struct Rva004F9F39Key
{
	unsigned char m_pad00[0x0C];
	int m_key; // +0x0C
};
struct Rva004F9F39Template
{
	unsigned char m_pad000[0x494];
	Rva00417FBA *m_494; // +0x494
	unsigned char m_pad498[0x5C4 - 0x498];
	unsigned int m_5c4; // +0x5C4
};
struct Rva004F9F39Unit : public TargetRef00217D4C
{
	Rva004F9F39Key *m_08; // +0x08
	float m_0c; // +0x0C
	unsigned char m_pad10[0x1C - 0x10];
	MedianKey004F60EC *m_1c; // +0x1C
	unsigned char m_pad20[0x2C - 0x20];
	Rva004F9F39Template *m_2c; // +0x2C
};
struct Rva004F9F39Info
{
	unsigned char m_pad00[0x04];
	unsigned int m_bits[4]; // +0x04
	bool m_frontToBack; // +0x14
};
struct Rva004F9F39Vec
{
	TreeHintRef00217D4C *m_start;
	TreeHintRef00217D4C *m_finish;
	TreeHintRef00217D4C *m_end;
	unsigned int size() const { return m_finish - m_start; }
	TreeHintRef00217D4C &operator[](unsigned int i) { return m_start[i]; }
};
static __forceinline const unsigned int &maxRef(const unsigned int &a, const unsigned int &b)
{
	return a < b ? b : a;
}

class Rva004F9F39
{
public:
	void rva004F9F39();
private:
	unsigned char m_pad00[0x0C];
	Rva004F9F39Vec m_vecs[2]; // +0x0C, +0x18
};

void Rva004F9F39::rva004F9F39()
{
	Rva004F887C records;
	records.records()->reserve(maxRef(m_vecs[1].size(), m_vecs[0].size()));
	for (int i = 0; i < 2; ++i)
	{
		Rva004F9F39Vec &vec = m_vecs[i];
		records.records()->erase(records.begin(), records.end());
		TreeHintRef00217D4C *end = vec.m_finish;
		for (TreeHintRef00217D4C *it = vec.m_start; it != end; ++it)
		{
			Rva004F9F39Unit *unit = (Rva004F9F39Unit *)it->m_ptr;
			Rva00417FBA *table = unit->m_2c->m_494;
			if (!table)
				continue;
			int *entry = table->rva00417FBA(unit->m_08->m_key);
			if (!entry)
				continue;
			records.records()->push_back(Rva004F691E((int)entry, (int)table, TreeHintRef00217D4C(*it)));
		}
		_STL::sort(records.begin(), records.end(), Rva004F6352Cmp());
		Rva004F6352 *rend = records.end();
		for (Rva004F6352 *r = records.begin(); r != rend; ++r)
		{
			int count = r->m_ptr->_00[1];
			Rva004F9F39Info *info = (Rva004F9F39Info *)r->m_04;
			bool frontToBack = info->m_frontToBack;
			int n = vec.size();
			for (int k = 0; count > 0 && k < n; ++k)
			{
				Rva004F9F39Unit *unit = (Rva004F9F39Unit *)(frontToBack ? vec[k] : vec[n - 1 - k]).m_ptr;
				if (unit->m_1c)
					continue;
				unsigned int bit = unit->m_2c->m_5c4;
				if ((info->m_bits[bit >> 5] & (1u << (bit & 31))) && unit != (Rva004F9F39Unit *)r->m_08.m_ptr && !(unit->m_0c <= 0.0f))
				{
					--count;
					unit->m_1c = r->m_ptr;
				}
			}
		}
	}
}
