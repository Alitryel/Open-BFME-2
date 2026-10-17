// ?rva000BB3E6@Rva000BB3E6@@QAEXHHHHVAsciiString@@PBVFXList@@@Z
// partial score=0.99 date=2026-10-17
// ?rva000BB3E6@Rva000BB3E6@@QAEXHHHHVAsciiString@@PBVFXList@@@Z
// partial score=0.947068 date=2026-10-15
// ?rva000BB3E6@Rva000BB3E6@@QAEXHHHHVAsciiString@@PBVFXList@@@Z
// partial score=0.836 date=2026-10-15
// ?rva000BB3E6@Rva000BB3E6@@QAEXHHHHVAsciiString@@PBVFXList@@@Z
// partial score=0.96 date=2026-10-03
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /arch:SSE /GX
// ?rva000BB3E6@Rva000BB3E6@@QAEXHHHHVAsciiString@@PBVFXList@@@Z 0x000BB3E6 171B
// Evidence: unlock lane; callees rowed doFXPos 0x94C29 doFXObj 0xB2235 releaseBuffer 0x36410; bone-empty check is AsciiString::isEmpty (mov eax+cmp+cmp word [eax+4]); str()+8 for virtual +0xD0; translation m[3,7,11] to Coord; speed 0.0 secondary NULL.
#include "ascii_string.h"

struct Coord3D
{
	float x;
	float y;
	float z;
};

class Matrix3D
{
public:
	float m[12];
};

class Object;
class FXList
{
public:
	void doFXPos(const Coord3D *pos, const Matrix3D *mtx, float speed, const Coord3D *secondary) const;
	bool rva001E2EF1() const;
	static void doFXPos(const FXList *fx, const Coord3D *primary, const Matrix3D *mtx, float speed, const Coord3D *secondary);
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

class Rva000BB3E6Drawer
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12(); virtual void v13(); virtual void v14(); virtual void v15();
	virtual void v16(); virtual void v17(); virtual void v18(); virtual void v19();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v30(); virtual void v31();
	virtual void v32(); virtual void v33(); virtual void v34(); virtual void v35();
	virtual void v36(); virtual void v37(); virtual void v38(); virtual void v39();
	virtual void v40(); virtual void v41(); virtual void v42(); virtual void v43();
	virtual void v44(); virtual void v45(); virtual void v46(); virtual void v47();
	virtual void v48(); virtual void v49(); virtual void v50(); virtual void v51();
	virtual void getBoneMatrix(Matrix3D *out, const char *bone);
};

struct Rva000BB3E6Holder
{
	unsigned char m_pad[0xFC];
	unsigned int m_objAddr;
};

class Rva000BB3E6
{
public:
	void rva000BB3E6(int a, int b, int c, int d, AsciiString bone, const FXList *fx);
private:
	unsigned char m_pad0[8];
	Rva000BB3E6Holder *m_holder;
	unsigned char m_padC[0x50 - 0x0C];
	Rva000BB3E6Drawer *m_drawer;
};

// ?rva000BB3E6@Rva000BB3E6@@QAEXHHHHVAsciiString@@PBVFXList@@@Z present-unmatched
void Rva000BB3E6::rva000BB3E6(int a, int b, int c, int d, AsciiString bone, const FXList *fx)
{
	if (fx == 0)
		return;
	if (!bone.isEmpty())
	{
		Matrix3D mtx;
		m_drawer->getBoneMatrix(&mtx, bone.str());
		Coord3D pos;
		pos.x = mtx.m[3];
		pos.y = mtx.m[7];
		pos.z = mtx.m[11];
		FXList::doFXPos(fx, &pos, &mtx, 0.0f, 0);
	}
	else
	{
		volatile Rva000BB3E6Holder *holder = m_holder;
		if (holder->m_objAddr != 0)
			FXList::doFXObj(fx,
				m_holder->m_objAddr != 0 ? (const Object *)m_holder->m_objAddr : (const Object *)0, 0);
	}
}
