// cl: /DNDEBUG /MD /EHsc
// Retail BFME 2 parent 0x0075A080, 127 bytes (BFME 1 donor: 0x009A4620).
// The list nodes use the existing CollisionData destructor identity.
// Normal cleanup and the parent's two unwind entries independently establish
// the embedded-table destructor lifetimes; their node-delete loops are retained
// from the previously verified donor bodies. The opaque member extents come
// from the target parent's offsets, not the donor class names.

class Rva009A36F0Param;

class CollisionManagerImpl
{
public:
	void UnRegisterObject(Rva009A36F0Param *param);
};

class Rva009A4620Param
{
public:
	unsigned char m_pad00[4];
	void *m_child;
};

class Rva009A45A0CollisionData
{
public:
	~Rva009A45A0CollisionData();
};

// Retail normal cleanup and both unwind entries call the same full table
// destructors at 0x00758F30 and 0x00759D30, respectively.
class Rva009A4620VMNView
{
public:
	~Rva009A4620VMNView() throw();
private:
	unsigned char m_storage[0xADF8];
};

class Rva009A4620VDBView
{
public:
	~Rva009A4620VDBView() throw();
private:
	unsigned char m_storage[0x1258];
};

class Rva009A4620CollisionData
{
public:
	~Rva009A4620CollisionData();

	Rva009A45A0CollisionData *m_root;
	unsigned char m_pad04[0x14];
	Rva009A4620VMNView m_vmn;
	Rva009A4620VDBView m_vdb;
};

Rva009A4620CollisionData::~Rva009A4620CollisionData()
{
	while (m_root != 0)
	{
		Rva009A4620Param *param = (Rva009A4620Param *)m_root;
		if (param->m_child != 0)
			((CollisionManagerImpl *)this)->UnRegisterObject((Rva009A36F0Param *)param->m_child);

		Rva009A45A0CollisionData *root = m_root;
		if (root != 0)
			delete root;
	}
}
