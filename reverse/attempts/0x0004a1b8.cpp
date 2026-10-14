// ?rva0004A1B8@Rva0004A1B8@@QAEXXZ
// partial score=0.5 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// Address-derived W3DDisplay skirmish-AI stats painter, retail
// 0x0004A1B8..0x0004A3C4 (524 bytes, ret 0, WB 0x0096CC30 names
// W3DDisplay::drawSkirmishAIStats).
// Layout read from retail: player count ThePlayerList+0x14, the looked-up
// record's inner vector at +0x164 (+0x20 begin / +0x24 end) of 4-byte
// element pointers with x/y/z at +4/+8/+0xC and the extra float at +0x14;
// the second lookup's object +0x10 is an Rva00049D20 whose pointer array
// begins at +0x10 and ends at +0x14; TheDisplay+0x2C is the 3D transform
// renderer (slot 0x38); this+0x1CC is the DisplayString whose slots
// 0x28/0x38/0x3C finish the frame.  All callees are rowed.
typedef int Int;

class Matrix3D
{
public:
	float m[3][4];
};

class Player;

class PlayerList
{
public:
	Player *getNthPlayer(Int index);
	char m_pad00[0x14];
	Int m_playerCount;			// +0x14
};
extern PlayerList *ThePlayerList;

class Player
{
public:
	bool rva002AA245() const;	// 0x002AA245
	char m_pad00[0x280];
	Int m_280;					// +0x280
};

struct Rva002A8AB1Record;
class Rva002A8F24
{
public:
	Rva002A8AB1Record *rva002A8AB1(void *player);	// 0x002A8AB1
	void *rva002A8F24(Player *player);				// 0x002A8F24
};
extern Rva002A8F24 *g_00DFEEF8;

class Rva00049D20
{
public:
	void *rva00049D20(void *out, Int index);		// 0x00049D20
	char m_pad00[0x10];
	void **m_array;				// +0x10
	void **m_arrayEnd;			// +0x14
};

struct Rva0004A1B8Inner
{
	char m_pad00[0x20];
	void **m_begin;				// +0x20
	void **m_end;				// +0x24
};
struct Rva0004A1B8Record
{
	char m_pad00[0x164];
	Rva0004A1B8Inner *m_inner;	// +0x164
};
struct Rva0004A1B8Element
{
	char m_pad00[4];
	float m_x;					// +4
	float m_y;					// +8
	float m_z;					// +0xC
	char m_pad10[4];
	float m_extra;				// +0x14
};

class Rva0004A1B8Renderer
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10();
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14(const Matrix3D &, float, Int, Int, Int);	// +0x38
};

class Display
{
public:
	char m_pad00[0x2C];
	Rva0004A1B8Renderer *m_2C;	// +0x2C
};
extern Display *TheDisplay;

class Rva0004A1B8String
{
public:
	virtual void v00();
	virtual void v01();
	virtual void v02();
	virtual void v03();
	virtual void v04();
	virtual void v05();
	virtual void v06();
	virtual void v07();
	virtual void v08();
	virtual void v09();
	virtual void v10(Int, Int);					// +0x28
	virtual void v11();
	virtual void v12();
	virtual void v13();
	virtual void v14(Int, Int, Int, Int);		// +0x38
	virtual void v15(Int *, Int *);				// +0x3C
};

class Rva0004A1B8
{
public:
	void rva0004A1B8();

private:
	char m_pad00[0x1CC];
	Rva0004A1B8String *m_1CC;	// +0x1CC
};

void Rva0004A1B8::rva0004A1B8()
{
	for (Int i = 0; i < ThePlayerList->m_playerCount; ++i) {
		Player *player = ThePlayerList->getNthPlayer(i);
		if (!player->rva002AA245())
			continue;

		Rva002A8AB1Record *record = g_00DFEEF8->rva002A8AB1(player);
		if (record) {
			Rva0004A1B8Inner *inner = ((Rva0004A1B8Record *)record)->m_inner;
			void **end = inner->m_end;
			for (void **it = inner->m_begin; it != end; ++it) {
				Rva0004A1B8Element *e = (Rva0004A1B8Element *)*it;
				Matrix3D matrix;
				matrix.m[0][0] = 1.0f; matrix.m[0][1] = 0.0f; matrix.m[0][2] = 0.0f; matrix.m[0][3] = e->m_x;
				matrix.m[1][0] = 0.0f; matrix.m[1][1] = 1.0f; matrix.m[1][2] = 0.0f; matrix.m[1][3] = e->m_y;
				matrix.m[2][0] = 0.0f; matrix.m[2][1] = 0.0f; matrix.m[2][2] = 1.0f; matrix.m[2][3] = e->m_z;
				TheDisplay->m_2C->v14(matrix, e->m_extra, (Int)0xffff0000, 0, 1);
			}
		}

		if (g_00DFEEF8->rva002A8F24(player)) {
			Rva00049D20 *vec = (Rva00049D20 *)*(void **)((char *)g_00DFEEF8->rva002A8F24(player) + 0x10);
			for (Int j = 0; j < (Int)(vec->m_arrayEnd - vec->m_array); ++j) {
				void *tmp;
				float *p = (float *)vec->rva00049D20(&tmp, j);
				Matrix3D matrix;
				matrix.m[0][0] = 1.0f; matrix.m[0][1] = 0.0f; matrix.m[0][2] = 0.0f; matrix.m[0][3] = p[0];
				matrix.m[1][0] = 0.0f; matrix.m[1][1] = 1.0f; matrix.m[1][2] = 0.0f; matrix.m[1][3] = p[1];
				matrix.m[2][0] = 0.0f; matrix.m[2][1] = 0.0f; matrix.m[2][2] = 1.0f; matrix.m[2][3] = p[2];
				TheDisplay->m_2C->v14(matrix, *(float *)((char *)vec->m_array[j] + 4), player->m_280, 0, 1);
			}
		}
	}

	Int w, h;
	m_1CC->v10(-1, (Int)0xff000000);
	m_1CC->v14(3, 3, 1, 1);
	m_1CC->v15(&w, &h);
}
