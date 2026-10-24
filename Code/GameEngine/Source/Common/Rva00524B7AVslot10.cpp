// cl: /O1 /MD /arch:SSE
//
// ?update@Rva00524B7A@@UAEXXZ @ 0x00524AE7 (147B).
// Virtual slot 10 (offset 0x28) of the MovieWindowPlayback vtable at
// 0x00867DFC. The class is spelled with an address-derived name because the
// owner TU (Rva00524B7ACtor.cpp) keeps a non-polymorphic explicit-vptr view
// for its matched ctor 0x00524B7A and OpenMovie 0x00524D01; declaring these
// virtuals there would insert the compiler vptr and shift every field.
//
// Layout carried from that owner TU: vtable +0, base pad 8, m_0C at +0xC,
// ints +0x10..+0x1C, m_20 at +0x20, flags m_24, color m_28, times m_2C/m_30,
// functor m_34 plus arg m_38. Evidence: timeGetTime IAT, rowed FunctorRef
// invoke 0x0057CC15, tail to slot 9 at [eax+0x24], virtual check on the +0x0C
// object at [eax+0x18]. Identity is address-derived; the class/fields remain
// structural views of the vtable owner. The two volatile members are a
// measured scheduling qualifier (they make the compiler emit the target's
// add-then-sub form of the remaining-time sum), not a target layout fact.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

extern "C" __declspec(dllimport) unsigned long __stdcall timeGetTime();

class Rva0057CC15Ref
{
public:
	void invoke(int a);
};

class Rva00524B7A_0C
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual unsigned char check(int v);
};

class Rva00524B7A
{
public:
	virtual void s00() = 0;
	virtual void s01() = 0;
	virtual void s02() = 0;
	virtual void s03() = 0;
	virtual void s04() = 0;
	virtual void s05() = 0;
	virtual void s06() = 0;
	virtual void s07() = 0;
	virtual void s08() = 0;
	virtual void tail() = 0;
	virtual void update();
private:
	char m_basePad[8];
	Rva00524B7A_0C *m_0C;
	volatile int m_10;
	int m_14;
	int m_18;
	int m_1C;
	int m_playbackFlags;
	unsigned char m_flags;
	char m_pad25[3];
	int m_color;
	int m_fadeDuration;
	volatile int m_fadeStartTime;
	Rva0057CC15Ref m_completionCallback;
	int m_completionCallbackArg;
};

void Rva00524B7A::update()
{
	if (m_0C == 0)
		return;
	if ((m_flags & 4) != 0)
	{
		int *pTotal = &m_fadeDuration;
		unsigned long now = timeGetTime();
		unsigned int total = (unsigned int)*pTotal;
		_ReadWriteBarrier();
		int remain = (int)(total + (unsigned int)m_fadeStartTime);
		remain = remain - (int)now;
		unsigned int v;
		if (remain > 0)
			v = (unsigned int)remain;
		else
			v = 0;
		_ReadWriteBarrier();
		v = v > total ? total : v;
		unsigned int alpha = (v * 255u) / total;
		unsigned char alphaByte = (unsigned char)alpha;
		m_color = (int)(((unsigned int)alphaByte << 24) | 0xFFFFFF);
	}
	if ((m_flags & 2) == 0)
		goto check0c;
	if ((m_playbackFlags & 0x80) != 0)
		return;
check0c:
	unsigned char r = m_0C->check(m_playbackFlags);
	if ((r & 2) == 0)
		return;
	if ((m_flags & 2) != 0)
		return;
	m_flags |= 2;
	if (*(void **)&m_completionCallback != 0)
		m_completionCallback.invoke(m_completionCallbackArg);
	if ((m_playbackFlags & 0x84) != 0)
		return;
	return tail();
}
