// cl: /DNDEBUG /MD /EHsc /Ob2
//
// Target facts from retail RVA 0x00113151: the 73-byte interval ends at
// 0x0011319A. It returns immediately when this+0x5C is null. Otherwise it
// optionally retains the incoming object, releases the prior object's +4
// count through vtable slot 0 when that count reaches zero, and stores the
// incoming pointer at this+0x5C. If byte this+0x60 is set, it calls
// 0x00112AD1 with two zero values, this+0x58, and the second float argument.
// The adjacent 0x00113110 REL32 supports a shared address-derived holder view;
// class and method identities remain unproven. Resource layout follows the
// target's vptr slot-0 and +4 count accesses. The callback pin records only
// its call target and stack shape; its body remains unrecovered.

class Rva00113151Resource
{
public:
	virtual void rva00113151Release() = 0;

private:
	int m_referenceCount;
	friend class Rva00113110Holder;
};

class W3DTerrainBackground
{
public:
	void setFlipRecursive(int arg0, int arg1, int arg2, float arg3);	// rowed 0x00112AD1
};

class Rva00113110Holder
{
public:
	void rva00113151(void *incoming, float value);

private:
	char m_pad00[0x58];
	int m_callbackContext;
	Rva00113151Resource * volatile m_resource;
	unsigned char m_refresh;
};

void Rva00113110Holder::rva00113151(void *incoming, float value)
{
	if (m_resource == 0) {
		return;
	}
	if (incoming != 0) {
		++*(int *)((char *)incoming + 4);
		Rva00113151Resource *old = m_resource;
		if (old != 0 && --old->m_referenceCount == 0) {
			old->rva00113151Release();
		}
		m_resource = (Rva00113151Resource *)incoming;
	}
	if (m_refresh != 0) {
		((W3DTerrainBackground *)this)->setFlipRecursive(0, 0, m_callbackContext, value);
	}
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x00112AD1 -> ?setFlipRecursive@W3DTerrainBackground@@QAEXHHHM@Z (defined by Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DTerrainBackgroundSetFlipRecursiveTolerance.cpp)
#pragma comment(linker, "/alternatename:?rva00112AD1@Rva00112AD1@@QAE_NHHHM@Z=?setFlipRecursive@W3DTerrainBackground@@QAEXHHHM@Z")
