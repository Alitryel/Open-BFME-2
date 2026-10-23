// cl: /MD
// These derived destructors install their own vtable and destroy AptValueWithHash.
// The retail tail calls reach its complete destructor at 0x006D63C0.
class AptValueWithHash
{
protected:
	virtual ~AptValueWithHash();
};

// Pooled classes: the scalar deleting destructors emitted here release
// through the chain-block pool at 0x00E176F4 with the class size, as retail's
// do (rowed here; previously modelled by address-named views in
// Rva006CBF40Siblings.cpp).
class Rva006D2A60
{
public:
	void freeBlock(void *block, int blockSize);
};

extern Rva006D2A60 *g_pChainBlockAllocatorF4;   // 0x00E176F4

class Rva006DE2B0 : public AptValueWithHash
{
public:
	virtual ~Rva006DE2B0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x1C]; // sizeof 0x20
};

Rva006DE2B0::~Rva006DE2B0()
{
}

class Rva006DE6C0 : public AptValueWithHash
{
public:
	virtual ~Rva006DE6C0();
	static void operator delete(void *p, unsigned int size)
	{
		g_pChainBlockAllocatorF4->freeBlock(p, size);
	}
	char m_pad[0x1C]; // sizeof 0x20
};

Rva006DE6C0::~Rva006DE6C0()
{
}
