// cl: /Os /DNDEBUG /MD /arch:SSE
// ?rva0010953E@Rva0010959E@@QAEXXZ retail 0x0010953E 96B
// Related sibling: Code/GameEngine/Source/Common/Rva0010959E.cpp (20B tail-call).
// Zeroes +0x4/+0x5 and floats +0x8/+0xC/+0x10/+0x20 on this and on both
// m_58/m_5c shadow objects; -1 at +0x28 and 0 at +0x68 on each shadow.
// The two adjacent flag bytes are written through a byte pointer so the
// compiler keeps the [ecx+4]=1 store ahead of the shared zeroing of edx,
// matching retail's schedule; the barrier still holds the m_58 load late.
struct ShadowObj
{
	char m_pad0[8];
	float m_8;
	float m_C;
	float m_10;
	char m_pad14[12];
	float m_20;
	char m_pad24[4];
	int m_28;
	char m_pad2C[60];
	int m_68;
};
class Rva0010959E
{
public:
	void rva0010953E();
private:
	char m_pad0[4];
	unsigned char m_4;
	unsigned char m_5;
	char m_pad6[2];
	float m_8;
	float m_C;
	float m_10;
	char m_pad14[12];
	float m_20;
	char m_pad24[52];
	ShadowObj *m_58;
	ShadowObj *m_5c;
	int m_60;
};
extern "C" void _ReadWriteBarrier();
void Rva0010959E::rva0010953E()
{
	unsigned char *q = &m_4;
	q[0] = 1;
	q[1] = 0;
	m_10 = 0.0f;
	m_C = 0.0f;
	m_8 = 0.0f;
	_ReadWriteBarrier();
	ShadowObj *shadowObj = m_58;
	m_20 = 0.0f;
	m_60 = 0;
	shadowObj->m_28 = -1;
	shadowObj->m_68 = 0;
	shadowObj->m_10 = 0.0f;
	shadowObj->m_C = 0.0f;
	shadowObj->m_8 = 0.0f;
	shadowObj->m_20 = 0.0f;
	_ReadWriteBarrier();
	ShadowObj *p2 = m_5c;
	p2->m_28 = -1;
	p2->m_68 = 0;
	p2->m_10 = 0.0f;
	p2->m_C = 0.0f;
	p2->m_8 = 0.0f;
	p2->m_20 = 0.0f;
}
