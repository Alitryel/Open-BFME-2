// cl: /DNDEBUG /MD /EHsc
// W3DSmudgeManager::ReleaseResources, retail 0x000A6135, 65 bytes.
//
// The lock and unlock at either end are a guard object, not two bare calls:
// that is what gives the body its SEH frame and the two unwind writes, which
// bracket exactly the region between the constructor and the destructor. Both
// halves are free functions the ledger already names.
//
// Between them one reference-counted handle at +0x34 is released -- the count
// at +0x04 of the target dropped in place, slot 0 of its table entered with no
// argument when it reaches zero -- and the pointer cleared.

typedef int Int;

void BFME_DX8_Thread_Lock(void);					// retail 0x00903090
bool BFME_DX8_Thread_Assert(void);					// matched release half at 0x00120F50

class BfmeRadarResetLock
{
public:
	BfmeRadarResetLock() { BFME_DX8_Thread_Lock(); }
	~BfmeRadarResetLock() { BFME_DX8_Thread_Assert(); }
};

class IndexBufferRef
{
public:
	virtual void destroy(void);					// slot 0

	Int m_refCount;							// +0x04
};

// Base extent: native index slot at +0x34; upstream class is in GameClient/Smudge.h.
class SmudgeManager
{
public:
	virtual ~SmudgeManager();

private:
	char m_body[0x20];
};

class DX8IndexBufferClass;

class W3DSmudgeManager : public SmudgeManager
{
public:
	virtual void ReleaseResources(void);

private:
	void *m_smudgeGroup;
	void *m_posBuffer;
	void *m_RGBABuffer;
	void *m_sizeBuffer;
	DX8IndexBufferClass *m_indexBuffer;
};

// ?ReleaseResources@W3DSmudgeManager@@UAEXXZ
void W3DSmudgeManager::ReleaseResources(void)
{
	BfmeRadarResetLock lock;

	// Keep the seed header's slot type; view only the native refcount prefix.
	// Retail decrements its count at +4 and calls slot zero when it reaches zero.
	IndexBufferRef *indexBuffer = reinterpret_cast<IndexBufferRef *>(m_indexBuffer);

	if (indexBuffer)
	{
		if (--indexBuffer->m_refCount == 0)
			indexBuffer->destroy();

		m_indexBuffer = 0;
	}
}
