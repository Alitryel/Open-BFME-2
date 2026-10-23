// ?rva006C1EB0@Rva006C1F60@@QAEXMII@Z @ 0x006C1EB0 172B
// Scale/min/max setter for the lock-guarded clamped scaler: stores the args
// to +0x534/+0x538/+0x53c clamps scale to [0.0 8.0] and min to max then clears
// flag bit 0x800 at +0x514 when scale is 0.0 or max is 0. Evidence: calls AddRef
// 0x00030DD0 Release 0x00030DF0 __ftol2 rowed; float constants 0.0 at 0x7BAEAC
// 8.0 at 0x7C2A10; same +0x4e4/+0x514/+0x534/+0x538/+0x53c layout as getter
// 0x006C1F60; no caller yet (chain of 0x00030DF0). Honest address-derived method
// of Rva006C1F60. No // cl: line (defaults match the frameless x87 shape).
struct Rva00030DD0Lock;
int Rva00030DD0AddRef(Rva00030DD0Lock *lock);
int Rva00030DF0Release(Rva00030DD0Lock *lock);

class Rva006C1F60
{
public:
	void rva006C1EB0(float scale, unsigned int mn, unsigned int mx);
private:
	unsigned char m_pad0[0x4e4];
	Rva00030DD0Lock *m_lock;
	unsigned char m_pad1[0x514 - 0x4e4 - 4];
	int m_flags;
	unsigned char m_pad2[0x534 - 0x514 - 4];
	float m_scale;
	unsigned int m_min;
	unsigned int m_max;
};

void Rva006C1F60::rva006C1EB0(float scale, unsigned int mn, unsigned int mx)
{
	Rva00030DD0Lock *lock = m_lock;
	if (lock != 0)
		Rva00030DD0AddRef(lock);
	m_scale = scale;
	m_min = mn;
	m_max = mx;
	if (m_scale < 0.0f)
		m_scale = 0.0f;
	if (m_scale > 8.0f)
		m_scale = 8.0f;
	if (m_min > m_max)
		m_min = m_max;
	if (m_scale == 0.0f || m_max == 0)
		m_flags &= ~0x800;
	if (lock != 0)
		Rva00030DF0Release(lock);
}
