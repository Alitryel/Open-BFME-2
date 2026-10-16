// cl: /O1 /arch:SSE /G7 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/shims/sweep /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /ICode/Libraries/Include
// BFME 1 W3DProjectedShadowDecalHelpers.cpp, donor revision
// 1399ad37d42ea52a63829e417c46a1ba9ed2cd20, compiled with BFME 2 flags above.
// These file-static algorithms come from ZH queueDecal: flatten/normalise the
// transform axes, and find the extrema of four projected corner coordinates.
// Their original private names are unknown, so names retain target addresses.
// Native axes body 0x108E7A..0x108FBD (323B), Ghidra FUN_00508e7a. Calls at
// 0x10ACAB / 0x10ACBF / 0x10CB9C pass Matrix3D in ESI and two Vector3 outputs
// in ECX/EDX. X/Y basis elements are +0/+0x10 and +4/+0x14; output Z is zero.
// Native extrema body 0x108E33..0x108E7A (71B), immediately after the thunk
// at 0x108E28. Inputs use XMM1/2/3 and one stack float; hidden Vector2 output
// is EAX. The projected-range body at 0x108FBD inlines the same extrema logic.
// A compiler-visible caller preserves both private conventions, as MSVC 7.1
// derives them from same-unit calls. It is an emission pattern, not a retail
// caller recovery. All body bytes and compiler float literals are verified.
// Native layer helper1086EC..108790164: ZH queueDecal bridge-layer
// semantic guide; WB queueDualDecal names the caller. Object getter28B511
// confirms layer40C/override48C; native user-data slot87 and drawableFC.
// Raw byte access to drawable object preserves private EAX/EBX/ESI ABI.
// W3DProjectedShadowManager::queueDualDecal (native 0x10A736..0x10B9B5, 4737B,
// RET 4, EH) is the real same-unit caller of the axes, layer and range helpers;
// WB 0x8CEAC0 names it and is the source-shape guide (per-decal size/offset
// arrays, per-loop counters, getDecalOffset/getAngle/getPosition accessors),
// ZH queueDecal the semantic guide. Its getDecalOffset(1) call is the
// out-of-line accessor copy at 0x1089EA (cl inlines the [0] call only).
// The remaining emission pattern anchors only the extrema helper.
#include "wwmath.h"
#include "vector3.h"
#include "matrix3d.h"
#include "Lib/Coord3D.h"
#include <math.h>
#define __max(a,b) (((a)>(b))?(a):(b))
#define __min(a,b) (((a)<(b))?(a):(b))

// Scoped storage views use the evidenced 12B vector, 8B pair, and 3x4 matrix
// representations without defining copies of the public math-library methods.
class Rva00108E7AVector
{
public:
    float X, Y, Z;
    WWINLINE Rva00108E7AVector() {}
    WWINLINE Rva00108E7AVector(float x, float y, float z) { X=x; Y=y; Z=z; }
    WWINLINE Rva00108E7AVector &operator=(const Rva00108E7AVector &v)
    { X=v.X; Y=v.Y; Z=v.Z; return *this; }
    WWINLINE Rva00108E7AVector &operator*=(float k)
    { X=X*k; Y=Y*k; Z=Z*k; return *this; }
    WWINLINE void Set(float x, float y, float z) { X=x; Y=y; Z=z; }
    WWINLINE float Length() const { return WWMath::Sqrt(X*X+Y*Y+Z*Z); }
};
class Rva00108E33Pair
{
public:
    float X, Y;
    WWINLINE Rva00108E33Pair() : X(0.0f), Y(0.0f) {}
    WWINLINE Rva00108E33Pair(float x, float y) { X=x; Y=y; }
};
class Rva00108E7AMatrix
{
public:
    float Row[3][4];
    WWINLINE Rva00108E7AVector Get_X_Vector() const
    { return Rva00108E7AVector(Row[0][0],Row[1][0],Row[2][0]); }
    WWINLINE Rva00108E7AVector Get_Y_Vector() const
    { return Rva00108E7AVector(Row[0][1],Row[1][1],Row[2][1]); }
};

static void decalAxesRva00108E7A(const Rva00108E7AMatrix &objXform, Rva00108E7AVector &uVector, Rva00108E7AVector &vVector)
{
	uVector = objXform.Get_X_Vector();
	uVector.Z = 0.0f;
	float vecLength = uVector.Length();
	if (vecLength != 0.0f) {
		uVector *= 1.0f / vecLength;
		vVector.Set(uVector.Y, -uVector.X, 0.0f);
	} else {
		vVector = objXform.Get_Y_Vector();
		vVector.Z = 0.0f;
		vecLength = vVector.Length();
		if (vecLength != 0.0f)
			vVector *= 1.0f / vecLength;
		else
			vVector.Set(0.0f, -1.0f, 0.0f);
		uVector.Set(-vVector.Y, vVector.X, 0.0f);
	}
}

static Rva00108E33Pair minMax4Rva00108E33(float a, float b, float c, float d)
{
	float lo, hi;
	if (a < b) {
		lo = a;
		hi = b;
	} else {
		lo = b;
		hi = a;
	}
	if (c < d) {
		if (c < lo)
			lo = c;
		if (d > hi)
			hi = d;
	} else {
		if (d < lo)
			lo = d;
		if (c > hi)
			hi = c;
	}
	return Rva00108E33Pair(lo, hi);
}
// Native projected-range body 0x108FBD..0x109129 (364B, RET 0): ZH queueDecal's
// box-corner extents for the dual decal (queueDualDecal 0x10A736 and 0x10C841
// call it). Axis inputs arrive in ECX/EAX, the x/y range outputs in EDX/ESI,
// size and offset pairs on the stack; cl derives that private convention from
// the same-unit caller below. The extrema are the minMax4 logic inlined, the
// ranges are 8-byte pair copies (integer moves through a stack temporary).
static __forceinline Rva00108E33Pair minMax4Inline(float a, float b, float c, float d)
{
	float lo, hi;
	if (a < b) {
		lo = a;
		hi = b;
	} else {
		lo = b;
		hi = a;
	}
	if (c < d) {
		if (c < lo)
			lo = c;
		if (d > hi)
			hi = d;
	} else {
		if (d < lo)
			lo = d;
		if (c > hi)
			hi = c;
	}
	return Rva00108E33Pair(lo, hi);
}

static WWINLINE Rva00108E7AVector operator+(const Rva00108E7AVector&a,const Rva00108E7AVector&b){return Rva00108E7AVector(a.X+b.X,a.Y+b.Y,a.Z+b.Z);}
static void projectRangesRva00108FBD(const Rva00108E7AVector &axisA, const Rva00108E7AVector &axisB, float sizeA, float sizeB,
	float offA, float offB, Rva00108E33Pair &xr, Rva00108E33Pair &yr)
{
	Rva00108E7AVector a0(axisA.X * (-((offA + 0.5f) * sizeA)), axisA.Y * (-((offA + 0.5f) * sizeA)), 0.0f);
	Rva00108E7AVector a1(axisA.X * ((0.5f - offA) * sizeA), axisA.Y * ((0.5f - offA) * sizeA), 0.0f);
	Rva00108E7AVector b0(axisB.X * (-((offB + 0.5f) * sizeB)), axisB.Y * (-((offB + 0.5f) * sizeB)), 0.0f);
	Rva00108E7AVector b1(axisB.X * ((0.5f - offB) * sizeB), axisB.Y * ((0.5f - offB) * sizeB), 0.0f);
	Rva00108E7AVector c0 = b0 + a0;
	Rva00108E7AVector c1 = b0 + a1;
	Rva00108E7AVector c2 = b1 + a1;
	Rva00108E7AVector c3 = b1 + a0;
	xr = minMax4Inline(c0.X, c1.X, c2.X, c3.X);
	yr = minMax4Inline(c0.Y, c1.Y, c2.Y, c3.Y);
}

class Object {public:int rva0028B511()const;};
class Drawable {public:char pad[0xfc];Object*object;};
struct DrawableInfo {void*unknown;Drawable*drawable;};
class RenderObjClass{public:
virtual void slot0();
virtual void slot1();
virtual void slot2();
virtual void slot3();
virtual void slot4();
virtual void slot5();
virtual void slot6();
virtual void slot7();
virtual void slot8();
virtual void slot9();
virtual void slot10();
virtual void slot11();
virtual void slot12();
virtual void slot13();
virtual void slot14();
virtual void slot15();
virtual void slot16();
virtual void slot17();
virtual void slot18();
virtual void slot19();
virtual void Validate_Transform();
virtual void slot21();
virtual void slot22();
virtual void slot23();
virtual void slot24();
virtual void slot25();
virtual void slot26();
virtual void slot27();
virtual void slot28();
virtual void slot29();
virtual void slot30();
virtual void slot31();
virtual void slot32();
virtual void slot33();
virtual void slot34();
virtual void slot35();
virtual void slot36();
virtual void slot37();
virtual void slot38();
virtual void slot39();
virtual void slot40();
virtual void slot41();
virtual void slot42();
virtual void slot43();
virtual void slot44();
virtual void slot45();
virtual void slot46();
virtual void slot47();
virtual void slot48();
virtual void slot49();
virtual void slot50();
virtual void slot51();
virtual void slot52();
virtual void slot53();
virtual void slot54();
virtual void slot55();
virtual void slot56();
virtual void slot57();
virtual void slot58();
virtual void slot59();
virtual void slot60();
virtual void slot61();
virtual void slot62();
virtual void slot63();
virtual void slot64();
virtual void slot65();
virtual void slot66();
virtual void slot67();
virtual void slot68();
virtual void slot69();
virtual void slot70();
virtual void slot71();
virtual void slot72();
virtual void slot73();
virtual void slot74();
virtual void slot75();
virtual void slot76();
virtual void slot77();
virtual void slot78();
virtual void slot79();
virtual void slot80();
virtual void slot81();
virtual void slot82();
virtual void slot83();
virtual void slot84();
virtual void slot85();
virtual void slot86();
virtual DrawableInfo*Get_User_Data();
Vector3 Get_Position()const;
char pad04[0x14];Matrix3D transform;
};
class TerrainLogic {public:
virtual void pad0();
virtual void pad1();
virtual void pad2();
virtual void pad3();
virtual void pad4();
virtual void pad5();
virtual void pad6();
virtual float getLayerHeight(float,float,int,Rva00108E7AVector*,bool);
};extern TerrainLogic*TheTerrainLogic;
static float layerHeightRva001086EC(RenderObjClass*robj,const Rva00108E7AVector&pos,Rva00108E7AVector&normal){
 if(robj&&robj->Get_User_Data()){
 Drawable*draw=robj->Get_User_Data()->drawable;char*drawBytes=(char*)draw;Object*object=*(Object**)(drawBytes+0xfc);
 if(object){int layer=object->rva0028B511();if(layer!=1&&TheTerrainLogic){Rva00108E7AVector n;float height=TheTerrainLogic->getLayerHeight(pos.X,pos.Y,layer,&n,true);normal=n;return height+1.5f;}}
 }
 normal.Set(0,0,1);return 0;
}

// ?Rva00108E33EmissionPattern absent-from-retail
void Rva00108E33EmissionPattern(float a, float b, float c, float d, Rva00108E33Pair *out)
{
    out[0] = minMax4Rva00108E33(a, b, c, d);
    out[1] = minMax4Rva00108E33(b, c, d, a);
}

class W3DShadowTexture;
typedef float Real;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef bool Bool;
enum ShadowType { SHADOW_NONE = 0 };

__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}
#define REAL_TO_INT_CEIL(x)		(fast_float2long_round(ceilf(x)))
#define REAL_TO_INT_FLOOR(x)	(fast_float2long_round(floorf(x)))

#define MAP_XY_FACTOR		(10.0f)
#define MAP_HEIGHT_SCALE	(MAP_XY_FACTOR/256.0f)

// The decal halves of a dual projected shadow (target offsets).
struct DualDecalChild
{
	char m_pad00[8];
	Coord3D m_position;					// +0x08
	char m_pad14[0xC];
	Real m_angle;						// +0x20
	char m_pad24[0x34];
	Real m_decalSizeX;					// +0x58
	Real m_decalSizeY;					// +0x5C
	char m_pad60[8];
	W3DShadowTexture *m_shadowTexture;	// +0x68
	Real m_decalOffsetU;				// +0x6C
	Real m_decalOffsetV;				// +0x70
};

class W3DDualProjectedShadow
{
public:
	W3DShadowTexture *getTexture(Int i) const { return m_child[i] ? m_child[i]->m_shadowTexture : 0; }
	void getSize(Int i, Real *x, Real *y) const { DualDecalChild *c = m_child[i]; *x = c->m_decalSizeX; *y = c->m_decalSizeY; }
	Real getAngle(Int i) const { return m_child[i]->m_angle; }
	Real getAngle() const { return m_angle; }
	void getPosition(Int i, Coord3D *pos) const { DualDecalChild *c = m_child[i]; *pos = c->m_position; }
	void getDecalOffset(Int i, Real *u, Real *v) const { DualDecalChild *c = m_child[i]; if (c) { *u = c->m_decalOffsetU; *v = c->m_decalOffsetV; } }

	char m_pad00[8];
	Coord3D m_position;					// +0x08
	Coord3D m_normal;					// +0x14
	Real m_angle;						// +0x20
	Int m_pad24;
	UnsignedInt m_diffuse;				// +0x28
	char m_pad2c[8];
	ShadowType m_type;					// +0x34
	char m_pad38[0x20];
	DualDecalChild *m_child[2];			// +0x58
	RenderObjClass *m_robj;				// +0x60
};

struct SHADOW_DECAL_DUAL_VERTEX { Real x, y, z; UnsignedInt diffuse; Real u0, v0, u1, v1; };
class VertexBufferClass { public: class AppendLockClass { public: AppendLockClass(VertexBufferClass *, unsigned, unsigned, int); ~AppendLockClass(); void *Get_Vertex_Array() { return m_vertices; } VertexBufferClass *m_buffer; void *m_vertices; char m_lock[4]; }; };
class IndexBufferClass { public: class AppendLockClass { public: AppendLockClass(IndexBufferClass *, unsigned, unsigned, int); ~AppendLockClass(); unsigned short *Get_Index_Array() { return m_indices; } IndexBufferClass *m_buffer; unsigned short *m_indices; char m_lock[4]; }; };
class BoundedShortGrid { public: short rva00062A58(int, int); };
class Gen_0074B410 { public: bool bfmeBitA(int, int) const; };
class WorldHeightMap
{
public:
	UnsignedShort getHeight(Int x, Int y) { return ((BoundedShortGrid *)this)->rva00062A58(x, y); }
	Real getDisplayHeight(Int x, Int y) { return getHeight(x, y) * MAP_HEIGHT_SCALE; }
	Bool getFlipState(Int x, Int y) const { return ((const Gen_0074B410 *)this)->bfmeBitA(x, y); }
	char m_pad00[0x10];
	Int m_borderSize;					// +0x10
};
class BaseHeightMapRenderObjClass { public: char m_pad[0x37c0]; WorldHeightMap *m_map; };
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern int g_Va00DEC2E4, g_Va00DEC2E8, g_Va00DEC2DC, g_Va00DEC2E0;
#define drawStartX	g_Va00DEC2E4
#define drawStartY	g_Va00DEC2E8
#define drawEdgeX	g_Va00DEC2DC
#define drawEdgeY	g_Va00DEC2E0

class W3DProjectedShadowManager
{
public:
	void queueDualDecal(W3DDualProjectedShadow *shadow);
	void flushDecals(ShadowType type, W3DShadowTexture *texture0, W3DShadowTexture *texture1, Int flags);
	char m_pad[0x254];
	VertexBufferClass *m_dynamicDecalVertexBuffer;	// +0x254
	IndexBufferClass *m_dynamicDecalIndexBuffer;	// +0x258
	Int m_numDecalVertsInBuffer;		// +0x25C
	Int m_decalStartVertex;				// +0x260
	Int m_numDecalIndicesInBuffer;		// +0x264
	Int m_decalStartIndex;				// +0x268
	Int m_numDecalPolysInBatch;			// +0x26C
	Int m_numDecalVertsInBatch;			// +0x270
};

void W3DProjectedShadowManager::queueDualDecal(W3DDualProjectedShadow *shadow)
{
	W3DShadowTexture *texture0 = shadow->getTexture(0);
	W3DShadowTexture *texture1 = shadow->getTexture(1);
	if (!texture0 || !texture1)
		return;

	Real decalSizeX[2], decalSizeY[2];
	shadow->getSize(0, &decalSizeX[0], &decalSizeY[0]);
	shadow->getSize(1, &decalSizeX[1], &decalSizeY[1]);
	if ((decalSizeX[0] == 0.0f || decalSizeY[0] == 0.0f) && (decalSizeX[1] == 0.0f || decalSizeY[1] == 0.0f))
		return;

	Matrix3D objXform(true);
	Vector3 objPos;
	Vector3 normal;
	Real layerHeight = 0.0f;
	RenderObjClass *robj = shadow->m_robj;
	if (robj)
	{
		objPos = robj->Get_Position();
		objPos.Z = 0.0f;
		robj->Validate_Transform();
		objXform = robj->transform;
		layerHeight = layerHeightRva001086EC(robj, *(Rva00108E7AVector *)&objPos, *(Rva00108E7AVector *)&normal);
	}
	else
	{
		Coord3D pos;
		pos = shadow->m_position;
		objPos.X = pos.x;
		objPos.Y = pos.y;
		objPos.Z = 0.0f;
		objXform.Rotate_Z(shadow->m_angle);
		normal = Vector3(shadow->m_normal.x, shadow->m_normal.y, shadow->m_normal.z);
	}

	Matrix3D rotations[2];
	rotations[0].Make_Identity();
	rotations[1].Make_Identity();
	rotations[0].Rotate_Z(shadow->getAngle(0) + shadow->getAngle());
	rotations[1].Rotate_Z(shadow->getAngle() + shadow->getAngle(1));

	Vector3 uVector[2], vVector[2];
	decalAxesRva00108E7A(*(Rva00108E7AMatrix *)&rotations[0], *(Rva00108E7AVector *)&uVector[0], *(Rva00108E7AVector *)&vVector[0]);
	decalAxesRva00108E7A(*(Rva00108E7AMatrix *)&rotations[1], *(Rva00108E7AVector *)&uVector[1], *(Rva00108E7AVector *)&vVector[1]);

	Vector3 decalPos[2];
	Coord3D pos;
	shadow->getPosition(0, &pos);
	decalPos[0].X = pos.x;
	decalPos[0].Y = pos.y;
	decalPos[0].Z = 0.0f;
	shadow->getPosition(1, &pos);
	decalPos[1].X = pos.x;
	decalPos[1].Y = pos.y;
	decalPos[1].Z = 0.0f;
	objXform.mulVector3(decalPos[0]);
	objXform.mulVector3(decalPos[1]);

	Real uOffset[2], vOffset[2];
	shadow->getDecalOffset(0, &uOffset[0], &vOffset[0]);
	shadow->getDecalOffset(1, &uOffset[1], &vOffset[1]);

	Rva00108E33Pair xRange[2];
	Rva00108E33Pair yRange[2];
	projectRangesRva00108FBD(*(Rva00108E7AVector *)&uVector[0], *(Rva00108E7AVector *)&vVector[0], decalSizeX[0], decalSizeY[0], uOffset[0], vOffset[0], xRange[0], yRange[0]);
	projectRangesRva00108FBD(*(Rva00108E7AVector *)&uVector[1], *(Rva00108E7AVector *)&vVector[1], decalSizeX[1], decalSizeY[1], uOffset[1], vOffset[1], xRange[1], yRange[1]);

	decalPos[0].X += objPos.X;
	decalPos[1].X += objPos.X;
	decalPos[0].Y += objPos.Y;
	decalPos[1].Y += objPos.Y;

	Rva00108E33Pair boundsX(WWMath::Min(xRange[0].X + decalPos[0].X, xRange[1].X + decalPos[1].X),
		WWMath::Max(xRange[0].Y + decalPos[0].X, xRange[1].Y + decalPos[1].X));
	Rva00108E33Pair boundsY(WWMath::Min(yRange[0].X + decalPos[0].Y, yRange[1].X + decalPos[1].Y),
		WWMath::Max(yRange[0].Y + decalPos[0].Y, yRange[1].Y + decalPos[1].Y));

	if (decalSizeX[0] == 0.0f)
		uVector[0].X = uVector[0].Y = uVector[0].Z = 0.0f;
	else
		uVector[0] /= decalSizeX[0];
	if (decalSizeX[1] == 0.0f)
		uVector[1].X = uVector[1].Y = uVector[1].Z = 0.0f;
	else
		uVector[1] /= decalSizeX[1];
	if (decalSizeY[0] == 0.0f)
		vVector[0].X = vVector[0].Y = vVector[0].Z = 0.0f;
	else
		vVector[0] /= decalSizeY[0];
	if (decalSizeY[1] == 0.0f)
		vVector[1].X = vVector[1].Y = vVector[1].Z = 0.0f;
	else
		vVector[1] /= decalSizeY[1];

	uOffset[0] += 0.5f;
	uOffset[1] += 0.5f;
	vOffset[0] += 0.5f;
	vOffset[1] += 0.5f;

	Real mapScaleInv = 1.0f / MAP_XY_FACTOR;
	WorldHeightMap *hmap = TheTerrainRenderObject->m_map;
	Int borderSize = hmap->m_borderSize;

	Int startX = REAL_TO_INT_FLOOR(boundsX.X * mapScaleInv) + borderSize;
	Int endX = REAL_TO_INT_CEIL(boundsX.Y * mapScaleInv) + borderSize;
	Int startY = REAL_TO_INT_FLOOR(boundsY.X * mapScaleInv) + borderSize;
	Int endY = REAL_TO_INT_CEIL(boundsY.Y * mapScaleInv) + borderSize;

	startX = __max(startX, drawStartX);
	startX = __min(startX, drawEdgeX);
	startY = __max(startY, drawStartY);
	startY = __min(startY, drawEdgeY);

	endX = __max(endX, drawStartX);
	endX = __min(endX, drawEdgeX);
	endY = __max(endY, drawStartY);
	endY = __min(endY, drawEdgeY);

	Int numExtraX = (endX - startX + 1) - 104;
	if (numExtraX > 0)
	{
		Int numStartExtraX = REAL_TO_INT_FLOOR((float)numExtraX / 2.0f);
		Int numEdgeExtraX = numExtraX - numStartExtraX;
		startX += numStartExtraX;
		endX -= numEdgeExtraX;
	}
	Int numExtraY = (endY - startY + 1) - 104;
	if (numExtraY > 0)
	{
		Int numStartExtraY = REAL_TO_INT_FLOOR((float)numExtraY / 2.0f);
		Int numEdgeExtraY = numExtraY - numStartExtraY;
		startY += numStartExtraY;
		endY -= numEdgeExtraY;
	}

	Int vertsPerRow = endX - startX + 1;
	Int vertsPerColumn = endY - startY + 1;
	if (vertsPerRow <= 1 || vertsPerColumn <= 1)
		return;

	Int numVerts = vertsPerRow * vertsPerColumn;
	Int numIndex = (endX - startX) * (endY - startY) * 6;

	Bool flushed = false;
	if (m_numDecalVertsInBuffer + numVerts > 0x8000 || m_numDecalIndicesInBuffer + numIndex > 0x10000)
	{
		flushDecals(shadow->m_type, texture0, texture1, 0);
		m_decalStartVertex = 0;
		m_decalStartIndex = 0;
		m_numDecalPolysInBatch = 0;
		m_numDecalVertsInBatch = 0;
		m_numDecalVertsInBuffer = 0;
		m_numDecalIndicesInBuffer = 0;
		flushed = true;
	}

	{
	VertexBufferClass::AppendLockClass lockVtxBuffer(m_dynamicDecalVertexBuffer, m_numDecalVertsInBuffer, numVerts, flushed ? 0x2000 : 0x1000);
	SHADOW_DECAL_DUAL_VERTEX *pvVertices = (SHADOW_DECAL_DUAL_VERTEX *)lockVtxBuffer.Get_Vertex_Array();
	if (!pvVertices)
		return;
	IndexBufferClass::AppendLockClass lockIdxBuffer(m_dynamicDecalIndexBuffer, m_numDecalIndicesInBuffer, numIndex, flushed ? 0x2000 : 0x1000);
	UnsignedShort *pvIndices = lockIdxBuffer.Get_Index_Array();
	if (!pvIndices)
		return;

	Vector3 hmapVertex;
	Vector3 decalVertex[2];
	UnsignedInt diffuse = shadow->m_diffuse;
	if (layerHeight)
	{
		for (Int j = startY; j <= endY; j++)
		{
			hmapVertex.Y = (float)(j - borderSize) * MAP_XY_FACTOR;
			for (Int i = startX; i <= endX; i++)
			{
				hmapVertex.X = (float)(i - borderSize) * MAP_XY_FACTOR;
				hmapVertex.Z = __max((float)hmap->getHeight(i, j) * MAP_HEIGHT_SCALE, layerHeight);
				decalVertex[0] = hmapVertex - decalPos[0];
				decalVertex[1] = hmapVertex - decalPos[1];
				pvVertices->x = hmapVertex.X;
				pvVertices->y = hmapVertex.Y;
				pvVertices->z = hmapVertex.Z;
				pvVertices->diffuse = diffuse;
				pvVertices->u0 = Vector3::Dot_Product(uVector[0], decalVertex[0]) + uOffset[0];
				pvVertices->v0 = Vector3::Dot_Product(vVector[0], decalVertex[0]) + vOffset[0];
				pvVertices->u1 = Vector3::Dot_Product(uVector[1], decalVertex[1]) + uOffset[1];
				pvVertices->v1 = Vector3::Dot_Product(vVector[1], decalVertex[1]) + vOffset[1];
				pvVertices++;
			}
		}
	}
	else
	{
		for (Int j = startY; j <= endY; j++)
		{
			hmapVertex.Y = (float)(j - borderSize) * MAP_XY_FACTOR;
			for (Int i = startX; i <= endX; i++)
			{
				hmapVertex.X = (float)(i - borderSize) * MAP_XY_FACTOR;
				hmapVertex.Z = (float)hmap->getHeight(i, j) * MAP_HEIGHT_SCALE + 0.01f * MAP_XY_FACTOR;
				decalVertex[0] = hmapVertex - decalPos[0];
				decalVertex[1] = hmapVertex - decalPos[1];
				pvVertices->x = hmapVertex.X;
				pvVertices->y = hmapVertex.Y;
				pvVertices->z = hmapVertex.Z;
				pvVertices->diffuse = diffuse;
				pvVertices->u0 = Vector3::Dot_Product(uVector[0], decalVertex[0]) + uOffset[0];
				pvVertices->v0 = Vector3::Dot_Product(vVector[0], decalVertex[0]) + vOffset[0];
				pvVertices->u1 = Vector3::Dot_Product(uVector[1], decalVertex[1]) + uOffset[1];
				pvVertices->v1 = Vector3::Dot_Product(vVector[1], decalVertex[1]) + vOffset[1];
				pvVertices++;
			}
		}
	}

	Int rowStart, j;
	for (j = startY, rowStart = 0; j < endY; j++, rowStart += vertsPerRow)
	{
		for (Int i = rowStart, k = startX; k < endX; i++, k++)
		{
			if (hmap->getFlipState(k, j))
			{
				pvIndices[0] = i + 1 + m_numDecalVertsInBatch;
				pvIndices[1] = i + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[2] = i + m_numDecalVertsInBatch;
				pvIndices[3] = i + 1 + m_numDecalVertsInBatch;
				pvIndices[4] = i + 1 + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[5] = i + vertsPerRow + m_numDecalVertsInBatch;
			}
			else
			{
				pvIndices[0] = i + m_numDecalVertsInBatch;
				pvIndices[1] = i + 1 + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[2] = i + vertsPerRow + m_numDecalVertsInBatch;
				pvIndices[3] = i + m_numDecalVertsInBatch;
				pvIndices[4] = i + 1 + m_numDecalVertsInBatch;
				pvIndices[5] = i + 1 + vertsPerRow + m_numDecalVertsInBatch;
			}
			pvIndices += 6;
		}
	}
	}

	m_numDecalPolysInBatch += (endX - startX) * (endY - startY) * 2;
	m_numDecalVertsInBuffer += numVerts;
	m_numDecalVertsInBatch += numVerts;
	m_numDecalIndicesInBuffer += numIndex;
}
