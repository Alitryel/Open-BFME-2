// cl: /O1 /EHsc /MD /DNDEBUG
//
// The three members of BFME 2's pathfind request ring that
// Pathfinder::queueForPath (0x002EBD31, PathfinderQueueForPath.cpp) calls: a 512-entry ObjectID ring at
// Pathfinder +0x1C1E0 with head +0x800 and tail +0x804.
//   0x002EABF3 33B  hasRoom: the slot after the tail is not the head
//   0x002EAC14 45B  push: store at the tail, advance it
//   0x002EAC41 59B  contains: scan head..tail for the ID
//   0x002EAC9F 154B rva002EAC9F: transfer head and tail, check the 512 size
//                   ("Unexpected queue size"), then each queued ID through the
//                   rowed XferObjectID (0x003060B2); Pathfinder::xfer
//                   (0x002F21F9) calls it for its two rings at +1C1DC/+1C9E4
// Zero Hour keeps the same queue as m_queuedPathfindRequests with head and
// tail indices inside Pathfinder; BFME 2 factors it into this ring. The
// ring's class and member names are descriptive, not recovered.

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;

enum ObjectID
{
	INVALID_ID = 0
};

class AsciiString; class UnicodeString; class PooledString; class Coord3DBase; class ICoord3D;
class Region3D; class IRegion3D; class Coord2D; class ICoord2D; class Region2D; class IRegion2D;
class RealRange; class RGBColor; class RGBAColorReal; class RGBAColorInt; class Snapshot;
class XferUnknown11;

// Retail's Xfer vtable: MSVC lays the operator== overloads out in reverse
// declaration order, which puts the unsigned int transfer at slot 0x78.
class Xfer
{
public:
	class Version;

	void Version1();	// 0x000053EE

	virtual ~Xfer();
	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;
	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;
	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3DBase &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);	// 0x0060C36E
	XferException(const XferException &that);
	~XferException();

	char *text;
	int tag;
};

void XferObjectID(Xfer *xfer, ObjectID *objectID);	// 0x003060B2

class PathfindRequestRing
{
public:
	enum { RING_SIZE = 512 };

	Bool hasRoom() const;
	void push(const ObjectID &id);
	Bool contains(const ObjectID &id) const;
	void rva002EAC9F(Xfer *xfer);

private:
	static UnsignedInt next(UnsignedInt slot) { return slot != RING_SIZE - 1 ? slot + 1 : 0; }

	ObjectID m_requests[RING_SIZE];
	UnsignedInt m_head;
	UnsignedInt m_tail;
};

Bool PathfindRequestRing::hasRoom() const
{
	return next(m_tail) != m_head;
}

void PathfindRequestRing::push(const ObjectID &id)
{
	m_requests[m_tail] = id;
	m_tail = next(m_tail);
}

Bool PathfindRequestRing::contains(const ObjectID &id) const
{
	for (UnsignedInt slot = m_head; slot != m_tail; slot = next(slot))
	{
		if (m_requests[slot] == id)
			return true;
	}
	return false;
}

void PathfindRequestRing::rva002EAC9F(Xfer *xfer)
{
	xfer->Version1();
	(*xfer == m_head) == m_tail;
	UnsignedInt size = RING_SIZE;
	*xfer == size;
	if (size != RING_SIZE)
		throw XferException(4, "Unexpected queue size");
	for (UnsignedInt slot = m_head; slot != m_tail; slot = next(slot))
		XferObjectID(xfer, &m_requests[slot]);
}
