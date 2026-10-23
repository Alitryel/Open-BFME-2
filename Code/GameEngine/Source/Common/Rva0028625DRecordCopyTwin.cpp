// cl: /MD /EHsc
//
// ICF twin of ??0Rva00285BEC@@QAE@ABV0@@Z (0x00285C30, Rva00285BECDtor.cpp):
// the element of the STLport sweep at 0x0028625D is the same two-base record
// (vptrs at +0/+4, pair at +8, registration id at +0x10), and its copy
// constructor is that body: copy the pair, clear the id, then register
// through the rowed 0x00285708.

class Rva00285708Host
{
public:
	void rva00285708();
};

class Rva00285BECBase
{
public:
	virtual ~Rva00285BECBase() {}
};

class Rva00285BECSnapshotBase
{
public:
	virtual ~Rva00285BECSnapshotBase() {}
};

struct Rva0028625DRecord : public Rva00285BECBase, public Rva00285BECSnapshotBase
{
	struct Pair080C
	{
		int m_00;
		int m_04;
		Pair080C() {}
	};
	Rva0028625DRecord(const Rva0028625DRecord &src);
	// Compiler-generated destruction (members, then the rowed base dtor), the
	// body retail's vtable slot 0 reaches.
	virtual ~Rva0028625DRecord() {}

	Pair080C m_08;
	int m_10;
};

Rva0028625DRecord::Rva0028625DRecord(const Rva0028625DRecord &src)
{
	m_08.m_00 = src.m_08.m_00;
	m_08.m_04 = src.m_08.m_04;
	m_10 = -1;
	((Rva00285708Host *)this)->rva00285708();
}
