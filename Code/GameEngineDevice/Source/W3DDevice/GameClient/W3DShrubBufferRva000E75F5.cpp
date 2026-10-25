// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// W3DShrubBuffer::removeTreeAtIndex, retail 0x000E75F5 (195 bytes, ret 4). Open-BFME-1 twin:
// W3DShrubBuffer_removeTreeAtIndex.cpp (0x0071D020), here in plain form: a tree in the toppling state snaps to its
// upright type (or the toppled type while a push-aside model exists), drops its topple and push-aside models (a
// shrub with none resets the rows that share its key) and leaves the toppling state. BFME2 layout: 2000 records
// of 0xA0 at +0x1958, count +0x4FB58, changed byte +0x4FB5C.
#define COORD3D_VIEW_INLINE
#include "../../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../../Libraries/Include/Lib/Coord2D.h"
typedef int Int;


class Rva000E75F5RenderObjClass
{
public:
	virtual void Delete_This(void);
	virtual void slot04(void); virtual void slot08(void); virtual void slot0c(void);
	virtual void slot10(void); virtual void slot14(void); virtual void slot18(void); virtual void slot1c(void);
	virtual void slot20(void); virtual void slot24(void); virtual void slot28(void); virtual void slot2c(void);
	virtual void slot30(void); virtual void slot34(void); virtual void slot38(void); virtual void slot3c(void);
	virtual void Remove(void);

	void Release_Ref(void)
	{
		--m_refCount;
		if (m_refCount == 0)
			Delete_This();
	}

	Int m_refCount;
};

struct Rva000E75F5Tree
{
	Coord3D m_position; float m_scale;
	unsigned char m_pad10[0x40 - 0x10];
	Int m_treeType;
	bool m_enabled; unsigned char m_pad45[0x58 - 0x45];
	Int m_key;
	unsigned char m_pad5c[0x84 - 0x5c];
	Int m_state;
	Int m_uprightType;
	Int m_toppledType;
	unsigned char m_pad90[0x94 - 0x90];
	Rva000E75F5RenderObjClass *m_topple;
	Rva000E75F5RenderObjClass *m_pushAside;
	unsigned char m_pad9c[0xa0 - 0x9c];
};

struct Rva000E7546TypeRecord {
 void *m_valid; char at04[0x2C-4];
 Coord2D m_shadowA; char at34[0x3C-0x34];
 Coord2D m_shadowB; bool m_ready; char at45[0x5C-0x45];
};
// The record and type arrays are spelled as W3DShrubBuffer.cpp's own view spells them (opaque element storage);
// this body reads them through its local element views above.
class Rva000E9C1DRecord
{
public:
	Rva000E9C1DRecord();
private:
	unsigned char m_storage[0xA0];
};

class Rva000E9C1DType
{
public:
	Rva000E9C1DType();
	~Rva000E9C1DType();
private:
	unsigned char m_storage[0x5C];
};

class W3DShrubBuffer
{
public:
	void rva000E75F5(Int index);
 bool rva000E7546(Int index, float *outPos, float *outScale, Coord2D *outShadowA, Coord2D *outShadowB);
	void rva000E70D9(Int key);

private:
	Rva000E75F5Tree &tree75F5(Int i) { return reinterpret_cast<Rva000E75F5Tree *>(m_records)[i]; }
	Rva000E7546TypeRecord &type7546(Int t) { return reinterpret_cast<Rva000E7546TypeRecord *>(m_types)[t]; }
	unsigned char m_pad0000[0x1958];
	Rva000E9C1DRecord m_records[2000];
	Int m_count;
	unsigned char m_4fb5c;
	unsigned char m_pad4fb5d[0x4FB70 - 0x4FB5D];
	Rva000E9C1DType m_types[64];
};

void W3DShrubBuffer::rva000E75F5(Int index)
{
	if (index >= m_count)
		return;
	if (tree75F5(index).m_treeType < 0)
		return;
	if (tree75F5(index).m_state == 1) {
		if (tree75F5(index).m_pushAside != 0)
			tree75F5(index).m_treeType = tree75F5(index).m_toppledType;
	} else {
		tree75F5(index).m_treeType = tree75F5(index).m_uprightType;
	}
	if (tree75F5(index).m_topple != 0) {
		tree75F5(index).m_topple->Remove();
		if (tree75F5(index).m_topple != 0) {
			tree75F5(index).m_topple->Release_Ref();
			tree75F5(index).m_topple = 0;
		}
	}
	if (tree75F5(index).m_pushAside != 0) {
		tree75F5(index).m_pushAside->Remove();
		if (tree75F5(index).m_pushAside != 0) {
			tree75F5(index).m_pushAside->Release_Ref();
			tree75F5(index).m_pushAside = 0;
		}
	} else {
		rva000E70D9(tree75F5(index).m_key);
	}
	tree75F5(index).m_state = 0;
	m_4fb5c = true;
}

static inline void copyShrubPosition(float *out, const Coord3D *position)
{
 out[0] = position->x; out[1] = position->y; out[2] = position->z;
}
// BF1 f98983a7 W3DShrubBufferRva0071CF40 is the semantic guide.
// BFME2's existing removeTreeAtIndex independently proves160B entries,
// not the donor164B stride; native175 proves all four copied outputs.
bool W3DShrubBuffer::rva000E7546(Int index, float *outPos, float *outScale, Coord2D *outShadowA, Coord2D *outShadowB)
{
 if (index < m_count) {
  Int type = tree75F5(index).m_treeType;
  if (type >= 0 && tree75F5(index).m_enabled && type7546(type).m_valid && type7546(type).m_ready) {
   copyShrubPosition(outPos, &tree75F5(index).m_position);
   *outScale = tree75F5(index).m_scale * 10.0f;
   *outShadowA = type7546(type).m_shadowA;
   *outShadowB = type7546(type).m_shadowB;
   return true;
  }
 }
 return false;
}
