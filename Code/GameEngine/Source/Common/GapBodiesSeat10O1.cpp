// Small unrowed .text bodies from the 0x0051xxxx..0x005Fxxxx (/O1) region.
// Retail bytes establish every shape; the owning classes are not recovered,
// so each keeps an address-derived name and a view of only the fields it
// touches. Bodies reached through a vftable slot (an absolute reference in
// .rdata, no direct caller) are declared virtual; the others have no
// recovered caller. Callees are the rowed bodies the retail jmp targets.

// ?rva00531041@Rva00531041@@QAEXXZ @0x00531041 9B: clear +0x10 then +0x0C.
class Rva00531041
{
public:
	void rva00531041();
private:
	char m_pad[0xc];
	int m_0c;
	int m_10;
};
void Rva00531041::rva00531041()
{
	m_10 = 0;
	m_0c = 0;
}

// ?rva0054C836@Rva0054C836@@QBE_NXZ @0x0054C836 9B: pointer at +0x14 non-null.
class Rva0054C836
{
public:
	bool rva0054C836() const;
private:
	char m_pad[0x14];
	void *m_14;
};
bool Rva0054C836::rva0054C836() const
{
	return m_14 != 0;
}

// ?rva005FC6EE@Rva005FC6EE@@QBE_NXZ @0x005FC6EE 9B: bit 0 of the byte at +0x34
// of the object held at +0x18 (same shape as the rowed 0x005F273B).
struct Rva005FC6EEFlags
{
	char m_pad[0x34];
	unsigned char m_bit0 : 1;
};
class Rva005FC6EE
{
public:
	bool rva005FC6EE() const;
private:
	char m_pad[0x18];
	Rva005FC6EEFlags *m_18;
};
bool Rva005FC6EE::rva005FC6EE() const
{
	return m_18->m_bit0;
}

// ?rva005CCBA8@Rva005CCBA8@@QAEXXZ @0x005CCBA8 8B: clear the byte at +0x20 of
// the object held at +0x08.
struct Rva005CCBA8Pointee
{
	char m_pad[0x20];
	unsigned char m_flag;
};
class Rva005CCBA8
{
public:
	void rva005CCBA8();
private:
	char m_pad[0x08];
	Rva005CCBA8Pointee *m_08;
};
void Rva005CCBA8::rva005CCBA8()
{
	m_08->m_flag = 0;
}

// Vector members whose rowed grow/resize bodies the slots tail-jump to.
template <class T>
struct Rva00584A7DVector
{
	void grow(unsigned int count);
};
struct Rva00584A7DEntry;
struct Rva00587057Entry;
struct BfmePod60;
namespace _STL
{
	template <class T> class allocator;
	template <class T, class A = allocator<T> >
	class vector
	{
	public:
		void resize(unsigned int count);
	};
	template <class T, class A = allocator<T> >
	class deque
	{
	public:
		~deque();
	};
	template <class A, class B> struct pair;
	template <class P> struct _Select1st;
	template <class T> struct less;
	template <class K, class V, class KoV, class C, class A>
	class _Rb_tree
	{
	public:
		~_Rb_tree();
	};
}

// ?rva00584A75@Rva00584A75@@UAEXI@Z @0x00584A75 8B (vftable slot at VA
// 0x00C6FC84): grow the +0x08 vector through rowed 0x00584A3D.
class Rva00584A75
{
public:
	virtual void rva00584A75(unsigned int count);
private:
	int m_04;
	Rva00584A7DVector<Rva00584A7DEntry> m_08;
};
void Rva00584A75::rva00584A75(unsigned int count)
{
	m_08.grow(count);
}

// ?rva0058704F@Rva0058704F@@UAEXI@Z @0x0058704F 8B (vftable slot at VA
// 0x00C6FD94): grow the +0x08 vector through rowed 0x0058702C.
class Rva0058704F
{
public:
	virtual void rva0058704F(unsigned int count);
private:
	int m_04;
	Rva00584A7DVector<Rva00587057Entry> m_08;
};
void Rva0058704F::rva0058704F(unsigned int count)
{
	m_08.grow(count);
}

// ?rva00588A95@Rva00588A95@@UAEXI@Z @0x00588A95 8B (vftable slot at VA
// 0x00C6FF3C): resize the +0x08 vector through rowed 0x00588A72.
class Rva00588A95
{
public:
	virtual void rva00588A95(unsigned int count);
private:
	int m_04;
	_STL::vector<BfmePod60> m_08;
};
void Rva00588A95::rva00588A95(unsigned int count)
{
	m_08.resize(count);
}

// ?rva005CFACB@Rva005CFACB@@UAEXXZ @0x005CFACB 8B (vftable slot at VA
// 0x00C75558): forward to the rowed 0x005EA91A on the +0x0C member.
class Rva005EA91A
{
public:
	void rva005EA91A();
};
class Rva005CFACB
{
public:
	virtual void rva005CFACB();
private:
	char m_pad[0x08];
	Rva005EA91A m_0c;
};
void Rva005CFACB::rva005CFACB()
{
	m_0c.rva005EA91A();
}

// ?rva00574AB3@Rva00574AB3@@UAE_NXZ @0x00574AB3 8B (vftable slot at VA
// 0x00C3C6D0): direct (qualified) call of the rowed Rva005743C0 slot body
// 0x005743C0 on the object held at +0x04.
class Rva005743C0
{
public:
	virtual bool rva005743C0();
};
class Rva00574AB3
{
public:
	virtual bool rva00574AB3();
private:
	Rva005743C0 *m_04;
};
bool Rva00574AB3::rva00574AB3()
{
	return m_04->Rva005743C0::rva005743C0();
}

// Out-of-line destructors whose only non-trivial member sits at +0, so each
// is a bare tail jump to that member's rowed destructor. Each is reached
// only from EH unwind funclets (0x0079xxxx..0x007Axxxx), i.e. it destroys a
// local of its type; the owning types are unrecovered.
class AsciiString;
struct TreeHintRef0051030C;
struct BfmeOpaque2148;
struct SBServer;
class BfmeMsg
{
public:
	virtual ~BfmeMsg();
};
struct Rva0060D031Member
{
	~Rva0060D031Member();
};

typedef _STL::pair<const AsciiString, TreeHintRef0051030C> Rva00510D07Pair;
typedef _STL::pair<const int, SBServer> Rva005E4920Pair;

// ??1Rva00510D07@@QAE@XZ @0x00510D07 5B: tree member, rowed dtor 0x0051097F.
class Rva00510D07
{
public:
	~Rva00510D07();
private:
	_STL::_Rb_tree<AsciiString, Rva00510D07Pair, _STL::_Select1st<Rva00510D07Pair>, _STL::less<AsciiString>, _STL::allocator<Rva00510D07Pair> > m_tree;
};
Rva00510D07::~Rva00510D07()
{
}

// ??1Rva00550634@@QAE@XZ @0x00550634 5B: BfmeMsg member, rowed dtor 0x00655780.
class Rva00550634
{
public:
	~Rva00550634();
private:
	BfmeMsg m_msg;
};
Rva00550634::~Rva00550634()
{
}

// ??1Rva00551983@@QAE@XZ @0x00551983 5B: deque member, rowed dtor 0x00551868.
class Rva00551983
{
public:
	~Rva00551983();
private:
	_STL::deque<BfmeOpaque2148> m_deque;
};
Rva00551983::~Rva00551983()
{
}

// ??1Rva005E4920@@QAE@XZ @0x005E4920 5B: tree member, rowed dtor 0x005E4670.
class Rva005E4920
{
public:
	~Rva005E4920();
private:
	_STL::_Rb_tree<int, Rva005E4920Pair, _STL::_Select1st<Rva005E4920Pair>, _STL::less<int>, _STL::allocator<Rva005E4920Pair> > m_tree;
};
Rva005E4920::~Rva005E4920()
{
}

// ??1Rva0060D0AE@@QAE@XZ @0x0060D0AE 5B: member, rowed dtor 0x0060D031.
class Rva0060D0AE
{
public:
	~Rva0060D0AE();
private:
	Rva0060D031Member m_member;
};
Rva0060D0AE::~Rva0060D0AE()
{
}

// ?rva00525E00@Rva00525E00@@QAEXPAVXfer@@@Z @0x00525E00 7B (called from
// 0x002D64C7): forward the Xfer to the rowed 0x00525ABF on the object held
// at +0.
class Xfer;
class Rva00525ABF
{
public:
	void rva00525ABF(Xfer *xfer);
};
class Rva00525E00
{
public:
	void rva00525E00(Xfer *xfer);
private:
	Rva00525ABF *m_00;
};
void Rva00525E00::rva00525E00(Xfer *xfer)
{
	m_00->rva00525ABF(xfer);
}

// ?rva0050EE1C@Rva0050EE1C@@QBEHXZ @0x0050EE1C 7B: the rowed
// AsciiStringPlusString::length 0x002198C8 of this object plus one.
struct AsciiStringPlusString
{
	int length() const;
};
struct Rva0050EE1C : AsciiStringPlusString
{
	int rva0050EE1C() const;
};
int Rva0050EE1C::rva0050EE1C() const
{
	return length() + 1;
}

// ?rva00522AFC@Rva00522AFC@@QAEAAV1@ABV1@@Z @0x00522AFC 18B: assignment of an
// object whose only member is an AsciiString->AsciiString tree, through the
// rowed tree operator= 0x0052274D, returning this.
typedef _STL::pair<const AsciiString, AsciiString> Rva00522AFCPair;
namespace _STL
{
	template <>
	class _Rb_tree<AsciiString, Rva00522AFCPair, _Select1st<Rva00522AFCPair>, less<AsciiString>, allocator<Rva00522AFCPair> >
	{
	public:
		_Rb_tree &operator=(const _Rb_tree &other);
	};
}
class Rva00522AFC
{
public:
	Rva00522AFC &rva00522AFC(const Rva00522AFC &other);
private:
	_STL::_Rb_tree<AsciiString, Rva00522AFCPair, _STL::_Select1st<Rva00522AFCPair>, _STL::less<AsciiString>, _STL::allocator<Rva00522AFCPair> > m_tree;
};
Rva00522AFC &Rva00522AFC::rva00522AFC(const Rva00522AFC &other)
{
	m_tree = other.m_tree;
	return *this;
}

// ?Rva0051C3AB@@YAXAAUBfmeE12@@0@Z @0x0051C3AB 5B: swap two 12-byte records
// through the rowed _STL::swap<BfmeE12> 0x004219CD (a tail jump).
struct BfmeE12;
namespace _STL
{
	template <class T> void swap(T &a, T &b);
}
void Rva0051C3AB(BfmeE12 &a, BfmeE12 &b)
{
	_STL::swap(a, b);
}

// ?rva005206FE@Rva005206FE@@QAEXPAURva005205DAElement@@IABU2@@Z @0x005206FE
// 5B: fill-insert into the vector at +0 through the rowed _M_fill_insert
// 0x005205DA (a tail jump with the arguments forwarded).
struct Rva005205DAElement;
namespace _STL
{
	template <>
	class vector<Rva005205DAElement, allocator<Rva005205DAElement> >
	{
	public:
		void _M_fill_insert(Rva005205DAElement *position, unsigned int count, const Rva005205DAElement &value);
	};
}
class Rva005206FE
{
public:
	void rva005206FE(Rva005205DAElement *position, unsigned int count, const Rva005205DAElement &value);
private:
	_STL::vector<Rva005205DAElement> m_vector;
};
void Rva005206FE::rva005206FE(Rva005205DAElement *position, unsigned int count, const Rva005205DAElement &value)
{
	m_vector._M_fill_insert(position, count, value);
}

// ?rva00531C54@Rva00531C54@@QAEXXZ @0x00531C54 6B: clear the 16-bit field at +2.
class Rva00531C54
{
public:
	void rva00531C54();
private:
	unsigned short m_00;
	unsigned short m_02;
};
void Rva00531C54::rva00531C54()
{
	m_02 = 0;
}

// ?Rva00531EF6@@YAHG@Z @0x00531EF6 6B: cdecl zero-extension of a 16-bit argument.
int Rva00531EF6(unsigned short value)
{
	return value;
}

// ?rva0053B8F1@Rva0053B8F1@@QBE_NXZ @0x0053B8F1 7B: the flag byte at +0x106.
class Rva0053B8F1
{
public:
	bool rva0053B8F1() const;
private:
	char m_pad[0x106];
	bool m_106;
};
bool Rva0053B8F1::rva0053B8F1() const
{
	return m_106;
}

// ?rva0056864A@Rva0056864A@@QBEEXZ @0x0056864A 7B: high nibble of the byte at +0x47.
class Rva0056864A
{
public:
	unsigned char rva0056864A() const;
private:
	char m_pad[0x47];
	unsigned char m_lo : 4;
	unsigned char m_hi : 4;
};
unsigned char Rva0056864A::rva0056864A() const
{
	return m_hi;
}

// ?rva005778D1@Rva005778D1@@QBEHXZ @0x005778D1 9B and
// ?rva005778DA@Rva005778D1@@QAEPAXXZ @0x005778DA 9B: through the object held
// at +0x40 to its first-word pointee, read its +4 word / take its +8 address.
struct Rva005778D1Record
{
	int m_00;
	int m_04;
	char m_08[4];
};
struct Rva005778D1Holder
{
	Rva005778D1Record *m_00;
};
class Rva005778D1
{
public:
	int rva005778D1() const;
	void *rva005778DA();
private:
	char m_pad[0x40];
	Rva005778D1Holder *m_40;
};
int Rva005778D1::rva005778D1() const
{
	return m_40->m_00->m_04;
}
void *Rva005778D1::rva005778DA()
{
	return m_40->m_00->m_08;
}

// ?rva00564B12@Rva00564B12@@QAEAAVRva005045DBTree@@ABV2@@Z @0x00564B12 8B:
// assign the +0x0C tree through the rowed Rva005045DBTree::assign 0x005045DB.
class Rva005045DBTree
{
public:
	Rva005045DBTree &assign(const Rva005045DBTree &other);
	int storage[3];
};
class Rva00564B12
{
public:
	Rva005045DBTree &rva00564B12(const Rva005045DBTree &other);
private:
	char m_pad[0x0c];
	Rva005045DBTree m_0c;
};
Rva005045DBTree &Rva00564B12::rva00564B12(const Rva005045DBTree &other)
{
	return m_0c.assign(other);
}
