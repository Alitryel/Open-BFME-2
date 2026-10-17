// ?rva0055DDD1@Rva0055DDD1@@QAEXXZ
// partial score=0.102 date=2026-10-17
// cl: /Oy- /DNDEBUG /MD /GX
//
// ?get@Rva0055DDB6SmartField@@QBE?AVRvaSmartPtr12@@XZ, retail 0x0055DDB6, 27 bytes.
// Value-returning smart-pointer getter same shape as siblings 0x003FDA90
// (member +0x15C, 30B) and 0x001F6C54 (member +0x68, 27B) via the rowed copy
// at 0x4CC19: returns the 12-byte member at +0x04 through the hidden return
// pointer (RVO). Callers at 0x0055DE57 0x0055F885 0x005623AA use a 12-byte
// temp plus the rowed handle dtor; landing unblocks 0x0055F840 0x0055DDD1
// 0x00562366.
class RvaSmartPtr12
{
public:
	RvaSmartPtr12(const RvaSmartPtr12 &that);
	~RvaSmartPtr12();

private:
	void *m_ptr;
	int m_pad04;
	int m_pad08;
};

class Rva0055DDB6SmartField
{
public:
	RvaSmartPtr12 get() const;

private:
	char m_pad[4];
	RvaSmartPtr12 m_value;
};

// Random variable with a float value accessor (retail 0x006341A1).
class GameClientRandomVariable
{
public:
	float getValue() const;

private:
	char m_pad[4];
};

// 3-float vector with a normalize() member (retail 0x004035B6).
class Coord3D
{
public:
	void normalize();

	float x;
	float y;
	float z;
};

// The object behind the smart pointer; only the fields the retail body reads.
class ParticleSystem
{
public:
	char m_pad00[0xBC];
	float m_00bc;
	float m_00c0;
	float m_00c4;
	float m_00c8;
	float m_00cc;
	float m_00d0;
	float m_00d4;
	float m_00d8;
	float m_00dc;
	float m_00e0;
	float m_00e4;
	float m_00e8;
	char m_padEC[0x188 - 0xEC];
	float m_0188;
	float m_018c;
	float m_0190;
	unsigned char m_0194;
};

ParticleSystem *Make001FCBD7();

class Rva0055DDD1
{
public:
	void rva0055DDD1();

private:
	char m_pad00[0x24];
	Coord3D m_24;
	Coord3D m_30;
	GameClientRandomVariable m_3c;
	GameClientRandomVariable m_48;
	GameClientRandomVariable m_54;
	GameClientRandomVariable m_60;
	GameClientRandomVariable m_6c;
	GameClientRandomVariable m_78;
	GameClientRandomVariable m_84;
	GameClientRandomVariable m_90;
	GameClientRandomVariable m_9c;
};

class RvaGuardHelper
{
public:
	RvaGuardHelper(int f3, int f2, int f1, int s, int n);
	~RvaGuardHelper();
	Coord3D pts[0x1E];
};
void Rva0055DDD1::rva0055DDD1()
{
	{
	RvaSmartPtr12 tmpSp = ((Rva0055DDB6SmartField *)this)->get();
	(void)*(volatile void **)&tmpSp;
	}
	static RvaGuardHelper s_points_wrap((1 ? 0x0C : 0x0C), 0x1E, 0x87a6a9, 0x4b3fd0, 0xbb93ec);
	struct { Coord3D v; unsigned char pad[12]; } pad_v0;
	if (m_pad00[0] == 0)
		return;
	Coord3D *s_points = s_points_wrap.pts;
	Coord3D v0 = m_24;
	Coord3D v1 = m_30;
	float p0 = m_3c.getValue();
	float p1 = m_48.getValue();
	float p2 = m_54.getValue();
	float p3 = m_60.getValue();
	float p4 = m_6c.getValue();
	float p5 = m_78.getValue();
	float p6 = m_84.getValue();
	float p7 = m_90.getValue();
	float p8 = m_9c.getValue();
	Coord3D d;
	d.x = v1.x - v0.x;
	d.y = v1.y - v0.y;
	d.z = v1.z - v0.z;
	d.normalize();
	{
		Coord3D e;
		e.x = d.x; e.y = d.y; e.z = d.z;
		e.normalize();
		d = e;
	}
	for (int i = 0; i < 0x1E; i++)
	{
		float t = (float)i;
		float s0 = (float)(double)(t * p0 + p1);
		float s1 = (float)(double)(t * p4 + p5);
		float s2 = (float)(double)(t * p7 + p8);
		(void)s0; (void)s1; (void)s2;
		s_points[i].x = v0.x + d.x * t;
		s_points[i].y = v0.y + d.y * t;
		s_points[i].z = v0.z + d.z * t;
	}
	Coord3D e = d;
	e.normalize();
	Rva0055DDB6SmartField *fld = (Rva0055DDB6SmartField *)this;
	RvaSmartPtr12 sp = (1 ? fld->get() : fld->get());
	ParticleSystem *p = (ParticleSystem *)*(void **)&sp;
	if ((p != 0 ? p : p)->m_0194 != 0)
	{
		(void)p->m_00bc; (void)p->m_00c0; (void)p->m_00c4;
		(void)p->m_00c8; (void)p->m_00cc; (void)p->m_00d0;
		(void)p->m_00d4; (void)p->m_00d8; (void)p->m_00dc;
		(void)p->m_00e0; (void)p->m_00e4; (void)p->m_00e8;
		(void)p->m_0188; (void)p->m_018c; (void)p->m_0190;
	}
	(void)p3; (void)p6; (void)p2;
}
